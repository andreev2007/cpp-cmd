#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  while (true) {
	std::cout << "$ ";
	std::string userCommand;

	std::getline(std::cin >> std::ws, userCommand);

	if (userCommand == "exit") {
		break;
	}

	std::cout << userCommand << ": command not found" << std::endl;
  }
  return 0;
}
