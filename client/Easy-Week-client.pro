QT += core gui
QT += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Singleton.cpp \
    add_product.cpp \
    functions_for_client.cpp \
    main.cpp \
    authregwindow.cpp \
    mainwindow.cpp \
    managerforms.cpp \
    menuCard.cpp \
    productCard.cpp

HEADERS += \
    Singleton.h \
    add_product.h \
    authregwindow.h \
    functions_for_client.h \
    mainwindow.h \
    managerforms.h \
    managerforms.h \
    menuCard.h \
    productCard.h

FORMS += \
    add_product.ui \
    authregwindow.ui \
    mainwindow.ui \
    menuCard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


HEADERS += \
    authregwindow.h \
    functions_for_client.h \
    managerforms.h

FORMS += \
    authregwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
