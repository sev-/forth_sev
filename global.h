/* global.h - объявления глобальных переменных */

BYTE vocabulary[65536];	/* словарь */

NUNSIGNED retstackhead;	/* вершина стэка возвратов */
NUNSIGNED stackhead;	/* вершина стэка */

NUNSIGNED vochead;	/* вершина словаря */

NUNSIGNED rpcf;		/* &rpcf */
NUNSIGNED h;		/* &h */
NUNSIGNED wminuslink;	/* &w-link */
NUNSIGNED s0;		/* &s0 */
NUNSIGNED r0;		/* &r0 */
NUNSIGNED fence;	/* &fence */
NUNSIGNED context;	/* &context */

NUNSIGNED forthcontext;	/* address of context-field in word forth */

NUNSIGNED lastname;	/* address of name-field last word */
