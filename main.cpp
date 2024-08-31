#include <iostream>
#include <chrono>  
#include <string>  

int main() {
    const char* clear;

    #ifdef _WIN32
        clear = "cls";
    #else 
        clear = "clear";
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
        std::cout << testText[count] << std::endl;
        for (size_t i = 0; i < testText[count].size(); i++) {
            std::cout << "-";
        }
        std::cout << "\n";

        std::string userInput;
        bool inputCorrect = true;

       
        auto start = std::chrono::steady_clock::now();
        
        std::getline(std::cin, userInput);
        
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        if (userInput == "exit") {
            break;
        }
        
        for (size_t i = 0; i < userInput.size(); i++) {
            if (userInput[i] != testText[count][i] && userInput[i] != ' ') {
                std::cout << "^";
                inputCorrect = false;
            } else {
                std::cout << " ";
            }
        }
        if (userInput.size() < testText[count].size()) {
            std::cout << "^";
            inputCorrect = false;
        }
        
        std::cout << "\n";

        if (inputCorrect == true) {
            int numChars = userInput.size();
            double charsPerSecond = numChars / elapsed_seconds.count();
            double charsPerMinute = charsPerSecond * 60;

            system(clear);

            std::cout << "Time taken: " << elapsed_seconds.count() << " seconds\n";
            std::cout << "Characters per minute: " << charsPerMinute << "\n\n";

            if (count == 10) {
                count = 0;
            } else {
                count++;
            }
        }
    }

    return 0;
}