#ifndef CPP3_SMARTCALC_SRC_MODEL_S21_CALC_MODEL_H
#define CPP3_SMARTCALC_SRC_MODEL_S21_CALC_MODEL_H

#include <math.h>

#include <algorithm>
#include <cstring>
#include <regex>
#include <stack>
#include <string>

#define NUM_REGEX "^\\d+(\\.?\\d+)?(e(\\+|-)?\\d+)?$"
#define FUNC_REGEX "^(ln|cos|sin|tan|log|acos|asin|atan|sqrt)$"
#define SIGN_REGEX "^(\\+|\\-|\\*|\\/|\\^|mod|~|p)$"
#define UNO_SIGN_REGEX "^(\\~|p)$"
#define BRACE_REGEX "^(\\(|\\))$"

namespace s21 {

class CalcModel {
 public:
  CalcModel();

  void Calculate(std::string input_expression, double x_value = 0);

  void Clear();

  double get_result();
  bool get_error_status();

 private:
  void CheckInput(std::string expression);

  bool IsDigit(char elem);
  bool IsX(char elem);
  bool IsSign(char elem);
  bool IsUnoSign(std::string::iterator it);
  bool IsFunc(char elem);
  bool IsBrace(char elem);

  void NumParser(std::string::iterator *it);
  void UnoSignParser(std::string::iterator *it);
  void SignParser(std::string::iterator *it);
  void BraceParser(std::string::iterator *it);
  void FuncParser(std::string::iterator *it);
  void XParser(std::string::iterator *it);

  std::vector<std::string> MakePolishExpresiion();
  void AddSignToPolish(std::string sign,
                       std::vector<std::string> *polish_expression,
                       std::stack<std::string> *polish_stack);
  void AddBraceToPolish(std::string lexem,
                        std::vector<std::string> *polish_expression,
                        std::stack<std::string> *polish_stack);
  unsigned GetPriorityOfSign(std::string sign);

  bool IsNum(std::string lexem);
  bool IsSign(std::string lexem);
  bool IsUnoSign(std::string lexem);
  bool IsFunc(std::string lexem);
  bool IsBrace(std::string lexem);

  std::vector<std::string> expression_;
  double x_value_;
  long double result_;
  bool error_status_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_SRC_MODEL_S21_CALC_MODEL_H