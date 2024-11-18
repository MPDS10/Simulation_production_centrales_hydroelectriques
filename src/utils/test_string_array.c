#include "string_array.h"
#include <tap.h>

/**
 * Tests an empty string array
 */
void test_empty_string_array(void) {
  diag("Initializing empty string array");
  struct StringArray sa;
  string_array_initialize(&sa);
  cmp_ok(sa.size, "==", 0, "size of string array is 0");
  cmp_ok(sa.capacity, "==", 1, "capacity of string array is 1");
  string_array_delete(&sa);
}

/**
 * Tests a string array of one element
 */
void test_one_element_string_array(void) {
  diag("Initializing string array with one element");
  struct StringArray sa;
  string_array_initialize(&sa);
  string_array_append(&sa, "alpha");
  cmp_ok(sa.size, "==", 1, "size of string array is 1");
  cmp_ok(sa.capacity, "==", 1, "capacity of string array is 1");
  is(sa.strings[0], "alpha", "first string of string array is \"alpha\"");
  string_array_delete(&sa);
}

/**
 * Tests a string array of two elements
 */
void test_two_elements_string_array(void) {
  diag("Initializing string array with one element");
  struct StringArray sa;
  string_array_initialize(&sa);
  string_array_append(&sa, "beta");
  string_array_append(&sa, "alpha");
  cmp_ok(sa.size, "==", 2, "size of string array is 2");
  cmp_ok(sa.capacity, "==", 2, "capacity of string array is 2");
  is(sa.strings[0], "beta", "first string of string array is \"beta\"");
  is(sa.strings[1], "alpha", "second string of string array is \"alpha\"");
  string_array_delete(&sa);
}

// Main
// ----

int main() {
  test_empty_string_array();
  test_one_element_string_array();
  test_two_elements_string_array();
  done_testing();
}
