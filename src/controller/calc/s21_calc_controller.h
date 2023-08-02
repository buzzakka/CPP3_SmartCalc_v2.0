#ifndef CPP3_SMARTCALC_SRC_CONTROLLER_S21_CALC_CONTROLLER_H
#define CPP3_SMARTCALC_SRC_CONTROLLER_S21_CALC_CONTROLLER_H

#include <QString>

#include "./../../model/calc/s21_calc_model.h"

namespace s21 {

class CalcController {
 public:
  CalcController();
  QString Calculate(QString qstring_expression, double x_value = 0);

 private:
  CalcModel model_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_SRC_CONTROLLER_S21_CALC_CONTROLLER_H
