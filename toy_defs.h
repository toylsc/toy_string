#pragma once

#if __linux__

#ifndef likely
#define likely(x) __builtin_expect(x, 1)
#endif

#ifndef unlikely
#define unlikely(x) __builtin_expect(x, 0)
#endif

#else // else of linux
	
#ifndef likely
#define likely(x) x
#endif

#ifndef unlikely
#define unlikely(x) x
#endif

#endif // end of linux

#ifndef CHAR_SPACE
#define CHAR_SPACE ' '
#endif

#ifndef CHAR_HTAB
#define CHAR_HTAB  '\t'
#endif

#ifndef CHAR_VTAB
#define CHAR_VTAB  '\v'
#endif

#ifndef CHAR_COLON
#define CHAR_COLON ':'
#endif

#ifndef IsBlank
#define IsBlank(p) (*p==CHAR_SPACE || *p==CHAR_HTAB || *p==CHAR_VTAB || *p=='\f' || *p=='\r' || *p=='\n' )
#endif
