#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct str_t {
  char* text;
  int size;
  int capacity;
} str_t;

typedef struct node_t {
  struct node_t* prev;
  struct node_t* next;
  str_t str;
} node_t;

node_t* allocate(const char* message) {
  int len = strlen(message);

  node_t* node = malloc(sizeof *node);
  node->str.text = malloc(len + 1);
  strcpy(node->str.text, message);
  node->str.size = len;
  node->str.capacity = len;

  node->next = NULL;
  node->prev = NULL;

  return node;
}

bool list_add(node_t* root, const char* message) {
  if (root == NULL) {
    return false;
  }
  node_t* current = root;
  while (current->next) {
    current = current->next;
  }
  current->next = allocate(message);
  current->next->prev = current;

  return true;
}

bool list_remove(node_t** root, const char* message) {
  if (root == NULL || *root == NULL) {
    return false;
  }
  if (strcmp((*root)->str.text, message) == 0) {
    node_t* to_remove = *root;
    node_t* next = (*root)->next;
    *root = next;
    free(to_remove->str.text);
    free(to_remove);
    return true;
  }
  node_t* current = *root;
  while (current) {
    if (strcmp(current->str.text, message) == 0) {
      node_t* to_remove = current;
      node_t* prev = current->prev;
      node_t* next = current->next;
      prev->next = next;
      if (next) {
        next->prev = prev;
      }
      free(to_remove->str.text);
      free(to_remove);
      return true;
    }
    current = current->next;
  }
  return false;
}

node_t* list_find(node_t* root, const char* message) {
  if (root == NULL) {
    return NULL;
  }
  node_t* current = root;
  while (current) {
    if (strcmp(current->str.text, message) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

void display(node_t* root) {
  if (root == NULL) {
    return;
  }
  node_t* current = root;
  while (current) {
    if (current->next == NULL) {
      break;
    }
    printf("%s, ", current->str.text);
    current = current->next;
  }
  printf("%s\n", current->str.text);
}

int main(int argc, char** argv) {
  printf("%s", "Hello, World!\n");

  node_t* root = allocate("first");

  printf("msg: %s\n", root->str.text);

  list_add(root, "second");
  list_add(root, "third");
  list_add(root, "fourth");

  display(root);

  list_remove(&root, "first");

  display(root);

  list_remove(&root, "third");

  display(root);

  bool removed = list_remove(&root, "something");
  if (!removed) {
    printf("Could not remove \"something\"\n");
  }

  list_remove(&root, "fourth");

  display(root);

  list_add(root, "fifth");
  list_add(root, "sixth");
  list_add(root, "seventh");

  node_t* sixth = list_find(root, "sixth");
  printf("Found: %s\n", sixth->str.text);

  display(root);

  list_remove(&root, "second");
  list_remove(&root, "seventh");

  display(root);

  return 0;
}
