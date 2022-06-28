#include <string>

using std::string;

class Plane {
public:
  int id;
  string name;
  time_t departs_at;
  time_t arrives_at;
};

class Human {
public:
  string name;
  int age;
};

class Passenger : Human {
public:
  int planes_taken;
  void ask_for_plane();

  Plane *planes;
};

class Income {
public:
  float amount;
  float calculate_income();
};

class System {
public:
  Human *people;
  Plane *planes;
  Income income;
  string location;
};
