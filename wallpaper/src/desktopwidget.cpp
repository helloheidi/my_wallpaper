#include "include/desktopwidget.h"
#include <QApplication>
#include <QScreen>
#include <QHBoxLayout>
#include <qt_windows.h>
#include <qvector.h>
#include <qdebug.h>
#include <qdir.h>
#include <qpainter.h>


QSet<QString> DesktopWidget::imageFormats;
QSet<QString> DesktopWidget::videoFormats;

DesktopWidget::DesktopWidget(QWidget* parent)
    : QWidget(parent)
    , bklabel(new QLabel(this))
{
    imageFormats = { "jpg", "jpeg", "png", "bmp", "gif" };//添加支持的格式
    videoFormats = { "mp4", "avi", "mov", "mkv", "flv", "wmv" };
    //setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(screenWidth, screenHeight);

    QHBoxLayout* layout = new QHBoxLayout(this);
    
    layout->setMargin(0);
    layout->addWidget(bklabel);
    // 获取主屏幕
    QScreen* screen = QApplication::primaryScreen();
    // 获取屏幕分辨率
    QRect screenGeometry = screen->geometry();
    screenWidth = screenGeometry.width();
    screenHeight = screenGeometry.height();
    SetBackground((HWND)this->winId());

    // 创建播放列表并添加视频
    playlist = new QMediaPlaylist();
    playlist->setPlaybackMode(QMediaPlaylist::Loop);  // 设置循环播放模式
    videoPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    videoWidget->setGeometry(0, 0, screenWidth, screenHeight);
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
    
    videoPlayer->setVideoOutput(videoWidget);
    layout->addWidget(videoWidget);
}

DesktopWidget::~DesktopWidget()
{}

void DesktopWidget::UpdateWallpaper() {
    if (filePath_.isEmpty()) {
        return;
    }
    QString suffix = QFileInfo(filePath_).suffix().toLower();
    if (imageFormats.contains(suffix)) {
        
        
        showImage(filePath_);
        qDebug() << "The file is an image." << filePath_;
    }
    else if (videoFormats.contains(suffix)) {
          
        //videoWidget->show();
        showVideo(filePath_);
        qDebug() << "The file is a video." << filePath_;
    }
    else {
        qDebug() << "Unknown file type.";
    }
}

void DesktopWidget::showVideo(QString filePath) {
    playlist->clear();
    playlist->setCurrentIndex(0);
    playlist->addMedia(QUrl::fromLocalFile(filePath));
    videoPlayer->setPlaylist(playlist);  // 设置播放列表
    connect(videoPlayer, &QMediaPlayer::mediaStatusChanged, this, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::LoadedMedia) {  // 确保媒体已加载
            videoPlayer->play();
            bklabel->hide();
            this->showFullScreen();            
        }
        });
}


void DesktopWidget::showImage(QString filePath) {
    if (QPixmap(filePath).isNull()) {
        return;
    }
    QPixmap bkPixmap;
	bool success = bkPixmap.load(filePath);
    if (!success) {
        qDebug() << "image load faild.";
    }
    
    switch (2) {//参数：imageMode_,其他几种显示比例与桌面分辨率不符的图片时会出现bug，所以暂时默认拉伸了
    case 0://填充
        {
            bkPixmap = bkPixmap.scaled(screenWidth, screenHeight, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            qDebug() << "填充";
        }
        break;
    case 1://适应
        bkPixmap = bkPixmap.scaled(screenWidth, screenHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        qDebug() << "适应";
        break;
    case 2://拉伸       
        bkPixmap = bkPixmap.scaled(screenWidth, screenHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        qDebug() << "拉伸";
        break;
    case 3://居中
        bklabel->setAlignment(Qt::AlignCenter);
        qDebug() << "居中";
        break;
    case 4://平铺
        {
            QPalette palette;
            palette.setBrush(bklabel->backgroundRole(), QBrush(bkPixmap));
            bklabel->setAutoFillBackground(true);
            bklabel->setPalette(palette);
            bklabel->setPixmap(QPixmap()); // 清除可能存在的图片设置
            this->showFullScreen();
            qDebug() << "平铺";
            return; // Skip setting pixmap directly since it's set via palette
        }
    }
    bklabel->show();
    videoPlayer->stop();
    videoPlayer->setMedia(QMediaContent());  // 清除当前媒体
    bklabel->setPixmap(bkPixmap);
    bklabel->setAutoFillBackground(false); // 清除可能存在的背景色设置
	this->showFullScreen();
    //qDebug() << "Label geometry:" << bklabel->geometry();
    //qDebug() << "Parent geometry:" << (bklabel->parentWidget() ? bklabel->parentWidget()->geometry() : QRect());
}

//获取背景窗体句柄
HWND DesktopWidget::GetBackground() {
    //背景窗体没有窗体名，但是知道它的类名是workerW，且有父窗体Program Maneger，所以只要
    //遍历所有workerW类型的窗体，逐一比较它的父窗体是不是Program Manager就可以找到背景窗体
    HWND hwnd = FindWindowA("progman", "Program Manager");
    HWND worker = NULL;
    do {
        worker = FindWindowExA(NULL, worker, "workerW", NULL); // 根据类名获取窗体句柄
        if (worker != NULL) {
            char buff[200] = { 0 };
            int ret = GetClassNameA(worker, (PCHAR)buff, sizeof(buff) * 2);
            if (ret == 0) {
                return NULL;
            }
            if (GetParent(worker) == hwnd) {
                return worker;//返回结果
            }
        }
    } while (worker != NULL);
    //没有找到
    //发送消息生成一个WorkerW窗体
    SendMessage(hwnd, 0x052C, 0, 0);
    //重复上面步骤
    do {
        worker = FindWindowExA(NULL, worker, "workerW", NULL);
        if (worker != NULL) {
            char buff[200] = { 0 };
            int ret = GetClassNameA(worker, (PCHAR)buff, sizeof(buff) * 2);
            if (ret == 0) {
                return NULL;
            }
            if (GetParent(worker) == hwnd) {
                return worker;//返回结果
            }
        }
    } while (worker != NULL);
    return NULL;
}

void DesktopWidget::SetBackground(HWND child) {
    SetParent(child, GetBackground()); // 把视频窗口设置为Program Manager的儿子
}

void DesktopWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);  // 调用基类实现
    // 更新 bklabel 的大小来匹配新的窗口尺寸
    bklabel->resize(this->size());
}
