#pragma once
#include <qstringlist.h>

class ImagePathGroup
{
public:
	ImagePathGroup(const QStringList& img_paths);
	~ImagePathGroup();
	//添加图片路径
	bool addImage(const QStringList& img_paths);
	const QStringList& GetAllImage() { return all_images_; }
	const QStringList& GetNewImage() { return new_images_; }

private:
	//所有图片数组
	QStringList all_images_;
	//新增图片数组
	QStringList new_images_;
};

