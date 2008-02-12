/* To know more about structure passing conventions,
 * compile this to assembly code: $(CC) -O -S port-structs.c
 */

typedef struct { char x1; } C1;
typedef struct { char x1,x2; } C2;
typedef struct { char x1,x2,x3; } C3;
typedef struct { char x1,x2,x3,x4; } C4;
typedef struct { char x1,x2,x3,x4,x5; } C5;
typedef struct { char x1,x2,x3,x4,x5,x6; } C6;
typedef struct { char x1,x2,x3,x4,x5,x6,x7; } C7;
typedef struct { char x1,x2,x3,x4,x5,x6,x7,x8; } C8;
typedef struct { char x1,x2,x3,x4,x5,x6,x7,x8,x9; } C9;
typedef struct { char x1,x2,x3,x4,x5,x6,x7,x8,x9,x10; } C10;
typedef struct { char x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11; } C11;
typedef struct { char x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12; } C12;
typedef struct { char x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13; } C13;
typedef struct { char x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14; } C14;
typedef struct { char x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15; } C15;
typedef struct { char x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16; } C16;

typedef struct { char x[1]; } CA1;
typedef struct { char x[2]; } CA2;
typedef struct { char x[3]; } CA3;
typedef struct { char x[4]; } CA4;
typedef struct { char x[5]; } CA5;
typedef struct { char x[6]; } CA6;
typedef struct { char x[7]; } CA7;
typedef struct { char x[8]; } CA8;
typedef struct { char x[9]; } CA9;
typedef struct { char x[10]; } CA10;
typedef struct { char x[11]; } CA11;
typedef struct { char x[12]; } CA12;
typedef struct { char x[13]; } CA13;
typedef struct { char x[14]; } CA14;
typedef struct { char x[15]; } CA15;
typedef struct { char x[16]; } CA16;

typedef struct { short x1; } S1;
typedef struct { short x1,x2; } S2;
typedef struct { short x1,x2,x3; } S3;
typedef struct { short x1,x2,x3,x4; } S4;
typedef struct { short x1,x2,x3,x4,x5; } S5;
typedef struct { short x1,x2,x3,x4,x5,x6; } S6;
typedef struct { short x1,x2,x3,x4,x5,x6,x7; } S7;
typedef struct { short x1,x2,x3,x4,x5,x6,x7,x8; } S8;

typedef struct { short x[1]; } SA1;
typedef struct { short x[2]; } SA2;
typedef struct { short x[3]; } SA3;
typedef struct { short x[4]; } SA4;
typedef struct { short x[5]; } SA5;
typedef struct { short x[6]; } SA6;
typedef struct { short x[7]; } SA7;
typedef struct { short x[8]; } SA8;

typedef struct { int x1; } I1;
typedef struct { int x1,x2; } I2;
typedef struct { int x1,x2,x3; } I3;
typedef struct { int x1,x2,x3,x4; } I4;
typedef struct { int x1,x2,x3,x4,x5; } I5;
typedef struct { int x1,x2,x3,x4,x5,x6; } I6;
typedef struct { int x1,x2,x3,x4,x5,x6,x7; } I7;
typedef struct { int x1,x2,x3,x4,x5,x6,x7,x8; } I8;

typedef struct { int x[1]; } IA1;
typedef struct { int x[2]; } IA2;
typedef struct { int x[3]; } IA3;
typedef struct { int x[4]; } IA4;
typedef struct { int x[5]; } IA5;
typedef struct { int x[6]; } IA6;
typedef struct { int x[7]; } IA7;
typedef struct { int x[8]; } IA8;

typedef struct { long x1; } L1;
typedef struct { long x1,x2; } L2;
typedef struct { long x1,x2,x3; } L3;
typedef struct { long x1,x2,x3,x4; } L4;
typedef struct { long x1,x2,x3,x4,x5; } L5;
typedef struct { long x1,x2,x3,x4,x5,x6; } L6;
typedef struct { long x1,x2,x3,x4,x5,x6,x7; } L7;
typedef struct { long x1,x2,x3,x4,x5,x6,x7,x8; } L8;
typedef struct { long x1,x2,x3,x4,x5,x6,x7,x8,x9; } L9;

