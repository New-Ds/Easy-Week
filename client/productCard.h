#pragma once
#include <QWidget>


class productCard : public QWidget {
    Q_OBJECT
public:
    explicit productCard(QString name, int price, QWidget *parent = nullptr);
};
