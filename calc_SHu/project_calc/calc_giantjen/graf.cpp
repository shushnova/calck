#include "graf.h"

#include "ui_graf.h"

Graf::Graf(QWidget* parent) : QDialog(parent), ui(new Ui::Graf) {
  ui->setupUi(this);
}

Graf::~Graf() { delete ui; }
void Graf::paint_graf(char* str, double x_max, double x_min, double y_max,
                      double y_min, int* status) {
  int dot_n = 1000;
  double step = (x_max - x_min) / dot_n;
  *status = OK;
  QVector<double> x(dot_n), y(dot_n);
  double x_val = x_min;
  for (int i = 0; i < dot_n && x_val <= x_max; x_val += step) {
    x[i] = x_val;

    *status = my_smartcalc(str, &y[i], x[i]);

    std::cout << x[i] << " " << y[i] << "\n";
    i++;
  }

  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  // give the axes some labels:
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  // set axes ranges, so we see all data:
  ui->widget->xAxis->setRange(x_min, x_max);
  ui->widget->yAxis->setRange(y_min, y_max);
  ui->widget->replot();
  x.clear();
  y.clear();
}

void Graf::on_pushButton_clicked() { this->close(); }
