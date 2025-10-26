#pragma once
#define MAIN
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
template <typename... Args> void print(Args &&...args) {
  (std::cout << ... << args) << std::endl;
}

void init(const std::string &);
void build(const std::string &);
std::string parser(const std::string &);
void start(const std::string &);
void start_with_argument(const std::string &args);
