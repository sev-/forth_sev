/* extern.h - объявление функций */

/* poppush.c */
SINGLE		PopSingle();
NUNSIGNED	PopNUnsigned();
DOUBLE		PopDouble();
DUNSIGNED	PopDUnsigned();
FLOAT		PopFloat();
void PushSingle();
void PushNUnsigned();
void PushDouble();
void PushDUnsigned();
void PushFloat();
NUNSIGNED	FetchNUnsigned();
DUNSIGNED	FetchDUnsigned();
SINGLE		FetchSingle();
void StoreNUnsigned();
void StoreDUnsigned();
void StoreSingle();

/* math.c */
void plus();		/* + */
void minus();		/* - */
void mul();		/* * */
void oneplus();		/* 1+ */
void oneminus();	/* 1- */
void divmod();		/* /mod */
void twoplus();		/* 2+ */
void twominus();	/* 2- */
void twodiv();		/* 2/ */
void Abs();		/* abs */
void twomul();		/* 2* */
void dplus();		/* d+ */
void dnegate();		/* dnegate */
void max();		/* max */
void min();		/* min */
void negate();		/* negate */
void true();		/* true */
void false();		/* false */
void ummul();		/* um* */
void dudivmod();	/* du/mod */
void udivmod();		/* u/mod */
void digit();		/* digit */

/* stackops.c */
void Dup();		/* dup */
void qdup();		/* ?dup */
void drop();		/* drop */
void over();		/* over */
void rot();		/* rot */
void swap();		/* swap */
void pick();		/* pick */
void twoswap();		/* 2swap */
void minusrot();	/* -rot */
void twodup();		/* 2dup */
void twodrop();		/* 2drop */
void press();		/* press */
void twoover();		/* 2over */
void spfetch();		/* sp@ */
void spstore();		/* sp! */
void roll();		/* roll */

/* mem.c */
void store();		/* ! */
void plusstore();	/* +! */
void fetch();		/* @ */
void cstore();		/* c! */
void cfetch();		/* c@ */
void cmove();		/* cmove */
void cmoverev();	/* cmove> */
void cmovesel();	/* <cmove> */
void fill();		/* fill */
void zerotobl();	/* 0>bl */
void comma();		/* , */
void ccomma();		/* c, */
void here();		/* here */
void allot();		/* allot */
void twostore();	/* 2! */
void twofetch();	/* 2@ */
void minusstore();	/* -! */
void zerostore();	/* 0! */
void oneplusstore();	/* 1+! */
void oneminusstore();	/* 1-! */
void minustrailing();	/* -trailing */
void minustext();	/* -text */
void qword();		/* ?word */
void count();		/* count */
void enclose();		/* enclose */

/* logical.c */
void xor();		/* xor */
void and();		/* and */
void not();		/* not */
void or();		/* or */
void toggle();		/* toggle */

/* compare.c */
void zeroless();	/* 0< */
void zeroeq();		/* 0= */
void zerogreat();	/* 0> */
void less();		/* < */
void eq();		/* = */
void great();		/* > */
void dless();		/* d< */
void uless();		/* u< */

/* retstack.c */
void toR();		/* >r */
void fromR();		/* r> */
void Rfetch();		/* r@ */
void rpfetch();		/* rp@ */
void rpstore();		/* rp! */
void Rdrop();		/* rdrop */
void Rpick();		/* rpick */
void Rj();		/* j */
void Rk();		/* k */

/* terminal.c */
int tty_raw();		/* Set a terminal's device into Raw mode */
int tty_reset();	/* Restore terminal's device */
int getchr();		/* Get a char without waiting */
void key();		/* (key) */
void qkey();		/* ?key */
void emit();		/* (emit) */
void cr();		/* (cr) */
void fflushstdout();	/* fflush */

/* vocabulary.c */
void init_voc();
void (*find_voc())();

/* interpret.c */
void address_interpreteter();
void init_vars();
void start_interpreteter();
