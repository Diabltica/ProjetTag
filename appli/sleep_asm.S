.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

@	Equates
	.equ SYSTICK_STCSR,    0xE000E010      @ Systick control register

.text

.global sleep_asm
sleep_asm:
	@no parameters
	LDR R0, =SYSTICK_STCSR	@ Loading Systick control register address
	LDR R1, [R0]						@ Fetching register content
	BIC R1, R1, #1						@ Disabling SYSTICK
	STR R1, [R0]						@ Storing to peripheral register (effective disable)

	WFI						@ Entering SLEEP mode with interrupt wake up

	ORR R1, R1, #1						@ Enabling SYSTICK
	STR R1, [R0]						@ Storing to peripheral register (effective enable)
	BX LR
