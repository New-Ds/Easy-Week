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
    explicit menuCard(QString day, QStringList products, int calories, QVector<int>& pfc, int weight, int price, QWidget *parent = nullptr, int index = 0);
    ~menuCard();


signals:
    void buttonClicked(int cardIndex);
private slots:

    void on_updateButton_clicked();

    void on_favoriteButton_clicked();

private:
    Ui::menuCard *ui;
    menuCard * card;
    int index;
};

#endif // MENUCARD_H
