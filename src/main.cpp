#include <iostream>
#include <string>
#include <sstream>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  while (true) {
	std::cout << "$ ";
	std::string userCommand;

	std::getline(std::cin >> std::ws, userCommand);

	std::stringstream ss(userCommand);

	if (userCommand == "exit") {
		break;
	}

	std::string firstWord;
	ss >> firstWord;

	size_t space_pos = userCommand.find(' ');

	if (space_pos != std::string::npos && firstWord == "echo") {
		userCommand.erase(0, space_pos + 1);
		std::cout << userCommand << std::endl;
	}
	else {
		std::cout << userCommand << ": command not found" << std::endl;
	}
  }
  return 0;
}
