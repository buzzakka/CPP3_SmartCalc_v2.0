#include "s21_credit_calc_view.h"
#include "ui_credit_calc.h"

s21::CreditCalcView::CreditCalcView(QWidget *parent)
    : QWidget(parent), credit_calc_ui_(new Ui::CreditCalcView) {
  credit_calc_ui_->setupUi(this);

  connect(credit_calc_ui_->calculate_button, SIGNAL(clicked()), this,
          SLOT(Calculate()));
}

s21::CreditCalcView::~CreditCalcView() { delete credit_calc_ui_; }

void s21::CreditCalcView::Calculate() {
  double credit_sum = credit_calc_ui_->credit_sum->value();
  double credit_term = credit_calc_ui_->credit_term->value();
  double interest_rate = credit_calc_ui_->interest_rate->value();
  int type = credit_calc_ui_->annuities_type->isChecked() ? 1 : 2;
  this->controller_.Calculate(credit_sum, credit_term, interest_rate, type);

  CreateTable();
  if (type == 1) {
    credit_calc_ui_->month_payment->setText(
        controller_.get_month_payment().front());
  } else {
    QString month_result = controller_.get_month_payment().back() + " ... " +
                           controller_.get_month_payment().front();
    credit_calc_ui_->month_payment->setText(month_result);
    FillTable();
  }
  credit_calc_ui_->overpayment->setText(controller_.get_overpayment());
  credit_calc_ui_->total_payout->setText(controller_.get_total_payout());
}

void s21::CreditCalcView::CreateTable() {
  auto table = credit_calc_ui_->month_payment_table;
  table->clear();
  table->setRowCount(0);
  table->setColumnCount(1);
  table->setHorizontalHeaderLabels({"Оплата"});
}

void s21::CreditCalcView::FillTable() {
  auto table = credit_calc_ui_->month_payment_table;
  table->setRowCount(credit_calc_ui_->credit_term->value());
  auto mont_arr = controller_.get_month_payment();
  auto it = mont_arr.rbegin();

  for (auto row = 0; it != mont_arr.rend(); ++it, ++row) {
    table->setItem(row - 1, 1, new QTableWidgetItem(*it));
  }
}
