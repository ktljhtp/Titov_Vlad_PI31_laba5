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
        title = t;
        artist = a;
        duration = d;
        format = f;
    }
    void print() {
        cout << "Track: " << title << " by " << artist << " (Duration: " << duration << " sec, Format: " << format << ")\n";
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
    float currentTime;  // Текущее время воспроизведения в секундах
    float totalTime;    // Общее время трека в секундах
    int isPlaying;      // Флаг воспроизведения (1 — воспроизводится, 0 — пауза)

public:
    void set(float& c, float& t, int& i) {
        currentTime = c;
        totalTime = t;
        isPlaying = i;
    }

    // Функция для вывода текущего состояния трека
    void print() const {
        cout << "Текущее время воспроизведения: " << currentTime << "/" << totalTime << " sec [" << (isPlaying ? "Playing" : "Paused") << "]\n";
    }
};

class Playlist {
private:
    string name_playlist;
    PlaylistSettings setting; //настройка плейлиста  
    Content* tracks;  // Массив треков
    int trackCount;  // Количество треков

public:
    void name(string name) {
        name_playlist = name;
    }
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
};

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

    // Демонстрация динамического массива объектов класса
    int numUsers;
    cout << "Введите количество пользователей: ";
    cin >> numUsers;

    // Создаем динамический массив объектов класса User
    User* usersArray = new User[numUsers];
    for (int i = 0; i < numUsers; ++i) {
        cout << "\nПользователь " << i + 1 << ":\n";
        usersArray[i].fill_user_data();

        char addMore;
        do {
            usersArray[i].add_playlist_user(); // Allow users to add playlists
            cout << "Хотите добавить еще один плейлист? (y/n): ";
            cin >> addMore;
        } while (addMore == 'y' || addMore == 'Y');
    }

    // Вывод информации о каждом пользователе
    cout << "\nИнформация о пользователях:\n";
    for (int i = 0; i < numUsers; ++i) {
        usersArray[i].print_user_info();
    }

    // Освобождаем память, выделенную для массива объектов
    delete[] usersArray;


}
