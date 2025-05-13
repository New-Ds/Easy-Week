#pragma once
#include <QWidget>

/**
 * @brief Виджет карточки продукта.
 *
 * Отображает информацию о продукте: название, цену и пищевую ценность (белки, жиры, углеводы).
 */
class productCard : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор карточки продукта.
     * @param name Название продукта.
     * @param price Стоимость продукта.
     * @param proteins Количество белков.
     * @param fatness Количество жиров.
     * @param carbs Количество углеводов.
     * @param parent Родительский виджет.
     */
    explicit productCard(QString name, int price, int proteins, int fatness, int carbs, QWidget *parent = nullptr);
};
