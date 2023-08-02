#include "s21_calc_model.h"

std::vector<std::string> s21::CalcModel::MakePolishExpresiion() {
  std::vector<std::string> polish_expression{};
  std::stack<std::string> polish_stack{};
  for (auto it = expression_.begin(); it != expression_.end() && !error_status_;
       ++it) {
    if (IsNum(*it)) {
      polish_expression.push_back(*it);
    } else if (*it == "x") {
      polish_expression.push_back("x");
    } else if (IsFunc(*it)) {
      polish_stack.push(*it);
    } else if (IsSign(*it) || IsUnoSign(*it)) {
      AddSignToPolish(*it, &polish_expression, &polish_stack);
    } else if (IsBrace(*it)) {
      AddBraceToPolish(*it, &polish_expression, &polish_stack);
    }
  }
  if (!error_status_) {
    while (!polish_stack.empty() && !error_status_) {
      std::string top_lexem = polish_stack.top();
      if (IsBrace(top_lexem)) {
        error_status_ = true;
      } else {
        polish_expression.push_back(top_lexem);
        polish_stack.pop();
      }
    }
  }
  return polish_expression;
}

void s21::CalcModel::AddSignToPolish(
    std::string sign, std::vector<std::string> *polish_expression,
    std::stack<std::string> *polish_stack) {
  if (!polish_stack->empty()) {
    std::string sign_in_stack = polish_stack->top();
    while (!polish_stack->empty() &&
           (GetPriorityOfSign(sign) <= GetPriorityOfSign(sign_in_stack)) &&
           !(sign == "^" && sign_in_stack == "^")) {
      polish_expression->push_back(polish_stack->top());
      polish_stack->pop();
      if (!polish_stack->empty()) sign_in_stack = polish_stack->top();
    }
  }
  polish_stack->push(sign);
}

void s21::CalcModel::AddBraceToPolish(
    std::string lexem, std::vector<std::string> *polish_expression,
    std::stack<std::string> *polish_stack) {
  if (lexem == "(") {
    polish_stack->push(lexem);
  } else if (!polish_stack->empty()) {
    std::string lexem = polish_stack->top();
    while (!polish_stack->empty() && !error_status_ && lexem != "(") {
      polish_expression->push_back(lexem);
      polish_stack->pop();
      if (polish_stack->empty()) {
        error_status_ = true;
      } else {
        lexem = polish_stack->top();
      }
    }
    if (!error_status_) {
      polish_stack->pop();
      if (!polish_stack->empty() && IsFunc(polish_stack->top())) {
        polish_expression->push_back(polish_stack->top());
        polish_stack->pop();
      }
    }
  } else {
    error_status_ = true;
  }
}

unsigned s21::CalcModel::GetPriorityOfSign(std::string sign) {
  unsigned priority = 0;
  switch (sign[0]) {
    case '+':
    case '-':
      priority = 1;
      break;
    case '*':
    case '/':
    case 'm':
      priority = 2;
      break;
    case '~':
    case 'p':
      priority = 3;
      break;
    case '^':
      priority = 4;
      break;
    default:
      break;
  }
  return priority;
}
