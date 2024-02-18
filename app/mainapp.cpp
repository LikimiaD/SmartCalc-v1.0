#include "mainapp.h"

#include "credit.h"
#include "deposit.h"
#include "graphwindow.h"
#include "ui_mainapp.h"

QString MainApp::replaceXWithValue(QString& expression, double value) {
  QString tempExpression = expression;
  QString valueStr = QString::number(value, 'f', 15);
  tempExpression.replace(QRegularExpression("\\bx\\b"), valueStr);
  return tempExpression;
}

MainApp::MainApp(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainApp) {
  ui->setupUi(this);
}

MainApp::~MainApp() { delete ui; }

void MainApp::setStyle() {
  ui->app->setStyleSheet(BACKGROUND_CSS);
  ui->menu->setStyleSheet(MENU_BACKGROUND_CSS);
  ui->inputBox->setStyleSheet(INPUT_CSS);
  ui->answerBox->setStyleSheet(ANSWER_CSS);

  ui->cosButton->setStyleSheet(COMMAND_CSS);
  ui->sinButton->setStyleSheet(COMMAND_CSS);
  ui->tanButton->setStyleSheet(COMMAND_CSS);
  ui->acosButton->setStyleSheet(COMMAND_CSS);
  ui->asinButton->setStyleSheet(COMMAND_CSS);
  ui->atanButton->setStyleSheet(COMMAND_CSS);
  ui->sqrtButton->setStyleSheet(COMMAND_CSS);
  ui->modButton->setStyleSheet(COMMAND_CSS);
  ui->lnButton->setStyleSheet(COMMAND_CSS);
  ui->logButton->setStyleSheet(COMMAND_CSS);

  ui->delButton->setStyleSheet(DEFAULT_COMMAND_CSS);
  ui->umButton->setStyleSheet(DEFAULT_COMMAND_CSS);
  ui->plusButton->setStyleSheet(DEFAULT_COMMAND_CSS);
  ui->minusButton->setStyleSheet(DEFAULT_COMMAND_CSS);
  ui->plusButton_2->setStyleSheet(DEFAULT_COMMAND_CSS);

  ui->resetButton->setStyleSheet(AC_DOT_CSS);
  ui->dotButton->setStyleSheet(AC_DOT_CSS);
  ui->openBracketButton->setStyleSheet(AC_DOT_CSS);
  ui->closeBracketButton->setStyleSheet(AC_DOT_CSS);
  ui->xButton->setStyleSheet(AC_DOT_CSS);

  ui->oneButton->setStyleSheet(NUM_CSS);
  ui->twoButton->setStyleSheet(NUM_CSS);
  ui->threeButton->setStyleSheet(NUM_CSS);
  ui->fourButton->setStyleSheet(NUM_CSS);
  ui->fiveButton->setStyleSheet(NUM_CSS);
  ui->sixButton->setStyleSheet(NUM_CSS);
  ui->sevenButton->setStyleSheet(NUM_CSS);
  ui->eightButton->setStyleSheet(NUM_CSS);
  ui->nineButton->setStyleSheet(NUM_CSS);
  ui->zeroButton->setStyleSheet(NUM_CSS);

  ui->equalButton->setStyleSheet(EQUAL_CSS);
  ui->depositButton->setStyleSheet(COMMAND_CSS);
  ui->creditButton->setStyleSheet(COMMAND_CSS);
}
void MainApp::addValue(QChar sym) {
  int cursorPosition = ui->inputBox->cursorPosition();
  QString currentText = ui->inputBox->text();

  if (currentText == "0" ||
      (currentText.endsWith('0') && currentText.contains('.'))) {
    if (!currentText.contains('.')) {
      currentText += '.';
      cursorPosition++;
    }
    currentText += sym;
    cursorPosition++;
  } else if (currentText.endsWith('x')) {
    currentText += '*';
    currentText += sym;
    cursorPosition += 2;
  } else {
    currentText += sym;
    cursorPosition++;
  }
  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(cursorPosition);
}

