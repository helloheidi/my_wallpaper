#include "include/ImageGroup.h"
#include <qdebug.h>
#include <qpainter.h>
#include <QtConcurrent/qtconcurrentrun.h>
#include <qdir.h>
#include <qdiriterator.h>
#include <qset.h>

ImageGroup::ImageGroup(QObject* parent)
    : QObject(parent)
{
    QString path1 = QString(QDir::currentPath() + "/resource/mywallpaper/");//本地图片路径
    QDirIterator it(path1, QStringList() << "*.png" << "*.jpg" << "*.jpeg", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        new_images_ << it.next();
    }
    all_images_.append(new_images_);
}

ImageGroup::~ImageGroup()
{
}

//向图片数组中添加图片
bool ImageGroup::addImage(const QStringList& img_paths)
{
    if (img_paths.empty()) return false;
    //清空新增图片数组
    new_images_.clear();
    new_images_ = img_paths;
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
    //将新增图片添加至全部图片数组
    all_images_.reserve(all_images_.size() + new_images_.size());
    all_images_.append(new_images_);
    return true;
}
//生成缩略图并添加item
void ImageGroup::creatPreviewPixmap()
{
    //for (int i = 0; i < all_images_.size(); i++) {
    //    qDebug() << all_images_.at(i);
    //    QString imagePath = path_ + "/" + all_images_.at(i);
    //    QPixmap PreviewPixmap = QPixmap(imagePath).scaled(125, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //    QIcon icon(createRoundedPixmap(PreviewPixmap, 5));
    //    QListWidgetItem* newitem = new QListWidgetItem(icon, "");
    //    newitem->setSizeHint(QSize(PreviewPixmap.width(), PreviewPixmap.height()));
    //    newitem->setData(Qt::UserRole, QVariant(imagePath));
    //    newitem->setText(""); // 不需要显示文本
    //    newitem->setTextAlignment(Qt::AlignHCenter);
    //    emit sendImage(newitem);
    //}
    //emit finished();
     for (int i = 0; i < new_images_.size(); ++i) {
        QString imagePath = new_images_.at(i);
        // 异步加载图片
        QtConcurrent::run([=]() {
            qDebug() << new_images_.at(i);
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
}
//为缩略图添加圆角
QPixmap ImageGroup::createRoundedPixmap(const QPixmap& source, int radius) {
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


