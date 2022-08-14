#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.show();
    w.setFixedSize(520,700);
    w.move(1000,450);
//    w.setWindowTitle("计科2101 张宏远");

    return a.exec();
}
