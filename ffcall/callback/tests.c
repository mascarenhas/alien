/* Some random tests for vacall. */

/*
 * Copyright 1993 Bill Triggs, <Bill.Triggs@inrialpes.fr>
 * Copyright 1995-1999, 2002 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callback.h"
FILE* out;

/* NB since K&R C always passes chars and shorts as ints and floats as doubles,
 * unprototyped ANSI-C functions must do the same, eg:
 * - foo(x) float x; { ... } passes x as a double & converts it to a float internally.
 * - foo(float x) { ... } passes x as a float.
 */
#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
#define _ ,
#define _P(ARGS,TYPES) (TYPES)
#define FTYPE(RETTYPE,ARGTYPES) (RETTYPE (*) ARGTYPES)
#else
#define _ ;
#define _P(ARGS,TYPES) ARGS TYPES;
#define FTYPE(RETTYPE,ARGTYPES) (RETTYPE (*) ())
#endif

#if defined(__hppa__) && defined(__GNUC__)
#if (__GNUC__ == 2 && __GNUC_MINOR__ < 6)
/* gcc-2.5.2 bugs prevent the T test from working. */
#define SKIP_T
#endif
#endif
#if defined(__m68k__) && defined(sun) && !defined(__GNUC__)
/* A SunOS 4.0.3 cc bug is triggered by the va_arg_struct macro. */
#define SKIP_STRUCTS
#endif
#if defined(__m68k__) && defined(__GNUC__)
/* "gcc-2.6.3 -freg-struct-return" returns  T = struct { char c[3]; }  (which
 * has size 4 !) in memory, in contrast to  struct { char a,b,c; }  and
 * struct { char c[4]; }  and  struct { char a,b,c,d; }  which have the same
 * size and the same alignment but are returned in registers. I don't know why.
 */
#define SKIP_T
#endif
#if defined(__i386__) && defined(__GNUC__)
#if (__GNUC__ == 2) && (__GNUC_MINOR__ == 7)
/* Problem with gcc-2.7.x on Linux/ELF: The X test fails.
 * The calling convention for C functions returning structures of size > 8 bytes
 * apparently has changed between gcc-2.6.3 and gcc-2.7 (all i386 platforms),
 * and vacall supports only the old one. Since gcc-2.8 will switch back to
 * gcc-2.6.3's calling convention, I won't change ffcall/vacall for this.
 * Just hide the problem by not running the test. The impact isn't big for
 * CLISP: Callbacks returning structures > 8 bytes won't work.
 */
#define SKIP_X
#endif
#endif
#if defined(__sparc__) && defined(sun) && defined(__SUNPRO_C) /* SUNWspro cc */
/* SunPRO cc miscompiles the simulator function for X_BcdB: d.i[1] is
 * temporarily stored in %l2 and put onto the stack from %l2, but in between
 * the copy of X has used %l2 as a counter without saving and restoring its
 * value.
 */
#define SKIP_X
#endif
#if defined(__mipsn32__) && !defined(__GNUC__)
/* The X test crashes for an unknown reason. */
#define SKIP_X
#endif

#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int
#define ulong unsigned long

typedef struct { char x; } Char;
typedef struct { short x; } Short;
typedef struct { int x; } Int;
typedef struct { long x; } Long;
typedef struct { float x; } Float;
typedef struct { double x; } Double;
typedef struct { char c; float f; } A;
typedef struct { double d; int i[3]; } B;
typedef struct { long l1; long l2; } J;
typedef struct { char c[3]; } T;
typedef struct { char c[33],c1; } X;

char c1='a', c2=127, c3=(char)128, c4=(char)255, c5=-1;
short s1=32767, s2=(short)32768, s3=3, s4=4, s5=5, s6=6, s7=7, s8=8, s9=9;
int i1=1, i2=2, i3=3, i4=4, i5=5, i6=6, i7=7, i8=8, i9=9,
    i10=11, i11=12, i12=13, i13=14, i14=15, i15=16, i16=17;
long l1=1, l2=2, l3=3, l4=4, l5=5, l6=6, l7=7, l8=8, l9=9;
#ifdef HAVE_LONGLONG
long long ll1 = 3875056143130689530LL;
#endif
float f1=0.1, f2=0.2, f3=0.3, f4=0.4, f5=0.5, f6=0.6, f7=0.7, f8=0.8, f9=0.9,
      f10=1.1, f11=1.2, f12=1.3, f13=1.4, f14=1.5, f15=1.6, f16=1.7;
double d1=0.1, d2=0.2, d3=0.3, d4=0.4, d5=0.5, d6=0.6, d7=0.7, d8=0.8, d9=0.9,
       d10=1.1, d11=1.2, d12=1.3, d13=1.4, d14=1.5, d15=1.6, d16=1.7;

uchar uc1='a', uc2=127, uc3=128, uc4=255, uc5=-1;
ushort us1=1, us2=2, us3=3, us4=4, us5=5, us6=6, us7=7, us8=8, us9=9;
uint ui1=1, ui2=2, ui3=3, ui4=4, ui5=5, ui6=6, ui7=7, ui8=8, ui9=9;
ulong ul1=1, ul2=2, ul3=3, ul4=4, ul5=5, ul6=6, ul7=7, ul8=8, ul9=9;

