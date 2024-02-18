#include "../include/test_poland.h"

START_TEST(stack_create_char) {
  StackChar* stack = createStackChar(25);
  ck_assert_int_eq(isEmptyChar(stack), true);
  ck_assert_int_eq(stack->capacity, 25);
  ck_assert_int_eq(stack->top, 0);
  destroyStackChar(stack);
}
END_TEST

START_TEST(stack_push) {
  StackChar* stack = createStackChar(25);
  pushChar(stack, 'a');
  pushChar(stack, 'b');
  pushChar(stack, 'c');
  pushChar(stack, 'd');
  pushChar(stack, 'e');
  ck_assert_int_eq(isEmptyChar(stack), false);
  ck_assert_int_eq(stack->top, 5);
  destroyStackChar(stack);
}
END_TEST

START_TEST(stack_push_peek) {
  StackChar* stack = createStackChar(25);
  pushChar(stack, 'a');
  pushChar(stack, 'b');
  pushChar(stack, 'c');
  pushChar(stack, 'd');
  pushChar(stack, 'e');
  ck_assert_int_eq(isEmptyChar(stack), false);
  ck_assert_int_eq(stack->top, 5);
  ck_assert_int_eq((int)peekChar(stack), (int)'e');
  ck_assert_int_eq(stack->capacity, 25);
  destroyStackChar(stack);
}
END_TEST

START_TEST(stack_push_peek_pop) {
  StackChar* stack = createStackChar(25);
  pushChar(stack, 'a');
  pushChar(stack, 'b');
  pushChar(stack, 'c');
  pushChar(stack, 'd');
  pushChar(stack, 'e');
  ck_assert_int_eq(isEmptyChar(stack), false);
  ck_assert_int_eq(stack->top, 5);
  ck_assert_int_eq((int)peekChar(stack), (int)'e');
  popChar(stack);
  ck_assert_int_eq((int)peekChar(stack), (int)'d');
  ck_assert_int_eq(stack->top, 4);
  ck_assert_int_eq(stack->capacity, 25);
  destroyStackChar(stack);
}
END_TEST

START_TEST(stack_create_double) {
  StackDouble* stack = createStackDouble(25);
  ck_assert_int_eq(isEmptyDouble(stack), true);
  ck_assert_int_eq(stack->capacity, 25);
  ck_assert_int_eq(stack->top, 0);
  destroyStackDouble(stack);
}
END_TEST

START_TEST(stack_double_push) {
  StackDouble* stack = createStackDouble(25);
  pushDouble(stack, 1.000f);
  pushDouble(stack, 2.000f);
  pushDouble(stack, 3.000f);
  pushDouble(stack, 4.000f);
  pushDouble(stack, 5.000f);
  ck_assert_int_eq(isEmptyDouble(stack), false);
  ck_assert_int_eq(stack->top, 5);
  destroyStackDouble(stack);
}
END_TEST

START_TEST(stack_double_push_peek) {
  StackDouble* stack = createStackDouble(25);
  pushDouble(stack, 1.000f);
  pushDouble(stack, 2.000f);
  pushDouble(stack, 3.000f);
  pushDouble(stack, 4.000f);
  pushDouble(stack, 5.000f);
  StackResult ans = peekDouble(stack);
  ck_assert_int_eq(isEmptyDouble(stack), false);
  ck_assert_int_eq(stack->top, 5);
  ck_assert_double_eq(ans.value, 5.000f);
  ck_assert_int_eq(stack->capacity, 25);
  destroyStackDouble(stack);
}
END_TEST

START_TEST(stack_double_push_peek_pop) {
  StackDouble* stack = createStackDouble(25);
  pushDouble(stack, 1.000f);
  pushDouble(stack, 2.000f);
  pushDouble(stack, 3.000f);
  pushDouble(stack, 4.000f);
  pushDouble(stack, 5.000f);
  ck_assert_int_eq(isEmptyDouble(stack), false);
  ck_assert_int_eq(stack->top, 5);
  StackResult ans = peekDouble(stack);
  ck_assert_double_eq(ans.value, 5.000f);
  popDouble(stack);
  ans = peekDouble(stack);
  ck_assert_double_eq(ans.value, 4.000f);
  ck_assert_int_eq(stack->top, 4);
  ck_assert_int_eq(stack->capacity, 25);
  destroyStackDouble(stack);
}
END_TEST

