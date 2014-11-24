#include "dzen_list.h"

static int DZEN_LIST_FORWARD_ITERATOR = 0;
static int DZEN_LIST_BACKWARD_ITERATOR = 1;

void dzen_list_iterate(int direction, dzen_list *list, void (*on_next)(dzen_list_node *node, struct dzen_token *token)) {
    dzen_list_node *current = direction > 0 ? list->last : list->first;
    dzen_list_node *next;

    while (current != NULL) {
        next = direction > 0 ? current->previous : current->next;

        on_next(current, current->token);
        current = next;
    }
}

dzen_list *dzen_list_create() {
    return calloc(1, sizeof(dzen_list));
}

void dzen_list_destroy_node(dzen_list_node *node, struct dzen_token *token) {
    free(token);
    free(node);
}

void dzen_list_destroy(dzen_list *list) {
    dzen_list_iterate(DZEN_LIST_BACKWARD_ITERATOR, list, dzen_list_destroy_node);
    free(list);
}

void dzen_list_add(dzen_list *list, struct dzen_token *token) {
    dzen_list_node *node = calloc(1, sizeof(dzen_list_node));
    node->token = token;

    if(list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->previous = list->last;
        list->last = node;
    }

    list->count++;
    node->position = list->count;
}

void dzen_list_iterate_forward(dzen_list *list, void (*on_next)(dzen_list_node *node, struct dzen_token *token)) {
    dzen_list_iterate(DZEN_LIST_FORWARD_ITERATOR, list, on_next);
}

void dzen_list_iterate_backward(dzen_list *list, void (*on_previous)(dzen_list_node *node, struct dzen_token *token)) {
    dzen_list_iterate(DZEN_LIST_BACKWARD_ITERATOR, list, on_previous);
}
