#ifndef CPP3_SMARTCALC_SRC_CONTROLLER_S21_CREDIT_CALC_CONTROLLER_H
#define CPP3_SMARTCALC_SRC_CONTROLLER_S21_CREDIT_CALC_CONTROLLER_H

#include <QVector>

#include "./../../model/credit_calc/s21_credit_calc_model.h"

namespace s21 {

class CreditCalcController {
 public:
  CreditCalcController();

  void Calculate(double credit_sum, double credit_term, double interest_rate,
                 unsigned type);

  QVector<QString> get_month_payment();
  QString get_overpayment();
  QString get_total_payout();

 public:
  CreditCalcModel model_;
  QVector<QString> month_payment_;
  QString overpayment_;
  QString total_payout_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_SRC_CONTROLLER_S21_CREDIT_CALC_CONTROLLER_H
