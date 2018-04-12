;--------------------------------------------------------
; File Created by SDCC : FreeWare ANSI-C Compiler
; Version 2.3.3 Mon Mar 19 17:31:35 2007

;--------------------------------------------------------
	.module main
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _init
	.globl _putchar
	.globl _getchar
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
_P0	=	0x0080
_SP	=	0x0081
_DPL	=	0x0082
_DPH	=	0x0083
_PCON	=	0x0087
_TCON	=	0x0088
_TMOD	=	0x0089
_TL0	=	0x008a
_TL1	=	0x008b
_TH0	=	0x008c
_TH1	=	0x008d
_P1	=	0x0090
_SCON	=	0x0098
_SBUF	=	0x0099
_P2	=	0x00a0
_IE	=	0x00a8
_P3	=	0x00b0
_IP	=	0x00b8
_PSW	=	0x00d0
_ACC	=	0x00e0
_B	=	0x00f0
;--------------------------------------------------------
; special function bits 
;--------------------------------------------------------
_P0_0	=	0x0080
_P0_1	=	0x0081
_P0_2	=	0x0082
_P0_3	=	0x0083
_P0_4	=	0x0084
_P0_5	=	0x0085
_P0_6	=	0x0086
_P0_7	=	0x0087
_IT0	=	0x0088
_IE0	=	0x0089
_IT1	=	0x008a
_IE1	=	0x008b
_TR0	=	0x008c
_TF0	=	0x008d
_TR1	=	0x008e
_TF1	=	0x008f
_P1_0	=	0x0090
_P1_1	=	0x0091
_P1_2	=	0x0092
_P1_3	=	0x0093
_P1_4	=	0x0094
_P1_5	=	0x0095
_P1_6	=	0x0096
_P1_7	=	0x0097
_RI	=	0x0098
_TI	=	0x0099
_RB8	=	0x009a
_TB8	=	0x009b
_REN	=	0x009c
_SM2	=	0x009d
_SM1	=	0x009e
_SM0	=	0x009f
_P2_0	=	0x00a0
_P2_1	=	0x00a1
_P2_2	=	0x00a2
_P2_3	=	0x00a3
_P2_4	=	0x00a4
_P2_5	=	0x00a5
_P2_6	=	0x00a6
_P2_7	=	0x00a7
_EX0	=	0x00a8
_ET0	=	0x00a9
_EX1	=	0x00aa
_ET1	=	0x00ab
_ES	=	0x00ac
_EA	=	0x00af
_P3_0	=	0x00b0
_P3_1	=	0x00b1
_P3_2	=	0x00b2
_P3_3	=	0x00b3
_P3_4	=	0x00b4
_P3_5	=	0x00b5
_P3_6	=	0x00b6
_P3_7	=	0x00b7
_RXD	=	0x00b0
_TXD	=	0x00b1
_INT0	=	0x00b2
_INT1	=	0x00b3
_T0	=	0x00b4
_T1	=	0x00b5
_WR	=	0x00b6
_RD	=	0x00b7
_PX0	=	0x00b8
_PT0	=	0x00b9
_PX1	=	0x00ba
_PT1	=	0x00bb
_PS	=	0x00bc
_P	=	0x00d0
_F1	=	0x00d1
_OV	=	0x00d2
_RS0	=	0x00d3
_RS1	=	0x00d4
_F0	=	0x00d5
_AC	=	0x00d6
_CY	=	0x00d7
;--------------------------------------------------------
; overlayable register banks 
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area	OSEG    (OVR,DATA)
	.area	OSEG    (OVR,DATA)
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG	(DATA)
__start__stack:
	.ds	1

;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
_main_flaga_1_1::
	.ds 1
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area CSEG    (CODE)
__interrupt_vect:
	ljmp	__sdcc_gsinit_startup
	reti
	.ds	7
	reti
	.ds	7
	reti
	.ds	7
	reti
	.ds	7
	reti
	.ds	7
	reti
	.ds	7
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
__sdcc_gsinit_startup:
	mov	sp,#__start__stack - 1
	lcall	__sdcc_external_startup
	mov	a,dpl
	jz	__sdcc_init_data
	ljmp	__sdcc_program_startup
__sdcc_init_data:
;	_mcs51_genXINIT() start
	mov	a,#l_XINIT
	orl	a,#l_XINIT>>8
	jz	00003$
	mov	a,#s_XINIT
	add	a,#l_XINIT
	mov	r1,a
	mov	a,#s_XINIT>>8
	addc	a,#l_XINIT>>8
	mov	r2,a
	mov	dptr,#s_XINIT
	mov	r0,#s_XISEG
	mov	p2,#(s_XISEG >> 8)
00001$:	clr	a
	movc	a,@a+dptr
	movx	@r0,a
	inc	dptr
	inc	r0
	cjne	r0,#0,00002$
	inc	p2
00002$:	mov	a,dpl
	cjne	a,ar1,00001$
	mov	a,dph
	cjne	a,ar2,00001$
	mov	p2,#0xFF
00003$:
;	_mcs51_genXINIT() end
	.area GSFINAL (CODE)
	ljmp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
__sdcc_program_startup:
	lcall	_main
;	return from main will lock up
	sjmp .
