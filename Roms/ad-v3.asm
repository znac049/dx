
; Labels:
;
ThreeKHz              = $2001
VGHalted              = $2002
ShieldSW              = $2003
FireSW                = $2004
SlamSW                = $2006
SelfTestSW            = $2007
LCoinSW               = $2400
CCoinSW               = $2401
RCoinSW               = $2402
PlayerOneSW           = $2403
PlayerTwoSW           = $2404
ThrustSW              = $2405
RotateRSW             = $2406
RotateLSW             = $2407
Option87              = $2800
Option65              = $2801
Option43              = $2802
Option21              = $2803
Pk_F1_Pot0            = $2c00
Pk_C1_Pot1            = $2c01
Pk_F2_Pot2            = $2c02
Pk_C2_Pot3            = $2c03
Pk_F3_Pot4            = $2c04
Pk_C3_Pot5            = $2c05
Pk_F4_Pot6            = $2c06
Pk_C4_Pot7            = $2c07
Pk_Ctl_All            = $2c08
Pk_STim_Kbc           = $2c09
Pk_SkRes_Rnd          = $2c0a
Pk_PotGo              = $2c0b
Pk_SerData            = $2c0d
Pk_IrqCtl             = $2c0e
Pk_SerCtl             = $2c0f
EaromRd               = $2c40
StartVG               = $3000
LatchEA               = $3200
WdogReset             = $3400
ExplodeCtrl           = $3600
VGReset               = $3800
EAControl             = $3a00
P1LED                 = $3c00
P2LED                 = $3c01
ThrustSnd             = $3c03
BankSel               = $3c04
LCount                = $3c05
CCount                = $3c06
RCoin                 = $3c07
NoiseReset            = $3e00
VRAM                  = $4000
Reset_Vec             = $fffc
NMI_Vec               = $fffe
IRQ_Vec               = $fffa
L4ba2                 = $4ba2
L4be1                 = $4be1
L4a9e                 = $4a9e
L49bb                 = $49bb
L48be                 = $48be
L4800                 = $4800
L4a22                 = $4a22
L49e7                 = $49e7
L4a32                 = $4a32
L4a75                 = $4a75



L6000                jsr  L7be3                            ; 6000
                     lda  $cd                              ; 6003
                     bne  L6011                            ; 6005
                                                           ; 0A -> +10
                     sta  $cc                              ; 6007
                     sta  $cb                              ; 6009
                     sta  $ce                              ; 600B
                     lda  #$20                             ; 600D
                     sta  $cd                              ; 600F

L6011                jsr  L6959                            ; 6011

L6014                bit  VGHalted                         ; 6014
                     bmi  L6014                            ; 6017
                                                           ; FB -> 04 ->  -5
                     jsr  L4ba2                            ; 6019

L601c                lsr  $75                              ; 601C
                     bcc  L601c                            ; 601E
                                                           ; FC -> 03 ->  -4
                     lda  $76                              ; 6020
                     and  #$01                             ; 6022
                     asl  A                                ; 6024
                     tax                                   ; 6025
                     eor  #$02                             ; 6026
                     tay                                   ; 6028
                     lda  $7799,X                          ; 6029
                     sta  VRAM                             ; 602C
                     lda  $779a,X                          ; 602F
                     sta  $4001                            ; 6032
                     lda  $7799,Y                          ; 6035
                     asl  A                                ; 6038
                     sta  $03                              ; 6039
                     lda  $779a,Y                          ; 603B
                     rol  A                                ; 603E
                     and  #$1f                             ; 603F
                     ora  #$40                             ; 6041
                     sta  $04                              ; 6043
                     sta  StartVG                          ; 6045
                     sta  WdogReset                        ; 6048
                     inc  $76                              ; 604B
                     bne  L607f                            ; 604D
                                                           ; 30 -> +48
                     inc  $77                              ; 604F
                     ldx  $20                              ; 6051
                     lda  $64,X                            ; 6053
                     and  #$0f                             ; 6055
                     sta  $10                              ; 6057
                     eor  $64,X                            ; 6059
                     lsr  A                                ; 605B
                     sta  $11                              ; 605C
                     lsr  A                                ; 605E
                     lsr  A                                ; 605F
                     adc  $11                              ; 6060
                     adc  $10                              ; 6062
                     ldx  $1f                              ; 6064
                     ldy  $77                              ; 6066
                     cpy  #$80                             ; 6068
                     bne  L6074                            ; 606A
                                                           ; 08 -> +8
                     cmp  $fa,X                            ; 606C
                     bne  L6072                            ; 606E
                                                           ; 02 -> +2
                     inc  $fb,X                            ; 6070

L6072                sta  $fa,X                            ; 6072

L6074                clc                                   ; 6074
                     adc  $fb,X                            ; 6075
                     cmp  #$10                             ; 6077
                     bcc  L607d                            ; 6079
                                                           ; 02 -> +2
                     lda  #$0f                             ; 607B

L607d                sta  $d3                              ; 607D

L607f                jsr  L7aff                            ; 607F
                     jsr  L4be1                            ; 6082
                     bcs  L60c9                            ; 6085
                                                           ; 42 -> +66
                     jsr  L6fd4                            ; 6087
                     jsr  L656b                            ; 608A
                     bpl  L60ad                            ; 608D
                                                           ; 1E -> +30
                     jsr  L6c9d                            ; 608F
                     bcs  L60ad                            ; 6092
                                                           ; 19 -> +25
                     lda  $74                              ; 6094
                     bne  L60a7                            ; 6096
                                                           ; 0F -> +15
                     jsr  L6659                            ; 6098
                     jsr  L6497                            ; 609B
                     jsr  L6810                            ; 609E
                     jsr  L4a9e                            ; 60A1
                     jsr  L6322                            ; 60A4

L60a7                jsr  L66dc                            ; 60A7
                     jsr  L60f7                            ; 60AA

L60ad                jsr  L6a7e                            ; 60AD
                     jsr  L6ef6                            ; 60B0
                     lda  #$7f                             ; 60B3
                     tax                                   ; 60B5
                     jsr  L7a1f                            ; 60B6
                     jsr  L79da                            ; 60B9
                     lda  $02ec                            ; 60BC
                     beq  L60c4                            ; 60BF
                                                           ; 03 -> +3
                     dec  $02ec                            ; 60C1

L60c4                ora  $02e7                            ; 60C4
                     bne  L60cc                            ; 60C7
                                                           ; 03 -> +3

L60c9                jmp  L6011                            ; 60C9

L60cc                jmp  L6014                            ; 60CC
                     fcb  $B2,$A5,$42,$25,$43,$30,$03,$4C    
                     fcb  $C7,$7B,$18,$60,$A5,$8A,$05,$13    
                     fcb  $10,$07,$A5,$76,$29,$20,$F0,$01    
                     fcb  $60,$4C,$59,$71,$A0,$01,$20,$59    
                     fcb  $71,$A4,$1E,$C8,$98,$4C,$EB,$79    

L60f7                lsr  $71                              ; 60F7
                     ldx  #$07                             ; 60F9

L60fb                lda  $0219,X                          ; 60FB
                     beq  L6102                            ; 60FE
                                                           ; 02 -> +2
                     bpl  L610c                            ; 6100
                                                           ; 0A -> +10

L6102                dex                                   ; 6102
                     bpl  L60fb                            ; 6103
                                                           ; F6 -> 09 ->  -10
                     bit  $71                              ; 6105
                     bmi  L610b                            ; 6107
                                                           ; 02 -> +2
                     stx  $72                              ; 6109

L610b                rts                                   ; 610B

L610c                ldy  #$1a                             ; 610C
                     cpx  #$04                             ; 610E
                     bcs  L6119                            ; 6110
                                                           ; 07 -> +7
                     dey                                   ; 6112
                     txa                                   ; 6113
                     bne  L6119                            ; 6114
                                                           ; 03 -> +3

L6116                dey                                   ; 6116
                     bmi  L6102                            ; 6117
                                                           ; E9 -> 16 ->  -23

L6119                lda  $0200,Y                          ; 6119
                     beq  L6116                            ; 611C
                                                           ; F8 -> 07 ->  -8
                     bmi  L6116                            ; 611E
                                                           ; F6 -> 09 ->  -10
                     sta  $0c                              ; 6120
                     lda  $0263,Y                          ; 6122
                     sec                                   ; 6125
                     sbc  $027c,X                          ; 6126
                     sbc  #$03                             ; 6129
                     cmp  #$fa                             ; 612B
                     bcc  L6116                            ; 612D
                                                           ; E7 -> 18 ->  -25
                     lda  $0284,Y                          ; 612F
                     sbc  $029d,X                          ; 6132
                     sbc  #$03                             ; 6135
                     cmp  #$fa                             ; 6137
                     bcc  L6116                            ; 6139
                                                           ; DB -> 24 ->  -37
                     lda  $02a5,Y                          ; 613B
                     sec                                   ; 613E
                     sbc  $02be,X                          ; 613F
                     sta  $09                              ; 6142
                     lda  $0263,Y                          ; 6144
                     sbc  $027c,X                          ; 6147
                     lsr  A                                ; 614A
                     ror  $09                              ; 614B
                     asl  A                                ; 614D
                     beq  L615e                            ; 614E
                                                           ; 0E -> +14
                     bpl  L6116                            ; 6150
                                                           ; C4 -> 3B ->  -60
                     eor  #$fe                             ; 6152
                     bne  L6116                            ; 6154
                                                           ; C0 -> 3F ->  -64
                     lda  $09                              ; 6156
                     eor  #$ff                             ; 6158
                     adc  #$00                             ; 615A
                     sta  $09                              ; 615C

L615e                lda  $02c6,Y                          ; 615E
                     sec                                   ; 6161
                     sbc  $02df,X                          ; 6162
                     sta  $0a                              ; 6165
                     lda  $0284,Y                          ; 6167
                     sbc  $029d,X                          ; 616A
                     lsr  A                                ; 616D
                     ror  $0a                              ; 616E
                     asl  A                                ; 6170
                     beq  L6181                            ; 6171
                                                           ; 0E -> +14
                     bpl  L6116                            ; 6173
                                                           ; A1 -> 5E ->  -95
                     eor  #$fe                             ; 6175
                     bne  L6116                            ; 6177
                                                           ; 9D -> 62 ->  -99
                     lda  $0a                              ; 6179
                     eor  #$ff                             ; 617B
                     adc  #$00                             ; 617D
                     sta  $0a                              ; 617F

L6181                lda  #$04                             ; 6181
                     cpx  #$01                             ; 6183
                     beq  L618e                            ; 6185
                                                           ; 07 -> +7
                     bcs  L6191                            ; 6187
                                                           ; 08 -> +8
                     jsr  L61d5                            ; 6189
                     bne  L6191                            ; 618C
                                                           ; 03 -> +3

L618e                jsr  L61de                            ; 618E

L6191                cpy  #$19                             ; 6191
                     bcs  L61a5                            ; 6193
                                                           ; 10 -> +16
                     adc  #$2a                             ; 6195
                     lsr  $0c                              ; 6197
                     bcs  L61af                            ; 6199
                                                           ; 14 -> +20
                     adc  #$1e                             ; 619B
                     lsr  $0c                              ; 619D
                     bcs  L61af                            ; 619F
                                                           ; 0E -> +14
                     adc  #$3c                             ; 61A1
                     bcc  L61af                            ; 61A3
                                                           ; 0A -> +10

L61a5                beq  L61ac                            ; 61A5
                                                           ; 05 -> +5
                     jsr  L61de                            ; 61A7
                     bne  L61af                            ; 61AA
                                                           ; 03 -> +3

L61ac                jsr  L61d5                            ; 61AC

L61af                cmp  $09                              ; 61AF
                     bcc  L61d2                            ; 61B1
                                                           ; 1F -> +31
                     cmp  $0a                              ; 61B3
                     bcc  L61d2                            ; 61B5
                                                           ; 1B -> +27
                     sta  $0c                              ; 61B7
                     lsr  A                                ; 61B9
                     clc                                   ; 61BA
                     adc  $0c                              ; 61BB
                     ror  A                                ; 61BD
                     sta  $0c                              ; 61BE
                     lda  $0a                              ; 61C0
                     adc  $09                              ; 61C2
                     ror  A                                ; 61C4
                     cmp  $0c                              ; 61C5
                     bcs  L61d2                            ; 61C7
                                                           ; 09 -> +9
                     txa                                   ; 61C9
                     pha                                   ; 61CA
                     jsr  L62a1                            ; 61CB
                     pla                                   ; 61CE
                     tax                                   ; 61CF
                     ldy  #$00                             ; 61D0

L61d2                jmp  L6116                            ; 61D2

L61d5                bit  $73                              ; 61D5
                     bpl  L61db                            ; 61D7
                                                           ; 02 -> +2
                     adc  #$08                             ; 61D9

L61db                adc  #$1c                             ; 61DB
                     rts                                   ; 61DD

L61de                adc  #$1c                             ; 61DE
                     pha                                   ; 61E0
                     lda  $021a                            ; 61E1
                     lsr  A                                ; 61E4
                     pla                                   ; 61E5
                     bcs  L61ea                            ; 61E6
                                                           ; 02 -> +2
                     adc  #$12                             ; 61E8

L61ea                rts                                   ; 61EA

L61eb                lda  $0200,Y                          ; 61EB
                     and  #$07                             ; 61EE
                     sta  $09                              ; 61F0
                     lda  Pk_SkRes_Rnd                     ; 61F2
                     and  #$18                             ; 61F5
                     ora  $09                              ; 61F7
                     sta  $0200,X                          ; 61F9
                     lda  $02a5,Y                          ; 61FC
                     sta  $02a5,X                          ; 61FF
                     lda  $0263,Y                          ; 6202
                     sta  $0263,X                          ; 6205
                     lda  $02c6,Y                          ; 6208
                     sta  $02c6,X                          ; 620B
                     lda  $0284,Y                          ; 620E
                     sta  $0284,X                          ; 6211
                     lda  $0221,Y                          ; 6214
                     sta  $0221,X                          ; 6217
                     lda  $0242,Y                          ; 621A
                     sta  $0242,X                          ; 621D
                     rts                                   ; 6220

L6221                ldy  #$ff                             ; 6221
                     bit  $12                              ; 6223
                     bmi  L6254                            ; 6225
                                                           ; 2D -> +45

L6227                iny                                   ; 6227
                     iny                                   ; 6228
                     lda  ($10),Y                          ; 6229
                     eor  $0a                              ; 622B
                     sta  ($03),Y                          ; 622D
                     dey                                   ; 622F
                     cmp  #$f0                             ; 6230
                     bcs  L624b                            ; 6232
                                                           ; 17 -> +23
                     lda  ($10),Y                          ; 6234
                     sta  ($03),Y                          ; 6236
                     iny                                   ; 6238
                     iny                                   ; 6239
                     lda  ($10),Y                          ; 623A
                     sta  ($03),Y                          ; 623C
                     iny                                   ; 623E
                     lda  ($10),Y                          ; 623F
                     eor  $09                              ; 6241
                     sta  ($03),Y                          ; 6243

L6245                dex                                   ; 6245
                     bpl  L6227                            ; 6246
                                                           ; DF -> 20 ->  -33
                     jmp  L7a55                            ; 6248

L624b                lda  ($10),Y                          ; 624B
                     eor  $09                              ; 624D
                     sta  ($03),Y                          ; 624F
                     iny                                   ; 6251
                     bne  L6245                            ; 6252
                                                           ; F1 -> 0E ->  -15

L6254                iny                                   ; 6254
                     lda  ($10),Y                          ; 6255
                     sta  $14                              ; 6257
                     iny                                   ; 6259
                     lda  ($10),Y                          ; 625A
                     cmp  #$f0                             ; 625C
                     bcs  L628c                            ; 625E
                                                           ; 2C -> +44
                     iny                                   ; 6260
                     iny                                   ; 6261
                     eor  ($10),Y                          ; 6262
                     and  #$0f                             ; 6264
                     sta  $13                              ; 6266
                     eor  ($10),Y                          ; 6268
                     eor  $09                              ; 626A
                     sta  ($03),Y                          ; 626C
                     dey                                   ; 626E
                     lda  ($10),Y                          ; 626F
                     pha                                   ; 6271
                     lda  $14                              ; 6272
                     sta  ($03),Y                          ; 6274
                     dey                                   ; 6276
                     lda  $13                              ; 6277
                     eor  $0a                              ; 6279
                     eor  ($10),Y                          ; 627B
                     sta  ($03),Y                          ; 627D
                     dey                                   ; 627F
                     pla                                   ; 6280
                     sta  ($03),Y                          ; 6281
                     iny                                   ; 6283
                     iny                                   ; 6284

L6285                iny                                   ; 6285
                     dex                                   ; 6286
                     bpl  L6254                            ; 6287
                                                           ; CB -> 34 ->  -53
                     jmp  L7a55                            ; 6289

L628c                eor  $14                              ; 628C
                     and  #$07                             ; 628E
                     pha                                   ; 6290
                     eor  ($10),Y                          ; 6291
                     eor  $0a                              ; 6293
                     sta  ($03),Y                          ; 6295
                     dey                                   ; 6297
                     pla                                   ; 6298
                     eor  ($10),Y                          ; 6299
                     eor  $09                              ; 629B
                     sta  ($03),Y                          ; 629D
                     bcs  L6285                            ; 629F
                                                           ; E4 -> 1B ->  -28

L62a1                jsr  L74e7                            ; 62A1
                     bcs  L6308                            ; 62A4
                                                           ; 62 -> +98
                     cpx  #$01                             ; 62A6
                     bne  L62b0                            ; 62A8
                                                           ; 06 -> +6
                     cpy  #$19                             ; 62AA
                     bne  L62b6                            ; 62AC
                                                           ; 08 -> +8
                     dex                                   ; 62AE
                     iny                                   ; 62AF

L62b0                txa                                   ; 62B0
                     bne  L62c9                            ; 62B1
                                                           ; 16 -> +22
                     jsr  L62f8                            ; 62B3

L62b6                lda  #$a0                             ; 62B6
                     sta  $0219,X                          ; 62B8
                     lda  #$00                             ; 62BB
                     sta  $023a,X                          ; 62BD
                     sta  $025b,X                          ; 62C0
                     cpy  #$19                             ; 62C3
                     bcc  L62d4                            ; 62C5
                                                           ; 0D -> +13
                     bcs  L6308                            ; 62C7
                                                           ; 3F -> +63

L62c9                lda  #$00                             ; 62C9
                     sta  $0219,X                          ; 62CB
                     cpy  #$19                             ; 62CE
                     beq  L62f3                            ; 62D0
                                                           ; 21 -> +33
                     bcs  L6308                            ; 62D2
                                                           ; 34 -> +52

L62d4                jsr  L6f62                            ; 62D4

L62d7                lda  $0200,Y                          ; 62D7
                     and  #$03                             ; 62DA
                     eor  #$02                             ; 62DC
                     lsr  A                                ; 62DE
                     ror  A                                ; 62DF
                     ror  A                                ; 62E0
                     ora  #$3f                             ; 62E1
                     sta  $7f                              ; 62E3
                     lda  #$a0                             ; 62E5
                     sta  $0200,Y                          ; 62E7
                     lda  #$00                             ; 62EA
                     sta  $0221,Y                          ; 62EC
                     sta  $0242,Y                          ; 62EF
                     rts                                   ; 62F2

L62f3                jsr  L62f8                            ; 62F3
                     bne  L62d7                            ; 62F6
                                                           ; DF -> 20 ->  -33

L62f8                txa                                   ; 62F8
                     ldx  $1e                              ; 62F9
                     dec  $6f,X                            ; 62FB
                     tax                                   ; 62FD
                     lda  #$81                             ; 62FE

L6300                sta  $02eb                            ; 6300
                     lda  #$05                             ; 6303
                     sta  $de                              ; 6305
                     rts                                   ; 6307

L6308                lda  $02e9                            ; 6308
                     sta  $02e8                            ; 630B
                     lda  $22                              ; 630E
                     beq  L62d7                            ; 6310
                                                           ; C5 -> 3A ->  -59
                     lda  $021a                            ; 6312
                     lsr  A                                ; 6315
                     lda  #$00                             ; 6316
                     bcs  L631c                            ; 6318
                                                           ; 02 -> +2
                     lda  #$20                             ; 631A

L631c                jsr  L6c44                            ; 631C
                     jmp  L62d7                            ; 631F

L6322                lda  $76                              ; 6322
                     and  #$03                             ; 6324
                     beq  L6329                            ; 6326
                                                           ; 01 -> +1

L6328                rts                                   ; 6328

L6329                lda  $021a                            ; 6329
                     beq  L6338                            ; 632C
                                                           ; 0A -> +10
                     bpl  L6335                            ; 632E
                                                           ; 05 -> +5
                     ldy  #$17                             ; 6330
                     jmp  L770d                            ; 6332

L6335                jmp  L63c5                            ; 6335

L6338                jsr  L67fa                            ; 6338
                     lda  $22                              ; 633B
                     beq  L6346                            ; 633D
                                                           ; 07 -> +7
                     lda  $0219                            ; 633F
                     beq  L6328                            ; 6342
                                                           ; E4 -> 1B ->  -28
                     bmi  L6328                            ; 6344
                                                           ; E2 -> 1D ->  -30

L6346                lda  $02ea                            ; 6346
                     beq  L634e                            ; 6349
                                                           ; 03 -> +3
                     dec  $02ea                            ; 634B

L634e                dec  $02e8                            ; 634E
                     bne  L6328                            ; 6351
                                                           ; D5 -> 2A ->  -43
                     lda  #$01                             ; 6353
                     sta  $02e8                            ; 6355
                     ldx  $02e7                            ; 6358
                     beq  L6328                            ; 635B
                                                           ; CB -> 34 ->  -53
                     lda  $02ea                            ; 635D
                     beq  L6367                            ; 6360
                                                           ; 05 -> +5
                     cpx  $02ee                            ; 6362
                     bcs  L6328                            ; 6365
                                                           ; C1 -> 3E ->  -63

L6367                lda  $02e9                            ; 6367
                     sec                                   ; 636A
                     sbc  #$06                             ; 636B
                     cmp  #$20                             ; 636D
                     bcc  L6374                            ; 636F
                                                           ; 03 -> +3
                     sta  $02e9                            ; 6371

