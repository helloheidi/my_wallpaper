#include "include/imageview.h"
#include <QEvent>
#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QWheelEvent>

ImageView::ImageView(QWidget* parent)
	: QWidget(parent)
{
    zoom_scale_ = 1.0f;
    move_start_ = false;
    is_moving_ = false;

    //qApp->installEventFilter(this);
    //this->setGeometry(rect);//设置显示图片窗口的x、y、w、h
    //this->setFixedSize(rect.width(), rect.height());//设置窗口固定大小
    //this->setWindowIcon(item->icon());
    this->setWindowTitle("查看图片");
    //this->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体外的其他所有窗体

    ////通过QLabel加载item上的图片
    //QLabel* lab = new QLabel(this);
    //lab->setFixedSize(this->width(), this->height());
    //lab->setPixmap(item->icon().pixmap(QSize(this->width(), this->height())).scaled(lab->width(), lab->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

ImageView::~ImageView()
{
    delete this;
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

void ImageView::resizeEvent(QResizeEvent* event)
{
    pix_display_ = pix_ori_.scaled(zoom_scale_ * size(), Qt::KeepAspectRatio);
    update();
}

//事件过滤器，实现点击窗口任意位置，窗口就可以关闭
bool ImageView::eventFilter(QObject* obj, QEvent* e)
{
    if (e->type() == QEvent::MouseButtonPress)
    {
        this->close();
    }
    return QWidget::eventFilter(obj, e);
}