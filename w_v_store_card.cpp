#include "w_v_store_card.h"
#include "ui_w_v_store_card.h"

w_v_store_card::w_v_store_card(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::w_v_store_card)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->ad_label->setText("매주문 무료배달 적용매장");
    ui->ad_label->setAlignment(Qt::AlignCenter);
    ui->ad_label->setStyleSheet(
        "QLabel {"
        " color: white;"              // 글자 색
        " background-color: #003366;" // 남색 배경
        " border-radius: 8px;"        // 둥근 모서리R
        " padding: 6px 12px;"         // 내부 여백
        " font-size: 12px;"             //글자크기 조절
        " font-weight: bold;"         // 글자 강조 (선택)
        "}"
        );






}

w_v_store_card::~w_v_store_card()
{
    delete ui;
}
