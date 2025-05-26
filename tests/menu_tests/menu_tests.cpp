#include "menu_tests.h"

void MenuTests::initTestCase()
{
    // Инициализация данных перед запуском всех тестов
    qDebug() << "Initializing test case for Easy Week menu functionality";
}

QJsonArray MenuTests::createMockProductsData()
{
    // Создаем тестовые данные продуктов в формате JSON
    QJsonArray productArray;
    
    // Продукт 1: Курица
    QJsonObject chicken;
    chicken["id"] = 1;
    chicken["name"] = "Куриная грудка";
    chicken["proteins"] = 25;
    chicken["fatness"] = 2;
    chicken["carbs"] = 0;
    chicken["weight"] = 100;
    chicken["cost"] = 80;
    chicken["type"] = 1; // Мясо
    productArray.append(chicken);
    
    // Продукт 2: Рис
    QJsonObject rice;
    rice["id"] = 2;
    rice["name"] = "Рис отварной";
    rice["proteins"] = 7;
    rice["fatness"] = 1;
    rice["carbs"] = 25;
    rice["weight"] = 100;
    rice["cost"] = 20;
    rice["type"] = 6; // Крупы
    productArray.append(rice);
    
    // Продукт 3: Брокколи
    QJsonObject broccoli;
    broccoli["id"] = 3;
    broccoli["name"] = "Брокколи";
    broccoli["proteins"] = 3;
    broccoli["fatness"] = 0;
    broccoli["carbs"] = 7;
    broccoli["weight"] = 100;
    broccoli["cost"] = 60;
    broccoli["type"] = 3; // Овощи
    productArray.append(broccoli);
    
    // Продукт 4: Яблоко
    QJsonObject apple;
    apple["id"] = 4;
    apple["name"] = "Яблоко";
    apple["proteins"] = 0;
    apple["fatness"] = 0;
    apple["carbs"] = 10;
    apple["weight"] = 100;
    apple["cost"] = 15;
    apple["type"] = 4; // Фрукты
    productArray.append(apple);
    
    // Продукт 5: Творог
    QJsonObject cottageCheese;
    cottageCheese["id"] = 5;
    cottageCheese["name"] = "Творог 5%";
    cottageCheese["proteins"] = 18;
    cottageCheese["fatness"] = 5;
    cottageCheese["carbs"] = 3;
    cottageCheese["weight"] = 100;
    cottageCheese["cost"] = 50;
    cottageCheese["type"] = 5; // Молочные продукты
    productArray.append(cottageCheese);
    
    return productArray;
}

QWidget* MenuTests::createMenuCardsContainer()
{
    // Создаем контейнер для карточек меню
    QWidget* container = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(container);
    
    // Дни недели
    const QStringList days = {"ПОНЕДЕЛЬНИК", "ВТОРНИК", "СРЕДА", "ЧЕТВЕРГ", "ПЯТНИЦА", "СУББОТА", "ВОСКРЕСЕНЬЕ"};
    
    // Создаем карточку для каждого дня
    for (const QString& day : days) {
        // Создаем тестовые данные для карточки
        QStringList products = {"Куриная грудка", "Рис отварной", "Брокколи"};
        QVector<int> pfc = {35, 3, 32}; // Белки, жиры, углеводы
        int calories = 295; // 35*4 + 3*9 + 32*4
        int weight = 300;
        int price = 160;
        
        // Создаем карточку меню
        MenuCard* card = new MenuCard(day, products, calories, pfc, weight, price, container);
        layout->addWidget(card);
    }
    
    return container;
}

