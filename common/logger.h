#pragma once
#include <initializer_list>
#include <iostream>
#include <string>
// TODO do isaty(3) test?
namespace logger {
namespace {
const std::string rest = "\x1B[0m";
const std::string red = "\x1B[31m";
const std::string green = "\x1B[32m";
const std::string yellow = "\x1B[33m";
const std::string blue = "\x1B[34m";
const std::string magenta = "\x1B[35m";
const std::string cyan = "\x1B[36m";
const std::string white = "\x1B[37m";

template <typename T>
void log(const T& t) {
  std::cout << t << rest << '\n';
}

template <typename T, typename... Args>
void log(const T& t, const Args&... args)  // recursive variadic function
{
  std::cout << t;

  log(args...);
}
}

template <typename T, typename... Args>
//TODO comment
void info(const T& t, const Args&... args)
{
  std::cout << white << "[INFO]    ";

  log(t, args...);
}

template <typename T, typename... Args>
//TODO comment
void warning(const T& t, const Args&... args)
{
  std::cout << yellow << "[WARNING] ";

  log(t, args...);
}

template <typename T, typename... Args>
//TODO comment
void error(const T& t, const Args&... args) 
{
  std::cout << red << "[ERROR]   ";

  log(t, args...);
}
}
