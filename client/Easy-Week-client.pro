QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    network/singleton.cpp \
    services/authservice.cpp \
    services/productservice.cpp \
    services/rationservice.cpp \
    services/statsservice.cpp \
    ui/auth/authregwindow.cpp \
    ui/common/managerforms.cpp \
    ui/main/mainwindow.cpp \
    ui/menu/menucard.cpp \
    ui/product/add_product.cpp \
    ui/product/productcard.cpp

HEADERS += \
    network/singleton.h \
    services/authservice.h \
    services/productservice.h \
    services/rationservice.h \
    services/statsservice.h \
    ui/auth/authregwindow.h \
    ui/common/managerforms.h \
    ui/main/mainwindow.h \
    ui/menu/menucard.h \
    ui/product/add_product.h \
    ui/product/productcard.h

FORMS += \
    ui/auth/authregwindow.ui \
    ui/main/mainwindow.ui \
    ui/menu/menuCard.ui \
    ui/product/add_product.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc