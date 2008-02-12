@ Trampoline for arm CPU

@ Copyright 1995-1997 Bruno Haible, <bruno@clisp.org>
@
@ This is free software distributed under the GNU General Public Licence
@ described in the file COPYING. Contact the author if you don't have this
@ or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
@ on this software.

@ Available registers: ip.

rfp	.req	r9
sl	.req	r10
fp	.req	r11
ip	.req	r12
sp	.req	r13
lr	.req	r14
pc	.req	r15
.text
	.align	0
	.global	_tramp
_tramp:
	@ Immediate constants are a problem. I take the indirect load approach
	@ because I don't want 4 instructions for each constant.
	ldr	ip,[pc,#_function-.-8]
	ldr	ip,[ip,#0]
	stmfd	sp!,{ip}
	ldr	ip,[pc,#_data-.-8]
	ldr	ip,[ip,#0]
	ldmfd	sp!,{pc}^

	.global	_data
	.align	0
_data:
	.word	0x73554711

	.global	_function
	.align	0
_function:
	.word	0xbabebec0
