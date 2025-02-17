#ifndef GRAF_H
#define GRAF_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class Graf;
}

class Graf : public QDialog {
  Q_OBJECT

 public:
  explicit Graf(QWidget *parent = nullptr);
  ~Graf();
  void paint_graf(char *str, double x_max, double x_min, double y_max,
                  double y_min, int *status);

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Graf *ui;
};

#endif  // GRAF_H
