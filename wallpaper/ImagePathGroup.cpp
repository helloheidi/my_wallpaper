#include "ImagePathGroup.h"

ImagePathGroup::ImagePathGroup(const QStringList& img_paths)
   : all_images_(img_paths)
{
}

ImagePathGroup::~ImagePathGroup()
{
}

//向图片数组中添加图片
bool ImagePathGroup::addImage(const QStringList& img_paths)
{
    if (img_paths.empty()) return false;
    //清空新增图片数组
    new_images_.clear();
    new_images_ = img_paths;
    for (auto& path : img_paths)
    {
        all_images_.push_back(path);
    }
    return true;
}
