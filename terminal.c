/* terminal.c - ввод/вывод терминала */

#include "stack.h"
#include <termio.h>

static struct termio tty_mode;	/* save tty mode here */

static int previous_key;	/* save key */

/*
 * Put a terminal device into RAW mode with ECHO off.
 * Before doing so we first save the terminal's current mode,
 * assuming the caller will call the tty_reset() function
 * when it's done with raw mode.
 */

int tty_raw()
{
  struct termio temp_mode;

  if(ioctl(0, TCGETA, (char *)&temp_mode) < 0)
    return(-1);
  tty_mode = temp_mode;		/* save for restoring later */

  temp_mode.c_iflag = 0;	/* turn off all input control */
  temp_mode.c_oflag &= ~OPOST;	/* disable output post-processing */
  temp_mode.c_lflag &= ~(ISIG | ICANON | ECHO | XCASE);
  				/* disable signal generation */
  				/* disable canonical input */
  				/* disable echo */
  				/* disable upper/lower output */
  temp_mode.c_cflag &= ~(CSIZE | PARENB);
  				/* clear char size, disable parity */
  temp_mode.c_cflag |= CS8;	/* 8-bit chars */

  temp_mode.c_cc[VMIN] = 0;	/* min #chars to satisfy read */
  temp_mode.c_cc[VTIME] = 0;	/* 10'ths of seconds between chars */

  if(ioctl(0, TCSETA, (char *)&temp_mode) < 0)
    return(-1);

  previous_key = -1;

  return 0;
}

/*
 * Restore a terminal's mode to whatewer it was on the most
 * recent call to the tty_raw() function above.
 */

int tty_reset()
{
  if(ioctl(0, TCSETA, (char *)&tty_mode) < 0)
    return(-1);

  return 0;
}

int getchr()		/* Get a char without waiting */
{
  unsigned char xchr[1];

  if(read(0, xchr, 1) != 1)
    return(-1);

  return xchr[0];
}

void key()	/* (key)	->c */
{
  int chr;

  if(previous_key != -1)
  {
    PushSingle(previous_key);
    previous_key = -1;
    return;
  }

  while((chr = getchr()) == -1);

  PushSingle(chr);
}

void qkey()	/* ?key		->f */
{
  int chr;

  if(previous_key != -1)
  {
    PushSingle(-1);	/* true */
    return;
  }

  if((chr = getchr()) != -1)
  {
    previous_key = chr;	/* save char for KEY operation */
    PushSingle(-1);	/* true */
    return;
  }

  PushSingle(0);		/* false */
}

void emit()		/* (emit)	c-> */
{
  SINGLE a;

  a = PopSingle();

  fputc(a, stdout);
}

void cr()		/* (cr)		-> */
{
  fputc('\n', stdout);
}

void fflushstdout()	/* fflush	-> */
{
  fflush(stdout);
}
