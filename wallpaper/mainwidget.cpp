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
	ui->ImagelistWidget->setIconSize(QSize(125, 125));//设置单个Icon大小
	ui->ImagelistWidget->setViewMode(QListView::IconMode);//设置显示模式
	ui->ImagelistWidget->setFlow(QListView::LeftToRight);//从左到右
	ui->ImagelistWidget->setResizeMode(QListView::Adjust);//大小自适应
	ui->ImagelistWidget->setMovement(QListView::Static);//设置列表每一项不可移动

    path = QString(QDir::currentPath() + "/resource/kona/");//本地图片路径
    QDir dir(path);

    //namefiles和files为QStringList类型
    namefiles << "*.png" << "*.jpg";

    //查找本地图片路径下的png后缀和jpg后缀的图片名  xxx.png  xxx.jpg
    files = dir.entryList(namefiles, QDir::Files | QDir::Readable, QDir::Name);
    ImagePaths = new ImagePathGroup(files);
    for (int i = 0; i < files.size(); ++i) {
        QString imagePath = path + "/" + files.at(i);
        // 异步加载图片
        QtConcurrent::run([=]() {
            qDebug() << files.at(i);
            QIcon icon(createRoundedPixmap(QPixmap(imagePath).scaled(125, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation), 5));
            QListWidgetItem* newitem = new QListWidgetItem(icon, "");
            //newitem->setSizeHint(QSize(125, 125));
            newitem->setData(Qt::UserRole, QVariant(imagePath));
            newitem->setText(""); // 如果不需要显示文本
            newitem->setTextAlignment(Qt::AlignHCenter);
            //ui->ImagelistWidget->addItem(newitem);
            emit sendImage(newitem);
            });
    }

    // 连接信号到槽，以添加图标到列表
    connect(this, &MainWidget::sendImage, this, &MainWidget::addIconToList, Qt::QueuedConnection);
    //样式表设计
    ui->ImagelistWidget->setStyleSheet("QListWidget{background-color: white;border:none; color:black;outline:0px; }"
        "QListWidget::Item{padding-left:0px;padding-top:5px; padding-bottom:4px;color:black}"
        "QListWidget::Item:hover{background:lightgreen; color:red;}"
        "QListWidget::item:selected{background:lightgray; color:green; }"
    );
    connect(ui->ImagelistWidget, &QListWidget::itemDoubleClicked, this, &MainWidget::enlargeImage);
    connect(ui->ImagelistWidget, &QListWidget::itemClicked, this, &MainWidget::previewImage);
}

void MainWidget::addIconToList(QListWidgetItem* newitem) {
    //QIcon icon(createRoundedPixmap(QPixmap(imagePath).scaled(125, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation), 5));
    //QListWidgetItem* newitem = new QListWidgetItem(icon, "");
    ////newitem->setSizeHint(QSize(125, 125));
    //newitem->setData(Qt::UserRole, QVariant(imagePath));
    //newitem->setText(""); // 如果不需要显示文本
    //newitem->setTextAlignment(Qt::AlignHCenter);
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
    desktopWidget->SetPixmap(filepath);
    ImageView* showImageWidget = new ImageView();
    showImageWidget->SetImage(filepath);
    showImageWidget->show();
    
}

//预览图片
void MainWidget::previewImage(QListWidgetItem* item) {
    QString filepath = item->data(Qt::UserRole).toString();

    ui->ImagePreview->setPixmap(QPixmap(filepath).scaled(ui->ImagePreview->width(), ui->ImagePreview->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::on_ImageListBnt_clicked() {
	ui->stackedWidget->setCurrentIndex(0);
}

void MainWidget::on_MyImageBnt_clicked() {
	ui->stackedWidget->setCurrentIndex(2);
}

//void MainWidget::on_SetDesktop_clicked() {
//    //ui->stackedWidget->setCurrentIndex(2);
//}