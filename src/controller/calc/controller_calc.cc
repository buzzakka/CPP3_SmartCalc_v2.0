#include "s21_calc_controller.h"

s21::CalcController::CalcController(){};

QString s21::CalcController::Calculate(QString qstring_expression,
                                       double x_value) {
  std::string string_expression = qstring_expression.toStdString();
  model_.Calculate(string_expression, x_value);
  QString result = model_.get_error_status()
                       ? QString::fromStdString("error")
                       : QString::number(model_.get_result(), 'g', 7);
  model_.Clear();
  return result;
}
