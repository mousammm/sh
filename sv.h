/*
  example:
    #include <stdio.h>

    #define STRING_DEF static
    #define STRING_IMPLEMENTATION
    #include "sv.h"
    
    int main() {
      String_View svstr = cstr_to_sv("   Hello, world    ");
      sv_trim(&svstr);
      sv_chop_left(&svstr, 2);
      sv_chop_right(&svstr, 2);

      // TODO:
      // sv_chop_by_delim
      // sv_chop_by_type
    
      char cstr[svstr.count+1];
      sv_to_cstr(svstr, cstr);
    
      printf("|"SV_FMT"|\n", SV_SPREAD(svstr));
      printf("|%s|\n", cstr);

      return 0;
    }
*/

#ifndef STRING_HEADER
#define STRING_HEADER

#include <stddef.h>
#include <ctype.h>
#include <string.h>

#ifndef STRING_DEF
#define STRING_DEF
#endif

#define SV_FMT "%.*s"
#define SV_SPREAD(s) ((int)(s).count), (s).data

typedef struct {
  size_t count;
  const char *data;
} String_View;

STRING_DEF String_View cstr_to_sv(const char *cstr);
// must guarantee that out has sv.count + 1 size (for null terminator).
STRING_DEF void sv_to_cstr(String_View sv, char *out);
STRING_DEF void sv_chop_left(String_View *sv, size_t n);
STRING_DEF void sv_chop_right(String_View *sv, size_t n);
STRING_DEF void sv_trim_left(String_View *sv);
STRING_DEF void sv_trim_right(String_View *sv);
STRING_DEF void sv_trim(String_View *sv);
STRING_DEF String_View sv_chop_by_delim(String_View *sv, char delim);
STRING_DEF String_View sv_chop_by_type(String_View *sv, int (*istype)(int c));

#endif // !STRING_HEADER

#ifdef STRING_IMPLEMENTATION

STRING_DEF String_View cstr_to_sv(const char *cstr)
{
  return (String_View) {
    .count = strlen(cstr),
    .data = cstr,
  };
}

STRING_DEF void sv_to_cstr(String_View sv, char *out)
{
  for (int i = 0; i < sv.count; i++) {
    *out = sv.data[i];
    out++;
  }
  *out = 0;
}

STRING_DEF void sv_chop_left(String_View *sv, size_t n)
{
  if (n > sv->count) n = sv->count;
  sv->count -= n;
  sv->data  += n;
}

STRING_DEF void sv_chop_right(String_View *sv, size_t n)
{
  if (n > sv->count) n = sv->count;
  sv->count -= n;
}

STRING_DEF void sv_trim_left(String_View *sv)
{
  while (sv->count > 0 && isspace(sv->data[0])) {
    sv_chop_left(sv, 1);
  }
}

STRING_DEF void sv_trim_right(String_View *sv)
{
  while (sv->count > 0 && isspace(sv->data[sv->count-1])) {
    sv_chop_right(sv, 1);
  }
}

STRING_DEF void sv_trim(String_View *sv)
{
  sv_trim_left(sv);
  sv_trim_right(sv);
}

STRING_DEF String_View sv_chop_by_delim(String_View *sv, char delim)
{
  size_t i = 0;
  while (i < sv->count && sv->data[i] != delim) {
    i++;
  }

  if (i < sv->count) {
    String_View result = {
      .data = sv->data,
      .count = i,
    };
    sv_chop_left(sv, i++);
    return result;
  }

  String_View result = *sv;
  sv_chop_left(sv, sv->count);
  return result;
}

STRING_DEF String_View sv_chop_by_type(String_View *sv, int (*istype)(int c))
{
  size_t i = 0;
  while (i < sv->count && !istype(sv->data[i])) {
    i++;
  }

  if (i < sv->count) {
    String_View result = {
      .data = sv->data,
      .count = i,
    };
    sv_chop_left(sv, i++);
    return result;
  }

  String_View result = *sv;
  sv_chop_left(sv, sv->count);
  return result;
}

#endif // STRING_IMPLEMENTATION
