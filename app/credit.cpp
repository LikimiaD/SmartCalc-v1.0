#include "credit.h"

#include <cmath>

#include "ui_credit.h"

credit::credit(QWidget *parent) : QDialog(parent), ui(new Ui::credit) {
  ui->setupUi(this);
}

credit::~credit() { delete ui; }

void credit::on_pushButton_clicked() {
  bool ok;
  double P = ui->totalPrice->text().toDouble(&ok);
  if (!ok) {
    ui->monthPrice->setText("Ошибка в сумме кредита");
    return;
  }
  int n = ui->rangePrice->text().toInt(&ok);
  if (!ok || n <= 0) {
    ui->monthPrice->setText("Ошибка в сроке кредита");
    return;
  }
  double annual_interest_rate = ui->procPrice->text().toDouble(&ok);
  if (!ok || annual_interest_rate < 0) {
    ui->monthPrice->setText("Ошибка в процентной ставке");
    return;
  }
  int type = ui->typeSlider->value();
  double A = 0;
  double A_total = 0;
  double O = 0;
  if (type == 0) {
    double i = annual_interest_rate / 12 / 100;
    double K = (i * pow(1 + i, n)) / (pow(1 + i, n) - 1);
    A = K * P;
    A_total = A * n;
    O = A_total - P;
  } else if (type == 1) {
    double i = annual_interest_rate / 12 / 100;
    double total_payment = 0;
    for (int m = 1; m <= n; ++m) {
      double D_m = (P / n) + (P - P * (m - 1) / n) * i;
      total_payment += D_m;
    }
    A_total = total_payment;
    O = A_total - P;
    A = (P / n) + (P - P * 0 / n) * i;
  }
  ui->monthPrice->setText(QString::number(A, 'f', 2));
  ui->overPrice->setText(QString::number(O, 'f', 2));
  ui->totalOverPrice->setText(QString::number(A_total, 'f', 2));
}
