#ifndef HEIDEFS_H
#define HEIDEFS_H

typedef int BOOL;
#define FALSE 0
#define TRUE 1

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned int UINT;

typedef long LONG;
#define ULONG_MAX 0xffffffff /* maximum unsigned long value */

#define LOBYTE(w) ((BYTE)(w))
#define HIBYTE(w) ((BYTE)(((UINT)(w) >> 8) & 0xff))

#define LOWORD(l) ((WORD)(DWORD)(l))
#define HIWORD(l) ((WORD)((((DWORD)(l)) >> 16) & 0xffff))

#define MAKEWORD(a, b) ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(low, high) ((LONG)(((WORD)(low)) | (((DWORD)((WORD)(high))) << 16)))

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

#ifndef NULL
#  define NULL ((void *)0)
#endif

/*
 ** This macro will return the difference between a start time (in milliseconds) and an end time (also in milliseconds).
 ** It handles the fact that a DWORD millisecond indicator will wrap every 49.XXX days.
 */
#define TimeDiff(StartTime, EndTime) (((DWORD)EndTime >= (DWORD)StartTime) ? ((DWORD)EndTime - (DWORD)StartTime) : ((DWORD)EndTime + ((DWORD)ULONG_MAX - (DWORD)StartTime) + 1))

#define WordDiff(Start, End) (((WORD)End >= (WORD)Start) ? ((WORD)End - (WORD)Start) : ((WORD)End + ((WORD)0xffff - (WORD)Start) + 1))

#endif
