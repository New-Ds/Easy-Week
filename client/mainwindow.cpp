#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QScrollArea>
#include <QDebug>

#include <QProcess>
#include <QApplication>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_show() {
    this->show();
};



//здесь мы забираем авторизовавшегося юзера используя сигнал, который посылаем из окна авторизации
void MainWindow::set_current_user(QString id, QString login,  QString email) {
    this->id = id;
    this->login = login;
    this->email = email;

    // Проверка на права администратора (временное решение)
    bool isAdmin = (email == "admin@new-devs.ru\r\n");

    // Управление видимостью компонентов администратора
    ui->adminSectionLabel->setVisible(isAdmin);
    ui->tableUsersButton->setVisible(isAdmin);
    ui->stableStatButton->setVisible(isAdmin);
    ui->dynamicStatButton->setVisible(isAdmin);
    ui->manageRoleButton->setVisible(isAdmin);

    // По умолчанию скрываем вертикальный layout с кнопками администратора
    for (int i = 0; i < ui->verticalLayout_2->count(); ++i) {
        QWidget* widget = ui->verticalLayout_2->itemAt(i)->widget();
        if (widget) {
            widget->setVisible(isAdmin);
        }
    }

    // Отображение меню при старте программы
    on_createMenButton_clicked();
}



// на время получения ответа с севера (5 сек) нужно будет делать кнопки заблокированными, чтобы юзер не тыкал их несколько раз
// и таким образом не отправлял на сервер несколько запросов сразу

void MainWindow::on_stableStatButton_clicked()
{
    QString stat = get_stable_stat(); // вызываем функцию получения статистки из func_for_cleint по клику на кнопку
    qDebug() << stat;
}


void MainWindow::on_dynamicStatButton_clicked()
{
    QString stat = get_dynamic_stat(); // вызываем функцию получения статистки из func_for_cleint по клику на кнопку
    qDebug() << stat;
}