void MainApp::on_oneButton_clicked() { addValue('1'); }

void MainApp::on_twoButton_clicked() { addValue('2'); }

void MainApp::on_threeButton_clicked() { addValue('3'); }

void MainApp::on_fourButton_clicked() { addValue('4'); }

void MainApp::on_fiveButton_clicked() { addValue('5'); }

void MainApp::on_sixButton_clicked() { addValue('6'); }

void MainApp::on_sevenButton_clicked() { addValue('7'); }

void MainApp::on_eightButton_clicked() { addValue('8'); }

void MainApp::on_nineButton_clicked() { addValue('9'); }

void MainApp::on_zeroButton_clicked() { addValue('0'); }

void MainApp::on_resetButton_clicked() {
  ui->inputBox->setText("");
  ui->inputBox->setCursorPosition(0);
  ui->answerBox->setText("");
}

void MainApp::on_dotButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();
  bool leftIsX = cursorPosition > 0 && currentText[cursorPosition - 1] == 'x';
  int start = cursorPosition - 1;
  while (start >= 0 &&
         (currentText[start].isDigit() || currentText[start] == '.' ||
          currentText[start] == 'x')) {
    --start;
  }
  int end = cursorPosition;
  while (end < currentText.length() &&
         (currentText[end].isDigit() || currentText[end] == '.')) {
    ++end;
  }
  bool containsDot = currentText.mid(start + 1, end - start - 1).contains('.');

  if (!containsDot) {
    if (leftIsX) {
      currentText.insert(cursorPosition, "*0.");
      cursorPosition += 3;
    } else if (currentText.isEmpty() ||
               !currentText[cursorPosition - 1].isDigit()) {
      currentText += "0.";
      cursorPosition += 2;
    } else {
      currentText.insert(cursorPosition, '.');
      cursorPosition += 1;
    }
    ui->inputBox->setText(currentText);
    ui->inputBox->setCursorPosition(cursorPosition);
  }
}

void MainApp::on_umButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (charToLeft.isDigit() || charToLeft == ')' || charToLeft == 'x') {
      currentText.insert(cursorPosition, '*');
      ui->inputBox->setText(currentText);
      ui->inputBox->setCursorPosition(cursorPosition + 1);
    }
  }
}

void MainApp::on_equalButton_clicked() {
  QString inputText = ui->inputBox->text();

  if (inputText.contains('x')) {
    QVector<QPointF> data;
    for (double x = -100; x <= 100; x += 0.25) {
      QString modifiedOutput = replaceXWithValue(inputText, x);
      QByteArray byteArray = modifiedOutput.toUtf8();
      char* cString = byteArray.data();

      StackChar* stack = createStackChar(MAX_LEN);
      char output[MAX_LEN] = {0};
      readString(cString, stack, output);

      double y = parsePoland(output);
      y = std::max(-1e6, std::min(1e6, y));
      data.append(QPointF(x, y));

      destroyStackChar(stack);
    }

    GraphWindow* window = new GraphWindow();
    window->setPlotData(data);
    window->resize(800, 800);
    window->show();
    ui->answerBox->setText("GRAPH");
  } else {
    int openBrackets = inputText.count('(');
    int closeBrackets = inputText.count(')');

    for (int i = closeBrackets; i < openBrackets; i++) {
      inputText += ')';
    }

    QByteArray byteArray = inputText.toUtf8();
    char* cString = byteArray.data();

    StackChar* stack = createStackChar(MAX_LEN);
    char output[MAX_LEN] = {0};

    readString(cString, stack, output);

    double answer = parsePoland(output);
    if (isnan(answer)) {
      ui->answerBox->setText("ERROR");
    } else {
      ui->answerBox->setText(QString::number(answer));
    }

    destroyStackChar(stack);
  }
}

void MainApp::on_delButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (charToLeft.isDigit() || charToLeft == ')') {
      currentText.insert(cursorPosition, '/');
      ui->inputBox->setText(currentText);
      ui->inputBox->setCursorPosition(cursorPosition + 1);
    }
  }
}

