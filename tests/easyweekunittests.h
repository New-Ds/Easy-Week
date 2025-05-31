#ifndef EASYWEEKUNITTESTS_H
#define EASYWEEKUNITTESTS_H

#include <QtTest/QtTest>
#include <QObject>
#include <QSignalSpy>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QTemporaryFile>
#include <QTextStream>
#include <QApplication>
#include <QWidget>

// Подключаем тестируемые классы
#include "../services/authservice.h"
#include "../services/productservice.h" 
#include "../services/rationservice.h"
#include "../ui/auth/authregwindow.h"
#include "../ui/main/mainwindow.h"
#include "../ui/menu/menucard.h"
#include "../ui/product/add_product.h"
#include "../network/singleton.h"

/**
 * @brief Комплексный набор unit-тестов для приложения EasyWeek
 * 
 * Покрывает все критические компоненты согласно стратегии тестирования:
 * - ТК-001: Регистрация и авторизация пользователей
 * - ТК-002: Добавление продуктов с валидацией
 * - ТК-003: Генерация меню с расчетом БЖУ
 * - ТК-004: Обновление карточек меню
 * - ТК-005: Экспорт меню в файл
 */
class EasyWeekUnitTests : public QObject
{
    Q_OBJECT

public:
    explicit EasyWeekUnitTests(QObject *parent = nullptr);

private slots:
    /**
     * @brief Инициализация перед выполнением тестов
     */
    void initTestCase();
    
    /**
     * @brief Очистка после выполнения тестов
     */
    void cleanupTestCase();
    
    /**
     * @brief Подготовка перед каждым тестом
     */
    void init();
    
    /**
     * @brief Очистка после каждого теста
     */
    void cleanup();

    // ===============================================
    // ТК-001: Тестирование регистрации и авторизации
    // ===============================================
    
    /**
     * @brief Тест успешной регистрации нового пользователя
     */
    void testUserRegistrationSuccess();
    
    /**
     * @brief Тест регистрации с некорректными данными
     */
    void testUserRegistrationFailure();
    
    /**
     * @brief Тест успешной авторизации зарегистрированного пользователя
     */
    void testUserAuthenticationSuccess();
    
    /**
     * @brief Тест авторизации с неверными данными
     */
    void testUserAuthenticationFailure();
    
    /**
     * @brief Тест интеграции UI компонентов авторизации
     */
    void testAuthRegWindowIntegration();

    // ===============================================
    // ТК-002: Тестирование добавления продуктов
    // ===============================================
    
    /**
     * @brief Тест добавления продукта с корректными данными
     */
    void testAddProductWithValidData();
    
    /**
     * @brief Тест добавления продукта с некорректными данными
     */
    void testAddProductWithInvalidData();
    
    /**
     * @brief Тест валидации полей при добавлении продукта
     */
    void testProductFieldValidation();
    
    /**
     * @brief Тест UI компонента добавления продукта
     */
    void testAddProductWindowIntegration();

    // ===============================================
    // ТК-003: Тестирование генерации меню
    // ===============================================
    
    /**
     * @brief Тест корректности генерации меню на неделю
     */
    void testMenuGenerationCorrectness();
    
    /**
     * @brief Тест расчета БЖУ и калорийности
     */
    void testNutritionalCalculation();
    
    /**
     * @brief Тест распределения продуктов по дням
     */
    void testProductDistribution();
    
    /**
     * @brief Тест генерации с недостаточным количеством продуктов
     */
    void testMenuGenerationWithLimitedProducts();

    // ===============================================
    // ТК-004: Тестирование обновления карточек меню
    // ===============================================
    
    /**
     * @brief Тест обновления отдельной карточки меню
     */
    void testMenuCardUpdate();
    
    /**
     * @brief Тест сохранения состояния других карточек при обновлении
     */
    void testMenuCardUpdateIsolation();
    
    /**
     * @brief Тест обновления с изменившимся списком продуктов
     */
    void testMenuCardUpdateWithModifiedProducts();

    // ===============================================
    // ТК-005: Тестирование экспорта меню
    // ===============================================
    
    /**
     * @brief Тест экспорта меню в текстовый файл
     */
    void testMenuExportToFile();
    
    /**
     * @brief Тест корректности структуры экспортированного файла
     */
    void testExportedFileStructure();
    
    /**
     * @brief Тест экспорта с различными наборами продуктов
     */
    void testExportWithDifferentProductSets();
    
    /**
     * @brief Тест обработки ошибок при экспорте
     */
    void testExportErrorHandling();

private:
    // ===============================================
    // Вспомогательные методы и данные для тестирования
    // ===============================================
    
    /**
     * @brief Создание тестовых данных пользователя
     * @return JSON объект с данными пользователя
     */
    QJsonObject createTestUserData();
    
    /**
     * @brief Создание тестовых данных продукта
     * @param name Название продукта
     * @param type Тип продукта
     * @return JSON объект с данными продукта
     */
    QJsonObject createTestProductData(const QString& name = "Test Product", int type = 1);
    
    /**
     * @brief Создание массива тестовых продуктов
     * @param count Количество продуктов
     * @return JSON массив продуктов
     */
    QJsonArray createTestProductArray(int count = 10);
    
    /**
     * @brief Симуляция ответа сервера для тестирования
     * @param type Тип ответа (success/failure)
     * @param data Данные для включения в ответ
     * @return Симулированный ответ сервера
     */
    QByteArray simulateServerResponse(const QString& type, const QJsonValue& data = QJsonValue());
    
    /**
     * @brief Создание временного файла для тестирования экспорта
     * @return Путь к временному файлу
     */
    QString createTemporaryFile();
    
    /**
     * @brief Проверка содержимого экспортированного файла
     * @param filePath Путь к файлу
     * @param expectedContent Ожидаемый контент
     * @return Результат проверки
     */
    bool verifyExportedFileContent(const QString& filePath, const QStringList& expectedContent);
    
    /**
     * @brief Расчет ожидаемых питательных значений
     * @param products Массив продуктов
     * @return Структура с расчетными значениями
     */
    struct NutritionalValues {
        int proteins;
        int fats;
        int carbs;
        int calories;
        int weight;
        int cost;
    };
    NutritionalValues calculateExpectedNutrition(const QJsonArray& products);
    
    /**
     * @brief Проверка валидности структуры меню
     * @param menuData Данные меню для проверки
     * @return Результат валидации
     */
    bool validateMenuStructure(const QJsonArray& menuData);

    // Тестовые данные и объекты
    MainWindow* testMainWindow;
    AuthRegWindow* testAuthWindow;
    AddProductWindow* testAddProductWindow;
    QTemporaryFile* tempFile;
    QRandomGenerator* testRandomGenerator;
    
    // Константы для тестирования
    static const QString TEST_USER_LOGIN;
    static const QString TEST_USER_EMAIL;
    static const QString TEST_USER_PASSWORD;
    static const int EXPECTED_MENU_DAYS;
    static const int MIN_PRODUCTS_PER_DAY;
    static const int MAX_PRODUCTS_PER_DAY;
};

#endif // EASYWEEKUNITTESTS_H
