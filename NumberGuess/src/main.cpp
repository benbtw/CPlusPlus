#include <iostream>
#include <string>
#include <random>

int main()
{
    int max = 0;
    int guess = 0;
    int counter = 0;
    std::cout << "What number would you like to guess up to? ";
    std::cin >> max;
    int number = rand() % max + 1;
    std::cout << "Pick a number between 1 and " << max << std::endl;
    while (true) {
        std::cin >> guess;
        if(guess == number){
            counter += 1;
            std::cout << "Congrats, you win! it took " << counter << " guesses" << std::endl;
            break;
        } else {
            if(guess < number){
                std::cout << "Guess Higher." << std::endl;
                counter += 1;
            }else{
                std::cout << "Guess Lower." << std::endl;
                counter += 1;
            }
        }
    }
}