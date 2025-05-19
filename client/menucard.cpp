#include "menuCard.h"
#include "ui_menuCard.h"
#include <QMessageBox>


 menuCard::menuCard(QString day, QStringList products, int calories, QVector<int>& pfc, int weight, int price, QWidget *parent, int index)
     : QWidget(parent)
     , ui(new Ui::menuCard)
     , index(index)
 {
     ui->setupUi(this);


     ui->dayLabel->setText(day);

     // В конструкторе menuCard::menuCard после вызова ui->setupUi(this)
     ui->favoriteButton->setIcon(QIcon(":/images/images/star.png"));
     ui->updateButton->setIcon(QIcon(":/images/images/upde.png"));

     // Установка размера иконок для лучшей видимости
     ui->favoriteButton->setIconSize(QSize(30, 30));
     ui->updateButton->setIconSize(QSize(30, 30));


     // 1. Добавляем продукты в menuVerticalLayout
     for(const QString& product : products) {
         QLabel* productLabel = new QLabel(product, this);
         productLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin: 0; padding: 0;");
         ui->menuVerticalLayout->addWidget(productLabel);
         ui->menuVerticalLayout->setSpacing(3);
     }

     // 2. Добавляем параметры в paramsVerticalLayout
     QLabel* caloriesLabel = new QLabel(QString("Калории: %1").arg(calories), this);
     QLabel* pfcLabel = new QLabel(QString("БЖУ: %1-%2-%3").arg(pfc[0]).arg(pfc[1]).arg(pfc[2]), this);
     QLabel* weightLabel = new QLabel(QString("Вес: %1 г").arg(weight), this);
     QLabel* priceLabel = new QLabel(QString("Цена: %1 руб.").arg(price), this);

     // Настройка стилей для параметров
     QString paramStyle = "font-size: 14px; color: black; font-weight: bold; margin: 0; padding: 0";
     caloriesLabel->setStyleSheet(paramStyle);
     pfcLabel->setStyleSheet(paramStyle);
     weightLabel->setStyleSheet(paramStyle);
     priceLabel->setStyleSheet(paramStyle);

     // Добавление в layout
     ui->paramsVerticalLayout->addStretch(1);
     ui->paramsVerticalLayout->addWidget(caloriesLabel);
     ui->paramsVerticalLayout->addStretch(1);
     ui->paramsVerticalLayout->addWidget(pfcLabel);
     ui->paramsVerticalLayout->addStretch(1);
     ui->paramsVerticalLayout->addWidget(weightLabel);
     ui->paramsVerticalLayout->addStretch(1);
     ui->paramsVerticalLayout->addWidget(priceLabel);
     ui->paramsVerticalLayout->addStretch(1);

     // Добавляем растягивающийся элемент в конец
     ui->menuVerticalLayout->addStretch();
     // ui->paramsVerticalLayout->addStretch();
 }

menuCard::~menuCard()
{
    delete ui;
}

void menuCard::on_updateButton_clicked()
{
    qDebug() << "upd buttonb clicked";
    emit buttonClicked(index);
}


void menuCard::on_favoriteButton_clicked()
{
    // это лохотрон, не работает на самом деле ахахахахахахахах
    QMessageBox msgBox;
    msgBox.setWindowTitle("Успех");
    msgBox.setText("Рацион добавлен в избранное!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setStyleSheet("QPushButton { background: #4CAF50; color: white; }");
    msgBox.exec();
}

