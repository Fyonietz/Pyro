#include "main.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <regex>
#include <sstream>
#include <string>
#include <system_error>
#include <unordered_map>

void init() {
  std::fstream file("CMakeLists.txt");
  if (!file.is_open()) {
    std::cerr << "CMakeLists.txt Should Be Created.";
  }
  std::regex pattern(R"(project\(([^)]+)\))");

  std::ostringstream ss;
  ss << file.rdbuf();
  std::string CMake = ss.str();

  auto words_begin = std::sregex_iterator(CMake.begin(), CMake.end(), pattern);
  auto words_end = std::sregex_iterator();

  std::smatch match;
  std::string value;
  for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
    match = *i;
    value = match[1].str();
    print(value);
  }
  std::string create = "project = " + value;
  std::ofstream config("pyro.conf");

  config << create;
}
std::string parser() {
  std::ifstream config_file("pyro.conf");
  if (!config_file) {
    std::cerr << "pyro.conf is missing!";
  }
  std::unordered_map<std::string, std::string> config;
  std::string line;

  while (std::getline(config_file, line)) {
    size_t start = line.find_first_not_of(" \t");
    size_t end = line.find_last_not_of(" \t");
    if (start == std::string::npos)
      continue;

    line = line.substr(start, end - start + 1);

    if (line.empty() || line[0] == '#')
      continue;
    size_t eqPos = line.find('=');
    if (eqPos == std::string::npos)
      continue;

    std::string key = line.substr(0, eqPos);
    std::string value = line.substr(eqPos + 1);

    size_t key_start = key.find_first_not_of(" \t");
    size_t key_end = key.find_last_not_of(" \t");
    key = key.substr(key_start, key_end - key_start + 1);

    // Trim spaces around value
    size_t val_start = value.find_first_not_of(" \t");
    size_t val_end = value.find_last_not_of(" \t");
    value = value.substr(val_start, val_end - val_start + 1);

    // Store in map
    config[key] = value;
  }

  std::string project_name = config["project"];

  return project_name;
}
void build() {
  // Starting Building
  int result = 0;
  result = system("cmake -S . -B build");
  if (result != 0) {
    std::cerr << "Failed:CMake Configuration\n";
  }
  result = system("cmake --build build");
  if (result != 0) {
    std::cerr << "Failed:CMake Build\n";
  }
  std::string project_name = std::move(parser());
  std::string project_name_execute = "./" + project_name + "";
  result = system(project_name_execute.c_str());
  if (result != 0) {
    std::cerr << "Failed\n";
  }
}
void start() {
  std::string project_name = std::move(parser());
  std::string project_name_execute = "./" + project_name + "";
  system(project_name_execute.c_str());
}
void version() { print("0.1"); }
int main(int argc, char *argv[]) {
  std::unordered_map<std::string, void (*)()> command_lists = {
      {"init", init}, {"build", build}, {"run", start}, {"--version", version}};
  if (argc > 1) {
    std::string input = argv[1];

    // Check if command exists in the map
    if (command_lists.find(input) != command_lists.end()) {
      command_lists[input](); // Call the corresponding function
    } else {
      std::cout << "Unknown command: " << input << std::endl;
    }
  } else {
    std::cout << "No command provided."
              << "DIR: " << std::filesystem::current_path() << std::endl;
  }
  return 0;
}
