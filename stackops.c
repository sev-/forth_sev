/* stackops.c - операции со стэком */

#include "stack.h"

void Dup()	/* dup 		n1 -> n1, n2 */
{
  SINGLE a;

  a = PopSingle();

  PushSingle(a);
  PushSingle(a);
}

void qdup()	/* ?dup 	n1 -> n1, |n1| */
{
  SINGLE a;

  a = PopSingle();

  PushSingle(a);
  if(a)
    PushSingle(a);
}

void drop()		/* drop		n1 -> */
{
  stackhead -= SINGLESIZE;
}

void over()	/* over 	n1, n2 -> n1, n2, n1 */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle(b);
  PushSingle(a);
  PushSingle(b);
}

void rot()	/* rot 	n1, n2, n3 -> n2, n3, n1 */
{
  SINGLE a, b, c;

  a = PopSingle();
  b = PopSingle();
  c = PopSingle();

  PushSingle(b);
  PushSingle(a);
  PushSingle(c);
}

void swap()	/* swap 	n1, n2 -> n2, n1 */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle(a);
  PushSingle(b);
}

void pick()	/* pick		d1, d2, ..., dn, n -> d1, d2, ..., dn, d1 */
{
  SINGLE n;

  n = PopSingle();
  PushNUnsigned(FetchNUnsigned(stackhead-n*SINGLESIZE-1));
}

void twoswap()		/* 2swap	d2, d1 -> d1, d2 */
{
  DOUBLE d1, d2;

  d1 = PopDouble();
  d2 = PopDouble();
  PushDouble(d1);
  PushDouble(d2);
}

void minusrot()		/* -rot		n1, n2, n3 -> n3, n1, n2 */
{
  SINGLE a, b, c;

  a = PopSingle();
  b = PopSingle();
  c = PopSingle();

  PushSingle(c);
  PushSingle(a);
  PushSingle(b);
}

void twodup()		/* 2dup		d -> d, d */
{
  DOUBLE d;

  d = PopDouble();
  PushDouble(d);
  PushDouble(d);
}

void twodrop()		/* 2drop	d -> */
{
  stackhead -= DOUBLESIZE;
}

void press()		/* press	n1, n2 -> n2	*/
{
  SINGLE n2;

  n2 = PopSingle();
  (void)PopSingle();
  PushSingle(n2);
}

void twoover()	/* 2over 	d1, d2 -> d1, d2, d1 */
{
  DOUBLE a, b;

  a = PopDouble();
  b = PopDouble();

  PushDouble(b);
  PushDouble(a);
  PushDouble(b);
}

void spfetch()	/* sp@		-> a */
{
  PushNUnsigned(stackhead);
}

void spstore()	/* sp!		a -> */
{
  stackhead = PopNUnsigned();
}

void roll()	/* roll		d1, d2, ..., dn, n -> d2, d3, ..., dn, d1 */
{
  SINGLE n;
  NUNSIGNED b;
  int i;

  n = PopSingle();
  b = FetchNUnsigned(stackhead-n*SINGLESIZE-1);
  
  for(i = stackhead-n*SINGLESIZE; i > stackhead-1; i++)
    vocabulary[i] = vocabulary[i+2];

  PushNUnsigned(b);
}

