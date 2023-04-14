.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

@       Equates
        .equ RCC_APB2ENR,       0x40021018      @ enable clock register
        .equ GPIOA_CRL,         0x40010800      @ port A Configuration Register Low
        .equ GPIOA_ODR,         0x4001080C      @ port A output data register

        .equ LEDDELAY,          800000

.text

@ Change function name from main (e.g. blinky_main) if another int main(void) is declared elsewhere
.global main
main:

@ next enable clock on GPIO port A
        ldr r6, =RCC_APB2ENR
        ldr r5, [r6]
        orr r5, 0x4
        str r5, [r6]
@ now set port A pin 5 to output with max speed of 2MHz and type = push-pull
        ldr r6, =GPIOA_CRL
        ldr r5, [r6]
        and r5, 0xff2fffff          @ clear bits 23 22 20
        orr r5, 0x00200000          @ set bit 21
        str r5, [r6]

@ start blinking
        ldr r6, =GPIOA_ODR			@load ODR register address in R6
loop:
        ldr r5, [r6]
        orr r5, 0x00000020          @set bit 5: LED green on
        str r5, [r6]
        ldr r1, =LEDDELAY
delay1:
        subs r1, 1
        bne delay1
@ turn off led
        ldr r5, [r6]
        and r5, 0xffffffdf          @clear bit 5: LED green off
        str r5, [r6]
        ldr r1, =LEDDELAY
delay2:
        subs r1, 1
        bne delay2

        b loop

