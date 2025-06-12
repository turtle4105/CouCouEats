#ifndef DATATYPE_H
#define DATATYPE_H

#include <QString>
#include <QVector>


/*
 1. 이용자 정보 자료구조 정의해야 함
- 회원 정보를 어떻게 계속 갖고 있을지~~
- 어떤 데이터가 있어야 하는지

◎ 회원의 자료 구조
회원의 ID
회원의 이름
회원의 주소 구조체 리스트

- 주소 ID
- 주소명
 */

/*
 2. 장바구니 정보 담을 자료구조 ?
 */

struct OptionInfo {
    QString opt_name;     // 옵션 이름
    int opt_price;        // 옵션 가격
    QString opt_state;    // 옵션 상태 (필수 여부 등)
};

struct MenuInfo {
    QString menu_cat_name;    // 메뉴 카테고리 이름
    QString menu_name;        // 메뉴 이름
    int menu_price;           // 메뉴 가격
    QString menu_img_path;    // 이미지 경로
    QString menu_info;        // 메뉴 정보
    QString menu_status;      // 판매중/판매중지
    QString option_category;  // 예: 음료선택
    QString option_required;  // Y/N

    QVector<OptionInfo> options;
};

struct StoreInfo {
    QString store_name;      // 식당 이름
    int category_num;        // 카테고리 번호
    QString store_addr;      // 식당 주소
    QString phone_num;       // 식당 전화번호
    QString owner_name;      // 사장님 이름
    QString opening_time;    // 오픈 시간
    QString closing_time;    // 마감 시간
    int delivery_fee;        // 배달 요금
    int minimum_order;       // 최소 주문 금액
    QString store_desc;      // 가게 인사말
    QString origin_info;     // 원산지 정보
    QString nutrition_fact;  // 영양 성분
    QString allergen_info;   // 알레르기 정보

    QVector<MenuInfo> menus;
};

struct Category {
    QString name;                    // 카테고리 이름
    QString img_path;                // 카테고리 이미지 경로
    QVector<StoreInfo> restaurants;  // 식당 목록
};

struct TopData {
    QVector<Category> categories;
};


#endif // DATATYPE_H
