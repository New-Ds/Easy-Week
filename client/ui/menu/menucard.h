#ifndef MENUCARD_H
#define MENUCARD_H

#include <QWidget>

namespace Ui {
class menuCard;
}

/**
 * @brief Карточка меню на один день
 */
class MenuCard : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор карточки меню
     * @param day День недели
     * @param products Список продуктов
     * @param calories Калорийность
     * @param pfc БЖУ (вектор)
     * @param weight Общий вес
     * @param price Общая стоимость
     * @param parent Родительский виджет
     * @param index Индекс карточки
     */
    explicit MenuCard(QString day, QStringList products, int calories, QVector<int>& pfc, int weight, int price, QWidget *parent = nullptr, int index = 0);
    
    /**
     * @brief Деструктор карточки меню
     */
    ~MenuCard();

signals:
    /**
     * @brief Сигнал нажатия кнопки
     * @param cardIndex Индекс карточки
     */
    void buttonClicked(int cardIndex);
    
private slots:
    /**
     * @brief Обработка нажатия кнопки обновления
     */
    void on_updateButton_clicked();

    /**
     * @brief Обработка нажатия кнопки добавления в избранное
     */
    void on_favoriteButton_clicked();

private:
    Ui::menuCard *ui;
    MenuCard* card;
    int index;
};

#endif // MENUCARD_H