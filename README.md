# Вариант №1
Условия задания: разработать инструмент визуализации графа зависимостей для менеджера пакетов. Готовые средства (менеджеры пакетов, библиотеки) для получения зависимостей использовать нельзя.

## Содержание:
- [Этап 1. REPL](#этап-1-минимальный-прототип-с-конфигурацией)
- [Результат 1 этапа](#результат-1-этапа)
- [Вывод для этапа 1](#вывод-для-этапа-1)
- [Код 1 этапа реализованного на языке С++](#код-1-этапа-реализованного-на-языке-с)
## Этап 1. Минимальный прототип с конфигурацией

**Цель**: создать минимальное CLI-приложение и сделать его настраиваемым

### Требования:
1. Источником настраиваемых пользователем параметров являются опции командной строки.
2. К настраиваемым параметрам относятся:

    – Имя анализируемого пакета.
  
    – URL-адрес репозитория или путь к файлу тестового репозитория.

    – Режим работы с тестовым репозиторием.

    – Подстрока для фильтрации пакетов.
  
4. (только для этого этапа) При запуске приложения вывести все параметры,
настраиваемые пользователем, в формате ключ-значение.
5. Реализовать и продемонстрировать обработку ошибок для всех параметров.
6. Результат выполнения этапа сохранить в репозиторий стандартно
оформленным коммитом.

## Доступные параметры:
| Параметр | Короткая версия | Назначение |
|----------|-----------------|------------|
| `--package` | `-p` | Имя анализируемого пакета |
| `--repository` | `-r` | URL репозитория или путь к файлу |
| `--test-mode` | `-t` | Режим тестового репозитория |
| `--filter` | `-f` | Подстрока для фильтрации пакетов |
| `--help` | `-h` | Показать справку |

### Валидация параметров:
- Имя пакета: `[a-z, A-Z, 0-9, -_.]` (только буквы, цифры, дефисы, подчеркивания и точки)
- URL/путь: запрещены последовательности `..` для безопасности
- Test-mode: принимает `true/false/1/0/on/off`
- Обязательные: хотя бы один из `--package` или `--repository`

## Результат 1 этапа
1. Тест справки
```
.\PackageVisualizer.exe --help
```
<img width="912" height="156" alt="image" src="https://github.com/user-attachments/assets/fe03dc09-74c2-4c86-b573-0d1bc4410e53" />

2. Базовая работа
```
.\PackageVisualizer.exe --package "help" --repository "https://help.com"
```
<img width="1101" height="161" alt="image" src="https://github.com/user-attachments/assets/e878dcf9-745f-4557-9ccf-1fdcb6842a1a" />

3. Полный набор параметров
```
.\PackageVisualizer.exe --package "help" --repository "help.org" --test-mode true --filter "help"
```
<img width="1087" height="156" alt="image" src="https://github.com/user-attachments/assets/9e947a8c-43a6-4a47-851a-ffe05a6173d4" />

4. Короткие флаги
```
.\PackageVisualizer.exe -p "help" -r "help.com" -t false -f "help"
```
<img width="1077" height="155" alt="image" src="https://github.com/user-attachments/assets/df89e6d7-4ee3-44e7-b6ef-3b6353f9e5ac" />

5. Только package
```
.\PackageVisualizer.exe --package "help-no"
```
<img width="947" height="134" alt="image" src="https://github.com/user-attachments/assets/41d842f9-540b-4b16-a602-018fbf9b39f5" />

6. Только repository
```
.\PackageVisualizer.exe --repository "https://github.com"
```
<img width="1063" height="134" alt="image" src="https://github.com/user-attachments/assets/588fe562-2c57-4a0a-9507-34ae605e7237" />

7. Локальный путь
```
.\PackageVisualizer.exe --package "PackageVisualizer" --repository "C:\Users\Admin\source\repos\PackageVisualizer"
```
<img width="1102" height="172" alt="image" src="https://github.com/user-attachments/assets/dab1f92c-656c-4d7b-8463-248c0e6102cb" />

8. Разные значения test-mode
```
.\PackageVisualizer.exe --package "help" --repository "ewq" --test-mode on
```
<img width="1075" height="176" alt="image" src="https://github.com/user-attachments/assets/7274ab65-f8ba-4590-ab55-b61906705aa1" />

9. Ошибка - некорректное имя пакета
```
.\PackageVisualizer.exe --package "help@not" --repository "help"
```
<img width="1087" height="93" alt="image" src="https://github.com/user-attachments/assets/67aa94b4-d711-41f3-a105-0426283151e6" />

10. Ошибка - отсутствует значение
```
.\PackageVisualizer.exe --package --repository "help"
```
<img width="1044" height="55" alt="image" src="https://github.com/user-attachments/assets/d2e0a86c-3f8f-416e-8f2d-1e0b30c18adc" />

11. Ошибка - неизвестный параметр
```
.\PackageVisualizer.exe --help-param value
```
<img width="970" height="67" alt="image" src="https://github.com/user-attachments/assets/eca60a6e-99cd-4226-9483-376543b53492" />

12. Ошибка - неверный test-mode
```
.\PackageVisualizer.exe --package "help" --repository "help.com" --test-mode invalid-value
```
<img width="1090" height="106" alt="image" src="https://github.com/user-attachments/assets/64a11fde-866c-45a6-8b63-221201211190" />

### Структура кода:
Config struct - хранение параметров конфигурации

parseArguments() - парсинг и валидация аргументов

isValidPackageName() - валидация имени пакета

isValidRepository() - базовая валидация URL/пути

printConfig() - вывод конфигурации пользователю

### Код 1 этапа реализованного на языке С++
```
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Структура для хранения конфигурации
struct Config {
    string package_name;
    string repository_url;
    bool test_mode = false;
    string filter;
};

// Функция для проверки имени пакета
bool isValidPackageName(const string& name) {
    if (name.empty()) return false;
    for (char c : name) {
        if (!isalnum(c) && c != '-' && c != '_' && c != '.') {
            return false;
        }
    }
    return true;
}

// Функция для проверки URL/пути
bool isValidRepository(const string& repo) {
    if (repo.empty()) return false;
    // Простая проверка - не должен содержать ".." для безопасности
    return repo.find("..") == string::npos;
}

// Функция разбора аргументов
Config parseArguments(int argc, char* argv[]) {
    Config config;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "--package" || arg == "-p") {
            if (i + 1 >= argc) throw runtime_error("Параметр --package требует значения");
            config.package_name = argv[++i];
            if (!isValidPackageName(config.package_name)) {
                throw runtime_error("Недопустимое имя пакета: " + config.package_name);
            }
        }
        else if (arg == "--repository" || arg == "-r") {
            if (i + 1 >= argc) throw runtime_error("Параметр --repository требует значения");
            config.repository_url = argv[++i];
            if (!isValidRepository(config.repository_url)) {
                throw runtime_error("Недопустимый URL репозитория: " + config.repository_url);
            }
        }
        else if (arg == "--test-mode" || arg == "-t") {
            if (i + 1 >= argc) throw runtime_error("Параметр --test-mode требует значения");
            string mode = argv[++i];
            if (mode == "true" || mode == "1" || mode == "on") {
                config.test_mode = true;
            }
            else if (mode == "false" || mode == "0" || mode == "off") {
                config.test_mode = false;
            }
            else {
                throw runtime_error("Недопустимое значение для --test-mode: " + mode);
            }
        }
        else if (arg == "--filter" || arg == "-f") {
            if (i + 1 >= argc) throw runtime_error("Параметр --filter требует значения");
            config.filter = argv[++i];
        }
        else if (arg == "--help" || arg == "-h") {
            cout << "Использование: " << argv[0] << " [ОПЦИИ]\n";
            cout << "Опции:\n";
            cout << "  -p, --package NAME    Имя анализируемого пакета\n";
            cout << "  -r, --repository URL  URL репозитория или путь к файлу\n";
            cout << "  -t, --test-mode MODE  Режим тестового репозитория (true/false)\n";
            cout << "  -f, --filter TEXT     Подстрока для фильтрации пакетов\n";
            cout << "  -h, --help            Показать эту справку\n";
            exit(0);
        }
        else {
            throw runtime_error("Неизвестный параметр: " + arg);
        }
    }

    // Проверка обязательных параметров
    if (config.package_name.empty() && config.repository_url.empty()) {
        throw runtime_error("Должен быть указан --package или --repository");
    }

    return config;
}

// Функция вывода конфигурации
void printConfig(const Config& config) {
    cout << "КОНФИГУРАЦИЯ ПРИЛОЖЕНИЯ" << endl;
    cout << "Имя анализируемого пакета: " <<
        (config.package_name.empty() ? "(не задано)" : config.package_name) << endl;
    cout << "URL репозитория: " <<
        (config.repository_url.empty() ? "(не задано)" : config.repository_url) << endl;
    cout << "Режим тестового репозитория: " <<
        (config.test_mode ? "включен" : "выключен") << endl;
    cout << "Подстрока для фильтрации: " <<
        (config.filter.empty() ? "(не задано)" : config.filter) << endl;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "RU");
    try {
        Config config = parseArguments(argc, argv);
        printConfig(config);
        cout << "Конфигурация успешно загружена!" << endl;
        return 0;
    }
    catch (const exception& e) {
        cerr << "ОШИБКА: " << e.what() << endl;
        cerr << "Используйте --help для справки" << endl;
        return 1;
    }
}
```
## Вывод для этапа 1:
**Реализованное CLI-приложение принимает и обрабатывает:**
- Аргументы командной строки через опции `--package`, `--repository`, `--test-mode`, `--filter`
- Валидацию корректности введенных параметров
- Вывод текущей конфигурации в формате ключ-значение
- Обработка ошибок 
- Систему справки по использованию через `--help`