char *str1="hello",str2[]="goodbye",*str3="still here?";
Char C1={'A'}, C2={'B'}, C3={'C'}, C4={'\377'}, C5={-1};
Short S1={1}, S2={2}, S3={3}, S4={4}, S5={5}, S6={6}, S7={7}, S8={8}, S9={9};
Int I1={1}, I2={2}, I3={3}, I4={4}, I5={5}, I6={6}, I7={7}, I8={8}, I9={9};
Float F1={0.1}, F2={0.2}, F3={0.3}, F4={0.4}, F5={0.5}, F6={0.6}, F7={0.7}, F8={0.8}, F9={0.9};
Double D1={0.1}, D2={0.2}, D3={0.3}, D4={0.4}, D5={0.5}, D6={0.6}, D7={0.7}, D8={0.8}, D9={0.9};

A A1={'a',0.1},A2={'b',0.2},A3={'\377',0.3};
B B1={0.1,{1,2,3}},B2={0.2,{5,4,3}};
J J1={47,11},J2={73,55};
T T1={'t','h','e'},T2={'f','o','x'};
X X1={"abcdefghijklmnopqrstuvwxyzABCDEF",'G'}, X2={"123",'9'}, X3={"return-return-return",'R'};

/* void tests */
void v_v()
{
  fprintf(out,"void f(void):\n");
  fflush(out);
}

