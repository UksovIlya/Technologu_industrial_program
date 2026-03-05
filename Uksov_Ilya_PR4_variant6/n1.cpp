#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <ctime>
#include <cstdio>  // для remove, rename
#include <sys/stat.h>  // для работы с файлами в Windows
#include <direct.h>  // для mkdir в Windows

using namespace std;

// Структура для хранения информации о файле
struct FileInfo {
    string name;
    string path;
    long long size;
    string creationTime;
    bool isReadOnly;

    FileInfo() : size(0), isReadOnly(false) {}
};

class FileManager {
private:
    string rootPath;
    map<string, FileInfo> files;

    // Получить текущее время
    string getCurrentTime() {
        time_t now = time(0);
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &now);
        string dt = buffer;
        if (!dt.empty() && dt[dt.length() - 1] == '\n')
            dt.erase(dt.length() - 1);
        return dt;
    }

    // Проверить, существует ли файл/папка
    bool fileExists(const string& path) {
        struct stat buffer;
        return (stat(path.c_str(), &buffer) == 0);
    }

    // Создать папку
    bool createDirectory(const string& path) {
        return _mkdir(path.c_str()) == 0;
    }

    // Получить размер файла
    long long getFileSize(const string& path) {
        struct stat buffer;
        if (stat(path.c_str(), &buffer) == 0) {
            return buffer.st_size;
        }
        return 0;
    }

    // Обновить информацию о файле
    void updateFileInfo(const string& name) {
        string fullPath = rootPath + "\\" + name;

        if (!fileExists(fullPath)) {
            files.erase(name);
            return;
        }

        if (files.count(name) > 0) {
            files[name].size = getFileSize(fullPath);
        }
    }

    // Просканировать папку
    void scanDirectory() {
        files.clear();

        // В Windows можно использовать findfirst/findnext, но это сложно
        // Поэтому просто проверяем существование файлов при необходимости
        cout << "Кэш очищен. Файлы будут добавляться при обращении." << endl;
    }

