#pragma once

#include <QWidget>
#include "ui_mainwidget.h"

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent = nullptr);
	~MainWidget();

	

private:
	QPixmap createRoundedPixmap(const QPixmap& source, int radius);
	Ui::MainWidgetClass* ui;
	QWidget* mywidget;
	//QListWidget* imgList;
	QString path;
	QStringList namefiles, files;

signals:
	void sendIcon(QIcon icon, QString filename);

public slots:
	void addIconToList(QIcon icon, QString filename);

private slots:
	void enlargeImage(QListWidgetItem* item);//·Å´óÍ¼Æ¬
	void on_ImageListBnt_clicked();
	void on_MyImageBnt_clicked();
};
