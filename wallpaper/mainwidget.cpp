#include "mainwidget.h"
#include "imageview.h"
#include <qdebug.h>
#include <qlistWidget.h>
#include <qdir.h>
#include <QVBoxLayout>
#include <QtConcurrent/qtconcurrentrun.h>
#include <qpainter.h>

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::MainWidgetClass)
{
	ui->setupUi(this);
	ui->ImagelistWidget->setIconSize(QSize(125, 125));//���õ���Icon��С
	ui->ImagelistWidget->setViewMode(QListView::IconMode);//������ʾģʽ
	ui->ImagelistWidget->setFlow(QListView::LeftToRight);//������
	ui->ImagelistWidget->setResizeMode(QListView::Adjust);//��С����Ӧ
	ui->ImagelistWidget->setMovement(QListView::Static);//�����б�ÿһ����ƶ�

    path = QString(QDir::currentPath() + "/resource/kona/");//����ͼƬ·��
    QDir dir(path);

    //namefiles��filesΪQStringList����
    namefiles << "*.png" << "*.jpg";

    //���ұ���ͼƬ·���µ�png��׺��jpg��׺��ͼƬ��  xxx.png  xxx.jpg
    files = dir.entryList(namefiles, QDir::Files | QDir::Readable, QDir::Name);
    //for (int i = 0; i < files.size(); i++)
    //{
    //    qDebug() << files.at(i);
    //    QListWidgetItem* newitem = new QListWidgetItem(QIcon(QPixmap(path + "/" + files.at(i)).scaled(125, 125)), files.at(i));
    //    QFileInfo fi = files.at(i);
    //    //newitem->setText(fi.baseName());//Returns the base name of the file without the path
    //    newitem->setText("");
    //    newitem->setTextAlignment(Qt::AlignHCenter);
    //    ui->ImagelistWidget->addItem(newitem);
    //}
    for (int i = 0; i < files.size(); ++i) {
        QString fullPath = path + "/" + files.at(i);
        // �첽����ͼƬ
        QtConcurrent::run([=]() {
            qDebug() << files.at(i);
            QIcon icon(createRoundedPixmap(QPixmap(fullPath).scaled(125, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation), 5));
            emit sendIcon(icon, files.at(i));
            });
    }

    // �����źŵ��ۣ������ͼ�굽�б�
    connect(this, &MainWidget::sendIcon, this, &MainWidget::addIconToList, Qt::QueuedConnection);
    //��ʽ�����
    ui->ImagelistWidget->setStyleSheet("QListWidget{background-color: white;border:none; color:black;outline:0px; }"
        "QListWidget::Item{padding-left:0px;padding-top:5px; padding-bottom:4px;color:black}"
        //"QListWidget::Item {border: 0px; padding: 0px; border:none;border-radius:5px;}"
        "QListWidget::Item {border:none;border-radius:10px;}"
        "QListWidget::Item:hover{background:lightgreen; color:red;}"
        "QListWidget::item:selected{background:lightgray; color:green; }"
    );
    connect(ui->ImagelistWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(enlargeImage(QListWidgetItem*)));

    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->addWidget(ui->ImagelistWidget);
    vlayout->addWidget(ui->ImageListBnt);
    vlayout->addWidget(ui->MyImageBnt);
    vlayout->addWidget(ui->SettingBnt);
}

void MainWidget::addIconToList(QIcon icon, QString filename) {
    QListWidgetItem* newitem = new QListWidgetItem(icon, filename);
    //newitem->setSizeHint(QSize(125, 125));
    newitem->setText(""); // �������Ҫ��ʾ�ı�
    newitem->setTextAlignment(Qt::AlignHCenter);
    ui->ImagelistWidget->addItem(newitem);
}

QPixmap MainWidget::createRoundedPixmap(const QPixmap& source, int radius) {
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

void MainWidget::enlargeImage(QListWidgetItem* item)
{
    QRect rect = this->geometry();//��ȡ��ǰ�������꼰��С x��y��w��h

    //ͨ���Զ���Ĵ�����ʾͼƬ
    ImageView* showImageWidget = new ImageView(item, QRect(rect.x(), rect.y() + rect.y() * 1 / 4, rect.width(), rect.height() * 2 / 3));
    showImageWidget->show();
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::on_ImageListBnt_clicked() {
	ui->stackedWidget->setCurrentIndex(0);
}

void MainWidget::on_MyImageBnt_clicked() {
	ui->stackedWidget->setCurrentIndex(2);
}