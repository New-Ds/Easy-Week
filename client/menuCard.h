#ifndef MENUCARD_H
#define MENUCARD_H

#include <QWidget>

namespace Ui {
class menuCard;
}

class menuCard : public QWidget
{
    Q_OBJECT

public:
    explicit menuCard(QString day, QStringList products, int calories, QVector<int>& pfc, int weight, int price, QWidget *parent = nullptr);
    ~menuCard();

private:
    Ui::menuCard *ui;
};

#endif // MENUCARD_H
