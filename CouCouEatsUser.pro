QT       += core gui
QT       += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    coucoumain.cpp \
    tcpclient.cpp \
    main2_login.cpp \
    w_h_menu_card.cpp \
    w_v_menu_card.cpp \
    w_v_store_card.cpp

HEADERS += \
    coucoumain.h \
    tcpclient.h \
    main2_login.h \
    w_h_menu_card.h \
    w_v_menu_card.h \
    w_v_store_card.h

FORMS += \
    coucoumain.ui \
    main2_login.ui \
    w_h_menu_card.ui \
    w_v_menu_card.ui \
    w_v_store_card.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
