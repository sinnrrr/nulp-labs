#include "widget.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>

template <typename T> std::string to_str(std::vector<T> &vec) {
  std::ostringstream oss;
  if (!vec.empty()) {
    std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<T>(oss, ", "));
    oss << vec.back();
  }
  return oss.str();
}

auto random_boolean = std::bind(std::uniform_int_distribution<>(0, 1),
                                std::default_random_engine());

std::string random_string(size_t length) {
  auto randchar = []() -> char {
    const char charset[] = "0123456789"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = (sizeof(charset) - 1);
    return charset[rand() % max_index];
  };
  std::string str(length, 0);
  std::generate_n(str.begin(), length, randchar);
  return str;
}

struct filterChars {
  bool operator()(const char *s) { return strstr(s, "a") == s; }
};

void Widget::on_start() {
  map.empty();
  vector.clear();
  vector2.clear();

  for (auto i = 0; i < 10; i++) {
    vector.push_back(random_string(10).c_str());
    vector2.push_back(random_string(10).c_str());
  }
  this->output_1->setMarkdown(
      QString("### Vector1:\n%1").arg(QString::fromStdString(to_str(vector))));

  vector.erase(vector.begin() + 2, vector.begin() + 7);
  vector.at(3) = "Dima";
  vector.insert(vector.end(), vector2.begin(), vector2.end());
  std::sort(vector.begin(), vector.end(),
            [](const char *c1, const char *c2) { return strcmp(c1, c2) < 0; });
  auto find_res = std::find_if(vector.begin(), vector.end(), filterChars());

  this->output_2->setMarkdown(QString("### Vector1 sorted desc:\n%1"
                                      "\n### Vector2:\n%2"
                                      "\n### Find result:\n%3")
                                  .arg(QString::fromStdString(to_str(vector)))
                                  .arg(QString::fromStdString(to_str(vector2)))
                                  .arg(QString(*find_res))

  );

  std::for_each(vector.begin(), vector.end(), [this](const char *s) {
    if (filterChars()(s)) {
      map.insert({s, random_boolean()});
    }
  });

  std::vector<const char *> vector_from_map;
  for (auto el : map) {
    vector_from_map.push_back(el.first);
  }
  std::sort(vector.begin(), vector.end());
  std::sort(vector_from_map.begin(), vector_from_map.end());

  this->output_3->setMarkdown(
      QString("### Vector1 sorted asc:\n%1"
              "\n### Map1 sorted asc:\n%2")
          .arg(QString::fromStdString(to_str(vector)))
          .arg(QString::fromStdString(to_str(vector_from_map))));

  std::vector<const char *> merged_vector(vector.size() +
                                          vector_from_map.size());
  std::merge(vector.begin(), vector.end(), vector_from_map.begin(),
             vector_from_map.end(), merged_vector.begin());

  int count =
      std::count_if(merged_vector.begin(), merged_vector.end(), filterChars());
  this->output_4->setMarkdown(
      QString("### Merged vector:\n%1"
              "\n### %2 elements satisfy filter")
          .arg(QString::fromStdString(to_str(merged_vector)))
          .arg(QString::number(count)));
}

Widget::Widget(QWidget *parent) : QWidget(parent) {
  auto *main_layout = new QGridLayout;

  this->start_btn = new QPushButton("Start");

  this->output_1 = new QTextEdit;
  this->output_2 = new QTextEdit;
  this->output_3 = new QTextEdit;
  this->output_4 = new QTextEdit;

  main_layout->addWidget(this->output_1, 0, 0);
  main_layout->addWidget(this->output_2, 0, 1);
  main_layout->addWidget(this->output_3, 1, 0);
  main_layout->addWidget(this->output_4, 1, 1);
  main_layout->addWidget(this->start_btn, 2, 0, 1, 2);

  connect(this->start_btn, &QPushButton::released, this, &Widget::on_start);

  setLayout(main_layout);
}
