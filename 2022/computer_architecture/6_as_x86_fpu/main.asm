; vim: ft=masm
.686 
.model flat,stdcall 
.stack 
 
.data 
 
A REAL4 9.8 
B REAL4 8.5; C variable 
D REAL4 2.3 
C1 REAL4 47.0 
C2 REAL4 7.6 
C3 REAL4 6.9 
C4 REAL4 8.1 
C5 REAL4 9.7 
 
TOP REAL4 ? 
BOT REAL4 ? 
 
RES REAL4 ? 
 
.code 
main: 
finit 
fld  D 
fmul A ; st0 = D * A
fld  B 
fmul B ; st0 = C * C, st1 = D * A
fadd
fabs ; st0 = abs(C * C + D * A)
fld  C1 ; st0 = C1, st1 = abs(C * C + D * A)
fmul A ; st0 = C1 * A, st1 = abs(C * C + D * A)
fadd C2  ; st0 = C1 * A + C2, st1 = abs(C * C + D * A)
fsqrt ; st0 = sqrt(C1 * A + C2), st1 = abs(C * C + D * A)
fsubp 
fst TOP 
 
fld  D 
fmul C3 
fld  B 
fdiv C4 
fld  C5 
fmul A 
fsubp 
faddp 
fst BOT 
 
fld  TOP 
fdiv BOT 
fst RES 
 
RET 
END main
