#include "include/listwidgetitem.h"
#include <qlabel.h>
#include <qmovie.h>
#include <qbitmap.h>
#include <qpainter.h>

ListWidgetItem::ListWidgetItem(const QString& filePath, QWidget* parent) : QWidget(parent) {
    QLabel* label = new QLabel;
    QMovie* movie = new QMovie(filePath);
    label->setMovie(movie);
    movie->start();

    QBitmap bitmap(movie->currentPixmap().size());
    bitmap.fill(Qt::color0);  // 初始化为全透明

    QPainter painter(&bitmap);
    painter.setRenderHint(QPainter::Antialiasing, true); // 开启抗锯齿
    QPainterPath path;
    path.addRoundedRect(0, 0, bitmap.width(), bitmap.height(), 50, 50);  // 注意这里直接使用控件的宽度和高度

    painter.fillPath(path, Qt::color1);  // 使用不透明的颜色填充路径
    label->setMask(bitmap);  // 应用遮罩
}

ListWidgetItem::~ListWidgetItem()
{}
