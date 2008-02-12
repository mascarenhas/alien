	.code
	.IMPORT $global$,DATA
	.IMPORT $$dyncall,MILLICODE
; gcc_compiled.:
	.code

	.align 4
	.EXPORT tramp,ENTRY,PRIV_LEV=3,RTNVAL=GR
	.label tramp
	.PROC
	.CALLINFO FRAME=64,CALLS,SAVE_RP
	.ENTRY
	stw %r2,-20(0,%r30)
	ldo 64(%r30),%r30
	ldil L'1934968593,%r19
	ldo R'1934968593(%r19),%r29
	ldil L'-1161904448,%r28
	ldo R'-1161904448(%r28),%r28
	copy %r28,%r22
	.CALL	ARGW0=GR
	bl $$dyncall,%r31
	copy %r31,%r2
	ldw -84(0,%r30),%r2
	bv 0(%r2)
	ldo -64(%r30),%r30
	.EXIT
	.PROCEND
	.align 4
	.EXPORT jump,ENTRY,PRIV_LEV=3,RTNVAL=GR
	.label jump
	.PROC
	.CALLINFO FRAME=0,NO_CALLS
	.ENTRY
	ldil L'-1161904448,%r19
	ldo R'-1161904448(%r19),%r19
	bv,n 0(%r19)
	.EXIT
	.PROCEND
