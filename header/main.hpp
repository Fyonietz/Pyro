#pragma once
#define MAIN
#include <any>
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

void init();
void build();
std::string parser();
void start();
