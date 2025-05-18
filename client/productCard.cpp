#include "ProductCard.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

productCard::productCard(QString name, int price, int proteins, int fatness, int carbs, QWidget *parent)
    : QWidget(parent)
{
    // Устанавливаем оптимальный размер с минимальными и максимальными ограничениями
    this->setMinimumSize(150, 200);
    this->setMaximumSize(200, 350);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Создаем основной контейнер с фоном #2D3E50
    QFrame* cardFrame = new QFrame(this);
    cardFrame->setStyleSheet("background-color: #2D3E50; border-radius: 8px;");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(cardFrame);

    QVBoxLayout* cardLayout = new QVBoxLayout(cardFrame);
    cardLayout->setContentsMargins(10, 10, 10, 10);
    cardLayout->setSpacing(8);

    // Стили для элементов с учетом темного фона
    QString labelStyle = "QLabel { font-size: 16px; color: white; }";
    QString titleStyle = "QLabel { font-weight: bold; font-size: 18px; color: white; }";
    QString priceStyle = "QLabel { font-weight: bold; font-size: 16px; color: #4AFF80; }";

    // Название продукта
    QLabel* nameLabel = new QLabel(name);
    nameLabel->setStyleSheet(titleStyle);
    nameLabel->setWordWrap(true);
    nameLabel->setAlignment(Qt::AlignCenter);
    cardLayout->addWidget(nameLabel);

    // Цена
    QLabel* priceLabel = new QLabel("Цена: " + QString::number(price) + "₽");
    priceLabel->setStyleSheet(priceStyle);
    priceLabel->setAlignment(Qt::AlignCenter);
    cardLayout->addWidget(priceLabel);

    // Разделительная линия
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("background-color: rgba(255, 255, 255, 0.3);");
    cardLayout->addWidget(line);

    // Панель с пищевой ценностью
    QWidget* nutritionPanel = new QWidget();
    nutritionPanel->setStyleSheet("background-color: transparent;");
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

    cardLayout->addWidget(nutritionPanel);
}