void MainWindow::createUsersTableUI()
{
    // Инициализация основного контейнера с архитектурой компоновки
    usersTableContainer = new QWidget(ui->mainContainer);
    usersTableContainer->setObjectName("usersTableContainer");

    QVBoxLayout* mainLayout = new QVBoxLayout(usersTableContainer);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // Заголовок секции с корпоративным стилем
    QLabel* titleLabel = new QLabel("Управление пользователями системы");
    titleLabel->setStyleSheet(
        "font-size: 24px; "
        "font-weight: bold; "
        "color: #2c3e50; "
        "margin-bottom: 10px;"
        );
    mainLayout->addWidget(titleLabel);

    // Панель управления с фильтрацией и поиском
    QHBoxLayout* controlPanelLayout = new QHBoxLayout();
    controlPanelLayout->setSpacing(15);

    // Компонент фильтрации по ролям
    QLabel* filterLabel = new QLabel("Фильтр по статусу:");
    filterLabel->setStyleSheet("font-size: 14px; font-weight: bold;");

    usersFilterCombo = new QComboBox();
    usersFilterCombo->addItem("Все пользователи");
    usersFilterCombo->addItem("Только администраторы");
    usersFilterCombo->addItem("Только пользователи");
    usersFilterCombo->setMinimumWidth(200);
    usersFilterCombo->setStyleSheet(
        "QComboBox {"
        "    border: 1px solid #cccccc;"
        "    border-radius: 4px;"
        "    padding: 8px;"
        "    background-color: white;"
        "    font-size: 14px;"
        "    color: #000000;"
        "}"
        "QComboBox:hover {"
        "    border: 1px solid #4a86e8;"
        "    color: #000000;"
        "}"
        "QComboBox::drop-down {"
        "    border: none;"
        "    width: 20px;"
        "    color: #000000;"
        "}"
        "QComboBox QAbstractItemView {"
        "    color: #000000;"
        "}"
        "QComboBox::down-arrow {"
        "    image: none;"
        "    border-left: 5px solid transparent;"
        "    border-right: 5px solid transparent;"
        "    border-top: 5px solid #333;"
        "    margin-right: 5px;"
        "    color: #000000;"
        "}"
        );

    // Компонент интеллектуального поиска
    QLabel* searchLabel = new QLabel("Поиск:");
    searchLabel->setStyleSheet("font-size: 14px; font-weight: bold;");

    usersSearchLine = new QLineEdit();
    usersSearchLine->setPlaceholderText("Введите имя или email...");
    usersSearchLine->setMinimumWidth(250);
    usersSearchLine->setStyleSheet(
        "QLineEdit {"
        "    border: 1px solid #cccccc;"
        "    border-radius: 4px;"
        "    padding: 8px;"
        "    background-color: white;"
        "    font-size: 14px;"
        "    color: #000000;"
        "}"
        "QLineEdit:focus {"
        "    border: 1px solid #4a86e8;"
        "    background-color: #f9f9f9;"
        "}"
        );

    // Кнопка синхронизации данных
    QPushButton* refreshButton = new QPushButton("Обновить данные");
    refreshButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4a86e8;"
        "    color: white;"
        "    border: none;"
        "    padding: 8px 20px;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #3a76d8;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #2a66c8;"
        "}"
        );

    // Компоновка панели управления
    controlPanelLayout->addWidget(filterLabel);
    controlPanelLayout->addWidget(usersFilterCombo);
    controlPanelLayout->addWidget(searchLabel);
    controlPanelLayout->addWidget(usersSearchLine);
    controlPanelLayout->addStretch();
    controlPanelLayout->addWidget(refreshButton);

    mainLayout->addLayout(controlPanelLayout);

    // Инициализация табличного компонента
    usersTable = new QTableWidget();
    usersTable->setColumnCount(4);
    QStringList headers = {"ID", "Имя пользователя", "Email", "Статус"};
    usersTable->setHorizontalHeaderLabels(headers);
    usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    usersTable->setAlternatingRowColors(true);
    usersTable->horizontalHeader()->setStretchLastSection(true);
    usersTable->setSortingEnabled(true);
    usersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Применение корпоративного стиля к таблице
    styleUsersTable();

    mainLayout->addWidget(usersTable);

    // Подключение сигналов для реактивного интерфейса
    // Техническое решение: используем лямбда-функции вместо слотов
    connect(usersFilterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index) {
                Q_UNUSED(index);
                filterUsersTable();
            });

    connect(usersSearchLine, &QLineEdit::textChanged,
            [this](const QString& text) {
                Q_UNUSED(text);
                filterUsersTable();
            });

    connect(refreshButton, &QPushButton::clicked,
            [this]() {
                refreshUsersTable();
            });

    // Интеграция в основной layout
    QVBoxLayout* containerLayout = qobject_cast<QVBoxLayout*>(ui->mainContainer->layout());
    if (!containerLayout) {
        containerLayout = new QVBoxLayout(ui->mainContainer);
        containerLayout->setContentsMargins(0, 0, 0, 0);
        ui->mainContainer->setLayout(containerLayout);
    }

    containerLayout->addWidget(usersTableContainer);
}

