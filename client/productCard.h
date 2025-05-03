#pragma once
#include <QWidget>


class productCard : public QWidget {
    Q_OBJECT
public:
    explicit productCard(QString name, int price, int proteins, int fatness, int carbs, QWidget *parent = nullptr);
};
