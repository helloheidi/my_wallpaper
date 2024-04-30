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
	//���ͼƬ·��
	bool addImage(const QVector<QString>& img_paths);
	const QVector<QString>& GetAllImage() { return all_images_; }
	const QVector<QString>& GetNewImage() { return new_images_; }

private:
	//ͼƬ·��
	QString path_;
	//����ͼƬ����
	QVector<QString> all_images_;
	//����ͼƬ����
	QVector<QString> new_images_;
	
	//Ϊ����ͼ���Բ��
	QPixmap createRoundedPixmap(const QPixmap& source, int radius);

signals:
	void sendImage(QListWidgetItem* item);
	void finished();

public slots:
	//��������ͼ
	void creatPreviewPixmap();
};

