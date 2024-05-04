#include "include/desktopwidget.h"
#include <QApplication>
#include <QScreen>
#include <QHBoxLayout>
#include <qt_windows.h>
#include <qvector.h>
#include <qdebug.h>
#include <qdir.h>

QSet<QString> DesktopWidget::imageFormats;
QSet<QString> DesktopWidget::videoFormats;

DesktopWidget::DesktopWidget(QWidget* parent)
    : QWidget(parent)
    , bklabel(new QLabel(this))
{
    imageFormats = { "jpg", "jpeg", "png", "bmp", "gif" };//设置可加载格式
    videoFormats = { "mp4", "avi", "mov", "mkv", "flv", "wmv" };
    //setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);
    //QHBoxLayout* layout = new QHBoxLayout(this);
    //layout->setMargin(0);
    //layout->addWidget(bklabel);
    // 获取主屏幕
    QScreen* screen = QApplication::primaryScreen();
    // 获取屏幕分辨率
    QRect screenGeometry = screen->geometry();
    screenWidth = screenGeometry.width();
    screenHeight = screenGeometry.height();
    SetBackground((HWND)this->winId());

    
    videoPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    videoWidget->setGeometry(0, 0, screenWidth, screenHeight);
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
    //videoWidget->setWindowState(Qt::WindowMaximized);
    //videoWidget->setWindowFlags(Qt::FramelessWindowHint);
    
    videoPlayer->setVideoOutput(videoWidget);
    connect(videoPlayer, &QMediaPlayer::mediaStatusChanged, this, &DesktopWidget::onMediaStatusChanged);
}

DesktopWidget::~DesktopWidget()
{}

//获取背景窗体句柄"D:/Electronic_2/MyProject/wallpaper/wallpaper/resource/video/心海.mp4"
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

void DesktopWidget::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::LoadedMedia) {
        videoPlayer->play();
        this->showFullScreen();
    }
}

void DesktopWidget::UpdateWallpaper() {
    if (filePath_.isEmpty()) {
        return;
    }
    QString suffix = QFileInfo(filePath_).suffix().toLower();
    if (imageFormats.contains(suffix)) {
        qDebug() << "The file is an image.";
    }
    else if (videoFormats.contains(suffix)) {
        qDebug() << "The file is a video.";
    }
    else {
        qDebug() << "Unknown file type.";
    }
}

void DesktopWidget::showVideo(QString filePath) {
    videoPlayer->setMedia(QUrl::fromLocalFile(filePath));
}

void DesktopWidget::showImage(QString filePath) {
    if (QPixmap(filePath_).isNull()) {
        return;
    }
    QPixmap bkPixmap;
	bkPixmap.load(filePath);

    switch (imageMode_) {
    case 0://填充
        {
            QSize scaledSize = bkPixmap.size();
            scaledSize.scale(screenWidth, screenHeight, Qt::KeepAspectRatioByExpanding);
            bkPixmap = bkPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
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
    bklabel->setPixmap(bkPixmap);
    bklabel->setAutoFillBackground(false); // 清除可能存在的背景色设置
	this->showFullScreen();
}
