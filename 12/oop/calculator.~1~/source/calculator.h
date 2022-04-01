#include "button.h"

#include <QLineEdit>
#include <QWidget>

class Calculator : public QWidget {
  Q_OBJECT

public:
  Calculator(QWidget *parent = nullptr);

private slots:
  void digitClicked();
  void unaryOperatorClicked();
  void additiveOperatorClicked();
  void multiplicativeOperatorClicked();
  void equalClicked();
  void pointClicked();
  void changeSignClicked();
  void backspaceClicked();
  void clear();
  void clearAll();
  void clearMemory();
  void readMemory();
  void setMemory();
  void addToMemory();

private:
  QLineEdit *display;

  QString pendingAdditiveOperator;
  QString pendingMultiplicativeOperator;

  enum { NumDigitButtons = 10 };

  Button *digitButtons[NumDigitButtons];
  Button *createButton(const QString &text, const char *member);

  void abortOperation();
  bool calculate(double rightOperand, const QString &pendingOperator);

  double sumInMemory;
  double sumSoFar;
  double factorSoFar;

  bool waitingForOperand;
};
