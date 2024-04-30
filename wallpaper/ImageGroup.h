#pragma once
#include <qvector.h>
#include <qstringlist.h>
#include <qpixmap.h>
#include <qlistWidget.h>
class ImageGroup : public QObject
{
	Q_OBJECT
public:
	ImageGroup(const QString& path, const QStringList& img_paths, QObject* parent = nullptr);
	~ImageGroup();
	//添加图片路径
	bool addImage(const QVector<QString>& img_paths);
	const QVector<QString>& GetAllImage() { return all_images_; }
	const QVector<QString>& GetNewImage() { return new_images_; }

private:
	//图片路径
	QString path_;
	//所有图片数组
	QVector<QString> all_images_;
	//新增图片数组
	QVector<QString> new_images_;
	
	//为缩略图添加圆角
	QPixmap createRoundedPixmap(const QPixmap& source, int radius);

signals:
	void sendImage(QListWidgetItem* item);
	void finished();

public slots:
	//生成缩略图
	void creatPreviewPixmap();
};

