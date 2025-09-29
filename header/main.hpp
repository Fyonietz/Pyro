#pragma once
#define MAIN
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
template <typename... Args> void print(Args &&...args) {
  (std::cout << ... << args) << std::endl;
}

void init();
void build();
