.text
	.align 2
	.globl ___builtin_avcall
___builtin_avcall:
	mflr r0
	stmw r30,-8(r1)
	stw r0,8(r1)
	mr r30,r3
	stwu r1,-1104(r1)
	li r3,8
	lwz r9,20(r30)
	addi r10,r1,56
	subf r9,r30,r9
	addi r9,r9,-32
	srawi r9,r9,2
	cmpw cr0,r3,r9
	bge- cr0,L102
	addi r9,r9,-8
	mtctr r9
L106:
	slwi r9,r3,2
	addi r3,r3,1
	add r11,r9,r30
	add r9,r9,r10
	lwz r0,32(r11)
	stw r0,-32(r9)
	bdnz L106
L102:
	lwz r9,1056(r30)
	subf r9,r30,r9
	addi r9,r9,-1060
	srawi. r9,r9,3
	beq- cr0,L8
	cmpwi cr0,r9,1
	beq- cr0,L11
	cmpwi cr0,r9,2
	beq- cr0,L14
	cmpwi cr0,r9,3
	beq- cr0,L17
	cmpwi cr0,r9,4
	beq- cr0,L20
	cmpwi cr0,r9,5
	beq- cr0,L23
	cmpwi cr0,r9,6
	beq- cr0,L26
	cmpwi cr0,r9,7
	beq- cr0,L29
	cmpwi cr0,r9,8
	beq- cr0,L32
	cmpwi cr0,r9,9
	beq- cr0,L35
	cmpwi cr0,r9,10
	beq- cr0,L38
	cmpwi cr0,r9,11
	beq- cr0,L41
	cmpwi cr0,r9,12
	beq- cr0,L44
L47:
	lfd f13,1156(r30)
L44:
	lfd f12,1148(r30)
L41:
	lfd f11,1140(r30)
L38:
	lfd f10,1132(r30)
L35:
	lfd f9,1124(r30)
L32:
	lfd f8,1116(r30)
L29:
	lfd f7,1108(r30)
L26:
	lfd f6,1100(r30)
L23:
	lfd f5,1092(r30)
L20:
	lfd f4,1084(r30)
L17:
	lfd f3,1076(r30)
L14:
	lfd f2,1068(r30)
L11:
	lfd f1,1060(r30)
L8:
	lwz r0,0(r30)
	lwz r9,56(r30)
	lwz r3,32(r30)
	mtctr r0
	lwz r4,36(r30)
	lwz r5,40(r30)
	lwz r6,44(r30)
	lwz r7,48(r30)
	lwz r8,52(r30)
	lwz r10,60(r30)
	bctrl
	lwz r9,12(r30)
	cmpwi cr0,r9,1
	beq- cr0,L49
	cmpwi cr0,r9,0
	beq- cr0,L116
	cmpwi cr0,r9,2
	beq- cr0,L109
	cmpwi cr0,r9,3
	beq- cr0,L109
	cmpwi cr0,r9,4
	beq- cr0,L109
	cmpwi cr0,r9,5
	beq- cr0,L108
	cmpwi cr0,r9,6
	beq- cr0,L108
	cmpwi cr0,r9,7
	beq- cr0,L116
	cmpwi cr0,r9,8
	beq- cr0,L116
	cmpwi cr0,r9,9
	beq- cr0,L116
	cmpwi cr0,r9,10
	beq- cr0,L116
	addi r0,r9,-11
	cmplwi cr0,r0,1
	ble- cr0,L115
	cmpwi cr0,r9,13
	beq- cr0,L117
	cmpwi cr0,r9,14
	beq- cr0,L118
	cmpwi cr0,r9,15
	beq- cr0,L116
	cmpwi cr0,r9,16
	beq- cr0,L119
L49:
	addi r1,r1,1104
	li r3,0
	lwz r0,8(r1)
	lmw r30,-8(r1)
	mtlr r0
	blr
L119:
	lwz r0,4(r30)
	andi. r9,r0,1
	beq- cr0,L79
	lwz r9,16(r30)
	cmpwi cr0,r9,1
	beq- cr0,L120
	cmpwi cr0,r9,2
	beq- cr0,L121
	cmpwi cr0,r9,4
	beq- cr0,L122
	cmpwi cr0,r9,8
	beq- cr0,L123
	addi r0,r9,3
	srwi r11,r0,2
	addic. r11,r11,-1
	blt- cr0,L49
	addi r0,r11,1
	lwz r10,8(r30)
	mtctr r0
L105:
	slwi r9,r11,2
	addi r11,r11,-1
	lwzx r0,r9,r3
	stwx r0,r9,r10
	bdnz L105
	b L49
L123:
	lwz r9,8(r30)
	lwz r0,0(r3)
	stw r0,0(r9)
	lwz r11,4(r3)
	stw r11,4(r9)
	b L49
L122:
	lwz r9,8(r30)
	lwz r0,0(r3)
	stw r0,0(r9)
	b L49
L121:
	lwz r9,8(r30)
	lhz r0,0(r3)
	sth r0,0(r9)
	b L49
L120:
	lwz r9,8(r30)
	lbz r0,0(r3)
	stb r0,0(r9)
	b L49
L79:
	andi. r9,r0,512
	beq- cr0,L49
	lwz r0,16(r30)
	cmpwi cr0,r0,1
	beq- cr0,L109
	cmpwi cr0,r0,2
	beq- cr0,L108
	cmpwi cr0,r0,4
	beq- cr0,L116
	cmpwi cr0,r0,8
	bne+ cr0,L49
L115:
	lwz r9,8(r30)
	stw r4,4(r9)
L107:
	stw r3,0(r9)
	b L49
L116:
	lwz r9,8(r30)
	b L107
L108:
	lwz r9,8(r30)
	sth r3,0(r9)
	b L49
L109:
	lwz r9,8(r30)
	stb r3,0(r9)
	b L49
L118:
	lwz r9,8(r30)
	stfd f1,0(r9)
	b L49
L117:
	lwz r9,8(r30)
	stfs f1,0(r9)
	b L49
