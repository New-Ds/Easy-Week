#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QByteArray>

// Предварительные объявления сервисов
class AuthService;
class ProductService;
class RationService;
class StatsService;

/**
 * @brief Класс для обработки запросов от клиентов
 */
class RequestHandler : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор обработчика запросов
     * @param parent Родительский объект
     */
    explicit RequestHandler(QObject *parent = nullptr);
    
    /**
     * @brief Деструктор обработчика запросов
     */
    ~RequestHandler();

    /**
     * @brief Обработка запроса от клиента
     * @param data Данные запроса
     * @param socketDescriptor Дескриптор сокета клиента
     * @return Ответ на запрос
     */
    QByteArray handleRequest(const QByteArray& data, int socketDescriptor);

private:
    AuthService* m_authService;         ///< Сервис аутентификации
    ProductService* m_productService;   ///< Сервис работы с продуктами
    RationService* m_rationService;     ///< Сервис работы с рационами
    StatsService* m_statsService;       ///< Сервис статистики
};

#endif // REQUESTHANDLER_H