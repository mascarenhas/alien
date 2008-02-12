#ifndef _tests_c				/*-*- C -*-*/
#define _tests_c
/**
  Copyright 1993 Bill Triggs, <Bill.Triggs@inrialpes.fr>

  This is free software distributed under the GNU General Public
  Licence described in the file COPYING. Contact the author if
  you don't have this or can't live with it. There is ABSOLUTELY
  NO WARRANTY, explicit or implied, on this software.
**/
/*----------------------------------------------------------------------
  Some test routines for avcall foreign function interface.
  The coverage is entirely random, this just contains some of the things
  that I think are likely to break.

  We really need to add some more pointer (void* / char* / func*) tests
  and some varargs ones, and also try to test structure alignment more
  throughly.
 ----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avcall.h"
FILE* out;

/* NB since K&R C always passes chars and shorts as ints and floats as doubles,
 * unprototyped ANSI-C functions must do the same, eg:
 * - foo(x) float x; { ... } passes x as a double & converts it to a float internally.
 * - foo(float x) { ... } passes x as a float.
 */
#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
#define _ ,
#define _P(ARGS,TYPES) (TYPES)
#else
#define _ ;
#define _P(ARGS,TYPES) ARGS TYPES;
#endif

#if defined(__hppa__) && defined(__GNUC__)
#if (__GNUC__ == 2 && __GNUC_MINOR__ < 6)
/* gcc-2.5.2 bugs prevent the T test from working. */
#define SKIP_T
#endif
#endif
#if defined(__m68k__) && defined(__GNUC__)
/* "gcc-2.6.3 -freg-struct-return" returns  T = struct { char c[3]; }  (which
 * has size 4 !) in memory, in contrast to  struct { char a,b,c; }  and
 * struct { char c[4]; }  and  struct { char a,b,c,d; }  which have the same
 * size and the same alignment but are returned in registers. I don't know why.
 */
#define SKIP_T
#endif

#if defined(AMIGA)
/* We don't test passing arguments in registers yet.
 * -1 means passing an argument in the stack instead of a register.
 */
#define AV_ARG_REGNUM -1
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

void v_v()
{
  fprintf(out,"void f(void):\n");
  fflush(out);
}
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

void* vp_vpdpcpsp _P((a,b,c,d), void* a _ double* b _ char* c _ Int* d)
{
  void* ret = (char*)b + 1;
  fprintf(out,"void* f(void*,double*,char*,Int*):(0x%lx,0x%lx,0x%lx,0x%lx)",(long)a,(long)b,(long)c,(long)d);
  fflush(out);
  return ret;
}

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

Int I_III _P((a,b,c), Int a _ Int b _ Int c)
{
  Int r;
  r.x = a.x + b.x + c.x;
  fprintf(out,"Int f(Int,Int,Int):({%d},{%d},{%d})",a.x,b.x,c.x);
  fflush(out);
  return r;
}
#ifndef SKIP_EXTRA_STRUCTS
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
#endif
J J_JiJ _P((a,b,c), J a _ int b _ J c)
{
  J r;
  r.l1 = a.l1+c.l1; r.l2 = a.l2+b+c.l2;
  fprintf(out,"J f(J,int,J):({%ld,%ld},%d,{%ld,%ld})",a.l1,a.l2,b,c.l1,c.l2);
  fflush(out);
  return r;
}
#ifndef SKIP_EXTRA_STRUCTS
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
#endif

