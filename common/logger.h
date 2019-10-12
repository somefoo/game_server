#pragma once
#define INFO
#include <initializer_list>
#include <iostream>
#include <string>
// TODO do isaty(3) test?

//We can't void cast the args... argument, so we this nifty #pragma directive
#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wunused-parameter"
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
void verbose(const T& t, const Args&... args)
{
#if defined(VERBOSE)
  std::cout << green << "[VERBOSE] ";

  log(t, args...);
#endif 
}

template <typename T, typename... Args>
//TODO comment
void info(const T& t, const Args&... args)
{
#if defined(VERBOSE) || defined(INFO)
  std::cout << white << "[INFO]    ";

  log(t, args...);
#endif
}

template <typename T, typename... Args>
//TODO comment
void warning(const T& t, const Args&... args)
{
#if defined(VERBOSE) || defined(INFO) || defined(WARNING)
  std::cout << yellow << "[WARNING] ";

  log(t, args...);
#endif
}

template <typename T, typename... Args>
//TODO comment
void error(const T& t, const Args&... args) 
{
#if defined(VERBOSE) || defined(INFO) || defined(WARNING) || defined(ERROR)
  std::cout << red << "[ERROR]   ";

#endif
}
}
#pragma GCC diagnostic pop
