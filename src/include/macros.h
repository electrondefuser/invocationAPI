#include <assert.h>
#define g_assert(x) for ( ; !(x) ; assert(x) )