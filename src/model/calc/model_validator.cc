#include "s21_calc_model.h"

void s21::CalcModel::CheckInput(std::string input_expr) {
  auto it = input_expr.begin();
  while (it != input_expr.end() && !error_status_) {
    std::string lexem = {};
    if (IsDigit(*it)) {
      NumParser(&it);
    } else if (IsX(*it)) {
      XParser(&it);
    } else if (IsUnoSign(it)) {
      UnoSignParser(&it);
    } else if (IsSign(*it)) {
      SignParser(&it);
    } else if (IsFunc(*it)) {
      FuncParser(&it);
    } else if (IsBrace(*it)) {
      BraceParser(&it);
    } else {
      error_status_ = true;
    }
  }
  if (expression_.empty() ||
      (expression_.back() != "x" && !IsNum(expression_.back()) &&
       expression_.back() != ")"))
    error_status_ = true;
}

bool s21::CalcModel::IsDigit(char elem) { return (elem >= '0' && elem <= '9'); }

bool s21::CalcModel::IsX(char elem) { return elem == 'x'; }

bool s21::CalcModel::IsSign(char elem) { return (strchr("+-*/m^", elem)); }

bool s21::CalcModel::IsUnoSign(std::string::iterator it) {
  if ((*it == '-' || *it == '+') && (expression_.empty() || *(it - 1) == '(')) {
    *it = *it == '-' ? '~' : 'p';
    return true;
  }
  return false;
}

bool s21::CalcModel::IsFunc(char elem) { return (strchr("lcstla", elem)); }

bool s21::CalcModel::IsBrace(char elem) { return (strchr("()", elem)); }

void s21::CalcModel::NumParser(std::string::iterator *it) {
  std::string lexem = {};
  while (IsDigit(**it) || **it == '.' || **it == 'e') {
    lexem += **it;
    ++(*it);
    if ((**it == '-' || **it == '+') && *(*it - 1) == 'e') {
      lexem += **it;
      ++(*it);
    }
  }
  error_status_ = !IsNum(lexem) ||
                  (!expression_.empty() &&
                   (IsFunc(expression_.back()) || expression_.back() == ")"));
  if (!error_status_) expression_.push_back(lexem);
}

void s21::CalcModel::XParser(std::string::iterator *it) {
  error_status_ = (!expression_.empty() &&
                   (IsFunc(expression_.back()) || expression_.back() == ")"));
  if (!error_status_) expression_.push_back("x");
  ++(*it);
}

void s21::CalcModel::SignParser(std::string::iterator *it) {
  std::string lexem = {};
  error_status_ = !IsNum(expression_.back()) && (expression_.back() != "x") &&
                  (expression_.back() != ")");
  if (!error_status_) {
    if (**it == 'm') {
      *it += 3;
      expression_.push_back("mod");
    } else {
      expression_.push_back(lexem + **it);
      ++(*it);
    }
  }
}

void s21::CalcModel::UnoSignParser(std::string::iterator *it) {
  std::string lexem = {};
  error_status_ = !expression_.empty() && (expression_.back() != "(");
  if (!error_status_) expression_.push_back(lexem + **it);
  ++(*it);
}

void s21::CalcModel::BraceParser(std::string::iterator *it) {
  std::string lexem = {};
  if (**it == '(') {
    error_status_ = !expression_.empty() && !IsNum(expression_.back()) &&
                    (expression_.back() != "x") && expression_.back() != "(" &&
                    !IsSign(expression_.back()) && !IsFunc(expression_.back());
  } else {
    error_status_ = !IsNum(expression_.back()) && (expression_.back() != "x") &&
                    expression_.back() != ")";
  }
  if (!error_status_) expression_.push_back(lexem + **it);
  ++(*it);
}

void s21::CalcModel::FuncParser(std::string::iterator *it) {
  std::string lexem = {};
  if (expression_.empty() || expression_.back() == "(" ||
      IsSign(expression_.back()) || expression_.back() == "~" ||
      expression_.back() == "p") {
    while (**it != '(') {
      lexem += **it;
      ++(*it);
    }
    expression_.push_back(lexem);
  } else {
    error_status_ = true;
  }
}
