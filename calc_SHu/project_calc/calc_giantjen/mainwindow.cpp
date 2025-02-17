#include "mainwindow.h"

#include "credit.h"
#include "graf.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_OB, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_CB, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(clear()));
  connect(ui->pushButton_ravno, SIGNAL(clicked()), this, SLOT(result()));
  connect(ui->backspace, SIGNAL(clicked()), this, SLOT(backspace()));
  connect(ui->pushButton_degree, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();

  ui->resultShow->setText(ui->resultShow->text() + button->text());
}
void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();
  ui->resultShow->setText(ui->resultShow->text() + button->text() + "(");
}

void MainWindow::clear() { ui->resultShow->setText(""); }

void MainWindow::result() {
  QString str = ui->resultShow->text();
  double res = 0;
  int status = OK;
  double x = ui->doubleSpinBox->value();
  QByteArray ba;
  ba = str.toLatin1();
  status = my_smartcalc(ba.data(), &res, x);

  if (status == OK)
    ui->resultShow->setText(QString::number(res, 'g', 15));
  else
    ui->resultShow->setText("INVALID INPUT, IZVINITI)");
}
void MainWindow::backspace() { ui->resultShow->backspace(); }

void MainWindow::on_buildgraph_clicked() {
  int status = OK;
  double x_max = ui->x_max->value();
  double x_min = ui->x_min->value();
  double y_max = ui->y_max->value();
  double y_min = ui->y_min->value();
  if (x_min >= x_max || y_min >= y_max) {
    status = ERROR;
    QMessageBox::critical(this, "ERROR", "TRY AGAIN, IZVINITE");
  }
  if (status == OK) {
    QString str = ui->resultShow->text();
    QByteArray ba;
    ba = str.toLatin1();

    Graf *graph = new Graf;
    graph->paint_graf(ba.data(), x_max, x_min, y_max, y_min, &status);
    if (status == OK)
      graph->show();
    else
      ui->resultShow->setText("INVALID INPUT, IZVINITI)");
  }
}

void MainWindow::on_credit_clicked() {
  Credit *credit = new Credit;
  credit->show();
}
