#include "w_h_menu_card.h"
#include "ui_w_h_menu_card.h"

w_h_menu_card::w_h_menu_card(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::w_h_menu_card)
{
    ui->setupUi(this);

    this->setStyleSheet(" border-radius: 12px;");//모서리 둥글게

}

w_h_menu_card::~w_h_menu_card()
{
    delete ui;
}
