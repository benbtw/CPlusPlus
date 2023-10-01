#include <iostream>
#include <stack>
#include <sstream>

class testing {
    public:
    int number = 20;

    void increase_num(){
        for(int i = 0; i < 20; i++){
            number++;
        }
    }

};

int main() {
    testing test;
    std::cout << test.number << "\n";
    test.increase_num();
    std::cout << test.number << "\n";
}