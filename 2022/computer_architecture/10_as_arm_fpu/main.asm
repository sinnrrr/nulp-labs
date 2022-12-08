	AREA myCode, CODE, READONLY
MyProg
	EXPORT MyProg

	LDR r0, =a
	VLDM r0, {s0-s2}  ; s0=a, s1=c, s2=d
	
	LDR r0, =n1
	VLDM r0, {s7-s11}  ; n1, n2 ... n5

	VDIV.F32 s3, s0, s1 ; s3=a/c
	VCMP.F32 s2, s3 ; d ? a/c
	VMRS APSR_nzcv, FPSCR ; load cmp resulting flags to cpu register
	BGT FIRST      ; d > a/c
	BLE SECOND      ; d <= a/c

FIRST
  VMUL.F32 s3, s1, s1; s3=c*c
  VMUL.F32 s4, s2, s0; s4=d*a
  VADD.F32 s3, s4; s3=(c*c)+(d*a)
  VABS.F32 s3, s3 

  VMUL.F32 s4, s7, s0; s4=47*a
  VADD.F32 s4, s8; s4=47*a+7.6
  VABS.F32 s4, s4
  VSQRT.F32 s4, s4

  VSUB.F32 s3, s4

  LDR r0, =y      
  VSTM r0, {s3}
  B STOP

SECOND
  VMUL.F32 s3, s9, s2; 6.9*d

  VDIV.F32 s4, s1, s10; c/8.1

  VDIV.F32 s5, s11, s0; 9.7*a

  VADD.F32 s3, s4; (6.9*d)+(c/8.1)
  VSUB.F32 s3, s5; (6.9*d)+(c/8.1)-(9.7*a)
	
  LDR r0, =y      
  VSTM r0, {s3}
  B STOP

STOP B STOP

a   DCFS 9.8
c   DCFS 8.5
d   DCFS 2.3

n1  DCFS 47.0
n2  DCFS 7.6
n3  DCFS 6.9
n4  DCFS 8.1
n5  DCFS 9.7


ALIGN
	AREA MyData, DATA, ReadWrite
y   DCFS 0.0
	END
