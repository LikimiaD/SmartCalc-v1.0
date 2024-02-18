#include "deposit.h"

#include "ui_deposit.h"

deposit::deposit(QWidget *parent) : QDialog(parent), ui(new Ui::deposit) {
  ui->setupUi(this);
}

deposit::~deposit() { delete ui; }

void deposit::on_pushButton_clicked() {
  bool ok;
  double initialAmount = ui->totalCount->text().toDouble(&ok);
  if (!ok || initialAmount < 0) {
    ui->totalPercent->setText("Ошибка в сумме вклада");
    return;
  }
  int termMonths = ui->totalRange->text().toInt(&ok);
  if (!ok || termMonths <= 0) {
    ui->totalPercent->setText("Ошибка в сроке размещения");
    return;
  }
  double annualRate = ui->percentInfo->text().toDouble(&ok);
  if (!ok || annualRate < 0) {
    ui->totalPercent->setText("Ошибка в процентной ставке");
    return;
  }
  double taxRate = ui->percentGoverment->text().toDouble(&ok);
  if (!ok || taxRate < 0) {
    ui->totalPercent->setText("Ошибка в налоговой ставке");
    return;
  }
  int payoutFrequencyWeeks = ui->weekRate->text().toInt(&ok);
  if (!ok || payoutFrequencyWeeks <= 0) {
    ui->totalPercent->setText("Ошибка в периодичности выплат");
    return;
  }
  bool capitalization = ui->percentCapitalization->text().toInt(&ok);
  if (!ok) {
    ui->totalPercent->setText("Ошибка в капитализации процентов");
    return;
  }
  QVector<double> additions = parseList(ui->listAdd->text());
  QVector<double> withdrawals = parseList(ui->listRemove->text());
  double totalInterest = 0, totalTax = 0, finalAmount = initialAmount;
  for (int month = 1; month <= termMonths; ++month) {
    finalAmount += (month - 1) < additions.size() ? additions[month - 1] : 0;
    finalAmount -=
        (month - 1) < withdrawals.size() ? withdrawals[month - 1] : 0;
    if (month % (payoutFrequencyWeeks / 4) == 0 || month == termMonths) {
      double interest = finalAmount * (annualRate / 12 / 100);
      double tax = interest * (taxRate / 100);
      totalInterest += interest;
      totalTax += tax;
      if (capitalization) {
        finalAmount += interest - tax;
      }
    }
  }
  ui->totalPercent->setText(QString::number(totalInterest, 'f', 2));
  ui->totalTax->setText(QString::number(totalTax, 'f', 2));
  ui->totalMoney->setText(QString::number(finalAmount, 'f', 2));
}

QVector<double> deposit::parseList(const QString &list) {
  QVector<double> result;
  QStringList items = list.split(";");
  bool ok;
  for (const QString &item : items) {
    double value = item.toDouble(&ok);
    if (ok) {
      result.push_back(value);
    }
  }
  return result;
}