/*
 * The way we run these tests - first call the function directly, then
 * through av_call() - there is the danger that arguments or results seem
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

void
  void_tests()
{
  av_alist a;
  v_v();
  clear_traces();
  av_start_void(a,v_v);
  av_call(a);
  return;
}
void
  int_tests()
{
  av_alist a;
  int ir;

  ir = i_v();
  fprintf(out,"->%d\n",ir);
  fflush(out);
  ir = 0; clear_traces();
  av_start_int(a,i_v,&ir);
  av_call(a);
  fprintf(out,"->%d\n",ir);
  fflush(out);

  ir = i_i(i1);
  fprintf(out,"->%d\n",ir);
  fflush(out);
  ir = 0; clear_traces();
  av_start_int(a,i_i,&ir);
  av_int(a,i1);
  av_call(a);
  fprintf(out,"->%d\n",ir);
  fflush(out);

  ir = i_i2(i1,i2);
  fprintf(out,"->%d\n",ir);
  fflush(out);
  ir = 0; clear_traces();
  av_start_int(a,i_i2,&ir);
  av_int(a,i1);
  av_int(a,i2);
  av_call(a);
  fprintf(out,"->%d\n",ir);
  fflush(out);

  ir = i_i4(i1,i2,i3,i4);
  fprintf(out,"->%d\n",ir);
  fflush(out);
  ir = 0; clear_traces();
  av_start_int(a,i_i4,&ir);
  av_int(a,i1);
  av_int(a,i2);
  av_int(a,i3);
  av_int(a,i4);
  av_call(a);
  fprintf(out,"->%d\n",ir);
  fflush(out);

  ir = i_i8(i1,i2,i3,i4,i5,i6,i7,i8);
  fprintf(out,"->%d\n",ir);
  fflush(out);
  ir = 0; clear_traces();
  av_start_int(a,i_i8,&ir);
  av_int(a,i1);
  av_int(a,i2);
  av_int(a,i3);
  av_int(a,i4);
  av_int(a,i5);
  av_int(a,i6);
  av_int(a,i7);
  av_int(a,i8);
  av_call(a);
  fprintf(out,"->%d\n",ir);
  fflush(out);

  ir = i_i16(i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16);
  fprintf(out,"->%d\n",ir);
  fflush(out);
  ir = 0; clear_traces();
  av_start_int(a,i_i16,&ir);
  av_int(a,i1);
  av_int(a,i2);
  av_int(a,i3);
  av_int(a,i4);
  av_int(a,i5);
  av_int(a,i6);
  av_int(a,i7);
  av_int(a,i8);
  av_int(a,i9);
  av_int(a,i10);
  av_int(a,i11);
  av_int(a,i12);
  av_int(a,i13);
  av_int(a,i14);
  av_int(a,i15);
  av_int(a,i16);
  av_call(a);
  fprintf(out,"->%d\n",ir);
  fflush(out);

  return;
}
void
  float_tests()
{
  av_alist a;
  float fr;

  fr = f_f(f1);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f,&fr);
  av_float(a,f1);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f2(f1,f2);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f2,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f4(f1,f2,f3,f4);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f4,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f8(f1,f2,f3,f4,f5,f6,f7,f8);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f8,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_float(a,f5);
  av_float(a,f6);
  av_float(a,f7);
  av_float(a,f8);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f16(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f16,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_float(a,f5);
  av_float(a,f6);
  av_float(a,f7);
  av_float(a,f8);
  av_float(a,f9);
  av_float(a,f10);
  av_float(a,f11);
  av_float(a,f12);
  av_float(a,f13);
  av_float(a,f14);
  av_float(a,f15);
  av_float(a,f16);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);
}
void
  double_tests()
{
  av_alist a;
  double dr;

  dr = d_d(d1);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d,&dr);
  av_double(a,d1);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d2(d1,d2);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d2,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d4(d1,d2,d3,d4);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d4,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_double(a,d4);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d8(d1,d2,d3,d4,d5,d6,d7,d8);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d8,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_double(a,d4);
  av_double(a,d5);
  av_double(a,d6);
  av_double(a,d7);
  av_double(a,d8);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d16(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d16,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_double(a,d4);
  av_double(a,d5);
  av_double(a,d6);
  av_double(a,d7);
  av_double(a,d8);
  av_double(a,d9);
  av_double(a,d10);
  av_double(a,d11);
  av_double(a,d12);
  av_double(a,d13);
  av_double(a,d14);
  av_double(a,d15);
  av_double(a,d16);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  return;
}
void
  mixed_number_tests()
{
  av_alist a;
  uchar ucr;
  ushort usr;
  double dr;
#ifdef HAVE_LONGLONG
  long long llr;
#endif

  /* Unsigned types.
   */
  ucr = uc_ucsil(uc1,us2,ui3,ul4);
  fprintf(out,"->%u\n",ucr);
  fflush(out);
  ucr = 0; clear_traces();
  av_start_uchar(a,uc_ucsil,&ucr);
  av_uchar(a,uc1);
  av_ushort(a,us2);
  av_uint(a,ui3);
  av_ulong(a,ul4);
  av_call(a);
  fprintf(out,"->%u\n",ucr);
  fflush(out);

  /* Mixed int & float types.
   */
  dr = d_iidd(i1,i2,d3,d4);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_iidd,&dr);
  av_int(a,i1);
  av_int(a,i2);
  av_double(a,d3);
  av_double(a,d4);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_idid(i1,d2,i3,d4);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_idid,&dr);
  av_int(a,i1);
  av_double(a,d2);
  av_int(a,i3);
  av_double(a,d4);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  usr = us_cdcd(c1,d2,c3,d4);
  fprintf(out,"->%u\n",usr);
  fflush(out);
  usr = 0; clear_traces();
  av_start_ushort(a,us_cdcd,&usr);
  av_char(a,c1);
  av_double(a,d2);
  av_char(a,c3);
  av_double(a,d4);
  av_call(a);
  fprintf(out,"->%u\n",usr);
  fflush(out);

#ifdef HAVE_LONGLONG
  /* Long long types.
   */
  llr = ll_flli(f13,ll1,i13);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);
  llr = 0; clear_traces();
  av_start_longlong(a,ll_flli,&llr);
  av_float(a,f13);
  av_longlong(a,ll1);
  av_int(a,i13);
  av_call(a);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);
