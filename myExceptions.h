#pragma once
// exception classes for various error types

#include <iostream>
#include <string>

// illegal parameter value
class illegalParameterValue {
 public:
  illegalParameterValue(std::string theMessage = "Illegal parameter value") {
    message = theMessage;
  }
  void outputMessage() { std::cout << message << std::endl; }

 private:
  std::string message;
};

// illegal input data
class illegalInputData {
 public:
  illegalInputData(std::string theMessage = "Illegal data input") {
    message = theMessage;
  }
  void outputMessage() { std::cout << message << std::endl; }

 private:
  std::string message;
};

// illegal index
class illegalIndex {
 public:
  illegalIndex(std::string theMessage = "Illegal index") {
    message = theMessage;
  }
  void outputMessage() { std::cout << message << std::endl; }

 private:
  std::string message;
};