typedef struct { long x[1]; } LA1;
typedef struct { long x[2]; } LA2;
typedef struct { long x[3]; } LA3;
typedef struct { long x[4]; } LA4;
typedef struct { long x[5]; } LA5;
typedef struct { long x[6]; } LA6;
typedef struct { long x[7]; } LA7;
typedef struct { long x[8]; } LA8;
typedef struct { long x[9]; } LA9;

typedef struct { float x1; } F1;
typedef struct { float x1,x2; } F2;
typedef struct { float x1,x2,x3; } F3;
typedef struct { float x1,x2,x3,x4; } F4;

typedef struct { float x[1]; } FA1;
typedef struct { float x[2]; } FA2;
typedef struct { float x[3]; } FA3;
typedef struct { float x[4]; } FA4;

typedef struct { double x1; } D1;
typedef struct { double x1,x2; } D2;

typedef struct { double x[1]; } DA1;
typedef struct { double x[2]; } DA2;

typedef struct { char c; float f; } CF;

typedef struct { float f; int i; } FI;
typedef struct { float f; int i,j; } FI2;
typedef struct { float f; int i,j,k; } FI3;

typedef struct { double d; int i; } DI;
typedef struct { double d; int i,j; } DI2;
typedef struct { double d; int i,j,k; } DI3;

typedef struct { float f; double d; } FD;
typedef struct { float f,g; double d; } F2D;

typedef struct { double d; float f; } DF;
typedef struct { double d; float f,g; } DF2;


#if defined(__STDC__) || defined(__cplusplus)
#define TEST_STRUCT_ARG(_type_)  \
  extern _type_ extern_##_type_;					\
  void set_##_type_ (_type_ arg) { extern_##_type_ = arg; }
#define TEST_STRUCT_RETURN(_type_)  \
  extern _type_ extern_##_type_;					\
  _type_ get_##_type_ () { return extern_##_type_; }
#else
#define TEST_STRUCT_ARG(_type_)  \
  extern _type_ extern_/**/_type_;					\
  void set_/**/_type_ (arg) _type_ arg; { extern_/**/_type_ = arg; }
#define TEST_STRUCT_RETURN(_type_)  \
  extern _type_ extern_/**/_type_;					\
  _type_ get_/**/_type_ () { return extern_/**/_type_; }
#endif