L6374                lda  Pk_SkRes_Rnd                     ; 6374
                     lsr  A                                ; 6377
                     ror  $02e0                            ; 6378
                     lsr  A                                ; 637B
                     ror  $02e0                            ; 637C
                     lsr  A                                ; 637F
                     ror  $02e0                            ; 6380
                     adc  #$04                             ; 6383
                     cmp  #$12                             ; 6385
                     bcc  L638b                            ; 6387
                                                           ; 02 -> +2
                     sbc  #$10                             ; 6389

L638b                sta  $029e                            ; 638B
                     lda  Pk_SkRes_Rnd                     ; 638E
                     asl  A                                ; 6391
                     lda  #$00                             ; 6392
                     tax                                   ; 6394
                     ldy  #$10                             ; 6395
                     bcc  L639e                            ; 6397
                                                           ; 05 -> +5
                     dex                                   ; 6399
                     lda  #$1f                             ; 639A
                     ldy  #$f0                             ; 639C

L639e                sty  $023b                            ; 639E
                     sta  $027d                            ; 63A1
                     stx  $02bf                            ; 63A4
                     ldy  #$02                             ; 63A7
                     lda  $d3                              ; 63A9
                     beq  L63b9                            ; 63AB
                                                           ; 0C -> +12
                     lda  $02ee                            ; 63AD
                     sec                                   ; 63B0
                     sbc  $02e7                            ; 63B1
                     cmp  #$04                             ; 63B4
                     bcc  L63b9                            ; 63B6
                                                           ; 01 -> +1
                     dey                                   ; 63B8

L63b9                sty  $021a                            ; 63B9
                     lda  $63c2,Y                          ; 63BC
                     tay                                   ; 63BF
                     jmp  L7716                            ; 63C0
                     fcb  $17,$37                            

L63c5                lda  $76                              ; 63C5
                     asl  A                                ; 63C7
                     bne  L63d6                            ; 63C8
                                                           ; 0C -> +12
                     lda  Pk_SkRes_Rnd                     ; 63CA
                     and  #$03                             ; 63CD
                     tax                                   ; 63CF
                     lda  $6457,X                          ; 63D0
                     sta  $025c                            ; 63D3

L63d6                lda  $22                              ; 63D6
                     beq  L63df                            ; 63D8
                                                           ; 05 -> +5
                     lda  $02eb                            ; 63DA
                     bne  L63e4                            ; 63DD
                                                           ; 05 -> +5

L63df                dec  $02e8                            ; 63DF
                     beq  L63e5                            ; 63E2
                                                           ; 01 -> +1

L63e4                rts                                   ; 63E4

L63e5                lda  #$0a                             ; 63E5
                     sta  $02e8                            ; 63E7
                     ldy  #$19                             ; 63EA
                     lda  $22                              ; 63EC
                     beq  L63ff                            ; 63EE
                                                           ; 0F -> +15
                     ldx  #$aa                             ; 63F0
                     lda  $021a                            ; 63F2
                     lsr  A                                ; 63F5
                     bcs  L63fa                            ; 63F6
                                                           ; 02 -> +2
                     ldx  #$40                             ; 63F8

L63fa                cpx  Pk_SkRes_Rnd                     ; 63FA
                     bcs  L6402                            ; 63FD
                                                           ; 03 -> +3

L63ff                jsr  L645b                            ; 63FF

L6402                sty  $18                              ; 6402
                     ldx  #$1a                             ; 6404
                     jsr  L4a22                            ; 6406
                     jsr  L49e7                            ; 6409
                     sta  $13                              ; 640C
                     lda  $0c                              ; 640E
                     sta  $12                              ; 6410
                     lda  $18                              ; 6412
                     clc                                   ; 6414
                     adc  #$21                             ; 6415
                     tay                                   ; 6417
                     ldx  #$3b                             ; 6418
                     jsr  L4a22                            ; 641A
                     jsr  L49e7                            ; 641D
                     jsr  L4a32                            ; 6420
                     sta  $7a                              ; 6423
                     lda  $18                              ; 6425
                     cmp  #$19                             ; 6427
                     bne  L6442                            ; 6429
                                                           ; 17 -> +23
                     ldx  $d3                              ; 642B
                     cpx  #$03                             ; 642D
                     bcc  L6433                            ; 642F
                                                           ; 02 -> +2
                     ldx  #$03                             ; 6431

L6433                lda  Pk_SkRes_Rnd                     ; 6433
                     and  $644f,X                          ; 6436
                     bpl  L643e                            ; 6439
                                                           ; 03 -> +3
                     ora  $6453,X                          ; 643B

L643e                adc  $7a                              ; 643E
                     sta  $7a                              ; 6440

L6442                ldy  #$03                             ; 6442
                     lda  #$01                             ; 6444
                     sta  $0f                              ; 6446
                     ldx  $18                              ; 6448
                     sta  $18                              ; 644A
                     jmp  L64c8                            ; 644C
                     fcb  $9F,$8F,$8F,$87,$60,$70,$70,$78    
                     fcb  $F0,$00,$00,$10                    

L645b                dey                                   ; 645B

L645c                lda  $0200,Y                          ; 645C
                     bne  L6468                            ; 645F
                                                           ; 07 -> +7

L6461                dey                                   ; 6461
                     bpl  L645c                            ; 6462
                                                           ; F8 -> 07 ->  -8
                     ldy  #$19                             ; 6464
                     sec                                   ; 6466
                     rts                                   ; 6467

L6468                bmi  L6461                            ; 6468
                                                           ; F7 -> 08 ->  -9
                     cmp  #$40                             ; 646A
                     bcc  L6478                            ; 646C
                                                           ; 0A -> +10
                     lsr  A                                ; 646E
                     lsr  A                                ; 646F
                     tax                                   ; 6470
                     lda  $02e8,X                          ; 6471
                     bpl  L6461                            ; 6474
                                                           ; EB -> 14 ->  -21
                     clc                                   ; 6476
                     rts                                   ; 6477

L6478                lda  $027d                            ; 6478
                     sec                                   ; 647B
                     sbc  $0263,Y                          ; 647C
                     bpl  L6483                            ; 647F
                                                           ; 02 -> +2
                     eor  #$ff                             ; 6481

L6483                cmp  #$08                             ; 6483
                     bcs  L6461                            ; 6485
                                                           ; DA -> 25 ->  -38
                     lda  $029e                            ; 6487
                     sec                                   ; 648A
                     sbc  $0284,Y                          ; 648B
                     bpl  L6492                            ; 648E
                                                           ; 02 -> +2
                     eor  #$ff                             ; 6490

L6492                cmp  #$08                             ; 6492
                     bcs  L6461                            ; 6494
                                                           ; CB -> 34 ->  -53
                     rts                                   ; 6496

L6497                ldx  #$00                             ; 6497
                     lda  $22                              ; 6499
                     bne  L64a0                            ; 649B
                                                           ; 03 -> +3

L649d                stx  $ff                              ; 649D
                     rts                                   ; 649F

L64a0                bit  $73                              ; 64A0
                     bmi  L649d                            ; 64A2
                                                           ; F9 -> 06 ->  -7
                     bit  $fe                              ; 64A4
                     bpl  L649d                            ; 64A6
                                                           ; F5 -> 0A ->  -11
                     lda  $02eb                            ; 64A8
                     bne  L649d                            ; 64AB
                                                           ; F0 -> 0F ->  -16
                     inc  $ff                              ; 64AD
                     lda  $ff                              ; 64AF
                     cmp  #$02                             ; 64B1
                     bcc  L64ba                            ; 64B3
                                                           ; 05 -> +5
                     cmp  #$0f                             ; 64B5
                     bcs  L649d                            ; 64B7
                                                           ; E4 -> 1B ->  -28
                     rts                                   ; 64B9

L64ba                stx  $18                              ; 64BA
                     lda  #$03                             ; 64BC
                     sta  $0f                              ; 64BE
                     ldx  #$19                             ; 64C0
                     lda  $79                              ; 64C2
                     sta  $7a                              ; 64C4
                     ldy  #$07                             ; 64C6

L64c8                lda  $0219,Y                          ; 64C8
                     beq  L64d3                            ; 64CB
                                                           ; 06 -> +6
                     dey                                   ; 64CD
                     cpy  $0f                              ; 64CE
                     bne  L64c8                            ; 64D0
                                                           ; F6 -> 09 ->  -10
                     rts                                   ; 64D2

L64d3                stx  $0e                              ; 64D3
                     lda  #$12                             ; 64D5
                     sta  $0219,Y                          ; 64D7
                     lda  $7a                              ; 64DA
                     jsr  L70fe                            ; 64DC
                     ldx  $0e                              ; 64DF
                     cmp  #$80                             ; 64E1
                     ror  A                                ; 64E3
                     sta  $0a                              ; 64E4
                     clc                                   ; 64E6
                     adc  $0221,X                          ; 64E7
                     bmi  L64f4                            ; 64EA
                                                           ; 08 -> +8
                     cmp  #$70                             ; 64EC
                     bcc  L64fa                            ; 64EE
                                                           ; 0A -> +10
                     lda  #$6f                             ; 64F0
                     bne  L64fa                            ; 64F2
                                                           ; 06 -> +6

L64f4                cmp  #$91                             ; 64F4
                     bcs  L64fa                            ; 64F6
                                                           ; 02 -> +2
                     lda  #$91                             ; 64F8

L64fa                sta  $023a,Y                          ; 64FA
                     lda  $7a                              ; 64FD
                     jsr  L7101                            ; 64FF
                     ldx  $0e                              ; 6502
                     cmp  #$80                             ; 6504
                     ror  A                                ; 6506
                     sta  $0d                              ; 6507
                     clc                                   ; 6509
                     adc  $0242,X                          ; 650A
                     bmi  L6517                            ; 650D
                                                           ; 08 -> +8
                     cmp  #$70                             ; 650F
                     bcc  L651d                            ; 6511
                                                           ; 0A -> +10
                     lda  #$6f                             ; 6513
                     bne  L651d                            ; 6515
                                                           ; 06 -> +6

L6517                cmp  #$91                             ; 6517
                     bcs  L651d                            ; 6519
                                                           ; 02 -> +2
                     lda  #$91                             ; 651B

L651d                sta  $025b,Y                          ; 651D
                     ldx  #$00                             ; 6520
                     lda  $0a                              ; 6522
                     bpl  L6527                            ; 6524
                                                           ; 01 -> +1
                     dex                                   ; 6526

L6527                stx  $09                              ; 6527
                     ldx  $18                              ; 6529
                     cmp  #$80                             ; 652B
                     ror  A                                ; 652D
                     clc                                   ; 652E
                     adc  $0a                              ; 652F
                     clc                                   ; 6531
                     adc  $02be,X                          ; 6532
                     sta  $02be,Y                          ; 6535
                     lda  $09                              ; 6538
                     adc  $027c,X                          ; 653A
                     sta  $027c,Y                          ; 653D
                     ldx  #$00                             ; 6540
                     lda  $0d                              ; 6542
                     bpl  L6547                            ; 6544
                                                           ; 01 -> +1
                     dex                                   ; 6546

L6547                stx  $0c                              ; 6547
                     ldx  $18                              ; 6549
                     cmp  #$80                             ; 654B
                     ror  A                                ; 654D
                     clc                                   ; 654E
                     adc  $0d                              ; 654F
                     clc                                   ; 6551
                     adc  $02df,X                          ; 6552
                     sta  $02df,Y                          ; 6555
                     lda  $0c                              ; 6558
                     adc  $029d,X                          ; 655A
                     sta  $029d,Y                          ; 655D
                     ldy  #$27                             ; 6560
                     cpx  #$01                             ; 6562
                     bcc  L6568                            ; 6564
                                                           ; 02 -> +2
                     ldy  #$1f                             ; 6566

L6568                jmp  L7717                            ; 6568

L656b                lda  $42                              ; 656B
                     and  $43                              ; 656D
                     bpl  L657b                            ; 656F
                                                           ; 0A -> +10
                     lda  $22                              ; 6571
                     bne  L6578                            ; 6573
                                                           ; 03 -> +3
                     jsr  L7844                            ; 6575

L6578                lda  #$ff                             ; 6578
                     rts                                   ; 657A

L657b                lda  $21                              ; 657B
                     lsr  A                                ; 657D
                     beq  L6598                            ; 657E
                                                           ; 18 -> +24
                     ldy  #$01                             ; 6580
                     jsr  L7159                            ; 6582
                     ldy  #$02                             ; 6585
                     ldx  $43                              ; 6587
                     bpl  L658c                            ; 6589
                                                           ; 01 -> +1
                     dey                                   ; 658B

L658c                sty  $1e                              ; 658C
                     lda  $76                              ; 658E
                     and  #$10                             ; 6590
                     bne  L6598                            ; 6592
                                                           ; 04 -> +4
                     tya                                   ; 6594
                     jsr  L79eb                            ; 6595

L6598                lsr  $1e                              ; 6598
                     jsr  L6c95                            ; 659A
                     ldy  #$02                             ; 659D
                     jsr  L7159                            ; 659F
                     ldy  #$03                             ; 65A2
                     jsr  L7159                            ; 65A4
                     ldy  #$04                             ; 65A7
                     jsr  L7159                            ; 65A9
                     ldy  #$05                             ; 65AC
                     jsr  L7159                            ; 65AE
                     lda  #$20                             ; 65B1
                     sta  $01                              ; 65B3
                     lda  #$64                             ; 65B5
                     ldx  #$39                             ; 65B7
                     jsr  L7a1f                            ; 65B9
                     lda  #$70                             ; 65BC
                     jsr  L7aea                            ; 65BE
                     ldx  $1e                              ; 65C1
                     ldy  $42,X                            ; 65C3
                     sty  $0c                              ; 65C5
                     tya                                   ; 65C7
                     clc                                   ; 65C8
                     adc  $41                              ; 65C9
                     sta  $0d                              ; 65CB
                     jsr  L66c5                            ; 65CD
                     ldy  $0c                              ; 65D0
                     iny                                   ; 65D2
                     jsr  L66c5                            ; 65D3
                     ldy  $0c                              ; 65D6
                     iny                                   ; 65D8
                     iny                                   ; 65D9
                     jsr  L66c5                            ; 65DA
                     asl  ShieldSW                         ; 65DD
                     rol  $7b                              ; 65E0
                     lda  $7b                              ; 65E2
                     and  #$1f                             ; 65E4
                     cmp  #$07                             ; 65E6
                     bne  L6618                            ; 65E8
                                                           ; 2E -> +46
                     inc  $41                              ; 65EA
                     lda  $41                              ; 65EC
                     cmp  #$03                             ; 65EE
                     bcc  L660c                            ; 65F0
                                                           ; 1A -> +26
                     ldx  $1e                              ; 65F2
                     lda  #$ff                             ; 65F4
                     sta  $42,X                            ; 65F6

L65f8                ldx  #$00                             ; 65F8
                     stx  $1e                              ; 65FA
                     stx  $41                              ; 65FC
                     ldx  #$f0                             ; 65FE
                     stx  $77                              ; 6600
                     lda  $42                              ; 6602
                     bpl  L6609                            ; 6604
                                                           ; 03 -> +3
                     jsr  L7bc7                            ; 6606

L6609                jmp  L6c95                            ; 6609

L660c                inc  $0d                              ; 660C
                     ldx  $0d                              ; 660E
                     lda  #$f4                             ; 6610
                     sta  $77                              ; 6612
                     lda  #$0b                             ; 6614
                     sta  $44,X                            ; 6616

L6618                lda  $77                              ; 6618
                     bne  L6624                            ; 661A
                                                           ; 08 -> +8
                     lda  #$ff                             ; 661C
                     sta  $42                              ; 661E
                     sta  $43                              ; 6620
                     bmi  L65f8                            ; 6622
                                                           ; D4 -> 2B ->  -44

L6624                lda  $76                              ; 6624
                     and  #$07                             ; 6626
                     bne  L6656                            ; 6628
                                                           ; 2C -> +44
                     ldx  $0d                              ; 662A
                     ldy  $44,X                            ; 662C
                     bit  RotateLSW                        ; 662E
                     bpl  L6634                            ; 6631
                                                           ; 01 -> +1
                     iny                                   ; 6633

L6634                bit  RotateRSW                        ; 6634
                     bpl  L663c                            ; 6637
                                                           ; 03 -> +3
                     dey                                   ; 6639
                     bmi  L664c                            ; 663A
                                                           ; 10 -> +16

L663c                cpy  #$0b                             ; 663C
                     bcs  L664e                            ; 663E
                                                           ; 0E -> +14
                     cpy  #$01                             ; 6640
                     beq  L6648                            ; 6642
                                                           ; 04 -> +4
                     ldy  #$00                             ; 6644
                     beq  L6654                            ; 6646
                                                           ; 0C -> +12

L6648                ldy  #$0b                             ; 6648
                     bne  L6654                            ; 664A
                                                           ; 08 -> +8

L664c                ldy  #$24                             ; 664C

L664e                cpy  #$25                             ; 664E
                     bcc  L6654                            ; 6650
                                                           ; 02 -> +2
                     ldy  #$00                             ; 6652

L6654                sty  $44,X                            ; 6654

L6656                lda  #$00                             ; 6656
                     rts                                   ; 6658

L6659                lsr  $73                              ; 6659
                     lda  $22                              ; 665B
                     beq  L6680                            ; 665D
                                                           ; 21 -> +33
                     lda  $0219                            ; 665F
                     bmi  L6680                            ; 6662
                                                           ; 1C -> +28
                     beq  L6680                            ; 6664
                                                           ; 1A -> +26
                     lda  $02ef                            ; 6666
                     beq  L6680                            ; 6669
                                                           ; 15 -> +21
                     asl  ShieldSW                         ; 666B
                     ror  $73                              ; 666E
                     bpl  L6680                            ; 6670
                                                           ; 0E -> +14
                     ldy  #$57                             ; 6672
                     jsr  L7713                            ; 6674
                     lda  $76                              ; 6677
                     and  #$03                             ; 6679
                     bne  L6680                            ; 667B
                                                           ; 03 -> +3
                     dec  $02ef                            ; 667D

L6680                rts                                   ; 6680

L6681                bit  $73                              ; 6681
                     bpl  L6680                            ; 6683
                                                           ; FB -> 04 ->  -5
                     lda  $02ef                            ; 6685
                     and  #$f0                             ; 6688
                     cmp  #$60                             ; 668A
                     bcs  L6690                            ; 668C
                                                           ; 02 -> +2
                     lda  #$60                             ; 668E

L6690                pha                                   ; 6690
                     ldx  #$12                             ; 6691
                     lda  #$50                             ; 6693
                     stx  $10                              ; 6695
                     sta  $11                              ; 6697
                     ldx  #$00                             ; 6699
                     stx  $09                              ; 669B
                     stx  $0a                              ; 669D
                     stx  $12                              ; 669F
                     jsr  L6221                            ; 66A1
                     ldx  #$07                             ; 66A4
                     pla                                   ; 66A6
                     sta  $09                              ; 66A7
                     jsr  L6e96                            ; 66A9
                     lda  #$00                             ; 66AC
                     sta  $09                              ; 66AE
                     jmp  L6e96                            ; 66B0

L66b3                lda  #$06                             ; 66B3
                     sta  $02ee                            ; 66B5
                     ldx  #$00                             ; 66B8
                     txa                                   ; 66BA

L66bb                sta  $0200,X                          ; 66BB
                     sta  $0300,X                          ; 66BE
                     inx                                   ; 66C1
                     bne  L66bb                            ; 66C2
                                                           ; F7 -> 08 ->  -9
                     rts                                   ; 66C4

L66c5                lda  $0044,Y                          ; 66C5
                     asl  A                                ; 66C8
                     tay                                   ; 66C9
                     bne  L66d9                            ; 66CA
                                                           ; 0D -> +13
                     lda  $42                              ; 66CC
                     and  $43                              ; 66CE
                     bmi  L66d9                            ; 66D0
                                                           ; 07 -> +7
                     ldx  #$b0                             ; 66D2
                     lda  #$56                             ; 66D4
                     jmp  L7a18                            ; 66D6

L66d9                jmp  L79f8                            ; 66D9

L66dc                ldx  #$20                             ; 66DC
                     lda  #$00                             ; 66DE
                     sta  $19                              ; 66E0

L66e2                lda  $0200,X                          ; 66E2
                     bne  L66eb                            ; 66E5
                                                           ; 04 -> +4

L66e7                dex                                   ; 66E7
                     bpl  L66e2                            ; 66E8
                                                           ; F8 -> 07 ->  -8
                     rts                                   ; 66EA

L66eb                bpl  L6750                            ; 66EB
                                                           ; 63 -> +99
                     jsr  L70b6                            ; 66ED
                     lsr  A                                ; 66F0
                     lsr  A                                ; 66F1
                     lsr  A                                ; 66F2
                     lsr  A                                ; 66F3
                     cpx  #$19                             ; 66F4
                     bne  L66ff                            ; 66F6
                                                           ; 07 -> +7
                     lda  $76                              ; 66F8
                     and  #$01                             ; 66FA
                     lsr  A                                ; 66FC
                     beq  L6700                            ; 66FD
                                                           ; 01 -> +1

L66ff                sec                                   ; 66FF

L6700                adc  $0200,X                          ; 6700
                     bmi  L672a                            ; 6703
                                                           ; 25 -> +37
                     cpx  #$19                             ; 6705
                     beq  L671c                            ; 6707
                                                           ; 13 -> +19
                     bcs  L6722                            ; 6709
                                                           ; 17 -> +23
                     dec  $02e7                            ; 670B
                     bne  L6715                            ; 670E
                                                           ; 05 -> +5
                     ldy  #$7f                             ; 6710
                     sty  $02ec                            ; 6712

L6715                lda  #$00                             ; 6715
                     sta  $0200,X                          ; 6717
                     beq  L66e7                            ; 671A
                                                           ; CB -> 34 ->  -53

L671c                jsr  L6a1b                            ; 671C
                     jmp  L6715                            ; 671F

