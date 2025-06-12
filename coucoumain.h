#ifndef COUCOUMAIN_H
#define COUCOUMAIN_H

#include "tcpclient.h"
#include "part1_login_signup.h"
#include "w_grid_category.h"

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
    void categoryBtn();
    ~CouCouMain();

private:
    Ui::CouCouMain *ui;
    TcpClient* client;
    // 이름 수정
    main2_login *login;
};
#endif // COUCOUMAIN_H
