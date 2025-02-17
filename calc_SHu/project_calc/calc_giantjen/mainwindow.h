#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <iostream>
extern "C" {
#include "../../my_smartcalc.h"
// int my_smartcalc(char *str, double *res);
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
 private slots:
  void digits_numbers();
  void functions();
  void clear();
  void result();
  void backspace();
  void on_buildgraph_clicked();

  void on_credit_clicked();
};
#endif  // MAINWINDOW_H