L6722                lda  $02e9                            ; 6722
                     sta  $02e8                            ; 6725
                     bne  L6715                            ; 6728
                                                           ; EB -> 14 ->  -21

L672a                sta  $0200,X                          ; 672A
                     and  #$f0                             ; 672D
                     clc                                   ; 672F
                     adc  #$10                             ; 6730
                     cpx  #$19                             ; 6732
                     bne  L6738                            ; 6734
                                                           ; 02 -> +2
                     lda  #$f0                             ; 6736

L6738                tay                                   ; 6738
                     lda  $02a5,X                          ; 6739
                     sta  $05                              ; 673C
                     lda  $0263,X                          ; 673E
                     sta  $06                              ; 6741
                     lda  $02c6,X                          ; 6743
                     sta  $07                              ; 6746
                     lda  $0284,X                          ; 6748
                     sta  $08                              ; 674B
                     jmp  L67e5                            ; 674D

L6750                sta  $1b                              ; 6750
                     asl  $1b                              ; 6752
                     bpl  L676b                            ; 6754
                                                           ; 15 -> +21
                     cpx  #$19                             ; 6756
                     bcs  L676b                            ; 6758
                                                           ; 11 -> +17
                     and  #$3c                             ; 675A
                     lsr  A                                ; 675C
                     lsr  A                                ; 675D
                     tay                                   ; 675E
                     sty  $1c                              ; 675F
                     lda  $02f8,Y                          ; 6761
                     sta  $1d                              ; 6764
                     bmi  L676b                            ; 6766
                                                           ; 03 -> +3
                     jsr  L48be                            ; 6768

L676b                ldy  #$00                             ; 676B
                     clc                                   ; 676D
                     lda  $0221,X                          ; 676E
                     bpl  L6774                            ; 6771
                                                           ; 01 -> +1
                     dey                                   ; 6773

L6774                adc  $02a5,X                          ; 6774
                     sta  $02a5,X                          ; 6777
                     sta  $05                              ; 677A
                     tya                                   ; 677C
                     adc  $0263,X                          ; 677D
                     cmp  #$20                             ; 6780
                     bcc  L67ae                            ; 6782
                                                           ; 2A -> +42
                     cpx  #$1a                             ; 6784
                     bne  L678e                            ; 6786
                                                           ; 06 -> +6
                     jsr  L67eb                            ; 6788

L678b                jmp  L66e7                            ; 678B

L678e                bit  $1b                              ; 678E
                     bpl  L67ac                            ; 6790
                                                           ; 1A -> +26
                     ldy  $1d                              ; 6792
                     bmi  L67ac                            ; 6794
                                                           ; 16 -> +22
                     cpy  #$04                             ; 6796
                     bcs  L67ac                            ; 6798
                                                           ; 12 -> +18
                     dec  $02e7                            ; 679A
                     dec  $02ff                            ; 679D
                     ldy  $1c                              ; 67A0
                     lda  #$00                             ; 67A2
                     sta  $0200,X                          ; 67A4
                     sta  $02f8,Y                          ; 67A7
                     beq  L678b                            ; 67AA
                                                           ; DF -> 20 ->  -33

L67ac                and  #$1f                             ; 67AC

L67ae                sta  $0263,X                          ; 67AE
                     and  #$7f                             ; 67B1
                     sta  $06                              ; 67B3
                     clc                                   ; 67B5
                     ldy  #$00                             ; 67B6
                     lda  $0242,X                          ; 67B8
                     bpl  L67be                            ; 67BB
                                                           ; 01 -> +1
                     dey                                   ; 67BD

L67be                adc  $02c6,X                          ; 67BE
                     sta  $02c6,X                          ; 67C1
                     sta  $07                              ; 67C4
                     tya                                   ; 67C6
                     adc  $0284,X                          ; 67C7
                     cmp  #$18                             ; 67CA
                     bcc  L67d6                            ; 67CC
                                                           ; 08 -> +8
                     beq  L67d4                            ; 67CE
                                                           ; 04 -> +4
                     lda  #$17                             ; 67D0
                     bne  L67d6                            ; 67D2
                                                           ; 02 -> +2

L67d4                lda  #$00                             ; 67D4

L67d6                sta  $0284,X                          ; 67D6
                     sta  $08                              ; 67D9
                     lda  $0200,X                          ; 67DB
                     and  #$03                             ; 67DE
                     tay                                   ; 67E0
                     lda  $680c,Y                          ; 67E1
                     tay                                   ; 67E4

L67e5                jsr  L6ba8                            ; 67E5
                     jmp  L66e7                            ; 67E8

L67eb                lda  $02e9                            ; 67EB
                     sta  $02e8                            ; 67EE
                     tya                                   ; 67F1
                     pha                                   ; 67F2
                     ldy  #$17                             ; 67F3
                     jsr  L770d                            ; 67F5
                     pla                                   ; 67F8
                     tay                                   ; 67F9

L67fa                lda  #$00                             ; 67FA
                     sta  $021a                            ; 67FC
                     sta  $023b                            ; 67FF
                     sta  $025c                            ; 6802
                     sta  $027d                            ; 6805
                     sta  $02bf                            ; 6808

L680b                rts                                   ; 680B
                     fcb  $00,$E0,$F0,$E0                    

L6810                lda  $22                              ; 6810
                     beq  L680b                            ; 6812
                                                           ; F7 -> 08 ->  -9
                     lda  $0219                            ; 6814
                     bmi  L680b                            ; 6817
                                                           ; F2 -> 0D ->  -14
                     bne  L6831                            ; 6819
                                                           ; 16 -> +22
                     dec  $02eb                            ; 681B
                     bne  L680b                            ; 681E
                                                           ; EB -> 14 ->  -21
                     jsr  L68fe                            ; 6820
                     bne  L680b                            ; 6823
                                                           ; E6 -> 19 ->  -26
                     ldx  #$01                             ; 6825
                     stx  $0219                            ; 6827
                     stx  $8b                              ; 682A
                     ldy  #$47                             ; 682C
                     jmp  L7716                            ; 682E

L6831                lda  RotateLSW                        ; 6831
                     bpl  L683a                            ; 6834
                                                           ; 04 -> +4
                     lda  #$03                             ; 6836
                     bne  L6841                            ; 6838
                                                           ; 07 -> +7

L683a                lda  RotateRSW                        ; 683A
                     bpl  L6846                            ; 683D
                                                           ; 07 -> +7
                     lda  #$fd                             ; 683F

L6841                clc                                   ; 6841
                     adc  $79                              ; 6842
                     sta  $79                              ; 6844

L6846                lda  $76                              ; 6846
                     lsr  A                                ; 6848
                     bcs  L680b                            ; 6849
                                                           ; C0 -> 3F ->  -64
                     lda  ThrustSW                         ; 684B
                     bpl  L6885                            ; 684E
                                                           ; 35 -> +53
                     lda  #$40                             ; 6850
                     sta  $12                              ; 6852
                     lda  $023a                            ; 6854
                     jsr  L68b6                            ; 6857
                     adc  $7c                              ; 685A
                     tax                                   ; 685C
                     lda  $11                              ; 685D
                     adc  $023a                            ; 685F
                     jsr  L68ea                            ; 6862
                     sta  $023a                            ; 6865
                     stx  $7c                              ; 6868
                     lda  #$00                             ; 686A
                     sta  $12                              ; 686C
                     lda  $025b                            ; 686E
                     jsr  L68b6                            ; 6871
                     adc  $7d                              ; 6874
                     tax                                   ; 6876
                     lda  $11                              ; 6877
                     adc  $025b                            ; 6879
                     jsr  L68ea                            ; 687C
                     sta  $025b                            ; 687F
                     stx  $7d                              ; 6882
                     rts                                   ; 6884

L6885                lda  #$00                             ; 6885
                     tax                                   ; 6887
                     sec                                   ; 6888
                     sbc  $023a                            ; 6889
                     asl  A                                ; 688C
                     asl  A                                ; 688D
                     bcc  L6892                            ; 688E
                                                           ; 02 -> +2
                     dex                                   ; 6890
                     clc                                   ; 6891

L6892                adc  $7c                              ; 6892
                     sta  $7c                              ; 6894
                     txa                                   ; 6896
                     adc  $023a                            ; 6897
                     sta  $023a                            ; 689A
                     lda  #$00                             ; 689D
                     tax                                   ; 689F
                     sec                                   ; 68A0
                     sbc  $025b                            ; 68A1
                     asl  A                                ; 68A4
                     asl  A                                ; 68A5
                     bcc  L68aa                            ; 68A6
                                                           ; 02 -> +2
                     dex                                   ; 68A8
                     clc                                   ; 68A9

L68aa                adc  $7d                              ; 68AA
                     sta  $7d                              ; 68AC
                     txa                                   ; 68AE
                     adc  $025b                            ; 68AF
                     sta  $025b                            ; 68B2
                     rts                                   ; 68B5

L68b6                bpl  L68bb                            ; 68B6
                                                           ; 03 -> +3
                     jsr  L70b6                            ; 68B8

L68bb                lsr  A                                ; 68BB
                     lsr  A                                ; 68BC
                     lsr  A                                ; 68BD
                     tax                                   ; 68BE
                     lda  $68e1,X                          ; 68BF
                     bit  $73                              ; 68C2
                     bpl  L68c7                            ; 68C4
                                                           ; 01 -> +1
                     lsr  A                                ; 68C6

L68c7                sta  $11                              ; 68C7
                     lda  $79                              ; 68C9
                     clc                                   ; 68CB
                     adc  $12                              ; 68CC
                     jsr  L7101                            ; 68CE
                     jsr  L49bb                            ; 68D1
                     ldy  #$00                             ; 68D4
                     asl  A                                ; 68D6
                     bcc  L68da                            ; 68D7
                                                           ; 01 -> +1
                     dey                                   ; 68D9

L68da                asl  A                                ; 68DA
                     sty  $11                              ; 68DB
                     rol  $11                              ; 68DD
                     clc                                   ; 68DF
                     rts                                   ; 68E0
                     fcb  $80,$70,$60,$50,$40,$30,$20,$10    
                     fcb  $11                                

L68ea                bmi  L68f5                            ; 68EA
                                                           ; 09 -> +9
                     cmp  #$40                             ; 68EC
                     bcc  L68fd                            ; 68EE
                                                           ; 0D -> +13
                     ldx  #$ff                             ; 68F0
                     lda  #$3f                             ; 68F2
                     rts                                   ; 68F4

L68f5                cmp  #$c1                             ; 68F5
                     bcs  L68fd                            ; 68F7
                                                           ; 04 -> +4
                     ldx  #$01                             ; 68F9
                     lda  #$c1                             ; 68FB

L68fd                rts                                   ; 68FD

L68fe                lda  $76                              ; 68FE
                     and  #$03                             ; 6900
                     bne  L6929                            ; 6902
                                                           ; 25 -> +37
                     inc  $de                              ; 6904
                     bne  L6929                            ; 6906
                                                           ; 21 -> +33
                     lda  #$02                             ; 6908
                     sta  $10                              ; 690A

L690c                ldx  #$18                             ; 690C

L690e                lda  $0200,X                          ; 690E
                     asl  A                                ; 6911
                     bmi  L6922                            ; 6912
                                                           ; 0E -> +14
                     and  $10                              ; 6914
                     beq  L6922                            ; 6916
                                                           ; 0A -> +10
                     dec  $02e7                            ; 6918
                     lda  #$00                             ; 691B
                     sta  $0200,X                          ; 691D
                     beq  L6929                            ; 6920
                                                           ; 07 -> +7

L6922                dex                                   ; 6922
                     bpl  L690e                            ; 6923
                                                           ; E9 -> 16 ->  -23
                     asl  $10                              ; 6925
                     bpl  L690c                            ; 6927
                                                           ; E3 -> 1C ->  -29

L6929                ldx  #$18                             ; 6929

L692b                lda  $0200,X                          ; 692B
                     beq  L694e                            ; 692E
                                                           ; 1E -> +30
                     lda  $0263,X                          ; 6930
                     sec                                   ; 6933
                     sbc  $027c                            ; 6934
                     cmp  #$05                             ; 6937
                     bcc  L693f                            ; 6939
                                                           ; 04 -> +4
                     cmp  #$fb                             ; 693B
                     bcc  L694e                            ; 693D
                                                           ; 0F -> +15

L693f                lda  $0284,X                          ; 693F
                     sec                                   ; 6942
                     sbc  $029d                            ; 6943
                     cmp  #$05                             ; 6946
                     bcc  L6953                            ; 6948
                                                           ; 09 -> +9
                     cmp  #$fb                             ; 694A
                     bcs  L6953                            ; 694C
                                                           ; 05 -> +5

L694e                dex                                   ; 694E
                     bpl  L692b                            ; 694F
                                                           ; DA -> 25 ->  -38
                     inx                                   ; 6951
                     rts                                   ; 6952

L6953                inc  $02eb                            ; 6953

L6956                rts                                   ; 6956
                     fcb  $1C,$10                            

L6959                ldx  #$18                             ; 6959
                     lda  $02ec                            ; 695B
                     beq  L6963                            ; 695E
                                                           ; 03 -> +3
                     jmp  L69de                            ; 6960

L6963                lda  $22                              ; 6963
                     beq  L696e                            ; 6965
                                                           ; 07 -> +7
                     lda  $0219                            ; 6967
                     beq  L6956                            ; 696A
                                                           ; EA -> 15 ->  -22
                     bmi  L6956                            ; 696C
                                                           ; E8 -> 17 ->  -24

L696e                lda  $021a                            ; 696E
                     bne  L6956                            ; 6971
                                                           ; E3 -> 1C ->  -29
                     sta  $02ff                            ; 6973
                     ldx  $1e                              ; 6976
                     sta  $d1,X                            ; 6978
                     ldx  #$06                             ; 697A

L697c                sta  $02f8,X                          ; 697C
                     dex                                   ; 697F
                     bpl  L697c                            ; 6980
                                                           ; FA -> 05 ->  -6
                     lda  Option65                         ; 6982
                     and  #$02                             ; 6985
                     ora  #$04                             ; 6987
                     clc                                   ; 6989
                     adc  $02f0                            ; 698A
                     tay                                   ; 698D
                     cmp  #$0a                             ; 698E
                     bcc  L6994                            ; 6990
                                                           ; 02 -> +2
                     lda  #$0a                             ; 6992

L6994                sta  $d9                              ; 6994
                     jsr  L70b6                            ; 6996
                     sta  $db                              ; 6999
                     clc                                   ; 699B
                     adc  #$eb                             ; 699C
                     sta  $dc                              ; 699E
                     jsr  L70b6                            ; 69A0
                     sta  $da                              ; 69A3
                     cpy  #$3f                             ; 69A5
                     bcc  L69b0                            ; 69A7
                                                           ; 07 -> +7
                     lda  $22                              ; 69A9
                     bne  L69b3                            ; 69AB
                                                           ; 06 -> +6
                     jsr  L66b3                            ; 69AD

L69b0                inc  $02f0                            ; 69B0

L69b3                cpy  #$09                             ; 69B3
                     bcc  L69b9                            ; 69B5
                                                           ; 02 -> +2
                     ldy  #$09                             ; 69B7

L69b9                sty  $02e7                            ; 69B9
                     sty  $09                              ; 69BC
                     ldx  #$18                             ; 69BE
                     lda  $02ee                            ; 69C0
                     cmp  #$0a                             ; 69C3
                     bcs  L69ca                            ; 69C5
                                                           ; 03 -> +3
                     inc  $02ee                            ; 69C7

L69ca                ldy  #$1a                             ; 69CA

L69cc                jsr  L69e7                            ; 69CC
                     dex                                   ; 69CF
                     dec  $09                              ; 69D0
                     bne  L69cc                            ; 69D2
                                                           ; F8 -> 07 ->  -8
                     lda  #$7f                             ; 69D4
                     sta  $02e8                            ; 69D6
                     lda  #$30                             ; 69D9
                     sta  $02ed                            ; 69DB

L69de                lda  #$00                             ; 69DE

L69e0                sta  $0200,X                          ; 69E0
                     dex                                   ; 69E3
                     bpl  L69e0                            ; 69E4
                                                           ; FA -> 05 ->  -6
                     rts                                   ; 69E6

L69e7                lda  Pk_SkRes_Rnd                     ; 69E7
                     and  #$38                             ; 69EA
                     ora  #$04                             ; 69EC
                     sta  $0200,X                          ; 69EE
                     jsr  L6a3b                            ; 69F1
                     lda  Pk_SkRes_Rnd                     ; 69F4
                     lsr  A                                ; 69F7
                     and  #$1f                             ; 69F8
                     bcc  L6a0f                            ; 69FA
                                                           ; 13 -> +19
                     cmp  #$18                             ; 69FC
                     bcc  L6a02                            ; 69FE
                                                           ; 02 -> +2
                     and  #$17                             ; 6A00

L6a02                sta  $0284,X                          ; 6A02
                     lda  #$00                             ; 6A05
                     sta  $0263,X                          ; 6A07
                     sta  $02a5,X                          ; 6A0A
                     beq  L6a1a                            ; 6A0D
                                                           ; 0B -> +11

L6a0f                sta  $0263,X                          ; 6A0F
                     lda  #$00                             ; 6A12
                     sta  $0284,X                          ; 6A14
                     sta  $02c6,X                          ; 6A17

L6a1a                rts                                   ; 6A1A

L6a1b                lda  #$60                             ; 6A1B
                     sta  $02be                            ; 6A1D
                     sta  $02df                            ; 6A20
                     lda  #$00                             ; 6A23
                     sta  $023a                            ; 6A25
                     sta  $025b                            ; 6A28
                     lda  #$10                             ; 6A2B
                     sta  $027c                            ; 6A2D
                     lda  #$0c                             ; 6A30
                     sta  $029d                            ; 6A32
                     lda  #$ff                             ; 6A35
                     sta  $02ef                            ; 6A37
                     rts                                   ; 6A3A

L6a3b                lda  Pk_SkRes_Rnd                     ; 6A3B
                     and  #$8f                             ; 6A3E
                     bpl  L6a44                            ; 6A40
                                                           ; 02 -> +2
                     ora  #$f0                             ; 6A42

L6a44                clc                                   ; 6A44
                     adc  $0221,Y                          ; 6A45
                     jsr  L6a62                            ; 6A48
                     sta  $0221,X                          ; 6A4B
                     lda  Pk_SkRes_Rnd                     ; 6A4E
                     and  #$8f                             ; 6A51
                     bpl  L6a57                            ; 6A53
                                                           ; 02 -> +2
                     ora  #$f0                             ; 6A55

L6a57                clc                                   ; 6A57
                     adc  $0242,Y                          ; 6A58
                     jsr  L6a62                            ; 6A5B
                     sta  $0242,X                          ; 6A5E
                     rts                                   ; 6A61

L6a62                bpl  L6a71                            ; 6A62
                                                           ; 0D -> +13
                     cmp  $dc                              ; 6A64
                     bcs  L6a6a                            ; 6A66
                                                           ; 02 -> +2
                     lda  $dc                              ; 6A68

L6a6a                cmp  $db                              ; 6A6A
                     bcc  L6a7d                            ; 6A6C
                                                           ; 0F -> +15
                     lda  $db                              ; 6A6E
                     rts                                   ; 6A70

L6a71                cmp  $d9                              ; 6A71
                     bcs  L6a77                            ; 6A73
                                                           ; 02 -> +2
                     lda  $d9                              ; 6A75

L6a77                cmp  $da                              ; 6A77
                     bcc  L6a7d                            ; 6A79
                                                           ; 02 -> +2
                     lda  $da                              ; 6A7B

L6a7d                rts                                   ; 6A7D

L6a7e                lda  $22                              ; 6A7E
                     beq  L6a8f                            ; 6A80
                                                           ; 0D -> +13
                     lda  #$81                             ; 6A82
                     ldx  #$c3                             ; 6A84
                     jsr  L7cd5                            ; 6A86
                     ldy  #$00                             ; 6A89
                     lda  $1e                              ; 6A8B
                     bne  L6a91                            ; 6A8D
                                                           ; 02 -> +2

L6a8f                ldy  #$10                             ; 6A8F

L6a91                sty  $01                              ; 6A91
                     lda  #$19                             ; 6A93
                     ldx  #$db                             ; 6A95
                     jsr  L7a1f                            ; 6A97
                     lda  #$70                             ; 6A9A
                     jsr  L7aea                            ; 6A9C
                     lda  $22                              ; 6A9F
                     cmp  #$02                             ; 6AA1
                     bcc  L6ab9                            ; 6AA3
                                                           ; 14 -> +20
                     lda  $1e                              ; 6AA5
                     bne  L6ab9                            ; 6AA7
                                                           ; 10 -> +16
                     lda  $0219                            ; 6AA9
                     bne  L6ab9                            ; 6AAC
                                                           ; 0B -> +11
                     lda  $02eb                            ; 6AAE
                     bmi  L6ab9                            ; 6AB1
                                                           ; 06 -> +6
                     lda  $76                              ; 6AB3
                     and  #$10                             ; 6AB5
                     beq  L6ac1                            ; 6AB7
                                                           ; 08 -> +8

L6ab9                lda  #$62                             ; 6AB9
                     ldy  #$03                             ; 6ABB
                     sec                                   ; 6ABD
                     jsr  L7c95                            ; 6ABE

L6ac1                ldy  $6f                              ; 6AC1
                     lda  #$00                             ; 6AC3
                     jsr  L6b74                            ; 6AC5
                     lda  #$28                             ; 6AC8
                     jsr  L7c6f                            ; 6ACA
                     lda  $1e                              ; 6ACD
                     bne  L6adb                            ; 6ACF
                                                           ; 0A -> +10
                     lda  $0219                            ; 6AD1
                     bmi  L6adb                            ; 6AD4
                                                           ; 05 -> +5
                     beq  L6adb                            ; 6AD6
                                                           ; 03 -> +3
                     jsr  L6b89                            ; 6AD8

