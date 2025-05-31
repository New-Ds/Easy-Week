# Файл проекта для unit-тестов EasyWeek
QT += core gui widgets testlib network

CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++17

TARGET = EasyWeekTests
TEMPLATE = app

# Определяем пути к исходному коду
CLIENT_PATH = ../client
SERVER_PATH = ../server

# Включаем пути к заголовочным файлам
INCLUDEPATH += $$CLIENT_PATH \
               $$CLIENT_PATH/ui/auth \
               $$CLIENT_PATH/ui/main \
               $$CLIENT_PATH/ui/menu \
               $$CLIENT_PATH/ui/product \
               $$CLIENT_PATH/ui/common \
               $$CLIENT_PATH/services \
               $$CLIENT_PATH/network

# Исходные файлы тестов
SOURCES += \
    main_test.cpp \
    easyweekunittests.cpp

# Заголовочные файлы тестов
HEADERS += \
    easyweekunittests.h

# Подключаем исходные файлы клиента для тестирования
SOURCES += \
    $$CLIENT_PATH/services/authservice.cpp \
    $$CLIENT_PATH/services/productservice.cpp \
    $$CLIENT_PATH/services/rationservice.cpp \
    $$CLIENT_PATH/services/statsservice.cpp \
    $$CLIENT_PATH/network/singleton.cpp \
    $$CLIENT_PATH/ui/auth/authregwindow.cpp \
    $$CLIENT_PATH/ui/main/mainwindow.cpp \
    $$CLIENT_PATH/ui/menu/menucard.cpp \
    $$CLIENT_PATH/ui/product/add_product.cpp \
    $$CLIENT_PATH/ui/product/productcard.cpp \
    $$CLIENT_PATH/ui/common/managerforms.cpp

# Подключаем заголовочные файлы клиента
HEADERS += \
    $$CLIENT_PATH/services/authservice.h \
    $$CLIENT_PATH/services/productservice.h \
    $$CLIENT_PATH/services/rationservice.h \
    $$CLIENT_PATH/services/statsservice.h \
    $$CLIENT_PATH/network/singleton.h \
    $$CLIENT_PATH/ui/auth/authregwindow.h \
    $$CLIENT_PATH/ui/main/mainwindow.h \
    $$CLIENT_PATH/ui/menu/menucard.h \
    $$CLIENT_PATH/ui/product/add_product.h \
    $$CLIENT_PATH/ui/product/productcard.h \
    $$CLIENT_PATH/ui/common/managerforms.h

# UI файлы
FORMS += \
    $$CLIENT_PATH/ui/auth/authregwindow.ui \
    $$CLIENT_PATH/ui/main/mainwindow.ui \
    $$CLIENT_PATH/ui/menu/menuCard.ui \
    $$CLIENT_PATH/ui/product/add_product.ui

# Ресурсы
RESOURCES += \
    $$CLIENT_PATH/resources/resources.qrc

# Компилятор настройки
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Правила развертывания
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Специальные настройки для тестирования
CONFIG(debug, debug|release) {
    DEFINES += EASYWEEK_DEBUG_MODE
    TARGET = $$join(TARGET,,,_debug)
}

# Настройки для Windows
win32 {
    CONFIG += console
    CONFIG -= app_bundle
}

# Настройки для Linux/Unix
unix:!macx {
    CONFIG += link_pkgconfig
}

# Настройки для macOS
macx {
    CONFIG += app_bundle
}
