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

//��ͼƬ���������ͼƬ
bool ImageGroup::addImage(const QStringList& img_paths)
{
    if (img_paths.empty()) return false;
    //�������ͼƬ����
    new_images_.clear();
    new_images_ = img_paths;
    for (auto& path : img_paths)
    {
        all_images_.push_back(path);
    }
    return true;
}
//��������ͼ�����item
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
        newitem->setText(""); // ����Ҫ��ʾ�ı�
        newitem->setTextAlignment(Qt::AlignHCenter);
        emit sendImage(newitem);
    }
    emit finished();
}
//Ϊ����ͼ���Բ��
QPixmap ImageGroup::createRoundedPixmap(const QPixmap& source, int radius) {
    if (source.isNull()) return QPixmap();  // ���ؿյ� QPixmap ���Դ�ǿյ�

    QPixmap pixmap(source.size());
    pixmap.fill(Qt::transparent);  // ʹ��͸����ɫ���

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);  // �����
    painter.setBrush(QBrush(source));  // ���û�ˢΪԭͼ
    painter.setPen(Qt::NoPen);  // �����ޱ߿򻭱ʣ������߿�

    // ����Բ�Ǿ��Σ��������Ϊ����ͼ��
    painter.drawRoundedRect(pixmap.rect(), radius, radius);

    return pixmap;
}