public:
    FileManager(const string& path) {
        rootPath = path;

        if (!fileExists(rootPath)) {
            if (createDirectory(rootPath)) {
                cout << "Создана папка: " << rootPath << endl;
            }
            else {
                cout << "Не удалось создать папку: " << rootPath << endl;
            }
        }

        scanDirectory();
        cout << "Файловый менеджер инициализирован. Рабочая папка: " << rootPath << endl;
    }

    bool createFile(const string& name) {
        string fullPath = rootPath + "\\" + name;

        // Проверяем, существует ли файл
        if (fileExists(fullPath)) {
            cout << "Ошибка: файл " << name << " уже существует!" << endl;
            return false;
        }

        // Создаем файл
        ofstream file(fullPath);
        if (!file) {
            cout << "Ошибка: не удалось создать файл " << name << endl;
            return false;
        }
        file.close();

        // Добавляем в кэш
        FileInfo newFile;
        newFile.name = name;
        newFile.path = fullPath;
        newFile.size = 0;
        newFile.creationTime = getCurrentTime();
        newFile.isReadOnly = false;

        files[name] = newFile;

        cout << "Файл " << name << " успешно создан!" << endl;
        return true;
    }

    bool deleteFile(const string& name) {
        if (files.count(name) == 0) {
            cout << "Ошибка: файл " << name << " не найден!" << endl;
            return false;
        }

        if (files[name].isReadOnly) {
            cout << "Ошибка: файл " << name << " защищен от удаления!" << endl;
            return false;
        }

        string fullPath = rootPath + "\\" + name;

        // Используем remove из cstdio
        if (remove(fullPath.c_str()) == 0) {
            files.erase(name);
            cout << "Файл " << name << " удален!" << endl;
            return true;
        }
        else {
            cout << "Ошибка: не удалось удалить файл " << name << endl;
            return false;
        }
    }

    bool copyFile(const string& source, const string& destination) {
        if (files.count(source) == 0) {
            cout << "Ошибка: исходный файл " << source << " не найден!" << endl;
            return false;
        }

        string sourcePath = rootPath + "\\" + source;
        string destPath = rootPath + "\\" + destination;

        // Простое копирование файла
        ifstream src(sourcePath, ios::binary);
        ofstream dst(destPath, ios::binary);

        if (!src || !dst) {
            cout << "Ошибка при копировании" << endl;
            return false;
        }

        dst << src.rdbuf();
        src.close();
        dst.close();

        // Добавляем в кэш
        FileInfo newFile;
        newFile.name = destination;
        newFile.path = destPath;
        newFile.size = files[source].size;
        newFile.creationTime = getCurrentTime();
        newFile.isReadOnly = false;
        files[destination] = newFile;

        cout << "Файл скопирован: " << source << " -> " << destination << endl;
        return true;
    }

    bool moveFile(const string& source, const string& destination) {
        if (files.count(source) == 0) {
            cout << "Ошибка: исходный файл " << source << " не найден!" << endl;
            return false;
        }

        string sourcePath = rootPath + "\\" + source;
        string destPath = rootPath + "\\" + destination;

        // Используем rename из cstdio
        if (rename(sourcePath.c_str(), destPath.c_str()) == 0) {
            files[destination] = files[source];
            files[destination].name = destination;
            files[destination].path = destPath;
            files.erase(source);

            cout << "Файл перемещен: " << source << " -> " << destination << endl;
            return true;
        }
        else {
            cout << "Ошибка при перемещении" << endl;
            return false;
        }
    }

    void setReadOnly(const string& name, bool readonly = true) {
        if (files.count(name) == 0) {
            cout << "Ошибка: файл " << name << " не найден!" << endl;
            return;
        }

        files[name].isReadOnly = readonly;

        // В Windows можно установить атрибут файла, но для простоты просто запоминаем
        if (readonly)
            cout << "Файл " << name << " теперь только для чтения (в менеджере)" << endl;
        else
            cout << "Файл " << name << " теперь доступен для записи (в менеджере)" << endl;
    }

    bool writeToFile(const string& name, const string& text) {
        if (files.count(name) == 0) {
            cout << "Ошибка: файл " << name << " не найден!" << endl;
            return false;
        }

        if (files[name].isReadOnly) {
            cout << "Ошибка: файл " << name << " только для чтения!" << endl;
            return false;
        }

        string fullPath = rootPath + "\\" + name;

        ofstream file(fullPath);
        if (!file) {
            cout << "Ошибка: не удалось открыть файл для записи" << endl;
            return false;
        }

        file << text;
        file.close();

        updateFileInfo(name);

        cout << "Текст записан в файл " << name << endl;
        return true;
    }

    string readFile(const string& name) {
        if (files.count(name) == 0) {
            cout << "Ошибка: файл " << name << " не найден!" << endl;
            return "";
        }

        string fullPath = rootPath + "\\" + name;

        ifstream file(fullPath);
        if (!file) {
            cout << "Ошибка: не удалось открыть файл для чтения" << endl;
            return "";
        }

        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();

        return content;
    }

    void showFileInfo(const string& name) {
        if (files.count(name) == 0) {
            cout << "Файл " << name << " не найден!" << endl;
            return;
        }

        FileInfo& f = files[name];
        updateFileInfo(name);

        cout << "\n=== Информация о файле: " << name << " ===" << endl;
        cout << "Путь: " << f.path << endl;
        cout << "Размер: " << f.size << " байт" << endl;
        cout << "Создан: " << f.creationTime << endl;
        cout << "Права: " << (f.isReadOnly ? "только чтение" : "чтение/запись") << endl;
    }

    void listFiles() {
        cout << "\n=== Файлы в папке " << rootPath << " (из кэша) ===" << endl;

        if (files.empty()) {
            cout << "В кэше нет файлов. Создайте или добавьте файлы." << endl;
            return;
        }

        for (const auto& pair : files) {
            const FileInfo& f = pair.second;
            cout << "• " << f.name;
            cout << " (" << f.size << " байт)";
            if (f.isReadOnly) cout << " [RO]";
            cout << endl;
        }
    }

    // Добавить существующий файл в кэш вручную
    bool addToCache(const string& name) {
        string fullPath = rootPath + "\\" + name;

        if (!fileExists(fullPath)) {
            cout << "Файл " << name << " не существует!" << endl;
            return false;
        }

        if (files.count(name) > 0) {
            cout << "Файл " << name << " уже есть в кэше!" << endl;
            return true;
        }

        FileInfo newFile;
        newFile.name = name;
        newFile.path = fullPath;
        newFile.size = getFileSize(fullPath);
        newFile.creationTime = getCurrentTime();
        newFile.isReadOnly = false;

        files[name] = newFile;
        cout << "Файл " << name << " добавлен в кэш" << endl;
        return true;
    }
};

int main() {
    // Отключаем предупреждение про ctime
    setlocale(LC_ALL, "Russian");

    cout << "=== ПРОСТОЙ ФАЙЛОВЫЙ МЕНЕДЖЕР (БЕЗ FILESYSTEM) ===\n" << endl;

    FileManager fm("my_files");

    fm.createFile("test1.txt");
    fm.createFile("test2.txt");
    fm.createFile("secret.txt");

    fm.writeToFile("test1.txt", "Привет, мир!");
    fm.writeToFile("test2.txt", "Это тестовый файл номер 2");
    fm.writeToFile("secret.txt", "Секретные данные");

    fm.listFiles();

    fm.copyFile("test1.txt", "test1_copy.txt");
    fm.moveFile("test2.txt", "test2_moved.txt");

    fm.setReadOnly("secret.txt", true);
    fm.writeToFile("secret.txt", "Попытка взлома");

    cout << "\nСодержимое test1.txt: " << fm.readFile("test1.txt") << endl;

    fm.showFileInfo("secret.txt");
    fm.deleteFile("test1_copy.txt");

    fm.listFiles();

    return 0;
}