;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer

			.define R4, i
;			.define R5, j
			.define R6, ADDR
			.define R7, PARALLEL			; parallel byte
			.define R8, P3DAT				; data to be moved to p3
SER_DAT		.equ BIT1 + BIT0				; SCLK, SOUT init values
SCLK   		.equ BIT1						; Mask to CLK bit in P3OUT (P3.1)
BUFFER		.equ 0x2400						; start address of buffer
LEN			.equ 10							; buffer length in bytes
;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
MAIN_LOOP:
; ------------------------ Initialize Variables --------------------------------
			mov #SER_DAT, &P3DIR				; initlaize P3DIR

			mov #LEN, i						; init loop (fetch bytes)
			mov #BUFFER, ADDR				; init loop (fetch bytes)

			bis.b #SCLK, &P3OUT				; set SCLK to idle state
; -------------------------------- PISO ----------------------------------------
DO
			mov.b @ADDR+, PARALLEL		; fetch byte
			rlc.b PARALLEL

SERIAL_BIT8
			mov.b R2, P3DAT					; 1 MCLK, move Carry to P3DAT

			bic.b #SCLK, P3DAT				; 1 MCLK, SCLK: HIGH->LOW
			mov.b P3DAT, &P3OUT				; 3 MCLK, set P3OUT to P3DAT

			rlc.b PARALLEL					; 1 MCLK

			bis.b #SCLK, &P3OUT				; 4 MCLK, SCLK: LOW->HIGH
SERIAL_BIT7
			mov.b R2, P3DAT

			bic.b #SCLK, P3DAT
			mov.b P3DAT, &P3OUT

			rlc.b PARALLEL

			bis.b #SCLK, &P3OUT
SERIAL_BIT6
			mov.b R2, P3DAT

			bic.b #SCLK, P3DAT
			mov.b P3DAT, &P3OUT

			rlc.b PARALLEL

			bis.b #SCLK, &P3OUT
SERIAL_BIT5
			mov.b R2, P3DAT

			bic.b #SCLK, P3DAT
			mov.b P3DAT, &P3OUT

			rlc.b PARALLEL

			bis.b #SCLK, &P3OUT
SERIAL_BIT4
			mov.b R2, P3DAT

			bic.b #SCLK, P3DAT
			mov.b P3DAT, &P3OUT

			rlc.b PARALLEL

			bis.b #SCLK, &P3OUT
SERIAL_BIT3
			mov.b R2, P3DAT

			bic.b #SCLK, P3DAT
			mov.b P3DAT, &P3OUT

			rlc.b PARALLEL

			bis.b #SCLK, &P3OUT
SERIAL_BIT2
			mov.b R2, P3DAT

			bic.b #SCLK, P3DAT
			mov.b P3DAT, &P3OUT

			rlc.b PARALLEL

			bis.b #SCLK, &P3OUT
SERIAL_BIT1
			mov.b R2, P3DAT

			bic.b #SCLK, P3DAT
			mov.b P3DAT, &P3OUT

			rlc.b PARALLEL

			bis.b #SCLK, &P3OUT
SERIAL_BIT0
			mov.b R2, P3DAT

			bic.b #SCLK, P3DAT
			mov.b P3DAT, &P3OUT

			rlc.b PARALLEL

			bis.b #SCLK, &P3OUT

			dec i
WHILE		jnz DO
;-------------------------------------------------------------------------------
DONE		jmp MAIN_LOOP					; jump back to main loop
			NOP

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
