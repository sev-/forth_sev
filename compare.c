/* compare.c - операции сравнения */

#include "stack.h"

void zeroless()		/* 0<	n1 -> n1<0 */
{
  PushSingle((SINGLE)(PopSingle() < 0) );
}

void zeroeq()		/* 0=	n1 -> n1==0 */
{
  PushSingle((SINGLE)(PopSingle() == 0) );
}

void zerogreat()	/* 0>	n1 -> n1>0 */
{
  PushSingle((SINGLE)(PopSingle() > 0) );
}

void less()	/* <	n1, n2 -> n1<n2 */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle(b < a);
}

void eq()	/* =	n1, n2 -> n1==n2 */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle(a == b);
}

void great()	/* >	n1, n2 -> n1>n2 */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle(b > a);
}

void dless()	/* d<	d1, d2 -> d1<d2 */
{
  DOUBLE a, b;

  a = PopDouble();
  b = PopDouble();

  PushSingle(b < a);
}

void uless()	/* u<	u1, u2 -> u1<u2 */
{
  NUNSIGNED a, b;

  a = PopNUnsigned();
  b = PopNUnsigned();

  PushSingle(b < a);
}
