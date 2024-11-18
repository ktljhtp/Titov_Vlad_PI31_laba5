#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <locale.h>
#include <vector> 
#include <Windows.h>
using namespace std;

class Content {
private:
    string title;  // Название трека
    string artist;  // Исполнитель
    float duration;   // Продолжительность в секундах
    string format;  // Формат (например, MP3)
public:
    void set(string& t, string& a, float d, string& f) {
        // работа с this
        this->title = t;
        this->artist = a;
        this->duration = d;
        this->format = f;
    }
    void print() {
        cout << "Track: " << title << " by " << artist << " (Duration: " << duration << " sec, Format: " << format << ")\n";
    }
    float getDuration() const {
        return duration;
    }
};

class AudioSettings {
private:
    int volume;    // Уровень громкости (0 - 100)
    int balance;   // Баланс между левым и правым каналом (-50 до +50)

public:
    void set(int& v, int& b) {
        volume = v;
        balance = b;
    }
    void print() const {
        cout << "Громкость: " << volume << "\nБаланс: " << balance;
    }
};

class Device {
private:
    string deviceName;   // Название устройства
    int maxVolume;          // Максимальная громкость устройства
    int currentVolume;      // Текущая громкость устройства

public:
    void set(string& d, int& m, int& c) {
        deviceName = d;
        maxVolume = m;
        currentVolume = c;
    }
    void print() const {
        cout << "Название устройства: " << deviceName << ", Максимальная громкость устройства: " << maxVolume << ", Текущая громкость устройства: " << currentVolume << endl;
    }
};

class Equalizer {
private:
    int bass;      // Уровень низких частот (-10 до +10)
    int mid;       // Уровень средних частот (-10 до +10)
    int treble;    // Уровень высоких частот (-10 до +10)

public:
    void set(int& b, int& m, int& t) {
        bass = b;
        mid = m;
        treble = t;
    }
    void print() const {
        cout << "Equalizer - бас: " << bass << ", средние частоты: " << mid << ", высокие частоты: " << treble << endl;
    }
};

class PlaylistSettings {
private:
    int shuffle;  // Включен ли режим случайного воспроизведения (1 — да, 0 — нет)
    int repeat;   // Включен ли режим повторного воспроизведения (1 — да, 0 — нет)

public:
    void set(int& s, int& r) {
        shuffle = s;
        repeat = r;
    }
    void input_settings() {
        cout << "Введите режим случайного воспроизведения (1 — включено, 0 — выключено): ";
        cin >> shuffle;
        cout << "Введите режим повторного воспроизведения (1 — включено, 0 — выключено): ";
        cin >> repeat;
    }
    void print() {
        cout << "Случ воспроизведение: " << shuffle << "\nПовторное воспроизв: " << repeat;
    }
};

class TrackProgress {
private:
    float totalTime;    // Общее время трека в секундах
    int isPlaying;      // Флаг воспроизведения (1 — воспроизводится, 0 — пауза)

public:
    int currentTime;  // Текущее время воспроизведения в секундах

    void set(float& c, float& t, int& i) {
        currentTime = c;
        totalTime = t;
        isPlaying = i;
    }

    // Функция для вывода текущего состояния трека
    void print() const {
        cout << "Текущее время воспроизведения: " << currentTime << "/" << totalTime << " sec [" << (isPlaying ? "Playing" : "Paused") << "]\n";
    }

    // Функция для перемещения по таймлайну на 5 сек ##через указатель##
    void jump_5sec_timeline(int* time) {
        if (time != nullptr) {
            *time += 5;
        }
    }
};


class Playlist {
private:
    string name_playlist;
    PlaylistSettings setting; // Настройка плейлиста
    Content* tracks;          // Массив треков
    int trackCount;           // Количество треков

public:
    // Конструктор по умолчанию
    Playlist() : tracks(nullptr), trackCount(0) {}

    // Конструктор копирования
    Playlist(const Playlist& other) {
        name_playlist = other.name_playlist;
        setting = other.setting;
        trackCount = other.trackCount;

        // Копируем массив треков
        if (trackCount > 0) {
            tracks = new Content[trackCount];
            for (int i = 0; i < trackCount; ++i) {
                tracks[i] = other.tracks[i];
            }
        }
        else {
            tracks = nullptr;
        }
    }

