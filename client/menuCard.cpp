#include "menuCard.h"
#include "ui_menuCard.h"

menuCard::menuCard(QString day, QStringList products, int calories, QVector<int>& pfc, int weight, int price, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menuCard)
{
    ui->setupUi(this);

    // Устанавливаем день недели
    ui->dayLabel->setText(day.toUpper());

    // Добавляем продукты в меню
    for(const QString& product : products) {
        QLabel* productLabel = new QLabel(product, this);
        productLabel->setStyleSheet("font-size: 14px; font-weight: bold; margin: 2px;");
        productLabel->setWordWrap(true);
        productLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->menuVerticalLayout->addWidget(productLabel);
    }

    // Добавляем растягивающийся элемент в конец меню
    ui->menuVerticalLayout->addStretch();

    // Добавляем параметры
    QLabel* caloriesLabel = new QLabel(QString("Калории: %1 ккал").arg(calories), this);
    QLabel* pfcLabel = new QLabel(QString("БЖУ: %1/%2/%3 г").arg(pfc[0]).arg(pfc[1]).arg(pfc[2]), this);
    QLabel* weightLabel = new QLabel(QString("Вес: %1 г").arg(weight), this);
    QLabel* priceLabel = new QLabel(QString("Цена: %1 ₽").arg(price), this);

    // Настройка стилей для параметров
    QString paramStyle = "font-size: 14px; color: black; font-weight: bold; margin: 2px;";
    caloriesLabel->setStyleSheet(paramStyle);
    pfcLabel->setStyleSheet(paramStyle);
    weightLabel->setStyleSheet(paramStyle);
    priceLabel->setStyleSheet(paramStyle);

    // Добавление параметров в layout
    ui->paramsVerticalLayout->addWidget(caloriesLabel);
    ui->paramsVerticalLayout->addWidget(pfcLabel);
    ui->paramsVerticalLayout->addWidget(weightLabel);
    ui->paramsVerticalLayout->addWidget(priceLabel);

    // Добавляем растягивающийся элемент в конец параметров
    ui->paramsVerticalLayout->addStretch();
}

menuCard::~menuCard()
{
    delete ui;
}