L6adb                lda  #$00                             ; 6ADB
                     sta  $01                              ; 6ADD
                     ora  $24                              ; 6ADF
                     ora  $25                              ; 6AE1
                     beq  L6b03                            ; 6AE3
                                                           ; 1E -> +30
                     lda  #$74                             ; 6AE5
                     ldx  #$db                             ; 6AE7
                     jsr  L7a1f                            ; 6AE9
                     lda  #$50                             ; 6AEC
                     jsr  L7aea                            ; 6AEE
                     lda  #$23                             ; 6AF1
                     ldy  #$03                             ; 6AF3
                     sec                                   ; 6AF5
                     jsr  L7c95                            ; 6AF6
                     ldy  #$00                             ; 6AF9
                     sty  $13                              ; 6AFB
                     jsr  L79f8                            ; 6AFD
                     jsr  L6d42                            ; 6B00

L6b03                lda  $22                              ; 6B03
                     beq  L6b1d                            ; 6B05
                                                           ; 16 -> +22
                     lda  $f9                              ; 6B07
                     bmi  L6b1d                            ; 6B09
                                                           ; 12 -> +18
                     ldy  #$0d                             ; 6B0B
                     lda  #$00                             ; 6B0D
                     jsr  L7162                            ; 6B0F
                     lda  #$68                             ; 6B12
                     clc                                   ; 6B14
                     adc  $20                              ; 6B15
                     ldy  #$03                             ; 6B17
                     sec                                   ; 6B19
                     jsr  L7c95                            ; 6B1A

L6b1d                ldx  #$10                             ; 6B1D
                     lda  $22                              ; 6B1F
                     cmp  #$01                             ; 6B21
                     beq  L6b88                            ; 6B23
                                                           ; 63 -> +99
                     bcc  L6b2c                            ; 6B25
                                                           ; 05 -> +5
                     lda  $1e                              ; 6B27
                     bne  L6b2c                            ; 6B29
                                                           ; 01 -> +1
                     tax                                   ; 6B2B

L6b2c                stx  $01                              ; 6B2C
                     lda  #$c0                             ; 6B2E
                     ldx  #$db                             ; 6B30
                     jsr  L7a1f                            ; 6B32
                     lda  #$50                             ; 6B35
                     jsr  L7aea                            ; 6B37
                     lda  $22                              ; 6B3A
                     beq  L6b52                            ; 6B3C
                                                           ; 14 -> +20
                     lda  $1e                              ; 6B3E
                     beq  L6b52                            ; 6B40
                                                           ; 10 -> +16
                     lda  $0219                            ; 6B42
                     bne  L6b52                            ; 6B45
                                                           ; 0B -> +11
                     lda  $02eb                            ; 6B47
                     bmi  L6b52                            ; 6B4A
                                                           ; 06 -> +6
                     lda  $76                              ; 6B4C
                     and  #$10                             ; 6B4E
                     beq  L6b5a                            ; 6B50
                                                           ; 08 -> +8

L6b52                lda  #$65                             ; 6B52
                     ldy  #$03                             ; 6B54
                     sec                                   ; 6B56
                     jsr  L7c95                            ; 6B57

L6b5a                ldy  $70                              ; 6B5A
                     lda  #$01                             ; 6B5C
                     jsr  L6b74                            ; 6B5E
                     lda  #$cf                             ; 6B61
                     jsr  L7c6f                            ; 6B63
                     lda  $1e                              ; 6B66
                     beq  L6b88                            ; 6B68
                                                           ; 1E -> +30
                     lda  $0219                            ; 6B6A
                     beq  L6b88                            ; 6B6D
                                                           ; 19 -> +25
                     bmi  L6b88                            ; 6B6F
                                                           ; 17 -> +23
                     jmp  L6b89                            ; 6B71

L6b74                eor  $1e                              ; 6B74
                     beq  L6b81                            ; 6B76
                                                           ; 09 -> +9
                     ldx  $0319                            ; 6B78
                     bmi  L6b7f                            ; 6B7B
                                                           ; 02 -> +2
                     bne  L6b80                            ; 6B7D
                                                           ; 01 -> +1

L6b7f                iny                                   ; 6B7F

L6b80                rts                                   ; 6B80

L6b81                ldx  $0219                            ; 6B81
                     beq  L6b7f                            ; 6B84
                                                           ; F9 -> 06 ->  -7
                     bmi  L6b7f                            ; 6B86
                                                           ; F7 -> 08 ->  -9

L6b88                rts                                   ; 6B88

L6b89                lda  $8b                              ; 6B89
                     cmp  #$c0                             ; 6B8B
                     bcc  L6b90                            ; 6B8D
                                                           ; 01 -> +1
                     rts                                   ; 6B8F

L6b90                pha                                   ; 6B90
                     eor  #$ff                             ; 6B91
                     adc  #$c1                             ; 6B93
                     sta  $8b                              ; 6B95
                     lda  $79                              ; 6B97
                     pha                                   ; 6B99
                     lda  #$40                             ; 6B9A
                     sta  $79                              ; 6B9C
                     jsr  L6e20                            ; 6B9E
                     pla                                   ; 6BA1
                     sta  $79                              ; 6BA2
                     pla                                   ; 6BA4
                     sta  $8b                              ; 6BA5
                     rts                                   ; 6BA7

L6ba8                sty  $01                              ; 6BA8
                     stx  $0e                              ; 6BAA
                     lsr  $06                              ; 6BAC
                     ror  $05                              ; 6BAE
                     lsr  $06                              ; 6BB0
                     ror  $05                              ; 6BB2
                     lsr  $06                              ; 6BB4
                     ror  $05                              ; 6BB6
                     lsr  $08                              ; 6BB8
                     ror  $07                              ; 6BBA
                     lsr  $08                              ; 6BBC
                     ror  $07                              ; 6BBE
                     inc  $08                              ; 6BC0
                     lsr  $08                              ; 6BC2
                     ror  $07                              ; 6BC4
                     jsr  L6c27                            ; 6BC6
                     ldx  $0e                              ; 6BC9
                     jsr  L6bd1                            ; 6BCB
                     ldx  $0e                              ; 6BCE
                     rts                                   ; 6BD0

L6bd1                lda  $0200,X                          ; 6BD1
                     bpl  L6be9                            ; 6BD4
                                                           ; 13 -> +19
                     cpx  #$19                             ; 6BD6
                     beq  L6be6                            ; 6BD8
                                                           ; 0C -> +12
                     and  #$0c                             ; 6BDA
                     lsr  A                                ; 6BDC
                     tay                                   ; 6BDD
                     lda  $4d80,Y                          ; 6BDE
                     ldx  $4d81,Y                          ; 6BE1
                     bne  L6c05                            ; 6BE4
                                                           ; 1F -> +31

L6be6                jmp  L6d5b                            ; 6BE6

L6be9                cpx  #$19                             ; 6BE9
                     beq  L6c08                            ; 6BEB
                                                           ; 1B -> +27
                     cpx  #$1a                             ; 6BED
                     beq  L6c0e                            ; 6BEF
                                                           ; 1D -> +29
                     bcs  L6c14                            ; 6BF1
                                                           ; 21 -> +33
                     asl  A                                ; 6BF3
                     bpl  L6bf9                            ; 6BF4
                                                           ; 03 -> +3
                     jmp  L4a75                            ; 6BF6

L6bf9                lsr  A                                ; 6BF9
                     lsr  A                                ; 6BFA
                     lsr  A                                ; 6BFB
                     and  #$06                             ; 6BFC
                     tay                                   ; 6BFE
                     lda  $779d,Y                          ; 6BFF
                     ldx  $779e,Y                          ; 6C02

L6c05                jmp  L7cd5                            ; 6C05

L6c08                jsr  L6681                            ; 6C08
                     jmp  L6e20                            ; 6C0B

L6c0e                lda  #$34                             ; 6C0E
                     ldx  #$c7                             ; 6C10
                     bne  L6c05                            ; 6C12
                                                           ; F1 -> 0E ->  -15

L6c14                lda  #$70                             ; 6C14
                     ldx  #$f0                             ; 6C16
                     jsr  L7aec                            ; 6C18
                     ldx  $0e                              ; 6C1B
                     lda  $76                              ; 6C1D
                     and  #$03                             ; 6C1F
                     bne  L6c26                            ; 6C21
                                                           ; 03 -> +3
                     dec  $0200,X                          ; 6C23

L6c26                rts                                   ; 6C26

L6c27                ldx  #$05                             ; 6C27
                     jsr  L7a38                            ; 6C29
                     lda  #$70                             ; 6C2C
                     sec                                   ; 6C2E
                     sbc  $01                              ; 6C2F

L6c31                cmp  #$a0                             ; 6C31
                     bcc  L6c41                            ; 6C33
                                                           ; 0C -> +12
                     pha                                   ; 6C35
                     lda  #$90                             ; 6C36
                     jsr  L7aea                            ; 6C38
                     pla                                   ; 6C3B
                     sec                                   ; 6C3C
                     sbc  #$10                             ; 6C3D
                     bne  L6c31                            ; 6C3F
                                                           ; F0 -> 0F ->  -16

L6c41                jmp  L7aea                            ; 6C41

L6c44                ror  A                                ; 6C44
                     ror  $10                              ; 6C45
                     lsr  A                                ; 6C47
                     ror  $10                              ; 6C48
                     lsr  A                                ; 6C4A
                     ror  $10                              ; 6C4B
                     lsr  A                                ; 6C4D
                     ror  $10                              ; 6C4E
                     sta  $11                              ; 6C50
                     sed                                   ; 6C52
                     stx  $12                              ; 6C53
                     ldx  $20                              ; 6C55
                     lda  $10                              ; 6C57
                     and  #$f0                             ; 6C59
                     clc                                   ; 6C5B
                     adc  $62,X                            ; 6C5C
                     sta  $62,X                            ; 6C5E
                     lda  $11                              ; 6C60
                     adc  $63,X                            ; 6C62
                     sta  $63,X                            ; 6C64
                     lda  #$00                             ; 6C66
                     adc  $64,X                            ; 6C68
                     sta  $64,X                            ; 6C6A
                     cmp  $6a,X                            ; 6C6C
                     bcc  L6c91                            ; 6C6E
                                                           ; 21 -> +33
                     bne  L6c78                            ; 6C70
                                                           ; 06 -> +6
                     lda  $63,X                            ; 6C72
                     cmp  $69,X                            ; 6C74
                     bcc  L6c91                            ; 6C76
                                                           ; 19 -> +25

L6c78                clc                                   ; 6C78
                     lda  $f8                              ; 6C79
                     adc  $69,X                            ; 6C7B
                     sta  $69,X                            ; 6C7D
                     lda  $f9                              ; 6C7F
                     adc  $6a,X                            ; 6C81
                     sta  $6a,X                            ; 6C83
                     ldx  $1e                              ; 6C85
                     lda  $6f,X                            ; 6C87
                     cmp  #$0a                             ; 6C89
                     bcs  L6c91                            ; 6C8B
                                                           ; 04 -> +4
                     inc  $6f,X                            ; 6C8D
                     inc  $7e                              ; 6C8F

L6c91                cld                                   ; 6C91
                     ldx  $12                              ; 6C92
                     rts                                   ; 6C94

L6c95                lda  $1e                              ; 6C95
                     lsr  A                                ; 6C97
                     ror  A                                ; 6C98
                     sta  BankSel                          ; 6C99
                     rts                                   ; 6C9C

L6c9d                ldx  $22                              ; 6C9D
                     bne  L6cbd                            ; 6C9F
                                                           ; 1C -> +28
                     lda  $77                              ; 6CA1
                     and  #$04                             ; 6CA3
                     beq  L6cbf                            ; 6CA5
                                                           ; 18 -> +24

L6ca7                stx  $01                              ; 6CA7
                     lda  #$70                             ; 6CA9
                     ldx  #$68                             ; 6CAB
                     jsr  L7a1f                            ; 6CAD
                     lda  #$70                             ; 6CB0
                     jsr  L7aea                            ; 6CB2
                     jsr  L7148                            ; 6CB5
                     ldy  #$07                             ; 6CB8
                     jsr  L7159                            ; 6CBA

L6cbd                clc                                   ; 6CBD
                     rts                                   ; 6CBE

L6cbf                lda  $23                              ; 6CBF
                     ora  $24                              ; 6CC1
                     ora  $25                              ; 6CC3
                     beq  L6ca7                            ; 6CC5
                                                           ; E0 -> 1F ->  -32
                     ldy  #$00                             ; 6CC7
                     jsr  L7159                            ; 6CC9
                     ldx  #$00                             ; 6CCC
                     stx  $10                              ; 6CCE
                     stx  $13                              ; 6CD0
                     lda  #$a7                             ; 6CD2
                     sta  $12                              ; 6CD4
                     ldx  #$23                             ; 6CD6

L6cd8                lda  #$10                             ; 6CD8
                     sta  $01                              ; 6CDA
                     stx  $11                              ; 6CDC
                     lda  $00,X                            ; 6CDE
                     ora  $01,X                            ; 6CE0
                     ora  $02,X                            ; 6CE2
                     beq  L6d40                            ; 6CE4
                                                           ; 5A -> +90
                     lda  #$5f                             ; 6CE6
                     ldx  $12                              ; 6CE8
                     jsr  L7a1f                            ; 6CEA
                     lda  #$40                             ; 6CED
                     jsr  L7aea                            ; 6CEF
                     lda  $10                              ; 6CF2
                     sed                                   ; 6CF4
                     clc                                   ; 6CF5
                     adc  #$01                             ; 6CF6
                     cld                                   ; 6CF8
                     sta  $10                              ; 6CF9
                     lda  #$10                             ; 6CFB
                     sec                                   ; 6CFD
                     ldy  #$01                             ; 6CFE
                     jsr  L7c95                            ; 6D00
                     lda  #$40                             ; 6D03
                     tax                                   ; 6D05
                     jsr  L7aec                            ; 6D06
                     ldy  #$00                             ; 6D09
                     jsr  L79f8                            ; 6D0B
                     lda  $11                              ; 6D0E
                     ldy  #$03                             ; 6D10
                     sec                                   ; 6D12
                     jsr  L7c95                            ; 6D13
                     ldy  #$00                             ; 6D16
                     jsr  L79f8                            ; 6D18
                     jsr  L6d42                            ; 6D1B
                     lda  $10                              ; 6D1E
                     cmp  #$04                             ; 6D20
                     bcs  L6d30                            ; 6D22
                                                           ; 0C -> +12
                     lda  $12                              ; 6D24
                     adc  #$02                             ; 6D26
                     tax                                   ; 6D28
                     lda  #$b2                             ; 6D29
                     ldy  #$02                             ; 6D2B
                     jsr  L7c71                            ; 6D2D

L6d30                lda  $12                              ; 6D30
                     sec                                   ; 6D32
                     sbc  #$08                             ; 6D33
                     sta  $12                              ; 6D35
                     ldx  $11                              ; 6D37
                     inx                                   ; 6D39
                     inx                                   ; 6D3A
                     inx                                   ; 6D3B
                     cpx  #$41                             ; 6D3C
                     bcc  L6cd8                            ; 6D3E
                                                           ; 98 -> 67 ->  -104

L6d40                sec                                   ; 6D40
                     rts                                   ; 6D41

L6d42                jsr  L6d48                            ; 6D42
                     jsr  L6d48                            ; 6D45

L6d48                ldy  $13                              ; 6D48
                     jsr  L66c5                            ; 6D4A
                     inc  $13                              ; 6D4D
                     rts                                   ; 6D4F

L6d50                ldx  #$18                             ; 6D50

L6d52                lda  $0200,X                          ; 6D52
                     beq  L6d5a                            ; 6D55
                                                           ; 03 -> +3
                     dex                                   ; 6D57
                     bpl  L6d52                            ; 6D58
                                                           ; F8 -> 07 ->  -8

L6d5a                rts                                   ; 6D5A

L6d5b                lda  $0219                            ; 6D5B
                     cmp  #$a2                             ; 6D5E
                     bcs  L6d9d                            ; 6D60
                                                           ; 3B -> +59
                     ldx  #$07                             ; 6D62

L6d64                lda  Pk_SkRes_Rnd                     ; 6D64
                     and  #$07                             ; 6D67
                     eor  $05                              ; 6D69
                     asl  A                                ; 6D6B
                     sta  $0100,X                          ; 6D6C
                     lda  $06                              ; 6D6F
                     rol  A                                ; 6D71
                     sta  $0110,X                          ; 6D72
                     lda  Pk_SkRes_Rnd                     ; 6D75
                     and  #$07                             ; 6D78
                     eor  $07                              ; 6D7A
                     asl  A                                ; 6D7C
                     sta  $0108,X                          ; 6D7D
                     lda  $08                              ; 6D80
                     rol  A                                ; 6D82
                     sta  $0118,X                          ; 6D83
                     lda  Pk_SkRes_Rnd                     ; 6D86
                     and  #$0f                             ; 6D89
                     adc  #$f8                             ; 6D8B
                     sta  $0120,X                          ; 6D8D
                     jsr  L6e15                            ; 6D90
                     sta  $df,X                            ; 6D93
                     jsr  L6e15                            ; 6D95
                     sta  $e7,X                            ; 6D98
                     dex                                   ; 6D9A
                     bpl  L6d64                            ; 6D9B
                                                           ; C7 -> 38 ->  -57

L6d9d                lda  #$07                             ; 6D9D
                     sta  $12                              ; 6D9F
                     sta  $15                              ; 6DA1

L6da3                ldx  $15                              ; 6DA3
                     lda  $0219                            ; 6DA5
                     jsr  L70b6                            ; 6DA8
                     and  #$f0                             ; 6DAB
                     adc  #$60                             ; 6DAD
                     sta  $09                              ; 6DAF
                     lda  $ef,X                            ; 6DB1
                     adc  $0120,X                          ; 6DB3
                     sta  $ef,X                            ; 6DB6
                     lsr  A                                ; 6DB8
                     lsr  A                                ; 6DB9
                     pha                                   ; 6DBA
                     lsr  A                                ; 6DBB
                     lsr  A                                ; 6DBC
                     lsr  A                                ; 6DBD
                     and  #$04                             ; 6DBE
                     sta  $0a                              ; 6DC0
                     ora  $09                              ; 6DC2
                     sta  $09                              ; 6DC4
                     jsr  L6df6                            ; 6DC6
                     sta  $06                              ; 6DC9
                     lda  $07                              ; 6DCB
                     sta  $05                              ; 6DCD
                     txa                                   ; 6DCF
                     clc                                   ; 6DD0
                     adc  #$08                             ; 6DD1
                     tax                                   ; 6DD3
                     jsr  L6df6                            ; 6DD4
                     jsr  L6c27                            ; 6DD7
                     pla                                   ; 6DDA
                     and  #$1e                             ; 6DDB
                     tax                                   ; 6DDD
                     lda  $506a,X                          ; 6DDE
                     asl  A                                ; 6DE1
                     sta  $10                              ; 6DE2
                     lda  $506b,X                          ; 6DE4
                     rol  A                                ; 6DE7
                     eor  #$c0                             ; 6DE8
                     sta  $11                              ; 6DEA
                     ldx  #$00                             ; 6DEC
                     jsr  L6221                            ; 6DEE
                     dec  $15                              ; 6DF1
                     bpl  L6da3                            ; 6DF3
                                                           ; AE -> 51 ->  -82
                     rts                                   ; 6DF5

L6df6                ldy  #$00                             ; 6DF6
                     lda  $df,X                            ; 6DF8
                     bpl  L6dfd                            ; 6DFA
                                                           ; 01 -> +1
                     dey                                   ; 6DFC

L6dfd                clc                                   ; 6DFD
                     adc  $0100,X                          ; 6DFE
                     sta  $0100,X                          ; 6E01
                     sta  $07                              ; 6E04
                     tya                                   ; 6E06
                     adc  $0110,X                          ; 6E07
                     and  #$07                             ; 6E0A
                     sta  $0110,X                          ; 6E0C
                     lsr  A                                ; 6E0F
                     sta  $08                              ; 6E10
                     ror  $07                              ; 6E12
                     rts                                   ; 6E14

L6e15                lda  Pk_SkRes_Rnd                     ; 6E15
                     and  #$07                             ; 6E18
                     clc                                   ; 6E1A
                     adc  #$fc                             ; 6E1B
                     adc  #$00                             ; 6E1D
                     rts                                   ; 6E1F

L6e20                lda  $8b                              ; 6E20
                     cmp  #$c0                             ; 6E22
                     bcs  L6e70                            ; 6E24
                                                           ; 4A -> +74
                     adc  #$06                             ; 6E26
                     sta  $8b                              ; 6E28
                     lda  Pk_SkRes_Rnd                     ; 6E2A
                     and  #$04                             ; 6E2D
                     sta  $09                              ; 6E2F
                     lda  Pk_SkRes_Rnd                     ; 6E31
                     and  #$04                             ; 6E34
                     sta  $0a                              ; 6E36
                     lda  Pk_SkRes_Rnd                     ; 6E38
                     and  #$80                             ; 6E3B
                     sta  $12                              ; 6E3D
                     lda  #$09                             ; 6E3F
                     sta  $15                              ; 6E41
                     lda  #$4d                             ; 6E43
                     ldx  #$87                             ; 6E45
                     sta  $11                              ; 6E47
                     stx  $10                              ; 6E49
                     ldy  #$00                             ; 6E4B
                     ldx  #$00                             ; 6E4D

L6e4f                jsr  L6e96                            ; 6E4F
                     lda  Pk_SkRes_Rnd                     ; 6E52
                     lsr  A                                ; 6E55
                     lda  #$00                             ; 6E56
                     bcc  L6e5c                            ; 6E58
                                                           ; 02 -> +2
                     lda  #$70                             ; 6E5A

L6e5c                ora  $09                              ; 6E5C
                     sta  $09                              ; 6E5E
                     jsr  L6e96                            ; 6E60
                     lda  $09                              ; 6E63
                     and  #$04                             ; 6E65
                     sta  $09                              ; 6E67
                     dec  $15                              ; 6E69
                     bpl  L6e4f                            ; 6E6B
                                                           ; E2 -> 1D ->  -30
                     jsr  L6e96                            ; 6E6D

L6e70                jsr  L6ea5                            ; 6E70
                     jsr  L6221                            ; 6E73
                     lda  $8b                              ; 6E76
                     and  #$f0                             ; 6E78
                     cmp  #$60                             ; 6E7A
                     bcs  L6e80                            ; 6E7C
                                                           ; 02 -> +2
                     lda  #$60                             ; 6E7E