/* int tests */
int i_v()
{
  int r=99;
  fprintf(out,"int f(void):");
  fflush(out);
  return r;
}
int i_i _P((a), int a)
{
  int r=a+1;
  fprintf(out,"int f(int):(%d)",a);
  fflush(out);
  return r;
}
int i_i2 _P((a,b), int a _ int b)
{
  int r=a+b;
  fprintf(out,"int f(2*int):(%d,%d)",a,b);
  fflush(out);
  return r;
}
int i_i4 _P((a,b,c,d), int a _ int b _ int c _ int d)
{
  int r=a+b+c+d;
  fprintf(out,"int f(4*int):(%d,%d,%d,%d)",a,b,c,d);
  fflush(out);
  return r;
}
int i_i8 _P((a,b,c,d,e,f,g,h),
            int a _ int b _ int c _ int d _ int e _ int f _ int g _ int h)
{
  int r=a+b+c+d+e+f+g+h;
  fprintf(out,"int f(8*int):(%d,%d,%d,%d,%d,%d,%d,%d)",a,b,c,d,e,f,g,h);
  fflush(out);
  return r;
}
int i_i16 _P((a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p),
             int a _ int b _ int c _ int d _ int e _ int f _ int g _ int h
             _ int i _ int j _ int k _ int l _ int m _ int n _ int o _ int p)
{
  int r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
  fprintf(out,"int f(16*int):(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)",
          a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
  fflush(out);
  return r;
}

/* float tests */
float f_f _P((a), float a)
{
  float r=a+1.0;
  fprintf(out,"float f(float):(%g)",a);
  fflush(out);
  return r;
}
float f_f2 _P((a,b), float a _ float b)
{
  float r=a+b;
  fprintf(out,"float f(2*float):(%g,%g)",a,b);
  fflush(out);
  return r;
}
float f_f4 _P((a,b,c,d), float a _ float b _ float c _ float d)
{
  float r=a+b+c+d;
  fprintf(out,"float f(4*float):(%g,%g,%g,%g)",a,b,c,d);
  fflush(out);
  return r;
}
float f_f8 _P((a,b,c,d,e,f,g,h), float a _ float b _ float c _ float d _ float e _ float f
              _ float g _ float h)
{
  float r=a+b+c+d+e+f+g+h;
  fprintf(out,"float f(8*float):(%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h);
  fflush(out);
  return r;
}
float f_f16 _P((a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p),
               float a _ float b _ float c _ float d _ float e _ float f _ float g _ float h
               _ float i _ float j _ float k _ float l _ float m _ float n _ float o _ float p)
{
  float r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
  fprintf(out,"float f(16*float):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
  fflush(out);
  return r;
}

/* double tests */
double d_d _P((a), double a)
{
  double r=a+1.0;
  fprintf(out,"double f(double):(%g)",a);
  fflush(out);
  return r;
}
double d_d2 _P((a,b), double a _ double b)
{
  double r=a+b;
  fprintf(out,"double f(2*double):(%g,%g)",a,b);
  fflush(out);
  return r;
}
double d_d4 _P((a,b,c,d), double a _ double b _ double c _ double d)
{
  double r=a+b+c+d;
  fprintf(out,"double f(4*double):(%g,%g,%g,%g)",a,b,c,d);
  fflush(out);
  return r;
}
double d_d8 _P((a,b,c,d,e,f,g,h),
               double a _ double b _ double c _ double d _ double e _ double f
               _ double g _ double h)
{
  double r=a+b+c+d+e+f+g+h;
  fprintf(out,"double f(8*double):(%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h);
  fflush(out);
  return r;
}
double d_d16 _P((a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p),
                double a _ double b _ double c _ double d _ double e _ double f
                _ double g _ double h _ double i _ double j _ double k _ double l
                _ double m _ double n _ double o _ double p)
{
  double r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
  fprintf(out,"double f(16*double):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
  fflush(out);
  return r;
}

/* pointer tests */
void* vp_vpdpcpsp _P((a,b,c,d), void* a _ double* b _ char* c _ Int* d)
{
  void* ret = (char*)b + 1;
  fprintf(out,"void* f(void*,double*,char*,Int*):(0x%lx,0x%lx,0x%lx,0x%lx)",(long)a,(long)b,(long)c,(long)d);
  fflush(out);
  return ret;
}

/* mixed number tests */
uchar uc_ucsil _P((a,b,c,d), uchar a _ ushort b _ uint c _ ulong d)
{
  uchar r = -1;
  fprintf(out,"uchar f(uchar,ushort,uint,ulong):(%u,%u,%u,%lu)",a,b,c,d);
  fflush(out);
  return r;
}
double d_iidd _P((a,b,c,d), int a _ int b _ double c _ double d)
{
  double r = a+b+c+d;
  fprintf(out,"double f(int,int,double,double):(%d,%d,%g,%g)",a,b,c,d);
  fflush(out);
  return r;
}
double d_idid _P((a,b,c,d), int a _ double b _ int c _ double d)
{
  double r = a+b+c+d;
  fprintf(out,"double f(int,double,int,double):(%d,%g,%d,%g)",a,b,c,d);
  fflush(out);
  return r;
}
ushort us_cdcd _P((a,b,c,d), char a _ double b _ char c _ double d)
{
  ushort r = (ushort)(a + b + c + d);
  fprintf(out,"ushort f(char,double,char,double):('%c',%g,'%c',%g)",a,b,c,d);
  fflush(out);
  return r;
}

#ifdef HAVE_LONGLONG
long long ll_flli _P((a,b,c), float a _ long long b _ int c)
{
  long long r = (long long)(int)a + b + (long long)c;
  fprintf(out,"long long f(float,long long,int):(%g,0x%lx%08lx,0x%lx)",a,(long)(b>>32),(long)(b&0xffffffff),(long)c);
  fflush(out);
  return r;
}
#endif

/* structure tests */
Int I_III _P((a,b,c), Int a _ Int b _ Int c)
{
  Int r;
  r.x = a.x + b.x + c.x;
  fprintf(out,"Int f(Int,Int,Int):({%d},{%d},{%d})",a.x,b.x,c.x);
  fflush(out);
  return r;
}
Char C_CdC _P((a,b,c), Char a _ double b _ Char c)
{
  Char r;
  r.x = (a.x + c.x)/2;
  fprintf(out,"Char f(Char,double,Char):({'%c'},%g,{'%c'})",a.x,b,c.x);
  fflush(out);
  return r;
}
Float F_Ffd _P((a,b,c), Float a _ float b _ double c)
{
  Float r;
  r.x = a.x + b + c;
  fprintf(out,"Float f(Float,float,double):({%g},%g,%g)",a.x,b,c);
  fflush(out);
  return r;
}
Double D_fDd _P((a,b,c), float a _ Double b _ double c)
{
  Double r;
  r.x = a + b.x + c;
  fprintf(out,"Double f(float,Double,double):(%g,{%g},%g)",a,b.x,c);
  fflush(out);
  return r;
}
J J_JiJ _P((a,b,c), J a _ int b _ J c)
{
  J r;
  r.l1 = a.l1+c.l1; r.l2 = a.l2+b+c.l2;
  fprintf(out,"J f(J,int,J):({%ld,%ld},%d,{%ld,%ld})",a.l1,a.l2,b,c.l1,c.l2);
  fflush(out);
  return r;
}
T T_TcT _P((a,b,c), T a _ char b _ T c)
{
  T r;
  r.c[0]='b'; r.c[1]=c.c[1]; r.c[2]=c.c[2];
  fprintf(out,"T f(T,char,T):({\"%c%c%c\"},'%c',{\"%c%c%c\"})",a.c[0],a.c[1],a.c[2],b,c.c[0],c.c[1],c.c[2]);
  fflush(out);
  return r;
}
X X_BcdB _P((a,b,c,d), B a _ char b _ double c _ B d)
{
  static X xr={"return val",'R'};
  X r;
  r = xr;
  r.c1 = b;
  fprintf(out,"X f(B,char,double,B):({%g,{%d,%d,%d}},'%c',%g,{%g,{%d,%d,%d}})",
          a.d,a.i[0],a.i[1],a.i[2],b,c,d.d,d.i[0],d.i[1],d.i[2]);
  fflush(out);
  return r;
}


/* These functions simulate the behaviour of the functions above. */

/* void tests */
void v_v_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&v_v) { fprintf(out,"wrong data for v_v\n"); exit(1); }
  va_start_void(alist);
  fprintf(out,"void f(void):\n");
  fflush(out);
  va_return_void(alist);
}

/* int tests */
void i_v_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&i_v) { fprintf(out,"wrong data for i_v\n"); exit(1); }
  va_start_int(alist);
 {int r=99;
  fprintf(out,"int f(void):");
  fflush(out);
  va_return_int(alist, r);
}}
void i_i_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&i_i) { fprintf(out,"wrong data for i_i\n"); exit(1); }
  va_start_int(alist);
 {int a = va_arg_int(alist);
  int r=a+1;
  fprintf(out,"int f(int):(%d)",a);
  fflush(out);
  va_return_int(alist, r);
}}
void i_i2_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&i_i2) { fprintf(out,"wrong data for i_i2\n"); exit(1); }
  va_start_int(alist);
 {int a = va_arg_int(alist);
  int b = va_arg_int(alist);
  int r=a+b;
  fprintf(out,"int f(2*int):(%d,%d)",a,b);
  fflush(out);
  va_return_int(alist, r);
}}
void i_i4_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&i_i4) { fprintf(out,"wrong data for i_i4\n"); exit(1); }
  va_start_int(alist);
 {int a = va_arg_int(alist);
  int b = va_arg_int(alist);
  int c = va_arg_int(alist);
  int d = va_arg_int(alist);
  int r=a+b+c+d;
  fprintf(out,"int f(4*int):(%d,%d,%d,%d)",a,b,c,d);
  fflush(out);
  va_return_int(alist, r);
}}
void i_i8_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&i_i8) { fprintf(out,"wrong data for i_i8\n"); exit(1); }
  va_start_int(alist);
 {int a = va_arg_int(alist);
  int b = va_arg_int(alist);
  int c = va_arg_int(alist);
  int d = va_arg_int(alist);
  int e = va_arg_int(alist);
  int f = va_arg_int(alist);
  int g = va_arg_int(alist);
  int h = va_arg_int(alist);
  int r=a+b+c+d+e+f+g+h;
  fprintf(out,"int f(8*int):(%d,%d,%d,%d,%d,%d,%d,%d)",a,b,c,d,e,f,g,h);
  fflush(out);
  va_return_int(alist, r);
}}
void i_i16_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&i_i16) { fprintf(out,"wrong data for i_i16\n"); exit(1); }
  va_start_int(alist);
 {int a = va_arg_int(alist);
  int b = va_arg_int(alist);
  int c = va_arg_int(alist);
  int d = va_arg_int(alist);
  int e = va_arg_int(alist);
  int f = va_arg_int(alist);
  int g = va_arg_int(alist);
  int h = va_arg_int(alist);
  int i = va_arg_int(alist);
  int j = va_arg_int(alist);
  int k = va_arg_int(alist);
  int l = va_arg_int(alist);
  int m = va_arg_int(alist);
  int n = va_arg_int(alist);
  int o = va_arg_int(alist);
  int p = va_arg_int(alist);
  int r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
  fprintf(out,"int f(16*int):(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)",
          a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
  fflush(out);
  va_return_int(alist, r);
}}

