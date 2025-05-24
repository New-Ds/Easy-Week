#pragma once
#include <QWidget>

/**
 * @brief Карточка продукта
 */
class ProductCard : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Конструктор карточки продукта
     * @param name Название продукта
     * @param price Цена
     * @param proteins Содержание белков
     * @param fatness Содержание жиров
     * @param carbs Содержание углеводов
     * @param parent Родительский виджет
     */
    explicit ProductCard(QString name, int price, int proteins, int fatness, int carbs, QWidget *parent = nullptr);
};