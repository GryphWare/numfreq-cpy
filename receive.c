#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define table_size 20

typedef struct node{
  int data_key;
  int freq;
  struct node *next;
}node;

typedef struct hashmap{
  node *table[table_size];
}hashmap;

void initTable(hashmap *map){
  for(size_t i = 0; i < table_size; i++){
    map->table[i] = NULL;
  }
}

unsigned int hash(int num){
  return abs(num) % table_size;
}

node *create(int data){
  node *new = (node*) malloc(sizeof(node));
  new->data_key = data;
  new->freq = 1;
  new->next = NULL;
  return new;
}

void insert_node(int data, hashmap *map){
  unsigned int index = hash(data);
  node *entry = map->table[index];
  while(entry){
    if(entry->data_key == data){
      entry->freq++;
      return;
    }
    entry = entry->next;
  }
  node *new_node = create(data);
  new_node->next = map->table[index];
  map->table[index] = new_node;
}

void display_freq(hashmap *map){
  for(size_t i = 0; i < table_size; i++){
    node *entry = map->table[i];
    while(entry){
      printf("so %d hien %d lan\n", entry->data_key, entry->freq);
      entry = entry->next;
    }
  }
}

void insert_to_hashmap(char *line, hashmap *map){
  for(size_t i = 0; line[i] != '\0'; i++){
    if(isdigit((unsigned char)line[i])){
      int digit = line[i] - '0';
      insert_node(digit, map);
    }
  }
}

void free_all(hashmap *map){
  for(size_t i = 0; i < table_size; i++){
    node *entry = map->table[i];
    while(entry){
      node *temp = entry;
      entry = entry->next;
      free(temp);
    }
  }
}

int main(){

  hashmap map;

  initTable(&map);

  FILE *file = fopen("random_num.txt", "r");
  if(!file){
    fprintf_s(stderr, "cant access to file!\n", 30);
    return EXIT_FAILURE;
  }

  char line[256];
  while(fgets(line, sizeof(line), file) != NULL){
    insert_to_hashmap(line, &map);
  }
  
  fclose(file);

  display_freq(&map);

  free_all(&map);
  
  return EXIT_SUCCESS;
}
