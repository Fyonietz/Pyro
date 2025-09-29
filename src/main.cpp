#include "main.hpp"
#include <ostream>
#include <regex>
#include <sstream>
#include <string>

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

void build(){
  
}

int main(int argc, char *argv[]) {
  init();
  return 0;
}
