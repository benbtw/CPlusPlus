#include <iostream>
#include <string>
#include <fstream>
#include "accFile.cpp"

int main(){
    std::ifstream accounts ("accounts.txt");
    std::ofstream acc_write ("accounts.txt", std::ios::app);
    std::string userInput;
    accFile file;
    if(accounts.is_open()){
        system("cls");
        std::cout << "Do you have an account with us already? ";
        std::cin >> userInput;
        if(userInput == "yes") {
            file.readFile(accounts);
            file.logIn(accounts);
        } else {
            file.Register(accounts,acc_write);
            file.readFile(accounts);
            file.logIn(accounts);
        }
    } else {
        std::cout << "file not opened";
    }

    accounts.close();
}