START_TEST(parse_add_1) {
  char string[MAX_LEN] = "1.11111+2.2222+3.3333";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "1.11111 2.2222 + 3.3333 +"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_add_2) {
  char string[MAX_LEN] = "1.11111+2.2222-3.3333+10";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "1.11111 2.2222 + 3.3333 - 10 +"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST
START_TEST(parse_cos) {
  char string[MAX_LEN] = "cos(0)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "0 c"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_sin) {
  char string[MAX_LEN] = "sin(0)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "0 s"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_tan) {
  char string[MAX_LEN] = "tan(45)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "45 t"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_acos) {
  char string[MAX_LEN] = "acos(1)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "1 o"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_asin) {
  char string[MAX_LEN] = "asin(0)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "0 i"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_atan) {
  char string[MAX_LEN] = "atan(1)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "1 a"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_sqrt) {
  char string[MAX_LEN] = "sqrt(4)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "4 q"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_ln) {
  char string[MAX_LEN] = "ln(22)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "22 n"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_log) {
  char string[MAX_LEN] = "log(10)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "10 g"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_mod) {
  char string[MAX_LEN] = "5 mod 2";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "5 2 m"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_unary_plus) {
  char string[MAX_LEN] = "((+4)-2)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "4 p 2 - "), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_unary_minus) {
  char string[MAX_LEN] = "((-4)+4)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "4 r 4 + "), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_complex_1) {
  char string[MAX_LEN] = "sqrt(4)+3*ln(12)-cos(0)+2^3";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "4 q 3 12 n * + 0 c - 2 3 ^ +"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_complex_2) {
  char string[MAX_LEN] = "((-4)*acos(1))+((+3)/atan(1))";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "4 r 1 o * 3 p 1 a / +"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(parse_complex_3) {
  char string[MAX_LEN] = "mod(10, 3)+sin(-3.14)+log(100)-2";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "10 3 m 3.14 r s + 100 g + 2 -"), SUCCESS);
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_add_1) {
  char string[MAX_LEN] = "1.11111+2.2222+3.3333";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "1.11111 2.2222 + 3.3333 +"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, 1.11111 + 2.2222 + 3.3333);
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_add_2) {
  char string[MAX_LEN] = "1.11111+2.2222-3.3333+10";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "1.11111 2.2222 + 3.3333 - 10 +"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, 1.11111 + 2.2222 - 3.3333 + 10);
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_cos) {
  char string[MAX_LEN] = "cos(0)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "0 c"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, cos(0));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_sin) {
  char string[MAX_LEN] = "sin(0)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "0 s"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, sin(0));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_tan) {
  char string[MAX_LEN] = "tan(45)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "45 t"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, tan(45));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_acos) {
  char string[MAX_LEN] = "acos(1)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "1 o"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, acos(1));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_asin) {
  char string[MAX_LEN] = "asin(0)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "0 i"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, asin(0));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_atan) {
  char string[MAX_LEN] = "atan(1)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "1 a"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, atan(1));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_sqrt) {
  char string[MAX_LEN] = "sqrt(4)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "4 q"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, sqrt(4));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_ln) {
  char string[MAX_LEN] = "ln(22)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "22 n"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, log(22));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_log) {
  char string[MAX_LEN] = "log(10)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "10 g"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, log10(10));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_mod) {
  char string[MAX_LEN] = "5 mod 2";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "5 2 m"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, fmod(5, 2));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_unary_plus) {
  char string[MAX_LEN] = "((+4)-2)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "4 p 2 - "), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, ((+4) - 2));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_unary_minus) {
  char string[MAX_LEN] = "((-4)+4)";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "4 r 4 + "), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, ((-4) + 4));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_complex_1) {
  char string[MAX_LEN] = "sqrt(4)+3*ln(12)-cos(0)+2^3";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "4 q 3 12 n * + 0 c - 2 3 ^ +"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, sqrt(4) + 3 * log(12) - cos(0) + pow(2, 3));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_complex_2) {
  char string[MAX_LEN] = "((-4)*acos(1))+((+3)/atan(1))";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "4 r 1 o * 3 p 1 a / +"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, (((-4) * acos(1)) + ((+3) / atan(1))));
  destroyStackChar(stack);
}
END_TEST

