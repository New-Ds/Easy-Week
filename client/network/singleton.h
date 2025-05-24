#ifndef SINGLETON_H
#define SINGLETON_H
#include <QObject>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QStringList>

class NetworkSingleton;

/**
 * @brief Класс-разрушитель для корректного удаления Singleton
 */
class NetworkSingletonDestroyer {
private:
    NetworkSingleton* p_instance;
public:
    ~NetworkSingletonDestroyer();
    void initialize(NetworkSingleton* p);
};

/**
 * @brief Класс для сетевого взаимодействия с сервером
 * 
 * Реализует паттерн Singleton для централизованного управления сетевым соединением
 */
class NetworkSingleton : public QObject
{
    Q_OBJECT
private:
    static NetworkSingleton* p_instance;
    static NetworkSingletonDestroyer destroyer;
    QTcpSocket* socket;
    
protected:
    /**
     * @brief Приватный конструктор для создания соединения с сервером
     */
    NetworkSingleton();
    
    /**
     * @brief Приватный деструктор для закрытия соединения
     */
    ~NetworkSingleton();
    
    NetworkSingleton(const NetworkSingleton&) = delete;
    NetworkSingleton& operator=(const NetworkSingleton&) = delete;

    friend class NetworkSingletonDestroyer;

public:
    /**
     * @brief Получение экземпляра Singleton
     * @return Ссылка на экземпляр NetworkSingleton
     */
    static NetworkSingleton& getInstance();
    
    /**
     * @brief Отправка сообщения серверу
     * @param params Параметры сообщения
     * @return Ответ сервера
     */
    QByteArray sendMessage(QStringList params);
    
public slots:
    /**
     * @brief Обработка установки соединения
     */
    void slotConnected();
    
    /**
     * @brief Обработка получения данных
     */
    void slotReadyRead();
};

#endif // SINGLETON_H