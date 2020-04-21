#include "t9window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    T9Window w;
    w.setFixedSize(279,477);
    w.show();
    return a.exec();
}
