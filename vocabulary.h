#include "stack.h"

#define SIZEPTR sizeof(void (*)())
#define NUMPRIMITIVES sizeof(primitives)/sizeof(PRIMITIVES)
 
typedef struct PRIMITIVES
{
  char *name;
  void (* ptr)();
} PRIMITIVES;

void dot();
void ddot();
void quit();

PRIMITIVES primitives[] =
{
  "forth",	0,		/* (forth) in interpret.c */
  "+",		plus,		/* math.c */
  "-",		minus,
  "*",		mul,
  "1+",		oneplus,
  "1-",		oneminus,
  "/mod",	divmod,
  "2+",		twoplus,
  "2-",		twominus,
  "2/",		twodiv,
  "abs",	Abs,
  "2*",		twomul,
  "d+",		dplus,
  "dnegate",	dnegate,
  "max",	max,
  "min",	min,
  "negate",	negate,
  "true",	true,
  "false",	false,
  "um*",	ummul,
  "du/mod",	dudivmod,
  "u/mod",	udivmod,
  "digit",	digit,
  "dup",	Dup,		/* stackops.c */
  "?dup",	qdup,
  "drop",	drop,
  "over",	over,
  "rot",	rot,
  "swap",	swap,
  "pick",	pick,
  "2swap",	twoswap,
  "-rot",	minusrot,
  "2dup",	twodup,
  "2drop",	twodrop,
  "press",	press,
  "2over",	twoover,
  "sp@",	spfetch,
  "sp!",	spstore,
  "roll",	roll,
  "!",		store,		/* mem.c */
  "+!",		plusstore,
  "@",		fetch,
  "c!",		cstore,
  "c@",		cfetch,
  "cmove",	cmove,
  "cmove>",	cmoverev,
  "<cmove>",	cmovesel,
  "fill",	fill,
  "0>bl",	zerotobl,
  ",",		comma,
  "c,",		ccomma,
  "here",	here,
  "allot",	allot,
  "2!",		twostore,
  "2@",		twofetch,
  "-!",		minusstore,
  "0!",		zerostore,
  "1+!",	oneplusstore,
  "1-!",	oneminusstore,
  "-trailing",	minustrailing,
  "-text",	minustext,
  "?word",	qword,
  "count",	count,
  "enclose",	enclose,
  "xor",	xor,		/* logical.c */
  "and",	and,
  "not",	not,
  "or",		or,
  "toggle",	toggle,
  "0<",		zeroless,	/* compare.c */
  "0=",		zeroeq,
  "0>",		zerogreat,
  "<",		less,
  "=",		eq,
  ">",		great,
  "d<",		dless,
  "u<",		uless,
  ">r",		toR,		/* retstack.c */
  "r>",		fromR,
  "r@",		Rfetch,
  "rp@",	rpfetch,
  "rp!",	rpstore,
  "rdrop",	Rdrop,
  "Rpick",	Rpick,
  "i",		Rfetch,
  "j",		Rj,
  "k",		Rk,
  "",		Rdrop,		/* null-word */
  "(emit)",	emit,		/* terminal.c */
  "(key)",	key,
  "(cr)",	cr,
  "?key",	qkey,
  "fflush",	fflushstdout,
  "bye",	quit,		/* stack.c */
  "..",		dot
};

typedef struct VAR
{
  char *name;
  NUNSIGNED	*var;		/* var - addres of constant */
} VAR;

VAR Variables[] =
{
  "rpcf",	&rpcf,
  "h",		&h,
  "w-link",	&wminuslink,
  "s0",		&s0,
  "r0",		&r0,
  "fence",	&fence,
  "context",	&context
};

#define NUMVARS sizeof(Variables)/sizeof(VAR)
