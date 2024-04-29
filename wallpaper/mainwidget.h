#pragma once

#include <QWidget>
#include "ui_mainwidget.h"
#include "ImagePathGroup.h"
#include "desktopwidget.h"

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent = nullptr);
	
	~MainWidget();

	

private:
	QPixmap createRoundedPixmap(const QPixmap& source, int radius);
	void updateImageList();
	Ui::MainWidgetClass* ui;
	QString path;
	QStringList namefiles, files;
	ImagePathGroup* ImagePaths;
	DesktopWidget* desktopWidget;

signals:
	void sendImage(QListWidgetItem* item);

public slots:
	void addIconToList(QListWidgetItem* item);

private slots:
	void enlargeImage(QListWidgetItem* item);//�鿴ͼƬ
	void previewImage(QListWidgetItem* item);//Ԥ��ͼƬ
	void on_ImageListBnt_clicked();
	void on_MyImageBnt_clicked();
};
