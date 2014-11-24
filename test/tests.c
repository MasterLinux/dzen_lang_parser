#include <stdio.h>

#include "minunit.h"
#include "../src/dzen_list.h"

static char *test_should_create_and_destroy_list() {
    dzen_list *list_under_test = dzen_list_create();
    dzen_list *another_list_under_test = dzen_list_create();

    mu_assert("error, newly created list is NULL", list_under_test != NULL);
    mu_assert("error, another created list is NULL", another_list_under_test != NULL);
    mu_assert("error, list isn't empty", list_under_test->count == 0);
    mu_assert("error, first node must be NULL", list_under_test->first == NULL);
    mu_assert("error, last node must be NULL", list_under_test->last == NULL);
    mu_assert("error, two lists must not be same", list_under_test != another_list_under_test);

    dzen_list_destroy(list_under_test);
    dzen_list_destroy(another_list_under_test);

    //mu_assert("error, destroyed list isn't NULL", list_under_test == NULL);
    //mu_assert("error, another destroyed list isn't NULL", another_list_under_test == NULL);

    return 0;
}

static char *test_should_add_token_to_list() {
    dzen_list *list_under_test = dzen_list_create();

    char *expected_string_value = "test";
    struct dzen_token *token_under_test = calloc(1, sizeof(struct dzen_token));
    token_under_test->string_value = expected_string_value;

    mu_assert("error, list is NULL", list_under_test != NULL);
    mu_assert("error, token is NULL", token_under_test != NULL);
    mu_assert("error, list isn't empty", list_under_test->count == 0);

    dzen_list_add(list_under_test, token_under_test);

    mu_assert("error, list is empty", list_under_test->count == 1);

    dzen_list_destroy(list_under_test);

    return 0;
}

static char *test_should_iterate_through_list() {
    dzen_list *list_under_test = dzen_list_create();

    char *expected_string_value = "test";
    struct dzen_token *token_under_test = calloc(1, sizeof(struct dzen_token));
    token_under_test->string_value = expected_string_value;

    char *expected_another_string_value = "another_test";
    struct dzen_token *another_token_under_test = calloc(1, sizeof(struct dzen_token));
    another_token_under_test->string_value = expected_another_string_value;

    dzen_list_add(list_under_test, token_under_test);
    dzen_list_add(list_under_test, another_token_under_test);

    mu_assert("error, list is empty", list_under_test->count == 2);

    //dzen_list_iterate_forward(list_under_test, test_should_iterate_forward);
    //dzen_list_iterate_backward(list_under_test, test_should_iterate_forward);

    dzen_list_destroy(list_under_test);

    return 0;
}

static char *run_all_tests() {
    mu_run_test(test_should_create_and_destroy_list);
    mu_run_test(test_should_add_token_to_list);
    mu_run_test(test_should_iterate_through_list);
    return 0;
}

int main(int argc, char **argv) {
    char *result = run_all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }

    return result != 0;
}
