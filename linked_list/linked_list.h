#pragma once

struct linked_list_t
{
    struct node_t *head;
    struct node_t *tail;
};

struct node_t
{
    char *data;
    struct node_t *next;
};

struct linked_list_t* ll_create();

int ll_push_back(struct linked_list_t* ll, char *value);
int ll_push_front(struct linked_list_t* ll, char *value);

int ll_size(const struct linked_list_t* ll);
int ll_is_empty(const struct linked_list_t* ll);

void ll_clear(struct linked_list_t* ll);

void ll_display(const struct linked_list_t* ll);

int ll_is_sorted_ascending(const struct linked_list_t* ll);
int ll_insert_words(struct linked_list_t* ll, int N, ...);
