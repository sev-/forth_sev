/* math.c - математические опреации */

#include "stack.h"

void plus()	/* +	n1, n2 -> n1+n2 */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle(a + b);
}

void minus()	/* -	n1, n2 -> n1-n2 */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle(b - a);
}

void mul()	/* *	n1, n2 -> n1*n2 */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle(a * b);
}

void oneplus() /* 1+	n1 -> n1+1 */
{
  PushSingle(PopSingle() + 1);
}

void oneminus() /* 1-	n1 -> n1-1 */
{
  PushSingle(PopSingle() - 1);
}

void divmod()	/* /mod		n1, n2 -> n1%n2, n1/n2 */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  if(a)
  {
    PushSingle(b % a);
    PushSingle(b / a);
  }
  else
    PushDouble(0);
}

void twoplus() /* 2+	n1 -> n1+2 */
{
  PushSingle(PopSingle() + 2);
}

void twominus() /* 2-	n1 -> n1-2 */
{
  PushSingle(PopSingle() - 2);
}

void twodiv() /* 2/	n1 -> n1/2 */
{
  PushSingle(PopSingle() / 2);
}

void Abs()	/* abs 	n1 -> |n1| */
{
  SINGLE a;

  a = PopSingle();

  a = (a < 0) ? -a : a;
  PushSingle(a);
}

void twomul() /* 2*	n1 -> n1*2 */
{
  PushSingle(PopSingle() * 2);
}

void dplus()	/* d+	d1, d2 -> d1+d2 */
{
  DOUBLE a, b;

  a = PopDouble();
  b = PopDouble();

  PushDouble(a + b);
}

void dnegate()	/* dnegate	d1 -> -d1 */
{
  PushDouble( -PopDouble() );
}

void max()	/* max	n1, n2 -> n */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle((a > b) ? a : b);
}

void min()	/* min	n1, n2 -> n */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle((a < b) ? a : b);
}

void negate()	/* negate	n1 -> -n1 */
{
  PushSingle( -PopSingle() );
}

void ummul()	/* um*	u1, u2 -> (ud)u1*u2 */
{
  NUNSIGNED a, b;
  DUNSIGNED c;

  a = PopNUnsigned();
  b = PopNUnsigned();

  c = (DUNSIGNED)a * (DUNSIGNED)b;
  PushDUnsigned(c);
}

void true()	/* true		-> -1 */
{
  PushSingle(-1);
}

void false()	/* false	-> 0 */
{
  PushSingle(0);
}

void dudivmod()	/* du/mod		du1, du2 -> du1%du2, du1/du2 */
{
  DUNSIGNED a, b;

  a = PopDUnsigned();
  b = PopDUnsigned();

  if(a)
  {
    PushDUnsigned(b % a);
    PushDUnsigned(b / a);
  }
  else
  {
    PushDUnsigned(0);
    PushDUnsigned(0);
  }
}

void udivmod()	/* u/mod		u1, u2 -> u1%u2, u1/u2 */
{
  NUNSIGNED a, b;

  a = PopNUnsigned();
  b = PopNUnsigned();

  if(a)
  {
    PushNUnsigned(b % a);
    PushNUnsigned(b / a);
  }
  else
    PushDUnsigned(0);
}

void digit()	/* digit	c, base -> (n, -1) | 0 */
{
  NUNSIGNED base, c;

  base = PopNUnsigned();
  c = PopNUnsigned();

  if((BYTE)c < '0')
  {
    PushNUnsigned(0);
    return;
  }
  if((BYTE)c > '9')
    c -= 'a';
  else
    c -= '0';

  if(c > base)
  {
    PushNUnsigned(0);
    return;
  }
  PushNUnsigned(c);
  PushSingle(-1);
}
