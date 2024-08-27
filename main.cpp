#include <iostream>
#include <chrono>  // для измерения времени
#include <string>  // для работы со строками

int main() {
    // Шаг 1: Подготовка текста
    std::string testText[] = {"Emma hurried through the park, her eyes scanning the ground.", 
                              "She had just realized she lost her house key somewhere on her walk,", 
                              "and panic was starting to set in. The sun was setting, casting long", 
                              "shadows across the path, making it harder to see.",
                              "As she retraced her steps, Emma's mind raced with thoughts of being locked out for the night.",
                              "How could I have been so careless?", 
                              "she muttered to herself. Just as she was about to give up hope, a glint of metal caught her eye.", 
                              "There, half-buried under some fallen leaves, was her key.",
                              "Emma let out a sigh of relief and picked up the key, a smile spreading across her face.",
                              "Never again, she promised herself, clutching the key tightly.",
                              "With a grateful heart, she continued her walk home, the day's worries fading away with each step."};

    int8_t count = 0;
    
    while (1) {
        std::cout << testText[count] << std::endl;
        for (size_t i = 0; i < testText[count].size(); i++) {
            std::cout << "-";
        }
        std::cout << "\n";

        // Шаг 2: Измерение времени начала ввода
        auto start = std::chrono::steady_clock::now();
        
        // Шаг 3: Считывание введенного текста
        std::string userInput;
        std::getline(std::cin, userInput);
        
        // Шаг 4: Измерение времени окончания ввода
        auto end = std::chrono::steady_clock::now();
        
        // Шаг 5: Вычисление времени выполнения
        std::chrono::duration<double> elapsed_seconds = end - start;
        
        // Шаг 6: Вычисление скорости ввода
        int numChars = userInput.size();
        double charsPerSecond = numChars / elapsed_seconds.count();
        double charsPerMinute = charsPerSecond * 60;

        system("cls");

        // Дополнительно: Проверка правильности введенного текста
        if (userInput == testText[count]) {
            std::cout << "Congratulations! You typed it correctly.\n";
        } else {
            std::cout << "There were some errors in your typing.\n";
        }   

        std::cout << "Time taken: " << elapsed_seconds.count() << " seconds\n";
        std::cout << "Characters per minute: " << charsPerMinute << "\n\n";

        if (count == 3) {
            count = 0;
        } else {
            count++;
        }
    }
    return 0;
}