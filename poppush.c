/* poppush.c - push и pop для всех типов */

#include "stack.h"

SINGLE PopSingle()
{
  union
  {
    BYTE byte[SINGLESIZE];
    SINGLE x;
  } tmp;
  int i;

  stackhead -= SINGLESIZE;
  for(i = SINGLESIZE-1; i >= 0; i--)
    tmp.byte[i] = vocabulary[stackhead+i];

  return tmp.x;
}

NUNSIGNED PopNUnsigned()
{
  union
  {
    BYTE byte[SINGLESIZE];
    NUNSIGNED x;
  } tmp;
  int i;

  stackhead -= SINGLESIZE;
  for(i = SINGLESIZE-1; i >= 0; i--)
    tmp.byte[i] = vocabulary[stackhead+i];

  return tmp.x;
}

DOUBLE PopDouble()
{
  union
  {
    BYTE byte[DOUBLESIZE];
    DOUBLE x;
  } tmp;
  int i;

  stackhead -= DOUBLESIZE;
  for(i = DOUBLESIZE-1; i >= 0; i--)
    tmp.byte[i] = vocabulary[stackhead+i];

  return tmp.x;
}

DUNSIGNED PopDUnsigned()
{
  union
  {
    BYTE byte[DOUBLESIZE];
    DUNSIGNED x;
  } tmp;
  int i;

  stackhead -= DOUBLESIZE;
  for(i = DOUBLESIZE-1; i >= 0; i--)
    tmp.byte[i] = vocabulary[stackhead+i];

  return tmp.x;
}

FLOAT PopFloat()
{
  union
  {
    BYTE byte[FLOATSIZE];
    FLOAT x;
  } tmp;
  int i;

  stackhead -= FLOATSIZE;
  for(i = FLOATSIZE-1; i >= 0; i--)
    tmp.byte[i] = vocabulary[stackhead+i];

  return tmp.x;
}

void PushSingle(a)
SINGLE a;
{
  union
  {
    BYTE byte[SINGLESIZE];
    SINGLE x;
  } tmp;
  int i;

  tmp.x = a;
  for(i = 0; i < SINGLESIZE; i++)
    vocabulary[stackhead+i] = tmp.byte[i];
  stackhead += SINGLESIZE;
}

void PushNUnsigned(a)
NUNSIGNED a;
{
  union
  {
    BYTE byte[SINGLESIZE];
    NUNSIGNED x;
  } tmp;
  int i;

  tmp.x = a;
  for(i = 0; i < SINGLESIZE; i++)
    vocabulary[stackhead+i] = tmp.byte[i];
  stackhead += SINGLESIZE;
}

void PushDouble(a)
DOUBLE a;
{
  union
  {
    BYTE byte[DOUBLESIZE];
    DOUBLE x;
  } tmp;
  int i;

  tmp.x = a;
  for(i = 0; i < DOUBLESIZE; i++)
    vocabulary[stackhead+i] = tmp.byte[i];
  stackhead += DOUBLESIZE;
}

void PushDUnsigned(a)
DUNSIGNED a;
{
  union
  {
    BYTE byte[DOUBLESIZE];
    DUNSIGNED x;
  } tmp;
  int i;

  tmp.x = a;
  for(i = 0; i < DOUBLESIZE; i++)
    vocabulary[stackhead+i] = tmp.byte[i];
  stackhead += DOUBLESIZE;
}

void PushFloat(a)
FLOAT a;
{
  union
  {
    BYTE byte[FLOATSIZE];
    FLOAT x;
  } tmp;
  int i;

  tmp.x = a;
  for(i = 0; i < FLOATSIZE; i++)
    vocabulary[stackhead+i] = tmp.byte[i];
  stackhead += FLOATSIZE;
}

NUNSIGNED FetchNUnsigned(a)
NUNSIGNED a;
{
  union
  {
    BYTE byte[SINGLESIZE];
    NUNSIGNED x;
  } tmp;
  int i;

  for(i = SINGLESIZE-1; i >= 0; i--)
    tmp.byte[i] = vocabulary[a+i];

  return tmp.x;
}

DUNSIGNED FetchDUnsigned(a)
NUNSIGNED a;
{
  union
  {
    BYTE byte[DOUBLESIZE];
    DUNSIGNED x;
  } tmp;
  int i;

  for(i = DOUBLESIZE-1; i >= 0; i--)
    tmp.byte[i] = vocabulary[a+i];

  return tmp.x;
}

void StoreNUnsigned(addr, a)
NUNSIGNED addr;
NUNSIGNED a;
{
  union
  {
    BYTE byte[SINGLESIZE];
    NUNSIGNED x;
  } tmp;
  int i;

  tmp.x = a;
  for(i = 0; i < SINGLESIZE; i++)
    vocabulary[addr+i] = tmp.byte[i];
}

void StoreDUnsigned(addr, a)
NUNSIGNED addr;
DUNSIGNED a;
{
  union
  {
    BYTE byte[DOUBLESIZE];
    DUNSIGNED x;
  } tmp;
  int i;

  tmp.x = a;
  for(i = 0; i < DOUBLESIZE; i++)
    vocabulary[addr+i] = tmp.byte[i];
}

SINGLE FetchSingle(a)
NUNSIGNED a;
{
  union
  {
    BYTE byte[SINGLESIZE];
    SINGLE x;
  } tmp;
  int i;

  for(i = SINGLESIZE-1; i >= 0; i--)
    tmp.byte[i] = vocabulary[a+i];

  return tmp.x;
}

void StoreSingle(addr, a)
NUNSIGNED addr;
SINGLE a;
{
  union
  {
    BYTE byte[SINGLESIZE];
    SINGLE x;
  } tmp;
  int i;

  tmp.x = a;
  for(i = 0; i < SINGLESIZE; i++)
    vocabulary[addr+i] = tmp.byte[i];
}