L6e80                ora  $09                              ; 6E80
                     sta  $09                              ; 6E82
                     ldx  #$07                             ; 6E84
                     jsr  L6e96                            ; 6E86
                     bit  ThrustSW                         ; 6E89
                     bpl  L6ec5                            ; 6E8C
                                                           ; 37 -> +55
                     lda  $76                              ; 6E8E
                     and  #$04                             ; 6E90
                     beq  L6ec5                            ; 6E92
                                                           ; 31 -> +49
                     ldx  #$01                             ; 6E94

L6e96                tya                                   ; 6E96
                     sec                                   ; 6E97
                     adc  $10                              ; 6E98
                     sta  $10                              ; 6E9A
                     lda  #$00                             ; 6E9C
                     adc  $11                              ; 6E9E
                     sta  $11                              ; 6EA0
                     jmp  L6221                            ; 6EA2

L6ea5                lda  $79                              ; 6EA5
                     sec                                   ; 6EA7
                     sbc  #$40                             ; 6EA8
                     jsr  L6ec6                            ; 6EAA
                     tya                                   ; 6EAD
                     lsr  A                                ; 6EAE
                     tay                                   ; 6EAF
                     ldx  #$53                             ; 6EB0
                     lda  $53bc,Y                          ; 6EB2
                     asl  A                                ; 6EB5
                     bcc  L6eba                            ; 6EB6
                                                           ; 02 -> +2
                     inx                                   ; 6EB8
                     clc                                   ; 6EB9

L6eba                adc  #$c6                             ; 6EBA
                     sta  $10                              ; 6EBC
                     txa                                   ; 6EBE
                     adc  #$00                             ; 6EBF
                     sta  $11                              ; 6EC1
                     ldx  #$00                             ; 6EC3

L6ec5                rts                                   ; 6EC5

L6ec6                lsr  A                                ; 6EC6
                     sta  $10                              ; 6EC7
                     lsr  A                                ; 6EC9
                     lsr  A                                ; 6ECA
                     lsr  A                                ; 6ECB
                     lsr  A                                ; 6ECC
                     tay                                   ; 6ECD
                     lda  $6eee,Y                          ; 6ECE
                     asl  A                                ; 6ED1
                     sta  $12                              ; 6ED2
                     lda  $10                              ; 6ED4
                     and  #$0e                             ; 6ED6
                     bcc  L6ede                            ; 6ED8
                                                           ; 04 -> +4
                     eor  #$0e                             ; 6EDA
                     adc  #$01                             ; 6EDC

L6ede                tay                                   ; 6EDE
                     lda  $12                              ; 6EDF
                     and  #$04                             ; 6EE1
                     sta  $09                              ; 6EE3
                     asl  $12                              ; 6EE5
                     lda  $12                              ; 6EE7
                     and  #$04                             ; 6EE9
                     sta  $0a                              ; 6EEB
                     rts                                   ; 6EED
                     fcb  $00,$A3,$22,$81,$03,$A0,$21,$82    

L6ef6                lsr  $10                              ; 6EF6
                     ldx  $22                              ; 6EF8
                     beq  L6f55                            ; 6EFA
                                                           ; 59 -> +89
                     ldx  $a2                              ; 6EFC
                     bne  L6f18                            ; 6EFE
                                                           ; 18 -> +24
                     lda  $7e                              ; 6F00
                     beq  L6f0d                            ; 6F02
                                                           ; 09 -> +9
                     ldy  #$2f                             ; 6F04
                     jsr  L7716                            ; 6F06
                     stx  $7e                              ; 6F09
                     beq  L6f18                            ; 6F0B
                                                           ; 0B -> +11

L6f0d                lda  $dd                              ; 6F0D
                     beq  L6f18                            ; 6F0F
                                                           ; 07 -> +7
                     ldy  #$5f                             ; 6F11
                     jsr  L7716                            ; 6F13
                     stx  $dd                              ; 6F16

L6f18                lda  $0219                            ; 6F18
                     bmi  L6f31                            ; 6F1B
                                                           ; 14 -> +20
                     beq  L6f31                            ; 6F1D
                                                           ; 12 -> +18
                     asl  ThrustSW                         ; 6F1F
                     ror  $10                              ; 6F22
                     lda  $02e7                            ; 6F24
                     beq  L6f31                            ; 6F27
                                                           ; 08 -> +8
                     lda  $83                              ; 6F29
                     beq  L6f38                            ; 6F2B
                                                           ; 0B -> +11
                     dec  $83                              ; 6F2D
                     bne  L6f4d                            ; 6F2F
                                                           ; 1C -> +28

L6f31                lda  $02ed                            ; 6F31
                     sta  $84                              ; 6F34
                     bpl  L6f4d                            ; 6F36
                                                           ; 15 -> +21

L6f38                dec  $84                              ; 6F38
                     bne  L6f4d                            ; 6F3A
                                                           ; 11 -> +17
                     lda  #$04                             ; 6F3C
                     sta  $83                              ; 6F3E
                     inc  $82                              ; 6F40
                     lda  $82                              ; 6F42
                     and  #$01                             ; 6F44
                     tax                                   ; 6F46
                     ldy  $6f60,X                          ; 6F47
                     jsr  L7713                            ; 6F4A

L6f4d                lda  $7f                              ; 6F4D
                     tax                                   ; 6F4F
                     and  #$3f                             ; 6F50
                     beq  L6f55                            ; 6F52
                                                           ; 01 -> +1
                     dex                                   ; 6F54

L6f55                stx  $7f                              ; 6F55
                     stx  ExplodeCtrl                      ; 6F57
                     lda  $10                              ; 6F5A
                     sta  ThrustSnd                        ; 6F5C
                     rts                                   ; 6F5F
                     fcb  $07,$0F                            

L6f62                stx  $0e                              ; 6F62
                     lda  #$50                             ; 6F64
                     sta  $02ea                            ; 6F66
                     lda  $0200,Y                          ; 6F69
                     and  #$78                             ; 6F6C
                     asl  A                                ; 6F6E
                     bpl  L6f74                            ; 6F6F
                                                           ; 03 -> +3
                     jmp  L4800                            ; 6F71

L6f74                lsr  A                                ; 6F74
                     sta  $0f                              ; 6F75
                     lda  $0200,Y                          ; 6F77
                     and  #$07                             ; 6F7A
                     lsr  A                                ; 6F7C
                     tax                                   ; 6F7D
                     beq  L6f82                            ; 6F7E
                                                           ; 02 -> +2
                     ora  $0f                              ; 6F80

L6f82                sta  $0200,Y                          ; 6F82
                     lda  $22                              ; 6F85
                     beq  L6f98                            ; 6F87
                                                           ; 0F -> +15
                     lda  $0e                              ; 6F89
                     beq  L6f91                            ; 6F8B
                                                           ; 04 -> +4
                     cmp  #$04                             ; 6F8D
                     bcc  L6f98                            ; 6F8F
                                                           ; 07 -> +7

L6f91                lda  $4d75,X                          ; 6F91
                     clc                                   ; 6F94
                     jsr  L6c44                            ; 6F95

L6f98                ldx  $0200,Y                          ; 6F98
                     beq  L6fd1                            ; 6F9B
                                                           ; 34 -> +52
                     jsr  L6d50                            ; 6F9D
                     bmi  L6fd1                            ; 6FA0
                                                           ; 2F -> +47
                     inc  $02e7                            ; 6FA2
                     jsr  L61eb                            ; 6FA5
                     jsr  L6a3b                            ; 6FA8
                     lda  $0221,X                          ; 6FAB
                     and  #$1f                             ; 6FAE
                     asl  A                                ; 6FB0
                     eor  $02a5,X                          ; 6FB1
                     sta  $02a5,X                          ; 6FB4
                     jsr  L6d52                            ; 6FB7
                     bmi  L6fd1                            ; 6FBA
                                                           ; 15 -> +21
                     inc  $02e7                            ; 6FBC
                     jsr  L61eb                            ; 6FBF
                     jsr  L6a3b                            ; 6FC2
                     lda  $0242,X                          ; 6FC5
                     and  #$1f                             ; 6FC8
                     asl  A                                ; 6FCA
                     eor  $02c6,X                          ; 6FCB
                     sta  $02c6,X                          ; 6FCE

L6fd1                ldx  $0e                              ; 6FD1
                     rts                                   ; 6FD3

L6fd4                lda  $22                              ; 6FD4
                     bpl  L7025                            ; 6FD6
                                                           ; 4D -> +77
                     sta  $77                              ; 6FD8
                     sta  $42                              ; 6FDA
                     sta  $43                              ; 6FDC
                     sta  $ce                              ; 6FDE
                     jsr  L7844                            ; 6FE0
                     ldx  #$03                             ; 6FE3

L6fe5                ldy  #$00                             ; 6FE5

L6fe7                lda  $0023,Y                          ; 6FE7
                     cmp  $62,X                            ; 6FEA
                     lda  $0024,Y                          ; 6FEC
                     sbc  $63,X                            ; 6FEF
                     lda  $0025,Y                          ; 6FF1
                     sbc  $64,X                            ; 6FF4
                     bcc  L7026                            ; 6FF6
                                                           ; 2E -> +46
                     iny                                   ; 6FF8
                     iny                                   ; 6FF9
                     iny                                   ; 6FFA
                     cpy  #$1e                             ; 6FFB
                     bcc  L6fe7                            ; 6FFD
                                                           ; E8 -> 17 ->  -24

L6fff                dex                                   ; 6FFF
                     dex                                   ; 7000
                     dex                                   ; 7001
                     bpl  L6fe5                            ; 7002
                                                           ; E1 -> 1E ->  -31
                     lda  $43                              ; 7004
                     bmi  L7016                            ; 7006
                                                           ; 0E -> +14
                     cmp  $42                              ; 7008
                     bcc  L7016                            ; 700A
                                                           ; 0A -> +10
                     adc  #$02                             ; 700C
                     cmp  #$1e                             ; 700E
                     bcc  L7014                            ; 7010
                                                           ; 02 -> +2
                     lda  #$ff                             ; 7012

L7014                sta  $43                              ; 7014

L7016                ldx  $ce                              ; 7016
                     bmi  L701f                            ; 7018
                                                           ; 05 -> +5
                     ldy  #$4f                             ; 701A
                     jsr  L7716                            ; 701C

L701f                lda  #$00                             ; 701F
                     sta  $22                              ; 7021
                     sta  $41                              ; 7023

L7025                rts                                   ; 7025

L7026                stx  $0c                              ; 7026
                     txa                                   ; 7028
                     lsr  A                                ; 7029
                     tax                                   ; 702A
                     sty  $42,X                            ; 702B
                     sty  $10                              ; 702D
                     cpy  $ce                              ; 702F
                     bcs  L7059                            ; 7031
                                                           ; 26 -> +38
                     sty  $ce                              ; 7033
                     lda  #$00                             ; 7035
                     sta  $11                              ; 7037
                     tya                                   ; 7039

L703a                sec                                   ; 703A
                     sbc  #$03                             ; 703B
                     bcc  L7043                            ; 703D
                                                           ; 04 -> +4
                     inc  $11                              ; 703F
                     bne  L703a                            ; 7041
                                                           ; F7 -> 08 ->  -9

L7043                lda  $11                              ; 7043
                     eor  #$ff                             ; 7045
                     adc  #$04                             ; 7047
                     sta  $11                              ; 7049
                     asl  $11                              ; 704B
                     adc  $11                              ; 704D
                     asl  $11                              ; 704F
                     adc  $11                              ; 7051
                     sta  $cc                              ; 7053
                     lda  #$14                             ; 7055
                     sta  $cb                              ; 7057

L7059                ldx  #$1b                             ; 7059

L705b                cpx  $10                              ; 705B
                     beq  L707c                            ; 705D
                                                           ; 1D -> +29
                     lda  $41,X                            ; 705F
                     sta  $44,X                            ; 7061
                     lda  $42,X                            ; 7063
                     sta  $45,X                            ; 7065
                     lda  $43,X                            ; 7067
                     sta  $46,X                            ; 7069
                     lda  $20,X                            ; 706B
                     sta  $23,X                            ; 706D
                     lda  $21,X                            ; 706F
                     sta  $24,X                            ; 7071
                     lda  $22,X                            ; 7073
                     sta  $25,X                            ; 7075
                     dex                                   ; 7077
                     dex                                   ; 7078
                     dex                                   ; 7079
                     bne  L705b                            ; 707A
                                                           ; DF -> 20 ->  -33

L707c                lda  #$0b                             ; 707C
                     sta  $44,X                            ; 707E
                     lda  #$00                             ; 7080
                     sta  $45,X                            ; 7082
                     sta  $46,X                            ; 7084
                     lda  #$f0                             ; 7086
                     sta  $77                              ; 7088
                     ldx  $0c                              ; 708A
                     lda  $64,X                            ; 708C
                     sta  $0025,Y                          ; 708E
                     lda  $63,X                            ; 7091
                     sta  $0024,Y                          ; 7093
                     lda  $62,X                            ; 7096
                     sta  $0023,Y                          ; 7098
                     jmp  L6fff                            ; 709B
                     fcb  $98,$10,$09,$20,$B6,$70,$20,$AA    
                     fcb  $70,$4C,$B6,$70,$A8,$8A,$10,$0E    
                     fcb  $20,$B6,$70,$20,$BC,$70,$49,$80    

L70b6                eor  #$ff                             ; 70B6
                     clc                                   ; 70B8
                     adc  #$01                             ; 70B9
                     rts                                   ; 70BB
                     fcb  $85,$0D,$98,$C5,$0D,$90,$0E,$A4    
                     fcb  $0D,$85,$0D,$98,$20,$D1,$70,$38    
                     fcb  $E9,$40,$4C,$B6,$70,$20,$EB,$70    
                     fcb  $AA,$BD,$D9,$70,$60,$00,$02,$05    
                     fcb  $07,$0A,$0C,$0F,$11,$13,$15,$17    
                     fcb  $19,$1A,$1C,$1D,$1F,$20,$D5,$A0    
                     fcb  $04,$C5,$0D,$90,$02,$E5,$0D,$26    
                     fcb  $0C,$0A,$88,$10,$F4,$A5,$0C,$29    
                     fcb  $1F,$60                            

L70fe                clc                                   ; 70FE
                     adc  #$40                             ; 70FF

L7101                bpl  L710b                            ; 7101
                                                           ; 08 -> +8
                     and  #$7f                             ; 7103
                     jsr  L710b                            ; 7105
                     jmp  L70b6                            ; 7108

L710b                cmp  #$41                             ; 710B
                     bcc  L7113                            ; 710D
                                                           ; 04 -> +4
                     eor  #$7f                             ; 710F
                     adc  #$00                             ; 7111

L7113                tax                                   ; 7113
                     lda  $4b61,X                          ; 7114
                     rts                                   ; 7117

L7118                lda  #$04                             ; 7118
                     sta  $76                              ; 711A

L711c                jsr  L4ba2                            ; 711C
                     dec  $76                              ; 711F
                     bne  L711c                            ; 7121
                                                           ; F9 -> 06 ->  -7
                     ldx  #$c9                             ; 7123
                     lda  #$47                             ; 7125
                     sta  $04                              ; 7127
                     lda  #$02                             ; 7129
                     sta  $03                              ; 712B
                     lda  #$c1                             ; 712D
                     jsr  L7cd5                            ; 712F
                     lda  #$be                             ; 7132
                     sta  $09                              ; 7134
                     lda  #$75                             ; 7136
                     sta  $0a                              ; 7138
                     lda  #$00                             ; 713A
                     sta  $01                              ; 713C
                     lda  #$70                             ; 713E
                     ldx  #$20                             ; 7140
                     jsr  L717f                            ; 7142
                     jmp  L79d6                            ; 7145

L7148                lda  #$c5                             ; 7148
                     ldx  #$c9                             ; 714A
                     jsr  L7cd5                            ; 714C
                     ldx  #$be                             ; 714F
                     lda  #$75                             ; 7151
                     sta  $0a                              ; 7153
                     stx  $09                              ; 7155
                     bne  L7187                            ; 7157
                                                           ; 2E -> +46

L7159                lda  Option21                         ; 7159
                     and  #$03                             ; 715C
                     ldx  #$10                             ; 715E
                     stx  $01                              ; 7160

L7162                asl  A                                ; 7162
                     tax                                   ; 7163
                     lda  $71f1,X                          ; 7164
                     sta  $0a                              ; 7167
                     lda  $71f0,X                          ; 7169
                     sta  $09                              ; 716C
                     adc  ($09),Y                          ; 716E
                     sta  $09                              ; 7170
                     bcc  L7176                            ; 7172
                                                           ; 02 -> +2
                     inc  $0a                              ; 7174

L7176                tya                                   ; 7176
                     asl  A                                ; 7177
                     tay                                   ; 7178
                     lda  $71d4,Y                          ; 7179
                     ldx  $71d5,Y                          ; 717C

L717f                jsr  L7a1f                            ; 717F
                     lda  #$70                             ; 7182
                     jsr  L7aea                            ; 7184

L7187                ldy  #$00                             ; 7187
                     ldx  #$00                             ; 7189

L718b                lda  ($09,X)                          ; 718B
                     sta  $0c                              ; 718D
                     lsr  A                                ; 718F
                     lsr  A                                ; 7190
                     jsr  L71b0                            ; 7191
                     lda  ($09,X)                          ; 7194
                     rol  A                                ; 7196
                     rol  $0c                              ; 7197
                     rol  A                                ; 7199
                     lda  $0c                              ; 719A
                     rol  A                                ; 719C
                     asl  A                                ; 719D
                     jsr  L71b6                            ; 719E
                     lda  ($09,X)                          ; 71A1
                     sta  $0c                              ; 71A3
                     jsr  L71b0                            ; 71A5
                     lsr  $0c                              ; 71A8
                     bcc  L718b                            ; 71AA
                                                           ; DF -> 20 ->  -33

L71ac                dey                                   ; 71AC
                     jmp  L7a55                            ; 71AD

L71b0                inc  $09                              ; 71B0
                     bne  L71b6                            ; 71B2
                                                           ; 02 -> +2
                     inc  $0a                              ; 71B4

L71b6                and  #$3e                             ; 71B6
                     bne  L71be                            ; 71B8
                                                           ; 04 -> +4
                     pla                                   ; 71BA
                     pla                                   ; 71BB
                     bne  L71ac                            ; 71BC
                                                           ; EE -> 11 ->  -18

L71be                cmp  #$0a                             ; 71BE
                     bcc  L71c4                            ; 71C0
                                                           ; 02 -> +2
                     adc  #$0d                             ; 71C2

