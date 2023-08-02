#include "s21_calc_view.h"

QString s21::CalcView::NumValidator(QString current_text, QString button_text) {
  QString result_text = "";
  if (current_text == "0")
    result_text = button_text;
  else if (current_text.back() == ')' || current_text.back() == 'x')
    result_text = current_text;
  else
    result_text = current_text + button_text;
  return result_text;
}

QString s21::CalcView::EValidator(QString current_text, QString button_text) {
  QString result_text = "";
  if (IsLetterInText("0123456789", current_text.back())) {
    auto it = current_text.end() - 1;
    while (it != current_text.begin() && IsLetterInText("0123456789", *it))
      --it;
    if (*it == '+' || *it == '-') {
      if (it != current_text.begin() && *(it - 1) != 'e')
        result_text = current_text + button_text;
      else
        result_text = current_text;
    } else if (*it != 'e')
      result_text = current_text + button_text;
    else
      result_text = current_text;
  } else {
    result_text = current_text;
  }
  return result_text;
}

QString s21::CalcView::XValidator(QString current_text, QString button_text) {
  QString result_text = "";
  if (current_text == "0")
    result_text = button_text;
  else if (IsLetterInText("+-/*^d(", current_text.back()))
    result_text = current_text + button_text;
  else
    result_text = current_text;
  return result_text;
}

QString s21::CalcView::DotValidator(QString current_text, QString button_text) {
  QString result_text = "";
  if (IsLetterInText("0123456789", current_text.back())) {
    auto it = current_text.end() - 1;
    while (it != current_text.begin() && IsLetterInText("0123456789", *it))
      --it;
    if (*it != '.')
      result_text = current_text + button_text;
    else
      result_text = current_text;
  } else {
    result_text = current_text;
  }
  return result_text;
}

QString s21::CalcView::SignValidator(QString current_text,
                                     QString button_text) {
  QString result_text = "";
  if (current_text == "0" || current_text == "+" || current_text == "-") {
    if (button_text == "+" || button_text == "-")
      result_text += button_text;
    else if (current_text == "0")
      result_text = current_text + button_text;
    else
      result_text = current_text;
  } else if (IsLetterInText("0123456789)x", current_text.back())) {
    result_text = current_text + button_text;
  } else if (IsLetterInText("e(", current_text.back())) {
    if (button_text == "-" || button_text == "+") {
      result_text = current_text + button_text;
    } else {
      result_text = current_text;
    }
  } else if (IsLetterInText("+-/*^d", current_text.back())) {
    auto it = current_text.end();
    if (IsLetterInText("(e", *(it - 2))) {
      if (button_text == "-" || button_text == "+") {
        if (current_text.back() == 'd')
          current_text.chop(3);
        else
          current_text.chop(1);
        result_text = current_text + button_text;
      } else {
        result_text = current_text;
      }
    } else {
      if (current_text.back() == 'd')
        current_text.chop(3);
      else
        current_text.chop(1);
      result_text = current_text + button_text;
    }
  } else {
    result_text = current_text;
  }
  return result_text;
}

QString s21::CalcView::BraceValidator(QString current_text,
                                      QString button_text) {
  QString result_text = "";
  if (button_text == "(") {
    if (current_text == "0") {
      result_text = "(";
    } else if (IsLetterInText("+-*/^d(", current_text.back())) {
      result_text = current_text + "(";
    } else {
      result_text = current_text;
    }
  } else if (button_text == ")") {
    int open_brace_count = 0;
    int close_brace_count = 0;
    for (auto it = current_text.begin(); it < current_text.end(); ++it) {
      if (*it == '(') ++open_brace_count;
      if (*it == ')') ++close_brace_count;
    }
    if (open_brace_count > close_brace_count &&
        IsLetterInText("1234567890)x", current_text.back()))
      result_text = current_text + ")";
    else
      result_text = current_text;
  } else {
    result_text = current_text;
  }
  return result_text;
}

QString s21::CalcView::FuncValidator(QString current_text,
                                     QString button_text) {
  QString result_text = "";
  if (current_text == "0")
    result_text = button_text + "(";
  else if (IsLetterInText("+-*/^d(", current_text.back()))
    result_text = current_text + button_text + "(";
  else
    result_text = current_text;
  return result_text;
}
