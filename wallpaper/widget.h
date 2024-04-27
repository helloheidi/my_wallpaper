#pragma once

#include <QWidget>
#include <qlabel.h>
#include <qpushbutton.h>
#include <desktopwidget.h>

class Widget  : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = nullptr);
	~Widget();
	void updateRoleAnimation();
	bool eventFilter(QObject* watched, QEvent* ev) override;
	void initBtn();
private:
	QLabel* rolelabel;
	qint8 curframe;//µ±Ç°Ö¡
	QPushButton* closeBtn;
	QPushButton* cutBtn;
	QPushButton* openBtn;

	DesktopWidget* desktopWidget;
};
