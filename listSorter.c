#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "string.h"
#include "stdbool.h"

typedef struct list_element
{
  unsigned long index;
  char label[10];               //10 char + "/0" fine stringa
  struct list_element* prev;
  struct list_element* next;
} list_element;

typedef struct
{
  list_element* head;
  list_element* tail;
  int size;
} list;

char stringa[10];
void create_label()
{
  for (int i = 0; i < 10; i++)
  {
    stringa[i] = (char)((rand()%25)+97); //da 97 a 122: char in ascii
  }
}

list_element create_element()
{
  list_element new_element;
  new_element.index = rand()%100;             //index tra 0 e 99
  create_label();
  strcpy(new_element.label, stringa);
  new_element.prev = NULL;                    //li crea senza i puntatori a next e prev
  new_element.next = NULL;

  return new_element;
}

// void bubbleSort(char *items, int count) 	//algoritmo di scambio
// {
// 	char t;
// 	for(int a = 1; a < count; a++)
// 	{
// 		for(int b = count-1; b >= a; b--)
// 		{
// 		    if(items[b-1] > items[b])
// 			{
// 				t = items[b-1];
// 				items[b-1] = items[b];
// 				items[b] = t;
// 		    }
// 		}
// 	}
// }

int pos = 0;
void stampaDati(list_element element)
{
  printf("ELEMENT %d\n", pos);
  pos++;
  printf("-index: %lu\n", element.index);
  printf("-label: %s\n", element.label);
  if(element.prev == NULL)
    printf("-prev -> index: NULL | label: NULL\n");
  else
    printf("-prev -> index: %lu | label: %s\n", element.prev->index, element.prev->label);
  if(element.next == NULL)
    printf("-next -> index: NULL | label: NULL\n");
  else
  {
    printf("-next -> index: %lu | label: %s\n\n", element.next->index, element.next->label);
    printf("      ^ | \n");
    printf("      | v \n\n");
  }
}

int main(int argc, char const *argv[])
{

  srand(time(NULL));                          //puù venire chiamato solo una volta
  int randDimension = ((rand() % 601) + 300);   //rand tra 300 e 900 (era rand()% 601) + 300

  list list;
  list.size = randDimension;
  list.head = NULL;
  list.tail = NULL;

  list_element elements[list.size]; //array di list_element grande list.size
                                    //so già quanti elementi ho, per non usare malloc

  for (int i = 0; i < list.size; i++)
  {
    elements[i] = create_element(); //inserisco gli elementi nel vettore
    if(i == 0)  //il primo non ha predecessore
    {
      elements[i].prev = NULL;
      list.head = &elements[i];
    }

    else if(i == list.size - 1) //l'ultimo non ha successore
    {
      elements[i].next = NULL;
      elements[i].prev = &elements[i - 1];
      elements[i - 1].next = &elements[i];
      list.tail = &elements[i];
    }
    else
    {
      elements[i].prev = &elements[i - 1]; //collega elemento al predecessore
      elements[i - 1].next = &elements[i];  //collega il predecessere all'elemento
    }
  }

  printf("dimensione lista: %d\n\n", list.size);

  bool thereIsElement;
  list_element element;
  if(list.head != NULL)  //se c'è il puntatore alla testa
  {
    thereIsElement = true;
    element = *list.head; //uso come elemento quello puntato dal puntatore
  }
  else
    thereIsElement = false;

  while(thereIsElement) //finchè l'elemento non ha NULL come successivo
  {
    stampaDati(element);
    if(element.next == NULL) //se non c'è il puntatore all'elemento successivo
      thereIsElement = false;
    else                        //il puntatore next punta a qualcosa
      element = *element.next;  //quel qualcosa diventa il prossimo elemento
  }

  // for (int i = 0; i < list.size; i++) {
  //   stampaDati(elements[i]);
  //}

  printf("\nLIST_INFO\n");
  printf("head -> index: %lu  | label: %s\n", list.head->index, list.head->label);
  printf("tail -> index: %lu  | label: %s\n", list.tail->index, list.tail->label);
  printf("size = %d\n", list.size);

  return 0;
}
