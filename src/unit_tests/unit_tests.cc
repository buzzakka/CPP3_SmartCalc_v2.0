#include "./../model/calc/s21_calc_model.h"
#include "./../model/credit_calc/s21_credit_calc_model.h"
#include "gtest/gtest.h"

/*
    ========== ТЕСТЫ BASE CALC (START) ==========
*/

void CheckCorrectExpression(std::string expression, double result,
                            double x_value = 0) {
  s21::CalcModel calc{};
  calc.Calculate(expression, x_value);
  EXPECT_DOUBLE_EQ(result, calc.get_result());
  EXPECT_FALSE(calc.get_error_status());
}

void CheckIncorrectExpression(std::string expression) {
  s21::CalcModel calc{};
  calc.Calculate(expression);
  EXPECT_TRUE(calc.get_error_status());
}

TEST(test_calc_model_num, num_correct_test_1) {
  std::string expression = "-3.3e-3+13.3-13.33e3";
  CheckCorrectExpression(expression, -3.3e-3 + 13.3 - 13.33e3);
}

TEST(test_calc_model_num, num_correct_test_2) {
  std::string expression = "3.3+3+0.333+13.3+1.5e-2+1.5e2";
  CheckCorrectExpression(expression, 3.3 + 3 + 0.333 + 13.3 + 1.5e-2 + 1.5e2);
}

TEST(test_calc_model_num, num_correct_test_3) {
  std::string expression = "3";
  CheckCorrectExpression(expression, 3);
}

TEST(test_calc_model_num, num_correct_test_4) {
  std::string expression = "-3";
  CheckCorrectExpression(expression, -3);
}

TEST(test_calc_model_num, num_correct_test_5) {
  std::string expression = "3.3";
  CheckCorrectExpression(expression, 3.3);
}

TEST(test_calc_model_num, num_correct_test_6) {
  std::string expression = "-3.3";
  CheckCorrectExpression(expression, -3.3);
}

TEST(test_calc_model_num, num_correct_test_7) {
  std::string expression = "3.3e4";
  CheckCorrectExpression(expression, 3.3e4);
}

TEST(test_calc_model_num, num_correct_test_8) {
  std::string expression = "3.3e-4";
  CheckCorrectExpression(expression, 3.3e-4);
}

TEST(test_calc_model_num, num_correct_test_9) {
  std::string expression = "-3.3e+4";
  CheckCorrectExpression(expression, -3.3e+4);
}

TEST(test_calc_model_num, num_correct_test_10) {
  std::string expression = "-3.3e-4";
  CheckCorrectExpression(expression, -3.3e-4);
}

TEST(test_calc_model_num, num_incorrect_test_1) {
  std::string expression = "3.";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_num, num_incorrect_test_2) {
  std::string expression = "-3.";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_num, num_incorrect_test_3) {
  std::string expression = "3.3.3";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_num, num_incorrect_test_4) {
  std::string expression = "-3.3.3";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_num, num_incorrect_test_5) {
  std::string expression = "3e1.1";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_num, num_incorrect_test_6) {
  std::string expression = "-3e1.1";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_num, num_incorrect_test_7) {
  std::string expression = "3.3.e1";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_num, num_incorrect_test_8) {
  std::string expression = "-3.3.e1";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_num, num_incorrect_test_9) {
  std::string expression = "3.3e";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_num, num_incorrect_test_10) {
  std::string expression = "3.3e-";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_num, num_incorrect_test_11) {
  std::string expression = "3.3e+";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_num, num_incorrect_test_12) {
  std::string expression = "3.3+12-3e2-3.3.3";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_sign, sign_correct_test_1) {
  std::string expression = "-3+3/2*3mod1.5+3+(+3+1.5^1.6^1.7)";
  CheckCorrectExpression(expression, -3 + 3 / 2 * fmod(3, 1.5) + 3 +
                                         (+3 + pow(1.5, pow(1.6, 1.7))));
}

TEST(test_calc_model_sign, sign_correct_test_2) {
  std::string expression = "(-3.3e-1*(+2.02/(-3.1e2+(+2))))";
  CheckCorrectExpression(expression, (-3.3e-1 * (+2.02 / (-3.1e2 + (+2)))));
}

TEST(test_calc_model_sign, sign_incorrect_test_1) {
  std::string expression = "-";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_sign, sign_incorrect_test_2) {
  std::string expression = "1-";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_sign, sign_incorrect_test_3) {
  std::string expression = "1++3";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_sign, sign_incorrect_test_4) {
  std::string expression = "1/3mod";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_sign, sign_incorrect_test_5) {
  std::string expression = "1/3mod2.2+3-4/1/";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_func, func_correct_test_1) {
  std::string expression = "cos(sin(tan(log(ln(10)))))";
  CheckCorrectExpression(expression, cos(sin(tan(log10(log(10))))));
}

