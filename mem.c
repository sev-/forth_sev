/* mem.c - операции с памятью */

#include "stack.h"

void store()		/* !	u, a ->   v[a] = u */
{
  NUNSIGNED a, b;

  a = PopNUnsigned();
  b = PopNUnsigned();
  
  StoreNUnsigned(a, b);
}

void plusstore()	/* +!	u, a ->   v[a] += u */
{
  NUNSIGNED a, b;

  a = PopNUnsigned();
  b = FetchNUnsigned(a);
  
  b += PopNUnsigned();

  StoreNUnsigned(a, b);
}

void fetch()		/* @ 	a -> n1 */
{
  PushNUnsigned(FetchNUnsigned(PopNUnsigned()));
}

void cstore()		/* c!	c, a ->   v[a] = c */
{
  NUNSIGNED a, b;
  BYTE c;
  
  a = PopNUnsigned();
  b = PopNUnsigned();

  c = (BYTE)(b&0x00ff);

  vocabulary[a] = c;
}

void cfetch()		/* c@ 	a -> c */
{
  PushSingle( (SINGLE)vocabulary[PopNUnsigned()] );
}

void cmove()		/* cmove 	a1, a2, u -> */
{
  NUNSIGNED a1, a2;
  NUNSIGNED u, i;

  u = PopNUnsigned();
  a2 = PopNUnsigned();
  a1 = PopNUnsigned();

  for(i = 0; i < u; i++)
    vocabulary[a2+i] = vocabulary[a1+i];
}

void cmoverev()		/* cmove> 	a1, a2, u -> */
{
  NUNSIGNED a1, a2;
  NUNSIGNED u;

  u = PopNUnsigned();
  a2 = PopNUnsigned();
  a1 = PopNUnsigned();

  for(; u; u--)
    vocabulary[a2+u-1] = vocabulary[a1+u-1];
}

void cmovesel()		/* <cmove>	a1, a2, u -> */
			/* if a1 > a2 then cmove> else <cmove */
{
  NUNSIGNED a1, a2;
  NUNSIGNED u, i;

  u = PopNUnsigned();
  a2 = PopNUnsigned();
  a1 = PopNUnsigned();

  if(a1 < a2)
    for(i = 0; i < u; i++)
      vocabulary[a2+i] = vocabulary[a1+i];
  else
    for(; u; u--)
      vocabulary[a2+u-1] = vocabulary[a1+u-1];
}  

void fill()		/* fill 	a, u, c -> */
{
  NUNSIGNED a;
  NUNSIGNED u;
  BYTE c;

  c = (BYTE)PopSingle();
  u = PopNUnsigned();
  a = PopNUnsigned();

  for(; u; u--)
    vocabulary[a+u-1] = c;
}

void zerotobl()		/* 0>bl		a, u ->	*/
			/* replace zeor to blank from [a] to [a+u] */
{
  NUNSIGNED a;
  NUNSIGNED u;

  u = PopNUnsigned();
  a = PopNUnsigned();

  for(; u; u--)
    if(vocabulary[a+u-1] == 0)
      vocabulary[a+u-1] = ' ';
}  

void comma()		/* ,		u ->	*/
{
  NUNSIGNED a;

  a = PopNUnsigned();

  StoreNUnsigned(vochead, a);
  vochead += 2;
  StoreNUnsigned(h, vochead);
}
  
void ccomma()		/* c,		c ->	*/
{
  NUNSIGNED a;

  a = PopNUnsigned();
  vocabulary[vochead++] = a&0x00ff;
  StoreNUnsigned(h, vochead);
}

void here()		/* here		-> a	*/
{
  PushNUnsigned(vochead);
}

void allot()		/* allot	u -> */
{
  vochead += PopNUnsigned();
  StoreNUnsigned(h, vochead);
}

void twostore()		/* 2!	d, a ->   v[a] = d */
{
  NUNSIGNED a;

  a = PopNUnsigned();

  StoreDUnsigned(a, PopDUnsigned());
}

void twofetch()		/* 2@ 	a -> d */
{
  PushDUnsigned(FetchDUnsigned(PopNUnsigned()));
}

void minusstore()	/* -!	u, a ->   v[a] += u */
{
  NUNSIGNED a, b;

  a = PopNUnsigned();
  b = FetchNUnsigned(a);
  
  b -= PopNUnsigned();

  StoreNUnsigned(a, b);
}

void zerostore()	/* 0!	a ->   v[a] = 0 */
{
  NUNSIGNED a;

  a = PopNUnsigned();
  
  vocabulary[a] = vocabulary[a+1] = 0;
}

