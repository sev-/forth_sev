/* interpret.c	интерпретатор и структуры управления */

#include "stack.h"
#include <ctype.h>

#define SIZEPTR sizeof(void (*)())

#define PRIMITIVE	0
#define CALL		2
#define EXIT		4
#define CONSTANT	6
#define VARIABLE	8
#define DOES		10	/* (does>) */
#define EXECUTE		12
#define NEXT		14
#define LIT		16
#define DLIT		18
#define BRANCH		20
#define QBRANCH		22	/* ?branch */
#define NQBRANCH	24	/* n?branch */
#define QDO		26	/* (?do) */
#define DO		28	/* (do) */
#define LOOP		30	/* (loop) */
#define PLOOP		32	/* (+loop) */
#define FEXECUTE	34	/* @execute */
#define QUOTE		36	/* (") */
#define FORTH		38	/* (forth) */

NUNSIGNED find_v();

void address_interpreteter()
{
  NUNSIGNED ip;		/* instructions pointer */
  NUNSIGNED jp;		/* jump pointer */
  NUNSIGNED wp;		/* word pointer */
  union
  {
    void (* p)();
    BYTE b[SIZEPTR];
  } PtrToFunc;
  char i, exec = 0;

  printf("Start...\n"); fflush(stdout);
  ip = find_v("rrestart", 0)+2;
  wp = ip+2;

  while(1)
  {
    /* next */
    if(!exec)
      jp = FetchNUnsigned(ip);
    else
    {
      exec = 0;
      ip -= 2;
    }
    if(jp > 48*2)	/* not primitive */
    {
      wp = jp;
      jp = FetchNUnsigned(jp);
    }
    ip += 2;
/*    printf("ip = %x wp = %x jp = %x\n", ip, wp, jp); fflush(stdout); */
    switch(jp)
    {
      case PRIMITIVE:
	for(i = 0; i < SIZEPTR; i++)
	  PtrToFunc.b[i] = vocabulary[wp+2+i];
	PtrToFunc.p();
	break;
      case CALL:
	StoreNUnsigned(retstackhead, ip);
	retstackhead += SINGLESIZE;
	ip = wp+2;
	break;
      case EXIT:
	retstackhead -= SINGLESIZE;
	ip = FetchNUnsigned(retstackhead);
	break;
      case CONSTANT:
	PushNUnsigned(FetchNUnsigned(wp+2));
	break;
      case VARIABLE:
	PushNUnsigned(wp+2);
	break;
      case DOES:		/* (does>) */
	StoreNUnsigned(retstackhead, ip);
	retstackhead += SINGLESIZE;
	ip = FetchNUnsigned(wp);
	PushNUnsigned(wp+2);
	break;
      case EXECUTE:
	jp = PopNUnsigned();
	exec = 1;
	break;
      case FEXECUTE:
	jp = FetchNUnsigned(PopNUnsigned());
	exec = 1;
	break;
      case NEXT:
	break;
      case LIT:
	PushNUnsigned(FetchNUnsigned(ip));
	ip += 2;
	break;
      case DLIT:
	PushDUnsigned(FetchDUnsigned(ip));
	ip += 4;
	break;
      case QBRANCH:	/* ?branch */
	if(PopNUnsigned())
	{
	  ip += 2;
	  break;
	}
      case BRANCH:
	ip = FetchNUnsigned(ip);
	break;
      case NQBRANCH:
	if(!PopNUnsigned())
	{
	  ip += 2;
	  break;
	}
	ip = FetchNUnsigned(ip);
	break;
      case QDO:		/* (?do) */
	if(FetchNUnsigned(stackhead-2) == FetchNUnsigned(stackhead-4))
	{
	  stackhead -= 4;
	  ip = FetchNUnsigned(ip);
	  break;
	}
      case DO:		/* (do) */
	StoreNUnsigned(retstackhead, FetchNUnsigned(ip)); /* for leave */
	ip += 2;
	retstackhead += 2;
	swap();
	StoreNUnsigned(retstackhead, PopNUnsigned()); /* end */
	retstackhead += 2;
	StoreNUnsigned(retstackhead, PopNUnsigned()); /* begin */
	retstackhead += 2;
	StoreNUnsigned(rpcf, retstackhead);
	break;
      case LOOP:	/* (loop) */
	PushNUnsigned(1);
      case PLOOP:	/* (+loop) */
			/* end				current */
	if(FetchSingle(retstackhead-4)-FetchSingle(retstackhead-2)-
	   FetchSingle(stackhead-2) <= 0)	/* step */
	{
	  retstackhead -= 6;
	  ip += 2;
	  StoreNUnsigned(rpcf, retstackhead);
	  break;
	}
	StoreSingle(retstackhead-2, FetchSingle(retstackhead-2)+PopSingle());
	ip = FetchNUnsigned(ip);
	break;
      case QUOTE:	/* (") */
	ip += vocabulary[ip]+1;
	break;
      case FORTH:
	StoreNUnsigned(context, forthcontext);
	break;
      default:
    	printf("Error: Calling to address %4x\n", jp);
    	exit(1);
    }
  }
}

