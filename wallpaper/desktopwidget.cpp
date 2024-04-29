#include "desktopwidget.h"
#include <QHBoxLayout>
#include <qt_windows.h>
#include <qvector.h>

DesktopWidget::DesktopWidget(QWidget *parent)
	: QWidget(parent)
	, bklabel(new QLabel)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(bklabel);

	SetPixmap(":/resource/wallpaper/2.jpg");
    SetBackground((HWND)this->winId());
}

DesktopWidget::~DesktopWidget()
{}

//获取背景窗体句柄
HWND DesktopWidget::GetBackground() {
    //背景窗体没有窗体名，但是知道它的类名是workerW，且有父窗体Program Maneger，所以只要
    //遍历所有workerW类型的窗体，逐一比较它的父窗体是不是Program Manager就可以找到背景窗体
    HWND hwnd = FindWindowA("progman", "Program Manager");
    HWND worker = NULL;
    do {
        worker = FindWindowExA(NULL, worker, "workerW", NULL); // 根据类名获取窗体句柄
        if (worker != NULL) {
            char buff[200] = { 0 };
            int ret = GetClassNameA(worker, (PCHAR)buff, sizeof(buff) * 2);
            if (ret == 0) {
                return NULL;
            }
            if (GetParent(worker) == hwnd) {
                return worker;//返回结果
            }
        }
    } while (worker != NULL);
    //没有找到
    //发送消息生成一个WorkerW窗体
    SendMessage(hwnd, 0x052C, 0, 0);
    //重复上面步骤
    do {
        worker = FindWindowExA(NULL, worker, "workerW", NULL);
        if (worker != NULL) {
            char buff[200] = { 0 };
            int ret = GetClassNameA(worker, (PCHAR)buff, sizeof(buff) * 2);
            if (ret == 0) {
                return NULL;
            }
            if (GetParent(worker) == hwnd) {
                return worker;//返回结果
            }
        }
    } while (worker != NULL);
    return NULL;
}

void DesktopWidget::SetBackground(HWND child) {
    SetParent(child, GetBackground()); // 把视频窗口设置为Program Manager的儿子
}

void DesktopWidget::SetPixmap(const QString& fileName)
{
	if (QPixmap(fileName).isNull()) {
		return;
	}
	bkPixmap.load(fileName);
	bklabel->setPixmap(bkPixmap);
	this->hide();
	this->showFullScreen();
}
