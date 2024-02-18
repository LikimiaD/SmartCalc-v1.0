#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

namespace Ui {
class credit;
}

class credit : public QDialog {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::credit *ui;
};

#endif  // CREDIT_H
