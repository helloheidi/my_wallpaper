#pragma once
#include <qstringlist.h>

class ImagePathGroup
{
public:
	ImagePathGroup(const QStringList& img_paths);
	~ImagePathGroup();
	//���ͼƬ·��
	bool addImage(const QStringList& img_paths);
	const QStringList& GetAllImage() { return all_images_; }
	const QStringList& GetNewImage() { return new_images_; }

private:
	//����ͼƬ����
	QStringList all_images_;
	//����ͼƬ����
	QStringList new_images_;
};

