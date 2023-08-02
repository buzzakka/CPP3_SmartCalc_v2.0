#include "s21_credit_calc_model.h"

s21::CreditCalcModel::CreditCalcModel(){};

void s21::CreditCalcModel::Calculate(double credit_sum, double credit_term,
                                     double interest_rate, unsigned type) {
  if (!month_payments_.empty()) month_payments_.clear();
  if (type == 1) {
    AnnuityCalculate(credit_sum, credit_term, interest_rate);
  } else if (type == 2) {
    DifferentiatedCalculate(credit_sum, credit_term, interest_rate);
  }
}

void s21::CreditCalcModel::AnnuityCalculate(double credit_sum,
                                            double credit_term,
                                            double interest_rate) {
  double i = interest_rate / (100 * 12);
  double payment = credit_sum * ((i * pow(1 + i, credit_term))) /
                   ((pow(1 + i, credit_term) - 1));
  month_payments_.push_back(payment);
  total_payout_ = credit_term * month_payments_.back();
  overpayment_ = total_payout_ - credit_sum;
}

void s21::CreditCalcModel::DifferentiatedCalculate(double credit_sum,
                                                   double credit_term,
                                                   double interest_rate) {
  total_payout_ = 0;
  for (int count = 1; count <= credit_term; ++count) {
    double payment = credit_sum / credit_term +
                     (credit_sum - (credit_sum / credit_term) * (count - 1)) *
                         (interest_rate / 100 / 12);
    month_payments_.push_back(payment);
    total_payout_ += payment;
  }
  overpayment_ = total_payout_ - credit_sum;
}

std::vector<double> s21::CreditCalcModel::get_month_payment() {
  return month_payments_;
}

double s21::CreditCalcModel::get_overpayment() { return overpayment_; }

double s21::CreditCalcModel::get_total_payout() { return total_payout_; }