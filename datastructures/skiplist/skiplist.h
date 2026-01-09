/*
 * skiplist.h - Skiplist Definition
 *
 * Author: frostzt
 * Date: 2026-01-09
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef unsigned long long int int64;

typedef struct Node Node;
struct Node {
  int64 value;
  Node *next_node;
};

/* creates a new node with the provided value and next node */
Node *new_node(int64 value, Node *next_node);

bool should_generate_level(size_t node_count) {
}

/*----------------------------------------------------------------
 *  Linked Lists
 *----------------------------------------------------------------*/

typedef struct LinkedList {
  Node *head;
  size_t current_size;
} LinkedList;

/* creates a new linked list with one node with the provided value set */
LinkedList *new_llist(int64 value);

/*----------------------------------------------------------------
 *  Skiplist
 *----------------------------------------------------------------
 * |1| ----------------------> |5| -> |6| --> NULL
 * |1| --------> |3| --------> |5| ---------> NULL
 * |1| -> |2| -> |3| -> |4| -> |5| -> |6| --> NULL
 *
 * // Definition idk if this will work but let's give this a shot lol
 * SkipList { LL (levels) -> [...], level_count -> n }
 *
 * - levels go 0->n, 0 being the base llist and n being the most
 *----------------------------------------------------------------*/

typedef struct Skiplist {
  LinkedList **levels;
  size_t levels_count;
} Skiplist;

/* initializes a skiplist, not sure if we need this though given all
 * we do is just set the levels count to zero */
void skiplist_init(Skiplist *skiplist);

void skiplist_add(Skiplist *skiplist, int64 value);