START_TEST(calc_complex_3) {
  char string[MAX_LEN] = "mod(10, 3)+sin(-3.14)+log(100)-2";
  StackChar* stack = createStackChar(MAX_LEN);
  char output[MAX_LEN] = {""};
  readString(string, stack, output);
  ck_assert_int_eq(strcmp(output, "10 3 m 3.14 r s + 100 g + 2 -"), SUCCESS);
  double answer = parsePoland(output);
  ck_assert_double_eq(answer, (fmod(10, 3) + sin(-3.14) + log10(100) - 2));
  destroyStackChar(stack);
}
END_TEST

Suite* stack_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("|Testing: StackChar/StackDouble");
  tc_core = tcase_create("Stack");
  tcase_add_test(tc_core, stack_create_char);
  tcase_add_test(tc_core, stack_push);
  tcase_add_test(tc_core, stack_push_peek);
  tcase_add_test(tc_core, stack_push_peek_pop);

  tcase_add_test(tc_core, stack_create_double);
  tcase_add_test(tc_core, stack_double_push);
  tcase_add_test(tc_core, stack_double_push_peek);
  tcase_add_test(tc_core, stack_double_push_peek_pop);

  suite_add_tcase(s, tc_core);

  return s;
}
Suite* parse_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("|Testing: From String to Poland Notation");
  tc_core = tcase_create("Parse");
  tcase_add_test(tc_core, parse_add_1);
  tcase_add_test(tc_core, parse_add_2);
  tcase_add_test(tc_core, parse_cos);
  tcase_add_test(tc_core, parse_sin);
  tcase_add_test(tc_core, parse_tan);
  tcase_add_test(tc_core, parse_acos);
  tcase_add_test(tc_core, parse_asin);
  tcase_add_test(tc_core, parse_atan);
  tcase_add_test(tc_core, parse_sqrt);
  tcase_add_test(tc_core, parse_ln);
  tcase_add_test(tc_core, parse_log);
  tcase_add_test(tc_core, parse_mod);
  tcase_add_test(tc_core, parse_unary_plus);
  tcase_add_test(tc_core, parse_unary_minus);
  tcase_add_test(tc_core, parse_complex_1);
  tcase_add_test(tc_core, parse_complex_2);
  tcase_add_test(tc_core, parse_complex_3);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite* calc_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("|Testing: From Notation To Answer");
  tc_core = tcase_create("Calculate");
  tcase_add_test(tc_core, calc_add_1);
  tcase_add_test(tc_core, calc_add_2);
  tcase_add_test(tc_core, calc_cos);
  tcase_add_test(tc_core, calc_sin);
  tcase_add_test(tc_core, calc_tan);
  tcase_add_test(tc_core, calc_acos);
  tcase_add_test(tc_core, calc_asin);
  tcase_add_test(tc_core, calc_atan);
  tcase_add_test(tc_core, calc_sqrt);
  tcase_add_test(tc_core, calc_ln);
  tcase_add_test(tc_core, calc_log);
  tcase_add_test(tc_core, calc_mod);
  tcase_add_test(tc_core, calc_unary_plus);
  tcase_add_test(tc_core, calc_unary_minus);
  tcase_add_test(tc_core, calc_complex_1);
  tcase_add_test(tc_core, calc_complex_2);
  tcase_add_test(tc_core, calc_complex_3);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  SRunner* sr;

  sr = srunner_create(stack_suite());

  srunner_add_suite(sr, parse_suite());
  srunner_add_suite(sr, calc_suite());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
