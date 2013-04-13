#include "qtrsed.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtrSed w;
    w.show();
    
    return a.exec();
}