;------------------------------------------------------------
;Allocation info for local variables in function 'getchar'
;------------------------------------------------------------
;------------------------------------------------------------
;main.c:3: char getchar(void)
;	-----------------------------------------
;	 function getchar
;	-----------------------------------------
_getchar:
	ar2 = 0x02
	ar3 = 0x03
	ar4 = 0x04
	ar5 = 0x05
	ar6 = 0x06
	ar7 = 0x07
	ar0 = 0x00
	ar1 = 0x01
;main.c:6: while (RI==0);
00101$:
;     genNot
	mov	c,_RI
	cpl	c
	clr	a
	rlc	a
;     genIfx
;       Peephole 105   removed redundant mov
	mov  r2,a
;     genIfxJump
;       Peephole 109   removed ljmp by inverse jump logic
	jnz  00101$
00108$:
;main.c:7: RI=0;
;     genAssign
	clr	_RI
;main.c:8: znak=SBUF;
;     genAssign
	mov	dpl,_SBUF
;main.c:9: return znak;
;     genRet
00104$:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'putchar'
;------------------------------------------------------------
;------------------------------------------------------------
;main.c:12: void putchar(char znak)
;	-----------------------------------------
;	 function putchar
;	-----------------------------------------
_putchar:
;     genReceive
	mov	_SBUF,dpl
;main.c:15: while(TI==0);
00101$:
;     genNot
	mov	c,_TI
	cpl	c
	clr	a
	rlc	a
;     genIfx
;       Peephole 105   removed redundant mov
	mov  r2,a
;     genIfxJump
;       Peephole 109   removed ljmp by inverse jump logic
	jnz  00101$
00108$:
;main.c:16: TI=0;
;     genAssign
	clr	_TI
00104$:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'init'
;------------------------------------------------------------
;------------------------------------------------------------
;main.c:19: void init()
;	-----------------------------------------
;	 function init
;	-----------------------------------------
_init:
;main.c:21: TH0=0xfd;
;     genAssign
	mov	_TH0,#0xFD
;main.c:22: SCON=0x50;
;     genAssign
	mov	_SCON,#0x50
;main.c:23: TMOD=0x20;
;     genAssign
	mov	_TMOD,#0x20
;main.c:24: PCON=0x80;
;     genAssign
	mov	_PCON,#0x80
;main.c:25: TCON=0x40;
;     genAssign
	mov	_TCON,#0x40
00101$:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;znak                      Allocated to registers r3 
;ile                       Allocated to registers 
;------------------------------------------------------------
;main.c:28: void main (void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;main.c:32: bit flaga=0;
;     genAssign
	clr	_main_flaga_1_1
;main.c:33: init();
;     genCall
	lcall	_init
;     genAssign
	mov	r2,#0x30
00110$:
;main.c:36: znak=getchar();
;     genCall
	push	ar2
	lcall	_getchar
	mov	a,dpl
	pop	ar2
;     genAssign
;main.c:38: if(znak < 65 || (znak > 90 && znak <97) || znak >122)
;     genCmpLt
;     genCmp
;       Peephole 106   removed redundant mov 
	mov  r3,a
	clr  c
	xrl	a,#0x80
	subb	a,#0xc1
;     genIfxJump
;       Peephole 132   changed ljmp to sjmp
;       Peephole 160   removed sjmp by inverse jump logic
	jc   00103$
00118$:
;     genCmpGt
;     genCmp
	clr	c
;       Peephole 159   avoided xrl during execution
	mov  a,#(0x5A ^ 0x80)
	mov	b,r3
	xrl	b,#0x80
	subb	a,b
;     genIfxJump
;       Peephole 108   removed ljmp by inverse jump logic
	jnc  00108$
00119$:
;     genCmpLt
;     genCmp
	clr	c
	mov	a,r3
	xrl	a,#0x80
	subb	a,#0xe1
;     genIfxJump
;       Peephole 132   changed ljmp to sjmp
;       Peephole 160   removed sjmp by inverse jump logic
	jc   00103$
00120$:
00108$:
;     genCmpGt
;     genCmp
	clr	c
;       Peephole 159   avoided xrl during execution
	mov  a,#(0x7A ^ 0x80)
	mov	b,r3
	xrl	b,#0x80
	subb	a,b
;     genIfxJump
;       Peephole 108   removed ljmp by inverse jump logic
	jnc  00104$
00121$:
00103$:
;     genIfx
;     genIfxJump
;       Peephole 111   removed ljmp by inverse jump logic
	jnb  _main_flaga_1_1,00110$
00122$:
;main.c:42: putchar(44);
;     genCall
	mov	dpl,#0x2C
	push	ar2
	lcall	_putchar
	pop	ar2
;main.c:43: ile++;
;     genPlus
;     genPlusIncr
	inc	r2
;main.c:44: putchar(ile);            		
;     genCall
	mov	dpl,r2
	push	ar2
	lcall	_putchar
	pop	ar2
;main.c:45: flaga=0;
;     genAssign
	clr	_main_flaga_1_1
;       Peephole 132   changed ljmp to sjmp
	sjmp 00110$
00104$:
;main.c:48: else flaga=1;
;     genAssign
	setb	_main_flaga_1_1
	ljmp	00110$
00112$:
	ret
	.area CSEG    (CODE)
	.area XINIT   (CODE)
