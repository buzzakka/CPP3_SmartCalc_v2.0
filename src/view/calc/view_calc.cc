#include "s21_calc_view.h"
#include "ui_calc.h"

s21::CalcView::CalcView(QWidget *parent)
    : QMainWindow(parent), calc_ui_(new Ui::CalcView) {
  calc_ui_->setupUi(this);

  credit_calc_view_ = new s21::CreditCalcView();

  QVector<QPushButton *> num_buttons = {
      calc_ui_->num_1, calc_ui_->num_2, calc_ui_->num_3, calc_ui_->num_4,
      calc_ui_->num_5, calc_ui_->num_6, calc_ui_->num_7, calc_ui_->num_8,
      calc_ui_->num_9, calc_ui_->num_0};
  for (auto button : num_buttons)
    connect(button, SIGNAL(clicked()), this, SLOT(AddNum()));

  QVector<QPushButton *> sign_buttons = {calc_ui_->plus, calc_ui_->minus,
                                         calc_ui_->mul,  calc_ui_->div,
                                         calc_ui_->mod,  calc_ui_->degree};
  for (auto button : sign_buttons)
    connect(button, SIGNAL(clicked()), this, SLOT(AddSign()));

  QVector<QPushButton *> func_buttons = {
      calc_ui_->sin,  calc_ui_->cos,  calc_ui_->tan,
      calc_ui_->acos, calc_ui_->asin, calc_ui_->atan,
      calc_ui_->log,  calc_ui_->ln,   calc_ui_->sqrt};
  for (auto button : func_buttons)
    connect(button, SIGNAL(clicked()), this, SLOT(AddFunc()));

  connect(calc_ui_->dot, SIGNAL(clicked()), this, SLOT(AddDot()));
  connect(calc_ui_->e, SIGNAL(clicked()), this, SLOT(AddE()));
  connect(calc_ui_->x, SIGNAL(clicked()), this, SLOT(AddX()));

  connect(calc_ui_->brace_open, SIGNAL(clicked()), this, SLOT(AddBrace()));
  connect(calc_ui_->brace_close, SIGNAL(clicked()), this, SLOT(AddBrace()));

  connect(calc_ui_->clear, SIGNAL(clicked()), this, SLOT(ClearLabel()));
  connect(calc_ui_->del, SIGNAL(clicked()), this, SLOT(Delete()));
  connect(calc_ui_->eq, SIGNAL(clicked()), this, SLOT(Calculate()));

  connect(calc_ui_->credit_calc, SIGNAL(clicked()), this,
          SLOT(OpenCreditCalcWindow()));

  calc_ui_->widget->xAxis->setRange(x_begin_, x_end_);
  calc_ui_->widget->yAxis->setRange(y_begin_, y_end_);
}

s21::CalcView::~CalcView() { delete calc_ui_; }

void s21::CalcView::AddNum() {
  CheckInput();
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString current_text = calc_ui_->label_result->text();
  QString result_string = NumValidator(current_text, button_text);
  calc_ui_->label_result->setText(result_string);
}

void s21::CalcView::AddDot() {
  CheckInput();
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString current_text = calc_ui_->label_result->text();
  QString result_string = DotValidator(current_text, button_text);
  calc_ui_->label_result->setText(result_string);
}

void s21::CalcView::AddE() {
  CheckInput();
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString current_text = calc_ui_->label_result->text();
  QString result_string = EValidator(current_text, button_text);
  calc_ui_->label_result->setText(result_string);
}

void s21::CalcView::AddX() {
  CheckInput();
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString current_text = calc_ui_->label_result->text();
  QString result_string = XValidator(current_text, button_text);
  calc_ui_->label_result->setText(result_string);
}

void s21::CalcView::AddBrace() {
  CheckInput();
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString current_text = calc_ui_->label_result->text();
  QString result_text = BraceValidator(current_text, button_text);
  calc_ui_->label_result->setText(result_text);
}

void s21::CalcView::AddSign() {
  CheckInput();

  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString current_text = calc_ui_->label_result->text();
  QString result_string = SignValidator(current_text, button_text);
  calc_ui_->label_result->setText(result_string);
}

void s21::CalcView::AddFunc() {
  CheckInput();
  QPushButton *button = (QPushButton *)sender();
  QString current_text = calc_ui_->label_result->text();
  QString button_text = button->text();
  QString result_string = FuncValidator(current_text, button_text);
  calc_ui_->label_result->setText(result_string);
}

void s21::CalcView::Calculate() {
  QString expression = calc_ui_->label_result->text();
  QString result = "";
  if (expression.contains("x")) {
    x_begin_ = calc_ui_->x_begin_value->value();
    x_end_ = calc_ui_->x_end_value->value();
    y_begin_ = calc_ui_->y_begin_value->value();
    y_end_ = calc_ui_->y_end_value->value();
    if (x_begin_ < x_end_ && y_begin_ < y_end_) {
      calc_ui_->widget->xAxis->setRange(x_begin_, x_end_);
      calc_ui_->widget->yAxis->setRange(y_begin_, y_end_);
    }
    double x_value = calc_ui_->x_value->value();
    result = controller_.Calculate(expression, x_value);
    if (result != "error") {
      MakeGraph(expression);
    }
  } else {
    result = controller_.Calculate(expression);
  }
  calc_ui_->label_result->setText(result);
  if (expression != "error") calc_ui_->label_equation->setText(expression);
}

void s21::CalcView::Delete() {
  QString current_text = calc_ui_->label_result->text();
  if (current_text.back() == '(') {
    current_text.chop(1);
    QString temp = "asincolntgqr";
    while (current_text != "" && IsLetterInText(temp, current_text.back())) {
      current_text.chop(1);
    }
  } else if (current_text.back() == 'd') {
    QString temp = "mod";
    while (current_text != "" && IsLetterInText(temp, current_text.back())) {
      current_text.chop(1);
    }
  } else if (current_text == "error" || current_text == "inf" ||
             current_text == "nan") {
    current_text = "";
  } else {
    current_text.chop(1);
  }
  if (current_text == "") current_text = "0";
  calc_ui_->label_result->setText(current_text);
}

void s21::CalcView::ClearLabel() { calc_ui_->label_result->setText("0"); }

void s21::CalcView::MakeGraph(QString expression) {
  calc_ui_->widget->clearGraphs();
  QVector<double> x_vector{};
  QVector<double> y_vector{};
  step_ = (abs(x_begin_) + abs(x_end_)) / 1000;
  for (auto x = x_begin_; x <= x_end_; x += step_) {
    x_vector.push_back(x);
    y_vector.push_back((controller_.Calculate(expression, x)).toDouble());
  }
  calc_ui_->widget->addGraph();
  calc_ui_->widget->graph(0)->setPen(QColor(50, 50, 50, 255));
  calc_ui_->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  calc_ui_->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

  calc_ui_->widget->graph(0)->addData(x_vector, y_vector);
  calc_ui_->widget->replot();
}

void s21::CalcView::CheckInput() {
  QString current_text = calc_ui_->label_result->text();
  if (current_text == "error" || current_text == "inf" ||
      current_text == "nan") {
    calc_ui_->label_result->setText("0");
  }
}

bool s21::CalcView::IsLetterInText(QString text, QChar letter) {
  bool result = false;
  for (auto let : text) {
    if (letter == let) result = true;
  }
  return result;
}

void s21::CalcView::OpenCreditCalcWindow() {
  this->hide();
  credit_calc_view_->show();
};
