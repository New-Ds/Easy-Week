#include "ProductCard.h"
#include <QVBoxLayout>
#include <QLabel>

productCard::productCard(QString name, int price, QWidget *parent)
    : QWidget(parent)
{

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Название: " + name));
    layout->addWidget(new QLabel("Цена: " + QString::number(price) + " руб"));
    layout->addWidget(new QLabel("Тип: " + QString::number(price) + " руб"));
    layout->addWidget(new QLabel("Белки: " + QString::number(price) + " руб"));
    layout->addWidget(new QLabel("Жиры: " + QString::number(price) + " руб"));
    layout->addWidget(new QLabel("Углеводы: " + QString::number(price) + " руб"));
    setStyleSheet("QWidget { border: 2px solid gray; border-radius: 8px; padding: 10px; }");
}
