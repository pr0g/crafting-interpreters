#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct str_t {
  char* text;
  size_t size;
  size_t capacity; // does not include null terminator
} str_t;

typedef struct node_t {
  struct node_t* prev;
  struct node_t* next;
  str_t str;
} node_t;

node_t* allocate(const char* message) {
  if (!message) {
    return nullptr;
  }
  const size_t len = strlen(message);
  node_t* node = malloc(sizeof *node);
  if (!node) {
    return nullptr;
  }
  const size_t buffer_size = len + 1;
  node->str.text = malloc(buffer_size);
  if (!node->str.text) {
    free(node);
    return nullptr;
  }
  memcpy(node->str.text, message, buffer_size);
  node->str.size = len;
  node->str.capacity = len;
  node->next = nullptr;
  node->prev = nullptr;
  return node;
}

void deallocate(node_t** node) {
  if (!node || !*node) {
    return;
  }
  node_t* current = *node;
  while (current) {
    node_t* next = current->next;
    free(current->str.text);
    free(current);
    current = next;
  }
  *node = nullptr;
}

bool list_add(node_t** root, const char* message) {
  if (!root || !message) {
    return false;
  }
  if (!*root) {
    *root = allocate(message);
    return *root != nullptr;
  }
  node_t* current = *root;
  while (current->next) {
    current = current->next;
  }
  node_t* next = allocate(message);
  if (!next) {
    return false;
  }
  current->next = next;
  current->next->prev = current;
  return true;
}

bool list_remove(node_t** root, const char* message) {
  if (!root || !*root || !message) {
    return false;
  }
  if (strcmp((*root)->str.text, message) == 0) {
    node_t* to_remove = *root;
    node_t* next = (*root)->next;
    *root = next;
    if (next) {
      next->prev = nullptr;
    }
    free(to_remove->str.text);
    free(to_remove);
    return true;
  }
  node_t* current = (*root)->next;
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
  if (!root || !message) {
    return nullptr;
  }
  node_t* current = root;
  while (current) {
    if (strcmp(current->str.text, message) == 0) {
      return current;
    }
    current = current->next;
  }
  return nullptr;
}

void display(node_t* root) {
  if (!root) {
    printf("--- empty list ---\n");
    return;
  }
  node_t* current = root;
  while (current) {
    printf("%s", current->str.text);
    if (current->next) {
      printf(", ");
    }
    current = current->next;
  }
  printf("\n");
}

int main(int argc, char** argv) {
  printf("%s", "Hello, World!\n");

  node_t* root = allocate("first");

  printf("msg: %s\n", root->str.text);

  list_add(&root, "second");
  list_add(&root, "third");
  list_add(&root, "fourth");

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

  list_add(&root, "fifth");
  list_add(&root, "sixth");
  list_add(&root, "seventh");

  node_t* sixth = list_find(root, "sixth");
  printf("Found: %s\n", sixth->str.text);

  display(root);

  list_remove(&root, "second");
  list_remove(&root, "seventh");

  display(root);

  list_remove(&root, "fifth");
  list_remove(&root, "sixth");

  display(root);

  list_add(&root, "this");
  list_add(&root, "is");
  list_add(&root, "a");
  list_add(&root, "list");

  display(root);

  deallocate(&root);

  display(root);

  return 0;
}
