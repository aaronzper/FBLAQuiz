#include "quizgeneration.h"
#include <iostream>
#include <string>

// Make a function for this since I'm too lazy to call std::getline() every time
std::string readline() {
	std::string out;
	std::getline(std::cin, out);
	return out;
}	

void generateQuiz() {
	while(1) {
		std::cout << std::endl;
		std::cout << "[a]dd a question\n";
		std::cout << "[l]ist all questions\n";
		std::cout << "[e]dit a question\n";
		std::cout << "[r]emove a question\n";
		std::cout << "[s]ave to file\n";
		std::cout << "[q]uit\n";
		std::cout << "Enter a command: ";
		
		std::string command = readline();
		command = command[0];
		
		if(command == "q") {
			while(1) {
				std::cout << "Are you sure? Any unsaved changes will be lost! ([y]es/[n]o)";
				std::string quit_confirm = readline();
				
				if(quit_confirm == "y" || quit_confirm == "Y") {
					return;
				}
				
				if(quit_confirm == "n" || quit_confirm == "N") {
					break;
				}
			}
		}
	}
}
