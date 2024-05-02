#pragma once

#include <QWidget>

class ListWidgetItem  : public QWidget
{
	Q_OBJECT

public:
	ListWidgetItem(const QString& filePath, QWidget* parent = nullptr);
	~ListWidgetItem();
};
