#pragma once
#include <qvector.h>
#include <qstringlist.h>
#include <qpixmap.h>
#include <qlistWidget.h>
class ImageGroup : public QObject
{
	Q_OBJECT
public:
	ImageGroup(const QString& path, const QStringList& img_names, QObject* parent = nullptr);
	~ImageGroup();
	//���ͼƬ·��
	bool addImage(const QStringList& img_names);
	const QStringList& GetAllImage() { return all_images_; }
	const QStringList& GetNewImage() { return new_images_; }

private:
	//ͼƬ·��
	QString path_;
	//����ͼƬ����
	QStringList all_images_;
	//����ͼƬ����
	QStringList new_images_;
	
	//Ϊ����ͼ���Բ��
	QPixmap createRoundedPixmap(const QPixmap& source, int radius);

signals:
	void sendImage(QListWidgetItem* item);
	void finished();

public slots:
	//��������ͼ
	void creatPreviewPixmap();
};

