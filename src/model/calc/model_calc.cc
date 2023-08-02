#include "s21_calc_model.h"

s21::CalcModel::CalcModel()
    : expression_{}, x_value_{}, result_{}, error_status_(false){};

void s21::CalcModel::Calculate(std::string input_expression, double x_value) {
  x_value_ = x_value;
  CheckInput(input_expression);
  std::vector<std::string> polish_expression = MakePolishExpresiion();
  if (!error_status_) {
    std::stack<double> number_stack{};
    for (auto it = polish_expression.begin();
         it != polish_expression.end() && !error_status_; ++it) {
      std::string lexem = *it;
      if (IsNum(lexem)) {
        number_stack.push(atof(lexem.c_str()));
      } else if (lexem == "x") {
        number_stack.push(x_value_);
      } else {
        if ((lexem == "~" || lexem == "p" || IsFunc(lexem)) &&
            !number_stack.empty()) {
          double num = number_stack.top();
          number_stack.pop();
          if (lexem == "~")
            num = -num;
          else if (lexem == "sin")
            num = sin(num);
          else if (lexem == "cos")
            num = cos(num);
          else if (lexem == "tan")
            num = tan(num);
          else if (lexem == "asin")
            num = asin(num);
          else if (lexem == "acos")
            num = acos(num);
          else if (lexem == "atan")
            num = atan(num);
          else if (lexem == "ln")
            num = log(num);
          else if (lexem == "log")
            num = log10(num);
          else if (lexem == "sqrt")
            num = sqrt(num);
          number_stack.push(num);
        } else if (number_stack.size() > 1) {
          double num_1 = number_stack.top();
          number_stack.pop();
          double num_2 = number_stack.top();
          number_stack.pop();

          if (lexem == "+")
            num_2 += num_1;
          else if (lexem == "-")
            num_2 -= num_1;
          else if (lexem == "*")
            num_2 *= num_1;
          else if (lexem == "/")
            num_2 /= num_1;
          else if (lexem == "mod")
            num_2 = fmod(num_2, num_1);
          else if (lexem == "^")
            num_2 = pow(num_2, num_1);
          number_stack.push(num_2);
        } else {
          error_status_ = true;
        }
      }
    }
    if (number_stack.size() != 1) error_status_ = true;
    if (!error_status_) result_ = number_stack.top();
  }
}

bool s21::CalcModel::IsNum(std::string lexem) {
  return std::regex_match(lexem, std::regex(NUM_REGEX));
}

bool s21::CalcModel::IsUnoSign(std::string lexem) {
  return std::regex_match(lexem, std::regex(UNO_SIGN_REGEX));
}

bool s21::CalcModel::IsSign(std::string lexem) {
  return std::regex_match(lexem, std::regex(SIGN_REGEX));
}

bool s21::CalcModel::IsFunc(std::string lexem) {
  return std::regex_match(lexem, std::regex(FUNC_REGEX));
}

bool s21::CalcModel::IsBrace(std::string lexem) {
  return std::regex_match(lexem, std::regex(BRACE_REGEX));
}

double s21::CalcModel::get_result() { return result_; }

bool s21::CalcModel::get_error_status() { return error_status_; }

void s21::CalcModel::Clear() {
  expression_.clear();
  result_ = 0;
  error_status_ = false;
}
