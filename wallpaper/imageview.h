#pragma once

#include <QWidget>
#include <QListWidget>
#include <QRect>

class ImageView  : public QWidget
{
	Q_OBJECT

public:
	ImageView(QListWidgetItem* item, QRect rect, QWidget* parent = 0);
	~ImageView();

private:
	QListWidget* imageWidget;
	QListWidgetItem* item;

protected:
	bool eventFilter(QObject* obj, QEvent* e);
};
