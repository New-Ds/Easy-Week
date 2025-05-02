#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
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

    get_products(this->email);

    QWidget* container = ui->productsContainer;

    // Проверяем и создаем grid layout
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(container->layout());
    if (!gridLayout) {
        gridLayout = new QGridLayout(container);
        container->setLayout(gridLayout);
    }

    // Очищаем старые карточки (если нужно обновлять каждый раз)
    QLayoutItem* item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    // Добавляем карточки по 3 в ряд
    QStringList names = {"Яблоко", "Банан", "Груша", "Ананас", "Апельсин"};
    QList<int> prices = {100, 80, 120, 150, 90};

    const int columns = 3;

    for (int i = 0; i < names.size(); ++i) {
        int row = i / columns;
        int col = i % columns;

        productCard* card = new productCard(names[i], prices[i], container);
        gridLayout->addWidget(card, row, col);
    }

    container->setVisible(true);
}