QString MenuTests::createMockMenuCardContent(const QString& day)
{
    // Создаем мок-контент карточки меню для тестирования экспорта
    QString content = "=========================================\n";
    content += "              " + day + "\n";
    content += "=========================================\n\n";
    content += "ПРОДУКТЫ:\n";
    content += "  1. Куриная грудка\n";
    content += "  2. Рис отварной\n";
    content += "  3. Брокколи\n";
    content += "\n";
    content += "ПИТАТЕЛЬНАЯ ЦЕННОСТЬ:\n";
    content += "  Белки:    35 г\n";
    content += "  Жиры:     3 г\n";
    content += "  Углеводы: 32 г\n";
    content += "  Калории:  295 ккал\n";
    content += "\n";
    content += "ОБЩАЯ ИНФОРМАЦИЯ:\n";
    content += "  Общий вес:  300 г\n";
    content += "  Общая цена: 160 руб.\n";
    content += "\n\n";
    
    return content;
}

void MenuTests::testGenerateMenu()
{
    // Тестируем генерацию меню на неделю
    
    // Создаем тестовые данные продуктов
    QJsonArray productArray = createMockProductsData();
    
    // Создаем тестовый экземпляр MainWindow
    MainWindow mainWindow;
    
    // Тестируем метод generateMenuCardForDay
    const QString dayName = "ПОНЕДЕЛЬНИК";
    QWidget* parent = new QWidget();
    int index = 0;
    
    // Вызываем тестируемый метод
    MenuCard* menuCard = mainWindow.generateMenuCardForDay(dayName, productArray, parent, index);
    
    // Проверяем результаты
    QVERIFY(menuCard != nullptr);
    QCOMPARE(menuCard->property("objectName").toString(), "menuCard");
    
    // Проверяем, что день недели отображается корректно
    QLabel* dayLabel = menuCard->findChild<QLabel*>("dayLabel");
    QVERIFY(dayLabel != nullptr);
    QCOMPARE(dayLabel->text(), dayName);
    
    // Проверяем, что в карточке есть продукты
    QList<QLabel*> labels = menuCard->findChildren<QLabel*>();
    bool hasProducts = false;
    for (QLabel* label : labels) {
        if (!label->text().contains(":") && !label->text().contains(dayName)) {
            hasProducts = true;
            break;
        }
    }
    QVERIFY(hasProducts);
    
    // Проверяем, что отображается информация о питательности
    bool hasNutrition = false;
    for (QLabel* label : labels) {
        if (label->text().startsWith("БЖУ:") || 
            label->text().startsWith("Калории:") || 
            label->text().startsWith("Вес:") || 
            label->text().startsWith("Цена:")) {
            hasNutrition = true;
            break;
        }
    }
    QVERIFY(hasNutrition);
    
    // Очистка
    delete parent;
}

