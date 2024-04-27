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

private:
	QLabel* bklabel;//�ű�ֽ
	QPixmap bkPixmap;
};
