#include "ImagePathGroup.h"

ImagePathGroup::ImagePathGroup(const QStringList& img_paths)
   : all_images_(img_paths)
{
}

ImagePathGroup::~ImagePathGroup()
{
}

//��ͼƬ���������ͼƬ
bool ImagePathGroup::addImage(const QStringList& img_paths)
{
    if (img_paths.empty()) return false;
    //�������ͼƬ����
    new_images_.clear();
    new_images_ = img_paths;
    for (auto& path : img_paths)
    {
        all_images_.push_back(path);
    }
    return true;
}
