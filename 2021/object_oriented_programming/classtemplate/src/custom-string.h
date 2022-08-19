#pragma once

#include <cstring>
#include <iostream>

using namespace std;

class CustomString {

  // Prototype for stream insertion
  friend ostream &operator<<(ostream &os, const CustomString &obj);

  // Prototype for stream extraction
  friend istream &operator>>(istream &is, CustomString &obj);

  // Prototype for '+'
  // operator overloading
  friend CustomString operator+(const CustomString &lhs,
                                const CustomString &rhs);
  char *str;

public:
  // No arguments constructor
  CustomString();

  // pop_back() function
  void pop_bk();

  // push_back() function
  void push_bk(char a);

  // To get the length
  int get_length();

  // Function to copy the string
  // of length len from position pos
  void copy(char s[], int len, int pos);

  // Swap strings function
  void swp(CustomString &rhs);

  // Constructor with 1 arguments
  CustomString(char *val);

  // Copy Constructor
  CustomString(const CustomString &source);

  // Move Constructor
  CustomString(CustomString &&source);

  // Overloading the assignment
  // operator
  CustomString &operator=(const CustomString &rhs);

  // Destructor
  ~CustomString() { delete str; }
};
