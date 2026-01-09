/*
 * skiplist.c - Skiplist Implementation
 *
 * Author: frostzt
 * Date: 2026-01-09
 */

#include "skiplist.h"

Node *new_node(int64 value, Node *next_node) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    return NULL;
  }

  node->value = value;
  node->next_node = next_node;
  return node;
}

LinkedList *new_llist(int64 value) {
  Node *head_node = new_node(value, NULL);
  if (head_node == NULL) {
    return NULL;
  }

  /* now create the list, normal llists will be on heap */
  LinkedList *llist = (LinkedList *)malloc(sizeof(LinkedList));
  if (llist == NULL) {
    free(head_node);
    return NULL;
  }

  llist->head = head_node;
  llist->current_size = 1;

  return llist;
}

void skiplist_init(Skiplist *skiplist) {
  if (skiplist == NULL || skiplist->levels_count != 0) {
    return;
  }

  skiplist->levels_count = 0;
}

void skiplist_add(Skiplist *skiplist, int64 value) {
  if (skiplist == NULL) {
    return;
  }

  /* here we know that the skiplist is a newly created one */
  if (skiplist->levels_count == 0) {
    LinkedList *llist = new_llist(value);
    if (llist == NULL) {
      return;
    }

    /* add the linkedlist to the skip list base list */
    skiplist->levels[0] = llist;
    skiplist->levels_count++;
    return;
  }
}
