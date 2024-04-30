#include "rolewidget.h"
#include <qtimer.h>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <qfiledialog.h>
#include <qapplication.h>
#include <qstackedwidget.h>
#include <QMainWindow>
#include <QVBoxLayout>

RoleWidget::RoleWidget(QWidget *parent)
	: QWidget(parent)
	, rolelabel(new QLabel(this))
	, curframe(0)
{
	//去掉窗口边框和让背景透明
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground);

	//使用定时器更新动画
	QTimer* updateTimer = new QTimer(this);
	updateTimer->callOnTimeout(this, &RoleWidget::updateRoleAnimation);
	updateTimer->start(500);

	//给窗口设置阴影
	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
	effect->setColor(QColor(100, 100, 100, 100));
	effect->setBlurRadius(5);
	this->setGraphicsEffect(effect);

	this->installEventFilter(this);

	updateRoleAnimation();
	rolelabel->resize(500, 500);

	//desktopWidget->show();


	initBtn();
}

RoleWidget::~RoleWidget()
{
	
}

void RoleWidget::updateRoleAnimation()
{
	QString qss("background-repeat:no-repeat;");
	rolelabel->setStyleSheet(qss + QString("background-image:url(:/resource/desktopRole/summerGril/%1.png);").arg(curframe));
	curframe = (curframe +1) % 6;
	//rolelabel->setStyleSheet(qss + "background-image:url(:/resource/wallpaper/1.jpg);");
}

bool RoleWidget::eventFilter(QObject* watched, QEvent* ev)
{
	QMouseEvent* mouseev = static_cast<QMouseEvent*>(ev);
	//判断鼠标左键按下
	static QPoint begpos;
	if (ev->type() == QEvent::MouseButtonPress) {
		begpos = mouseev->globalPos() - this->pos();
	}
	//判断鼠标移动
	else if (ev->type() == QEvent::MouseMove && mouseev->buttons() & Qt::MouseButton::LeftButton) {
		this->move(mouseev->globalPos() - begpos);
	}
	return false;
}

void RoleWidget::initBtn()
{
	closeBtn = new QPushButton(this);
	cutBtn = new QPushButton(this);
	openBtn = new QPushButton(this);

	closeBtn->setGeometry(300, 200, 32, 32);
	cutBtn->setGeometry(300, 240, 32, 32);
	openBtn->setGeometry(300, 280, 32, 32);
	closeBtn->setObjectName("closeBtn");

	closeBtn->setStyleSheet("background-image:url(:/resource/button/quit.png)");
	cutBtn->setStyleSheet("background-image:url(:/resource/button/cut.png)");
	openBtn->setStyleSheet("background-image:url(:/resource/button/open.png)");

	this->setStyleSheet("QPushButton{background-color:rgb(64,173,250);\
						border:none;border-radius:5px;}\
						QPushButton#closeBtn:hover{background-color:rgb(233,31,48);}");
	connect(closeBtn, &QPushButton::pressed, this, &QApplication::quit);
	connect(cutBtn, &QPushButton::clicked, this, []() {
		QWidget* wid = new QWidget();
		wid->setWindowFlags(Qt::Tool);
		wid->setWindowTitle("fuck you");
		wid->show();
		});
	connect(openBtn, &QPushButton::pressed, this, [=]() {
			QString filename =  QFileDialog::getOpenFileName(nullptr, "选择壁纸", "./", "Image(*.jpg *.png)");
			if (filename.isEmpty()) return;
			//desktopWidget->SetPixmap(filename);
		});
}