void MainWindow::populateUsersTable(const QByteArray& jsonData)
{
    // Архитектурное решение: детальная диагностика на всех уровнях
    qDebug() << "=== JSON DEBUG START ===";
    qDebug() << "Raw data size:" << jsonData.size();
    qDebug() << "Raw data (first 200 chars):" << jsonData.left(200);
    qDebug() << "Raw data (hex):" << jsonData.toHex().left(100);

    // Техническое решение: очистка данных от артефактов протокола
    QByteArray cleanedData = jsonData;

    // Удаление управляющих символов \r\n в конце
    if (cleanedData.endsWith("\r\n")) {
        cleanedData.chop(2);
        qDebug() << "Removed \\r\\n from end";
    }

    // Проверка на BOM (Byte Order Mark) и его удаление
    if (cleanedData.startsWith("\xEF\xBB\xBF")) {
        cleanedData.remove(0, 3);
        qDebug() << "Removed BOM";
    }

    // Валидация начала и конца JSON
    cleanedData = cleanedData.trimmed();

    // Архитектурное решение: проверка валидности JSON структуры
    if (!cleanedData.startsWith('[') || !cleanedData.endsWith(']')) {
        qDebug() << "ERROR: Invalid JSON structure";
        qDebug() << "First char:" << (cleanedData.isEmpty() ? "EMPTY" : QString(cleanedData.at(0)));
        qDebug() << "Last char:" << (cleanedData.isEmpty() ? "EMPTY" : QString(cleanedData.at(cleanedData.length()-1)));

        // Попытка найти JSON в ответе
        int jsonStart = cleanedData.indexOf('[');
        int jsonEnd = cleanedData.lastIndexOf(']');

        if (jsonStart != -1 && jsonEnd != -1 && jsonEnd > jsonStart) {
            cleanedData = cleanedData.mid(jsonStart, jsonEnd - jsonStart + 1);
            qDebug() << "Extracted JSON from position" << jsonStart << "to" << jsonEnd;
        } else {
            QMessageBox::critical(this, "Критическая ошибка",
                                  "Сервер вернул некорректный формат данных.\n"
                                  "Проверьте серверную часть приложения.");
            return;
        }
    }

    qDebug() << "Cleaned data:" << cleanedData;
    qDebug() << "=== JSON DEBUG END ===";

    // Парсинг с детальной обработкой ошибок
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(cleanedData, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "JSON parsing error:" << error.errorString();
        qDebug() << "Error offset:" << error.offset;
        qDebug() << "Error type:" << error.error;

        // Техническое решение: показ контекста ошибки
        if (error.offset > 0 && error.offset < cleanedData.size()) {
            int contextStart = qMax(0, error.offset - 20);
            int contextEnd = qMin(cleanedData.size(), error.offset + 20);
            qDebug() << "Context around error:" << cleanedData.mid(contextStart, contextEnd - contextStart);
            qDebug() << "Error position marked: " << QString(error.offset - contextStart, ' ') << "^";
        }

        QMessageBox::warning(this, "Ошибка парсинга",
                             QString("Не удалось обработать данные пользователей.\n"
                                     "Ошибка: %1\n"
                                     "Позиция: %2").arg(error.errorString()).arg(error.offset));
        return;
    }

    if (!doc.isArray()) {
        QString docType = "Unknown";
        if (doc.isObject()) docType = "Object";
        else if (doc.isNull()) docType = "Null";
        else if (doc.isEmpty()) docType = "Empty";

        qDebug() << "ERROR: Root element is not array. Document type:" << docType;
        QMessageBox::warning(this, "Ошибка формата",
                             QString("Сервер вернул данные в неверном формате.\n"
                                     "Ожидался массив JSON, получен: %1").arg(docType));
        return;
    }

    // Сохранение валидных данных
    allUsersData = doc.array();
    qDebug() << "Successfully parsed" << allUsersData.size() << "users";

    // Применение фильтров к валидным данным
    filterUsersTable();
}

void MainWindow::filterUsersTable()
{
    // Очистка таблицы перед новой отрисовкой
    usersTable->setRowCount(0);

    // Получение параметров фильтрации
    QString searchText = usersSearchLine->text().toLower().trimmed();
    int filterIndex = usersFilterCombo->currentIndex();

    // Архитектурный паттерн: применение фильтров в цикле обработки
    for (const QJsonValue& value : allUsersData) {
        QJsonObject user = value.toObject();

        // Извлечение атрибутов пользователя
        int userId = user["id"].toInt();
        QString name = user["name"].toString();
        QString email = user["email"].toString();
        bool isAdmin = user["is_admin"].toBool();

        // Логика фильтрации по ролям
        if (filterIndex == 1 && !isAdmin) continue;    // Только администраторы
        if (filterIndex == 2 && isAdmin) continue;     // Только обычные пользователи

        // Интеллектуальный поиск по множественным полям
        if (!searchText.isEmpty()) {
            bool matchFound = name.toLower().contains(searchText) ||
                              email.toLower().contains(searchText) ||
                              QString::number(userId).contains(searchText);
            if (!matchFound) continue;
        }

        // Добавление строки в таблицу
        int row = usersTable->rowCount();
        usersTable->insertRow(row);

        // Заполнение ячеек с форматированием
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(userId));
        idItem->setTextAlignment(Qt::AlignCenter);
        usersTable->setItem(row, 0, idItem);

        usersTable->setItem(row, 1, new QTableWidgetItem(name));
        usersTable->setItem(row, 2, new QTableWidgetItem(email));

        // Визуализация статуса с цветовой индикацией
        QTableWidgetItem* statusItem = new QTableWidgetItem(isAdmin ? "Администратор" : "Пользователь");
        statusItem->setTextAlignment(Qt::AlignCenter);

        if (isAdmin) {
            // Зеленая цветовая схема для администраторов
            statusItem->setBackground(QColor("#e8f5e9"));
            statusItem->setForeground(QColor("#2e7d32"));
            QFont font = statusItem->font();
            font.setBold(true);
            statusItem->setFont(font);
        } else {
            // Фиолетовая цветовая схема для пользователей
            statusItem->setBackground(QColor("#f3e5f5"));
            statusItem->setForeground(QColor("#6a1b9a"));
        }

        usersTable->setItem(row, 3, statusItem);
    }

    // Адаптивная настройка ширины столбцов
    usersTable->resizeColumnsToContents();
    usersTable->setColumnWidth(0, 80);  // ID
    usersTable->setColumnWidth(1, 200); // Имя
    usersTable->setColumnWidth(2, 250); // Email
}

