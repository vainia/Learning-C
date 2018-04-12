                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.3.3 Mon Mar 19 17:31:35 2007
                              4 
                              5 ;--------------------------------------------------------
                              6 	.module main
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _main
                             12 	.globl _init
                             13 	.globl _putchar
                             14 	.globl _getchar
                             15 ;--------------------------------------------------------
                             16 ; special function registers
                             17 ;--------------------------------------------------------
                    0080     18 _P0	=	0x0080
                    0081     19 _SP	=	0x0081
                    0082     20 _DPL	=	0x0082
                    0083     21 _DPH	=	0x0083
                    0087     22 _PCON	=	0x0087
                    0088     23 _TCON	=	0x0088
                    0089     24 _TMOD	=	0x0089
                    008A     25 _TL0	=	0x008a
                    008B     26 _TL1	=	0x008b
                    008C     27 _TH0	=	0x008c
                    008D     28 _TH1	=	0x008d
                    0090     29 _P1	=	0x0090
                    0098     30 _SCON	=	0x0098
                    0099     31 _SBUF	=	0x0099
                    00A0     32 _P2	=	0x00a0
                    00A8     33 _IE	=	0x00a8
                    00B0     34 _P3	=	0x00b0
                    00B8     35 _IP	=	0x00b8
                    00D0     36 _PSW	=	0x00d0
                    00E0     37 _ACC	=	0x00e0
                    00F0     38 _B	=	0x00f0
                             39 ;--------------------------------------------------------
                             40 ; special function bits 
                             41 ;--------------------------------------------------------
                    0080     42 _P0_0	=	0x0080
                    0081     43 _P0_1	=	0x0081
                    0082     44 _P0_2	=	0x0082
                    0083     45 _P0_3	=	0x0083
                    0084     46 _P0_4	=	0x0084
                    0085     47 _P0_5	=	0x0085
                    0086     48 _P0_6	=	0x0086
                    0087     49 _P0_7	=	0x0087
                    0088     50 _IT0	=	0x0088
                    0089     51 _IE0	=	0x0089
                    008A     52 _IT1	=	0x008a
                    008B     53 _IE1	=	0x008b
                    008C     54 _TR0	=	0x008c
                    008D     55 _TF0	=	0x008d
                    008E     56 _TR1	=	0x008e
                    008F     57 _TF1	=	0x008f
                    0090     58 _P1_0	=	0x0090
                    0091     59 _P1_1	=	0x0091
                    0092     60 _P1_2	=	0x0092
                    0093     61 _P1_3	=	0x0093
                    0094     62 _P1_4	=	0x0094
                    0095     63 _P1_5	=	0x0095
                    0096     64 _P1_6	=	0x0096
                    0097     65 _P1_7	=	0x0097
                    0098     66 _RI	=	0x0098
                    0099     67 _TI	=	0x0099
                    009A     68 _RB8	=	0x009a
                    009B     69 _TB8	=	0x009b
                    009C     70 _REN	=	0x009c
                    009D     71 _SM2	=	0x009d
                    009E     72 _SM1	=	0x009e
                    009F     73 _SM0	=	0x009f
                    00A0     74 _P2_0	=	0x00a0
                    00A1     75 _P2_1	=	0x00a1
                    00A2     76 _P2_2	=	0x00a2
                    00A3     77 _P2_3	=	0x00a3
                    00A4     78 _P2_4	=	0x00a4
                    00A5     79 _P2_5	=	0x00a5
                    00A6     80 _P2_6	=	0x00a6
                    00A7     81 _P2_7	=	0x00a7
                    00A8     82 _EX0	=	0x00a8
                    00A9     83 _ET0	=	0x00a9
                    00AA     84 _EX1	=	0x00aa
                    00AB     85 _ET1	=	0x00ab
                    00AC     86 _ES	=	0x00ac
                    00AF     87 _EA	=	0x00af
                    00B0     88 _P3_0	=	0x00b0
                    00B1     89 _P3_1	=	0x00b1
                    00B2     90 _P3_2	=	0x00b2
                    00B3     91 _P3_3	=	0x00b3
                    00B4     92 _P3_4	=	0x00b4
                    00B5     93 _P3_5	=	0x00b5
                    00B6     94 _P3_6	=	0x00b6
                    00B7     95 _P3_7	=	0x00b7
                    00B0     96 _RXD	=	0x00b0
                    00B1     97 _TXD	=	0x00b1
                    00B2     98 _INT0	=	0x00b2
                    00B3     99 _INT1	=	0x00b3
                    00B4    100 _T0	=	0x00b4
                    00B5    101 _T1	=	0x00b5
                    00B6    102 _WR	=	0x00b6
                    00B7    103 _RD	=	0x00b7
                    00B8    104 _PX0	=	0x00b8
                    00B9    105 _PT0	=	0x00b9
                    00BA    106 _PX1	=	0x00ba
                    00BB    107 _PT1	=	0x00bb
                    00BC    108 _PS	=	0x00bc
                    00D0    109 _P	=	0x00d0
                    00D1    110 _F1	=	0x00d1
                    00D2    111 _OV	=	0x00d2
                    00D3    112 _RS0	=	0x00d3
                    00D4    113 _RS1	=	0x00d4
                    00D5    114 _F0	=	0x00d5
                    00D6    115 _AC	=	0x00d6
                    00D7    116 _CY	=	0x00d7
                            117 ;--------------------------------------------------------
                            118 ; overlayable register banks 
                            119 ;--------------------------------------------------------
                            120 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     121 	.ds 8
                            122 ;--------------------------------------------------------
                            123 ; internal ram data
                            124 ;--------------------------------------------------------
                            125 	.area DSEG    (DATA)
                            126 ;--------------------------------------------------------
                            127 ; overlayable items in internal ram 
                            128 ;--------------------------------------------------------
                            129 	.area	OSEG    (OVR,DATA)
                            130 	.area	OSEG    (OVR,DATA)
                            131 ;--------------------------------------------------------
                            132 ; Stack segment in internal ram 
                            133 ;--------------------------------------------------------
                            134 	.area	SSEG	(DATA)
   0021                     135 __start__stack:
   0021                     136 	.ds	1
                            137 
                            138 ;--------------------------------------------------------
                            139 ; indirectly addressable internal ram data
                            140 ;--------------------------------------------------------
                            141 	.area ISEG    (DATA)
                            142 ;--------------------------------------------------------
                            143 ; bit data
                            144 ;--------------------------------------------------------
                            145 	.area BSEG    (BIT)
   0000                     146 _main_flaga_1_1::
   0000                     147 	.ds 1
                            148 ;--------------------------------------------------------
                            149 ; external ram data
                            150 ;--------------------------------------------------------
                            151 	.area XSEG    (XDATA)
                            152 ;--------------------------------------------------------
                            153 ; external initialized ram data
                            154 ;--------------------------------------------------------
                            155 	.area XISEG   (XDATA)
                            156 ;--------------------------------------------------------
                            157 ; interrupt vector 
                            158 ;--------------------------------------------------------
                            159 	.area CSEG    (CODE)
   4000                     160 __interrupt_vect:
   4000 02 40 C1            161 	ljmp	__sdcc_gsinit_startup
   4003 32                  162 	reti
   4004                     163 	.ds	7
   400B 32                  164 	reti
   400C                     165 	.ds	7
   4013 32                  166 	reti
   4014                     167 	.ds	7
   401B 32                  168 	reti
   401C                     169 	.ds	7
   4023 32                  170 	reti
   4024                     171 	.ds	7
   402B 32                  172 	reti
   402C                     173 	.ds	7
                            174 ;--------------------------------------------------------
                            175 ; global & static initialisations
                            176 ;--------------------------------------------------------
                            177 	.area GSINIT  (CODE)
                            178 	.area GSFINAL (CODE)
                            179 	.area GSINIT  (CODE)
   40C1                     180 __sdcc_gsinit_startup:
   40C1 75 81 20            181 	mov	sp,#__start__stack - 1
   40C4 12 40 BD            182 	lcall	__sdcc_external_startup
   40C7 E5 82               183 	mov	a,dpl
   40C9 60 03               184 	jz	__sdcc_init_data
   40CB 02 40 33            185 	ljmp	__sdcc_program_startup
   40CE                     186 __sdcc_init_data:
                            187 ;	_mcs51_genXINIT() start
   40CE 74 00               188 	mov	a,#l_XINIT
   40D0 44 00               189 	orl	a,#l_XINIT>>8
   40D2 60 29               190 	jz	00003$
   40D4 74 00               191 	mov	a,#s_XINIT
   40D6 24 00               192 	add	a,#l_XINIT
   40D8 F9                  193 	mov	r1,a
   40D9 74 41               194 	mov	a,#s_XINIT>>8
   40DB 34 00               195 	addc	a,#l_XINIT>>8
   40DD FA                  196 	mov	r2,a
   40DE 90 41 00            197 	mov	dptr,#s_XINIT
   40E1 78 00               198 	mov	r0,#s_XISEG
   40E3 75 A0 00            199 	mov	p2,#(s_XISEG >> 8)
   40E6 E4                  200 00001$:	clr	a
   40E7 93                  201 	movc	a,@a+dptr
   40E8 F2                  202 	movx	@r0,a
   40E9 A3                  203 	inc	dptr
   40EA 08                  204 	inc	r0
   40EB B8 00 02            205 	cjne	r0,#0,00002$
   40EE 05 A0               206 	inc	p2
   40F0 E5 82               207 00002$:	mov	a,dpl
   40F2 B5 01 F1            208 	cjne	a,ar1,00001$
   40F5 E5 83               209 	mov	a,dph
   40F7 B5 02 EC            210 	cjne	a,ar2,00001$
   40FA 75 A0 FF            211 	mov	p2,#0xFF
   40FD                     212 00003$:
                            213 ;	_mcs51_genXINIT() end
                            214 	.area GSFINAL (CODE)
   40FD 02 40 33            215 	ljmp	__sdcc_program_startup
                            216 ;--------------------------------------------------------
                            217 ; Home
                            218 ;--------------------------------------------------------
                            219 	.area HOME    (CODE)
                            220 	.area CSEG    (CODE)
                            221 ;--------------------------------------------------------
                            222 ; code
                            223 ;--------------------------------------------------------
                            224 	.area CSEG    (CODE)
   4033                     225 __sdcc_program_startup:
   4033 12 40 64            226 	lcall	_main
                            227 ;	return from main will lock up
   4036 80 FE               228 	sjmp .
                            229 ;------------------------------------------------------------
                            230 ;Allocation info for local variables in function 'getchar'
                            231 ;------------------------------------------------------------
                            232 ;------------------------------------------------------------
                            233 ;main.c:3: char getchar(void)
                            234 ;	-----------------------------------------
                            235 ;	 function getchar
                            236 ;	-----------------------------------------
   4038                     237 _getchar:
                    0002    238 	ar2 = 0x02
                    0003    239 	ar3 = 0x03
                    0004    240 	ar4 = 0x04
                    0005    241 	ar5 = 0x05
                    0006    242 	ar6 = 0x06
                    0007    243 	ar7 = 0x07
                    0000    244 	ar0 = 0x00
                    0001    245 	ar1 = 0x01
                            246 ;main.c:6: while (RI==0);
   4038                     247 00101$:
                            248 ;     genNot
   4038 A2 98               249 	mov	c,_RI
   403A B3                  250 	cpl	c
   403B E4                  251 	clr	a
   403C 33                  252 	rlc	a
                            253 ;     genIfx
                            254 ;       Peephole 105   removed redundant mov
   403D FA                  255 	mov  r2,a
                            256 ;     genIfxJump
                            257 ;       Peephole 109   removed ljmp by inverse jump logic
   403E 70 F8               258 	jnz  00101$
   4040                     259 00108$:
                            260 ;main.c:7: RI=0;
                            261 ;     genAssign
   4040 C2 98               262 	clr	_RI
                            263 ;main.c:8: znak=SBUF;
                            264 ;     genAssign
   4042 85 99 82            265 	mov	dpl,_SBUF
                            266 ;main.c:9: return znak;
                            267 ;     genRet
   4045                     268 00104$:
   4045 22                  269 	ret
                            270 ;------------------------------------------------------------
                            271 ;Allocation info for local variables in function 'putchar'
                            272 ;------------------------------------------------------------
                            273 ;------------------------------------------------------------
                            274 ;main.c:12: void putchar(char znak)
                            275 ;	-----------------------------------------
                            276 ;	 function putchar
                            277 ;	-----------------------------------------
   4046                     278 _putchar:
                            279 ;     genReceive
   4046 85 82 99            280 	mov	_SBUF,dpl
                            281 ;main.c:15: while(TI==0);
   4049                     282 00101$:
                            283 ;     genNot
   4049 A2 99               284 	mov	c,_TI
   404B B3                  285 	cpl	c
   404C E4                  286 	clr	a
   404D 33                  287 	rlc	a
                            288 ;     genIfx
                            289 ;       Peephole 105   removed redundant mov
   404E FA                  290 	mov  r2,a
                            291 ;     genIfxJump
                            292 ;       Peephole 109   removed ljmp by inverse jump logic
   404F 70 F8               293 	jnz  00101$
   4051                     294 00108$:
                            295 ;main.c:16: TI=0;
                            296 ;     genAssign
   4051 C2 99               297 	clr	_TI
   4053                     298 00104$:
   4053 22                  299 	ret
                            300 ;------------------------------------------------------------
                            301 ;Allocation info for local variables in function 'init'
                            302 ;------------------------------------------------------------
                            303 ;------------------------------------------------------------
                            304 ;main.c:19: void init()
                            305 ;	-----------------------------------------
                            306 ;	 function init
                            307 ;	-----------------------------------------
   4054                     308 _init:
                            309 ;main.c:21: TH0=0xfd;
                            310 ;     genAssign
   4054 75 8C FD            311 	mov	_TH0,#0xFD
                            312 ;main.c:22: SCON=0x50;
                            313 ;     genAssign
   4057 75 98 50            314 	mov	_SCON,#0x50
                            315 ;main.c:23: TMOD=0x20;
                            316 ;     genAssign
   405A 75 89 20            317 	mov	_TMOD,#0x20
                            318 ;main.c:24: PCON=0x80;
                            319 ;     genAssign
   405D 75 87 80            320 	mov	_PCON,#0x80
                            321 ;main.c:25: TCON=0x40;
                            322 ;     genAssign
   4060 75 88 40            323 	mov	_TCON,#0x40
   4063                     324 00101$:
   4063 22                  325 	ret
                            326 ;------------------------------------------------------------
                            327 ;Allocation info for local variables in function 'main'
                            328 ;------------------------------------------------------------
                            329 ;znak                      Allocated to registers r3 
                            330 ;ile                       Allocated to registers 
                            331 ;------------------------------------------------------------
                            332 ;main.c:28: void main (void)
                            333 ;	-----------------------------------------
                            334 ;	 function main
                            335 ;	-----------------------------------------
   4064                     336 _main:
                            337 ;main.c:32: bit flaga=0;
                            338 ;     genAssign
   4064 C2 00               339 	clr	_main_flaga_1_1
                            340 ;main.c:33: init();
                            341 ;     genCall
   4066 12 40 54            342 	lcall	_init
                            343 ;     genAssign
   4069 7A 30               344 	mov	r2,#0x30
   406B                     345 00110$:
                            346 ;main.c:36: znak=getchar();
                            347 ;     genCall
   406B C0 02               348 	push	ar2
   406D 12 40 38            349 	lcall	_getchar
   4070 E5 82               350 	mov	a,dpl
   4072 D0 02               351 	pop	ar2
                            352 ;     genAssign
                            353 ;main.c:38: if(znak < 65 || (znak > 90 && znak <97) || znak >122)
                            354 ;     genCmpLt
                            355 ;     genCmp
                            356 ;       Peephole 106   removed redundant mov 
   4074 FB                  357 	mov  r3,a
   4075 C3                  358 	clr  c
   4076 64 80               359 	xrl	a,#0x80
   4078 94 C1               360 	subb	a,#0xc1
                            361 ;     genIfxJump
                            362 ;       Peephole 132   changed ljmp to sjmp
                            363 ;       Peephole 160   removed sjmp by inverse jump logic
   407A 40 20               364 	jc   00103$
   407C                     365 00118$:
                            366 ;     genCmpGt
                            367 ;     genCmp
   407C C3                  368 	clr	c
                            369 ;       Peephole 159   avoided xrl during execution
   407D 74 DA               370 	mov  a,#(0x5A ^ 0x80)
   407F 8B F0               371 	mov	b,r3
   4081 63 F0 80            372 	xrl	b,#0x80
   4084 95 F0               373 	subb	a,b
                            374 ;     genIfxJump
                            375 ;       Peephole 108   removed ljmp by inverse jump logic
   4086 50 08               376 	jnc  00108$
   4088                     377 00119$:
                            378 ;     genCmpLt
                            379 ;     genCmp
   4088 C3                  380 	clr	c
   4089 EB                  381 	mov	a,r3
   408A 64 80               382 	xrl	a,#0x80
   408C 94 E1               383 	subb	a,#0xe1
                            384 ;     genIfxJump
                            385 ;       Peephole 132   changed ljmp to sjmp
                            386 ;       Peephole 160   removed sjmp by inverse jump logic
   408E 40 0C               387 	jc   00103$
   4090                     388 00120$:
   4090                     389 00108$:
                            390 ;     genCmpGt
                            391 ;     genCmp
   4090 C3                  392 	clr	c
                            393 ;       Peephole 159   avoided xrl during execution
   4091 74 FA               394 	mov  a,#(0x7A ^ 0x80)
   4093 8B F0               395 	mov	b,r3
   4095 63 F0 80            396 	xrl	b,#0x80
   4098 95 F0               397 	subb	a,b
                            398 ;     genIfxJump
                            399 ;       Peephole 108   removed ljmp by inverse jump logic
   409A 50 1B               400 	jnc  00104$
   409C                     401 00121$:
   409C                     402 00103$:
                            403 ;     genIfx
                            404 ;     genIfxJump
                            405 ;       Peephole 111   removed ljmp by inverse jump logic
   409C 30 00 CC            406 	jnb  _main_flaga_1_1,00110$
   409F                     407 00122$:
                            408 ;main.c:42: putchar(44);
                            409 ;     genCall
   409F 75 82 2C            410 	mov	dpl,#0x2C
   40A2 C0 02               411 	push	ar2
   40A4 12 40 46            412 	lcall	_putchar
   40A7 D0 02               413 	pop	ar2
                            414 ;main.c:43: ile++;
                            415 ;     genPlus
                            416 ;     genPlusIncr
   40A9 0A                  417 	inc	r2
                            418 ;main.c:44: putchar(ile);            		
                            419 ;     genCall
   40AA 8A 82               420 	mov	dpl,r2
   40AC C0 02               421 	push	ar2
   40AE 12 40 46            422 	lcall	_putchar
   40B1 D0 02               423 	pop	ar2
                            424 ;main.c:45: flaga=0;
                            425 ;     genAssign
   40B3 C2 00               426 	clr	_main_flaga_1_1
                            427 ;       Peephole 132   changed ljmp to sjmp
   40B5 80 B4               428 	sjmp 00110$
   40B7                     429 00104$:
                            430 ;main.c:48: else flaga=1;
                            431 ;     genAssign
   40B7 D2 00               432 	setb	_main_flaga_1_1
   40B9 02 40 6B            433 	ljmp	00110$
   40BC                     434 00112$:
   40BC 22                  435 	ret
                            436 	.area CSEG    (CODE)
                            437 	.area XINIT   (CODE)
