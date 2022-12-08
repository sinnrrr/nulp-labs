	; vim: ft=masm

	INCLUDE D:\Irvine\Irvine16.inc

	; Константи відеорежимів
	Mode_03 = 03h     ; Текстовий режим 80x25, 16 кольорів, 8 сторінок
	Mode_06 = 06h     ; 640 х 200, 2 кольори
	Mode_0D = 0Dh     ; 320 х 200, 16 кольорів
	Mode_0E = 0Eh     ; 640 х 200, 16 кольорів
	Mode_0F = 0Fh     ; 640 х 350, 2 кольори
	Mode_10 = 10h     ; 640 х 350, 16 кольорів
	Mode_11 = 11h     ; 640 х 480, 2 кольори
	Mode_12 = 12h     ; 640 х 480, 16 кольорів
	Mode_13 = 13h     ; 320 х 200, 256 кольорів
	Mode_6A = 6Ah     ; 800 х 600, 16 кольорів

	.data
	saveMode BYTE ?; Збережений поточний відеорежим

	mySurname    BYTE 'S', 1Ch, 'o', 5Dh, 'l', 1Fh, 't', 5Ah, 'y', 1Ah, 's', 4Ah, 'i', 7Ch, 'u', 3Fh, 'k', 3Ch
	myName       BYTE 'D', 0Eh, 'm', 4Bh, 'y', 3Ah, 't', 3Dh, 'r', 7Eh, 'o', 1Fh
	myMiddleName BYTE 'A', 3Bh, 'n', 6Eh, 'd', 5Ah, 'r', 6Eh, 'i', 3Ch, 'i', 6Dh, 'o', 2Bh, 'v', 7Eh, 'y', 3Ah, 'c', 2Ah, 'h', 7Dh

	;      variant = 22
	row    WORD  2; variant % 10
	column WORD  44; variant + group number

	xVal            WORD  ?; Координата X
	yVal            WORD  ?; Координата Y
	rectangleWidth  WORD  132; 3 * (group number + variant) = 3 * (22 + 22) =  3 * 44 = 132
	rectangleHeight WORD  74; 2 * (group number + variant) = 2 * (22 + 22) =  2 * 44 = 88

	.code
	main PROC
	mov  ax, @data
	mov  ds, ax

	;   Збережемо номер поточного відеорежиму
	mov ah, 0Fh; tells "int 10h" to return current video mode
	int 10h
	mov saveMode, al

	;   Встановлення текстового режиму (Очищення екрану)
	mov ax, Mode_03
	int 10h

	;   Обрання першої сторінки
	mov ah, 05h
	mov al, 1
	int 10h

	;   Запис тексту в першу сторінку текстової пам'яті
	mov ax, 0B900h; адреса першої сторінки
	mov es, ax

	;   Виведення прізвища
	mov cx, SIZEOF mySurname
	mov si, OFFSET mySurname
	xor di, di; di = 0, but faster

	mov  bx, row
	imul bx, 2
	imul bx, 80
	add  di, bx
	mov  bx, column
	imul bx, 2
	add  di, bx

	call WRITE_TO_FIRST_PAGE_OF_TEXTMEMORY

	;   Виведення імені
	mov cx, SIZEOF myName
	mov si, OFFSET myName
	xor di, di

	mov  bx, row
	add  bx, 2
	imul bx, 2
	imul bx, 80
	add  di, bx
	mov  bx, column
	add  bx, 3
	imul bx, 2
	add  di, bx

	call WRITE_TO_FIRST_PAGE_OF_TEXTMEMORY

	;   Виведення по-батькові
	mov cx, SIZEOF myMiddleName
	mov si, OFFSET myMiddleName
	xor di, di

	mov  bx, row
	add  bx, 6
	imul bx, 2
	imul bx, 80
	add  di, bx
	mov  bx, column
	add  bx, 8
	imul bx, 2
	add  di, bx

	call WRITE_TO_FIRST_PAGE_OF_TEXTMEMORY

	;   Чекаємо натиснення будь-якої клавіші
	mov ah, 10h
	int 16h

	;    Побудова прямокутника
	;    Перемкнемося в графічний режим
	mov  ah, 00h; Функція встановлення відеорежиму
	mov  al, Mode_13
	int  10h
	;    int 10h
	push 0A000h; Сегментна адреса відеобуфера
	pop  es; ES = A000h (відеосегмент)

	call DRAW_RECTANGLE

	;   Чекаємо натиснення будь-якої клавіші
	mov ah, 10h
	int 16h

	;   Відновимо попередній відеорежим
	mov ah, 0; Функція встановлення відеорежиму
	mov al, saveMode; Номер збереженого відеорежиму
	int 10h
	exit

	main ENDP

	WRITE_TO_FIRST_PAGE_OF_TEXTMEMORY PROC

LOOP_FIRST_PAGE_OF_TEXTMEMORY:
	lodsb ; завантажує si до al
	mov   es:[di], al
	inc   di
	loop  LOOP_FIRST_PAGE_OF_TEXTMEMORY
	ret
	WRITE_TO_FIRST_PAGE_OF_TEXTMEMORY ENDP

	DRAW_RECTANGLE PROC
	;    Встановлює колір окремого елемента палітри кольорів і
	;    креслить на екрані кілька пікселів
	;    Змінимо колір елемента палітри, що визначається індексом 1
	mov  dx, 3c8h; Порт індексу палітри кольорів (3C8h)
	mov  al, 1; Встановимо індекс 1
	out  dx, al
	mov  dx, 3c9h; Значення кольорів виводяться у порт 3C9h
	mov  al, 1; Зелений колір
	out  dx, al
	;    Обчислимо зміщення першого пікселя у відеобуфері.
	;    Воно характерне для поточного відеорежиму 13h, роздільна здатність якого
	;    складає 320х200.
	mov  xVal, (SIZEOF myMiddleName)/2
	mov  yVal, (SIZEOF mySurname)/2
	mov  ax, 320; Кількість пікселів у рядку
	mov  bx, 0
	mul  yVal; множимо на координату Y
	add  ax, xVAl; і додаємо координату X.
	;    Помістимо значення індексу кольору у відеопам'ять.
	mov  cx, rectangleWidth
	imul cx, rectangleHeight
	mov  di, ax; в АХ – зміщення відеобуфера
	;    Рисуємо пряму завдовжки 10 пікселів.

DPI:
	mov  BYTE PTR es:[di], 1; Записуємо індекс кольору
	;    В регістрі ES зберігається сегментна адреса відеобуфера.
	add  di, 1
	add  bx, 1
	.IF  bx == rectangleWidth
	mov  bx, 0
	add  di, 320
	sub  di, rectangleWidth
	.ENDIF
	Loop DPI
	ret
	DRAW_RECTANGLE ENDP

	END main
