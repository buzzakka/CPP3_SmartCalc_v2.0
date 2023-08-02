#ifndef S21_CREDIT_CALC_VIEW_H
#define S21_CREDIT_CALC_VIEW_H

#include <QWidget>

#include "./../../controller/credit_calc/s21_credit_calc_controller.h"

namespace Ui {
class CreditCalcView;
}

namespace s21 {
class CreditCalcView : public QWidget {
  Q_OBJECT

 public:
  CreditCalcView(QWidget *parent = nullptr);
  ~CreditCalcView();

 private slots:
  void Calculate();

 private:
  void CreateTable();
  void FillTable();

  Ui::CreditCalcView *credit_calc_ui_;
  s21::CreditCalcController controller_;
};
}  // namespace s21

#endif  // S21_CREDIT_CALC_VIEW_H
