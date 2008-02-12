.text
	.align 2
	.globl ___vacall
___vacall:
	mflr r0
	stmw r29,-12(r1)
	bcl 20,31,L1$pb
L1$pb:
	stw r0,8(r1)
	mflr r31
	stwu r1,-224(r1)
	addis r29,r31,ha16(L_vacall_function$non_lazy_ptr-L1$pb)
	li r11,0
	lwz r29,lo16(L_vacall_function$non_lazy_ptr-L1$pb)(r29)
	addi r0,r1,248
	stw r0,68(r1)
	addi r0,r1,100
	lwz r29,0(r29)
	stw r3,248(r1)
	addi r3,r1,64
	stw r9,272(r1)
	mtctr r29
	stw r5,256(r1)
	stw r6,260(r1)
	stw r7,264(r1)
	stw r8,268(r1)
	stw r10,276(r1)
	stw r11,76(r1)
	stw r0,96(r1)
	stw r4,252(r1)
	stfd f1,100(r1)
	stfd f2,108(r1)
	stfd f3,116(r1)
	stfd f4,124(r1)
	stfd f5,132(r1)
	stfd f6,140(r1)
	stfd f7,148(r1)
	stfd f8,156(r1)
	stfd f9,164(r1)
	stfd f10,172(r1)
	stfd f11,180(r1)
	stfd f12,188(r1)
	stfd f13,196(r1)
	stw r11,64(r1)
	stw r11,72(r1)
	bctrl
	lwz r9,76(r1)
	cmpwi cr0,r9,0
	beq- cr0,L1
	cmpwi cr0,r9,1
	beq- cr0,L43
	cmpwi cr0,r9,2
	beq- cr0,L43
	cmpwi cr0,r9,3
	beq- cr0,L44
	cmpwi cr0,r9,4
	beq- cr0,L45
	cmpwi cr0,r9,5
	beq- cr0,L46
	cmpwi cr0,r9,6
	beq- cr0,L42
	cmpwi cr0,r9,7
	beq- cr0,L42
	cmpwi cr0,r9,8
	beq- cr0,L42
	cmpwi cr0,r9,9
	beq- cr0,L42
	addi r0,r9,-10
	cmplwi cr0,r0,1
	bgt- cr0,L22
	lwz r3,88(r1)
	lwz r4,92(r1)
L1:
	addi r1,r1,224
	lwz r0,8(r1)
	lmw r29,-12(r1)
	mtlr r0
	blr
L22:
	cmpwi cr0,r9,12
	beq- cr0,L47
	cmpwi cr0,r9,13
	beq- cr0,L48
	cmpwi cr0,r9,14
	beq- cr0,L42
	cmpwi cr0,r9,15
	bne+ cr0,L1
	lwz r0,64(r1)
	andi. r9,r0,1
	beq- cr0,L31
	lwz r3,72(r1)
	b L1
L31:
	andi. r9,r0,1024
	beq- cr0,L1
	lwz r0,80(r1)
	cmpwi cr0,r0,1
	beq- cr0,L49
	cmpwi cr0,r0,2
	beq- cr0,L50
	cmpwi cr0,r0,4
	beq- cr0,L51
	cmpwi cr0,r0,8
	bne+ cr0,L1
	lwz r9,72(r1)
	lwz r4,4(r9)
L41:
	lwz r3,0(r9)
	b L1
L51:
	lwz r9,72(r1)
	b L41
L50:
	lwz r9,72(r1)
	lhz r3,0(r9)
	b L1
L49:
	lwz r9,72(r1)
	lbz r3,0(r9)
	b L1
L42:
	lwz r3,88(r1)
	b L1
L48:
	lfd f1,88(r1)
	b L1
L47:
	lfs f1,88(r1)
	b L1
L46:
	lhz r3,88(r1)
	b L1
L45:
	lha r3,88(r1)
	b L1
L44:
	lbz r3,88(r1)
	b L1
L43:
	lbz r0,88(r1)
	extsb r3,r0
	b L1
.data
.non_lazy_symbol_pointer
L_vacall_function$non_lazy_ptr:
	.indirect_symbol _vacall_function
	.long	0
