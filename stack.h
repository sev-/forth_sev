/* stack.h - типы данных стэка */

#include <stdio.h>

typedef char BYTE;
typedef short SINGLE;
typedef unsigned short NUNSIGNED;
typedef int DOUBLE;
typedef unsigned int DUNSIGNED;
typedef float FLOAT;

#define BYTESIZE	1
#define SINGLESIZE	2
#define DOUBLESIZE	4
#define FLOATSIZE	4

#define BEGSTACK	0xf000
#define BEGRETSTACK	0xa800

#include "global.h"	/* глобальные переменные */
#include "extern.h"	/* внешние функции */
