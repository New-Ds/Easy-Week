QT += core gui widgets testlib network

CONFIG += c++17 testcase

TARGET = menu_tests
TEMPLATE = app

# Путь к исходникам основного проекта
INCLUDEPATH += \
    ../../client

# Исходники тестов
SOURCES += \
    menu_tests.cpp

HEADERS += \
    menu_tests.h

# Исходники основного проекта, необходимые для тестирования
SOURCES += \
    ../../client/ui/menu/menucard.cpp \
    ../../client/ui/product/productcard.cpp \
    ../../client/ui/main/mainwindow.cpp \
    ../../client/services/productservice.cpp

HEADERS += \
    ../../client/ui/menu/menucard.h \
    ../../client/ui/product/productcard.h \
    ../../client/ui/main/mainwindow.h \
    ../../client/services/productservice.h

# Формы Qt UI
FORMS += \
    ../../client/ui/menu/menuCard.ui \
    ../../client/ui/main/mainwindow.ui

# Ресурсы приложения
RESOURCES += \
    ../../client/resources/resources.qrc