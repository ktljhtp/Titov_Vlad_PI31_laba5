#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <Windows.h>
#include <stdexcept>

using namespace std;

// Класс исключений
class PlaylistException : public runtime_error {
public:
    explicit PlaylistException(const string& message) : runtime_error(message) {}
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

    friend bool operator==(const Content& c1, const Content& c2); // Дружественная функция
};

bool operator==(const Content& c1, const Content& c2) {
    return c1.title == c2.title && c1.artist == c2.artist &&
        c1.duration == c2.duration && c1.format == c2.format;
}

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
        try {
            if (count <= 0) {
                throw PlaylistException("Количество треков должно быть больше нуля.");
            }

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
        catch (const PlaylistException& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "Неизвестная ошибка: " << e.what() << endl;
        }
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

    // Возврат значения через указатель
    const Content* getTrackByIndexPtr(int index) const {
        if (index >= 0 && index < trackCount) {
            return &tracks[index];
        }
        return nullptr; // Вернем nullptr, если индекс неверный
    }

    // Возврат значения через ссылку
    Content& getTrackByIndexRef(int index) {
        if (index >= 0 && index < trackCount) {
            return tracks[index];
        }
        throw out_of_range("Неверный индекс трека.");
    }

    int getTrackCount() const {
        return trackCount;
    }

    static int getTotalTrackCount() {
        return totalTrackCount;
    }

    // Перегрузка оператора сравнения
    friend bool operator==(const Playlist& p1, const Playlist& p2);
};

int Playlist::totalTrackCount = 0;

// Перегрузка оператора сравнения для Playlist
bool operator==(const Playlist& p1, const Playlist& p2) {
    return p1.name_playlist == p2.name_playlist && p1.trackCount == p2.trackCount;
}

float calculateTotalDuration(const Playlist& playlist) {
    float totalDuration = 0.0f;
    for (int i = 0; i < playlist.getTrackCount(); i++) {
        totalDuration += playlist.getTracks()[i].getDuration();
    }
    return totalDuration;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int numUsers;
    cout << "Введите количество пользователей: ";
    cin >> numUsers;

    vector<Playlist> playlists;

    for (int i = 0; i < numUsers; ++i) {
        Playlist p;
        cout << "\nВведите название плейлиста для пользователя " << i + 1 << ": ";
        string name;
        cin.ignore(); // Очистка буфера ввода
        getline(cin, name);
        p.setName(name);

        int trackCount;
        cout << "Введите количество треков: ";
        cin >> trackCount;
        p.add_tracks_to_playlist(trackCount);

        playlists.push_back(p);
    }

    for (int i = 0; i < numUsers; ++i) {
        cout << "\nПлейлист пользователя " << i + 1 << ":\n";
        playlists[i].print_playlist_info();
    }

    cout << "\nОбщее количество треков во всех плейлистах: " << Playlist::getTotalTrackCount() << endl;

    for (int i = 0; i < numUsers; ++i) {
        float totalDuration = calculateTotalDuration(playlists[i]);
        cout << "Общая длительность плейлиста пользователя " << i + 1 << ": " << totalDuration << " секунд\n";
    }
}
