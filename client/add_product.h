#ifndef ADD_PRODUCT_H
#define ADD_PRODUCT_H

#include <QWidget>
#include <QMessageBox>
namespace Ui {
class AddProductWindow;
}

class AddProductWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AddProductWindow(QWidget *parent = nullptr);
    ~AddProductWindow();


private:
    Ui::AddProductWindow *ui;

signals:
    void productAdded(QString name, int proteins, int fats, int carbs, int weight, int cost, int type);


public slots:
    void clear();
    void slot_show();

private slots:
    void on_add_clicked();
};

#endif // ADD_PRODUCT_H
