; partners: nbadam2, mp31
; We start by calculating the ASCII value to print out using the line counter. 
; After printing the character, we print out a space. Then we print out the hex
; representation of the count of each character (histogram data). We use the code
; developed in lab to convert each 4 bits into hex, and then we calculate
; the ASCII value to print. After repeating this 4 times, we print out a new line
; and repeat the whole process line by line, until we reach the 27th line. 

; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments
; table of register use for printing
;    R0 ascii character being printed
;    R1 bit counter
;    R2 destination register
;    R3 contains the full binary number (count for histogram)
;    R4 histogram pointer
;    R5 counter for loops of extraction
;    R6 line counter

			LD  R4, HIST_ADDR	; load histogram address into R4
			AND R6, R6, #0		; initialize R6 to 0
	PRINTCHAR	LDR R3, R4, #0		; load contents at address stored in R4 into R3
			AND R5, R5, #0		; clear R5
			ADD R5, R5, #4		; initialize R5 to 4
			ADD R0, R6, #15		; R0 <- R6 + 15
			ADD R0, R0, #15		; add 30 to R6
			ADD R0, R0, #15		; add 45 to R6
			ADD R0, R0, #15		; add 60 to R6
			ADD R0, R0, #4		; add 64 to R6
			OUT			; print current character out	
			LD R0, SPACE		; load ASCII value for space into R0
			OUT			; print current character out
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
			ADD R5, R5, #-1		; decrement R5
			BRp EXTRACT		; branch to EXTRACT
			ADD R4, R4, #1		; decrement R5
			LD R0, NEW_LINE		; newline
			OUT			;
			ADD R6, R6, #-16	; compare R6 (increment)
			ADD R6, R6, #-10
			BRzp DONE
			ADD R6, R6, #15
			ADD R6, R6, #12
			BRnzp PRINTCHAR



DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
ZERO		.FILL #48
A		.FILL #65
SPACE		.FILL x0020
NEW_LINE	.FILL x000A

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