void MainWindow::styleUsersTable()
{
    // Применение корпоративного дизайн-системы к таблице
    usersTable->setStyleSheet(
        "QTableWidget {"
        "    border: 1px solid #cccccc;"
        "    border-radius: 4px;"
        "    background-color: white;"
        "    gridline-color: #e0e0e0;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QTableWidget::item {"
        "    padding: 10px;"
        "    font-size: 14px;"
        "    border-bottom: 1px solid #f0f0f0;"
        "    color: #000000;"
        "}"
        "QTableWidget::item:selected {"
        "    background-color: #e3f2fd;"
        "    color: #1976d2;"
        "}"
        "QTableWidget::item:hover {"
        "    background-color: #f5f5f5;"
        "}"
        "QHeaderView::section {"
        "    background-color: #f5f5f5;"
        "    padding: 12px;"
        "    border: none;"
        "    border-bottom: 2px solid #4a86e8;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "    color: #2c3e50;"
        "}"
        "QHeaderView::section:hover {"
        "    background-color: #e8e8e8;"
        "}"
        "QTableWidget::verticalHeader {"
        "    border: none;"
        "    background-color: #fafafa;"
        "}"
        "QTableWidget QTableCornerButton::section {"
        "    background-color: #f5f5f5;"
        "    border: none;"
        "}"
        );

    // Архитектурное решение: скрытие вертикального заголовка для минимализма
    usersTable->verticalHeader()->setVisible(false);

    // Настройка высоты строк для улучшенной читаемости
    usersTable->verticalHeader()->setDefaultSectionSize(45);

    // Визуальная оптимизация: фиксированная ширина первого столбца
    usersTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    usersTable->setColumnWidth(0, 80);
}

void MainWindow::refreshUsersTable()
{
    // Архитектурный паттерн: централизованное обновление данных
    QByteArray usersData = get_all_users();

    // Визуальная индикация загрузки (опционально для UX)
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // Обработка полученных данных
    populateUsersTable(usersData);

    // Восстановление курсора
    QApplication::restoreOverrideCursor();

    // Информирование пользователя об успешном обновлении
    qDebug() << "Данные пользователей успешно обновлены";
}

void MainWindow::on_tableUsersButton_clicked()
{
    // Архитектурный паттерн: скрытие всех активных виджетов
    for (QObject* child : ui->mainContainer->children()) {
        if (QWidget* widget = qobject_cast<QWidget*>(child)) {
            widget->hide();
        }
    }

    // Ленивая инициализация - создаем UI только при первом вызове
    if (!usersTableContainer) {
        createUsersTableUI();
    }

    // Загрузка актуальных данных с сервера
    refreshUsersTable();

    // Отображение контейнера с таблицей
    usersTableContainer->show();
}

