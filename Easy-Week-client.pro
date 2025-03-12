QT += core gui
QT += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Singleton.cpp \
    functions_for_client.cpp \
    main.cpp \
    authregwindow.cpp \
    mainwindow.cpp \
    managerforms.cpp

HEADERS += \
    Singleton.h \
    authregwindow.h \
    functions_for_client.h \
    mainwindow.h \
    managerforms.h \
    managerforms.h

FORMS += \
    authregwindow.ui \
    mainwindow.ui \
    mainwindow_2.ui

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