void MainApp::on_xButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();
  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];
    if ((charToLeft.isDigit() || charToLeft == '(' || charToLeft == '^' ||
         charToLeft == '*' || charToLeft == '+' || charToLeft == '-' ||
         charToLeft == '/') &&
        charToLeft != 'x' && charToLeft != ')') {
      if (charToLeft.isDigit()) {
        currentText.insert(cursorPosition, "*x");
      } else {
        currentText.insert(cursorPosition, 'x');
      }
      ui->inputBox->setCursorPosition(cursorPosition + 2);
    }
  } else {
    currentText.insert(cursorPosition, 'x');
  }
  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(cursorPosition + 1);
}

void MainApp::on_openBracketButton_clicked() { addValue('('); }

void MainApp::on_closeBracketButton_clicked() {
  QString currentText = ui->inputBox->text();

  int openBrackets = 0;
  int closeBrackets = 0;

  for (int i = 0; i < currentText.length(); ++i) {
    if (currentText[i] == '(') {
      ++openBrackets;
    } else if (currentText[i] == ')') {
      ++closeBrackets;
    }
  }

  if (openBrackets > closeBrackets) {
    currentText += ')';
    ui->inputBox->setText(currentText);
  }
}

void MainApp::on_modButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  int startPos = cursorPosition - 1;
  while (startPos >= 0 &&
         (currentText[startPos].isDigit() || currentText[startPos] == '.' ||
          currentText[startPos] == 'x')) {
    --startPos;
  }
  ++startPos;

  if (startPos < cursorPosition) {
    QString modifiedText =
        currentText.left(startPos) + "mod(" +
        currentText.mid(startPos, cursorPosition - startPos) + ", " +
        currentText.mid(cursorPosition);
    ui->inputBox->setText(modifiedText);
    ui->inputBox->setCursorPosition(startPos + 4 + (cursorPosition - startPos) +
                                    1);
  }
}

void MainApp::on_cosButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (charToLeft.isDigit() || charToLeft == ')' || charToLeft == 'x') {
      currentText.insert(cursorPosition, "*cos(");
    } else {
      currentText.insert(cursorPosition, "cos(");
    }
  } else {
    currentText += "cos(";
  }

  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(
      cursorPosition + 4 +
      (cursorPosition > 0 && currentText[cursorPosition - 1].isDigit() ? 1
                                                                       : 0));
}

void MainApp::on_sinButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (charToLeft.isDigit() || charToLeft == ')' || charToLeft == 'x') {
      currentText.insert(cursorPosition, "*sin(");
    } else {
      currentText.insert(cursorPosition, "sin(");
    }
  } else {
    currentText += "sin(";
  }

  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(
      cursorPosition + 4 +
      (cursorPosition > 0 && currentText[cursorPosition - 1].isDigit() ? 1
                                                                       : 0));
}

void MainApp::on_tanButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (charToLeft.isDigit() || charToLeft == ')' || charToLeft == 'x') {
      currentText.insert(cursorPosition, "*tan(");
    } else {
      currentText.insert(cursorPosition, "tan(");
    }
  } else {
    currentText += "tan(";
  }

  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(
      cursorPosition + 4 +
      (cursorPosition > 0 && currentText[cursorPosition - 1].isDigit() ? 1
                                                                       : 0));
}

void MainApp::on_acosButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (charToLeft.isDigit() || charToLeft == ')' || charToLeft == 'x') {
      currentText.insert(cursorPosition, "*acos(");
    } else {
      currentText.insert(cursorPosition, "acos(");
    }
  } else {
    currentText += "acos(";
  }

  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(
      cursorPosition + 5 +
      (cursorPosition > 0 && currentText[cursorPosition - 1].isDigit() ? 1
                                                                       : 0));
}

void MainApp::on_asinButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (charToLeft.isDigit() || charToLeft == ')' || charToLeft == 'x') {
      currentText.insert(cursorPosition, "*asin(");
    } else {
      currentText.insert(cursorPosition, "asin(");
    }
  } else {
    currentText += "asin(";
  }

  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(
      cursorPosition + 5 +
      (cursorPosition > 0 && currentText[cursorPosition - 1].isDigit() ? 1
                                                                       : 0));
}

