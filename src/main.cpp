#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <cstdlib>
#include <limits.h>

#ifdef _WIN32
const bool isWin = true;
#else
const bool isWin = false;
#endif

class Command {
private:
	std::string userCommand;
	const std::vector<std::string> commands {"echo", "type", "exit"};

public:
	Command() {
		std::getline(std::cin >> std::ws, userCommand);
	};

	int iterateThroughPath(bool execute = false) {
		std::string pathEnv = std::getenv("PATH");

		std::stringstream ssPath(pathEnv);

		std::string path;
		bool found{ false };
		char pathSep = isWin ? ';' : ':';

		while (std::getline(ssPath, path, pathSep)) {
			if (path.empty()) continue;

			try {
				std::filesystem::path dirPath(path);
				std::size_t firstSpacePos = userCommand.find(' ');

				for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
					std::string formattedString = firstSpacePos != std::string::npos ? userCommand.substr(0, firstSpacePos) : userCommand;

					if (entry.is_regular_file() && entry.path().filename().string() == formattedString) {
						found = true;
						
						// Execute file if passed flag
						if (execute) {
							if (isWin) {
								system(("start \"\" \"" + entry.path().string() + "\" " + userCommand.erase(0, firstSpacePos)).c_str());
							}
							else {
								system(entry.path().string().c_str());
							}
						}
						else {
							std::cout << userCommand << " is " << entry.path().string() << std::endl;
						}

						break;
					}
				}
			}
			catch (const std::filesystem::filesystem_error& e) {}
			if (found) break;
		}

		if (!found) {
			std::cout << userCommand << ": not found" << std::endl;
		}
		return found;
	}

	int execute() {
		std::stringstream ss(userCommand);

		if (userCommand == "exit") {
			return 1;
		}

		std::string firstWord;
		ss >> firstWord;

		size_t space_pos = userCommand.find(' ');
		bool hasPos = space_pos != std::string::npos;

		if (hasPos && firstWord == "echo") {
			userCommand.erase(0, space_pos + 1);
			std::cout << userCommand << std::endl;
		}

		else if (hasPos && firstWord == "type") {
			userCommand.erase(0, space_pos + 1);
			auto it = std::find(commands.begin(), commands.end(), userCommand);

			if (it != commands.end()) {
				std::cout << userCommand << " is a shell builtin" << std::endl;
			}
			else {
				this->iterateThroughPath();
			}
		}
		else {
			iterateThroughPath(true);
		}
		return 0;
	}
};

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  while (true) {
	std::cout << "$ ";
	Command* command = new Command();
	int executionStatus = command->execute();
	if (executionStatus) {
		break;
	}
  }
  return 0;
}