TEST_STRUCT_ARG(C1)
TEST_STRUCT_ARG(C2)
TEST_STRUCT_ARG(C3)
TEST_STRUCT_ARG(C4)
TEST_STRUCT_ARG(C5)
TEST_STRUCT_ARG(C6)
TEST_STRUCT_ARG(C7)
TEST_STRUCT_ARG(C8)
TEST_STRUCT_ARG(C9)
TEST_STRUCT_ARG(C10)
TEST_STRUCT_ARG(C11)
TEST_STRUCT_ARG(C12)
TEST_STRUCT_ARG(C13)
TEST_STRUCT_ARG(C14)
TEST_STRUCT_ARG(C15)
TEST_STRUCT_ARG(C16)
TEST_STRUCT_ARG(CA1)
TEST_STRUCT_ARG(CA2)
TEST_STRUCT_ARG(CA3)
TEST_STRUCT_ARG(CA4)
TEST_STRUCT_ARG(CA5)
TEST_STRUCT_ARG(CA6)
TEST_STRUCT_ARG(CA7)
TEST_STRUCT_ARG(CA8)
TEST_STRUCT_ARG(CA9)
TEST_STRUCT_ARG(CA10)
TEST_STRUCT_ARG(CA11)
TEST_STRUCT_ARG(CA12)
TEST_STRUCT_ARG(CA13)
TEST_STRUCT_ARG(CA14)
TEST_STRUCT_ARG(CA15)
TEST_STRUCT_ARG(CA16)
TEST_STRUCT_ARG(S1)
TEST_STRUCT_ARG(S2)
TEST_STRUCT_ARG(S3)
TEST_STRUCT_ARG(S4)
TEST_STRUCT_ARG(S5)
TEST_STRUCT_ARG(S6)
TEST_STRUCT_ARG(S7)
TEST_STRUCT_ARG(S8)
TEST_STRUCT_ARG(SA1)
TEST_STRUCT_ARG(SA2)
TEST_STRUCT_ARG(SA3)
TEST_STRUCT_ARG(SA4)
TEST_STRUCT_ARG(SA5)
TEST_STRUCT_ARG(SA6)
TEST_STRUCT_ARG(SA7)
TEST_STRUCT_ARG(SA8)
TEST_STRUCT_ARG(I1)
TEST_STRUCT_ARG(I2)
TEST_STRUCT_ARG(I3)
TEST_STRUCT_ARG(I4)
TEST_STRUCT_ARG(I5)
TEST_STRUCT_ARG(I6)
TEST_STRUCT_ARG(I7)
TEST_STRUCT_ARG(I8)
TEST_STRUCT_ARG(IA1)
TEST_STRUCT_ARG(IA2)
TEST_STRUCT_ARG(IA3)
TEST_STRUCT_ARG(IA4)
TEST_STRUCT_ARG(IA5)
TEST_STRUCT_ARG(IA6)
TEST_STRUCT_ARG(IA7)
TEST_STRUCT_ARG(IA8)
TEST_STRUCT_ARG(L1)
TEST_STRUCT_ARG(L2)
TEST_STRUCT_ARG(L3)
TEST_STRUCT_ARG(L4)
TEST_STRUCT_ARG(L5)
TEST_STRUCT_ARG(L6)
TEST_STRUCT_ARG(L7)
TEST_STRUCT_ARG(L8)
TEST_STRUCT_ARG(L9)
TEST_STRUCT_ARG(LA1)
TEST_STRUCT_ARG(LA2)
TEST_STRUCT_ARG(LA3)
TEST_STRUCT_ARG(LA4)
TEST_STRUCT_ARG(LA5)
TEST_STRUCT_ARG(LA6)
TEST_STRUCT_ARG(LA7)
TEST_STRUCT_ARG(LA8)
TEST_STRUCT_ARG(LA9)
TEST_STRUCT_ARG(F1)
TEST_STRUCT_ARG(F2)
TEST_STRUCT_ARG(F3)
TEST_STRUCT_ARG(F4)
TEST_STRUCT_ARG(FA1)
TEST_STRUCT_ARG(FA2)
TEST_STRUCT_ARG(FA3)
TEST_STRUCT_ARG(FA4)
TEST_STRUCT_ARG(D1)
TEST_STRUCT_ARG(D2)
TEST_STRUCT_ARG(DA1)
TEST_STRUCT_ARG(DA2)
TEST_STRUCT_ARG(CF)
TEST_STRUCT_ARG(FI)
TEST_STRUCT_ARG(FI2)
TEST_STRUCT_ARG(FI3)
TEST_STRUCT_ARG(DI)
TEST_STRUCT_ARG(DI2)
TEST_STRUCT_ARG(DI3)
TEST_STRUCT_ARG(FD)
TEST_STRUCT_ARG(F2D)
TEST_STRUCT_ARG(DF)
TEST_STRUCT_ARG(DF2)

