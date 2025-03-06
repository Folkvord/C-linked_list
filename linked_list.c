#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "linked_list.h"

int __invalid_index(Linked_list linked_list, int index);            // Sjekker om en indeks er gyldig
int __add_head(Linked_list* linked_list, void* data, size_t size);  // Legger til en node som skal bli hodet til listen
void __remove_head(Linked_list* linked_list);                       // Fjerner hodet


/* 
  Mulige optimaliseringer:
    - Det fuckings dilemmaet i ll_insert()
    - ll_create() ???????????????
  Mulige addisjoner:
    - Legg til funksjoner rettet mot stacker og køer
*/

// Initialiserer listen
void ll_create(Linked_list* linked_list){

  linked_list -> size = 0;

}


// Legger til en verdi øverst på listen (indeks 0)
int ll_add(Linked_list* linked_list, void* data, size_t size){

  if(linked_list -> size == 0){
    return __add_head(linked_list, data, size);
  }

  // Lag det nye hodet
  __Node* new_head = malloc(sizeof(__Node));
  if(!new_head){
    return FAILED;
  }

  // Alloker minne til datafeltet
  new_head -> __data = malloc(size);
  if(!new_head -> __data){
    free(new_head);
    return FAILED;
  }

  // Kopier over data til datafeltet
  memcpy(new_head -> __data, data, size);

  // Gi det nye hodet andre verdier
  __Node* old_head = linked_list -> __head;
  new_head -> __next = old_head;

  // Sett det nye hodet som det nye hodet
  linked_list -> __head = new_head;
  linked_list -> size++;

  return SUCCESS;

}


// Legger til en node i listen
int ll_append(Linked_list* linked_list, void* data, size_t size){

  if(linked_list -> size == 0){
    return __add_head(linked_list, data, size);
  }

  // Bla til halen
  __Node* current_node = linked_list -> __head;
  for(int i = 1; i < linked_list -> size; i++){
    current_node = current_node -> __next;
  }

  // Rydd plass til noden
  __Node* new_node = malloc(sizeof(__Node));
  if(!new_node){
    return FAILED;
  }

  // Rydd plass for datafeltet i noden
  new_node -> __data = malloc(size);
  if(!new_node -> __data){
    free(new_node);
    return FAILED;
  }

  // Legg til data
  memcpy(new_node -> __data, data, size);

  // Legg til andre verdier
  current_node -> __next = new_node;

  linked_list -> size++;

  return SUCCESS;

}


// Legger til en node på indeks "index"
int ll_insert(Linked_list* linked_list, int index, void* data, size_t size){

  // Om siste indeks
  if(index == linked_list -> size){
    return ll_append(linked_list, data, size);
  }

  // Om første indeks
  if(index == 0){
    return ll_add(linked_list, data, size);
  }

  // Sjekker om gyldig indeks
  if(__invalid_index(*linked_list, index)){
    return INVALID_INDEX;
  }

  // Sjekker om listen er tom og legger til noden som det nye hodet
  if(linked_list -> size == 0){
    return __add_head(linked_list, data, size);
  }

  // Bla til indeksen
  __Node* current_node = linked_list -> __head;
  for(int i = 0; i < index-1; i++){
    current_node = current_node -> __next;
  }

  // Gjør klar plass i minnet for den nye noden
  __Node* new_node = malloc(sizeof(__Node));
  if(!new_node){
    return FAILED;
  }

  // Legger til datafeltet
  new_node -> __data = malloc(size);
  if(!new_node -> __data){
    free(new_node);
    return FAILED;
  }

  // Kopierer over data
  memcpy(new_node -> __data, data, size);

  // Injiserer noden mellom nodene
  __Node* __next_node = current_node -> __next;
  current_node -> __next = new_node;
  new_node -> __next = __next_node;

  linked_list -> size++;

  return SUCCESS;

}