void start_interpreteter(fname)
char *fname;
{
  FILE *in;
  char buf[256];
  char state = 0;
  NUNSIGNED previous, previous1, cfa;
  NUNSIGNED value, addr;
  NUNSIGNED blockptr[32], abortptr[128];
  char numblockptr = 0, numabortptr = 0;
  int i, j;

  somevords();

  addr = vochead;
  previous = lastname;

  if((in = fopen(fname, "r")) == (FILE *)NULL)
  {
    printf("cannot open start file %s\n", fname);
    exit(1);
  }

  while(!feof(in))
  {
    fscanf(in, "%s", buf);
    if(!strcmp(buf, "--"))
    {
      while(fgetc(in) != '\n');
      continue;
    }
    if(!strcmp(buf, "("))
    {
      while(fgetc(in) != ')');
      continue;
    }
    if(state && !strcmp(buf, ";"))
    {
      state = 0;
      StoreNUnsigned(addr, 4);	/* 0004	exit */
      addr += 2;
      lastname = previous;
      continue;
    }
    if(state)
    {
      if(!strcmp(buf, "if")||!strcmp(buf, "while"))
      {
        StoreNUnsigned(addr, QBRANCH);	/* compile ?branch */
        addr += 2;
        PushNUnsigned(addr);		/* here */
        StoreNUnsigned(addr, 0);	/* 0 , */
        addr += 2;
        continue;
      }
      if(!strcmp(buf, "ifnot"))
      {
        StoreNUnsigned(addr, NQBRANCH);	/* compile n?branch */
        addr += 2;
        PushNUnsigned(addr);		/* here */
        StoreNUnsigned(addr, 0);	/* 0 , */
        addr += 2;
        continue;
      }
      if(!strcmp(buf, "else"))
      {
        StoreNUnsigned(addr, BRANCH);	/* compile branch */
        addr += 2;
        PushNUnsigned(addr);		/* here */
        StoreNUnsigned(addr, 0);	/* 0 , */
        addr += 2;
        swap();
        PushNUnsigned(addr);		/* here */
        swap();
        store();
        continue;
      }
      if(!strcmp(buf, "then"))
      {
        PushNUnsigned(addr);		/* here */
        swap();
        store();
        continue;
      }
      if(!strcmp(buf, "do"))
      {
        StoreNUnsigned(addr, DO);	/* compile (do) */
        addr += 2;
        PushNUnsigned(addr);		/* here */
        StoreNUnsigned(addr, 0);	/* 0 , */
        addr += 2;
        PushNUnsigned(addr);		/* here */
        continue;
      }
      if(!strcmp(buf, "?do"))
      {
        StoreNUnsigned(addr, QDO);	/* compile (?do) */
        addr += 2;
        PushNUnsigned(addr);		/* here */
        StoreNUnsigned(addr, 0);	/* 0 , */
        addr += 2;
        PushNUnsigned(addr);		/* here */
        continue;
      }
      if(!strcmp(buf, "loop"))
      {
        StoreNUnsigned(addr, LOOP);	/* compile (loop) */
        addr += 2;
        StoreNUnsigned(addr, PopNUnsigned());	/* , */
        addr += 2;
        PushNUnsigned(addr);		/* here */
        swap();
        store();
        continue;
      }
      if(!strcmp(buf, "+loop"))
      {
        StoreNUnsigned(addr, PLOOP);	/* compile (+loop) */
        addr += 2;
        StoreNUnsigned(addr, PopNUnsigned());	/* , */
        addr += 2;
        PushNUnsigned(addr);		/* here */
        swap();
        store();
        continue;
      }
      if(!strcmp(buf, "begin"))
      {
        PushNUnsigned(addr);		/* here */
        continue;
      }
      if(!strcmp(buf, "again"))
      {
        StoreNUnsigned(addr, BRANCH);	/* compile branch */
        addr += 2;
        StoreNUnsigned(addr, PopNUnsigned());	/* , */
        addr += 2;
        continue;
      }
      if(!strcmp(buf, "until"))
      {
        StoreNUnsigned(addr, QBRANCH);	/* compile ?branch */
        addr += 2;
        StoreNUnsigned(addr, PopNUnsigned());	/* , */
        addr += 2;
        continue;
      }
      if(!strcmp(buf, "repeat"))
      {
        StoreNUnsigned(addr, BRANCH);	/* compile branch */
        addr += 2;
        swap();
        StoreNUnsigned(addr, PopNUnsigned());	/* , */
        addr += 2;
        PushNUnsigned(addr);		/* here */
        swap();
        store();
        continue;
      }        
      if(!strcmp(buf, "[']"))
      {
        fscanf(in, "%s", buf);
        if((cfa = find_v(buf, 0)) == 0)
        {
          printf("cannot find %s\n", buf);
          savvoc(addr);
          exit(1);
        }
        StoreNUnsigned(addr, LIT);
        addr += 2;
        StoreNUnsigned(addr, cfa);
        addr += 2;
        continue;
      }
      if(!strcmp(buf, "abort\""))
      {
        for(i = 0; (buf[i] = fgetc(in)) != '"'; i++);
        abortptr[numabortptr++] = addr;		/* compile (abort") */
        addr += 2;
        vocabulary[addr++] = (BYTE)i;
        for(j = 0; j < i; j++, addr++)
          vocabulary[addr] = buf[j];
        continue;
      }
      if(!strcmp(buf, ".\""))
      {
        for(i = 0; (buf[i] = fgetc(in)) != '"'; i++);
        StoreNUnsigned(addr, find_v("(.\")", 0));
        addr += 2;
        vocabulary[addr++] = (BYTE)i;
        for(j = 0; j < i; j++, addr++)
          vocabulary[addr] = buf[j];
        continue;
      }
      if(!strcmp(buf, "[compile]"))
      {
        fscanf(in, "%s", buf);
        if((cfa = find_v(buf, 1)) == 0)
        {
          printf("cannot find %s\n", buf);
          savvoc(addr);
          exit(1);
        }
        StoreNUnsigned(addr, cfa);
        addr += 2;
        continue;
      }
      if(!strcmp(buf, "does>"))
      {
        StoreNUnsigned(addr, DOES);
        addr += 2;
        StoreNUnsigned(addr, CALL);
        addr += 2;
        continue;
      }
      if((cfa = find_v(buf, 0)) == 0)
        if(isdigit(*buf)||isdigit(buf[1]))
        {
          sscanf(buf, "%x", &value);
          StoreNUnsigned(addr, LIT);
          addr += 2;
          StoreNUnsigned(addr, value);
          addr += 2;
        }
        else
        {
          if(!strcmp(buf, "block"))	/* forwarded */
          {
            blockptr[numblockptr++] = addr;
            addr += 2;
            continue;
          }
          printf("cannot find %s\n", buf);
          savvoc(addr);
          exit(1);
        }
      else
      {
        StoreNUnsigned(addr, cfa);
        addr += 2;
      }
      continue;
    }
    if(!strcmp(buf, ":") || !strcmp(buf, "83:"))
    {
      fscanf(in, "%s", buf);
/*      printf(": %s\n", buf); */
      previous1 = addr;	/* для поля связи */
      compname(buf, &addr, previous);
      if(!strcmp(buf, "block"))		/* forwarded */
        while(numblockptr--)
          StoreNUnsigned(blockptr[numblockptr], addr);
      StoreNUnsigned(addr, CALL);
      addr += 2;
      lastname = previous = previous1;	/* указатель на предыдущее слово */
      state = 1;
      continue;
    }
    if(!strcmp(buf, ":c"))
    {
      fscanf(in, "%*s");
      continue;
    }
    if(!strcmp(buf, "variable"))
    {
      fscanf(in, "%s", buf);
/*      printf("variable %s\n", buf); */
      previous1 = addr;	/* для поля связи */
      compname(buf, &addr, previous);
      StoreNUnsigned(addr, VARIABLE);
      addr += 2;
      StoreNUnsigned(addr, 0);	/* value */
      addr += 2;
      lastname = previous = previous1;	/* указатель на предыдущее слово */
      continue;
    }
    if(isdigit(*buf)||isdigit(buf[1]))
    {
      sscanf(buf, "%x", &value);
      fscanf(in, "%s", buf);
      if(strcmp(buf, "constant"))
      {
        printf("error: unexpected %s\n", buf);
        exit(1);
      }
      fscanf(in, "%s", buf);
/*      printf("constant %s\n", buf); */
      previous1 = addr;	/* для поля связи */
      compname(buf, &addr, previous);
      StoreNUnsigned(addr, CONSTANT);
      addr += 2;
      StoreNUnsigned(addr, value);
      addr += 2;
      lastname = previous = previous1;	/* указатель на предыдущее слово */
      continue;
    }
    if(!strcmp(buf, "immediate"))
    {
      StoreNUnsigned(previous, FetchNUnsigned(previous)|0x80);
      continue;
    }
    if(!strcmp(buf, "stop-compilation"))
      break;
    printf("error: unexpected %s\n", buf);
    exit(1);
  }
  cfa = find_v("(abort\")", 1);
  while(numabortptr--)
    StoreNUnsigned(abortptr[numabortptr], addr);
  vochead = addr;
}

