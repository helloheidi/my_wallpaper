#include "mainwidget.h"
#include "imageview.h"

#include <qdebug.h>
#include <qlistWidget.h>
#include <qdir.h>
#include <QVBoxLayout>
#include <QtConcurrent/qtconcurrentrun.h>
#include <qpainter.h>


MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::MainWidgetClass)
    , desktopWidget(new DesktopWidget())
{
	ui->setupUi(this);
    this->setWindowIcon(QIcon(":/resource/icon.png"));
    // 设置 QTextBrowser 的默认字体
    QFont font("Microsoft YaHei", 10);  // 字体名和字体大小
    ui->ImageSizeInfo->setFont(font);
    ui->ImageNameInfo->setFont(font);
	ui->ImagelistWidget->setIconSize(QSize(125, 125));//设置单个Icon大小
	ui->ImagelistWidget->setViewMode(QListView::IconMode);//设置显示模式
	ui->ImagelistWidget->setFlow(QListView::LeftToRight);//从左到右
	ui->ImagelistWidget->setResizeMode(QListView::Adjust);//大小自适应
	ui->ImagelistWidget->setMovement(QListView::Static);//设置列表每一项不可移动

    path = QString(QDir::currentPath() + "/resource/op/");//本地图片路径
    QDir dir(path);

    //namefiles和files为QStringList类型
    namefiles << "*.png" << "*.jpg";

    //查找本地图片路径下的png后缀和jpg后缀的图片名  xxx.png  xxx.jpg
    files = dir.entryList(namefiles, QDir::Files | QDir::Readable, QDir::Name);
    QThread* thread = new QThread;   // 创建一个 QThread 对象
    ImagePaths = new ImageGroup(path, files);
    ImagePaths->moveToThread(thread);
    QObject::connect(thread, &QThread::started, ImagePaths, &ImageGroup::creatPreviewPixmap);  // 线程开始时调用 doWork
    QObject::connect(ImagePaths, &ImageGroup::finished, thread, &QThread::quit);   // 工作完成时退出线程
    QObject::connect(thread, &QThread::finished, ImagePaths, &QObject::deleteLater);  // 线程结束后删除 worker 对象
    QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);  // 线程结束后删除线程对象

    thread->start();  // 启动线程，会触发 QThread::started 信号
    //for (int i = 0; i < files.size(); ++i) {
    //    QString imagePath = path + "/" + files.at(i);
    //    // 异步加载图片
    //    QtConcurrent::run([=]() {
    //        qDebug() << files.at(i);
    //        QIcon icon(createRoundedPixmap(QPixmap(imagePath).scaled(125, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation), 5));
    //        QListWidgetItem* newitem = new QListWidgetItem(icon, "");
    //        //newitem->setSizeHint(QSize(125, 125));
    //        newitem->setData(Qt::UserRole, QVariant(imagePath));
    //        newitem->setText(""); // 如果不需要显示文本
    //        newitem->setTextAlignment(Qt::AlignHCenter);
    //        //ui->ImagelistWidget->addItem(newitem);
    //        emit sendImage(newitem);
    //        });
    //}

    // 连接信号到槽，以添加图标到列表
    connect(ImagePaths, &ImageGroup::sendImage, this, &MainWidget::addIconToList, Qt::QueuedConnection);
    //connect(this, &MainWidget::sendImage, this, &MainWidget::addIconToList, Qt::QueuedConnection);

    //样式表设计
    //ui->ImagelistWidget->setStyleSheet("QListWidget{background-color: white;border:none; color:black;outline:0px; }"
    ui->ImagelistWidget->setStyleSheet(
        "QListWidget::Item{padding-left:0px;padding-top:5px; padding-bottom:4px;color:black}"
        "QListWidget::Item:hover{background:lightgreen; color:red;}"
        "QListWidget::item:selected{background:lightgray; color:green; }"
    );
    connect(ui->ImagelistWidget, &QListWidget::itemDoubleClicked, this, &MainWidget::enlargeImage);
    connect(ui->ImagelistWidget, &QListWidget::itemClicked, this, &MainWidget::previewImage);
}

void MainWidget::addIconToList(QListWidgetItem* newitem) {
    ui->ImagelistWidget->addItem(newitem);
}

QPixmap MainWidget::createRoundedPixmap(const QPixmap& source, int radius) {
    if (source.isNull()) return QPixmap();  // 返回空的 QPixmap 如果源是空的

    QPixmap pixmap(source.size());
    pixmap.fill(Qt::transparent);  // 使用透明颜色填充

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);  // 抗锯齿
    painter.setBrush(QBrush(source));  // 设置画刷为原图
    painter.setPen(Qt::NoPen);  // 设置无边框画笔，消除边框

    // 绘制圆角矩形，填充区域为整个图像
    painter.drawRoundedRect(pixmap.rect(), radius, radius);

    return pixmap;
}

void MainWidget::updateImageList() {

}
//查看图片
void MainWidget::enlargeImage(QListWidgetItem* item) {
    QString filepath = item->data(Qt::UserRole).toString();
    //desktopWidget->SetPixmap(filepath);
    ImageView* showImageWidget = new ImageView();
    showImageWidget->SetImage(filepath);
    showImageWidget->show();  
}

//预览图片
void MainWidget::previewImage(QListWidgetItem* item) {
    selectImage = item->data(Qt::UserRole).toString();
    QPixmap Image = QPixmap(selectImage);
    QString Imagesize = QString("%1 × %2").arg(Image.width()).arg(Image.height());
    Image = Image.scaled(ui->ImagePreview->width(), ui->ImagePreview->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->ImagePreview->setPixmap(Image);
    ui->ImageSizeInfo->setPlainText(Imagesize);
    ui->ImageNameInfo->setPlainText(selectImage.section('/', -1));
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::on_ImageListBnt_clicked() {
	ui->stackedWidget->setCurrentIndex(0);
}

void MainWidget::on_SettingBnt_clicked() {
    if (!rolewidget) {
        rolewidget = new RoleWidget();
        rolewidget->show();
        qDebug() << "fuck you";
    }
    else {
        rolewidget->close();
        rolewidget = nullptr;
    }     
}

void MainWidget::on_SetDesktop_clicked() {
    desktopWidget->SetPixmap(selectImage);
}

void MainWidget::closeEvent(QCloseEvent* event)
{
    if (desktopWidget) {
        desktopWidget->close();
    }
    if (rolewidget) {
        desktopWidget->close();
    }
    //MainWidget::closeEvent(event);  // 调用基类的关闭事件处理
}
void MainWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPixmap pixmap(":/resource/background/Nahida-Kusanali.jpg");
    pixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(this->rect(), pixmap);
}