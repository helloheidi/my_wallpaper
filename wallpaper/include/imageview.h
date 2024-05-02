#pragma once
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QWidget>
#include <QListWidget>
#include <QRect>

class ImageView  : public QWidget
{
	Q_OBJECT

public:
	ImageView(QWidget* parent = 0);
	~ImageView();

	//���ļ�·������ͼƬ
	void SetImage(const QString& img_path);
	//�����������ű���
	void ResetTransform();

private:

    //ԭʼpixmap��Ϣ
    QPixmap pix_ori_;
    //����չʾ��pixmap��Ϣ
    QPixmap pix_display_;
    //ͼƬ·��
    QString img_path_;
    //�����ֿ��Ƶ����ű���
    float zoom_scale_;
    //������ƶ����Ƶ��ƶ�
    QPoint move_step_;
    bool move_start_;
    bool is_moving_;
    QPoint mouse_point_;

protected:
	bool eventFilter(QObject* obj, QEvent* e);
    void paintEvent(QPaintEvent* event)override;
    void wheelEvent(QWheelEvent* event)override;
    void mousePressEvent(QMouseEvent* event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void mouseMoveEvent(QMouseEvent* event)override;
    void resizeEvent(QResizeEvent* event)override;
};