#endif

  return;
}
void
  pointer_tests()
{
  av_alist a;
  void* vpr;

  vpr = vp_vpdpcpsp(&uc1,&d2,str3,&I4);
  fprintf(out,"->0x%lx\n",(long)vpr);
  fflush(out);
  vpr = 0; clear_traces();
  av_start_ptr(a,vp_vpdpcpsp,void*,&vpr);
  av_ptr(a,void*,&uc1);
  av_ptr(a,double*,&d2);
  av_ptr(a,char*,str3);
  av_ptr(a,Int*,&I4);
  av_call(a);
  fprintf(out,"->0x%lx\n",(long)vpr);
  fflush(out);

  return;
}
void
  structure_tests()
{
  av_alist a;
  Int Ir;
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
  av_start_struct(a,I_III,Int,1,&Ir);
  av_struct(a,Int,I1);
  av_struct(a,Int,I2);
  av_struct(a,Int,I3);
  av_call(a);
  fprintf(out,"->{%d}\n",Ir.x);
  fflush(out);

#ifndef SKIP_EXTRA_STRUCTS
  Cr = C_CdC(C1,d2,C3);
  fprintf(out,"->{'%c'}\n",Cr.x);
  fflush(out);
  Cr.x = '\0'; clear_traces();
  av_start_struct(a,C_CdC,Char,1,&Cr);
  av_struct(a,Char,C1);
  av_double(a,d2);
  av_struct(a,Char,C3);
  av_call(a);
  fprintf(out,"->{'%c'}\n",Cr.x);
  fflush(out);

  Fr = F_Ffd(F1,f2,d3);
  fprintf(out,"->{%g}\n",Fr.x);
  fflush(out);
  Fr.x = 0.0; clear_traces();
  av_start_struct(a,F_Ffd,Float,av_word_splittable_1(float),&Fr);
  av_struct(a,Float,F1);
  av_float(a,f2);
  av_double(a,d3);
  av_call(a);
  fprintf(out,"->{%g}\n",Fr.x);
  fflush(out);

  Dr = D_fDd(f1,D2,d3);
  fprintf(out,"->{%g}\n",Dr.x);
  fflush(out);
  Dr.x = 0.0; clear_traces();
  av_start_struct(a,D_fDd,Double,av_word_splittable_1(double),&Dr);
  av_float(a,f1);
  av_struct(a,Double,D2);
  av_double(a,d3);
  av_call(a);
  fprintf(out,"->{%g}\n",Dr.x);
  fflush(out);
#endif

  Jr = J_JiJ(J1,i2,J2);
  fprintf(out,"->{%ld,%ld}\n",Jr.l1,Jr.l2);
  fflush(out);
  Jr.l1 = Jr.l2 = 0; clear_traces();
  av_start_struct(a,J_JiJ,J,av_word_splittable_2(long,long),&Jr);
  av_struct(a,J,J1);
  av_int(a,i2);
  av_struct(a,J,J2);
  av_call(a);
  fprintf(out,"->{%ld,%ld}\n",Jr.l1,Jr.l2);
  fflush(out);

#ifndef SKIP_EXTRA_STRUCTS
#ifndef SKIP_T
  Tr = T_TcT(T1,' ',T2);
  fprintf(out,"->{\"%c%c%c\"}\n",Tr.c[0],Tr.c[1],Tr.c[2]);
  fflush(out);
  Tr.c[0] = Tr.c[1] = Tr.c[2] = 0; clear_traces();
  av_start_struct(a,T_TcT,T,1,&Tr);
  av_struct(a,T,T1);
  av_char(a,' ');
  av_struct(a,T,T2);
  av_call(a);
  fprintf(out,"->{\"%c%c%c\"}\n",Tr.c[0],Tr.c[1],Tr.c[2]);
  fflush(out);
#endif

  Xr = X_BcdB(B1,c2,d3,B2);
  fprintf(out,"->{\"%s\",'%c'}\n",Xr.c,Xr.c1);
  fflush(out);
  Xr.c[0]=Xr.c1='\0'; clear_traces();
  av_start_struct(a,X_BcdB,X,0,&Xr);
  av_struct(a,B,B1);
  av_char(a,c2);
  av_double(a,d3);
  av_struct(a,B,B2);
  av_call(a);
  fprintf(out,"->{\"%s\",'%c'}\n",Xr.c,Xr.c1);
  fflush(out);
#endif

  return;
}
int
  main()
{
  out = stdout;
  void_tests();
  int_tests();
  float_tests();
  double_tests();
  mixed_number_tests();
  pointer_tests();
  structure_tests();

  exit(0);
}

#endif /*_tests_c */
