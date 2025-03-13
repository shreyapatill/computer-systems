; partners: nbadam2, mp31
; First we jump to the evaluate function. After reading and echoing the input, we check if the input is an equal sign.
; If it is, we print the result unless the stack contains more than one value. In that case, we print out "Invalid expression."
; Then we check if the input is a space. If it is, we read the next character. If not, we check if the character is valid. 
; If it isn't valid, we print out "Invalid expression." If it is, we check if the input is an operand or operator. If it is 
; an operand, we push. If it is an operator, we pop two values and store them in R3 and R4. Then we determine which operation to
; use and jump to the respective subroutine. Then we push the result back onto the stack and read the next input.
;
.ORIG x3000

	JSR EVALUATE

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;    R1 bit counter
;    R2 destination register
;    R3 value to print in hexadecimal
;    R5 result (binary to convert)
;    R6 counter for loops of extraction

PRINT_HEX
			AND R3, R3, #0
			ADD R3, R3, R5		; add R5 to R3
			AND R6, R6, #0
			ADD R6, R6, #4		; initialize loop counter R6 to 4
	EXTRACT		AND R2, R2, #0		; clear destination register R2
			AND R1, R1, #0		; clear bit counter R1
			ADD R1, R1, #4		; initialize bit counter to 4
	EXTRACT_LOOP	ADD R2, R2, R2		; shift R2 to make space to next bit
			ADD R3, R3, #0		; observe the highest bit R2
			BRzp SHIFT		; if highest bit is 0, skip adding 1 to R2
			ADD R2, R2, #1		; add 1 to R2
			
	SHIFT		ADD R3, R3, R3	 	; left shift R3
			ADD R1, R1, #-1		; decrement bit counter
			BRp EXTRACT_LOOP	; if there's still more bits, go back

			ADD R0, R2, #-9		; compare digit with 9
			BRnz PRINT_NUMERICAL	; if digit is 0-9, go to PRINT_NUMERICAL
			LD R0, A		; otherwise load ASCII of 'A'
			ADD R0, R0, R2		; R0 <- R2 + 'A' - 10
			ADD R0, R0, #-10	; R0 <- R2 + 'A' - 10
			BRnzp DIG_LOOP_DONE	; use OUT TRAP

	PRINT_NUMERICAL LD R0, ZERO		; Load ASCII of '0'
			ADD R0, R0, R2		; R0 <- R2 + '0'

	DIG_LOOP_DONE	OUT			; use OUT
			ADD R6, R6, #-1		; decrement R6
			BRp EXTRACT		; branch to EXTRACT
			HALT			;


TEST		.FILL x5764
ZERO		.FILL #48
A		.FILL #65
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; R0: character input from keyboard
; R1: used to check what input character is
; R2: STACK_START
; R3: STACK_TOP, stores popped value
; R4: stores popped value
; R5: result, check for underflow
; R6: current numerical output
;
;
EVALUATE

READ_INPUT	GETC			; read next input
		OUT			; echo it to the screen
		LD R1, EQUALS
		ADD R1, R1, R0		; checks if input is '='
		BRz CHECK_STACK		; check stack if input is '='

CHECK_SPACE	LD R1, SPACE
		ADD R1, R1, R0		; check if input is ' ' if it is not '='
		BRz READ_INPUT		; reads input if input is space

CHECK_OPERAND	LD R1, ZEROS
		ADD R1, R1, R0		; check if input is > '0'
		BRn CHECK_ADD		; if input is < '0' check if it is operator
		LD R1, NINE
		ADD R1, R1, R0		; check if input is < '9'
		BRp CHECK_ADD		; if input is not [0, 9] check if it is operator
		LD R1, ZEROS
		ADD R0, R1, R0		; convert from ASCII to binary
		JSR PUSH		; push if input is [0, 9]
		JSR READ_INPUT		; read next input after pushing operand

CHECK_ADD	LD R1, ADDITION
		ADD R1, R1, R0		; check if input is '+'
		ST R0, SAVE_OPERATOR
		BRz APPLY_OPERATOR	; branch to apply operator

CHECK_SUB	LD R1, SUBTRACT
		ADD R1, R1, R0		; check if input is '-'
		ST R0, SAVE_OPERATOR
		BRz APPLY_OPERATOR	; branch to apply operator

CHECK_MULT	LD R1, MULTIPLY
		ADD R1, R1, R0		; check if input is '*'
		ST R0, SAVE_OPERATOR
		BRz APPLY_OPERATOR	; branch to apply operator

CHECK_DIV	LD R1, DIVIDE
		ADD R1, R1, R0		; check if input is '/'
		ST R0, SAVE_OPERATOR
		BRz APPLY_OPERATOR	; branch to apply operator

CHECK_EXP	LD R1, EXPONENT
		ADD R1, R1, R0		; check if input is '^'
		ST R0, SAVE_OPERATOR
		BRnp PRINT_INVALID	; if input is not '^' print invalid