void MainWindow::on_productListButton_clicked()
{
    // Получаем данные продуктов через API
    QByteArray productsJson = get_products(id);
    // qDebug() << "Сырой JSON продуктов: " << productsJson;

    // Проверяем наличие существующей области отображения продуктов
    QScrollArea* productScrollArea = ui->mainContainer->findChild<QScrollArea*>("productScrollArea");

    // Скрываем все дочерние виджеты для переключения режима отображения
    for (QObject* child : ui->mainContainer->children()) {
        if (QWidget* widget = qobject_cast<QWidget*>(child)) {
            widget->hide();
        }
    }

    // Используем кешированную область прокрутки, если она уже существует
    if (productScrollArea) {
        productScrollArea->show();
        return;
    }

    // Инициализируем область прокрутки для списка продуктов
    productScrollArea = new QScrollArea(ui->mainContainer);
    productScrollArea->setObjectName("productScrollArea");
    productScrollArea->setWidgetResizable(true); // Критично для автоматической адаптации размера
    productScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    productScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Создаем контейнер для размещения карточек продуктов в сетке
    QWidget* productListWidget = new QWidget();
    productListWidget->setObjectName("productListWidget");
    QGridLayout* gridLayout = new QGridLayout(productListWidget);
    gridLayout->setSpacing(15); // Оптимальный отступ между карточками

    // Парсим JSON с валидацией
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(productsJson, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Ошибка парсинга JSON: " << parseError.errorString();
        return;
    }

    if (!doc.isArray()) {
        qDebug() << "Ошибка: ожидался JSON-массив!";
        return;
    }

    QJsonArray productArray = doc.array();

    // Размещаем продукты в сетке с фиксированным количеством колонок
    const int columns = 4;
    for (int i = 0; i < productArray.size(); ++i) {
        QJsonObject obj = productArray[i].toObject();

        QString productName = obj["name"].toString();
        int price = obj["cost"].toInt();
        int proteins = obj["proteins"].toInt();
        int fatness = obj["fatness"].toInt();
        int carbs = obj["carbs"].toInt();

        // qDebug() << "Продукт #" << (i + 1) << " Name:" << productName << " Price:" << price << " Proteins:" << proteins << " Fatness:" << fatness << " Carbs:" << carbs;

        // Создаем карточку продукта с сохранением натурального размера
        productCard* card = new productCard(productName, price, proteins, fatness, carbs, productListWidget);


        // Регулируем размеры карточки для консистентного отображения
        card->setMinimumHeight(200); // Гарантируем минимальную высоту
        card->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addWidget(card, i / columns, i % columns);
    }

    // Устанавливаем контент-виджет в область прокрутки
    productScrollArea->setWidget(productListWidget);

    // Инициализируем или используем существующий layout для контейнера
    QVBoxLayout* containerLayout = qobject_cast<QVBoxLayout*>(ui->mainContainer->layout());
    if (!containerLayout) {
        containerLayout = new QVBoxLayout(ui->mainContainer);
        ui->mainContainer->setLayout(containerLayout);
    }

    // Добавляем область прокрутки в основной контейнер
    containerLayout->addWidget(productScrollArea);
    productScrollArea->show();
}


