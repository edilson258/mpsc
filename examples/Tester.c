#include <stdlib.h>

#include "../include/Tester.h"

typedef struct Person {
  int age;
  char *name;
} Person;

/// Function under test
int sum_two_ints(int a, int b) { return a + b; }

/// Function under test
int mul_two_ints(int a, int b) { return a * b; }

/// Function under test
Person *create_person(char *name, int age) {
  Person *p = malloc(sizeof(Person));
  p->age = age;
  p->name = name;
  return p;
}

/// Test function: function's name will be used as test's name
TEST test_create_person() {
  Person p1 = {.name = "Low", .age = 30};
  Person *p2 = create_person("Low", 30);
  ASSERT_EQUALS_STRUCT(&p1, p2, sizeof(Person));
}

/// Test function: function's name will be used as test's name
TEST test_sum_two_ints() {
  int a = 34;
  int b = 35;
  ASSERT_EQUALS_INT(69, sum_two_ints(a, b));
}

/// Test function: function's name will be used as test's name
TEST test_mul_two_ints() {
  int a = 12;
  int b = 12;
  ASSERT_EQUALS_INT(144, mul_two_ints(a, b));
}

/// Test function: function's name will be used as test's name
TEST test_expect_true() {
  // will fail
  ASSERT_TRUE(False);
}

int main() {
  Tester_t t = Tester_new();
  Tester_add(t, test_sum_two_ints);
  Tester_add(t, test_mul_two_ints);
  Tester_add(t, test_create_person);
  Tester_add(t, test_expect_true);
  return Tester_run(t);
}