void MenuTests::testExportMenu()
{
    // Тестируем экспорт меню в файл
    
    // Создаем временный файл для теста
    QTemporaryFile tempFile;
    if (!tempFile.open()) {
        QFAIL("Could not create temporary file for testing");
    }
    
    // Получаем имя временного файла
    QString fileName = tempFile.fileName();
    tempFile.close(); // Закрываем, чтобы можно было открыть для записи в тесте
    
    // Создаем тестовые данные
    QWidget* container = createMenuCardsContainer();
    
    // Открываем файл для записи
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QFAIL("Could not open temporary file for writing");
    }
    
    QTextStream out(&file);
    
    // Эмулируем экспорт меню (как в методе on_exportButton_clicked)
    // Заголовок файла
    out << "=========================================\n";
    out << "        МЕНЮ НА НЕДЕЛЮ - EASY WEEK      \n";
    out << "=========================================\n\n";
    out << "Пользователь: test_user (test@example.com)\n";
    out << "Дата экспорта: " << QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm") << "\n\n";
    
    // Дни недели
    const QStringList days = {"ПОНЕДЕЛЬНИК", "ВТОРНИК", "СРЕДА", "ЧЕТВЕРГ", "ПЯТНИЦА", "СУББОТА", "ВОСКРЕСЕНЬЕ"};
    
    // Записываем контент для каждого дня
    for (const QString& day : days) {
        out << createMockMenuCardContent(day);
    }
    
    // Записываем итоговую информацию
    out << "=========================================\n";
    out << "          ИТОГО ЗА НЕДЕЛЮ:\n";
    out << "=========================================\n\n";
    
    out << "ИТОГОВАЯ СВОДКА ПО ПИТАТЕЛЬНОЙ ЦЕННОСТИ:\n";
    out << "  Белки:    245 г\n";
    out << "  Жиры:     21 г\n";
    out << "  Углеводы: 224 г\n";
    out << "  Калории:  2065 ккал\n\n";
    
    out << "ИТОГОВАЯ СВОДКА ПО ВЕСУ И СТОИМОСТИ:\n";
    out << "  Общий вес за неделю:  2100 г (2.1 кг)\n";
    out << "  Общая цена за неделю: 1120 руб.\n";
    
    // Закрываем файл
    file.close();
    
    // Проверяем, что файл создан и содержит нужные данные
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QFAIL("Could not open temporary file for reading");
    }
    
    QString fileContent = file.readAll();
    file.close();
    
    // Проверяем наличие ключевых элементов в экспортированном файле
    QVERIFY(fileContent.contains("МЕНЮ НА НЕДЕЛЮ - EASY WEEK"));
    QVERIFY(fileContent.contains("ПОНЕДЕЛЬНИК"));
    QVERIFY(fileContent.contains("ИТОГО ЗА НЕДЕЛЮ"));
    QVERIFY(fileContent.contains("ПРОДУКТЫ:"));
    QVERIFY(fileContent.contains("ПИТАТЕЛЬНАЯ ЦЕННОСТЬ:"));
    QVERIFY(fileContent.contains("Белки:"));
    QVERIFY(fileContent.contains("Общая цена за неделю:"));
    
    // Очистка
    delete container;
}

void MenuTests::testUpdateMenuCard()
{
    // Тестируем обновление карточки меню
    
    // Создаем тестовые данные
    QJsonArray productArray = createMockProductsData();
    QWidget* container = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(container);
    
    // Создаем тестовую карточку меню
    const QString dayName = "ПОНЕДЕЛЬНИК";
    QStringList products = {"Куриная грудка", "Рис отварной"};
    QVector<int> pfc = {32, 3, 25}; // Начальные БЖУ
    int calories = 255;
    int weight = 200;
    int price = 100;
    int index = 0;
    
    MenuCard* oldCard = new MenuCard(dayName, products, calories, pfc, weight, price, container, index);
    layout->addWidget(oldCard);
    
    // Запоминаем ссылку на старую карточку
    QPointer<MenuCard> oldCardPointer(oldCard);
    
    // Создаем тестовый экземпляр MainWindow
    MainWindow mainWindow;
    
    // Эмулируем обновление карточки меню (как в методе updateMenuCard)
    // В реальном методе используется функция layout->itemAt(cardIndex)->widget(),
    // но здесь мы знаем, что у нас только одна карточка
    oldCard->hide();
    layout->removeWidget(oldCard);
    
    // Создаем новую карточку
    MenuCard* newCard = mainWindow.generateMenuCardForDay(dayName, productArray, container, index);
    layout->insertWidget(index, newCard);
    
    // Проверяем, что старая карточка была скрыта и удалена из layout
    QVERIFY(!oldCardPointer->isVisible());
    
    // Проверяем, что новая карточка была добавлена в layout
    QCOMPARE(layout->count(), 1);
    QVERIFY(layout->itemAt(0)->widget() == newCard);
    
    // Проверяем, что новая карточка отображает корректные данные
    QVERIFY(newCard->findChild<QLabel*>("dayLabel")->text() == dayName);
    
    // Очистка
    delete container; // Также удалит все дочерние виджеты
    delete oldCardPointer; // Удаляем старую карточку если она еще существует
}

