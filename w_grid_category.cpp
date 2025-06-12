#include "w_grid_category.h"
#include "ui_w_grid_category.h"

w_grid_category::w_grid_category(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::w_grid_category)
{
    ui->setupUi(this);

    this->categories = {"치킨", "커피/차", "버거", "구이", "샐러드",
                          "한식", "분식", "돈까스", "족발/보쌈", "찜/탕",
                          "피자", "중식", "일식", "회/해물", "양식",
                          "디저트", "간식", "아시안", "샌드위치", "멕시칸",
                          "도시락", "죽", "포장", "1인분"};

    // 그리드 레이아웃 구성
    QGridLayout* layout = new QGridLayout;

    int initial_count = 9;
    int max_column = 5;

    int row = 0;
    int col = 0;

    for (int i = 0; i < initial_count; i++) {
        QPushButton* btn = new QPushButton(this->categories[i]);
        btn->setFixedSize(SIZE,SIZE);
        layout->addWidget(btn, row, col);
        if (col++ >= max_column) {
            col = 0;
            row++;
        }
    }

    int startRow = row;
    int startCol = col;

    QPushButton* moreBtn = new QPushButton("더보기 ▼");
    moreBtn->setFixedSize(SIZE, SIZE);
    layout->addWidget(moreBtn, startRow, startCol);

    // connect(moreBtn, &QPushButton::clicked, this, [=]() mutable {
    // });

}

w_grid_category::~w_grid_category()
{
    delete ui;
}
