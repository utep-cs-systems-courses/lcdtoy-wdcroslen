	.arch msp430g2553

	.data

	.extern led_changed



state:

	.word 1

	.text

jt:

	.word case1

	.word default

	.global assembly



assembly:

	cmp #2, &state

	jc default

	mov &state,r12

	add r12,r12

	mov jt(r12),r0



case1:

	call #toggle_red

	mov #1, &state

	jmp out

default:

	call #toggle_green

	mov #0, &state

	jmp out

out:

	mov #1, led_changed

	call #led_update

	pop r0
