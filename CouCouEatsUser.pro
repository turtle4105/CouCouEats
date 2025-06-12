QT       += core gui
QT       += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    tcpclient.cpp \
    coucoumain.cpp \
    part1_login_signup.cpp \
    w_grid_category.cpp

HEADERS += \
    dataType.h \
    tcpclient.h \
    coucoumain.h \
    part1_login_signup.h \
    w_grid_category.h


FORMS += \
    coucoumain.ui \
    part1_login_signup.ui \
    w_grid_category.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