/* float tests */
void f_f_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&f_f) { fprintf(out,"wrong data for f_f\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float r=a+1.0;
  fprintf(out,"float f(float):(%g)",a);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f2_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&f_f2) { fprintf(out,"wrong data for f_f2\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float r=a+b;
  fprintf(out,"float f(2*float):(%g,%g)",a,b);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f4_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&f_f4) { fprintf(out,"wrong data for f_f4\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  float r=a+b+c+d;
  fprintf(out,"float f(4*float):(%g,%g,%g,%g)",a,b,c,d);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f8_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&f_f8) { fprintf(out,"wrong data for f_f8\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  float e = va_arg_float(alist);
  float f = va_arg_float(alist);
  float g = va_arg_float(alist);
  float h = va_arg_float(alist);
  float r=a+b+c+d+e+f+g+h;
  fprintf(out,"float f(8*float):(%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f16_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&f_f16) { fprintf(out,"wrong data for f_f16\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  float e = va_arg_float(alist);
  float f = va_arg_float(alist);
  float g = va_arg_float(alist);
  float h = va_arg_float(alist);
  float i = va_arg_float(alist);
  float j = va_arg_float(alist);
  float k = va_arg_float(alist);
  float l = va_arg_float(alist);
  float m = va_arg_float(alist);
  float n = va_arg_float(alist);
  float o = va_arg_float(alist);
  float p = va_arg_float(alist);
  float r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
  fprintf(out,"float f(16*float):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
  fflush(out);
  va_return_float(alist, r);
}}

/* double tests */
void d_d_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&d_d) { fprintf(out,"wrong data for d_d\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double r=a+1.0;
  fprintf(out,"double f(double):(%g)",a);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d2_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&d_d2) { fprintf(out,"wrong data for d_d2\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double r=a+b;
  fprintf(out,"double f(2*double):(%g,%g)",a,b);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d4_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&d_d4) { fprintf(out,"wrong data for d_d4\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double r=a+b+c+d;
  fprintf(out,"double f(4*double):(%g,%g,%g,%g)",a,b,c,d);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d8_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&d_d8) { fprintf(out,"wrong data for d_d8\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double e = va_arg_double(alist);
  double f = va_arg_double(alist);
  double g = va_arg_double(alist);
  double h = va_arg_double(alist);
  double r=a+b+c+d+e+f+g+h;
  fprintf(out,"double f(8*double):(%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d16_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&d_d16) { fprintf(out,"wrong data for d_d16\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double e = va_arg_double(alist);
  double f = va_arg_double(alist);
  double g = va_arg_double(alist);
  double h = va_arg_double(alist);
  double i = va_arg_double(alist);
  double j = va_arg_double(alist);
  double k = va_arg_double(alist);
  double l = va_arg_double(alist);
  double m = va_arg_double(alist);
  double n = va_arg_double(alist);
  double o = va_arg_double(alist);
  double p = va_arg_double(alist);
  double r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
  fprintf(out,"double f(16*double):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
  fflush(out);
  va_return_double(alist, r);
}}

/* pointer tests */
void vp_vpdpcpsp_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&vp_vpdpcpsp) { fprintf(out,"wrong data for vp_vpdpcpsp\n"); exit(1); }
  va_start_ptr(alist, void*);
 {void* a = va_arg_ptr(alist, void*);
  double* b = va_arg_ptr(alist, double*);
  char* c = va_arg_ptr(alist, char*);
  Int* d = va_arg_ptr(alist, Int*);
  void* ret = (char*)b + 1;
  fprintf(out,"void* f(void*,double*,char*,Int*):(0x%lx,0x%lx,0x%lx,0x%lx)",(long)a,(long)b,(long)c,(long)d);
  fflush(out);
  va_return_ptr(alist, void*, ret);
}}

/* mixed number tests */
void uc_ucsil_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&uc_ucsil) { fprintf(out,"wrong data for uc_ucsil\n"); exit(1); }
  va_start_uchar(alist);
 {uchar a = va_arg_uchar(alist);
  ushort b = va_arg_ushort(alist);
  uint c = va_arg_uint(alist);
  ulong d = va_arg_ulong(alist);
  uchar r=-1;
  fprintf(out,"uchar f(uchar,ushort,uint,ulong):(%u,%u,%u,%lu)",a,b,c,d);
  fflush(out);
  va_return_uchar(alist, r);
}}
void d_iidd_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&d_iidd) { fprintf(out,"wrong data for d_iidd\n"); exit(1); }
  va_start_double(alist);
 {int a = va_arg_int(alist);
  int b = va_arg_int(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double r=a+b+c+d;
  fprintf(out,"double f(int,int,double,double):(%d,%d,%g,%g)",a,b,c,d);
  fflush(out);
  va_return_double(alist, r);
}}
void d_idid_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&d_idid) { fprintf(out,"wrong data for d_idid\n"); exit(1); }
  va_start_double(alist);
 {int a = va_arg_int(alist);
  double b = va_arg_double(alist);
  int c = va_arg_int(alist);
  double d = va_arg_double(alist);
  double r=a+b+c+d;
  fprintf(out,"double f(int,double,int,double):(%d,%g,%d,%g)",a,b,c,d);
  fflush(out);
  va_return_double(alist, r);
}}
void us_cdcd_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&us_cdcd) { fprintf(out,"wrong data for us_cdcd\n"); exit(1); }
  va_start_ushort(alist);
 {char a = va_arg_char(alist);
  double b = va_arg_double(alist);
  char c = va_arg_char(alist);
  double d = va_arg_double(alist);
  ushort r = (ushort)(a + b + c + d);
  fprintf(out,"ushort f(char,double,char,double):('%c',%g,'%c',%g)",a,b,c,d);
  fflush(out);
  va_return_ushort(alist, r);
}}
#ifdef HAVE_LONGLONG
void ll_flli_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&ll_flli) { fprintf(out,"wrong data for ll_flli\n"); exit(1); }
  va_start_longlong(alist);
 {float a = va_arg_float(alist);
  long long b = va_arg_longlong(alist);
  int c = va_arg_int(alist);
  long long r = (long long)(int)a + b + (long long)c;
  fprintf(out,"long long f(float,long long,int):(%g,0x%lx%08lx,0x%lx)",a,(long)(b>>32),(long)(b&0xffffffff),(long)c);
  fflush(out);
  va_return_longlong(alist, r);
}}
#endif

