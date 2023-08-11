#include <iostream>
#include <string>
#include <fstream>
#include <map>

class accFile {
    
    std::map<std::string, std::string> acc;
    std::string userName;
    std::string passWord;
    std::string user;
    bool logged = false;
    bool valid = false;

    public:
    void readFile(std::ifstream& stream){
        while(stream >> userName >> passWord) {
            acc[userName] = passWord;
        }
    }
    void Register(std::ifstream& stream, std::ofstream& writeToFile){
        
        std::cout << "Create a username: ";
        std::cin >> user;
        writeToFile << user << " ";
        std::cout << "Create a password: ";
        std::cin >> user;
        writeToFile << user << std::endl;
        std::cout << "Account created" << std::endl;
    }

    void logIn(std::ifstream& stream){
        while(!logged) {
            std::cout << "Enter username: ";
            std::cin >> userName;
            for(auto& elem : acc) {
                if (elem.first == userName)
                    valid = true;
            }
            while(valid) {
                std::cout << "Enter password: ";
                std::cin >> passWord;
                for(auto& elem : acc) {
                    if(elem.second == passWord)
                        valid = false;
                        logged = true;
                }
            }
        }
        std::cout << "Log-in Success!";
    }

};