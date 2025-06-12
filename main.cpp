#include "coucoumain.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CouCouMain w;
    w.show();
    return a.exec();
}
