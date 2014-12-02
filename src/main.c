#include <stdio.h>
#include "dzen_parser.h"
#include "dzen_token_list.h"

int main() {
    printf("Hello World");

    struct dzen_token token = {
            DZEN_TOKEN_TYPE_CONSTANT,
            DZEN_VALUE_MODIFIER_NONE,
            "test",
            DZEN_NOT_SET,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
    };

    struct dzen_token *list = dzen_make_token_list();
    dzen_add_token(list, token);

    printf(list->next_token->string_value);

    return 0;
}