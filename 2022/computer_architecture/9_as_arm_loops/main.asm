    AREA   MyCode, CODE, ReadOnly
  ENTRY
  EXPORT MyProg
MyProg
	;      6*8, 5 and 1 th columns, 4th row, a < -49, a >= 73
TRANSPOSE
  LDR r2, = 6; rows
  LDR r3, = 8; cols
  LDR r7, = 4; DCD size
  LDR r4, = 0; 0..cols counter - i

OUTER
  LDR r5, = 0; 0..rows counter - j

INNER
  LDR r0, = arr
  LDR r1, = res

  ;   arr[i][j] => arr[4*(i*cols)+j]
  MUL r6, r5, r3
  ADD r6, r4
  MUL r6, r6, r7
  ADD r0, r6

  ;   res[j][i] => res[4*(j*rows)+i]
  MUL r6, r4, r2
  ADD r6, r5
  MUL r6, r6, r7
  ADD r1, r6

  LDR r6, [r0]; mov [r0], [r1]
  STR r6, [r1]

  ADD r5, #1; if r5 < r2 goto INNER
  CMP r5, r2
  BLO INNER

  ADD r4, #1; if r4 < r3 goto OUTER
  CMP r4, r3
  BLO OUTER

SCALAR
  LDR r0, = arr; 1 col
  LDR r1, = arr + 16; 5 col
  LDR r4, = 6; rows
  LDR r5, = 0; 0..rows
  LDR r6, = 0; scalar
  LDR r7, = scalar

LOOP
  LDR r2, [r0]; load el from 1 col
  LDR r3, [r1]; load el from 5 col
  MUL r2, r2, r3
  ADD r6, r2
  ADD r0, #32; 8*4 next cell of 1 col
  ADD r1, #32; 8*4 next cell of 5 col
  ADD r5, #1
  CMP r5, r4
  BLO LOOP
  STR r6, [r7]; answer

  LDR r0, = arr + 96; (8*4)*3 4 row
  LDR r3, = 0; 0..cols
  LDR r4, = 0; sum
  LDR r5, = 0; count
  LDR r6, = sum
  LDR r7, = count

COUNT_AND_SUM
  LDR r1, [r0]
  ADD r0, #4

  CMP r3, #8; >= cols
  BGE DONE

  ADD r3, #1
  CMP r1, #-49
  BLO SUM
  CMP r1, #73
  BGE SUM
  B COUNT_AND_SUM
  
SUM
  ADD r4, r1
  ADD r5, #1
  B   COUNT_AND_SUM

DONE
  STR r4, [r6]
  STR r5, [r7]

STOP B STOP
	ALIGN
	AREA   InputData, Data, ReadOnly
	EXPORT arr
arr    DCD  10, 64, -94, 77, 99, 18, 52, -11
    DCD    -23, -77, -45, 65, 77, 66, -24, 69
    DCD    -81, -78, -82, -39, -90, -78, 24, 95
    DCD    -18, -64, -74, -28, -16, -40, 91, 42
    DCD    56, -19, 86, 34, -83, -99, -31, -51
    DCD    -70, -58, 13, 98, 90, 46, -77, 37; -37 <= a < 69 => 13+46+37 = 96

	AREA   OutputData, Data, ReadWrite
	EXPORT res
	EXPORT scalar
	EXPORT sum
	EXPORT count

res    SPACE 6 * 8 * 4
scalar SPACE 4
sum    SPACE 4
count  SPACE 4
	END
