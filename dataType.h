#ifndef DATATYPE_H
#define DATATYPE_H

#include <QString>
#include <QVector>

// 이용자 정보 자료구조 정의해야 함
/*
- 회원 정보를 어떻게 계속 갖고 있을지~~
- 어떤 데이터가 있어야 하는지

◎ 회원의 자료 구조
회원의 ID
회원의 이름
회원의 주소 구조체 리스트

- 주소 ID
- 주소명
 */

struct OptionInfo {
    QString name;
    int price;
};

struct MenuInfo {
    QString name;
    int price;
    QString img_path;
    QVector<OptionInfo> options;
};

struct StoreInfo {
    QString name;
    QString info;
    QVector<MenuInfo> menus;
};

struct Category {
    QString name;
    QString img_path;
    QVector<StoreInfo> restaurants;
};


struct TopData {
    QVector<Category> categories;
};



#endif // DATATYPE_H
