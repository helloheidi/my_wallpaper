#pragma once

#include <QWidget>
#include "ui_mainwidget.h"
#include "ImageGroup.h"
#include "include/desktopwidget.h"
#include "include/rolewidget.h"

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
	ImageGroup* imageGroup;
	QString selectImage;
	DesktopWidget* desktopWidget;
	RoleWidget* rolewidget;

protected:
	void closeEvent(QCloseEvent* event);
	void paintEvent(QPaintEvent* event);

signals:
	void sendImage(QListWidgetItem* item);

public slots:
	void addIconToList(QListWidgetItem* item);

private slots:
	void enlargeImage(QListWidgetItem* item);//�鿴ͼƬ
	void previewImage(QListWidgetItem* item);//Ԥ��ͼƬ
	void on_ImageListBnt_clicked();
	void on_SettingBnt_clicked();
	void on_SetDesktop_clicked();
};
