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
    , imageMode_(0)
{
    init();
    imageGroup = new ImageGroup();

    //样式表设计美化界面
    ui->ImagelistWidget->setStyleSheet(R"(
        QListWidget::Item:hover{background:lightblue;}
        QListWidget::item:selected{background:lightgreen;}
        QScrollBar:vertical {
            border: 2px solid grey;
            background: #f1f1f1;
            width: 15px;
            margin: 22px 0 22px 0;
        }

        QScrollBar::handle:vertical {
            background: #888; /* 滑块的颜色 */
            min-height: 20px;
        }

        QScrollBar::add-line:vertical {
            border: 2px solid grey;
            background: #32CC99;
            height: 20px;
            subcontrol-position: bottom;
            subcontrol-origin: margin;
        }

        QScrollBar::sub-line:vertical {
            border: 2px solid grey;
            background: #32CC99;
            height: 20px;
            subcontrol-position: top;
            subcontrol-origin: margin;
        }

        QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {
            border: 2px solid grey;
            width: 3px;
            height: 3px;
            background: white;
        }

        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: none;
        }
    )");

    connect(imageGroup, &ImageGroup::sendImage, this, &MainWidget::addIconToList, Qt::QueuedConnection);  //添加图标到列表
    connect(ui->ImagelistWidget, &QListWidget::itemDoubleClicked, this, &MainWidget::enlargeImage);  //双击查看原图
    connect(ui->ImagelistWidget, &QListWidget::itemClicked, this, &MainWidget::previewImage);  //单击预览图片
    imageGroup->creatPreviewPixmap();
}

void MainWidget::init()
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/resource/icon.png"));
    this->setWindowTitle("Wallpaper");
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
    ui->wallpaperMode->hide();//bug尚未解决，先隐藏
    ui->wallpaperMode->setFont(font);
    ui->wallpaperMode->addItem("填充", QVariant("fill"));
    ui->wallpaperMode->addItem("适应", QVariant("fit"));
    ui->wallpaperMode->addItem("拉伸", QVariant("stretch"));   
    ui->wallpaperMode->addItem("居中", QVariant("center"));
    ui->wallpaperMode->addItem("平铺", QVariant("tile"));

    connect(ui->wallpaperMode, SIGNAL(currentIndexChanged(int)), this, SLOT(updateImageMode(int)));
}

//向图片列表添加缩略图图标
void MainWidget::addIconToList(QString filePath) {    
    QFileInfo fileInfo(filePath);
    QString baseName = fileInfo.baseName();
    QString dirPath = fileInfo.dir().path();
    QString thumbnailPath = dirPath + "/" + baseName + "_preview.gif";
    if (!QFile::exists(thumbnailPath)) {
        thumbnailPath = dirPath + "/" + baseName + "_preview.jpg";
    }
    qDebug() << "basename:" << baseName << "dirpath:" << dirPath << "thumbnail" << thumbnailPath;
    QListWidgetItem* newitem = new QListWidgetItem();
    ListWidgetItem* itemWidget = new ListWidgetItem(thumbnailPath);
    newitem->setSizeHint(itemWidget->sizeHint());
    newitem->setData(Qt::UserRole, QVariant(thumbnailPath));
    newitem->setData(Qt::UserRole + 1, QVariant(filePath));
    newitem->setText(""); // 如果不需要显示文本
    ui->ImagelistWidget->addItem(newitem);
    ui->ImagelistWidget->setItemWidget(newitem, itemWidget);
}

//更新图片显示模式
void MainWidget::updateImageMode(int imageMode) {
    imageMode_ = imageMode;
    desktopWidget->SetimageMode(imageMode);
    desktopWidget->UpdateWallpaper();
}

//查看图片
void MainWidget::enlargeImage(QListWidgetItem* item) {
    QString filepath = item->data(Qt::UserRole + 1).toString();
    ImageView* showImageWidget = new ImageView();
    showImageWidget->setAttribute(Qt::WA_DeleteOnClose); //关闭窗口后释放内存
    showImageWidget->SetImage(filepath);
    showImageWidget->show();
}

//预览图片
void MainWidget::previewImage(QListWidgetItem* item) {
    selectImage_pre = item->data(Qt::UserRole).toString();
    selectImage_ = item->data(Qt::UserRole + 1).toString();
    //QPixmap Image = QPixmap(selectImage_);

    QMovie* movie = new QMovie(selectImage_pre);
    ui->ImagePreview->setScaledContents(true);
    if (movie->isValid()) {
        ui->ImagePreview->setMovie(movie);
        movie->start();
    }
    else {
        // 如果不是有效的动图，就当作普通图像处理
        QPixmap pixmap(selectImage_pre);
        ui->ImagePreview->setPixmap(pixmap);
    }
    //QString Imagesize = QString("%1 × %2").arg(Image.width()).arg(Image.height());
    //Image = Image.scaled(ui->ImagePreview->width(), ui->ImagePreview->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //ui->ImagePreview->setPixmap(Image);
    //ui->ImageSizeInfo->setPlainText(Imagesize);
    ui->ImageNameInfo->setPlainText(selectImage_pre.section('/', -1));
}

MainWidget::~MainWidget()
{
	delete ui;
}

//从本地文件夹添加图片
void MainWidget::on_ImageListBnt_clicked() {
    QStringList file_paths = QFileDialog::getOpenFileNames(this, tr("Image Path"), "Data\\", tr("Image Files(*.png *.jpg *.jpeg *.mp4);"));
    //添加图片
    imageGroup->addImage(file_paths);
}

void MainWidget::on_SettingBnt_clicked() {
    if (!rolewidget) {
        rolewidget = new RoleWidget();
        rolewidget->setAttribute(Qt::WA_DeleteOnClose);
        rolewidget->show();
    }
    else {
        rolewidget->close();
        //delete rolewidget;  // 释放内存
        rolewidget = nullptr; //避免野指针
    }     
}

void MainWidget::on_SetDesktop_clicked() {
    desktopWidget->SetfilePath(selectImage_);
    desktopWidget->SetimageMode(imageMode_);
    desktopWidget->UpdateWallpaper();
}

void MainWidget::closeEvent(QCloseEvent* event)
{
    if (desktopWidget) {
        desktopWidget->close();
    }
    if (rolewidget) {
        rolewidget->close();
    }
    //MainWidget::closeEvent(event);  // 调用基类的关闭事件处理
}
void MainWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPixmap pixmap(":/resource/background/Nahida-Kusanali.jpg");
    pixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(this->rect(), pixmap);
}