void oneplusstore()	/* 1+!	a ->   v[a]++ */
{
  NUNSIGNED a;

  a = PopNUnsigned();

  StoreNUnsigned(a, FetchNUnsigned(a)+1);
}

void oneminusstore()	/* 1-!	a ->   v[a]-- */
{
  NUNSIGNED a;

  a = PopNUnsigned();

  StoreNUnsigned(a, FetchNUnsigned(a)-1);
}

void minustrailing()	/* -trailing		a, n -> a, n */
{
  NUNSIGNED a, n;

  n = PopNUnsigned();
  a = PopNUnsigned();

  while(n && vocabulary[a] == ' ')
    n--;
  PushNUnsigned(a);
  PushNUnsigned(n);
}

void minustext()	/* -text	a1, n, a2 -> f=a1-a2 */
{
  NUNSIGNED a1, a2, n, i;

  a2 = PopNUnsigned();
  n = PopNUnsigned();
  a1 = PopNUnsigned();

  for(i = a2; i < a2+n; i++)
    if(vocabulary[a1++] - vocabulary[i])
    {
      PushSingle(((int)vocabulary[a1++]-(int)vocabulary[i])<0?-1:1);
      break;
    }
  if(i == a2+n)
    PushSingle(0);
}

void qword()		/* ?word	word, voc -> word, f */
{
  NUNSIGNED a1, a2, link;
  BYTE len;

  savvoc(vochead);
  a1 = PopNUnsigned();	/* vocabulary */
  a2 = PopNUnsigned();	/* counted string */
  printf("?word: %x %x\n", a2,a1);

  len = vocabulary[a2++];
  printf("len = %x\n", len);

  while(1)
  {
    link = a1;
    a1 = FetchNUnsigned(a1);
    printf("%x ", a1);
    if(a1 == 0)
    {
      PushNUnsigned(a2-1);
      PushSingle(0);
      StoreNUnsigned(wminuslink, link);
      return;
    }
    if((vocabulary[a1]&0x2f) == len)	/* учитывать smudge = 20h */
    {
      if(!len || !strncmp(&vocabulary[a1+1], &vocabulary[a2], len))
      {
        PushNUnsigned(a1);
        PushSingle(-1);
        StoreNUnsigned(wminuslink, link);
        printf("^^^^^^^^^^ Found %x\n", a2);
        return;
      }
    }
    if(!(vocabulary[a1]&0x1f))
      printf("Yes ");
    a1 += (vocabulary[a1]&0x1f)+1;
  }
}

void count()	/* count	t -> a, n */
{
  NUNSIGNED t;

  t = PopNUnsigned();
  PushNUnsigned(t+1);
  PushNUnsigned((NUNSIGNED)vocabulary[t]);
}

void enclose()	/* enclose   c, begbuf, lenbuf -> (begword, len, endword, -1)|(0) */
{
  NUNSIGNED lenbuf, c;
  NUNSIGNED begword, len, endword;

  lenbuf = PopNUnsigned();
  begword = PopNUnsigned();
  c = PopNUnsigned();
  
  do
  {
    if(vocabulary[begword++] != (BYTE)c)
      break;
  } while(lenbuf--);

  if(!lenbuf+1)
  {
    PushNUnsigned(0);
    return;
  }
  PushNUnsigned(begword-1);
  endword = begword;
  
  do
  {
    if(vocabulary[endword++] == (BYTE)c)
      break;
  } while(lenbuf--);

  endword--;
  PushNUnsigned(endword-begword);
  PushNUnsigned(endword);
  PushSingle(-1);

/*
code enclose   --  c adr1 len1 --- adr2 len2 adr3 true / false
	pop	b	; len
	pop	d	; begin buffer
	xthl		; c
	xchg		; e - cиmboл-oгpahичиteль hl = adr1
	dcx	b
1#:	mov	a, b
	ora	a
	jm	4#	; if len < 0
	mov	a, m
	cmp	e
	dcx	b
	inx	h
	jz	1#	; пропустить начальныу ограничители
	push	h	; in stack - begin of word
2#:	mov	a, b
	ora	a
	jm	3#	; if len < 0
	mov	a, m
	cmp	e
	dcx	b
	inx	h
	jnz	2#
	dcx	h	; in hl - end of word
3#:	pop	d	; true
	dcx	d	; begin of word
	push	d	; begin
	push	h	; end
	mov	a, l	
	sub	e
	mov	l, a
	mov	a, h
	sbb	d
	mov	h, a	; in hl - word length
	xthl		; in hl - end, in stack - length
	inx	h	; end ++;
	push	h
	lxi	h, -1	; begin length end true
	push	h
	jmp	next
4#:	lxi	h, 0
	push	h	; false
	jmp	next
end-code
*/
}
