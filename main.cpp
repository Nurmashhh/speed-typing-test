#include <iostream>
#include <chrono>
#include <string>

#ifdef _WIN32
    #include <conio.h>  // для _getch() на Windows
    #define PRINT_ERROR system("color 4")
    #define DEFAULT_PRINT system("color 7")
#else
    #include <termios.h>
    #include <unistd.h>
    #define PRINT_ERROR std::cout << "\033[91m"
    #define DEFAULT_PRINT std::cout << "\033[0m"

    // Реализация _getch() для Linux/Unix
        char _getch() {
        char buf = 0;
        struct termios old;
        struct termios newt;

        if (tcgetattr(STDIN_FILENO, &old) < 0) {
            perror("tcgetattr()");
        }

        newt = old;  // Сохраняем текущие настройки

        newt.c_lflag &= ~ICANON;  // Отключаем буферизацию ввода (неканонический режим)
        newt.c_lflag &= ~ECHO;    // Отключаем вывод символов в терминал

        if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) < 0) {
            perror("tcsetattr ICANON");
        }

        if (read(STDIN_FILENO, &buf, 1) < 0) {
            perror("read()");
        }

        // Восстанавливаем старые параметры терминала
        if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0) {
            perror("tcsetattr ~ICANON");
        }

        return buf;
    }
#endif

bool valid_character(char ch) {
    if (ch != '\b' && ch != '\r' && ch != '\n' && (isalpha(ch) || ch == ' ' || ch == ',' || ch == '.' || ch == '?' || ch == '\'' || ch == '-')) {
        return true;
    }
    return false;
}

int main() {
    // Шаг 1: Подготовка текста
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
    
    std::string testText[] = {
        "Emma hurried through the park, her eyes scanning the ground.", 
        "She had just realized she lost her house key somewhere on her walk,", 
        "and panic was starting to set in. The sun was setting, casting long", 
        "shadows across the path, making it harder to see.",
        "As she retraced her steps, Emma's mind raced with thoughts of being locked out for the night.",
        "How could I have been so careless?", 
        "she muttered to herself. Just as she was about to give up hope, a glint of metal caught her eye.", 
        "There, half-buried under some fallen leaves, was her key.",
        "Emma let out a sigh of relief and picked up the key, a smile spreading across her face.",
        "Never again, she promised herself, clutching the key tightly.",
        "With a grateful heart, she continued her walk home, the day's worries fading away with each step."
    };

    size_t count = 0;

    while (true) {
        std::string userInput;
        std::cout << testText[count] << std::endl;
        for (size_t i = 0; i < testText[count].size(); i++) {
            std::cout << "-";
        }
        std::cout << "\n";

        // Шаг 2: Измерение времени начала ввода
        auto start = std::chrono::steady_clock::now();

        // Ввод текста в реальном времени с отображением ошибок
        size_t position = 0;
        bool inputCorrect = true;

        while (position < testText[count].size()) {
            char ch = _getch();  // Считываем символ с клавиатуры

            if ((ch == 8 || ch == 127) && position > 0) {  // Обработка удаления символа (Backspace)
                std::cout << "\b \b" << std::flush;  // Удаляем символ с экрана
                userInput.pop_back();  // Удаляем последний символ из строки
                position--;
            } else if (valid_character(ch)) {  // Если это не Backspace и не Enter
                if (testText[count][position] != ch) {
                    PRINT_ERROR;  // Выводим в красном цвете, если ошибка
                    inputCorrect = false;
                } else {
                    DEFAULT_PRINT;  // Выводим в белом цвете, если правильно
                }
                std::cout << ch << std::flush;  // Выводим символ на экран
                userInput += ch;  // Добавляем символ в строку
                position++;
            }
        }
        for (size_t i = 0; i < testText[count].size(); i++) {
            if (userInput[i] != testText[count][i]) {
                inputCorrect = false;
                break;
            }
            if (userInput[i] == testText[count][i]) {
                inputCorrect = true;
            }
        }

        // Шаг 4: Измерение времени окончания ввода
        auto end = std::chrono::steady_clock::now();

        // Шаг 5: Вычисление времени выполнения
        std::chrono::duration<double> elapsed_seconds = end - start;

        // Очищение экрана
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        DEFAULT_PRINT;
        if (inputCorrect) {
            std::cout << "Congratulations! You typed it correctly!\n";
        } else {
            std::cout << "Try again.\n";
        }
        
        std::cout << "Time taken: " << elapsed_seconds.count() << " seconds\n";
        std::cout << "Characters per minute: " << (userInput.size() / elapsed_seconds.count()) * 60 << "\n\n";

        // Счётчик строк
        if (count == 10) {
            count = 0;
        } else if (inputCorrect) {
            count++;
        }
    }

    return 0;
}
