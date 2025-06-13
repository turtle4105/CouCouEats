#ifndef COUCOUMAIN_H
#define COUCOUMAIN_H

#include "tcpclient.h"
#include "main2_login.h"
#include "w_v_store_card.h"

#include <QMainWindow>
#include <QDialog>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class CouCouMain;
}
QT_END_NAMESPACE

class CouCouMain : public QMainWindow
{
    Q_OBJECT

public:
    CouCouMain(QWidget *parent = nullptr);
    void showChoiceLoginDialg();
    ~CouCouMain();

private:
    Ui::CouCouMain *ui;
    TcpClient* client;
    // 이름 수정
    main2_login *login;
    w_v_store_card *store_card_widget;
};
#endif // COUCOUMAIN_H
