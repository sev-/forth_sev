/* vocabulary.c - словарь */

#define MAIN

#include "vocabulary.h"


void dot() {}
void ddot() {}
void null() {}
void quit() {}

main()
{
  BYTE *address = vocabulary;
  char *nameptr;
  BYTE len;
  union
  {
    SINGLE s;
    BYTE b[2];
  } previous;
  SINGLE previous1;
  union
  {
    void (* p)();
    BYTE b[SIZEPTR];
  } PtrToFunc;
  int i, j;

  previous.s = 0;

  address += 64;	/* для служебных целей */

  printf("Примитивов %d\t", NUMPRIMITIVES);
  printf("Переменных %d\n", NUMVARS);

  for(i = 0; i < NUMPRIMITIVES; i++)
  {
    previous1 = (SINGLE)(address - vocabulary);	/* для поля связи */

    nameptr = primitives[i].name;
    len = (BYTE)strlen(nameptr);
    printf("длина имени: %d\tимя: ", len);
    address ++;
    for(; *nameptr; address++, nameptr++)	/* имя */
      printf("%c", *nameptr);
    printf("\tполе связи: %d\t", previous.s);
    *address++ = previous.b[0];	 /* поле связи */
    *address++ = previous.b[1];

    *address++ = 0;		/* поле кода (0000h - примитив) */
    *address++ = 0;

    PtrToFunc.p = primitives[i].ptr;	/* указатель на Си-функцию */
    printf("указатель на Си-функцию: %0x\n", PtrToFunc.p);
    for(j = 0; j < SIZEPTR; j++, address++)
      *address = PtrToFunc.b[j];

    previous.s = previous1;	/* указатель на предыдущее слово */
  }
  for(i = 0; i < NUMVARS; i++)
  {
    previous1 = (SINGLE)(address - vocabulary);	/* для поля связи */

    nameptr = Variables[i].name;
    len = (BYTE)strlen(nameptr);
    printf("длина имени: %d\tимя: ", len);
    address ++;
    for(; *nameptr; address++, nameptr++)	/* имя */
      printf("%c", *nameptr);
    printf("\tполе связи: %d\n", previous.s);
    *address++ = previous.b[0];	 /* поле связи */
    *address++ = previous.b[1];

    *address++ = 1;		/* поле кода (0004h - переменная) */
    *address++ = 0;

    *(Variables[i].var) = (NUNSIGNED)(address-vocabulary);/* Адрес переменной */
    address += 2;		/* Значение переменной пропустить */

    previous.s = previous1;	/* указатель на предыдущее слово */
  }
  vochead = (SINGLE)(address - vocabulary); /* установить вершину словаря */
  printf("\nвершинa словаря: %04xh (%d)\n", vochead, vochead);
}
