#include <QApplication>

#include "./../controller/calc/s21_calc_controller.h"
#include "./../model/calc/s21_calc_model.h"
#include "./../view/calc/s21_calc_view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::CalcView user_view(nullptr);
  user_view.show();
  return a.exec();
}
