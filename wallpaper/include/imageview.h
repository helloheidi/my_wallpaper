#pragma once

#include <QWidget>
#include <QListWidget>
#include <QRect>

class ImageView  : public QWidget
{
	Q_OBJECT

public:
	ImageView(QWidget* parent = 0);
	~ImageView();

	//从文件路径加载图片
	void SetImage(const QString& img_path);
	//重新设置缩放比例
	void ResetTransform();

private:

    //原始pixmap信息
    QPixmap pix_ori_;
    //用来展示的pixmap信息
    QPixmap pix_display_;
    //图片路径
    QString img_path_;
    //鼠标滚轮控制的缩放比例
    float zoom_scale_;
    //由鼠标移动控制的移动
    QPoint move_step_;
    bool move_start_;
    bool is_moving_;
    QPoint mouse_point_;
    void updateDisplayImage();

protected:
    //void closeEvent(QCloseEvent* event)override;
    void paintEvent(QPaintEvent* event)override;
    void wheelEvent(QWheelEvent* event)override;
    void mousePressEvent(QMouseEvent* event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void mouseMoveEvent(QMouseEvent* event)override;
    //void resizeEvent(QResizeEvent* event)override;
};