void MainWindow::on_createMenButton_clicked()
{
    // Проверяем, существует ли уже область для меню
    QScrollArea* menuScrollArea = ui->mainContainer->findChild<QScrollArea*>("menuScrollArea");

    // Сначала скрываем все виджеты в контейнере
    for (QObject* child : ui->mainContainer->children()) {
        if (QWidget* widget = qobject_cast<QWidget*>(child)) {
            widget->hide();
        }
    }

    // Если ScrollArea для меню уже существует, просто показываем её
    if (menuScrollArea) {
        menuScrollArea->show();
        return;
    }

    // Инициализируем интерфейс прокрутки для меню
    menuScrollArea = new QScrollArea(ui->mainContainer);
    menuScrollArea->setObjectName("menuScrollArea");
    menuScrollArea->setWidgetResizable(false);
    menuScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Получаем продукты из базы данных
    QByteArray productsJson = get_products(id);
    QJsonDocument doc = QJsonDocument::fromJson(productsJson);

    if (!doc.isArray()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось получить список продуктов");
        return;
    }

    QJsonArray productArray = doc.array();

    // Создаем контейнер для карточек меню
    QWidget* cardsContainer = new QWidget();
    QHBoxLayout* cardsLayout = new QHBoxLayout(cardsContainer);
    cardsLayout->setSpacing(5);

    // Дни недели
    const QStringList days = {"ПОНЕДЕЛЬНИК", "ВТОРНИК", "СРЕДА", "ЧЕТВЕРГ", "ПЯТНИЦА", "СУББОТА", "ВОСКРЕСЕНЬЕ"};

    // Генерируем меню для каждого дня недели
    for (int dayIndex = 0; dayIndex < 7; dayIndex++) {
        // Распределяем продукты по типам для разнообразного меню
        QMap<int, QList<QJsonObject>> productsByType;
        int totalProducts = productArray.size();

        for (int i = 0; i < totalProducts; ++i) {
            QJsonObject product = productArray[i].toObject();
            int type = product["type"].toInt();
            productsByType[type].append(product);
        }

        // Выбираем случайные продукты для дня (3-5 продуктов)
        QStringList selectedProducts;
        QVector<int> pfc = {0, 0, 0}; // Белки, Жиры, Углеводы
        int totalCalories = 0;
        int totalWeight = 0;
        int totalPrice = 0;

        // Определяем количество продуктов для этого дня
        int productsForDay = qMin(3 + (QRandomGenerator::global()->bounded(3)), totalProducts);

        for (int i = 0; i < productsForDay && !productsByType.isEmpty(); ++i) {
            // Выбираем случайный тип продукта из доступных
            QList<int> types = productsByType.keys();
            if (types.isEmpty()) break;

            int randomTypeIndex = QRandomGenerator::global()->bounded(types.size());
            int selectedType = types[randomTypeIndex];

            QList<QJsonObject>& productsOfType = productsByType[selectedType];
            if (productsOfType.isEmpty()) {
                productsByType.remove(selectedType);
                --i; // Повторяем итерацию
                continue;
            }

            // Выбираем случайный продукт этого типа
            int randomProductIndex = QRandomGenerator::global()->bounded(productsOfType.size());
            QJsonObject selectedProduct = productsOfType.takeAt(randomProductIndex);

            // Удаляем тип, если больше нет продуктов этого типа
            if (productsOfType.isEmpty()) {
                productsByType.remove(selectedType);
            }

            // Добавляем продукт в меню
            QString productName = selectedProduct["name"].toString();
            selectedProducts.append(productName);

            // Суммируем БЖУ, калории, вес и цену
            pfc[0] += selectedProduct["proteins"].toInt();
            pfc[1] += selectedProduct["fatness"].toInt();
            pfc[2] += selectedProduct["carbs"].toInt();

            int weight = selectedProduct["weight"].toInt();
            int price = selectedProduct["cost"].toInt();
            totalWeight += weight;
            totalPrice += price;
            // Приблизительный расчет калорий: 4 ккал на 1г белка, 9 ккал на 1г жира, 4 ккал на 1г углеводов
            totalCalories += pfc[0] * 4 + pfc[1] * 9 + pfc[2] * 4;
        }

        // Создаем карточку меню для дня

        menuCard* card = generateMenuCardForDay(days[dayIndex], productArray, cardsContainer, dayIndex);
        connect(card, &menuCard::buttonClicked, this, &MainWindow::updateMenuCard);
        card->setFixedHeight(450);
        cardsLayout->addWidget(card);
    }

    // Настраиваем область прокрутки
    menuScrollArea->setWidget(cardsContainer);

    // Добавляем ScrollArea в контейнер, если ещё нет layout
    QVBoxLayout* containerLayout = qobject_cast<QVBoxLayout*>(ui->mainContainer->layout());
    if (!containerLayout) {
        containerLayout = new QVBoxLayout(ui->mainContainer);
        ui->mainContainer->setLayout(containerLayout);
    }

    containerLayout->addWidget(menuScrollArea);
    menuScrollArea->show();
}


void MainWindow::on_addProductButton_clicked()
{
    emit add_product();  // Отправляем сигнал для открытия окна добавления продукта
}


void MainWindow::handleProductAdded(QString name, int proteins, int fats, int carbs, int weight, int cost, int type)
{
    QByteArray response = ::add_product(id, name, proteins, fats, carbs, weight, cost, type);
    qDebug() << "Response from server:" << response;

    if (response.contains("success")) {
        QMessageBox::information(this, "Успех", "Продукт успешно добавлен!");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить продукт: " + response);
    }
}


