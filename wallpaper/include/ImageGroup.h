#pragma once
#include <qvector.h>
#include <qstringlist.h>
#include <qpixmap.h>
#include <qlistWidget.h>
#include "include/listwidgetitem.h"
class ImageGroup : public QObject
{
	Q_OBJECT
public:
	ImageGroup(QObject* parent = nullptr);
	~ImageGroup();
	//添加图片路径
	bool addImage(const QStringList& img_names);
	const QStringList& GetAllImage() { return all_images_; }
	const QStringList& GetNewImage() { return new_images_; }

private:
	//图片路径
	QString path_;
	//所有图片数组
	QStringList all_images_;
	QStringList namefiles, files;
	//新增图片数组
	QStringList new_images_;
	
	//为缩略图添加圆角
	QPixmap createRoundedPixmap(const QPixmap& source, int radius);

signals:
	void sendImage(QListWidgetItem* item, ListWidgetItem* itemWidget);
	void finished();

public slots:
	//生成缩略图
	void creatPreviewPixmap();
};

