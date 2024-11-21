#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <Windows.h>
#include <stdexcept>

using namespace std;

class TrackProgress {
public:
    float currentTime;

    // Метод для перемотки трека на 5 секунд вперед
    void jump_5sec_timeline(float* time) {
        if (time) {
            *time += 5.0f;
        }
    }
};

class PlaylistSettings {
private:
    bool shuffle; // Режим случайного воспроизведения
    bool repeat;  // Режим повтора

public:
    void inputSettings() {
        int input;

        cout << "Введите режим случайного воспроизведения (1 - включено, 0 - выключено): ";
        cin >> input;
        shuffle = (input == 1);

        cout << "Введите режим повторного воспроизведения (1 - включено, 0 - выключено): ";
        cin >> input;
        repeat = (input == 1);
    }

    void print() const {
        cout << "Случайное воспроизведение: " << (shuffle ? "включено" : "выключено")
            << "\nПовторное воспроизведение: " << (repeat ? "включено" : "выключено") << endl;
    }
};


class Device {
private:
    static constexpr const char* deviceType = "Audio Device"; // Тип устройства (статический)
    string deviceName; // Название устройства
    int maxVolume;     // Максимальная громкость
    int currentVolume; // Текущая громкость

public:
    void set(const string& name, int maxVol, int currVol) {
        deviceName = name;
        maxVolume = maxVol;
        currentVolume = currVol;
    }

    void print() const {
        cout << "Название устройства: " << deviceName
            << "\nМаксимальная громкость: " << maxVolume
            << "\nТекущая громкость: " << currentVolume << endl;
    }

    static void printDeviceType() {
        cout << "Тип устройства: " << deviceType << endl;
    }
};

class AudioSettings {
private:
    int volume;   // Уровень громкости
    int balance;  // Баланс каналов

public:
    void set(int vol, int bal) {
        volume = vol;
        balance = bal;
    }

    void print() const {
        cout << "Громкость: " << volume
            << "\nБаланс: " << balance << endl;
    }
};


class Content {
private:
    string title;  // Название трека
    string artist; // Исполнитель
    float duration;   // Продолжительность в секундах
    string format;  // Формат (например, MP3)
public:
    void set(const string& t, const string& a, float d, const string& f) {
        this->title = t;
        this->artist = a;
        this->duration = d;
        this->format = f;
    }
    void print() const {
        cout << "Track: " << title << " by " << artist << " (Duration: " << duration << " sec, Format: " << format << ")\n";
    }
    float getDuration() const {
        return duration;
    }
};

class Playlist {
private:
    string name_playlist;
    Content* tracks;
    int trackCount;

    static int totalTrackCount; // Общее количество треков

public:
    Playlist() : tracks(nullptr), trackCount(0) {}

    Playlist(const Playlist& other) : name_playlist(other.name_playlist), trackCount(other.trackCount) {
        tracks = new Content[trackCount];
        for (int i = 0; i < trackCount; i++) {
            tracks[i] = other.tracks[i];
        }
        totalTrackCount += trackCount;
    }

    ~Playlist() {
        totalTrackCount -= trackCount;
        delete[] tracks;
    }

    Playlist& operator=(const Playlist& other) {
        if (this == &other)
            return *this;

        delete[] tracks;

        name_playlist = other.name_playlist;
        trackCount = other.trackCount;
        tracks = new Content[trackCount];
        for (int i = 0; i < trackCount; i++) {
            tracks[i] = other.tracks[i];
        }
        return *this;
    }

    void setName(const string& name) {
        this->name_playlist = name;
    }

    void add_tracks_to_playlist(int count) {
        delete[] tracks;
        tracks = new Content[count];
        trackCount = count;

        cin.ignore(); // Очистка буфера ввода
        for (int i = 0; i < count; i++) {
            string title, artist, format;
            float duration;

            cout << "Введите название трека: ";
            getline(cin, title);
            cout << "Введите исполнителя: ";
            getline(cin, artist);
            cout << "Продолжительность в секундах: ";
            cin >> duration;
            cin.ignore(); // Очистка буфера ввода
            cout << "Введите формат трека: ";
            getline(cin, format);

            tracks[i].set(title, artist, duration, format);
        }

        totalTrackCount += count;
    }

    void print_playlist_info() const {
        cout << "Playlist Name: " << name_playlist << endl;
        for (int i = 0; i < trackCount; i++) {
            cout << "Track " << i + 1 << ": ";
            tracks[i].print();
        }
    }

    const Content* getTracks() const {
        return tracks;
    }

    int getTrackCount() const {
        return trackCount;
    }

    static int getTotalTrackCount() {
        return totalTrackCount;
    }
};

int Playlist::totalTrackCount = 0;

class User {
private:
    vector<Playlist> userPlaylists;
public:
    void add_playlist_user() {
        Playlist p;
        cout << "Введите название нового плейлиста: ";
        string name;
        cin.ignore(); // Очистка буфера ввода
        getline(cin, name);
        p.setName(name);

        int trackCount;
        cout << "Введите количество треков: ";
        cin >> trackCount;
        p.add_tracks_to_playlist(trackCount);

        userPlaylists.push_back(p);
    }

    void print_user_playlists() const {
        for (size_t i = 0; i < userPlaylists.size(); ++i) {
            cout << "\nПлейлист " << i + 1 << ":\n";
            userPlaylists[i].print_playlist_info();
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Работа с Device
    Device device;
    device.set("Мультимедиа система", 100, 50);
    device.print();
    Device::printDeviceType();

    // Работа с AudioSettings
    AudioSettings audioSettings;
    audioSettings.set(70, 0); // Громкость 70, баланс 0
    audioSettings.print();

    // Работа с PlaylistSettings
    PlaylistSettings playlistSettings;
    playlistSettings.inputSettings();
    playlistSettings.print();

    // Работа с пользователями и плейлистами
    int numUsers;
    cout << "Введите количество пользователей: ";
    cin >> numUsers;

    vector<User> usersArray(numUsers);

    for (int i = 0; i < numUsers; ++i) {
        char addMore;
        cout << "\nДобавление плейлистов для пользователя " << i + 1 << ":\n";
        do {
            usersArray[i].add_playlist_user();
            cout << "Хотите добавить еще один плейлист? (y/n): ";
            cin >> addMore;
        } while (addMore == 'y' || addMore == 'Y');
    }

    for (int i = 0; i < numUsers; ++i) {
        cout << "\nПлейлисты пользователя " << i + 1 << ":\n";
        usersArray[i].print_user_playlists();
    }

    // Демонстрация работы TrackProgress
    char question;
    TrackProgress trackProgress;
    trackProgress.currentTime = 0;
    cout << "Хотите перемотать трек на 5 сек вперед? (y/n): ";
    cin >> question;
    if (question == 'y' || question == 'Y') {
        trackProgress.jump_5sec_timeline(&trackProgress.currentTime);
    }
    cout << "Текущий прогресс трека: " << trackProgress.currentTime << " секунд\n";

}
