#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QScrollArea>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_show() {
    this->show();
};

//здесь мы забираем авторизовавшегося юзера используя сигнал, который посылаем из окна авторизации
void MainWindow::set_current_user(QString id, QString login, QString password, QString email) {
    this->id = id;
    this->login = login;
    this->password = password;
    this->email = email;
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
    // Получаем строку с продуктами (теперь это JSON)
    QByteArray productsJson = get_products(id);

    qDebug() << "Сырой JSON продуктов: " << productsJson;

    // Парсим JSON
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

    // 1️⃣ Берём контейнер и удаляем старый layout/карточки (как у тебя было)
    QWidget* container = ui->mainContainer;
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(container->layout());

    if (ui->mainContainer->layout()) {
        while (QLayoutItem* item = ui->mainContainer->layout()->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                delete widget; // Удаляем виджет
            }
            delete item; // Удаляем сам item
        }
        delete ui->mainContainer->layout();
    }

    if (!gridLayout) {
        gridLayout = new QGridLayout(container);
        container->setLayout(gridLayout);
    }

    // 2️⃣ Создаём карточки (визуал точно как у тебя)
    const int columns = 4;

    for (int i = 0; i < productArray.size(); ++i) {
        QJsonObject obj = productArray[i].toObject();

        // Извлекаем данные (ключи должны совпадать с сервером)
        QString productName = obj["name"].toString();
        int price = obj["cost"].toInt();
        int proteins = obj["proteins"].toInt();
        int fatness = obj["fatness"].toInt();
        int carbs = obj["carbs"].toInt();

        qDebug() << "Продукт #" << (i + 1)
                 << " Name:" << productName
                 << " Price:" << price
                 << " Proteins:" << proteins
                 << " Fatness:" << fatness
                 << " Carbs:" << carbs;

        // Создание и размещение карточки (визуал не трогаем)
        productCard* card = new productCard(productName, price, proteins, fatness, carbs, container);
        gridLayout->addWidget(card, i / columns, i % columns);
    }

    container->setVisible(true);
}




void MainWindow::on_createMenButton_clicked()
{
    QScrollArea* scrollArea = qobject_cast<QScrollArea*>(ui->mainContainer->findChild<QWidget*>("innerScrollArea"));

    if (!scrollArea) {
        scrollArea = new QScrollArea(ui->mainContainer);
        scrollArea->setObjectName("innerScrollArea");
        scrollArea->setWidgetResizable(false); // Отключаем авто-растягивание
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);


        if (ui->mainContainer->layout()) {
            delete ui->mainContainer->layout();
        }
        ui->mainContainer->setLayout(new QVBoxLayout());
        ui->mainContainer->layout()->addWidget(scrollArea);
    }

    QWidget* cardsContainer = new QWidget();
    QHBoxLayout* cardsLayout = new QHBoxLayout(cardsContainer);
    cardsLayout->setSpacing(10);

    const QStringList days = {"ПОНЕДЕЛЬНИК", "ВТОРНИК", "СРЕДА", "ЧЕТВЕРГ", "ПЯТНИЦА", "СУББОТА", "ВОСКРЕСЕНЬЕ"};

    for (int i = 0; i < 7; i++) {

        QStringList products = {"Курица c рисом", "Овощи", "Квас"};
        QVector<int> pfc = {34, 21, 113};


        menuCard* card = new menuCard(days[i], products, 623, pfc, 500, 219, cardsContainer);

        card->setFixedSize(370, 468);
        cardsLayout->addWidget(card);
    }

    // 4. Настраиваем скролл
    scrollArea->setWidget(cardsContainer);
}

