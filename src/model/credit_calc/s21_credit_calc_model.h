#ifndef CPP3_SMARTCALC_SRC_MODEL_S21_CREDIT_CALC_MODEL_H
#define CPP3_SMARTCALC_SRC_MODEL_S21_CREDIT_CALC_MODEL_H

#include <cmath>
#include <vector>

namespace s21 {

class CreditCalcModel {
 public:
  CreditCalcModel();

  void Calculate(double credit_sum, double credit_term, double interest_rate,
                 unsigned type);
  void AnnuityCalculate(double credit_sum, double credit_term,
                        double interest_rate);
  void DifferentiatedCalculate(double credit_sum, double credit_term,
                               double interest_rate);

  std::vector<double> get_month_payment();
  double get_overpayment();
  double get_total_payout();

 private:
  std::vector<double> month_payments_;
  double overpayment_;
  double total_payout_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_SRC_MODEL_S21_CREDIT_CALC_MODEL_H
