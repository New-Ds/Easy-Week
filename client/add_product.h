#ifndef ADD_PRODUCT_H
#define ADD_PRODUCT_H

#include <QWidget>

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

public slots:
    void slot_show();

signals:
    void add_product();
};

#endif // ADD_PRODUCT_H
