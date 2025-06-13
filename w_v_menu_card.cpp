#include "w_v_menu_card.h"
#include "ui_w_v_menu_card.h"

w_v_menu_card::w_v_menu_card(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::w_v_menu_card)
{
    ui->setupUi(this);

    ui->m_cart->setStyleSheet("QPushButton { border-radius:12px;};");
}

w_v_menu_card::~w_v_menu_card()
{
    delete ui;
}