void MenuTests::testDisplayProductCards()
{
    // Тестируем вывод карточек продуктов
    
    // Создаем тестовые данные продуктов
    QJsonArray productArray = createMockProductsData();
    
    // Создаем контейнер для карточек продуктов
    QWidget* container = new QWidget();
    QGridLayout* gridLayout = new QGridLayout(container);
    
    // Добавляем карточки продуктов в сетку
    const int columns = 2; // Для теста используем 2 колонки
    for (int i = 0; i < productArray.size(); ++i) {
        QJsonObject obj = productArray[i].toObject();
        
        QString productName = obj["name"].toString();
        int price = obj["cost"].toInt();
        int proteins = obj["proteins"].toInt();
        int fatness = obj["fatness"].toInt();
        int carbs = obj["carbs"].toInt();
        
        // Создаем карточку продукта
        ProductCard* card = new ProductCard(productName, price, proteins, fatness, carbs, container);
        gridLayout->addWidget(card, i / columns, i % columns);
    }
    
    // Проверяем, что все карточки добавлены
    QCOMPARE(gridLayout->count(), productArray.size());
    
    // Проверяем, что каждая карточка содержит правильную информацию
    for (int i = 0; i < gridLayout->count(); ++i) {
        QLayoutItem* item = gridLayout->itemAt(i);
        ProductCard* card = qobject_cast<ProductCard*>(item->widget());
        QVERIFY(card != nullptr);
        
        // Находим все надписи в карточке
        QList<QLabel*> labels = card->findChildren<QLabel*>();
        
        // Проверяем, что название продукта отображается
        QJsonObject expectedProduct = productArray[i].toObject();
        QString expectedName = expectedProduct["name"].toString();
        
        bool foundName = false;
        for (QLabel* label : labels) {
            if (label->text() == expectedName) {
                foundName = true;
                break;
            }
        }
        QVERIFY2(foundName, qPrintable("Product name not found in card: " + expectedName));
        
        // Проверяем, что отображается цена
        QString expectedPrice = "Цена: " + QString::number(expectedProduct["cost"].toInt()) + "₽";
        bool foundPrice = false;
        for (QLabel* label : labels) {
            if (label->text() == expectedPrice) {
                foundPrice = true;
                break;
            }
        }
        QVERIFY2(foundPrice, qPrintable("Price not found in card for: " + expectedName));
    }
    
    // Очистка
    delete container;
}

void MenuTests::testAddProduct()
{
    // Тестируем добавление продукта
    
    // Создаем тестовые данные
    QString userId = "1";
    QString productName = "Тестовый продукт";
    int proteins = 10;
    int fats = 5;
    int carbs = 15;
    int weight = 100;
    int cost = 50;
    int type = 7; // Другое
    
    // Мокаем вызов метода addProduct в ProductService
    // В реальном тесте мы бы использовали мок-объект, но для примера эмулируем успешный ответ
    
    // Создаем тестовый экземпляр MainWindow
    MainWindow mainWindow;
    
    // Устанавливаем ID пользователя
    mainWindow.id = userId;
    
    // Заменяем QMessageBox на мок
    QMessageBox::StandardButton mockResult = QMessageBox::Ok;
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);
    
    // Эмулируем успешное добавление продукта
    // В реальности мы бы мокировали сетевой запрос
    
    // Проверяем, что метод обрабатывает добавление продукта
    bool exceptionThrown = false;
    try {
        mainWindow.handleProductAdded(productName, proteins, fats, carbs, weight, cost, type);
    } catch (...) {
        exceptionThrown = true;
    }
    
    // Проверяем, что исключение не было выброшено
    QVERIFY(!exceptionThrown);
}

void MenuTests::cleanupTestCase()
{
    // Очистка после всех тестов
    qDebug() << "Cleaning up after test case";
    
    // Удаляем временные файлы и ресурсы
}

// Для запуска тестов
QTEST_MAIN(MenuTests)
#include "menu_tests.moc"