NUNSIGNED find_v(s, flag)
char *s;
int flag;
{
  NUNSIGNED a2;
  BYTE len;

  a2 = lastname;

  len = strlen(s);

  while(1)
  {
    if((flag && ((vocabulary[a2]&0x1f) == len)) ||
		vocabulary[a2] == len)	/* do not use immediate words */
    {
      a2++;
      if(!strncmp(s, &vocabulary[a2], len&0x1f))
        return (a2+len+2);
      a2 += len;
    }
    else
      a2 += (vocabulary[a2]&0x1f)+1;
    a2 = FetchNUnsigned(a2);
    if(a2 == 0)
      return 0;
  }
}

savvoc(c)
NUNSIGNED c;
{
  FILE *o;
  int i;

  o = fopen("voc", "w");
  for(i = 0; i < c; i++)
    fputc(vocabulary[i], o);
  fclose(o);
}

compname(s, a, prev)
char *s;
NUNSIGNED *a;
NUNSIGNED prev;
{
  NUNSIGNED addr = *a;

  vocabulary[addr++] = (BYTE)strlen(s);
  for(; *s; addr++)	/* имя */
    vocabulary[addr] = *s++;
  StoreNUnsigned(addr, prev);
  addr += 2;
  *a = addr;
}

#define NUMSOME		(sizeof(some)/sizeof(struct Some))