L71c4                tax                                   ; 71C4
                     lda  $56f6,X                          ; 71C5
                     sta  ($03),Y                          ; 71C8
                     iny                                   ; 71CA
                     lda  $56f7,X                          ; 71CB
                     sta  ($03),Y                          ; 71CE
                     iny                                   ; 71D0
                     ldx  #$00                             ; 71D1
                     rts                                   ; 71D3
                     fcb  $68,$B6,$72,$B6,$0C,$AA,$0C,$A2    
                     fcb  $0C,$9A,$0C,$92,$68,$C6,$6E,$A7    
                     fcb  $56,$42,$5A,$42,$58,$42,$68,$32    
                     fcb  $64,$C6,$6E,$D2,$F8,$71,$AE,$72    
                     fcb  $7D,$73,$38,$74,$0E,$16,$1C,$32    
                     fcb  $44,$58,$70,$78,$7E,$8A,$94,$A0    
                     fcb  $A6,$B0,$63,$56,$60,$6E,$3C,$EC    
                     fcb  $4D,$C0,$A4,$0A,$EA,$6C,$08,$00    
                     fcb  $EC,$F2,$B0,$6E,$3C,$EC,$48,$5A    
                     fcb  $B8,$66,$92,$42,$9A,$82,$C3,$12    
                     fcb  $0E,$12,$90,$4C,$4D,$F1,$A4,$12    
                     fcb  $2D,$D2,$0A,$64,$C2,$6C,$0F,$66    
                     fcb  $CD,$82,$6C,$9A,$C3,$4A,$85,$C0    
                     fcb  $A5,$92,$BD,$C2,$B4,$F0,$2E,$12    
                     fcb  $0E,$26,$0D,$D2,$82,$4E,$C0,$60    
                     fcb  $4E,$30,$4D,$80,$A5,$92,$BD,$C2    
                     fcb  $BB,$1A,$4C,$10,$0E,$D8,$4C,$82    
                     fcb  $82,$70,$C2,$6C,$0B,$6E,$09,$E6    
                     fcb  $B5,$92,$3E,$00,$A5,$92,$BD,$C2    
                     fcb  $BE,$0A,$B6,$00,$59,$62,$48,$66    
                     fcb  $D2,$6D,$18,$4E,$9B,$64,$09,$02    
                     fcb  $3D,$92,$43,$70,$B8,$00,$18,$4E    
                     fcb  $9B,$64,$08,$C2,$3D,$92,$43,$71    
                     fcb  $20,$4E,$9B,$64,$B8,$46,$09,$EC    
                     fcb  $4A,$1A,$C0,$00,$3D,$92,$43,$70    
                     fcb  $B8,$40,$20,$56,$2C,$52,$0C,$5A    
                     fcb  $93,$62,$CC,$40,$34,$E4,$CD,$C2    
                     fcb  $2E,$03,$0D,$17,$1D,$37,$4F,$67    
                     fcb  $7D,$8B,$91,$9D,$A9,$B5,$BB,$64    
                     fcb  $D2,$3B,$2E,$C2,$6C,$5A,$4C,$93    
                     fcb  $6F,$BD,$1A,$4C,$12,$B0,$40,$6B    
                     fcb  $2C,$0A,$6C,$5A,$4C,$93,$6E,$0B    
                     fcb  $6E,$C0,$52,$6C,$92,$B8,$50,$4D    
                     fcb  $82,$F2,$58,$90,$4C,$4D,$F0,$4C    
                     fcb  $80,$33,$70,$C2,$42,$5A,$4C,$4C    
                     fcb  $82,$BB,$52,$0B,$58,$B2,$42,$6C    
                     fcb  $9A,$C3,$4A,$82,$64,$0A,$5A,$90    
                     fcb  $00,$F6,$6C,$09,$B2,$3B,$2E,$C1    
                     fcb  $4C,$4C,$B6,$2B,$20,$0D,$A6,$C1    
                     fcb  $70,$48,$50,$B6,$52,$3B,$D2,$90    
                     fcb  $00,$DA,$64,$90,$4C,$C9,$D8,$BE    
                     fcb  $0A,$32,$42,$9B,$C2,$BB,$1A,$4C    
                     fcb  $10,$0A,$2C,$CA,$4E,$7A,$65,$BE    
                     fcb  $0A,$B6,$1E,$94,$D2,$A2,$92,$0A    
                     fcb  $2C,$CA,$4E,$7A,$65,$BD,$1A,$4C    
                     fcb  $12,$92,$13,$18,$62,$CA,$64,$F2    
                     fcb  $42,$20,$6E,$A3,$52,$82,$40,$18    
                     fcb  $62,$CA,$64,$F2,$42,$18,$6E,$A3    
                     fcb  $52,$80,$00,$20,$62,$CA,$64,$F2    
                     fcb  $64,$08,$C2,$BD,$1A,$4C,$00,$7D    
                     fcb  $92,$43,$70,$48,$40,$5A,$60,$42    
                     fcb  $5A,$96,$F2,$B2,$82,$56,$52,$B0    
                     fcb  $7C,$DA,$5A,$0D,$E8,$6A,$60,$48    
                     fcb  $00,$0D,$17,$1B,$33,$43,$59,$71    
                     fcb  $7D,$87,$93,$9F,$AB,$B1,$8A,$5A    
                     fcb  $84,$12,$CD,$82,$B9,$E6,$B2,$40    
                     fcb  $74,$F2,$4D,$83,$D4,$F0,$B2,$42    
                     fcb  $B9,$E6,$B2,$42,$4D,$F0,$0E,$64    
                     fcb  $0A,$12,$B8,$46,$10,$62,$4B,$60    
                     fcb  $82,$72,$B5,$C0,$BE,$A8,$0A,$64    
                     fcb  $C5,$92,$F0,$74,$9D,$C2,$6C,$9A    
                     fcb  $C3,$4A,$82,$6F,$A4,$F2,$BD,$D2    
                     fcb  $F0,$6C,$9E,$0A,$C2,$42,$A4,$F2    
                     fcb  $B0,$74,$9D,$C2,$6C,$9A,$C3,$4A    
                     fcb  $82,$6F,$A4,$F2,$BD,$D2,$F0,$6E    
                     fcb  $63,$52,$82,$02,$AE,$4A,$92,$02    
                     fcb  $82,$70,$C5,$92,$09,$E6,$B5,$92    
                     fcb  $3E,$13,$2D,$28,$CF,$52,$B0,$6E    
                     fcb  $CD,$82,$BE,$0A,$B6,$00,$53,$64    
                     fcb  $0A,$12,$0D,$0A,$B6,$1A,$48,$00    
                     fcb  $18,$68,$6A,$4E,$48,$48,$0B,$A6    
                     fcb  $CA,$72,$B5,$C0,$18,$68,$6A,$4E    
                     fcb  $48,$46,$0B,$A6,$CA,$72,$B0,$00    
                     fcb  $20,$68,$6A,$4E,$4D,$C2,$18,$5C    
                     fcb  $9E,$52,$CD,$80,$3D,$92,$43,$70    
                     fcb  $B8,$40,$20,$5C,$4E,$78,$0C,$5A    
                     fcb  $93,$62,$CC,$40,$0D,$13,$19,$33    
                     fcb  $47,$61,$6B,$73,$7D,$89,$93,$9F    
                     fcb  $A5,$B2,$4E,$9D,$90,$B8,$00,$76    
                     fcb  $56,$2A,$26,$B0,$40,$BE,$42,$A6    
                     fcb  $64,$C1,$5C,$48,$52,$BE,$0A,$0A    
                     fcb  $64,$C5,$92,$0C,$26,$B8,$50,$6A    
                     fcb  $7C,$0C,$52,$74,$EC,$4D,$C0,$A4    
                     fcb  $EC,$0A,$8A,$D4,$EC,$0A,$64,$C5    
                     fcb  $92,$0D,$F2,$B8,$5A,$93,$4E,$69    
                     fcb  $60,$4D,$C0,$9D,$2C,$6C,$4A,$0D    
                     fcb  $A6,$C1,$70,$48,$68,$2D,$8A,$0D    
                     fcb  $D2,$82,$4E,$3B,$66,$91,$6C,$0C    
                     fcb  $0A,$0C,$12,$C5,$8B,$9D,$2C,$6C    
                     fcb  $4A,$0D,$D8,$6A,$60,$40,$00,$A6    
                     fcb  $60,$B9,$6C,$0D,$F0,$2D,$B1,$76    
                     fcb  $52,$5C,$C2,$C2,$6C,$8B,$64,$2A    
                     fcb  $27,$18,$54,$69,$D8,$28,$48,$0B    
                     fcb  $B2,$4A,$E6,$B8,$00,$18,$54,$69    
                     fcb  $D8,$28,$46,$0B,$B2,$4A,$E7,$20    
                     fcb  $54,$69,$D8,$2D,$C2,$18,$5C,$CA    
                     fcb  $56,$98,$00,$3D,$92,$43,$70,$9D    
                     fcb  $C3,$20,$5C,$CA,$56,$2D,$C2,$8B    
                     fcb  $64,$6C,$67                        

L74e7                bit  $73                              ; 74E7
                     bpl  L7514                            ; 74E9
                                                           ; 29 -> +41
                     txa                                   ; 74EB
                     beq  L74f5                            ; 74EC
                                                           ; 07 -> +7
                     cpy  #$19                             ; 74EE
                     bne  L7514                            ; 74F0
                                                           ; 22 -> +34
                     adc  #$18                             ; 74F2
                     tay                                   ; 74F4

L74f5                lda  $0200,Y                          ; 74F5
                     cpy  #$1a                             ; 74F8
                     beq  L7516                            ; 74FA
                                                           ; 1A -> +26
                     bcc  L7528                            ; 74FC
                                                           ; 2A -> +42
                     lda  #$00                             ; 74FE
                     sta  $0200,Y                          ; 7500
                     ldx  #$e1                             ; 7503

L7505                pla                                   ; 7505
                     pla                                   ; 7506

L7507                txa                                   ; 7507
                     adc  $02ef                            ; 7508
                     bcs  L7511                            ; 750B
                                                           ; 04 -> +4
                     lda  #$00                             ; 750D
                     sta  $73                              ; 750F

L7511                sta  $02ef                            ; 7511

L7514                clc                                   ; 7514
                     rts                                   ; 7515

L7516                ldx  #$80                             ; 7516
                     cpx  $02ef                            ; 7518
                     bcc  L7523                            ; 751B
                                                           ; 06 -> +6
                     ldx  #$00                             ; 751D
                     ldy  #$1a                             ; 751F
                     clc                                   ; 7521
                     rts                                   ; 7522

L7523                jsr  L7507                            ; 7523
                     sec                                   ; 7526
                     rts                                   ; 7527

L7528                ldx  #$f8                             ; 7528
                     sec                                   ; 752A
                     ror  $71                              ; 752B
                     cpy  $72                              ; 752D
                     beq  L7505                            ; 752F
                                                           ; D4 -> 2B ->  -44
                     sty  $72                              ; 7531
                     asl  A                                ; 7533
                     and  #$86                             ; 7534
                     sta  $10                              ; 7536
                     bmi  L7554                            ; 7538
                                                           ; 1A -> +26
                     beq  L7554                            ; 753A
                                                           ; 18 -> +24
                     lda  $0221,Y                          ; 753C
                     cmp  #$80                             ; 753F
                     ror  A                                ; 7541
                     jsr  L6a62                            ; 7542
                     sta  $0221,Y                          ; 7545
                     lda  $0242,Y                          ; 7548
                     cmp  #$80                             ; 754B
                     ror  A                                ; 754D
                     jsr  L6a62                            ; 754E
                     sta  $0242,Y                          ; 7551

L7554                ldx  #$00                             ; 7554
                     jsr  L7567                            ; 7556
                     ldx  #$21                             ; 7559
                     tya                                   ; 755B
                     clc                                   ; 755C
                     adc  #$21                             ; 755D
                     tay                                   ; 755F
                     jsr  L7567                            ; 7560
                     ldx  #$b0                             ; 7563
                     bne  L7505                            ; 7565
                                                           ; 9E -> 61 ->  -98

L7567                stx  $11                              ; 7567
                     lda  $0221,Y                          ; 7569
                     bmi  L7581                            ; 756C
                                                           ; 13 -> +19
                     lda  $023a,X                          ; 756E
                     bmi  L758b                            ; 7571
                                                           ; 18 -> +24
                     jsr  L75b1                            ; 7573
                     bcc  L758b                            ; 7576
                                                           ; 13 -> +19

L7578                lda  #$00                             ; 7578
                     sec                                   ; 757A
                     sbc  $0221,Y                          ; 757B
                     jmp  L759a                            ; 757E

L7581                lda  $023a,X                          ; 7581
                     bpl  L758b                            ; 7584
                                                           ; 05 -> +5
                     jsr  L75b1                            ; 7586
                     bcc  L7578                            ; 7589
                                                           ; ED -> 12 ->  -19

L758b                lda  $0221,Y                          ; 758B
                     bit  $10                              ; 758E
                     bpl  L7599                            ; 7590
                                                           ; 07 -> +7
                     cmp  #$80                             ; 7592
                     ror  A                                ; 7594
                     adc  $0221,Y                          ; 7595
                     lsr  A                                ; 7598

L7599                rol  A                                ; 7599

L759a                jsr  L68ea                            ; 759A
                     bpl  L75a5                            ; 759D
                                                           ; 06 -> +6
                     cmp  #$fb                             ; 759F
                     bcc  L75ab                            ; 75A1
                                                           ; 08 -> +8
                     lda  #$fa                             ; 75A3

L75a5                cmp  #$06                             ; 75A5
                     bcs  L75ab                            ; 75A7
                                                           ; 02 -> +2
                     lda  #$06                             ; 75A9

L75ab                ldx  $11                              ; 75AB
                     sta  $023a,X                          ; 75AD
                     rts                                   ; 75B0

L75b1                lda  $02a5,Y                          ; 75B1
                     cmp  $02be,X                          ; 75B4
                     lda  $0263,Y                          ; 75B7
                     sbc  $027c,X                          ; 75BA
                     rts                                   ; 75BD
                     fcb  $1F,$C4,$09,$70,$2D,$9A,$0B,$64    
                     fcb  $38,$00,$00,$00,$00,$00,$00,$00    
                     fcb  $01,$08,$00,$00,$00,$00,$00,$00    
                     fcb  $0F,$08,$00,$00,$00,$00,$16,$21    
                     fcb  $00,$00,$00,$00,$2F,$36,$00,$00    
                     fcb  $00,$00,$3D,$44,$00,$00,$00,$00    
                     fcb  $00,$00,$00,$00,$00,$00,$00,$00    
                     fcb  $4B,$52,$00,$00,$00,$00,$28,$21    
                     fcb  $00,$00,$00,$00,$5D,$64,$00,$00    
                     fcb  $00,$00,$00,$00,$00,$00,$6F,$7A    
                     fcb  $85,$7A,$90,$A5,$00,$00,$00,$00    
                     fcb  $90,$B6,$D3,$DE,$00,$00,$00,$00    
                     fcb  $00,$00,$00,$00,$00,$00,$00,$00    
                     fcb  $C1,$CC,$00,$01,$04,$E0,$03,$05    
                     fcb  $00,$00,$01,$04,$A8,$FF,$05,$00    
                     fcb  $00,$01,$04,$D0,$03,$05,$00,$00    
                     fcb  $7F,$01,$04,$01,$10,$01,$14,$FF    
                     fcb  $10,$00,$00,$7F,$20,$A2,$00,$01    
                     fcb  $00,$00,$7F,$01,$10,$01,$20,$00    
                     fcb  $00,$01,$02,$0C,$01,$18,$00,$00    
                     fcb  $01,$10,$A4,$FF,$03,$00,$00,$01    
                     fcb  $01,$04,$01,$40,$00,$00,$01,$10    
                     fcb  $A4,$FF,$04,$00,$00,$01,$F0,$06    
                     fcb  $00,$02,$00,$00,$0F,$10,$A8,$00    
                     fcb  $01,$10,$A0,$00,$01,$00,$00,$01    
                     fcb  $02,$50,$01,$70,$00,$00,$07,$10    
                     fcb  $A8,$00,$01,$10,$A0,$00,$01,$00    
                     fcb  $00,$0C,$02,$0A,$01,$03,$04,$0C    
                     fcb  $FF,$02,$00,$00,$01,$18,$A0,$01    
                     fcb  $05,$18,$A5,$FF,$05,$00,$00,$18    
                     fcb  $02,$0A,$01,$02,$02,$0B,$00,$02    
                     fcb  $00,$00,$10,$0C,$21,$00,$01,$0C    
                     fcb  $18,$00,$01,$00,$01,$02,$20,$10    
                     fcb  $FF,$04,$30,$02,$30,$00,$00,$01    
                     fcb  $30,$21,$01,$08,$00,$01,$80,$84    
                     fcb  $01,$04,$30,$85,$FF,$04,$00,$00    
                     fcb  $04,$18,$A5,$FF,$04,$18,$A1,$01    
                     fcb  $04,$00,$00,$10,$0C,$49,$00,$01    
                     fcb  $0C,$30,$00,$01,$00,$00,$02,$C0    
                     fcb  $A4,$00,$01,$00,$00,$01,$01,$F0    
                     fcb  $01,$0F,$01,$FF,$FF,$0F,$00,$00    
                     fcb  $01,$1F,$A2,$00,$01,$00,$00        

L770d                bit  $7741                            ; 770D
                     clc                                   ; 7710
                     bcc  L771c                            ; 7711
                                                           ; 09 -> +9

L7713                sec                                   ; 7713
                     bcs  L7717                            ; 7714
                                                           ; 01 -> +1

L7716                clc                                   ; 7716

L7717                lda  $22                              ; 7717
                     beq  L770d                            ; 7719
                                                           ; F2 -> 0D ->  -14
                     clv                                   ; 771B

L771c                txa                                   ; 771C
                     pha                                   ; 771D
                     ldx  #$07                             ; 771E

L7720                bcc  L7726                            ; 7720
                                                           ; 04 -> +4
                     lda  $9b,X                            ; 7722
                     bne  L773b                            ; 7724
                                                           ; 15 -> +21

L7726                lda  $75c8,Y                          ; 7726
                     beq  L773b                            ; 7729
                                                           ; 10 -> +16
                     bvc  L772f                            ; 772B
                                                           ; 02 -> +2
                     lda  #$00                             ; 772D

L772f                pha                                   ; 772F
                     lda  #$00                             ; 7730
                     sta  $9b,X                            ; 7732
                     lda  #$80                             ; 7734
                     sta  $bb,X                            ; 7736
                     pla                                   ; 7738
                     sta  $9b,X                            ; 7739

L773b                dey                                   ; 773B
                     dex                                   ; 773C
                     bpl  L7720                            ; 773D
                                                           ; E1 -> 1E ->  -31
                     pla                                   ; 773F
                     tax                                   ; 7740
                     rts                                   ; 7741

L7742                ldx  #$07                             ; 7742

L7744                ldy  $9b,X                            ; 7744
                     beq  L7782                            ; 7746
                                                           ; 3A -> +58
                     lda  $bb,X                            ; 7748
                     bmi  L778d                            ; 774A
                                                           ; 41 -> +65
                     dec  $ab,X                            ; 774C
                     bne  L7784                            ; 774E
                                                           ; 34 -> +52
                     dec  $b3,X                            ; 7750
                     beq  L775d                            ; 7752
                                                           ; 09 -> +9
                     lda  $a3,X                            ; 7754
                     clc                                   ; 7756
                     adc  $762a,Y                          ; 7757
                     jmp  L776b                            ; 775A

L775d                iny                                   ; 775D
                     iny                                   ; 775E
                     iny                                   ; 775F
                     iny                                   ; 7760

L7761                sty  $9b,X                            ; 7761
                     lda  $762b,Y                          ; 7763
                     sta  $b3,X                            ; 7766
                     lda  $7629,Y                          ; 7768

L776b                sta  $a3,X                            ; 776B
                     lda  $7628,Y                          ; 776D
                     sta  $ab,X                            ; 7770
                     bne  L7784                            ; 7772
                                                           ; 10 -> +16
                     ldy  $c3,X                            ; 7774
                     dec  $bb,X                            ; 7776
                     bne  L7761                            ; 7778
                                                           ; E7 -> 18 ->  -25
                     ldy  $9b,X                            ; 777A
                     iny                                   ; 777C
                     bne  L778d                            ; 777D
                                                           ; 0E -> +14

L777f                tay                                   ; 777F
                     sty  $9b,X                            ; 7780

L7782                sty  $a3,X                            ; 7782

L7784                lda  $a3,X                            ; 7784
                     sta  Pk_F1_Pot0,X                     ; 7786
                     dex                                   ; 7789
                     bpl  L7744                            ; 778A
                                                           ; B8 -> 47 ->  -72
                     rts                                   ; 778C

L778d                lda  $7628,Y                          ; 778D
                     beq  L777f                            ; 7790
                                                           ; ED -> 12 ->  -19
                     sta  $bb,X                            ; 7792
                     iny                                   ; 7794
                     sty  $c3,X                            ; 7795
                     bne  L7761                            ; 7797
                                                           ; C8 -> 37 ->  -56
                     ora  ($e0,X)                          ; 7799
                     cpy  #$e1                             ; 779B
                     sbc  $c3                              ; 779D
                     dex                                   ; 779F
                     fcb  $C3,$AF,$C3,$94,$C3,$7F,$02,$04    
                     fcb  $04,$05,$03,$7F,$7F,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF    
                     fcb  $FF,$FF,$FF,$FF                    

L7844                lda  #$00                             ; 7844
                     ldx  #$07                             ; 7846

L7848                sta  $9b,X                            ; 7848
                     dex                                   ; 784A
                     bpl  L7848                            ; 784B
                                                           ; FB -> 04 ->  -5
                     sta  Pk_Ctl_All                       ; 784D
                     rts                                   ; 7850

IRQ_Handler          bit  $01ff                            ; 7851
                     bpl  L7857                            ; 7854
                                                           ; 01 -> +1
                     rti                                   ; 7856

L7857                pha                                   ; 7857
                     tya                                   ; 7858
                     pha                                   ; 7859
                     txa                                   ; 785A
                     pha                                   ; 785B
                     cld                                   ; 785C
                     lda  $01ff                            ; 785D
                     ora  $01d0                            ; 7860

L7863                bne  L7863                            ; 7863
                                                           ; FE -> 01 ->  -2
                     inc  $78                              ; 7865
                     lda  $78                              ; 7867
                     and  #$03                             ; 7869
                     bne  L787a                            ; 786B
                                                           ; 0D -> +13
                     inc  $75                              ; 786D
                     lda  $75                              ; 786F
                     cmp  #$03                             ; 7871
                     bcc  L787a                            ; 7873
                                                           ; 05 -> +5

L7875                bne  L7875                            ; 7875
                                                           ; FE -> 01 ->  -2
                     sta  VGReset                          ; 7877

L787a                ldx  $22                              ; 787A
                     bne  L789b                            ; 787C
                                                           ; 1D -> +29
                     lda  $42                              ; 787E
                     and  $43                              ; 7880
                     bpl  L789b                            ; 7882
                                                           ; 17 -> +23
                     stx  Pk_SerCtl                        ; 7884
                     ldx  #$04                             ; 7887

L7889                dex                                   ; 7889
                     bne  L7889                            ; 788A
                                                           ; FD -> 02 ->  -3
                     ldx  #$07                             ; 788C
                     stx  Pk_SerCtl                        ; 788E
                     stx  Pk_PotGo                         ; 7891
                     lda  Pk_Ctl_All                       ; 7894
                     eor  #$ff                             ; 7897
                     sta  $8d                              ; 7899

L789b                jsr  L7742                            ; 789B
                     ldx  #$02                             ; 789E

L78a0                lda  LCoinSW,X                        ; 78A0
                     asl  A                                ; 78A3
                     lda  $96,X                            ; 78A4
                     and  #$1f                             ; 78A6
                     bcc  L78e1                            ; 78A8
                                                           ; 37 -> +55
                     beq  L78bc                            ; 78AA
                                                           ; 10 -> +16
                     cmp  #$1b                             ; 78AC
                     bcs  L78ba                            ; 78AE
                                                           ; 0A -> +10
                     tay                                   ; 78B0
                     lda  $78                              ; 78B1
                     and  #$07                             ; 78B3
                     cmp  #$07                             ; 78B5
                     tya                                   ; 78B7
                     bcc  L78bc                            ; 78B8
                                                           ; 02 -> +2

L78ba                sbc  #$01                             ; 78BA

L78bc                sta  $96,X                            ; 78BC
                     lda  SlamSW                           ; 78BE
                     and  #$80                             ; 78C1
                     beq  L78c9                            ; 78C3
                                                           ; 04 -> +4
                     lda  #$f0                             ; 78C5
                     sta  $8e                              ; 78C7

L78c9                lda  $8e                              ; 78C9
                     beq  L78d5                            ; 78CB
                                                           ; 08 -> +8
                     dec  $8e                              ; 78CD
                     lda  #$00                             ; 78CF
                     sta  $96,X                            ; 78D1
                     sta  $93,X                            ; 78D3

L78d5                clc                                   ; 78D5
                     lda  $93,X                            ; 78D6
                     beq  L78fd                            ; 78D8
                                                           ; 23 -> +35
                     dec  $93,X                            ; 78DA
                     bne  L78fd                            ; 78DC
                                                           ; 1F -> +31
                     sec                                   ; 78DE
                     bcs  L78fd                            ; 78DF
                                                           ; 1C -> +28

