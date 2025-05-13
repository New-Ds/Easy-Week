#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QStringList>

/**
 * @brief Разрушитель Singleton для корректного удаления ClientSingleton.
 */
class ClientSingletonDestroyer {
private:
    ClientSingleton* p_instance;  /**< Указатель на экземпляр ClientSingleton */
public:
    /**
     * @brief Деструктор. Удаляет экземпляр ClientSingleton.
     */
    ~ClientSingletonDestroyer();

    /**
     * @brief Инициализирует указатель на Singleton.
     * @param p Указатель на экземпляр ClientSingleton.
     */
    void initialize(ClientSingleton* p);
};


/**
 * @brief Сетевой клиент, реализующий паттерн Singleton.
 *
 * Используется для подключения к серверу, отправки и получения данных.
 */
class ClientSingleton : public QObject {
    Q_OBJECT

private:
    static ClientSingleton* p_instance;          /**< Указатель на экземпляр Singleton */
    static ClientSingletonDestroyer destroyer;   /**< Объект-разрушитель */
    QTcpSocket* socket;                          /**< Сокет для соединения с сервером */

protected:
    /**
     * @brief Конструктор по умолчанию. Устанавливает соединение с сервером.
     */
    ClientSingleton();

    /**
     * @brief Деструктор. Закрывает соединение с сервером.
     */
    ~ClientSingleton();

    ClientSingleton(const ClientSingleton&) = delete;             /**< Запрещено копирование */
    ClientSingleton& operator=(const ClientSingleton&) = delete;  /**< Запрещено присваивание */

    friend class ClientSingletonDestroyer;

public:
    /**
     * @brief Получить экземпляр Singleton.
     * @return Ссылка на экземпляр ClientSingleton.
     */
    static ClientSingleton& getInstance();

    /**
     * @brief Отправляет сообщение серверу.
     * @param list Список строк с данными для отправки.
     * @return Ответ от сервера в виде QByteArray.
     */
    QByteArray send_msg(QStringList list);

public slots:
    /**
     * @brief Слот вызывается при успешном соединении с сервером.
     */
    void slot_connected();

    /**
     * @brief Слот вызывается при получении данных от сервера.
     */
    void slot_readyRead();
};

#endif // SINGLETON_H
