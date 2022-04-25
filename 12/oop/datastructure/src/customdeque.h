#import "deque.h"

#import <QLabel>
#import <QListWidget>
#import <QTableWidget>
#import <QTextEdit>

class CustomDeque : public Deque {
public:
  const auto getMaxValue();
  const auto getMinValue();
  const double averageValue();

  void operator=(const CustomDeque &);

  friend void operator>>(QTableWidget *, CustomDeque &);
  friend void operator<<(QTableWidget *, CustomDeque &);
  friend void operator>>(QListWidget *, CustomDeque &);
  friend void operator<<(QListWidget *, CustomDeque &);
  friend void operator<<(QTextEdit *, CustomDeque &);
  friend void operator<<(QLabel *, CustomDeque &);
  friend void operator+(double, CustomDeque &);
  friend void operator+(CustomDeque &, double);
  friend void operator-(CustomDeque &, Node *);
  friend void operator-(Node *, CustomDeque &);
  friend void operator*(CustomDeque &, double);
};
