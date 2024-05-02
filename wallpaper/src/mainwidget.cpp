#include "include/mainwidget.h"
#include "include/imageview.h"

#include <qdebug.h>
#include <qlistWidget.h>

#include <qfiledialog.h>
#include <QVBoxLayout>
#include <qpainter.h>


MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::MainWidgetClass)
    , desktopWidget(new DesktopWidget())
{
    init();
    imageGroup = new ImageGroup();
    imageGroup->creatPreviewPixmap();
    //QThread* thread = new QThread;   // 创建一个 QThread 对象
    //imageGroup = new ImageGroup(path, files);
    //imageGroup->moveToThread(thread);
    //QObject::connect(thread, &QThread::started, imageGroup, &ImageGroup::creatPreviewPixmap);  // 线程开始时调用 doWork
    //QObject::connect(imageGroup, &ImageGroup::finished, thread, &QThread::quit);   // 工作完成时退出线程
    //QObject::connect(thread, &QThread::finished, imageGroup, &QObject::deleteLater);  // 线程结束后删除 worker 对象
    //QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);  // 线程结束后删除线程对象

    //thread->start();  // 启动线程，会触发 QThread::started 信号

    // 连接信号到槽，以添加图标到列表
    connect(imageGroup, &ImageGroup::sendImage, this, &MainWidget::addIconToList, Qt::QueuedConnection);

    //样式表设计
    ui->ImagelistWidget->setStyleSheet(
        "QListWidget::Item{padding-left:0px;padding-top:5px; padding-bottom:4px;color:black}"
        "QListWidget::Item:hover{background:lightgreen; color:red;}"
        "QListWidget::item:selected{background:lightgray; color:green; }"
    );
    connect(ui->ImagelistWidget, &QListWidget::itemDoubleClicked, this, &MainWidget::enlargeImage);
    connect(ui->ImagelistWidget, &QListWidget::itemClicked, this, &MainWidget::previewImage);
}

void MainWidget::init()
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/resource/icon.png"));
    // 设置 QTextBrowser 的默认字体
    QFont font("Microsoft YaHei", 10);  // 字体名和字体大小
    ui->ImageSizeInfo->setFont(font);
    ui->ImageNameInfo->setFont(font);
    //设置图片列表
    ui->ImagelistWidget->setIconSize(QSize(125, 125));//设置单个Icon大小
    ui->ImagelistWidget->setViewMode(QListView::IconMode);//设置显示模式
    ui->ImagelistWidget->setFlow(QListView::LeftToRight);//从左到右
    ui->ImagelistWidget->setResizeMode(QListView::Adjust);//大小自适应
    ui->ImagelistWidget->setMovement(QListView::Static);//设置列表每一项不可移动
    //设置桌面图片填充模式
    ui->wallpaperMode->setFont(font);
    ui->wallpaperMode->addItem("拉伸", QVariant("stretch"));
    ui->wallpaperMode->addItem("适合", QVariant("fit"));
    ui->wallpaperMode->addItem("填充", QVariant("fill"));
    ui->wallpaperMode->addItem("居中", QVariant("center"));
    ui->wallpaperMode->addItem("平铺", QVariant("tile"));
    //connect(ui->wallpaperMode, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxChanged()));
}

void MainWidget::addIconToList(QListWidgetItem* newitem) {
    ui->ImagelistWidget->addItem(newitem);
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
	//ui->stackedWidget->setCurrentIndex(0);
    QStringList file_paths = QFileDialog::getOpenFileNames(this, tr("Image Path"), "Data\\", tr("Image Files(*png *jpg *tif);"));
    //添加图片
    imageGroup->addImage(file_paths);
    imageGroup->creatPreviewPixmap();
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
