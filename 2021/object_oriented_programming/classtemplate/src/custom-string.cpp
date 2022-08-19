#include "custom-string.h"

// Overloading the assignment operator
CustomString &CustomString::operator=(const CustomString &rhs) {
  if (this == &rhs)
    return *this;
  delete[] str;
  str = new char[strlen(rhs.str) + 1];
  strcpy(str, rhs.str);
  return *this;
}

// Overloading the plus operator
CustomString operator+(const CustomString &lhs, const CustomString &rhs) {
  int length = strlen(lhs.str) + strlen(rhs.str);

  char *buff = new char[length + 1];

  // Copy the strings to buff[]
  strcpy(buff, lhs.str);
  strcat(buff, rhs.str);
  buff[length] = '\0';

  // String temp
  CustomString temp{buff};

  // delete the buff[]
  delete[] buff;

  // Return the concatenated string
  return temp;
}
// Overloading the stream
// extraction operator
istream &operator>>(istream &is, CustomString &obj) {
  char *buff = new char[1000];
  memset(&buff[0], 0, sizeof(buff));
  is >> buff;
  obj = CustomString{buff};
  delete[] buff;
  return is;
}

// Overloading the stream
// insertion operator
ostream &operator<<(ostream &os, const CustomString &obj) {
  os << obj.str;
  return os;
}

// Function for swapping string
void CustomString::swp(CustomString &rhs) {
  CustomString temp{rhs};
  rhs = *this;
  *this = temp;
}

// Function to copy the string
void CustomString::copy(char s[], int len, int pos) {
  for (int i = 0; i < len; i++) {
    s[i] = str[pos + i];
  }
  s[len] = '\0';
}

// Function to implement push_bk
void CustomString::push_bk(char a) {
  // Find length of string
  int length = strlen(str);

  char *buff = new char[length + 2];

  // Copy character from str
  // to buff[]
  for (int i = 0; i < length; i++) {
    buff[i] = str[i];
  }
  buff[length] = a;
  buff[length + 1] = '\0';

  // Assign the new string with
  // char a to string str
  *this = CustomString{buff};

  // Delete the temp buff[]
  delete[] buff;
}

// Function to implement pop_bk
void CustomString::pop_bk() {
  int length = strlen(str);
  char *buff = new char[length];

  // Copy character from str
  // to buff[]
  for (int i = 0; i < length - 1; i++)
    buff[i] = str[i];
  buff[length - 1] = '\0';

  // Assign the new string with
  // char a to string str
  *this = CustomString{buff};

  // delete the buff[]
  delete[] buff;
}

// Function to implement get_length
int CustomString::get_length() { return strlen(str); }

// Function to illustrate Constructor
// with no arguments
CustomString::CustomString() : str{nullptr} {
  str = new char[1];
  str[0] = '\0';
}

// Function to illustrate Constructor
// with one arguments
CustomString::CustomString(char *val) {
  if (val == nullptr) {
    str = new char[1];
    str[0] = '\0';
  }

  else {

    str = new char[strlen(val) + 1];

    // Copy character of val[]
    // using strcpy
    strcpy(str, val);
    str[strlen(val)] = '\0';
  }
}

// Function to illustrate
// Copy Constructor
CustomString::CustomString(const CustomString &source) {
  str = new char[strlen(source.str) + 1];
  strcpy(str, source.str);
}

// Function to illustrate
// Move Constructor
CustomString::CustomString(CustomString &&source) {
  str = source.str;
  source.str = nullptr;
}
