/* retstack.c - операции со стэком возвратов */

#include "stack.h"

void toR()	/* >r	n1 -> */
{
  StoreNUnsigned(retstackhead, PopNUnsigned());
  retstackhead += 2;
  StoreNUnsigned(rpcf, retstackhead);
}

void fromR()	/* r>	-> n1 */
{
  retstackhead -= 2;
  PushNUnsigned(FetchNUnsigned(retstackhead));
  StoreNUnsigned(rpcf, retstackhead);
}

void Rfetch()	/* r@	-> n1 */
{
  PushNUnsigned(FetchNUnsigned(retstackhead-2));
}

void rpfetch()	/* rp@		-> a */
{
  PushNUnsigned(retstackhead);
}

void rpstore()	/* rp!		a -> */
{
  retstackhead = PopSingle();
  StoreNUnsigned(rpcf, retstackhead);
}

void Rdrop()
{
  retstackhead -= SINGLESIZE;
  StoreNUnsigned(rpcf, retstackhead);
}

void Rpick()	/* rpick	d1, d2, ..., dn, n -> d1, d2, ..., dn, d1 */
{
  StoreNUnsigned(retstackhead, FetchNUnsigned(retstackhead-PopSingle()
							*SINGLESIZE-1));
  retstackhead += SINGLESIZE;
  StoreNUnsigned(rpcf, retstackhead);
}

void Rj()	/* j		-> n */
{
  PushSingle(FetchSingle(retstackhead - 4*SINGLESIZE));
}

void Rk()	/* k		-> n */
{
  PushSingle(FetchSingle(retstackhead - 7*SINGLESIZE));
}
