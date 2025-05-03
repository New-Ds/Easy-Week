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

    // Получаем строку с продуктами
    QString productsString = get_products(id);

    qDebug() << "Строка всех продуктов: " << productsString;

    // Разбиваем строку на отдельные продукты (разделены запятыми или другим разделителем?)
    // Предполагаю, что продукты разделены запятыми, как в вашем примере mockDatabase
    QStringList productList = productsString.split("\r\n", Qt::SkipEmptyParts);

    qDebug() << "Массив продуктов: " << productList;


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

    // Очистка предыдущих карточек
    QLayoutItem* child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget();
        }
        delete child;
    }

    // Создание карточек
    const int columns = 4;

    for (int i = 0; i < productList.size(); ++i) {
        // Разбиваем данные продукта
        QStringList parts = productList[i].split("_", Qt::SkipEmptyParts);

        if (parts.size() < 5) {
            qDebug() << "Invalid product format:" << productList[i];
            continue;
        }

        // Парсинг данных
        QString productName = parts[0].trimmed();
        int price = parts[1].trimmed().toInt();
        int proteins = parts[2].trimmed().toInt();
        int fatness = parts[3].trimmed().toInt();
        int carbs = parts[4].trimmed().toInt();

        // Создание и размещение карточки
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