    // Оператор присваивания
    Playlist& operator=(const Playlist& other) {
        if (this == &other) {
            return *this; // Проверка на самоприсваивание
        }

        // Освобождаем текущую память
        delete[] tracks;

        // Копируем данные
        name_playlist = other.name_playlist;
        setting = other.setting;
        trackCount = other.trackCount;

        // Копируем массив треков
        if (trackCount > 0) {
            tracks = new Content[trackCount];
            for (int i = 0; i < trackCount; ++i) {
                tracks[i] = other.tracks[i];
            }
        }
        else {
            tracks = nullptr;
        }

        return *this;
    }

    // Деструктор
    ~Playlist() {
        delete[] tracks;
    }

    // Установка имени плейлиста
    void name(string name) {
        name_playlist = name;
    }

    // Ввод настроек плейлиста
    void input_settings() {
        setting.input_settings();
    }

    // Функция для добавления треков в плейлист
    void add_tracks_to_playlist(int count) {
        delete[] tracks; // Освобождаем память, если массив уже существует
        tracks = new Content[count];
        trackCount = count;

        for (int i = 0; i < count; i++) {
            string title, artist, format;
            float duration;
            cout << "Введите название трека: ";
            cin >> title;
            cout << "Введите исполнителя: ";
            cin >> artist;
            cout << "Продолжительность в секундах: ";
            cin >> duration;
            cout << "Введите формат трека: ";
            cin >> format;
            tracks[i].set(title, artist, duration, format);
        }
    }

    // Функция для вывода информации о треках
    void print_playlist_info() {
        for (int i = 0; i < trackCount; i++) {
            cout << "Track " << i + 1 << ": ";
            tracks[i].print();
        }
    }

    // Функция для вывода настроек плейлиста
    void print_playlist_settings() {
        setting.print();
    }

    // Дружественная функция для вычисления общей продолжительности
    friend float calculateTotalDuration(Playlist& playlist);


    // Оператор присваивания
    Playlist& operator=(const Playlist& other) {
        // Проверка на самоприсваивание
        if (this == &other) {
            return *this;
        }

        // Освобождаем память текущего объекта
        delete[] tracks;

        // Копируем данные из другого объекта
        name_playlist = other.name_playlist;
        setting = other.setting;
        trackCount = other.trackCount;

        // Копируем массив треков
        if (trackCount > 0) {
            tracks = new Content[trackCount];
            for (int i = 0; i < trackCount; ++i) {
                tracks[i] = other.tracks[i]; // Используем оператор присваивания для Content
            }
        }
        else {
            tracks = nullptr;
        }

        // Возвращаем текущий объект для цепочки присваивания
        return *this;
    }
};


// Дружественная функции
float calculateTotalDuration(Playlist& playlist) {
    float totalDuration = 0.0;
    for (int i = 0; i < playlist.trackCount; i++) {
        totalDuration += playlist.tracks[i].getDuration();
    }
    return totalDuration; // Возвращаем общее время
}

class User {
private:
    string username;               // Имя пользователя
    AudioSettings audioSettings;   // Настройки аудио
    Device device;                 // Устройство пользователя
    Equalizer equalizer;           // Настройки эквалайзера
    string preferredCodec;         // Предпочтительный аудиоформат
    vector<Playlist*> playlists;    // Вектор для хранения указателей на плейлисты

public:

    // Функция для добавления плейлистов
    void add_playlist_user() {
        Playlist* newPlaylist = new Playlist(); // Создаем новый плейлист
        string name;

        cout << "Введите название плейлиста: ";
        cin >> name;
        newPlaylist->name(name);

        int trackCount;
        cout << "Введите количество треков для добавления в плейлист: ";
        cin >> trackCount;
        newPlaylist->add_tracks_to_playlist(trackCount);
        cout << "Введите настройки плейлиста:\n";
        newPlaylist->input_settings();

        playlists.push_back(newPlaylist); // Добавляем плейлист в вектор
    }

