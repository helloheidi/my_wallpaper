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
    , desktopWidget(new DesktopWidget())
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
    ImagePaths = new ImagePathGroup(files);
    for (int i = 0; i < files.size(); ++i) {
        QString imagePath = path + "/" + files.at(i);
        // �첽����ͼƬ
        QtConcurrent::run([=]() {
            qDebug() << files.at(i);
            QIcon icon(createRoundedPixmap(QPixmap(imagePath).scaled(125, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation), 5));
            QListWidgetItem* newitem = new QListWidgetItem(icon, "");
            //newitem->setSizeHint(QSize(125, 125));
            newitem->setData(Qt::UserRole, QVariant(imagePath));
            newitem->setText(""); // �������Ҫ��ʾ�ı�
            newitem->setTextAlignment(Qt::AlignHCenter);
            //ui->ImagelistWidget->addItem(newitem);
            emit sendImage(newitem);
            });
    }

    // �����źŵ��ۣ������ͼ�굽�б�
    connect(this, &MainWidget::sendImage, this, &MainWidget::addIconToList, Qt::QueuedConnection);
    //��ʽ�����
    ui->ImagelistWidget->setStyleSheet("QListWidget{background-color: white;border:none; color:black;outline:0px; }"
        "QListWidget::Item{padding-left:0px;padding-top:5px; padding-bottom:4px;color:black}"
        "QListWidget::Item:hover{background:lightgreen; color:red;}"
        "QListWidget::item:selected{background:lightgray; color:green; }"
    );
    connect(ui->ImagelistWidget, &QListWidget::itemDoubleClicked, this, &MainWidget::enlargeImage);
    connect(ui->ImagelistWidget, &QListWidget::itemClicked, this, &MainWidget::previewImage);
}

void MainWidget::addIconToList(QListWidgetItem* newitem) {
    //QIcon icon(createRoundedPixmap(QPixmap(imagePath).scaled(125, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation), 5));
    //QListWidgetItem* newitem = new QListWidgetItem(icon, "");
    ////newitem->setSizeHint(QSize(125, 125));
    //newitem->setData(Qt::UserRole, QVariant(imagePath));
    //newitem->setText(""); // �������Ҫ��ʾ�ı�
    //newitem->setTextAlignment(Qt::AlignHCenter);
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

void MainWidget::updateImageList() {

}
//�鿴ͼƬ
void MainWidget::enlargeImage(QListWidgetItem* item) {
    QString filepath = item->data(Qt::UserRole).toString();
    desktopWidget->SetPixmap(filepath);
    ImageView* showImageWidget = new ImageView();
    showImageWidget->SetImage(filepath);
    showImageWidget->show();
    
}

//Ԥ��ͼƬ
void MainWidget::previewImage(QListWidgetItem* item) {
    QString filepath = item->data(Qt::UserRole).toString();

    ui->ImagePreview->setPixmap(QPixmap(filepath).scaled(ui->ImagePreview->width(), ui->ImagePreview->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
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

//void MainWidget::on_SetDesktop_clicked() {
//    //ui->stackedWidget->setCurrentIndex(2);
//}