/* vocabulary.c - словарь */

#include <ctype.h>
#include "vocabulary.h"  

void init_voc()
{
  BYTE *address = vocabulary;
  char *nameptr;
  BYTE len;
  union
  {
    NUNSIGNED s;
    BYTE b[2];
  } previous;
  NUNSIGNED previous1;
  union
  {
    void (* p)();
    BYTE b[SIZEPTR];
  } PtrToFunc;
  int i, j;

  previous.s = 0;

  for(i = 0; i < 48; i++)	/* для служебных целей */
    StoreNUnsigned(i*2, i*2);
  address += i*2;

  for(i = 0; i < NUMPRIMITIVES; i++)
  {
    previous1 = (SINGLE)(address - vocabulary);	/* для поля связи */

    nameptr = primitives[i].name;
    len = (BYTE)strlen(nameptr);
    *address = len;		/* длина имени */
    if(!len)		/* null-word */
      *address |= 0x80;	/* immediate-state */
    address ++;
    for(; *nameptr; address++, nameptr++)	/* имя */
      *address = *nameptr;
    *address++ = previous.b[0];	 /* поле связи */
    *address++ = previous.b[1];

    if(!i)	/* forth */
    {
      StoreNUnsigned(address-vocabulary, 38);	/* (forth) */
      address += 2;
      *address++ = 01;	/* word len 	fictive word header */
      *address++ = 20;	/* space */
      forthcontext = (NUNSIGNED)(address - vocabulary);
      address += 2;
      *address++ = 0;	/* voc-link */
      *address++ = 0;
    }
    else
    {
      *address++ = 0;		/* поле кода (0000h - примитив) */
      *address++ = 0;

      PtrToFunc.p = primitives[i].ptr;	/* указатель на Си-функцию */
      for(j = 0; j < SIZEPTR; j++, address++)
        *address = PtrToFunc.b[j];
    }

    previous.s = previous1;	/* указатель на предыдущее слово */
  }
  for(i = 0; i < NUMVARS; i++)
  {
    previous1 = (SINGLE)(address - vocabulary);	/* для поля связи */

    nameptr = Variables[i].name;
    len = (BYTE)strlen(nameptr);
    *address = len;		/* длина имени */
    address ++;
    for(; *nameptr; address++, nameptr++)	/* имя */
      *address = *nameptr;
    *address++ = previous.b[0];	 /* поле связи */
    *address++ = previous.b[1];

    *address++ = 8;		/* поле кода (0008h - переменная) */
    *address++ = 0;

    *(Variables[i].var) = (NUNSIGNED)(address-vocabulary);/* Адрес переменной */
    address += 2;		/* Значение переменной пропустить */

    previous.s = previous1;	/* указатель на предыдущее слово */
  }
  lastname = previous.s;
  vochead = (NUNSIGNED)(address - vocabulary); /* установить вершину словаря */
}

void (*find_voc(s, n))()
char *s;
int *n;
{
  int i;
  char buf[80];

  while(*s && isspace(*s))
    s++, n[0]++;

  for(i = 0; *s && !isspace(*s); buf[i++] = *s++, n[0]++);
  buf[i] = 0;

  for(i = 0; i < NUMPRIMITIVES; i++)
    if(!strcmp(buf, primitives[i].name))
      return primitives[i].ptr;
  return primitives[i].ptr;
}
