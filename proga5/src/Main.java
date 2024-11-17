import java.util.ArrayList;
import java.util.Scanner;

class Content {
    private String title;   // Название трека
    private String artist;  // Исполнитель
    private float duration; // Продолжительность в секундах
    private String format;  // Формат (например, MP3)

    public void set(String title, String artist, float duration, String format) {
        this.title = title;
        this.artist = artist;
        this.duration = duration;
        this.format = format;
    }

    public void print() {
        System.out.println("Track: " + title + " by " + artist + " (Duration: " + duration + " sec, Format: " + format + ")");
    }
}

class AudioSettings {
    private int volume;  // Уровень громкости (0 - 100)
    private int balance; // Баланс между левым и правым каналом (-50 до +50)

    public void set(int volume, int balance) {
        this.volume = volume;
        this.balance = balance;
    }

    public void print() {
        System.out.println("Громкость: " + volume + "\nБаланс: " + balance);
    }
}

class Device {
    private String deviceName;  // Название устройства
    private int maxVolume;      // Максимальная громкость устройства
    private int currentVolume;  // Текущая громкость устройства

    public void set(String deviceName, int maxVolume, int currentVolume) {
        this.deviceName = deviceName;
        this.maxVolume = maxVolume;
        this.currentVolume = currentVolume;
    }

    public void print() {
        System.out.println("Название устройства: " + deviceName + ", Максимальная громкость устройства: " + maxVolume + ", Текущая громкость устройства: " + currentVolume);
    }
}

class Equalizer {
    private int bass;   // Уровень низких частот (-10 до +10)
    private int mid;    // Уровень средних частот (-10 до +10)
    private int treble; // Уровень высоких частот (-10 до +10)

    public void set(int bass, int mid, int treble) {
        this.bass = bass;
        this.mid = mid;
        this.treble = treble;
    }

    public void print() {
        System.out.println("Equalizer - бас: " + bass + ", средние частоты: " + mid + ", высокие частоты: " + treble);
    }
}

class PlaylistSettings {
    private boolean shuffle; // Включен ли режим случайного воспроизведения
    private boolean repeat;  // Включен ли режим повторного воспроизведения

    public void inputSettings(Scanner scanner) {
        System.out.print("Введите режим случайного воспроизведения (1 - включено, 0 - выключено): ");
        shuffle = scanner.nextInt() == 1;
        System.out.print("Введите режим повторного воспроизведения (1 - включено, 0 - выключено): ");
        repeat = scanner.nextInt() == 1;
    }

    public void print() {
        System.out.println("Случ воспроизведение: " + (shuffle ? "включено" : "выключено") + "\nПовторное воспроизв: " + (repeat ? "включено" : "выключено"));
    }
}

class Playlist {
    private String name;
    private PlaylistSettings setting = new PlaylistSettings();
    private ArrayList<Content> tracks = new ArrayList<>();

    public void setName(String name) {
        this.name = name;
    }

    public void inputSettings(Scanner scanner) {
        setting.inputSettings(scanner);
    }

    public void addTracks(Scanner scanner, int count) {
        tracks.clear();

        for (int i = 0; i < count; i++) {
            System.out.print("Введите название трека: ");
            String title = scanner.next();
            System.out.print("Введите исполнителя: ");
            String artist = scanner.next();
            System.out.print("Продолжительность в секундах: ");
            float duration = scanner.nextFloat();
            System.out.print("Введите формат трека: ");
            String format = scanner.next();
            Content track = new Content();
            track.set(title, artist, duration, format);
            tracks.add(track);
        }
    }

    public void printPlaylistInfo() {
        for (int i = 0; i < tracks.size(); i++) {
            System.out.print("Track " + (i + 1) + ": ");
            tracks.get(i).print();
        }
    }

    public void printPlaylistSettings() {
        setting.print();
    }
}

class User {
    private String username;
    private AudioSettings audioSettings = new AudioSettings();
    private Device device = new Device();
    private Equalizer equalizer = new Equalizer();
    private String preferredCodec;
    private ArrayList<Playlist> playlists = new ArrayList<>();

    public void addPlaylist(Scanner scanner) {
        Playlist newPlaylist = new Playlist();
        System.out.print("Введите название плейлиста: ");
        String name = scanner.next();
        newPlaylist.setName(name);

        System.out.print("Введите количество треков для добавления в плейлист: ");
        int trackCount = scanner.nextInt();
        newPlaylist.addTracks(scanner, trackCount);

        System.out.println("Введите настройки плейлиста:");
        newPlaylist.inputSettings(scanner);

        playlists.add(newPlaylist);
    }

    public void fillUserData(Scanner scanner) {
        System.out.print("Введите имя пользователя: ");
        username = scanner.next();

        System.out.print("Введите уровень громкости (0 - 100): ");
        int volume = scanner.nextInt();
        System.out.print("Введите баланс (-50 до +50): ");
        int balance = scanner.nextInt();
        audioSettings.set(volume, balance);

        System.out.print("Введите название устройства: ");
        String deviceName = scanner.next();
        System.out.print("Введите максимальную громкость устройства: ");
        int maxVolume = scanner.nextInt();
        System.out.print("Введите текущую громкость устройства: ");
        int currentVolume = scanner.nextInt();
        device.set(deviceName, maxVolume, currentVolume);

        System.out.print("Введите уровень низких частот (-10 до +10): ");
        int bass = scanner.nextInt();
        System.out.print("Введите уровень средних частот (-10 до +10): ");
        int mid = scanner.nextInt();
        System.out.print("Введите уровень высоких частот (-10 до +10): ");
        int treble = scanner.nextInt();
        equalizer.set(bass, mid, treble);

        System.out.print("Введите предпочитаемый аудиоформат (например, MP3): ");
        preferredCodec = scanner.next();
    }

    public void printUserInfo() {
        System.out.println("\nИнформация о пользователе:");
        System.out.println("Имя: " + username);
        audioSettings.print();
        device.print();
        equalizer.print();
        System.out.println("Preferred Codec: " + preferredCodec);

        System.out.println("\nПлейлисты:");
        for (int i = 0; i < playlists.size(); i++) {
            System.out.println("Плейлист " + (i + 1) + ":");
            playlists.get(i).printPlaylistInfo();
            playlists.get(i).printPlaylistSettings();
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Введите количество пользователей: ");
        int numUsers = scanner.nextInt();
        User[] usersArray = new User[numUsers];

        for (int i = 0; i < numUsers; i++) {
            System.out.println("\nПользователь " + (i + 1) + ":");
            usersArray[i] = new User();
            usersArray[i].fillUserData(scanner);

            char addMore;
            do {
                usersArray[i].addPlaylist(scanner);
                System.out.print("Хотите добавить еще один плейлист? (y/n): ");
                addMore = scanner.next().charAt(0);
            } while (addMore == 'y' || addMore == 'Y');
        }

        System.out.println("\nИнформация о пользователях:");
        for (User user : usersArray) {
            user.printUserInfo();
        }

        scanner.close();
    }
}