TEST_STRUCT_RETURN(C1)
TEST_STRUCT_RETURN(C2)
TEST_STRUCT_RETURN(C3)
TEST_STRUCT_RETURN(C4)
TEST_STRUCT_RETURN(C5)
TEST_STRUCT_RETURN(C6)
TEST_STRUCT_RETURN(C7)
TEST_STRUCT_RETURN(C8)
TEST_STRUCT_RETURN(C9)
TEST_STRUCT_RETURN(C10)
TEST_STRUCT_RETURN(C11)
TEST_STRUCT_RETURN(C12)
TEST_STRUCT_RETURN(C13)
TEST_STRUCT_RETURN(C14)
TEST_STRUCT_RETURN(C15)
TEST_STRUCT_RETURN(C16)
TEST_STRUCT_RETURN(CA1)
TEST_STRUCT_RETURN(CA2)
TEST_STRUCT_RETURN(CA3)
TEST_STRUCT_RETURN(CA4)
TEST_STRUCT_RETURN(CA5)
TEST_STRUCT_RETURN(CA6)
TEST_STRUCT_RETURN(CA7)
TEST_STRUCT_RETURN(CA8)
TEST_STRUCT_RETURN(CA9)
TEST_STRUCT_RETURN(CA10)
TEST_STRUCT_RETURN(CA11)
TEST_STRUCT_RETURN(CA12)
TEST_STRUCT_RETURN(CA13)
TEST_STRUCT_RETURN(CA14)
TEST_STRUCT_RETURN(CA15)
TEST_STRUCT_RETURN(CA16)
TEST_STRUCT_RETURN(S1)
TEST_STRUCT_RETURN(S2)
TEST_STRUCT_RETURN(S3)
TEST_STRUCT_RETURN(S4)
TEST_STRUCT_RETURN(S5)
TEST_STRUCT_RETURN(S6)
TEST_STRUCT_RETURN(S7)
TEST_STRUCT_RETURN(S8)
TEST_STRUCT_RETURN(SA1)
TEST_STRUCT_RETURN(SA2)
TEST_STRUCT_RETURN(SA3)
TEST_STRUCT_RETURN(SA4)
TEST_STRUCT_RETURN(SA5)
TEST_STRUCT_RETURN(SA6)
TEST_STRUCT_RETURN(SA7)
TEST_STRUCT_RETURN(SA8)
TEST_STRUCT_RETURN(I1)
TEST_STRUCT_RETURN(I2)
TEST_STRUCT_RETURN(I3)
TEST_STRUCT_RETURN(I4)
TEST_STRUCT_RETURN(I5)
TEST_STRUCT_RETURN(I6)
TEST_STRUCT_RETURN(I7)
TEST_STRUCT_RETURN(I8)
TEST_STRUCT_RETURN(IA1)
TEST_STRUCT_RETURN(IA2)
TEST_STRUCT_RETURN(IA3)
TEST_STRUCT_RETURN(IA4)
TEST_STRUCT_RETURN(IA5)
TEST_STRUCT_RETURN(IA6)
TEST_STRUCT_RETURN(IA7)
TEST_STRUCT_RETURN(IA8)
TEST_STRUCT_RETURN(L1)
TEST_STRUCT_RETURN(L2)
TEST_STRUCT_RETURN(L3)
TEST_STRUCT_RETURN(L4)
TEST_STRUCT_RETURN(L5)
TEST_STRUCT_RETURN(L6)
TEST_STRUCT_RETURN(L7)
TEST_STRUCT_RETURN(L8)
TEST_STRUCT_RETURN(L9)
TEST_STRUCT_RETURN(LA1)
TEST_STRUCT_RETURN(LA2)
TEST_STRUCT_RETURN(LA3)
TEST_STRUCT_RETURN(LA4)
TEST_STRUCT_RETURN(LA5)
TEST_STRUCT_RETURN(LA6)
TEST_STRUCT_RETURN(LA7)
TEST_STRUCT_RETURN(LA8)
TEST_STRUCT_RETURN(LA9)
TEST_STRUCT_RETURN(F1)
TEST_STRUCT_RETURN(F2)
TEST_STRUCT_RETURN(F3)
TEST_STRUCT_RETURN(F4)
TEST_STRUCT_RETURN(FA1)
TEST_STRUCT_RETURN(FA2)
TEST_STRUCT_RETURN(FA3)
TEST_STRUCT_RETURN(FA4)
TEST_STRUCT_RETURN(D1)
TEST_STRUCT_RETURN(D2)
TEST_STRUCT_RETURN(DA1)
TEST_STRUCT_RETURN(DA2)
TEST_STRUCT_RETURN(CF)
TEST_STRUCT_RETURN(FI)
TEST_STRUCT_RETURN(FI2)
TEST_STRUCT_RETURN(FI3)
TEST_STRUCT_RETURN(DI)
TEST_STRUCT_RETURN(DI2)
TEST_STRUCT_RETURN(DI3)
TEST_STRUCT_RETURN(FD)
TEST_STRUCT_RETURN(F2D)
TEST_STRUCT_RETURN(DF)
TEST_STRUCT_RETURN(DF2)

