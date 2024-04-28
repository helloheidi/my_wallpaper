#pragma once

#include <QWidget>
#include <qlabel.h>
#include <qpushbutton.h>
#include <desktopwidget.h>

class RoleWidget  : public QWidget
{
	Q_OBJECT

public:
	RoleWidget(QWidget *parent = nullptr);
	~RoleWidget();
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
