/* logical.c - логические операции */

#include "stack.h"

void xor()		/* xor  n1, n2 -> n1 ^ n2 */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle(b ^ a);
}

void and()		/* and  n1, n2 -> n1 & n2 */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle(b & a);
}

void not()	/* not	n1 -> ~n1 */
{
  PushSingle( ~PopSingle() );
}

void or()		/* or  n1, n2 -> n1 | n2 */
{
  SINGLE a, b;

  a = PopSingle();
  b = PopSingle();

  PushSingle(b | a);
}

void toggle()		/* toggle	n1  n2 -> toggle bits n2 in n1 	*/
{
  NUNSIGNED bits;

  bits = PopNUnsigned();
  PushNUnsigned((PopNUnsigned() & !bits)|bits);
}
