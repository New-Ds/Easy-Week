#include "menuCard.h"
#include "ui_menuCard.h"
 //pfc это БЖУ






 menuCard::menuCard(QString day, QStringList products, int calories, QVector<int>& pfc, int weight, int price, QWidget *parent)
     : QWidget(parent)
     , ui(new Ui::menuCard)
 {
     ui->setupUi(this);


     ui->dayLabel->setText(day);


     // 1. Добавляем продукты в menuVerticalLayout
     for(const QString& product : products) {
         QLabel* productLabel = new QLabel(product, this);
         productLabel->setStyleSheet("font-size: 16px; font-weight: bold");
         ui->menuVerticalLayout->addWidget(productLabel);
     }

     // 2. Добавляем параметры в paramsVerticalLayout
     QLabel* caloriesLabel = new QLabel(QString("Калории: %1").arg(calories), this);
     QLabel* pfcLabel = new QLabel(QString("БЖУ: %1-%2-%3").arg(pfc[0]).arg(pfc[1]).arg(pfc[2]), this);
     QLabel* weightLabel = new QLabel(QString("Вес: %1 г").arg(weight), this);
     QLabel* priceLabel = new QLabel(QString("Цена: %1 руб.").arg(price), this);

     // Настройка стилей для параметров
     QString paramStyle = "font-size: 14px; color: black; font-weight: bold";
     caloriesLabel->setStyleSheet(paramStyle);
     pfcLabel->setStyleSheet(paramStyle);
     weightLabel->setStyleSheet(paramStyle);
     priceLabel->setStyleSheet(paramStyle);

     // Добавление в layout
     ui->paramsVerticalLayout->addWidget(caloriesLabel);
     ui->paramsVerticalLayout->addWidget(pfcLabel);
     ui->paramsVerticalLayout->addWidget(weightLabel);
     ui->paramsVerticalLayout->addWidget(priceLabel);

     // Добавляем растягивающийся элемент в конец
     ui->menuVerticalLayout->addStretch();
     ui->paramsVerticalLayout->addStretch();
 }

menuCard::~menuCard()
{
    delete ui;
}
