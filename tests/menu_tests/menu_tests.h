#ifndef MENU_TESTS_H
#define MENU_TESTS_H

#include <QObject>
#include <QTest>
#include <QTemporaryFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>
#include <QVector>
#include <QDir>
#include <QMessageBox>

#include "../client/ui/menu/menucard.h"
#include "../client/ui/product/productcard.h"
#include "../client/ui/main/mainwindow.h"
#include "../client/services/productservice.h"

class MenuTests : public QObject
{
    Q_OBJECT

private slots:
    // Инициализация перед тестами
    void initTestCase();
    
    // Тест генерации меню на неделю
    void testGenerateMenu();
    
    // Тест экспорта меню в файл
    void testExportMenu();
    
    // Тест обновления карточки меню
    void testUpdateMenuCard();
    
    // Тест вывода карточек продуктов
    void testDisplayProductCards();
    
    // Тест добавления продукта
    void testAddProduct();
    
    // Очистка после тестов
    void cleanupTestCase();

private:
    // Вспомогательные методы и данные для тестов
    QJsonArray createMockProductsData();
    QWidget* createMenuCardsContainer();
    QString createMockMenuCardContent(const QString& day);
};

#endif // MENU_TESTS_H