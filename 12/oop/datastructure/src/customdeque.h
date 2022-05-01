#include "deque.h"

#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QTableWidget>

class CustomDeque : public Deque {
public:
  const double getMaxValue();
  const double getMinValue();
  const double getAverageValue();

  void operator=(const CustomDeque &);

  friend void operator>>(QListWidget *, CustomDeque &);
  friend void operator<<(QListWidget *, CustomDeque &);
  friend void operator>>(QLineEdit *, CustomDeque &);
  friend void operator>>(CustomDeque &, QLineEdit *);
  friend void operator+(double, CustomDeque &);
  friend void operator+(CustomDeque &, double);
  friend void operator-(CustomDeque &, Node *);
  friend void operator-(Node *, CustomDeque &);
};
