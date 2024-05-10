#include "include/ImageGroup.h"
#include <qdebug.h>
#include <qpainter.h>
#include <QtConcurrent/qtconcurrentrun.h>
#include <qdir.h>
#include <qdiriterator.h>
#include <qset.h>
#include <QLabel>
#include <QMovie>
#include <QBitmap>

ImageGroup::ImageGroup(QObject* parent)
    : QObject(parent)
{
    QFile configFile("resource/config.txt");
    if (!configFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Unable to open config file for reading.";
        qDebug() << "Current Path:" << QDir::currentPath();
        qDebug() << "Current Path:" << QCoreApplication::applicationDirPath();
        return;
    }
    QTextStream in(&configFile);
    QString line;

    while (in.readLineInto(&line)) {
        qDebug() << line;
        QFileInfo checkFile(line);
        if (checkFile.exists() && checkFile.isFile()) {
            // 检查缩略图是否存在
            QString previewPath_jpg = checkFile.absoluteDir().absolutePath() + "/" + checkFile.completeBaseName() + "_preview.jpg";
            QString previewPath_gif = checkFile.absoluteDir().absolutePath() + "/" + checkFile.completeBaseName() + "_preview.gif";
            if (!QFile::exists(previewPath_jpg) && !QFile::exists(previewPath_gif)) {
                // 如果缩略图不存在，则生成
                createThumbnail(line, checkFile.baseName(), checkFile.dir().path());
            }
            new_images_.append(line);
            all_images_.append(line);
        }        
    }
    configFile.close();   
}

ImageGroup::~ImageGroup()
{
}

//向图片数组中添加图片
bool ImageGroup::addImage(const QStringList& img_paths)
{
    //清空新增图片数组
    new_images_.clear();
    new_images_ = img_paths;
    if (new_images_.empty()) return false;
    //从新添加的图片列表中提出源列表中已经存在的图片路径
    QSet<QString> pathsSet(all_images_.begin(), all_images_.end());
    QStringList filteredNewPaths;
    for (const QString& path : new_images_) {
        if (!pathsSet.contains(path)) {
            filteredNewPaths.append(path);
            qDebug() << "fuck you" << path;
        }
    }
    new_images_ = filteredNewPaths;
    processImages(new_images_);
    //creatPreviewPixmap();
    //将新增图片添加至全部图片数组
    all_images_.reserve(all_images_.size() + new_images_.size());
    all_images_.append(new_images_);
    return true;
}

//将添加的图片拷贝到本地文件夹并创建缩略图
void ImageGroup::processImages(QStringList& fileNames) {
    QFile configFile("resource/config.txt");
    if (!configFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Unable to open config file for writing.";
        return;
    }
    QTextStream out(&configFile);

    foreach(const QString & filePath, fileNames) {
        QFileInfo fileInfo(filePath);
        QString baseName = fileInfo.baseName();
        QString dirPath = "resource/data/" + baseName;

        // 创建目录
        if (!QDir().mkpath(dirPath)) {  // 使用mkpath创建文件夹
            qDebug() << "Failed to create directory:" << dirPath;
            continue;  // 如果创建失败，则跳过这个文件
        }

        // 复制文件
        QString newFilePath = dirPath + "/" + fileInfo.fileName();
        bool success = QFile::copy(filePath, newFilePath);
        if (!success) {
            continue;  // 如果拷贝失败，则跳过这个文件
        }
        // 创建缩略图
        createThumbnail(newFilePath, baseName, dirPath);
        // 保存图片路径到配置文件
        out << newFilePath << "\n";
    }
    configFile.close();
}

//线程池创建缩略图
void ImageGroup::createThumbnail(const QString& filePath, const QString& baseName, const QString& dirPath) {    
    QtConcurrent::run([=]() {
        QImage image(filePath);
        if (image.isNull()) {
            return;  // 如果图片加载失败，返回
        }

        const QSize targetSize(320, 320);
        qreal scale = qMax(
            static_cast<qreal>(targetSize.width()) / image.width(),
            static_cast<qreal>(targetSize.height()) / image.height()
        );

        QImage scaled = image.scaled(
            image.width() * scale,
            image.height() * scale,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        );

        int x = (scaled.width() - targetSize.width()) / 2;
        int y = (scaled.height() - targetSize.height()) / 2;

        QImage cropped = scaled.copy(x, y, targetSize.width(), targetSize.height());
        cropped.save(dirPath + "/" + baseName + "_preview.jpg");

        emit sendImage(filePath);  // 确保信号与槽通过 Qt::QueuedConnection 连接
        });
}

//添加item
void ImageGroup::creatPreviewPixmap()
{
    for(QString & filePath : new_images_) {
        qDebug() << "fucking send" << filePath;
        emit sendImage(filePath);
    }
}

//为缩略图添加圆角
QPixmap ImageGroup::createRoundedPixmap(const QPixmap& source, int radius) {

    //QLabel* label = new QLabel;
    //QMovie* movie = new QMovie(gifPath);
    //label->setMovie(movie);
    //movie->start();

    //QBitmap bitmap(movie->currentPixmap().size());
    //bitmap.fill(Qt::color0);  // 初始化为全透明

    //QPainter painter(&bitmap);
    //painter.setRenderHint(QPainter::Antialiasing, true); // 开启抗锯齿
    //QPainterPath path;
    //path.addRoundedRect(0, 0, bitmap.width(), bitmap.height(), 50, 50);  // 注意这里直接使用控件的宽度和高度

    //painter.fillPath(path, Qt::color1);  // 使用不透明的颜色填充路径
    //label->setMask(bitmap);  // 应用遮罩

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


