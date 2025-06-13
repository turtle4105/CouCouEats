#ifndef W_V_MENU_CARD_H
#define W_V_MENU_CARD_H

#include <QWidget>

namespace Ui {
class w_v_menu_card;
}

class w_v_menu_card : public QWidget
{
    Q_OBJECT

public:
    explicit w_v_menu_card(QWidget *parent = nullptr);
    ~w_v_menu_card();

private:
    Ui::w_v_menu_card *ui;
};

#endif // W_V_MENU_CARD_H
