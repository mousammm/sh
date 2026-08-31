#include <stdio.h>
#include "./sh_string.c"

// char in c and char stdard lib
// null terminated string in c, and string.h

int main()
{
  String_View s = sv("    Hello, world     ");
  sv_trim(&s);
  printf(SV_Fmt, SV_Arg(s));
  return 0;
}