APPLY_OPERATOR	JSR POP			; pop one operand
		AND R3, R3, #0
		ADD R3, R3, R0		; store first popped value in R3
		JSR POP			; pop another operand
		AND R4, R4, #0
		ADD R4, R4, R0		; store second popped value in R4
		ADD R5, R5, #0
		BRp PRINT_INVALID	; if there is underflow print invalid expression
		LD R0, SAVE_OPERATOR

APPLY_ADD	LD R1, ADDITION
		ADD R1, R1, R0		; check if input is '+'
		BRnp APPLY_SUB		; if input is not '+' check if it is  '-'
		JSR PLUS		; compute addition
		JSR PUSH		; push sum
		JSR READ_INPUT		; read input after pushing

APPLY_SUB	LD R1, SUBTRACT
		ADD R1, R1, R0		; check if input is '-'
		BRnp APPLY_MULT		; if input is not '-' check if it is  '*'
		JSR MIN			; compute addition
		JSR PUSH		; push product
		JSR READ_INPUT		; read input after pushing

APPLY_MULT	LD R1, MULTIPLY
		ADD R1, R1, R0		; check if input is '*'
		BRnp APPLY_DIV		; if input is not '*' check if it is  '/'
		JSR MUL			; compute addition
		JSR PUSH		; push sum
		JSR READ_INPUT		; read input after pushing

APPLY_DIV	LD R1, DIVIDE
		ADD R1, R1, R0		; check if input is '/'
		BRnp APPLY_EXP		; if input is not '/' check if it is '^'
		JSR DIV			; compute addition
		JSR PUSH		; push sum
		JSR READ_INPUT		; read input after pushing

APPLY_EXP	LD R1, EXPONENT
		ADD R1, R1, R0		; check if input is '^'
		BRnp PRINT_INVALID	; if input is not '^' print invalid
		JSR EXP			; compute addition
		JSR PUSH		; push sum
		JSR READ_INPUT		; read input after pushing

CHECK_STACK	LD R2, STACK_START
		NOT R2, R2
		LD R3, STACK_TOP
		ADD R3, R3, #2
		ADD R2, R3, R2		; checks if stack has 1 value
		BRz LOAD_RESULT		; load result if stack has 1 value

PRINT_INVALID	LEA R0, ERROR
		PUTS			; print invalid expression if stack has more than 1 value
		JSR STOP

LOAD_RESULT	JSR POP			; pop the result
		AND R5, R5, #0
		ADD R5, R5, R0		; add result to R5
		JSR PRINT_HEX		; print result
		JSR STOP		

STOP		HALT			;
		

ERROR		.STRINGZ "Invalid Expression"

EQUALS		.FILL xFFC3	; inverse of '='
SPACE		.FILL xFFE0	; inverse of space
ZEROS		.FILL xFFD0	; inverse of '0'
NINE		.FILL xFFC7	; inverse of '9'

ADDITION	.FILL xFFD5	; inverse of '+'
SUBTRACT	.FILL xFFD3	; inverse of '-'
MULTIPLY	.FILL xFFD6	; inverse of '*'
DIVIDE		.FILL xFFD1	; inverse of '/'
EXPONENT	.FILL xFFA2	; inverse of '^'

SAVE_OPERATOR	.BLKW #1


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
; R3 and R4: operands
; R0: sum
PLUS	
	AND R0, R0, #0
	ADD R0, R3, R4
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
; R3: first operand
; R4: operand being subtracted
; R0: difference
MIN	
	AND R0, R0, #0
	NOT R3, R3
	ADD R3, R3, #1
	ADD R0, R3, R4
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
; R3: operand being added
; R4: counter
; R0: product
MUL		AND R0, R0, #0
		ADD R4, R4, #0
		BRn MUL_LOOP2
MUL_LOOP	ADD R0, R0, R3
		ADD R4, R4, #-1
		BRp MUL_LOOP
		RET
MUL_LOOP2	ADD R0, R0, R3
		ADD R4, R4, #1
		BRn MUL_LOOP2
		BRnzp NEGATE
		RET
NEGATE		NOT R0, R0
		ADD R0, R0, #1
		RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
; R3: first operand
; R4: operand being subtracted
; R0: counter (quotient)
DIV	
		AND R0, R0, #0
		NOT R3, R3
		ADD R3, R3, #1
DIV_LOOP	ADD R0, R0, #1
		ADD R4, R4, R3
		BRzp DIV_LOOP	
		ADD R0, R0, #-1
		RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
; R1: base (counter)
; R3: exponent
; R4: base
; R0: result
EXP
		AND R1, R1, #0
		AND R0, R0, #0
		ADD R3, R3, #-1
EXP_LOOP	ADD R1, R4, #0
MULT_LOOP	ADD R0, R0, R4
		ADD R1, R1, #-1
		BRp MULT_LOOP
		ADD R3, R3, #-1
		BRp EXP_LOOP
		RET

	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
