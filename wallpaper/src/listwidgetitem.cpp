#include "include/listwidgetitem.h"

#include <qbitmap.h>
#include <qpainter.h>
#include <QVBoxLayout>

ListWidgetItem::ListWidgetItem(const QString& filePath, QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(5);  // 设置边距为0
    layout->setSpacing(5); // 设置间隔为0
    label = new QLabel;
    movie = new QMovie(filePath);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->setScaledContents(true);
    label->setMovie(movie);
    label->setFixedSize(150,150);
    movie->start();

    if (movie->isValid()) {
        label->setMovie(movie);
        movie->start();
    }
    else {
        // 如果不是有效的动图，就当作普通图像处理
        QPixmap pixmap(filePath);
        label->setPixmap(pixmap);
    }
    layout->addWidget(label);
    layout->setAlignment(Qt::AlignCenter);
    this->setLayout(layout);
}


ListWidgetItem::~ListWidgetItem()
{}
