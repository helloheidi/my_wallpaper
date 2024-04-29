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

//��ȡ����������
HWND DesktopWidget::GetBackground() {
    //��������û�д�����������֪������������workerW�����и�����Program Maneger������ֻҪ
    //��������workerW���͵Ĵ��壬��һ�Ƚ����ĸ������ǲ���Program Manager�Ϳ����ҵ���������
    HWND hwnd = FindWindowA("progman", "Program Manager");
    HWND worker = NULL;
    do {
        worker = FindWindowExA(NULL, worker, "workerW", NULL); // ����������ȡ������
        if (worker != NULL) {
            char buff[200] = { 0 };
            int ret = GetClassNameA(worker, (PCHAR)buff, sizeof(buff) * 2);
            if (ret == 0) {
                return NULL;
            }
            if (GetParent(worker) == hwnd) {
                return worker;//���ؽ��
            }
        }
    } while (worker != NULL);
    //û���ҵ�
    //������Ϣ����һ��WorkerW����
    SendMessage(hwnd, 0x052C, 0, 0);
    //�ظ����沽��
    do {
        worker = FindWindowExA(NULL, worker, "workerW", NULL);
        if (worker != NULL) {
            char buff[200] = { 0 };
            int ret = GetClassNameA(worker, (PCHAR)buff, sizeof(buff) * 2);
            if (ret == 0) {
                return NULL;
            }
            if (GetParent(worker) == hwnd) {
                return worker;//���ؽ��
            }
        }
    } while (worker != NULL);
    return NULL;
}

void DesktopWidget::SetBackground(HWND child) {
    SetParent(child, GetBackground()); // ����Ƶ��������ΪProgram Manager�Ķ���
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
