#ifndef MAIN2_LOGIN_H
#define MAIN2_LOGIN_H

#include "tcpclient.h"
#include <QWidget>
#include <QRegularExpression>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QMessageBox>
#include <QStackedWidget>


namespace Ui {
class main2_login;
}

class main2_login : public QWidget
{
    Q_OBJECT

public:
    explicit main2_login(TcpClient *client,QWidget *parent = nullptr);
    void move_page();
    void updateSignupButton();
    void fix_everything();

    void make_id();
    void move_page_to_login();
    void for_login();
    void move_page_to_search_pw();
    void move_page_to_search_id();

    QStackedWidget* getStackedWidget() const;
    QWidget* getSignupPage() const;
    QWidget* getLoginPage() const;

    int check_count = 0;

    ~main2_login();

signals:
    void reqTurnToMain();

private:
    Ui::main2_login *ui;
    TcpClient *client;
};

#endif // MAIN2_LOGIN_H

