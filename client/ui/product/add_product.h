#ifndef ADD_PRODUCT_H
#define ADD_PRODUCT_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class AddProductWindow;
}

/**
 * @brief Окно добавления продукта
 */
class AddProductWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор окна добавления продукта
     * @param parent Родительский виджет
     */
    explicit AddProductWindow(QWidget *parent = nullptr);
    
    /**
     * @brief Деструктор окна добавления продукта
     */
    ~AddProductWindow();

private:
    Ui::AddProductWindow *ui;

signals:
    /**
     * @brief Сигнал о добавлении продукта
     * @param name Название продукта
     * @param proteins Содержание белков
     * @param fats Содержание жиров
     * @param carbs Содержание углеводов
     * @param weight Вес порции
     * @param cost Стоимость
     * @param type Тип продукта
     */
    void productAdded(QString name, int proteins, int fats, int carbs, int weight, int cost, int type);

public slots:
    /**
     * @brief Очистка полей ввода
     */
    void clear();
    
    /**
     * @brief Отображение окна
     */
    void slot_show();

private slots:
    /**
     * @brief Обработка нажатия кнопки добавления
     */
    void on_add_clicked();
    
    /**
     * @brief Обработка нажатия кнопки отмены
     */
    void on_cancle_clicked();
};

#endif // ADD_PRODUCT_H