struct Some
{
  char *n;
  NUNSIGNED a;
} some[] =
{
  "execute",	EXECUTE,
  "exit",	EXIT,
  "lit",	LIT,
  "dlit",	DLIT,
  "branch",	BRANCH,
  "?branch",	QBRANCH,
  "n?branch",	NQBRANCH,
  "(do)",	DO,
  "(?do)",	QDO,
  "(loop)",	LOOP,
  "(+loop)",	PLOOP,
  "@execute",	FEXECUTE,
  "(\")",	QUOTE
};

somevords()
{
  NUNSIGNED previous, previous1;
  NUNSIGNED addr;
  int i;

  addr = vochead;
  previous = lastname;

  for(i = 0; i < NUMSOME; i++)
  {
    previous1 = addr;	/* для поля связи */
    compname(some[i].n, &addr, previous);
    StoreNUnsigned(addr, some[i].a);
    addr += 2;
    lastname = previous = previous1;	/* указатель на предыдущее слово */
  }
  previous1 = addr;	/* для поля связи */
  compname("tib", &addr, previous);
  StoreNUnsigned(addr, VARIABLE);
  addr += 82;	/* tib */
  lastname = previous1;
  vochead = addr;
}

void init_vars()
{
  StoreNUnsigned(h, vochead);
  StoreNUnsigned(s0, BEGSTACK);
  StoreNUnsigned(r0, BEGRETSTACK);
  StoreNUnsigned(fence, vochead);
  StoreNUnsigned(context, forthcontext);
  StoreNUnsigned(forthcontext, lastname);
  printf("%x %x %x\n", context, FetchNUnsigned(context),FetchNUnsigned(FetchNUnsigned(context)));
}
