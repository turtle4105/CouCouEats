#include "coucoumain.h"
// #include "w_v_store_card.h"
// #include "main2_login.h"
// #include "w_v_menu_card.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CouCouMain w;
    // w_v_store_card w;
    // w_v_menu_card w;

    w.show();
    return a.exec();
}
