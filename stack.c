#include "stack.h"
#include <ctype.h>
#include <stdio.h>

SINGLE ConvSingle();
DOUBLE ConvDouble();

main()
{
  stackhead = BEGSTACK;
  retstackhead = BEGRETSTACK;

  init_voc();
  start_interpreteter("stack.con");
  init_vars();
  play();
/*  address_interpreteter(); */
}

SINGLE ConvSingle(s)
char *s;
{
  SINGLE num = 0;

  while(*s && isdigit(*s))
  {
    num = num * 10 + (*s - '0');
    s++;
  }

  return num;
}

DOUBLE ConvDouble(s)
char *s;
{
  DOUBLE num = 0;

  while(*s && isdigit(*s))
  {
    num = num * 10 + (*s - '0');
    s++;
    if(*s == '.')
      s++;
  }

  return num;
}

void dot()
{
  printf("%5d ", PopSingle());
}

void ddot()
{
  printf("%10d ", PopDouble());
}

void null()
{
  printf("Error\t");
}

void quit()
{
  exit(0);
}

play()
{
  char tmp[80];
  int i, j;
  int fdoub;

  while(1)
  {
    printf("> ");
    fflush(stdout);
    memset(tmp, '\0', 80);
    gets(tmp);
    i = 0;
    while(tmp[i])
    {
      while(tmp[i] && isspace(tmp[i]))
        i++;
      if(isdigit(tmp[i]))
      {
        fdoub = 0;
        j = i;
        i++;
        while(tmp[i] && (isdigit(tmp[i]) || tmp[i] == '.'))
        {
          if(tmp[i] == '.')
            fdoub = 1;
          i++;
        }
        i--;
        if(fdoub)
          PushDouble(ConvDouble(&tmp[j]));
        else
          PushSingle(ConvSingle(&tmp[j]));
      }
      else
        find_voc(&tmp[i], &i)();
      i++;
    }
    printf("Ok\n");
  }
}
