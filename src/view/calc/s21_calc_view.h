#ifndef CPP3_SMARTCALC_SRC_VIEW_S21_CALC_VIEW_H
#define CPP3_SMARTCALC_SRC_VIEW_S21_CALC_VIEW_H

#include <QMainWindow>
#include <QVector>
#include <cmath>
#include <string>

#include "./../../controller/calc/s21_calc_controller.h"
#include "./../../model/credit_calc/s21_credit_calc_model.h"
#include "./../credit_calc/s21_credit_calc_view.h"
#include "./qcustomplot/qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcView;
}
QT_END_NAMESPACE

namespace s21 {

class CalcView : public QMainWindow {
  Q_OBJECT

 public:
  CalcView(QWidget *parent = nullptr);
  ~CalcView();

  QString NumValidator(QString current_text, QString button_text);
  QString DotValidator(QString current_text, QString button_text);
  QString EValidator(QString current_text, QString button_text);
  QString XValidator(QString current_text, QString button_text);
  QString SignValidator(QString current_text, QString button_text);
  QString FuncValidator(QString current_text, QString button_text);
  QString BraceValidator(QString current_text, QString button_text);

  bool IsLetterInText(QString text, QChar letter);
  void CheckInput();

 private slots:
  void AddNum();
  void AddSign();
  void AddFunc();
  void AddBrace();
  void AddDot();
  void AddE();
  void AddX();

  void Calculate();
  void Delete();
  void ClearLabel();

  void MakeGraph(QString expression);

  void OpenCreditCalcWindow();

 private:
  Ui::CalcView *calc_ui_;
  s21::CalcController controller_;

  s21::CreditCalcView *credit_calc_view_;

  double x_begin_ = -10;
  double x_end_ = 10;
  double y_begin_ = -10;
  double y_end_ = 10;
  double step_ = 0.1;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_SRC_VIEW_S21_CALC_VIEW_H
