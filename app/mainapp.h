#ifndef MAINAPP_H
#define MAINAPP_H

#include <QMainWindow>
#include <QRegularExpression>
#include <QString>
#include <algorithm>

extern "C" {
#include "../include/poland_notation.h"
#include "../include/stack_char.h"
#include "../include/stack_double.h"
}

#define BACKGROUND_CSS "background-color: #212327;"
#define MENU_BACKGROUND_CSS                                           \
  "QFrame { background-color: #27292E; border-top-left-radius: 25%; " \
  "border-top-right-radius: 25%; }"
#define INPUT_CSS                                                          \
  "QLineEdit { border-radius: 0px; color: rgb(204, 205, 215); font-size: " \
  "20px; font-weight: 400; line-height: 36px; letter-spacing: 0px; "       \
  "text-align: right; }"
#define ANSWER_CSS                                                         \
  "QLineEdit { border-radius: 0px; color: rgb(255, 255, 255); font-size: " \
  "48px; font-weight: 700; line-height: 60px; letter-spacing: 0px; "       \
  "text-align: right; }"
#define COMMAND_CSS                                                   \
  "QPushButton { box-sizing: border-box; border: 2px solid #808080; " \
  "border-radius: 40px; color: white; }"
#define NUM_CSS \
  "QPushButton { background-color: #27292E; border: 0px; color: white; }"
#define AC_DOT_CSS                                                             \
  "QPushButton { background-color: #27292E; border: 0px; color: rgb(254, 90, " \
  "45); }"
#define DEFAULT_COMMAND_CSS                                               \
  "QPushButton { background-color: #808080; border: 0px; border-radius: " \
  "40px; color: white; }"
#define EQUAL_CSS                                                            \
  "QPushButton { background-color: rgb(254, 90, 45); color: white; border: " \
  "0px; border-radius: 35% }"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainApp;
}
QT_END_NAMESPACE

class MainApp : public QMainWindow {
  Q_OBJECT

 public:
  MainApp(QWidget *parent = nullptr);
  ~MainApp();
  void setStyle();
  void addValue(QChar sym);

 private slots:
  void on_oneButton_clicked();

  void on_twoButton_clicked();

  void on_threeButton_clicked();

  void on_fourButton_clicked();

  void on_fiveButton_clicked();

  void on_sixButton_clicked();

  void on_sevenButton_clicked();

  void on_eightButton_clicked();

  void on_nineButton_clicked();

  void on_zeroButton_clicked();

  void on_resetButton_clicked();

  void on_dotButton_clicked();

  void on_umButton_clicked();

  void on_equalButton_clicked();

  void on_delButton_clicked();

  void on_xButton_clicked();

  void on_openBracketButton_clicked();

  void on_closeBracketButton_clicked();

  void on_modButton_clicked();

  void on_cosButton_clicked();

  void on_sinButton_clicked();

  void on_tanButton_clicked();

  void on_acosButton_clicked();

  void on_asinButton_clicked();

  void on_atanButton_clicked();

  void on_sqrtButton_clicked();

  void on_lnButton_clicked();

  void on_logButton_clicked();

  void on_minusButton_clicked();

  void on_plusButton_clicked();

  void on_powButton_clicked();

  void on_creditButton_clicked();

  void on_depositButton_clicked();

 private:
  Ui::MainApp *ui;
  QString replaceXWithValue(QString &expression, double value);
};
#endif  // MAINAPP_H