#ifndef SKIP_STRUCTS
/* structure tests */
void I_III_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&I_III) { fprintf(out,"wrong data for I_III\n"); exit(1); }
 {Int a;
  Int b;
  Int c;
  Int r;
  va_start_struct(alist, Int, 1);
  a = va_arg_struct(alist, Int);
  b = va_arg_struct(alist, Int);
  c = va_arg_struct(alist, Int);
  r.x = a.x + b.x + c.x;
  fprintf(out,"Int f(Int,Int,Int):({%d},{%d},{%d})",a.x,b.x,c.x);
  fflush(out);
  va_return_struct(alist, Int, r);
}}
#ifndef SKIP_EXTRA_STRUCTS
void C_CdC_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&C_CdC) { fprintf(out,"wrong data for C_CdC\n"); exit(1); }
 {Char a;
  double b;
  Char c;
  Char r;
  va_start_struct(alist, Char, 1);
  a = va_arg_struct(alist, Char);
  b = va_arg_double(alist);
  c = va_arg_struct(alist, Char);
  r.x = (a.x + c.x)/2;
  fprintf(out,"Char f(Char,double,Char):({'%c'},%g,{'%c'})",a.x,b,c.x);
  fflush(out);
  va_return_struct(alist, Char, r);
}}
void F_Ffd_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&F_Ffd) { fprintf(out,"wrong data for F_Ffd\n"); exit(1); }
 {Float a;
  float b;
  double c;
  Float r;
  va_start_struct(alist, Float, va_word_splittable_1(float));
  a = va_arg_struct(alist, Float);
  b = va_arg_float(alist);
  c = va_arg_double(alist);
  r.x = a.x + b + c;
  fprintf(out,"Float f(Float,float,double):({%g},%g,%g)",a.x,b,c);
  fflush(out);
  va_return_struct(alist, Float, r);
}}
void D_fDd_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&D_fDd) { fprintf(out,"wrong data for D_fDd\n"); exit(1); }
 {float a;
  Double b;
  double c;
  Double r;
  va_start_struct(alist, Double, va_word_splittable_1(double));
  a = va_arg_float(alist);
  b = va_arg_struct(alist, Double);
  c = va_arg_double(alist);
  r.x = a + b.x + c;
  fprintf(out,"Double f(float,Double,double):(%g,{%g},%g)",a,b.x,c);
  fflush(out);
  va_return_struct(alist, Double, r);
}}
#endif
void J_JiJ_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&J_JiJ) { fprintf(out,"wrong data for J_JiJ\n"); exit(1); }
 {J a;
  int b;
  J c;
  J r;
  va_start_struct(alist, J, va_word_splittable_2(long,long));
  a = va_arg_struct(alist, J);
  b = va_arg_int(alist);
  c = va_arg_struct(alist, J);
  r.l1 = a.l1+c.l1; r.l2 = a.l2+b+c.l2;
  fprintf(out,"J f(J,int,J):({%ld,%ld},%d,{%ld,%ld})",a.l1,a.l2,b,c.l1,c.l2);
  fflush(out);
  va_return_struct(alist, J, r);
}}
#ifndef SKIP_EXTRA_STRUCTS
void T_TcT_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&T_TcT) { fprintf(out,"wrong data for T_TcT\n"); exit(1); }
 {T a;
  char b;
  T c;
  T r;
  va_start_struct(alist, T, 1);
  a = va_arg_struct(alist, T);
  b = va_arg_char(alist);
  c = va_arg_struct(alist, T);
  r.c[0]='b'; r.c[1]=c.c[1]; r.c[2]=c.c[2];
  fprintf(out,"T f(T,char,T):({\"%c%c%c\"},'%c',{\"%c%c%c\"})",a.c[0],a.c[1],a.c[2],b,c.c[0],c.c[1],c.c[2]);
  fflush(out);
  va_return_struct(alist, T, r);
}}
void X_BcdB_simulator _P((data,alist), void* data _ va_alist alist)
{
  if (data != (void*)&X_BcdB) { fprintf(out,"wrong data for X_BcdB\n"); exit(1); }
 {B a;
  char b;
  double c;
  B d;
  static X xr={"return val",'R'};
  X r;
  va_start_struct(alist, X, 0);
  a = va_arg_struct(alist, B);
  b = va_arg_char(alist);
  c = va_arg_double(alist);
  d = va_arg_struct(alist, B);
  r = xr;
  r.c1 = b;
  fprintf(out,"X f(B,char,double,B):({%g,{%d,%d,%d}},'%c',%g,{%g,{%d,%d,%d}})",
          a.d,a.i[0],a.i[1],a.i[2],b,c,d.d,d.i[0],d.i[1],d.i[2]);
  fflush(out);
  va_return_struct(alist, X, r);
}}
#endif
#endif

