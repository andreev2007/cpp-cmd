#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <cstdlib>

class Command {
private:
	std::string userCommand;
	const std::vector<std::string> commands {"echo", "type", "exit"};

public:
	Command() {
		std::getline(std::cin >> std::ws, userCommand);
	};

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
				std::string pathEnv = std::getenv("PATH");

				std::stringstream ssPath(pathEnv);

				std::string path;
				bool found{ false };

				while (std::getline(ssPath, path, ':')) {
					if (path.empty()) continue;

					try {
						std::filesystem::path dirPath(path);

						for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
							if (entry.is_regular_file() && entry.path().filename().string() == userCommand) {
								auto perms = std::filesystem::status(entry.path()).permissions();
								if ((perms & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ||
									(perms & std::filesystem::perms::group_exec) != std::filesystem::perms::none ||
									(perms & std::filesystem::perms::others_exec) != std::filesystem::perms::none) {
									std::cout << userCommand << " is " << entry.path().string() << std::endl;
									found = true;
									break;
								}
							} 
						}
						if (found) break;
					}
					catch (const std::filesystem::filesystem_error& e) {}
				}

				if (!found) {
					std::cout << userCommand << ": not found" << std::endl;
				}
			}
		}
		else {
			std::string pathEnv = std::getenv("PATH");
			std::stringstream ssPath(pathEnv);

			std::string path;
			bool found = false;
			while (std::getline(ssPath, path, ':')) {
				if (path.empty()) continue;

				std::string fullPath = path + '/' + userCommand;
				if (std::filesystem::exists(fullPath)) {
					std::cout << userCommand << " is " << fullPath << std::endl;
					found = true;
					break;
				}
			}

			if (!found) {
				std::cout << userCommand << ": command not found" << std::endl;
			}
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
