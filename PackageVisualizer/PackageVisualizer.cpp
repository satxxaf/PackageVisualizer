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