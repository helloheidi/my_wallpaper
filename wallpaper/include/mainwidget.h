#pragma once

#include <QWidget>
#include "ui_mainwidget.h"
#include "ImageGroup.h"
#include "include/desktopwidget.h"
#include "include/rolewidget.h"
#include "include/listwidgetitem.h"

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent = nullptr);
	
	~MainWidget();
	//int GetimageMode() const { return imageMode_; };
	//QString GetselectImage() const { return selectImage_; };
private:
	void init();
	Ui::MainWidgetClass* ui;

	ImageGroup* imageGroup;	
	DesktopWidget* desktopWidget;
	RoleWidget* rolewidget;

	QString selectImage_pre;//设置选中的图片预览图的路径
	QString selectImage_;//设置选中的图片的路径
	int imageMode_;//设置图片填充模式

protected:
	void closeEvent(QCloseEvent* event);
	void paintEvent(QPaintEvent* event);

public slots:
	void addIconToList(QString filePath);

private slots:
	void updateImageMode(int imageMode);//更新桌面图片填充模式
	void enlargeImage(QListWidgetItem* item);//查看图片
	void previewImage(QListWidgetItem* item);//预览图片
	void on_ImageListBnt_clicked();
	void on_SettingBnt_clicked();
	void on_SetDesktop_clicked();
	void showContextMenu(const QPoint& pos);
	void deleteSelectedItems();
	void editSelectedItems();
	//右键菜单
};
