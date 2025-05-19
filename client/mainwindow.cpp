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



void MainWindow::on_tableUsersButton_clicked()
{
    QByteArray users = get_all_users();
    qDebug() << users;
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

