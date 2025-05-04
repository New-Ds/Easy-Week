#include "ProductCard.h"
#include <QVBoxLayout>
#include <QLabel>

productCard::productCard(QString name, int price, int proteins, int fatness, int carbs, QWidget *parent)
    : QWidget(parent)
{
    // Устанавливаем оптимальный размер с минимальными и максимальными ограничениями
    this->setMinimumSize(150, 200);
    this->setMaximumSize(200, 250);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(8);

    // Стили для улучшения читаемости
    QString labelStyle = "QLabel { font-size: 16px; color: white; }";
    QString titleStyle = "QLabel { font-weight: bold; font-size: 18px; color: white; }";
    QString priceStyle = "QLabel { font-weight: bold; font-size: 16px; color: green; }";

    // Название продукта
    QLabel* nameLabel = new QLabel(name);
    nameLabel->setStyleSheet(titleStyle);
    nameLabel->setWordWrap(true);
    nameLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(nameLabel);

    // Цена
    QLabel* priceLabel = new QLabel("Цена: " + QString::number(price) + "₽");
    priceLabel->setStyleSheet(priceStyle);
    priceLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(priceLabel);

    // Разделительная линия
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("color: #e0e0e0;");
    mainLayout->addWidget(line);

    // Панель с пищевой ценностью
    QWidget* nutritionPanel = new QWidget();
    QGridLayout* nutritionLayout = new QGridLayout(nutritionPanel);
    nutritionLayout->setContentsMargins(5, 5, 5, 5);
    nutritionLayout->setHorizontalSpacing(10);
    nutritionLayout->setVerticalSpacing(5);

    // Заголовки и значения БЖУ
    QLabel* proteinTitle = new QLabel("Белки:");
    QLabel* proteinValue = new QLabel(QString::number(proteins) + " г");
    QLabel* fatTitle = new QLabel("Жиры:");
    QLabel* fatValue = new QLabel(QString::number(fatness) + " г");
    QLabel* carbsTitle = new QLabel("Углеводы:");
    QLabel* carbsValue = new QLabel(QString::number(carbs) + " г");

    // Применяем стили
    proteinTitle->setStyleSheet(labelStyle);
    proteinValue->setStyleSheet(labelStyle);
    fatTitle->setStyleSheet(labelStyle);
    fatValue->setStyleSheet(labelStyle);
    carbsTitle->setStyleSheet(labelStyle);
    carbsValue->setStyleSheet(labelStyle);

    // Добавляем в layout
    nutritionLayout->addWidget(proteinTitle, 0, 0);
    nutritionLayout->addWidget(proteinValue, 0, 1);
    nutritionLayout->addWidget(fatTitle, 1, 0);
    nutritionLayout->addWidget(fatValue, 1, 1);
    nutritionLayout->addWidget(carbsTitle, 2, 0);
    nutritionLayout->addWidget(carbsValue, 2, 1);

    mainLayout->addWidget(nutritionPanel);
}
