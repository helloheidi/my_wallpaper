#include<qapplication.h>
#include<rolewidget.h>
#include <mainwidget.h>

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	/*RoleWidget w;
	w.show();*/
    /*CustomWidget customWidget;
    customWidget.show();*/
	MainWidget mainwidget;
	mainwidget.show();
	return app.exec();
}
//#include <QApplication>
//#include <QListWidget>
//#include <QListWidgetItem>
//#include <QLabel>
//#include <QMovie>
//
//class ListWidgetWithGifs : public QListWidget {
//public:
//    ListWidgetWithGifs(QWidget* parent = nullptr) : QListWidget(parent) {
//        for (int i = 0; i < 5; ++i) {
//            QListWidgetItem* item = new QListWidgetItem(this);
//            QLabel* label = new QLabel;
//            QMovie* movie = new QMovie(":/resource/gif/2.gif");
//            label->setMovie(movie);
//            movie->start();
//
//            item->setSizeHint(label->minimumSizeHint());
//            setItemWidget(item, label);
//        }
//    }
//};
//
//int main(int argc, char* argv[]) {
//    QApplication app(argc, argv);
//    ListWidgetWithGifs listWidget;
//    listWidget.show();
//    return app.exec();
//}