/*
 * The way we run these tests - first call the function directly, then
 * through vacall() - there is the danger that arguments or results seem
 * to be passed correctly, but what we are seeing are in fact the vestiges
 * (traces) or the previous call. This may seriously fake the test.
 * Avoid this by clearing the registers between the first and the second call.
 */
long clear_traces_i _P((a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p),
  long a _ long b _ long c _ long d _ long e _ long f _ long g _ long h _
  long i _ long j _ long k _ long l _ long m _ long n _ long o _ long p)
{ return 0; }
float clear_traces_f _P((a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p),
  float a _ float b _ float c _ float d _ float e _ float f _ float g _
  float h _ float i _ float j _ float k _ float l _ float m _ float n _
  float o _ float p)
{ return 0.0; }
double clear_traces_d _P((a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p),
  double a _ double b _ double c _ double d _ double e _ double f _ double g _
  double h _ double i _ double j _ double k _ double l _ double m _ double n _
  double o _ double p)
{ return 0.0; }
J clear_traces_J ()
{ J j; j.l1 = j.l2 = 0; return j; }
void clear_traces()
{ clear_traces_i(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  clear_traces_f(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
  clear_traces_d(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
  clear_traces_J();
}

int main ()
{
  __TR_function callback;

  out = stdout;

  /* void tests */
  v_v();
  clear_traces();
  callback = alloc_callback(&v_v_simulator,(void*)&v_v);
  (FTYPE(void,(void)) callback) ();

  /* int tests */
  { int ir;

    ir = i_v();
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    callback = alloc_callback(&i_v_simulator,(void*)&i_v);
    ir = (FTYPE(int,(void)) callback) ();
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i(i1);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    callback = alloc_callback(&i_i_simulator,(void*)&i_i);
    ir = (FTYPE(int,(int)) callback) (i1);
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i2(i1,i2);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    callback = alloc_callback(&i_i2_simulator,(void*)&i_i2);
    ir = (FTYPE(int,(int,int)) callback) (i1,i2);
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i4(i1,i2,i3,i4);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    callback = alloc_callback(&i_i4_simulator,(void*)&i_i4);
    ir = (FTYPE(int,(int,int,int,int)) callback) (i1,i2,i3,i4);
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i8(i1,i2,i3,i4,i5,i6,i7,i8);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    callback = alloc_callback(&i_i8_simulator,(void*)&i_i8);
    ir = (FTYPE(int,(int,int,int,int,int,int,int,int)) callback) (i1,i2,i3,i4,i5,i6,i7,i8);
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i16(i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    callback = alloc_callback(&i_i16_simulator,(void*)&i_i16);
    ir = (FTYPE(int,(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int)) callback) (i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16);
    fprintf(out,"->%d\n",ir);
    fflush(out);
  }

  /* float tests */
  { float fr;

    fr = f_f(f1);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f_simulator,(void*)&f_f);
    fr = (FTYPE(float,(float)) callback) (f1);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f2(f1,f2);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f2_simulator,(void*)&f_f2);
    fr = (FTYPE(float,(float,float)) callback) (f1,f2);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f4(f1,f2,f3,f4);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f4_simulator,(void*)&f_f4);
    fr = (FTYPE(float,(float,float,float,float)) callback) (f1,f2,f3,f4);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f8(f1,f2,f3,f4,f5,f6,f7,f8);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f8_simulator,(void*)&f_f8);
    fr = (FTYPE(float,(float,float,float,float,float,float,float,float)) callback) (f1,f2,f3,f4,f5,f6,f7,f8);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f16(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f16_simulator,(void*)&f_f16);
    fr = (FTYPE(float,(float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float)) callback) (f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16);
    fprintf(out,"->%g\n",fr);
    fflush(out);
  }

  /* double tests */
  { double dr;

    dr = d_d(d1);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d_simulator,(void*)&d_d);
    dr = (FTYPE(double,(double)) callback) (d1);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d2(d1,d2);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d2_simulator,(void*)&d_d2);
    dr = (FTYPE(double,(double,double)) callback) (d1,d2);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d4(d1,d2,d3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d4_simulator,(void*)&d_d4);
    dr = (FTYPE(double,(double,double,double,double)) callback) (d1,d2,d3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d8(d1,d2,d3,d4,d5,d6,d7,d8);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d8_simulator,(void*)&d_d8);
    dr = (FTYPE(double,(double,double,double,double,double,double,double,double)) callback) (d1,d2,d3,d4,d5,d6,d7,d8);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d16(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d16_simulator,(void*)&d_d16);
    dr = (FTYPE(double,(double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double)) callback) (d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16);
    fprintf(out,"->%g\n",dr);
    fflush(out);
  }

  /* pointer tests */
  { void* vpr;

    vpr = vp_vpdpcpsp(&uc1,&d2,str3,&I4);
    fprintf(out,"->0x%lx\n",(long)vpr);
    fflush(out);
    vpr = 0; clear_traces();
    callback = alloc_callback(&vp_vpdpcpsp_simulator,(void*)&vp_vpdpcpsp);
    vpr = (FTYPE(void*,(void*,double*,char*,Int*)) callback) (&uc1,&d2,str3,&I4);
    fprintf(out,"->0x%lx\n",(long)vpr);
    fflush(out);
  }

  /* mixed number tests */
  { uchar ucr;
    ushort usr;
    double dr;
#ifdef HAVE_LONGLONG
    long long llr;
#endif

    ucr = uc_ucsil(uc1,us2,ui3,ul4);
    fprintf(out,"->%u\n",ucr);
    fflush(out);
    ucr = 0; clear_traces();
    callback = alloc_callback(&uc_ucsil_simulator,(void*)&uc_ucsil);
    ucr = (FTYPE(uchar,(uchar,ushort,uint,ulong)) callback) (uc1,us2,ui3,ul4);
    fprintf(out,"->%u\n",ucr);
    fflush(out);

    dr = d_iidd(i1,i2,d3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_iidd_simulator,(void*)&d_iidd);
    dr = (FTYPE(double,(int,int,double,double)) callback) (i1,i2,d3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_idid(i1,d2,i3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_idid_simulator,(void*)&d_idid);
    dr = (FTYPE(double,(int,double,int,double)) callback) (i1,d2,i3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    usr = us_cdcd(c1,d2,c3,d4);
    fprintf(out,"->%u\n",usr);
    fflush(out);
    usr = 0; clear_traces();
    callback = alloc_callback(&us_cdcd_simulator,(void*)&us_cdcd);
    usr = (FTYPE(ushort,(char,double,char,double)) callback) (c1,d2,c3,d4);
    fprintf(out,"->%u\n",usr);
    fflush(out);

#ifdef HAVE_LONGLONG
    llr = ll_flli(f13,ll1,i13);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    callback = alloc_callback(&ll_flli_simulator,(void*)&ll_flli);
    llr = (FTYPE(long long,(float,long long,int)) callback) (f13,ll1,i13);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
#endif
  }

#ifndef SKIP_STRUCTS
  /* structure tests */
  { Int Ir;
    Char Cr;
    Float Fr;
    Double Dr;
    J Jr;
    T Tr;
    X Xr;

    Ir = I_III(I1,I2,I3);
    fprintf(out,"->{%d}\n",Ir.x);
    fflush(out);
    Ir.x = 0; clear_traces();
    callback = alloc_callback(&I_III_simulator,(void*)&I_III);
    Ir = (FTYPE(Int,(Int,Int,Int)) callback) (I1,I2,I3);
    fprintf(out,"->{%d}\n",Ir.x);
    fflush(out);

#ifndef SKIP_EXTRA_STRUCTS
    Cr = C_CdC(C1,d2,C3);
    fprintf(out,"->{'%c'}\n",Cr.x);
    fflush(out);
    Cr.x = '\0'; clear_traces();
    callback = alloc_callback(&C_CdC_simulator,(void*)&C_CdC);
    Cr = (FTYPE(Char,(Char,double,Char)) callback) (C1,d2,C3);
    fprintf(out,"->{'%c'}\n",Cr.x);
    fflush(out);

    Fr = F_Ffd(F1,f2,d3);
    fprintf(out,"->{%g}\n",Fr.x);
    fflush(out);
    Fr.x = 0.0; clear_traces();
    callback = alloc_callback(&F_Ffd_simulator,(void*)&F_Ffd);
    Fr = (FTYPE(Float,(Float,float,double)) callback) (F1,f2,d3);
    fprintf(out,"->{%g}\n",Fr.x);
    fflush(out);

    Dr = D_fDd(f1,D2,d3);
    fprintf(out,"->{%g}\n",Dr.x);
    fflush(out);
    Dr.x = 0.0; clear_traces();
    callback = alloc_callback(&D_fDd_simulator,(void*)&D_fDd);
    Dr = (FTYPE(Double,(float,Double,double)) callback) (f1,D2,d3);
    fprintf(out,"->{%g}\n",Dr.x);
    fflush(out);
#endif

    Jr = J_JiJ(J1,i2,J2);
    fprintf(out,"->{%ld,%ld}\n",Jr.l1,Jr.l2);
    fflush(out);
    Jr.l1 = Jr.l2 = 0; clear_traces();
    callback = alloc_callback(&J_JiJ_simulator,(void*)&J_JiJ);
    Jr = (FTYPE(J,(J,int,J)) callback) (J1,i2,J2);
    fprintf(out,"->{%ld,%ld}\n",Jr.l1,Jr.l2);
    fflush(out);

#ifndef SKIP_EXTRA_STRUCTS
#ifndef SKIP_T
    Tr = T_TcT(T1,' ',T2);
    fprintf(out,"->{\"%c%c%c\"}\n",Tr.c[0],Tr.c[1],Tr.c[2]);
    fflush(out);
    Tr.c[0] = Tr.c[1] = Tr.c[2] = 0; clear_traces();
    callback = alloc_callback(&T_TcT_simulator,(void*)&T_TcT);
    Tr = (FTYPE(T,(T,char,T)) callback) (T1,' ',T2);
    fprintf(out,"->{\"%c%c%c\"}\n",Tr.c[0],Tr.c[1],Tr.c[2]);
    fflush(out);
#endif

#ifndef SKIP_X
    Xr = X_BcdB(B1,c2,d3,B2);
    fprintf(out,"->{\"%s\",'%c'}\n",Xr.c,Xr.c1);
    fflush(out);
    Xr.c[0]=Xr.c1='\0'; clear_traces();
    callback = alloc_callback(&X_BcdB_simulator,(void*)&X_BcdB);
    Xr = (FTYPE(X,(B,char,double,B)) callback) (B1,c2,d3,B2);
    fprintf(out,"->{\"%s\",'%c'}\n",Xr.c,Xr.c1);
    fflush(out);
#endif
#endif
  }
#endif

  exit(0);
}