L78e1                cmp  #$1b                             ; 78E1
                     bcs  L78ee                            ; 78E3
                                                           ; 09 -> +9
                     lda  $96,X                            ; 78E5
                     adc  #$20                             ; 78E7
                     bcc  L78bc                            ; 78E9
                                                           ; D1 -> 2E ->  -47
                     beq  L78ee                            ; 78EB
                                                           ; 01 -> +1
                     clc                                   ; 78ED

L78ee                lda  #$1f                             ; 78EE
                     bcs  L78bc                            ; 78F0
                                                           ; CA -> 35 ->  -54
                     sta  $96,X                            ; 78F2
                     lda  $93,X                            ; 78F4
                     beq  L78f9                            ; 78F6
                                                           ; 01 -> +1
                     sec                                   ; 78F8

L78f9                lda  #$78                             ; 78F9
                     sta  $93,X                            ; 78FB

L78fd                bcc  L7929                            ; 78FD
                                                           ; 2A -> +42
                     lda  #$00                             ; 78FF
                     cpx  #$01                             ; 7901
                     bcc  L791b                            ; 7903
                                                           ; 16 -> +22
                     beq  L7913                            ; 7905
                                                           ; 0C -> +12
                     lda  $8d                              ; 7907
                     and  #$0c                             ; 7909
                     lsr  A                                ; 790B
                     lsr  A                                ; 790C
                     beq  L791b                            ; 790D
                                                           ; 0C -> +12
                     adc  #$02                             ; 790F
                     bne  L791b                            ; 7911
                                                           ; 08 -> +8

L7913                lda  $8d                              ; 7913
                     and  #$10                             ; 7915
                     beq  L791b                            ; 7917
                                                           ; 02 -> +2
                     lda  #$01                             ; 7919

L791b                sec                                   ; 791B
                     pha                                   ; 791C
                     adc  $99                              ; 791D
                     sta  $99                              ; 791F
                     pla                                   ; 7921
                     sec                                   ; 7922
                     adc  $8f                              ; 7923
                     sta  $8f                              ; 7925
                     inc  $90,X                            ; 7927

L7929                dex                                   ; 7929
                     bmi  L792f                            ; 792A
                                                           ; 03 -> +3
                     jmp  L78a0                            ; 792C

L792f                lda  $8d                              ; 792F
                     lsr  A                                ; 7931
                     lsr  A                                ; 7932
                     lsr  A                                ; 7933
                     lsr  A                                ; 7934
                     lsr  A                                ; 7935
                     tay                                   ; 7936
                     lda  $99                              ; 7937
                     sec                                   ; 7939
                     sbc  $77a5,Y                          ; 793A
                     bmi  L7949                            ; 793D
                                                           ; 0A -> +10
                     sta  $99                              ; 793F
                     inc  $9a                              ; 7941
                     cpy  #$03                             ; 7943
                     bne  L7949                            ; 7945
                                                           ; 02 -> +2
                     inc  $9a                              ; 7947

L7949                lda  $8d                              ; 7949
                     and  #$03                             ; 794B
                     tay                                   ; 794D
                     beq  L796a                            ; 794E
                                                           ; 1A -> +26
                     lsr  A                                ; 7950
                     adc  #$00                             ; 7951
                     eor  #$ff                             ; 7953
                     sec                                   ; 7955
                     adc  $8f                              ; 7956
                     bcs  L7962                            ; 7958
                                                           ; 08 -> +8
                     adc  $9a                              ; 795A
                     bmi  L796c                            ; 795C
                                                           ; 0E -> +14
                     sta  $9a                              ; 795E
                     lda  #$00                             ; 7960

L7962                cpy  #$02                             ; 7962
                     bcs  L7968                            ; 7964
                                                           ; 02 -> +2
                     inc  $8c                              ; 7966

L7968                inc  $8c                              ; 7968

L796a                sta  $8f                              ; 796A

L796c                lda  $78                              ; 796C
                     lsr  A                                ; 796E
                     bcs  L7998                            ; 796F
                                                           ; 27 -> +39
                     ldy  #$00                             ; 7971
                     ldx  #$02                             ; 7973

L7975                lda  $90,X                            ; 7975
                     beq  L7982                            ; 7977
                                                           ; 09 -> +9
                     cmp  #$10                             ; 7979
                     bcc  L7982                            ; 797B
                                                           ; 05 -> +5
                     adc  #$ef                             ; 797D
                     iny                                   ; 797F
                     sta  $90,X                            ; 7980

L7982                dex                                   ; 7982
                     bpl  L7975                            ; 7983
                                                           ; F0 -> 0F ->  -16
                     tya                                   ; 7985
                     bne  L7998                            ; 7986
                                                           ; 10 -> +16
                     ldx  #$02                             ; 7988

L798a                lda  $90,X                            ; 798A
                     beq  L7995                            ; 798C
                                                           ; 07 -> +7
                     clc                                   ; 798E
                     adc  #$ef                             ; 798F
                     sta  $90,X                            ; 7991
                     bmi  L7998                            ; 7993
                                                           ; 03 -> +3

L7995                dex                                   ; 7995
                     bpl  L798a                            ; 7996
                                                           ; F2 -> 0D ->  -14

L7998                lda  $90                              ; 7998
                     sta  LCount                           ; 799A
                     lda  $91                              ; 799D
                     sta  CCount                           ; 799F
                     lda  $92                              ; 79A2
                     sta  RCoin                            ; 79A4
                     lda  $85                              ; 79A7
                     eor  #$03                             ; 79A9
                     ror  A                                ; 79AB
                     ror  A                                ; 79AC
                     sta  P1LED                            ; 79AD
                     ror  A                                ; 79B0
                     sta  P2LED                            ; 79B1
                     lda  $8e                              ; 79B4
                     beq  L79c2                            ; 79B6
                                                           ; 0A -> +10
                     lda  #$08                             ; 79B8
                     ldy  #$af                             ; 79BA
                     sta  Pk_F1_Pot0                       ; 79BC
                     sty  Pk_C1_Pot1                       ; 79BF

L79c2                lda  #$00                             ; 79C2
                     asl  FireSW                           ; 79C4
                     bcc  L79ce                            ; 79C7
                                                           ; 05 -> +5
                     lda  $fe                              ; 79C9
                     ora  #$08                             ; 79CB
                     asl  A                                ; 79CD

L79ce                sta  $fe                              ; 79CE
                     pla                                   ; 79D0
                     tax                                   ; 79D1
                     pla                                   ; 79D2
                     tay                                   ; 79D3
                     pla                                   ; 79D4
                     rti                                   ; 79D5

L79d6                lda  #$d0                             ; 79D6
                     bne  L79dc                            ; 79D8
                                                           ; 02 -> +2

L79da                lda  #$b0                             ; 79DA

L79dc                ldy  #$00                             ; 79DC
                     sta  ($03),Y                          ; 79DE
                     iny                                   ; 79E0
                     sta  ($03),Y                          ; 79E1
                     bne  L7a55                            ; 79E3
                                                           ; 70 -> +112

L79e5                bcc  L79eb                            ; 79E5
                                                           ; 04 -> +4
                     and  #$0f                             ; 79E7
                     beq  L79f0                            ; 79E9
                                                           ; 05 -> +5

L79eb                and  #$0f                             ; 79EB
                     clc                                   ; 79ED
                     adc  #$01                             ; 79EE

L79f0                php                                   ; 79F0
                     asl  A                                ; 79F1
                     tay                                   ; 79F2
                     jsr  L79f8                            ; 79F3
                     plp                                   ; 79F6
                     rts                                   ; 79F7

L79f8                cpy  #$4a                             ; 79F8
                     bcc  L79fe                            ; 79FA
                                                           ; 02 -> +2
                     ldy  #$00                             ; 79FC

L79fe                ldx  $56f9,Y                          ; 79FE
                     lda  $56f8,Y                          ; 7A01
                     jmp  L7cd5                            ; 7A04
                     fcb  $4A,$29,$0F,$09,$E0                

L7a0c                ldy  #$01                             ; 7A0C
                     sta  ($03),Y                          ; 7A0E
                     dey                                   ; 7A10
                     txa                                   ; 7A11
                     ror  A                                ; 7A12
                     sta  ($03),Y                          ; 7A13
                     iny                                   ; 7A15
                     bne  L7a55                            ; 7A16
                                                           ; 3D -> +61

L7a18                lsr  A                                ; 7A18
                     and  #$0f                             ; 7A19
                     ora  #$c0                             ; 7A1B
                     bne  L7a0c                            ; 7A1D
                                                           ; ED -> 12 ->  -19

L7a1f                ldy  #$00                             ; 7A1F
                     sty  $06                              ; 7A21
                     sty  $08                              ; 7A23
                     asl  A                                ; 7A25
                     rol  $06                              ; 7A26
                     asl  A                                ; 7A28
                     rol  $06                              ; 7A29
                     sta  $05                              ; 7A2B
                     txa                                   ; 7A2D
                     asl  A                                ; 7A2E
                     rol  $08                              ; 7A2F
                     asl  A                                ; 7A31
                     rol  $08                              ; 7A32
                     sta  $07                              ; 7A34
                     ldx  #$05                             ; 7A36

L7a38                lda  $02,X                            ; 7A38
                     ldy  #$00                             ; 7A3A
                     sta  ($03),Y                          ; 7A3C
                     lda  $03,X                            ; 7A3E
                     and  #$0f                             ; 7A40
                     ora  #$a0                             ; 7A42
                     iny                                   ; 7A44
                     sta  ($03),Y                          ; 7A45
                     lda  $00,X                            ; 7A47
                     iny                                   ; 7A49
                     sta  ($03),Y                          ; 7A4A
                     lda  $01,X                            ; 7A4C
                     and  #$0f                             ; 7A4E
                     ora  $01                              ; 7A50
                     iny                                   ; 7A52
                     sta  ($03),Y                          ; 7A53

L7a55                tya                                   ; 7A55
                     sec                                   ; 7A56
                     adc  $03                              ; 7A57
                     sta  $03                              ; 7A59
                     bcc  L7a5f                            ; 7A5B
                                                           ; 02 -> +2
                     inc  $04                              ; 7A5D

L7a5f                rts                                   ; 7A5F
                     fcb  $A2,$00,$A5,$06,$C9,$80,$90,$0A    
                     fcb  $8A,$E5,$05,$85,$05,$8A,$E5,$06    
                     fcb  $85,$06,$26,$09,$A5,$08,$C9,$80    
                     fcb  $90,$0A,$8A,$E5,$07,$85,$07,$8A    
                     fcb  $E5,$08,$85,$08,$26,$09,$05,$06    
                     fcb  $F0,$08,$C9,$02,$B0,$24,$A0,$01    
                     fcb  $D0,$10,$A0,$02,$A2,$09,$A5,$05    
                     fcb  $05,$07,$F0,$16,$30,$04,$C8,$0A    
                     fcb  $10,$FC,$98,$AA,$A5,$06,$06,$05    
                     fcb  $2A,$06,$07,$26,$08,$88,$D0,$F6    
                     fcb  $85,$06,$8A,$38,$E9,$0A,$49,$FF    
                     fcb  $0A,$66,$09,$2A,$66,$09,$2A,$0A    
                     fcb  $85,$09,$A0,$00,$A5,$07,$91,$03    
                     fcb  $A5,$09,$29,$F4,$05,$08,$C8,$91    
                     fcb  $03,$A5,$05,$C8,$91,$03,$A5,$09    
                     fcb  $29,$02,$0A,$05,$02,$05,$06,$C8    
                     fcb  $91,$03,$4C,$55,$7A                

L7ae5                jsr  L7a1f                            ; 7AE5
                     lda  #$70                             ; 7AE8

L7aea                ldx  #$00                             ; 7AEA

L7aec                ldy  #$01                             ; 7AEC
                     sta  ($03),Y                          ; 7AEE
                     dey                                   ; 7AF0
                     tya                                   ; 7AF1
                     sta  ($03),Y                          ; 7AF2
                     iny                                   ; 7AF4
                     iny                                   ; 7AF5
                     sta  ($03),Y                          ; 7AF6
                     iny                                   ; 7AF8
                     txa                                   ; 7AF9
                     sta  ($03),Y                          ; 7AFA
                     jmp  L7a55                            ; 7AFC

L7aff                lda  $78                              ; 7AFF
                     and  #$0c                             ; 7B01
                     bne  L7b26                            ; 7B03
                                                           ; 21 -> +33
                     lda  $cd                              ; 7B05
                     beq  L7b23                            ; 7B07
                                                           ; 1A -> +26
                     bpl  L7b27                            ; 7B09
                                                           ; 1C -> +28
                     ldx  $cb                              ; 7B0B
                     lda  #$06                             ; 7B0D
                     sta  EAControl                        ; 7B0F
                     sta  LatchEA,X                        ; 7B12
                     lda  #$0e                             ; 7B15
                     dec  $cb                              ; 7B17
                     dec  $cc                              ; 7B19
                     bne  L7b23                            ; 7B1B
                                                           ; 06 -> +6
                     ldx  #$40                             ; 7B1D
                     stx  $cd                              ; 7B1F

L7b21                inc  $cb                              ; 7B21

L7b23                sta  EAControl                        ; 7B23

L7b26                rts                                   ; 7B26

L7b27                ldy  $cc                              ; 7B27
                     bne  L7b2d                            ; 7B29
                                                           ; 02 -> +2
                     sty  $cf                              ; 7B2B

L7b2d                asl  A                                ; 7B2D
                     bpl  L7b65                            ; 7B2E
                                                           ; 35 -> +53
                     lda  $7bc0,Y                          ; 7B30
                     bpl  L7b41                            ; 7B33
                                                           ; 0C -> +12
                     sta  $cc                              ; 7B35
                     inc  $ce                              ; 7B37
                     inc  $ce                              ; 7B39
                     inc  $ce                              ; 7B3B
                     lda  $cf                              ; 7B3D
                     bcc  L7b4c                            ; 7B3F
                                                           ; 0B -> +11

L7b41                adc  $ce                              ; 7B41
                     tax                                   ; 7B43
                     lda  $23,X                            ; 7B44
                     adc  $cf                              ; 7B46
                     sta  $cf                              ; 7B48
                     lda  $23,X                            ; 7B4A

L7b4c                inc  $cc                              ; 7B4C
                     ldx  $cb                              ; 7B4E
                     sta  LatchEA,X                        ; 7B50
                     lda  #$04                             ; 7B53
                     sta  EAControl                        ; 7B55
                     lda  #$0c                             ; 7B58

L7b5a                inx                                   ; 7B5A
                     cpx  #$15                             ; 7B5B
                     bcc  L7b21                            ; 7B5D
                                                           ; C2 -> 3D ->  -62
                     ldx  #$00                             ; 7B5F
                     stx  $cd                              ; 7B61
                     beq  L7b23                            ; 7B63
                                                           ; BE -> 41 ->  -66

L7b65                ldx  $cb                              ; 7B65
                     lda  #$08                             ; 7B67
                     sta  LatchEA,X                        ; 7B69
                     sta  EAControl                        ; 7B6C
                     lda  #$09                             ; 7B6F
                     sta  EAControl                        ; 7B71
                     lda  #$08                             ; 7B74
                     sta  EAControl                        ; 7B76
                     ldx  #$00                             ; 7B79
                     lda  $7bc0,Y                          ; 7B7B
                     bpl  L7baa                            ; 7B7E
                                                           ; 2A -> +42
                     stx  $cc                              ; 7B80
                     lda  EaromRd                          ; 7B82
                     stx  EAControl                        ; 7B85
                     eor  $cf                              ; 7B88
                     beq  L7ba2                            ; 7B8A
                                                           ; 16 -> +22
                     ldy  #$02                             ; 7B8C
                     tya                                   ; 7B8E
                     adc  $ce                              ; 7B8F
                     tax                                   ; 7B91
                     lda  #$00                             ; 7B92

L7b94                sta  $23,X                            ; 7B94
                     sta  $44,X                            ; 7B96
                     dex                                   ; 7B98
                     dey                                   ; 7B99
                     bpl  L7b94                            ; 7B9A
                                                           ; F8 -> 07 ->  -8
                     inc  $d0                              ; 7B9C

L7b9e                ldx  $cb                              ; 7B9E
                     bpl  L7b5a                            ; 7BA0
                                                           ; B8 -> 47 ->  -72

L7ba2                inc  $ce                              ; 7BA2
                     inc  $ce                              ; 7BA4
                     inc  $ce                              ; 7BA6
                     bpl  L7b9e                            ; 7BA8
                                                           ; F4 -> 0B ->  -12

L7baa                adc  $ce                              ; 7BAA
                     tay                                   ; 7BAC
                     lda  EaromRd                          ; 7BAD
                     stx  EAControl                        ; 7BB0
                     sta  $0023,Y                          ; 7BB3
                     adc  $cf                              ; 7BB6
                     sta  $cf                              ; 7BB8
                     inc  $cc                              ; 7BBA
                     lda  #$00                             ; 7BBC
                     beq  L7b9e                            ; 7BBE
                                                           ; DE -> 21 ->  -34
                     brk                                   ; 7BC0
                     ora  ($02,X)                          ; 7BC1
                     and  ($22,X)                          ; 7BC3
                     fcb  $23,$FF                            

L7bc7                ldy  $cd                              ; 7BC7
                     bne  L7be2                            ; 7BC9
                                                           ; 17 -> +23
                     lda  #$08                             ; 7BCB
                     cmp  $ce                              ; 7BCD
                     bcc  L7be2                            ; 7BCF
                                                           ; 11 -> +17
                     ror  $cd                              ; 7BD1
                     lda  $d0                              ; 7BD3
                     beq  L7be2                            ; 7BD5
                                                           ; 0B -> +11
                     ldx  #$15                             ; 7BD7
                     stx  $cc                              ; 7BD9
                     dex                                   ; 7BDB
                     stx  $cb                              ; 7BDC
                     sty  $ce                              ; 7BDE
                     sty  $d0                              ; 7BE0

L7be2                rts                                   ; 7BE2

L7be3                bit  VGHalted                         ; 7BE3
                     bmi  L7be3                            ; 7BE6
                                                           ; FB -> 04 ->  -5
                     jsr  L7118                            ; 7BE8
                     lda  #$b0                             ; 7BEB
                     sta  $4003                            ; 7BED
                     lda  #$00                             ; 7BF0
                     ldx  #$03                             ; 7BF2

L7bf4                sta  $61,X                            ; 7BF4
                     sta  $64,X                            ; 7BF6
                     dex                                   ; 7BF8
                     bne  L7bf4                            ; 7BF9
                                                           ; F9 -> 06 ->  -7

L7bfb                sta  $0200,X                          ; 7BFB
                     inx                                   ; 7BFE
                     bne  L7bfb                            ; 7BFF
                                                           ; FA -> 05 ->  -6
                     sta  $dd                              ; 7C01
                     sta  $d3                              ; 7C03
                     sta  $fa                              ; 7C05
                     sta  $fc                              ; 7C07
                     lda  Option65                         ; 7C09
                     and  #$02                             ; 7C0C
                     sta  $fb                              ; 7C0E
                     sta  $fd                              ; 7C10
                     lda  #$01                             ; 7C12
                     jsr  L6300                            ; 7C14
                     lda  #$98                             ; 7C17
                     sta  $02e9                            ; 7C19
                     sta  $02e8                            ; 7C1C
                     lda  #$7f                             ; 7C1F
                     sta  $02ec                            ; 7C21
                     lda  #$06                             ; 7C24
                     sta  $02ee                            ; 7C26
                     lda  #$ff                             ; 7C29
                     sta  $42                              ; 7C2B
                     sta  $43                              ; 7C2D
                     lda  #$30                             ; 7C2F
                     sta  $02ed                            ; 7C31

L7c34                jsr  L7fcf                            ; 7C34
                     lda  Option87                         ; 7C37
                     and  #$03                             ; 7C3A
                     tay                                   ; 7C3C
                     lda  $7c6b,Y                          ; 7C3D
                     sta  $f8                              ; 7C40
                     sta  $69                              ; 7C42
                     sta  $6c                              ; 7C44
                     bmi  L7c4a                            ; 7C46
                                                           ; 02 -> +2
                     lda  #$01                             ; 7C48

L7c4a                sta  $6a                              ; 7C4A
                     sta  $f9                              ; 7C4C
                     sta  $6d                              ; 7C4E
                     lda  #$03                             ; 7C50
                     and  Option43                         ; 7C52
                     tax                                   ; 7C55
                     inx                                   ; 7C56
                     inx                                   ; 7C57
                     cpy  #$03                             ; 7C58
                     bne  L7c5d                            ; 7C5A
                                                           ; 01 -> +1
                     inx                                   ; 7C5C

L7c5d                lda  $8d                              ; 7C5D
                     and  #$03                             ; 7C5F
                     cmp  #$03                             ; 7C61
                     bne  L7c66                            ; 7C63
                                                           ; 01 -> +1
                     inx                                   ; 7C65

L7c66                stx  $6e                              ; 7C66
                     jmp  L7844                            ; 7C68
                     fcb  $00,$20,$50,$FF                    

L7c6f                ldx  #$d5                             ; 7C6F

L7c71                sty  $09                              ; 7C71
                     ldy  #$e0                             ; 7C73
                     sty  $01                              ; 7C75
                     jsr  L7a1f                            ; 7C77
                     lda  #$70                             ; 7C7A
                     jsr  L7aea                            ; 7C7C
                     jmp  L7c89                            ; 7C7F

L7c82                ldx  #$ca                             ; 7C82
                     lda  #$a4                             ; 7C84
                     jsr  L7cd5                            ; 7C86

L7c89                dec  $09                              ; 7C89
                     beq  L7c8f                            ; 7C8B
                                                           ; 02 -> +2
                     bpl  L7c82                            ; 7C8D
                                                           ; F3 -> 0C ->  -13

L7c8f                rts                                   ; 7C8F

L7c90                lda  #$f7                             ; 7C90
                     ldy  #$03                             ; 7C92
                     sec                                   ; 7C94

L7c95                php                                   ; 7C95
                     stx  $1d                              ; 7C96
                     dey                                   ; 7C98
                     sty  $1c                              ; 7C99
                     clc                                   ; 7C9B
                     adc  $1c                              ; 7C9C
                     sta  $1b                              ; 7C9E
                     plp                                   ; 7CA0
                     tax                                   ; 7CA1

