#ifndef W_H_MENU_CARD_H
#define W_H_MENU_CARD_H

#include <QWidget>

namespace Ui {
class w_h_menu_card;
}

class w_h_menu_card : public QWidget
{
    Q_OBJECT

public:
    explicit w_h_menu_card(QWidget *parent = nullptr);
    ~w_h_menu_card();

private:
    Ui::w_h_menu_card *ui;
};

#endif // W_H_MENU_CARD_H
