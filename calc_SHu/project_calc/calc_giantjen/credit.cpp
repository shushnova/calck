#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_clicked() {
  double sum = ui->sum->value();
  int term = ui->term->value();
  double rate = ui->rate->value();
  double res = 0;
  double first_pay = 0;
  double last_pay = 0;
  bool type_annuite = ui->annuit->isChecked();
  if (type_annuite) {
    count_credit_annuity(sum, rate, term, &res);
  }
  bool type_difference = ui->difference->isChecked();
  if (type_difference) {
    count_credit_difference(sum, rate, term, &res, &first_pay, &last_pay);
  }

  res = round(res * 100) / 100;
  double over = res - sum;
  ui->m_sum->setText(QString::number(first_pay, 'f', 2) + " ... " +
                     QString::number(last_pay, 'f', 2));
  ui->over->setText(QString::number(over, 'f', 2));
  ui->total->setText(QString::number(res, 'f', 2));
}
