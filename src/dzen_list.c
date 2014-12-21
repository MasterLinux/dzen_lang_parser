#include "dzen_list.h"

static int DZEN_LIST_ITERATOR_START_POS = -1;
static int DZEN_LIST_ITERATOR_END_POS = -2;

dzen_list *dzen_list_create() {
    return calloc(1, sizeof(dzen_list));
}

dzen_list *dzen_list_copy(dzen_list *list) {
    dzen_list *copy = NULL;

    if(list != NULL) {
        copy = dzen_list_create();
        dzen_list_iterator *it = dzen_list_iterator_create(list);

        while(dzen_list_iterate_forward(it)) {
            dzen_list_add(copy, dzen_token_copy(it->current->token));
        }

        dzen_list_iterator_destroy(it);
    }

    return copy;
}

void dzen_list_destroy(dzen_list *list) {
    dzen_list_iterator *it = dzen_list_iterator_create(list);

    while(dzen_list_iterate_backward(it)) {
        if(it->current->next != NULL) {
            free(it->current->next);
        }
    }

    if(list->last != NULL) {
        free(list->last);
    }

    free(list);
    free(it);
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

dzen_list_iterator *dzen_list_iterator_create(dzen_list *list) {
    dzen_list_iterator *it = calloc(1, sizeof(dzen_list_iterator));

    it->position = DZEN_LIST_ITERATOR_START_POS;
    it->list = list;

    return it;
}

void dzen_list_iterator_destroy(dzen_list_iterator *iterator) {
    free(iterator);
}

int dzen_list_iterate(int direction, dzen_list_iterator *iterator) {
    int position = iterator->position;
    int has_next = 0;

    if(position == DZEN_LIST_ITERATOR_START_POS || position == DZEN_LIST_ITERATOR_END_POS) {
        iterator->current = direction > 0 ? iterator->list->last : iterator->list->first;

        if(iterator->current != NULL) {
            iterator->token = iterator->current->token;
            iterator->position = direction > 0 ? iterator->list->count - 1 : 0;
            has_next = 1;
        }

    } else if(position >= 0 && position < iterator->list->count) {
        iterator->current = direction > 0 ? iterator->current->previous : iterator->current->next;

        if(iterator->current != NULL) {
            iterator->token = iterator->current->token;

            if(direction > 0) {
                iterator->position--;
            } else {
                iterator->position++;
            }

            has_next = 1;

        } else {
            iterator->position = DZEN_LIST_ITERATOR_END_POS;
            iterator->token = NULL;
        }
    }

    return has_next;
}

int dzen_list_iterate_forward(dzen_list_iterator *iterator) {
    return dzen_list_iterate(0, iterator);
}

int dzen_list_iterate_backward(dzen_list_iterator *iterator) {
    return dzen_list_iterate(1, iterator);
}
