# Unit Tests для EasyWeek

## Описание

Комплексная система unit-тестов для клиентской части приложения EasyWeek, покрывающая все критические компоненты согласно стратегии тестирования.

## Покрытие тест-кейсов

### ТК-001: Регистрация и авторизация пользователей
- ✅ `testUserRegistrationSuccess()` - Успешная регистрация нового пользователя
- ✅ `testUserRegistrationFailure()` - Обработка некорректных данных при регистрации
- ✅ `testUserAuthenticationSuccess()` - Успешная авторизация зарегистрированного пользователя
- ✅ `testUserAuthenticationFailure()` - Обработка неверных данных авторизации
- ✅ `testAuthRegWindowIntegration()` - Интеграция UI компонентов авторизации

### ТК-002: Добавление продуктов с валидацией
- ✅ `testAddProductWithValidData()` - Добавление продукта с корректными данными
- ✅ `testAddProductWithInvalidData()` - Обработка некорректных данных продукта
- ✅ `testProductFieldValidation()` - Валидация полей при добавлении продукта
- ✅ `testAddProductWindowIntegration()` - Интеграция UI компонента добавления продукта

### ТК-003: Генерация меню с расчетом БЖУ
- ✅ `testMenuGenerationCorrectness()` - Корректность генерации меню на неделю
- ✅ `testNutritionalCalculation()` - Расчет БЖУ и калорийности
- ✅ `testProductDistribution()` - Распределение продуктов по дням недели
- ✅ `testMenuGenerationWithLimitedProducts()` - Генерация с ограниченным набором продуктов

### ТК-004: Обновление карточек меню
- ✅ `testMenuCardUpdate()` - Обновление отдельной карточки меню
- ✅ `testMenuCardUpdateIsolation()` - Изоляция обновления карточек
- ✅ `testMenuCardUpdateWithModifiedProducts()` - Обновление с измененным списком продуктов

### ТК-005: Экспорт меню в файл
- ✅ `testMenuExportToFile()` - Экспорт меню в текстовый файл
- ✅ `testExportedFileStructure()` - Корректность структуры экспортированного файла
- ✅ `testExportWithDifferentProductSets()` - Экспорт с различными наборами продуктов
- ✅ `testExportErrorHandling()` - Обработка ошибок при экспорте

## Запуск тестов

### Подготовка окружения

1. **Убедитесь, что установлены зависимости:**
   ```bash
   # Ubuntu/Debian
   sudo apt-get install qt5-default qtbase5-dev qttools5-dev
   
   # CentOS/RHEL
   sudo yum install qt5-qtbase-devel qt5-qttools-devel
   
   # macOS
   brew install qt5
   ```

2. **Структура проекта должна быть:**
   ```
   EasyWeek/
   ├── client/                  # Исходный код клиента
   ├── server/                  # Исходный код сервера
   └── tests/                   # Папка с тестами
       ├── easyweekunittests.h
       ├── easyweekunittests.cpp
       ├── main_test.cpp
       ├── EasyWeekTests.pro
       └── README_Tests.md
   ```

### Сборка и запуск

#### Метод 1: Через Qt Creator
1. Откройте файл `EasyWeekTests.pro` в Qt Creator
2. Настройте kit для сборки
3. Соберите проект (Build → Build Project)
4. Запустите тесты (Build → Run Tests)

#### Метод 2: Через командную строку
```bash
# Переходим в папку с тестами
cd tests/

# Генерируем Makefile
qmake EasyWeekTests.pro

# Собираем проект
make

# Запускаем тесты
./EasyWeekTests

# Или с детальным выводом
./EasyWeekTests -v2
```

#### Метод 3: Запуск отдельных тестов
```bash
# Запуск только тестов авторизации (ТК-001)
./EasyWeekTests testUserRegistrationSuccess testUserAuthenticationSuccess

# Запуск с XML отчетом
./EasyWeekTests -xml -o test_results.xml

# Запуск с CSV отчетом
./EasyWeekTests -csv -o test_results.csv
```

## Использование с базой данных администратора

### Настройка тестового окружения

Тесты могут работать **БЕЗ MOC файлов** и используют следующие подходы:

1. **Симуляция серверных ответов** - вместо реальных сетевых запросов
2. **Тестовые данные администратора**:
   ```cpp
   // В тестах используется встроенный администратор
   Email: admin@new-devs.ru
   Password: admin
   ```

3. **Изолированное тестирование компонентов**:
   - UI тестируется отдельно от сетевого слоя
   - Бизнес-логика тестируется с mock данными
   - Валидация работает независимо от БД

### Конфигурация для работы с реальной БД

Если нужно тестировать с реальной базой данных:

1. **Запустите сервер EasyWeek**
2. **Убедитесь, что БД содержит тестовые данные**
3. **Измените режим тестирования**:
   ```cpp
   // В файле easyweekunittests.cpp
   #define USE_REAL_DATABASE true
   ```

## Интерпретация результатов

### Успешное выполнение
```
=================================================
     ✅ ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!
     Система готова к использованию.
=================================================
PASS   : EasyWeekUnitTests::testUserRegistrationSuccess()
PASS   : EasyWeekUnitTests::testAddProductWithValidData()
PASS   : EasyWeekUnitTests::testMenuGenerationCorrectness()
PASS   : EasyWeekUnitTests::testMenuCardUpdate()
PASS   : EasyWeekUnitTests::testMenuExportToFile()
...
Totals: 20 passed, 0 failed, 0 skipped
```

### Обнаружение ошибок
```
=================================================
     ❌ ОБНАРУЖЕНЫ ОШИБКИ В ТЕСТАХ!
     Требуется исправление перед релизом.
=================================================
FAIL!  : EasyWeekUnitTests::testUserRegistrationSuccess()
   Actual   (registrationResult): false
   Expected (true): true
   Loc: [easyweekunittests.cpp(156)]
```

## Расширение тестов

### Добавление новых тест-кейсов

1. **Добавьте объявление в easyweekunittests.h:**
   ```cpp
   private slots:
       void testNewFeature();
   ```

2. **Реализуйте тест в easyweekunittests.cpp:**
   ```cpp
   void EasyWeekUnitTests::testNewFeature()
   {
       qDebug() << "ТК-006: Новый тест";
       
       // Ваша логика тестирования
       QVERIFY2(condition, "Описание ошибки");
       
       qDebug() << "ТК-006: ПРОЙДЕН";
   }
   ```

### Создание mock объектов
```cpp
class MockNetworkSingleton : public NetworkSingleton {
public:
    QByteArray sendMessage(QStringList params) override {
        // Возвращаем предопределенный ответ
        return simulateServerResponse("success", QJsonValue());
    }
};
```

## Continuous Integration

### GitHub Actions пример
```yaml
name: EasyWeek Tests
on: [push, pull_request]
jobs:
  test:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v2
    - name: Install Qt
      run: sudo apt-get install qt5-default qtbase5-dev
    - name: Build tests
      run: |
        cd tests
        qmake EasyWeekTests.pro
        make
    - name: Run tests
      run: cd tests && ./EasyWeekTests -xml -o test_results.xml
    - name: Upload results
      uses: actions/upload-artifact@v2
      with:
        name: test-results
        path: tests/test_results.xml
```

## Troubleshooting

### Частые проблемы

1. **Ошибка компиляции "moc файлы не найдены"**
   ```bash
   # Решение: Пересоберите проект
   make clean && qmake && make
   ```

2. **Тесты падают с ошибкой сегментации**
   ```bash
   # Запустите с отладчиком
   gdb ./EasyWeekTests
   (gdb) run
   (gdb) bt  # при падении посмотрите стек
   ```

3. **UI тесты не работают в headless режиме**
   ```bash
   # Используйте виртуальный дисплей
   export QT_QPA_PLATFORM=offscreen
   ./EasyWeekTests
   ```

4. **Проблемы с путями к файлам**
   ```bash
   # Проверьте рабочую директорию
   pwd
   # Запустите из корректной папки
   cd tests && ./EasyWeekTests
   ```

## Контакты

При возникновении вопросов по тестированию обращайтесь к документации Qt Test Framework или команде разработки EasyWeek.