menuCard* MainWindow::generateMenuCardForDay(const QString& dayName, const QJsonArray& productArray, QWidget* parent, int index) {
    // Распределяем продукты по типам
    QMap<int, QList<QJsonObject>> productsByType;
    for (const QJsonValue& value : productArray) {
        QJsonObject product = value.toObject();
        int type = product["type"].toInt();
        productsByType[type].append(product);
    }

    QStringList selectedProducts;
    QVector<int> pfc = {0, 0, 0}; // Белки, Жиры, Углеводы
    int totalCalories = 0;
    int totalWeight = 0;
    int totalPrice = 0;

    int productsForDay = qMin(3 + QRandomGenerator::global()->bounded(3), productArray.size());

    for (int i = 0; i < productsForDay && !productsByType.isEmpty(); ++i) {
        QList<int> types = productsByType.keys();
        if (types.isEmpty()) break;

        int selectedType = types[QRandomGenerator::global()->bounded(types.size())];
        QList<QJsonObject>& products = productsByType[selectedType];
        if (products.isEmpty()) {
            productsByType.remove(selectedType);
            --i;
            continue;
        }

        QJsonObject selectedProduct = products.takeAt(QRandomGenerator::global()->bounded(products.size()));
        if (products.isEmpty()) {
            productsByType.remove(selectedType);
        }

        selectedProducts.append(selectedProduct["name"].toString());

        pfc[0] += selectedProduct["proteins"].toInt();
        pfc[1] += selectedProduct["fatness"].toInt();
        pfc[2] += selectedProduct["carbs"].toInt();

        int weight = selectedProduct["weight"].toInt();
        int price = selectedProduct["cost"].toInt();
        totalWeight += weight;
        totalPrice += price;

        totalCalories += selectedProduct["proteins"].toInt() * 4 +
                         selectedProduct["fatness"].toInt() * 9 +
                         selectedProduct["carbs"].toInt() * 4;
    }

    return new menuCard(dayName, selectedProducts, totalCalories, pfc, totalWeight, totalPrice, parent, index);
}



void MainWindow::updateMenuCard(int cardIndex) {
    QByteArray productsJson = get_products(id);
    QJsonDocument doc = QJsonDocument::fromJson(productsJson);
    if (!doc.isArray()) return;

    QJsonArray productArray = doc.array();

    QWidget* container = ui->mainContainer->findChild<QScrollArea*>("menuScrollArea") ?
                             ui->mainContainer->findChild<QScrollArea*>("menuScrollArea")->widget() : nullptr;

    if (!container) return;

    QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(container->layout());
    if (!layout || layout->count() <= cardIndex) return;

    // Обновляем карточку с нужным индексом
    QWidget* oldCard = layout->itemAt(cardIndex)->widget();
    if (oldCard) {
        oldCard->hide();
        layout->removeWidget(oldCard);
        oldCard->deleteLater();
    }

    // Получаем имя дня для карточки с этим индексом
    const QStringList days = {"ПОНЕДЕЛЬНИК", "ВТОРНИК", "СРЕДА", "ЧЕТВЕРГ", "ПЯТНИЦА", "СУББОТА", "ВОСКРЕСЕНЬЕ"};
    QString dayName = (cardIndex >= 0 && cardIndex < days.size()) ? days[cardIndex] : "ДЕНЬ";

    menuCard* newCard = generateMenuCardForDay(dayName, productArray, container, cardIndex);

    connect(newCard, &menuCard::buttonClicked, this, &MainWindow::updateMenuCard);


    newCard->setFixedHeight(450);
    layout->insertWidget(cardIndex, newCard);
}


void MainWindow::on_exitButton_clicked()
{
    // Получаем путь к исполняемому файлу и аргументы
    QString program = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    arguments.removeFirst(); // Удаляем первый аргумент (путь к программе)

    // Запускаем новый экземпляр приложения
    QProcess::startDetached(program, arguments);

    // Закрываем текущее приложение
    QApplication::quit();
}

