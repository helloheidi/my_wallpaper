#include "include/imageview.h"
#include <QEvent>
#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QWheelEvent>
#include <qdebug.h>

ImageView::ImageView(QWidget* parent)
	: QWidget(parent)
{
    zoom_scale_ = 1.0f;
    move_start_ = false;
    is_moving_ = false;

    this->setWindowIcon(QIcon(":/resource/icon.png"));
    this->setWindowTitle("查看图片");
}

ImageView::~ImageView()
{

}

void ImageView::SetImage(const QString& img_path)
{
    ResetTransform();
    QSize view_size = size();
    //通过QPixmap加载图像
    img_path_ = img_path;
    pix_ori_.load(img_path_);
    pix_display_ = pix_ori_.scaled(zoom_scale_ * size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

}

void ImageView::ResetTransform()
{
    //重新设置缩放比例和移动位置
    zoom_scale_ = 1.0f;
    move_step_ = QPoint(0, 0);
}

void ImageView::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(move_step_.x() + (width() - pix_display_.width()) / 2, move_step_.y() + (height() - pix_display_.height()) / 2, pix_display_);
}

void ImageView::wheelEvent(QWheelEvent* event)
{
    //随滚轮缩放
    if (event->delta() > 0)
    {
        zoom_scale_ *= 1.1;
    }
    else {
        zoom_scale_ *= 0.9;
    }
    pix_display_ = pix_ori_.scaled(zoom_scale_ * size(), Qt::KeepAspectRatio);
    update();
}

void ImageView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (!move_start_)
        {
            move_start_ = true;
            is_moving_ = false;
            mouse_point_ = event->globalPos();
        }
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (move_start_)
        {
            move_start_ = false;
            is_moving_ = false;
        }
    }
}

void ImageView::mouseMoveEvent(QMouseEvent* event)
{
    if (move_start_)
    {
        const QPoint mos_pt = event->globalPos();
        move_step_ += mos_pt - mouse_point_;
        is_moving_ = true;
        mouse_point_ = mos_pt;
        repaint();
    }
}

//void ImageView::resizeEvent(QResizeEvent* event)
//{
//    pix_display_ = pix_ori_.scaled(zoom_scale_ * size(), Qt::KeepAspectRatio);
//    update();
//}

//void ImageView::closeEvent(QCloseEvent *event) {
//    delete this;
//}