// Henter verdien på indeks "index" og lagrer innholdet i "store"
int ll_get(Linked_list* linked_list, int index, void** store, size_t size){

  // Sjekker om indeksen er gyldig
  if(__invalid_index(*linked_list, index)){
    return INVALID_INDEX;
  }

  // Blar til indeksen
  __Node* current_node = linked_list -> __head;
  for(int i = 0; i < index; i++){
    current_node = current_node -> __next;
  }  
  
  // Gjør klart minne for "store"
  *store = malloc(size);
  if(!*store){
    return FAILED;
  }

  // Kopierer over data til "store"
  memcpy(*store, current_node -> __data, size);
  
  return SUCCESS;

}


// Setter verdien på indeks "index"
int ll_set(Linked_list* linked_list, int index, void* data, size_t size){

  // Sjekker om indeksen er gyldig
  if(__invalid_index(*linked_list, index)){
    return INVALID_INDEX;
  }

  // Blar til noden 
  __Node* current_node = linked_list -> __head;
  for(int i = 0; i < index; i++){
    current_node = current_node -> __next;
  }

  // Overskriver datafeltet
  memcpy(current_node -> __data, data, size);

  return SUCCESS;

}


// Fjerne en node på indeks "index"
int ll_remove(Linked_list* linked_list, int index){

  // Sjekker om gyldig indeks
  if(__invalid_index(*linked_list, index)){
    return INVALID_INDEX;
  }

  // Om noden er hodet
  if(index == 0){
    __remove_head(linked_list);
    return SUCCESS;
  }

  // Blar til noden
  __Node* last_node;
  __Node* current_node = linked_list -> __head;
  for(int i = 0; i < index; i++){
    last_node = current_node;
    current_node = current_node -> __next;
  }

  // Sjøt den forrige noden sammen med whatever
  last_node -> __next = current_node -> __next;

  // Frigjør minnet til noden som skal slettes
  free(current_node);
  linked_list -> size--;

  return SUCCESS;

}


// Finner antallet ganger instansen av "data" dukker opp i listen
int ll_find(Linked_list* linked_list, void* data, int** store, size_t size){

  // Antall ganger "data" er i listen
  int match_amount = 0;

  // Bla gjennom hele listen
  __Node* current_node = linked_list -> __head;
  for(int i = 0; i < linked_list -> size; i++){
    
    // Sammenlign hva som er i minnet
    int match = memcmp(data, current_node -> __data, size) == 0;
    if(match){
      match_amount++;
    }

    current_node = current_node -> __next;

  }

  // Gjør klar store
  *store = malloc(size);
  if(!store){
    return FAILED;
  }

  memcpy(*store, &match_amount, size);
  
  return SUCCESS;

}


// Ødelegger hele listen og frigjør minnet
void ll_destroy(Linked_list* linked_list){

  // Om listen er tom
  if(!linked_list -> __head){
    linked_list -> size = 0;
    return;
  }

  // Fjern hodet
  __remove_head(linked_list);

  // Repeter fram til listen er tom
  ll_destroy(linked_list);

}





// Sjekker om en index er gyldig
int __invalid_index(Linked_list linked_list, int index){

  return (index < 0 || index >= linked_list.size);

}

// Legger til den første noden i listen
int __add_head(Linked_list* linked_list, void* data, size_t size){

  // Alloker minne til hodet
  linked_list -> __head = malloc(sizeof(__Node));
  if(!linked_list -> __head){
    return FAILED;
  }

  // Alloker minne til datafeltet til hodet
  // Dette gjøres for alle felt som er pekere
  linked_list -> __head -> __data = malloc(size);
  if(!linked_list -> __head -> __data){
    free(linked_list -> __head);
    return FAILED;
  }

  // Kopier over data til datafeltet
  memcpy(linked_list -> __head -> __data, data, size);

  // Ekstra info
  // Trenger ikke å allokere minne 
  // da dette er konkrete verdier og ikke pekere
  linked_list -> __head -> __next = NULL;

  linked_list -> size = 1;

  return SUCCESS;

}

// Fjerner hodet
void __remove_head(Linked_list* linked_list){

  __Node* head = linked_list -> __head;
  __Node* neck = head -> __next;
  
  linked_list -> __head = neck;

  free(head);

}