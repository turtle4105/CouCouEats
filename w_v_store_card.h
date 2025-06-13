#ifndef W_V_STORE_CARD_H
#define W_V_STORE_CARD_H

#include <QWidget>

namespace Ui {
class w_v_store_card;
}

class w_v_store_card : public QWidget
{
    Q_OBJECT

public:
    explicit w_v_store_card(QWidget *parent = nullptr);
    ~w_v_store_card();

private:
    Ui::w_v_store_card *ui;
};

#endif // W_V_STORE_CARD_H
