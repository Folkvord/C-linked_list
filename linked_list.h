#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER

// Returnkoder
#define SUCCESS 0
#define FAILED  1
#define INVALID_INDEX -1

// Nodestrukturen
typedef struct __Node {

  void* __data;             // Data som tar alle datatyper
  struct __Node* __next;    // Neste node i linjen

} __Node;

// En struct som fungerer som linkedlist objektet
typedef struct Linked_list {

  struct __Node* __head;
  int size;

} Linked_list;


// Lager en linked list
void ll_create(Linked_list* __linked_list);

// Legger til en node øverst på listen
int ll_add(Linked_list* __linked_list, void* __data, size_t __size);

// Legger til en node bakerst i listen: Tar inn listen og data
int ll_append(Linked_list* __linked_list, void* __data, size_t __size);

// Injiserer en node på en indeks
int ll_insert(Linked_list* __linked_list, int __index, void* __data, size_t __size);

// Henter en verdi fra en indeks
int ll_get(Linked_list* __linked_list, int __index, void** __store, size_t __size);

// Setter en verdi til en indeks
int ll_set(Linked_list* __linked_list, int __index, void* __data, size_t __size);

// Fjerner en node på en indeks
int ll_remove(Linked_list* __linked_list, int __index);

// Finner antall ganger en instanse av "data" som dukker opp i listen. Returnerer en tabell med indeksene
int ll_find(Linked_list* __linked_list, void* data, int**__store, size_t size);

// Sletter listen og frigjør plassen i heapen
void ll_destroy(Linked_list* __linked_list);


#endif