L7ca2                php                                   ; 7CA2
                     lda  $00,X                            ; 7CA3
                     lsr  A                                ; 7CA5
                     lsr  A                                ; 7CA6
                     lsr  A                                ; 7CA7
                     lsr  A                                ; 7CA8
                     plp                                   ; 7CA9
                     jsr  L79e5                            ; 7CAA
                     lda  $1c                              ; 7CAD
                     bne  L7cb2                            ; 7CAF
                                                           ; 01 -> +1
                     clc                                   ; 7CB1

L7cb2                ldx  $1b                              ; 7CB2
                     lda  $00,X                            ; 7CB4
                     jsr  L79e5                            ; 7CB6
                     dec  $1b                              ; 7CB9
                     ldx  $1b                              ; 7CBB
                     dec  $1c                              ; 7CBD
                     bpl  L7ca2                            ; 7CBF
                                                           ; E1 -> 1E ->  -31
                     rts                                   ; 7CC1

L7cc2                jsr  L7cc5                            ; 7CC2

L7cc5                ldx  $0c                              ; 7CC5
                     dec  $0c                              ; 7CC7
                     lda  Option87,X                       ; 7CC9
                     and  #$03                             ; 7CCC

L7cce                jsr  L79eb                            ; 7CCE
                     lda  #$0a                             ; 7CD1
                     ldx  #$cb                             ; 7CD3

L7cd5                ldy  #$00                             ; 7CD5
                     sta  ($03),Y                          ; 7CD7
                     iny                                   ; 7CD9
                     txa                                   ; 7CDA
                     sta  ($03),Y                          ; 7CDB
                     jmp  L7a55                            ; 7CDD

Reset_Handler        ldx  #$fe                             ; 7CE0
                     txs                                   ; 7CE2
                     cld                                   ; 7CE3
                     ldx  #$00                             ; 7CE4
                     stx  Pk_SerCtl                        ; 7CE6

L7ce9                lda  #$11                             ; 7CE9

L7ceb                sta  $0100,X                          ; 7CEB
                     tay                                   ; 7CEE
                     eor  $0100,X                          ; 7CEF
                     bne  L7d48                            ; 7CF2
                                                           ; 54 -> +84
                     tya                                   ; 7CF4
                     asl  A                                ; 7CF5
                     bcc  L7ceb                            ; 7CF6
                                                           ; F3 -> 0C ->  -13
                     txa                                   ; 7CF8
                     sta  $00,X                            ; 7CF9
                     sta  $0100,X                          ; 7CFB
                     sta  $0200,X                          ; 7CFE
                     sta  $0300,X                          ; 7D01
                     sta  VRAM,X                           ; 7D04
                     sta  $4100,X                          ; 7D07
                     sta  $4200,X                          ; 7D0A
                     sta  $4300,X                          ; 7D0D
                     sta  $4400,X                          ; 7D10
                     sta  $4500,X                          ; 7D13
                     sta  $4600,X                          ; 7D16
                     sta  $4700,X                          ; 7D19
                     dex                                   ; 7D1C
                     bne  L7ce9                            ; 7D1D
                                                           ; CA -> 35 ->  -54
                     sta  WdogReset                        ; 7D1F

L7d22                txa                                   ; 7D22

L7d23                eor  $0100,X                          ; 7D23
                     bne  L7d48                            ; 7D26
                                                           ; 20 -> +32
                     sta  $0100,X                          ; 7D28
                     inx                                   ; 7D2B
                     bit  SelfTestSW                       ; 7D2C
                     bpl  L7d36                            ; 7D2F
                                                           ; 05 -> +5
                     txa                                   ; 7D31
                     bne  L7d23                            ; 7D32
                                                           ; EF -> 10 ->  -17
                     beq  L7d3c                            ; 7D34
                                                           ; 06 -> +6

L7d36                cpx  #$fb                             ; 7D36
                     bcc  L7d22                            ; 7D38
                                                           ; E8 -> 17 ->  -24
                     ldx  #$00                             ; 7D3A

L7d3c                txa                                   ; 7D3C
                     eor  $00,X                            ; 7D3D
                     bne  L7d48                            ; 7D3F
                                                           ; 07 -> +7
                     lda  #$11                             ; 7D41

L7d43                sta  $00,X                            ; 7D43
                     tay                                   ; 7D45
                     eor  $00,X                            ; 7D46

L7d48                bne  L7d8b                            ; 7D48
                                                           ; 41 -> +65
                     tya                                   ; 7D4A
                     asl  A                                ; 7D4B
                     bcc  L7d43                            ; 7D4C
                                                           ; F5 -> 0A ->  -11
                     ldy  #$00                             ; 7D4E
                     sty  $00,X                            ; 7D50
                     dex                                   ; 7D52
                     bne  L7d3c                            ; 7D53
                                                           ; E7 -> 18 ->  -25
                     sta  WdogReset                        ; 7D55
                     lda  #$02                             ; 7D58

L7d5a                sta  $01                              ; 7D5A

L7d5c                tya                                   ; 7D5C
                     eor  ($00),Y                          ; 7D5D
                     bne  L7d8f                            ; 7D5F
                                                           ; 2E -> +46
                     lda  #$11                             ; 7D61

L7d63                sta  ($00),Y                          ; 7D63
                     tax                                   ; 7D65
                     eor  ($00),Y                          ; 7D66
                     bne  L7d8f                            ; 7D68
                                                           ; 25 -> +37
                     sta  ($00),Y                          ; 7D6A
                     txa                                   ; 7D6C
                     asl  A                                ; 7D6D
                     bcc  L7d63                            ; 7D6E
                                                           ; F3 -> 0C ->  -13
                     iny                                   ; 7D70
                     bne  L7d5c                            ; 7D71
                                                           ; E9 -> 16 ->  -23
                     sta  WdogReset                        ; 7D73
                     inc  $01                              ; 7D76
                     ldx  $01                              ; 7D78
                     cpx  #$04                             ; 7D7A
                     bcc  L7d5c                            ; 7D7C
                                                           ; DE -> 21 ->  -34
                     lda  #$40                             ; 7D7E
                     cpx  #$40                             ; 7D80
                     bcc  L7d5a                            ; 7D82
                                                           ; D6 -> 29 ->  -42
                     cpx  #$48                             ; 7D84
                     bcc  L7d5c                            ; 7D86
                                                           ; D4 -> 2B ->  -44
                     bcs  L7dfc                            ; 7D88
                                                           ; 72 -> +114
                     fcb  $64                                

L7d8b                ldy  #$00                             ; 7D8B
                     beq  L7d9d                            ; 7D8D
                                                           ; 0E -> +14

L7d8f                ldy  #$00                             ; 7D8F
                     ldx  $01                              ; 7D91
                     cpx  #$04                             ; 7D93
                     bcc  L7d9d                            ; 7D95
                                                           ; 06 -> +6
                     iny                                   ; 7D97
                     cpx  #$44                             ; 7D98
                     bcc  L7d9d                            ; 7D9A
                                                           ; 01 -> +1
                     iny                                   ; 7D9C

L7d9d                cmp  #$10                             ; 7D9D
                     rol  A                                ; 7D9F
                     and  #$1f                             ; 7DA0
                     cmp  #$02                             ; 7DA2
                     rol  A                                ; 7DA4
                     and  #$03                             ; 7DA5

L7da7                dey                                   ; 7DA7
                     bmi  L7dae                            ; 7DA8
                                                           ; 04 -> +4
                     asl  A                                ; 7DAA
                     asl  A                                ; 7DAB
                     bcc  L7da7                            ; 7DAC
                                                           ; F9 -> 06 ->  -7

L7dae                lsr  A                                ; 7DAE
                     ldy  #$07                             ; 7DAF
                     sty  Pk_SerCtl                        ; 7DB1
                     ldx  #$20                             ; 7DB4
                     bcc  L7dba                            ; 7DB6
                                                           ; 02 -> +2
                     ldx  #$80                             ; 7DB8

L7dba                stx  Pk_F1_Pot0                       ; 7DBA
                     ldx  #$a8                             ; 7DBD
                     stx  Pk_C1_Pot1                       ; 7DBF
                     ldx  #$00                             ; 7DC2

L7dc4                bit  ThreeKHz                         ; 7DC4
                     bpl  L7dc4                            ; 7DC7
                                                           ; FB -> 04 ->  -5

L7dc9                bit  ThreeKHz                         ; 7DC9
                     bmi  L7dc9                            ; 7DCC
                                                           ; FB -> 04 ->  -5
                     dex                                   ; 7DCE
                     sta  WdogReset                        ; 7DCF
                     bne  L7dc4                            ; 7DD2
                                                           ; F0 -> 0F ->  -16
                     dey                                   ; 7DD4
                     bpl  L7dc4                            ; 7DD5
                                                           ; ED -> 12 ->  -19
                     stx  Pk_C1_Pot1                       ; 7DD7
                     ldy  #$08                             ; 7DDA

L7ddc                bit  ThreeKHz                         ; 7DDC
                     bpl  L7ddc                            ; 7DDF
                                                           ; FB -> 04 ->  -5

L7de1                bit  ThreeKHz                         ; 7DE1
                     bmi  L7de1                            ; 7DE4
                                                           ; FB -> 04 ->  -5
                     dex                                   ; 7DE6
                     sta  WdogReset                        ; 7DE7
                     bne  L7ddc                            ; 7DEA
                                                           ; F0 -> 0F ->  -16
                     dey                                   ; 7DEC
                     bne  L7ddc                            ; 7DED
                                                           ; ED -> 12 ->  -19
                     tax                                   ; 7DEF
                     bne  L7dae                            ; 7DF0
                                                           ; BC -> 43 ->  -68

L7df2                sta  WdogReset                        ; 7DF2
                     lda  SelfTestSW                       ; 7DF5
                     bmi  L7df2                            ; 7DF8
                                                           ; F8 -> 07 ->  -8

L7dfa                bpl  L7dfa                            ; 7DFA
                                                           ; FE -> 01 ->  -2

L7dfc                lda  #$00                             ; 7DFC
                     tay                                   ; 7DFE
                     tax                                   ; 7DFF
                     lda  #$48                             ; 7E00

L7e02                sta  $0a                              ; 7E02
                     lda  #$07                             ; 7E04
                     sta  $0c                              ; 7E06
                     lda  #$55                             ; 7E08
                     clc                                   ; 7E0A

L7e0b                adc  ($09),Y                          ; 7E0B
                     iny                                   ; 7E0D
                     bne  L7e0b                            ; 7E0E
                                                           ; FB -> 04 ->  -5
                     inc  $0a                              ; 7E10
                     dec  $0c                              ; 7E12
                     bpl  L7e0b                            ; 7E14
                                                           ; F5 -> 0A ->  -11
                     sta  $10,X                            ; 7E16
                     inx                                   ; 7E18
                     sta  WdogReset                        ; 7E19
                     lda  $0a                              ; 7E1C
                     cmp  #$58                             ; 7E1E
                     bcc  L7e02                            ; 7E20
                                                           ; E0 -> 1F ->  -32
                     bne  L7e26                            ; 7E22
                                                           ; 02 -> +2
                     lda  #$60                             ; 7E24

L7e26                cmp  #$80                             ; 7E26
                     bcc  L7e02                            ; 7E28
                                                           ; D8 -> 27 ->  -40
                     sta  $0300                            ; 7E2A
                     sta  BankSel                          ; 7E2D
                     cmp  $0200                            ; 7E30
                     beq  L7e37                            ; 7E33
                                                           ; 02 -> +2
                     inc  $1a                              ; 7E35

L7e37                lda  $0300                            ; 7E37
                     beq  L7e3e                            ; 7E3A
                                                           ; 02 -> +2
                     inc  $1a                              ; 7E3C

L7e3e                lda  #$10                             ; 7E3E
                     sta  $01                              ; 7E40
                     sta  BankSel                          ; 7E42
                     ldx  #$24                             ; 7E45

L7e47                lda  ThreeKHz                         ; 7E47
                     bpl  L7e47                            ; 7E4A
                                                           ; FB -> 04 ->  -5

L7e4c                lda  ThreeKHz                         ; 7E4C
                     bmi  L7e4c                            ; 7E4F
                                                           ; FB -> 04 ->  -5
                     dex                                   ; 7E51
                     bpl  L7e47                            ; 7E52
                                                           ; F3 -> 0C ->  -13

L7e54                bit  VGHalted                         ; 7E54
                     bmi  L7e54                            ; 7E57
                                                           ; FB -> 04 ->  -5
                     sta  WdogReset                        ; 7E59
                     lda  #$00                             ; 7E5C
                     sta  $03                              ; 7E5E
                     lda  #$40                             ; 7E60
                     sta  $04                              ; 7E62
                     lda  SelfTestSW                       ; 7E64
                     and  #$80                             ; 7E67
                     bne  L7e71                            ; 7E69
                                                           ; 06 -> +6
                     sta  $01ff                            ; 7E6B
                     jmp  L6000                            ; 7E6E

L7e71                lda  $1a                              ; 7E71
                     beq  L7e7c                            ; 7E73
                                                           ; 07 -> +7
                     ldx  #$cc                             ; 7E75
                     lda  #$57                             ; 7E77
                     jsr  L7a18                            ; 7E79

L7e7c                ldx  #$96                             ; 7E7C
                     stx  $0d                              ; 7E7E
                     ldx  #$05                             ; 7E80

L7e82                lda  $10,X                            ; 7E82
                     beq  L7ea7                            ; 7E84
                                                           ; 21 -> +33
                     stx  $0c                              ; 7E86
                     ldx  $0d                              ; 7E88
                     txa                                   ; 7E8A
                     sec                                   ; 7E8B
                     sbc  #$08                             ; 7E8C
                     sta  $0d                              ; 7E8E
                     lda  #$20                             ; 7E90
                     jsr  L7ae5                            ; 7E92
                     ldx  $0c                              ; 7E95
                     ldy  $7fee,X                          ; 7E97
                     jsr  L79f8                            ; 7E9A
                     ldx  $0c                              ; 7E9D
                     ldy  $7ff4,X                          ; 7E9F
                     jsr  L79f8                            ; 7EA2
                     ldx  $0c                              ; 7EA5

L7ea7                dex                                   ; 7EA7
                     bpl  L7e82                            ; 7EA8
                                                           ; D8 -> 27 ->  -40
                     lda  #$57                             ; 7EAA
                     ldx  #$44                             ; 7EAC
                     jsr  L7a18                            ; 7EAE
                     lda  #$93                             ; 7EB1
                     ldx  #$a0                             ; 7EB3
                     jsr  L7ae5                            ; 7EB5
                     ldx  #$03                             ; 7EB8
                     stx  $0c                              ; 7EBA
                     jsr  L7cc2                            ; 7EBC
                     dec  $0c                              ; 7EBF
                     lda  Option65                         ; 7EC1
                     pha                                   ; 7EC4
                     and  #$01                             ; 7EC5
                     jsr  L7cce                            ; 7EC7
                     pla                                   ; 7ECA
                     and  #$02                             ; 7ECB
                     lsr  A                                ; 7ECD
                     jsr  L7cce                            ; 7ECE
                     jsr  L7cc5                            ; 7ED1
                     lda  #$93                             ; 7ED4
                     ldx  #$b0                             ; 7ED6
                     jsr  L7ae5                            ; 7ED8
                     lda  #$07                             ; 7EDB
                     sta  Pk_SerCtl                        ; 7EDD
                     sta  Pk_PotGo                         ; 7EE0
                     lda  Pk_Ctl_All                       ; 7EE3
                     eor  #$ff                             ; 7EE6
                     sta  $0c                              ; 7EE8
                     sta  $8d                              ; 7EEA
                     asl  A                                ; 7EEC
                     rol  A                                ; 7EED
                     rol  A                                ; 7EEE
                     rol  A                                ; 7EEF
                     rol  $0d                              ; 7EF0
                     and  #$07                             ; 7EF2
                     jsr  L7cce                            ; 7EF4
                     lda  $0d                              ; 7EF7
                     and  #$01                             ; 7EF9
                     jsr  L7cce                            ; 7EFB
                     lda  $0c                              ; 7EFE
                     lsr  A                                ; 7F00
                     lsr  A                                ; 7F01
                     and  #$03                             ; 7F02
                     jsr  L7cce                            ; 7F04
                     lda  $0c                              ; 7F07
                     and  #$03                             ; 7F09
                     jsr  L7cce                            ; 7F0B
                     jsr  L7c34                            ; 7F0E
                     ldy  $6e                              ; 7F11
                     lda  #$96                             ; 7F13
                     ldx  #$94                             ; 7F15
                     iny                                   ; 7F17
                     jsr  L7c71                            ; 7F18
                     lda  #$10                             ; 7F1B
                     sta  $01                              ; 7F1D
                     lda  $f9                              ; 7F1F
                     bmi  L7f2d                            ; 7F21
                                                           ; 0A -> +10
                     lda  #$8e                             ; 7F23
                     ldx  #$83                             ; 7F25
                     jsr  L7ae5                            ; 7F27
                     jsr  L7c90                            ; 7F2A

L7f2d                lda  $d4                              ; 7F2D
                     beq  L7f38                            ; 7F2F
                                                           ; 07 -> +7
                     ldx  #$cb                             ; 7F31
                     lda  #$f4                             ; 7F33
                     jsr  L7cd5                            ; 7F35

L7f38                inc  $76                              ; 7F38
                     lda  FireSW                           ; 7F3A
                     and  ThrustSW                         ; 7F3D
                     and  RotateLSW                        ; 7F40
                     and  RotateRSW                        ; 7F43
                     bpl  L7f57                            ; 7F46
                                                           ; 0F -> +15
                     bit  $21                              ; 7F48
                     bmi  L7f57                            ; 7F4A
                                                           ; 0B -> +11
                     sta  $cd                              ; 7F4C
                     sta  $21                              ; 7F4E
                     ldx  #$15                             ; 7F50
                     stx  $cc                              ; 7F52
                     dex                                   ; 7F54
                     stx  $cb                              ; 7F55

L7f57                lda  $21                              ; 7F57
                     beq  L7f77                            ; 7F59
                                                           ; 1C -> +28
                     lda  $cd                              ; 7F5B
                     beq  L7f77                            ; 7F5D
                                                           ; 18 -> +24
                     lda  #$94                             ; 7F5F
                     ldx  #$72                             ; 7F61
                     jsr  L7ae5                            ; 7F63
                     ldx  #$f2                             ; 7F66
                     lda  #$57                             ; 7F68
                     jsr  L7a18                            ; 7F6A
                     jsr  L7aff                            ; 7F6D
                     lda  $78                              ; 7F70
                     clc                                   ; 7F72
                     adc  #$04                             ; 7F73
                     sta  $78                              ; 7F75

L7f77                lda  #$7f                             ; 7F77
                     tax                                   ; 7F79
                     jsr  L7a1f                            ; 7F7A
                     jsr  L79da                            ; 7F7D
                     ldy  #$08                             ; 7F80
                     lda  #$00                             ; 7F82

L7f84                sta  $2bff,Y                          ; 7F84
                     dey                                   ; 7F87
                     bne  L7f84                            ; 7F88
                                                           ; FA -> 05 ->  -6
                     jsr  L7fa4                            ; 7F8A
                     ora  $88                              ; 7F8D
                     ora  $87                              ; 7F8F
                     ora  $86                              ; 7F91
                     beq  L7f97                            ; 7F93
                                                           ; 02 -> +2
                     lda  #$a4                             ; 7F95

L7f97                sta  Pk_C1_Pot1                       ; 7F97
                     lsr  A                                ; 7F9A
                     sta  Pk_F1_Pot0                       ; 7F9B
                     sta  StartVG                          ; 7F9E
                     jmp  L7e3e                            ; 7FA1

L7fa4                jsr  L7fa7                            ; 7FA4

L7fa7                ldx  #$07                             ; 7FA7

L7fa9                rol  LCoinSW,X                        ; 7FA9
                     ror  A                                ; 7FAC
                     dex                                   ; 7FAD
                     bpl  L7fa9                            ; 7FAE
                                                           ; F9 -> 06 ->  -7
                     jsr  L7fc4                            ; 7FB0
                     ldx  #$04                             ; 7FB3

L7fb5                rol  ShieldSW,X                       ; 7FB5
                     ror  A                                ; 7FB8
                     dex                                   ; 7FB9
                     bpl  L7fb5                            ; 7FBA
                                                           ; F9 -> 06 ->  -7
                     stx  BankSel                          ; 7FBC
                     ldx  #$64                             ; 7FBF

L7fc1                dex                                   ; 7FC1
                     bpl  L7fc1                            ; 7FC2
                                                           ; FD -> 02 ->  -3

L7fc4                tax                                   ; 7FC4
                     eor  $0016,Y                          ; 7FC5
                     sta  $0086,Y                          ; 7FC8
                     stx  $16,Y                            ; 7FCB
                     iny                                   ; 7FCD
                     rts                                   ; 7FCE

L7fcf                lda  $76                              ; 7FCF
                     and  #$03                             ; 7FD1
                     tax                                   ; 7FD3
                     lda  Pk_SkRes_Rnd                     ; 7FD4
                     sta  $d5,X                            ; 7FD7
                     ldy  #$00                             ; 7FD9
                     ldx  #$04                             ; 7FDB

L7fdd                cmp  $d4,X                            ; 7FDD
                     bne  L7fe2                            ; 7FDF
                                                           ; 01 -> +1
                     iny                                   ; 7FE1

L7fe2                dex                                   ; 7FE2
                     bne  L7fdd                            ; 7FE3
                                                           ; F8 -> 07 ->  -8
                     cpy  #$04                             ; 7FE5
                     lda  Pk_Ctl_All                       ; 7FE7
                     ror  A                                ; 7FEA
                     sta  $d4                              ; 7FEB
                     rts                                   ; 7FED
                     fcb  $38,$30,$1C,$1E,$24,$28,$06,$06    
                     fcb  $04,$04,$04,$04                    
                     fdb  IRQ_Handler                      ; 7FFA
                     fdb  Reset_Handler                    ; 7FFC
                     fdb  Reset_Handler                    ; 7FFE
