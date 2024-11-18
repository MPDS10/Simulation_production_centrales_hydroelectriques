#include "treemap.h"

#include <tap.h>

/**
 * Tests an empty treemap
 */
void test_empty_treemap(void) {
  diag("Initializing an empty treemap");
  struct Treemap t;
  treemap_initialize(&t);
  struct StringArray sa;
  treemap_compute_keys(&t, &sa);

  ok(!treemap_has_key(&t, "key"), "treemap_has_key(key) is false");
  cmp_ok(treemap_get(&t, "key"), "==", 0.0, "treemap_get(key) == 0.0");
  cmp_ok(sa.size, "==", 0, "size of string array keys is 0");

  string_array_delete(&sa);
  treemap_delete(&t);
}

/**
 * Tests a treemap with one entry
 */
void test_size_one_treemap(void) {
  diag("Initializing a treemap with one entry");
  struct Treemap t;
  treemap_initialize(&t);
  treemap_set(&t, "alpha", 1.0);
  struct StringArray sa;
  treemap_compute_keys(&t, &sa);

  ok(treemap_has_key(&t, "alpha"), "treemap_has_key(alpha) is true");
  ok(!treemap_has_key(&t, "key"), "treemap_has_key(key) is false");
  cmp_ok(treemap_get(&t, "alpha"), "==", 1.0, "treemap_get(alpha) == 1.0");
  cmp_ok(treemap_get(&t, "key"), "==", 0.0, "treemap_get(key) == 0.0");
  cmp_ok(sa.size, "==", 1, "size of string array keys is 1");
  is(sa.strings[0], "alpha", "first string in string array is \"alpha\"");

  diag("Updating key \"alpha\" with value 2.0");
  treemap_set(&t, "alpha", 2.0);
  ok(treemap_has_key(&t, "alpha"), "treemap_has_key(alpha) is true");
  cmp_ok(treemap_get(&t, "alpha"), "==", 2.0, "treemap_get(alpha) == 2.0");

  string_array_delete(&sa);
  treemap_delete(&t);
}

/**
 * Tests a treemap with two entries
 */
void test_size_two_treemap(void) {
  diag("Initializing a treemap with two entries");
  struct Treemap t;
  treemap_initialize(&t);
  treemap_set(&t, "beta", 2.0);
  treemap_set(&t, "alpha", 1.0);
  struct StringArray sa;
  treemap_compute_keys(&t, &sa);

  ok(treemap_has_key(&t, "alpha"), "treemap_has_key(alpha) is true");
  ok(treemap_has_key(&t, "beta"), "treemap_has_key(beta) is true");
  ok(!treemap_has_key(&t, "key"), "treemap_has_key(key) is false");
  cmp_ok(treemap_get(&t, "alpha"), "==", 1.0, "treemap_get(alpha) == 1.0");
  cmp_ok(treemap_get(&t, "beta"), "==", 2.0, "treemap_get(beta) == 2.0");
  cmp_ok(treemap_get(&t, "key"), "==", 0.0, "treemap_get(key) == 0.0");
  cmp_ok(sa.size, "==", 2, "size of string array keys is 2");
  is(sa.strings[0], "alpha", "first string in string array is \"alpha\"");
  is(sa.strings[1], "beta", "first string in string array is \"beta\"");

  diag("Updating key \"alpha\" with value 2.0");
  treemap_set(&t, "alpha", 2.0);
  ok(treemap_has_key(&t, "alpha"), "treemap_has_key(alpha) is true");
  cmp_ok(treemap_get(&t, "alpha"), "==", 2.0, "treemap_get(alpha) == 2.0");

  string_array_delete(&sa);
  treemap_delete(&t);
}

/**
 * Tests treemap equality
 */
void test_treemap_are_equal(void) {
  diag("Testing treemap equality");
  struct TestCase {
    struct Treemap* t1;
    struct Treemap* t2;
    bool equal;
  };
  struct Treemap t_e, t_a1, t_a2, t_ab, t_ba;
  treemap_initialize(&t_e);
  treemap_initialize(&t_a1);
  treemap_set(&t_a1, "alpha", 1.0);
  treemap_initialize(&t_a2);
  treemap_set(&t_a2, "alpha", 2.0);
  treemap_initialize(&t_ab);
  treemap_set(&t_ab, "alpha", 1.0);
  treemap_set(&t_ab, "beta", 2.0);
  treemap_initialize(&t_ba);
  treemap_set(&t_ba, "beta", 2.0);
  treemap_set(&t_ba, "alpha", 1.0);
  struct TestCase test_cases[] = {
    {&t_e,  &t_e,  true},  {&t_e,  &t_a1, false}, {&t_e,  &t_a2, false},
    {&t_e,  &t_ab, false}, {&t_e,  &t_ba, false},
    {&t_a1, &t_e,  false}, {&t_a1, &t_a1, true},  {&t_a1, &t_a2, false},
    {&t_a1, &t_ab, false}, {&t_a1, &t_ba, false},
    {&t_a2, &t_e,  false}, {&t_a2, &t_a1, false}, {&t_a2, &t_a2, true},
    {&t_a2, &t_ab, false}, {&t_a2, &t_ba, false},
    {&t_ab, &t_e,  false}, {&t_ab, &t_a1, false}, {&t_ab, &t_a2, false},
    {&t_ab, &t_ab, true},  {&t_ab, &t_ba, true},
    {&t_ba, &t_e,  false}, {&t_ba, &t_a1, false}, {&t_ba, &t_a2, false},
    {&t_ba, &t_ab, true},  {&t_ba, &t_ba, true},
  };
  int num_test_cases = sizeof(test_cases) / sizeof(struct TestCase);

  for (int tc = 0; tc < num_test_cases; ++tc)
    cmp_ok(treemap_are_equal(test_cases[tc].t1,
                             test_cases[tc].t2) ? true : false,
           "==",
           test_cases[tc].equal,
           "treemap_are_equal for test case %d returns %s",
           tc,
           test_cases[tc].equal ? "true" : "false");

  treemap_delete(&t_e);
  treemap_delete(&t_a1);
  treemap_delete(&t_a2);
  treemap_delete(&t_ab);
  treemap_delete(&t_ba);
}

// Main
// ----

int main() {
  test_empty_treemap();
  test_size_one_treemap();
  test_size_two_treemap();
  test_treemap_are_equal();
  done_testing();
}
