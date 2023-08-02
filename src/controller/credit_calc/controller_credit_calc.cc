#include "s21_credit_calc_controller.h"

s21::CreditCalcController::CreditCalcController(){};

void s21::CreditCalcController::Calculate(double credit_sum, double credit_term,
                                          double interest_rate, unsigned type) {
  model_.Calculate(credit_sum, credit_term, interest_rate, type);
  if (!month_payment_.empty()) month_payment_.clear();
  for (auto elem : model_.get_month_payment()) {
    month_payment_.push_front(QString::number(elem, 'f', 2));
  }
  overpayment_ = QString::number(model_.get_overpayment(), 'f', 2);
  total_payout_ = QString::number(model_.get_total_payout(), 'f', 2);
}

QVector<QString> s21::CreditCalcController::get_month_payment() {
  return month_payment_;
}

QString s21::CreditCalcController::get_overpayment() { return overpayment_; }

QString s21::CreditCalcController::get_total_payout() { return total_payout_; }