TEST(test_calc_model_func, func_correct_test_2) {
  std::string expression = "asin(0.22)*acos(-0.33)/atan(1e-2)";
  CheckCorrectExpression(expression, asin(0.22) * acos(-0.33) / atan(1e-2));
}

TEST(test_calc_model_func, func_incorrect_test_1) {
  std::string expression = "13cos(sin(tan(log(ln(10)))))";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_func, func_incorrect_test_2) {
  std::string expression = "cos(14";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_func, func_incorrect_test_3) {
  std::string expression = "cos(14)+sin";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_func, func_incorrect_test_4) {
  std::string expression = "cos(14)+sin()";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_func, x_correct_test_1) {
  std::string expression = "x";
  CheckCorrectExpression(expression, -1.3, -1.3);
}

TEST(test_calc_model_func, x_correct_test_2) {
  std::string expression = "-x-cos(+x^x-x)";
  CheckCorrectExpression(expression, -1.3 - cos(pow(1.3, 1.3) - 1.3), 1.3);
}

TEST(test_calc_model_func, x_correct_test_3) {
  std::string expression = "(-x)+(+x+cos(x))";
  CheckCorrectExpression(expression, 1.3 + (-1.3 + cos(-1.3)), -1.3);
}

TEST(test_calc_model_func, x_incorrect_test_1) {
  std::string expression = "x.1";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_func, x_incorrect_test_2) {
  std::string expression = "1.x";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_func, x_incorrect_test_3) {
  std::string expression = "asin(x";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_func, x_incorrect_test_4) {
  std::string expression = "(1-3)x";
  CheckIncorrectExpression(expression);
}

TEST(test_calc_model_expr, expr_correct_test_1) {
  std::string expression = "-(-sin(1.3e1))-log(+(-(ln(+1))))";
  CheckCorrectExpression(expression, -(-sin(1.3e1)) - log10(+(-(log(+1)))));
}

TEST(test_calc_model_expr, expr_correct_test_2) {
  std::string expression = "sin(cos(tan(log(ln(3.3))/2)*3)^2)mod(-2)";
  CheckCorrectExpression(
      expression, fmod(sin(pow(cos(tan(log10(log(3.3)) / 2) * 3), 2)), -2));
}

/*
    ========== ТЕСТЫ BASE CALC (END) ==========
*/

/*
    ========== ТЕСТЫ CREDIT CALC (START) ==========
*/

TEST(test_credit_calc, credit_calc_annuity_1) {
  s21::CreditCalcModel credit_calc;
  credit_calc.Calculate(123456789, 12, 20.71, 1);
  EXPECT_TRUE(credit_calc.get_month_payment().front() - 11478351.53 < 0.001);
  EXPECT_TRUE(credit_calc.get_overpayment() - 14283429.36 < 0.01);
  EXPECT_TRUE(credit_calc.get_total_payout() - 137740218.36 < 0.01);
}

TEST(test_credit_calc, credit_calc_annuity_2) {
  s21::CreditCalcModel credit_calc;
  credit_calc.Calculate(22302010120, 50, 50, 1);
  EXPECT_TRUE(credit_calc.get_month_payment().front() - 1067963739.41 < 0.01);
  EXPECT_TRUE(credit_calc.get_overpayment() - 31096176850.50 < 1);
  EXPECT_TRUE(credit_calc.get_total_payout() - 53398186970.50 < 1);
}

TEST(test_credit_calc, credit_calc_differentiated_1) {
  s21::CreditCalcModel credit_calc;
  credit_calc.Calculate(44201, 5, 20.71, 2);
  std::vector<double> correct_values = {9603.04, 9450.47, 9297.90, 9145.33,
                                        8992.77};
  std::vector<double> calc_values = credit_calc.get_month_payment();
  auto it_1 = correct_values.begin();
  auto it_2 = calc_values.begin();
  while (it_1 != correct_values.end()) {
    EXPECT_TRUE(*it_1 - *it_2 <= 0.01);
    ++it_1;
    ++it_2;
  }
  EXPECT_TRUE(credit_calc.get_overpayment() - 2288.51 < 0.01);
  EXPECT_TRUE(credit_calc.get_total_payout() - 46489.51 < 0.01);
}

TEST(test_credit_calc, credit_calc_differentiated_2) {
  s21::CreditCalcModel credit_calc;
  credit_calc.Calculate(4420134, 50, 20.71, 2);
  std::vector<double> calc_values = credit_calc.get_month_payment();
  EXPECT_TRUE(credit_calc.get_month_payment().front() - 164686.83 < 0.01);
  EXPECT_TRUE(credit_calc.get_month_payment().back() - 89928.36 < 0.01);
  EXPECT_TRUE(credit_calc.get_overpayment() - 1945245.72 < 0.01);
  EXPECT_TRUE(credit_calc.get_total_payout() - 6365379.72 < 0.01);
}

/*
    ========== ТЕСТЫ CREDIT CALC (END) ==========
*/

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
