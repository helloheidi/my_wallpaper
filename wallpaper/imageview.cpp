#include "imageview.h"
#include <QEvent>
#include <QApplication>
#include <QLabel>
#include <QPixmap>

ImageView::ImageView(QListWidgetItem* item, QRect rect, QWidget* parent)
	: QWidget(parent)
{
    qApp->installEventFilter(this);
    this->setGeometry(rect);//������ʾͼƬ���ڵ�x��y��w��h
    this->setFixedSize(rect.width(), rect.height());//���ô��ڹ̶���С
    this->setWindowIcon(item->icon());
    this->setWindowTitle("�鿴ͼƬ");
    this->setWindowModality(Qt::ApplicationModal);//��������ǰ��������������д���

    //ͨ��QLabel����item�ϵ�ͼƬ
    QLabel* lab = new QLabel(this);
    lab->setFixedSize(this->width(), this->height());
    lab->setPixmap(item->icon().pixmap(QSize(this->width(), this->height())).scaled(lab->width(), lab->height()));

}

ImageView::~ImageView()
{
    delete this;
}

//�¼���������ʵ�ֵ����������λ�ã����ھͿ��Թر�
bool ImageView::eventFilter(QObject* obj, QEvent* e)
{
    if (e->type() == QEvent::MouseButtonPress)
    {
        this->close();
    }
    return QWidget::eventFilter(obj, e);
}