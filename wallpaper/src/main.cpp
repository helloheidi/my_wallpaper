#include<qapplication.h>
#include <include/mainwidget.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWidget mainwidget;
    mainwidget.show();
    return app.exec();
}
