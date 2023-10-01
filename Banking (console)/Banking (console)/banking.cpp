#include "bank_sql.h"
#include "banking.h"

void Banking::main_menu() {
	std::cout << "--------------------\n";
	std::cout << "|    C++ Banking   |\n";
	std::cout << "--------------------\n";
	std::cout << "1. Log-in\n";
	std::cout << "2. Register\n";
	std::cout << "3. Exit\n";
	std::cin >> user;
	if (user == "1")
		log_in();
	else if (user == "2")
		create_acc();
}

void Banking::log_in() {
	std::cout << "Login\n";
}

void Banking::create_acc() {
	std::cout << "create acc\n";
}