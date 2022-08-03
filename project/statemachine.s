	.arch msp430g2553
	.p2align 1,0
	.text
	.global led_state_update

led_state_update:
	mov.b &switch_btn, r12
	cmp.w #2,  r12 { jeq .STATE2 ; Jump to state 2
	mov.b #2,  r13
	cmp.w r12, r13 { jl  .L2 ; Jump to check for state 3 and 4
	cmp.w #1,  r12 { jeq .STATE1 ; Jump to state 1

.L2:
	cmp.w #4, r12 { jeq .STATE3 ; Jump to state 3
	cmp.w #8, r12 { jeq .STATE4 ; Jump to state 4
	br    #.L7

.STATE1:		;SW1
	mov.b #1, &led_changed
	mov.b #0, &green_on
	mov.b #1, &red_on
	call  #buzzer_advance_frequency
	br    #.L7

.STATE2:		;SW2
	mov.b #1, &led_changed
	mov.b #1, &red_on
	mov.b #0, &green_on
	call  #led_dim_state_update
	call  #buzzer_advance_frequency
	br    #.L7
.STATE3:		;SW3
	mov.b #1, &led_changed
	mov.b #1, &green_on
	mov.b #0, &red_on
	call  #buzzer_advance_frequency
	br    #.L7

.STATE4: 		;SW4
	mov.b #1, &led_changed
	mov.b #0, &red_on
	mov.b #1, &green_on
	call  #led_dim_state_update
	call  #buzzer_advance_frequency
	br    #.L7

.L7:
	mov.b #0, &switch_state_down
	mov.b #0, switch_state_up
	call #led_update
	nop
	ret
	.size led_state_update, .-led_state_update

