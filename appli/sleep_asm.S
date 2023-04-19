.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

@	Equates
			...      @ Systick control register

.text

.global sleep_asm
sleep_asm:
	@no parameters
	LDR R0, =SYSTICK_STCSR	@ Loading Systick control register address
	...						@ Fetching register content
	...						@ Disabling SYSTICK
	...						@ Storing to peripheral register (effective disable)

	...						@ Entering SLEEP mode with interrupt wake up

	...						@ Enabling SYSTICK
	...						@ Storing to peripheral register (effective enable)
	BX LR
