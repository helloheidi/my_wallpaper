/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidgetClass
{
public:
    QLabel *ImagePreview;
    QTextBrowser *ImageNameInfo;
    QTextBrowser *ImageSizeInfo;
    QFrame *frame;
    QPushButton *ImageListBnt;
    QPushButton *SettingBnt;
    QStackedWidget *stackedWidget;
    QWidget *ImageListPage;
    QListWidget *ImagelistWidget;
    QWidget *MyImagePage;
    QLabel *label_2;
    QWidget *SettingPage;
    QLabel *label_3;
    QPushButton *SetDesktop;

    void setupUi(QWidget *MainWidgetClass)
    {
        if (MainWidgetClass->objectName().isEmpty())
            MainWidgetClass->setObjectName(QString::fromUtf8("MainWidgetClass"));
        MainWidgetClass->resize(1130, 610);
        MainWidgetClass->setStyleSheet(QString::fromUtf8("*{\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"QFrame#frame {\n"
"	background-color: rgba(255, 255, 255, 200);\n"
"}\n"
"QWidget#MainWidgetClass {\n"
"	background-image: url(:/resource/background/Nahida-Kusanali.jpg);\n"
"}\n"
"#ImageListPage {\n"
"	border:none;\n"
"	background-color: rgba(255, 170, 255, 0);\n"
"}\n"
"QLabel#ImagePreview {\n"
"	background:transparent;\n"
"}\n"
"QTextBrowser#ImageSizeInfo {\n"
"	border-radius:10px;	\n"
"	background-color: rgba(163, 163, 163, 80);\n"
"}\n"
"#ImageNameInfo {\n"
"	border-radius:10px;\n"
"	background-color: rgba(163, 163, 163, 80);\n"
"}\n"
"QPushButton {\n"
"    background-color: transparent; \n"
"    border: none;\n"
"}\n"
"QPushButton:hover{\n"
"	border-radius:10px;\n"
"	background-color: rgba(255, 255, 255, 80);\n"
"}\n"
"QPushButton#ImageListBnt {\n"
"	background-image: url(:/resource/button/icon1.png);\n"
"	background-position: center;\n"
"    background-repeat: no-repeat;\n"
"    background-size: contain;\n"
"}\n"
"#SettingBnt {\n"
"	background-imag"
                        "e: url(:/resource/button/icon.png);\n"
"	background-position: center;\n"
"    background-repeat: no-repeat;\n"
"    background-size: contain;\n"
"}\n"
"#SetDesktop {\n"
"	background-image: url(:/resource/button/icon2.png);\n"
"	background-position: center;\n"
"    background-repeat: no-repeat;\n"
"    background-size: contain;\n"
"}\n"
"QListWidget#ImagelistWidget {\n"
"	border:none;\n"
"	border-radius:30px;\n"
"	background-color: rgba(100, 170, 255, 40);\n"
"}\n"
"\n"
"QStackedWidget#stackedWidget {	\n"
"	border:none;\n"
"	background:transparent;\n"
"}"));
        ImagePreview = new QLabel(MainWidgetClass);
        ImagePreview->setObjectName(QString::fromUtf8("ImagePreview"));
        ImagePreview->setGeometry(QRect(860, 40, 250, 250));
        ImageNameInfo = new QTextBrowser(MainWidgetClass);
        ImageNameInfo->setObjectName(QString::fromUtf8("ImageNameInfo"));
        ImageNameInfo->setGeometry(QRect(860, 300, 250, 35));
        ImageSizeInfo = new QTextBrowser(MainWidgetClass);
        ImageSizeInfo->setObjectName(QString::fromUtf8("ImageSizeInfo"));
        ImageSizeInfo->setGeometry(QRect(860, 340, 250, 31));
        frame = new QFrame(MainWidgetClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 1130, 610));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        ImageListBnt = new QPushButton(frame);
        ImageListBnt->setObjectName(QString::fromUtf8("ImageListBnt"));
        ImageListBnt->setGeometry(QRect(130, 550, 201, 51));
        SettingBnt = new QPushButton(frame);
        SettingBnt->setObjectName(QString::fromUtf8("SettingBnt"));
        SettingBnt->setGeometry(QRect(510, 550, 191, 51));
        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 10, 850, 520));
        ImageListPage = new QWidget();
        ImageListPage->setObjectName(QString::fromUtf8("ImageListPage"));
        ImagelistWidget = new QListWidget(ImageListPage);
        ImagelistWidget->setObjectName(QString::fromUtf8("ImagelistWidget"));
        ImagelistWidget->setGeometry(QRect(0, 0, 850, 520));
        stackedWidget->addWidget(ImageListPage);
        MyImagePage = new QWidget();
        MyImagePage->setObjectName(QString::fromUtf8("MyImagePage"));
        label_2 = new QLabel(MyImagePage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(140, 120, 54, 12));
        stackedWidget->addWidget(MyImagePage);
        SettingPage = new QWidget();
        SettingPage->setObjectName(QString::fromUtf8("SettingPage"));
        label_3 = new QLabel(SettingPage);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(150, 120, 54, 12));
        stackedWidget->addWidget(SettingPage);
        SetDesktop = new QPushButton(frame);
        SetDesktop->setObjectName(QString::fromUtf8("SetDesktop"));
        SetDesktop->setGeometry(QRect(890, 440, 201, 111));
        frame->raise();
        ImagePreview->raise();
        ImageNameInfo->raise();
        ImageSizeInfo->raise();

        retranslateUi(MainWidgetClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *MainWidgetClass)
    {
        MainWidgetClass->setWindowTitle(QCoreApplication::translate("MainWidgetClass", "MainWidget", nullptr));
        ImagePreview->setText(QString());
        ImageListBnt->setText(QString());
        SettingBnt->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWidgetClass", "MyImage", nullptr));
        label_3->setText(QCoreApplication::translate("MainWidgetClass", "Setting", nullptr));
        SetDesktop->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWidgetClass: public Ui_MainWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
