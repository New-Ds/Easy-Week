#ifndef FUNC2SERV_H
#define FUNC2SERV_H

#include <QByteArray>

QByteArray parsing(QString input);
QByteArray auth(QStringList );
QByteArray reg(/*QStringList*/);
QByteArray get_stat(/*QStringList*/);
QByteArray check_task(/*QStringList*/);

#endif // FUNC2SERV_H
