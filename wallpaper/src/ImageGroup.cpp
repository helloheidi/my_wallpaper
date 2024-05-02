#include "include/ImageGroup.h"
#include <qdebug.h>
#include <qpainter.h>


ImageGroup::ImageGroup(const QString& path, const QStringList& img_names, QObject* parent)
    : QObject(parent)
    , all_images_(img_names)
    , path_(path)
{
    //creatPreviewPixmap(all_images_);
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
    for (auto& path : img_paths)
    {
        all_images_.push_back(path);
    }
    return true;
}
//生成缩略图并添加item
void ImageGroup::creatPreviewPixmap()
{
    for (int i = 0; i < all_images_.size(); i++) {
        qDebug() << all_images_.at(i);
        QString imagePath = path_ + "/" + all_images_.at(i);
        QPixmap PreviewPixmap = QPixmap(imagePath).scaled(125, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QIcon icon(createRoundedPixmap(PreviewPixmap, 5));
        QListWidgetItem* newitem = new QListWidgetItem(icon, "");
        newitem->setSizeHint(QSize(PreviewPixmap.width(), PreviewPixmap.height()));
        newitem->setData(Qt::UserRole, QVariant(imagePath));
        newitem->setText(""); // 不需要显示文本
        newitem->setTextAlignment(Qt::AlignHCenter);
        emit sendImage(newitem);
    }
    emit finished();
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


