#pragma once

#include <QWidget>
#include <QPropertyAnimation>
#include <qlabel.h>
#include <qmovie.h>

class ListWidgetItem  : public QWidget
{
	Q_OBJECT

public:
	ListWidgetItem(const QString& filePath, QWidget* parent = nullptr);
	~ListWidgetItem();

private:
    QLabel* label;
    QMovie* movie;

};
