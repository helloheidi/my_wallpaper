#pragma once

#include <QWidget>
#include <qlabel.h>
#include <QPixmap>

class DesktopWidget  : public QWidget
{
	Q_OBJECT

public:
	DesktopWidget(QWidget *parent = nullptr);
	~DesktopWidget();
	HWND GetBackground();
	void SetBackground(HWND child);
	void SetPixmap(const QString& fileNname);

	int screenWidth;
	int screenHeight;

private:
	QLabel* bklabel;//·Å±ÚÖ½
	QPixmap bkPixmap;
};
