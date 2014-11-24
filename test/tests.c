#include <stdio.h>

#include "minunit.h"
#include "../src/dzen_list.h"

static char *test_should_create_and_destroy_list() {
    struct dzen_list *list_under_test = dzen_list_create();
    struct dzen_list *another_list_under_test = dzen_list_create();

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

static char *run_all_tests() {
    mu_run_test(test_should_create_and_destroy_list);
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
