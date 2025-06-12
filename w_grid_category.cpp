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

    QMap<QString, QString> categoryImageMap = {
        {"치킨", "CHICKEN.jpeg"},
        {"커피/차", "COFFEE.jpeg"},
        {"버거", "BURGER.jpeg"},
        {"구이", "GOOEE.jpeg"},
        {"샐러드", "SALAD.jpeg"},
        {"한식", "HANSIK.jpeg"},
        {"분식", "BOONSIK.jpeg"},
        {"돈까스", "DONGASS.jpeg"},
        {"족발/보쌈", "JOKBAL.jpeg"},
        {"찜/탕", "JJIM_TANG.jpeg"},
        {"피자", "PIZZA.jpeg"},
        {"중식", "CHINA.jpeg"},
        {"일식", "JAPAN.jpeg"},
        {"회/해물", "SEAFOOD.jpeg"},
        {"양식", "USA.jpeg"},
        {"디저트", "DESSERT.jpeg"},
        {"간식", "SNACK.jpeg"},
        {"아시안", "ASIAN.jpeg"},
        {"샌드위치", "SANDWICH.jpeg"},
        {"멕시칸", "MEXICO.jpeg"},
        {"도시락", "BENTTO.jpeg"},
        {"죽", "JOOK.jpeg"},
        {"포장", "TAKE_OUT.jpeg"},
        {"1인분", "ONE.jpeg"}
    };



    // 그리드 레이아웃 구성
    QGridLayout* layout = new QGridLayout;
    layout->setContentsMargins(0, 0, 0, 0);  // 위, 오른쪽, 아래, 왼쪽 여백 모두 제거
    layout->setSpacing(0);  // 위젯 사이 간격도 제거

    int row = 0;
    int col = 0;

    for (int i = 0; i < this->initial_count; i++) {
        QString categoryName = this->categories[i];
        QString imageName = categoryImageMap[categoryName]; // 위에서 정의한 map

        QToolButton* btn = new QToolButton;
        btn->setIcon(QIcon(":/CATEGORY_IMG/" + imageName));
        btn->setIconSize(QSize(64, 64));
        btn->setText(categoryName);
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btn->setFixedSize(SIZE, SIZE);

        layout->addWidget(btn, row, col);
        if (++col >= this->max_column) {
            col = 0;
            row++;
        }
    }

    int startRow = row;
    int startCol = col;

    // 더보기 버튼
    showMoreBtn(startRow, startCol, layout);
    this->setLayout(layout);
}

void w_grid_category::showMoreBtn(int row, int col, QGridLayout *layout) {
    QPushButton* moreBtn = new QPushButton("더보기");
    moreBtn->setFixedSize(SIZE, SIZE);
    layout->addWidget(moreBtn, row, col);

    connect(moreBtn, &QPushButton::clicked, this, [=]() mutable {
        layout->removeWidget(moreBtn);
        moreBtn->deleteLater();
        showExtraCategories(row, col, layout);
    });
}

void w_grid_category::showExtraCategories(int row, int col, QGridLayout *layout) {
    QMap<QString, QString> categoryImageMap = {
        {"치킨", "CHICKEN.jpeg"},
        {"커피/차", "COFFEE.jpeg"},
        {"버거", "BURGER.jpeg"},
        {"구이", "GOOEE.jpeg"},
        {"샐러드", "SALAD.jpeg"},
        {"한식", "HANSIK.jpeg"},
        {"분식", "BOONSIK.jpeg"},
        {"돈까스", "DONGASS.jpeg"},
        {"족발/보쌈", "JOKBAL.jpeg"},
        {"찜/탕", "JJIM_TANG.jpeg"},
        {"피자", "PIZZA.jpeg"},
        {"중식", "CHINA.jpeg"},
        {"일식", "JAPAN.jpeg"},
        {"회/해물", "SEAFOOD.jpeg"},
        {"양식", "USA.jpeg"},
        {"디저트", "DESSERT.jpeg"},
        {"간식", "SNACK.jpeg"},
        {"아시안", "ASIAN.jpeg"},
        {"샌드위치", "SANDWICH.jpeg"},
        {"멕시칸", "MEXICO.jpeg"},
        {"도시락", "BENTTO.jpeg"},
        {"죽", "JOOK.jpeg"},
        {"포장", "TAKE_OUT.jpeg"},
        {"1인분", "ONE.jpeg"}
    };

    for (int i = this->initial_count; i < this->categories.size(); i++) {
        QString categoryName = this->categories[i];
        QString imageName = categoryImageMap[categoryName];

        QToolButton* btn = new QToolButton;
        btn->setIcon(QIcon(":/CATEGORY_IMG/" + imageName));
        btn->setIconSize(QSize(64, 64));
        btn->setText(categoryName);
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btn->setFixedSize(SIZE, SIZE);

        layout->addWidget(btn, row, col);
        this->extraBtns.append(btn);

        if (++col >= this->max_column) {
            col = 0;
            ++row;
        }
    }

    QPushButton *foldBtn = new QPushButton("접기");
    foldBtn->setFixedSize(SIZE, SIZE);
    layout->addWidget(foldBtn, row, col);

    connect(foldBtn, &QPushButton::clicked, this, [=]() {
        hideExtraCategories(layout, foldBtn);
    });
}


void w_grid_category::hideExtraCategories(QGridLayout *layout, QPushButton *foldBtn) {
    for (QToolButton* btn : this->extraBtns) {
        layout->removeWidget(btn);
        btn->deleteLater();
    }
    this->extraBtns.clear();
    layout->removeWidget(foldBtn);
    foldBtn->deleteLater();
    foldBtn = nullptr;

    showMoreBtn(1, 4, layout);
}

w_grid_category::~w_grid_category()
{
    delete ui;
}
