#ifndef MENUCARD_H
#define MENUCARD_H

#include <QWidget>

namespace Ui {
class menuCard;
}

/**
 * @brief Виджет отображения информации о рационе питания.
 * 
 * Показывает данные за определённый день: список продуктов, калорийность,
 * содержание БЖУ, вес и цену.
 */
class menuCard : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор виджета menuCard.
     * @param day День недели или дата.
     * @param products Список продуктов в рационе.
     * @param calories Общее количество калорий.
     * @param pfc Вектор, содержащий значения белков, жиров и углеводов.
     * @param weight Общий вес рациона.
     * @param price Общая стоимость рациона.
     * @param parent Родительский виджет.
     */
    explicit menuCard(QString day, QStringList products, int calories, QVector<int>& pfc, int weight, int price, QWidget *parent = nullptr);

    /**
     * @brief Деструктор.
     */
    ~menuCard();

private:
    Ui::menuCard *ui; ///< UI-компоненты, сгенерированные Qt Designer.
};

#endif // MENUCARD_H
