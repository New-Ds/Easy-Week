#ifndef ADD_PRODUCT_H
#define ADD_PRODUCT_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class AddProductWindow;
}

/**
 * @brief Класс окна для добавления нового продукта.
 *
 * Этот класс предоставляет пользовательский интерфейс для ввода информации
 * о продукте (название, белки, жиры, углеводы, вес, цена, тип) и отправки этих данных.
 */
class AddProductWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор окна добавления продукта.
     * @param parent Родительский виджет.
     */
    explicit AddProductWindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор.
     */
    ~AddProductWindow();

signals:
    /**
     * @brief Сигнал, испускаемый после успешного добавления продукта.
     * @param name Название продукта.
     * @param proteins Количество белков.
     * @param fats Количество жиров.
     * @param carbs Количество углеводов.
     * @param weight Вес продукта.
     * @param cost Стоимость продукта.
     * @param type Тип продукта.
     */
    void productAdded(QString name, int proteins, int fats, int carbs, int weight, int cost, int type);

public slots:
    /**
     * @brief Очистка всех полей ввода.
     */
    void clear();

    /**
     * @brief Отображение окна добавления продукта.
     */
    void slot_show();

private:
    Ui::AddProductWindow *ui; /**< Указатель на интерфейс UI. */

private slots:
    /**
     * @brief Обработчик нажатия кнопки добавления продукта.
     */
    void on_add_clicked();
};

#endif // ADD_PRODUCT_H