    // Функция для заполнения информации о пользователе
    void fill_user_data() {
        cout << "Введите имя пользователя: ";
        cin >> username;

        int volume, balance;
        cout << "Введите уровень громкости (0 - 100): ";
        cin >> volume;
        cout << "Введите баланс (-50 до +50): ";
        cin >> balance;
        audioSettings.set(volume, balance);

        string deviceName;
        int maxVolume, currentVolume;
        cout << "Введите название устройства: ";
        cin >> deviceName;
        cout << "Введите максимальную громкость устройства: ";
        cin >> maxVolume;
        cout << "Введите текущую громкость устройства: ";
        cin >> currentVolume;
        device.set(deviceName, maxVolume, currentVolume);

        int bass, mid, treble;
        cout << "Введите уровень низких частот (-10 до +10): ";
        cin >> bass;
        cout << "Введите уровень средних частот (-10 до +10): ";
        cin >> mid;
        cout << "Введите уровень высоких частот (-10 до +10): ";
        cin >> treble;
        equalizer.set(bass, mid, treble);

        cout << "Введите предпочитаемый аудиоформат (например, MP3): ";
        cin >> preferredCodec;
    }

    vector<Playlist*> getPlaylists() const {
        return playlists;
    }

    // Функция для вывода информации о пользователе
    void print_user_info() const {
        cout << "\nИнформация о пользователе:\n";
        cout << "Имя: " << username << "\n";
        audioSettings.print();
        device.print();
        equalizer.print();
        cout << "Preferred Codec: " << preferredCodec << "\n";

        // Вывод информации о плейлистах
        cout << "\nПлейлисты:\n";
        for (size_t i = 0; i < playlists.size(); i++) {
            cout << "Плейлист " << i + 1 << ":\n";
            playlists[i]->print_playlist_info();
            playlists[i]->print_playlist_settings();
        }
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    // Демонстрация динамического массива объектов класса User
    int numUsers;
    cout << "Введите количество пользователей: ";
    cin >> numUsers;

    // Создаем динамический массив объектов класса User
    User* usersArray = new User[numUsers];
    for (int i = 0; i < numUsers; ++i) {
        cout << "\nПользователь " << i + 1 << ":\n";
        usersArray[i].fill_user_data();

        // Добавление плейлистов для пользователя
        char addMore;
        do {
            usersArray[i].add_playlist_user();
            cout << "Хотите добавить еще один плейлист? (y/n): ";
            cin >> addMore;
        } while (addMore == 'y' || addMore == 'Y');
    }

    // Вывод информации о каждом пользователе и демонстрация работы calculateTotalDuration
    cout << "\nИнформация о пользователях:\n";
    for (int i = 0; i < numUsers; ++i) {
        cout << "\n--- Пользователь " << i + 1 << " ---\n";
        usersArray[i].print_user_info();

        // Вычисление общей продолжительности всех треков во всех плейлистах
        float totalDuration = 0.0;
        for (Playlist* playlist : usersArray[i].getPlaylists()) { // Получаем список плейлистов пользователя
            totalDuration += calculateTotalDuration(*playlist);
        }
        cout << "\nОбщая продолжительность всех треков пользователя: " << totalDuration << " секунд\n";
    }

    // Демонстрация работы указателя
    char question;
    TrackProgress trackProgress;
    trackProgress.currentTime = 0;
    cout << "\nХотите перемотать трек на 5 сек вперед? (y/n): ";
    cin >> question;
    if (question == 'y' || question == 'Y') {
        trackProgress.jump_5sec_timeline(&trackProgress.currentTime);
    }
    std::cout << "Трек прогресс: " << trackProgress.currentTime << " секунд\n";

    //демонстрация работы перегрузки
    Playlist playlist1;
    playlist1.add_tracks_to_playlist(2);

    Playlist playlist2;
    playlist2 = playlist1; // Используется перегруженный оператор присваивания

    playlist2.print_playlist_info();

    // Освобождаем память, выделенную для массива объектов
    delete[] usersArray;
}