void MainApp::on_atanButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (charToLeft.isDigit() || charToLeft == ')' || charToLeft == 'x') {
      currentText.insert(cursorPosition, "*atan(");
    } else {
      currentText.insert(cursorPosition, "atan(");
    }
  } else {
    currentText += "atan(";
  }

  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(
      cursorPosition + 5 +
      (cursorPosition > 0 && currentText[cursorPosition - 1].isDigit() ? 1
                                                                       : 0));
}

void MainApp::on_sqrtButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (charToLeft.isDigit() || charToLeft == ')' || charToLeft == 'x') {
      currentText.insert(cursorPosition, "*sqrt(");
    } else {
      currentText.insert(cursorPosition, "sqrt(");
    }
  } else {
    currentText += "sqrt(";
  }

  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(
      cursorPosition + 5 +
      (cursorPosition > 0 && currentText[cursorPosition - 1].isDigit() ? 1
                                                                       : 0));
}

void MainApp::on_lnButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (charToLeft.isDigit() || charToLeft == ')' || charToLeft == 'x') {
      currentText.insert(cursorPosition, "*ln(");
    } else {
      currentText.insert(cursorPosition, "ln(");
    }
  } else {
    currentText += "ln(";
  }

  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(
      cursorPosition + 3 +
      (cursorPosition > 0 && currentText[cursorPosition - 1].isDigit() ? 1
                                                                       : 0));
}

void MainApp::on_logButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();
  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (charToLeft.isDigit() || charToLeft == ')' || charToLeft == 'x') {
      currentText.insert(cursorPosition, "*log(");
    } else {
      currentText.insert(cursorPosition, "log(");
    }
  } else {
    currentText += "log(";
  }
  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(
      cursorPosition + 4 +
      (cursorPosition > 0 && currentText[cursorPosition - 1].isDigit() ? 1
                                                                       : 0));
}

void MainApp::on_minusButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();
  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];
    if (charToLeft == '+' || charToLeft == '-' || charToLeft == '*' ||
        charToLeft == '/' || charToLeft == '(') {
      currentText.insert(cursorPosition, "(-");
      cursorPosition += 2;
    } else if (charToLeft == ')') {
      currentText.insert(cursorPosition, "*(-");
      cursorPosition += 3;
    } else {
      currentText.insert(cursorPosition, "-");
      cursorPosition += 1;
    }
  } else {
    currentText.insert(cursorPosition, "(-");
    cursorPosition += 2;
  }

  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(cursorPosition);
}

void MainApp::on_plusButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (!(charToLeft == '+' || charToLeft == '-' || charToLeft == '*' ||
          charToLeft == '/' || charToLeft == '(')) {
      currentText.insert(cursorPosition, "+");
      ui->inputBox->setCursorPosition(cursorPosition + 1);
    }
  }
  ui->inputBox->setText(currentText);
}

void MainApp::on_powButton_clicked() {
  QString currentText = ui->inputBox->text();
  int cursorPosition = ui->inputBox->cursorPosition();

  if (cursorPosition > 0) {
    QChar charToLeft = currentText[cursorPosition - 1];

    if (charToLeft.isDigit() || charToLeft == ')' || charToLeft == 'x') {
      currentText.insert(cursorPosition, "^");
    }
  }

  ui->inputBox->setText(currentText);
  ui->inputBox->setCursorPosition(cursorPosition + 1);
}

void MainApp::on_creditButton_clicked() {
  credit creditWindow;
  creditWindow.setModal(true);
  creditWindow.setWindowTitle("Credit Calculator");
  creditWindow.exec();
}

void MainApp::on_depositButton_clicked() {
  deposit depositWindow;
  depositWindow.setModal(true);
  depositWindow.setWindowTitle("Deposit Calculator");
  depositWindow.exec();
}
