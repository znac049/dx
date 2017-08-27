#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

const char *EngineX09::mne[] = {
  "???", "abx", "adca", "adcb", "adda", "addb", "addd", "anda", "andb",
  "andcc", "asla", "aslb", "asl", "asra", "asrb", "asr", "bcc", "lbcc",
  "bcs", "lbcs", "beq", "lbeq", "bge", "lbge", "bgt", "lbgt", "bhi",
  "lbhi", "bita", "bitb", "ble", "lble", "bls", "lbls", "blt", "lblt",
  "bmi", "lbmi", "bne", "lbne", "bpl", "lbpl", "bra", "lbra", "brn",
  "lbrn", "bsr", "lbsr", "bvc", "lbvc", "bvs", "lbvs", "clra", "clrb",
  "clr", "cmpa", "cmpb", "cmpd", "cmps", "cmpu", "cmpx", "cmpy", "coma",
  "comb", "com", "cwai", "daa", "deca", "decb", "dec", "eora", "eorb",
  "exg", "inca", "incb", "inc", "jmp", "jsr", "lda", "ldb", "ldd",
  "lds", "ldu", "ldx", "ldy", "leas", "leau", "leax", "leay", "lsra",
  "lsrb", "lsr", "mul", "nega", "negb", "neg", "nop", "ora", "orb",
  "orcc", "pshs", "pshu", "puls", "pulu", "rola", "rolb", "rol", "rora",
  "rorb", "ror", "rti", "rts", "sbca", "sbcb", "sex", "sta", "stb",
  "std", "sts", "stu", "stx", "sty", "suba", "subb", "subd", "swi",
  "swi2", "swi3", "sync", "tfr", "tsta", "tstb", "tst", "reset",
#ifdef H6309
  "NEGD", "COMD", "LSRD", "RORD", "ASRD", "ROLD", "DECD",
  "INCD", "TSTD", "CLRD", "OIM", "AIM", "EIM", "ADDR", "LDE", "LDF", 
  "LDW", "DECE", "INCE", "TSTE", "CLRE", "DECF", "INCF", "TSTF", "CLRF",
  "COME", "COMF", "LDQ", "STQ", "SEXW", "TIM", "PSHSW", "PSHUW", "PULSW",
  "PULUW", "STE", "STF", "ADCR", "SUBR", "SBCR", "ANDR", "ORR", "EORR",
  "CMPR", "ASLD", "COMW", "LSRW", "RORW", "ROLW", "DECW", "INCW", "TSTW",
  "CLRW", "SUBW", "CMPW", "SBCD", "ANDD", "BITD", "EORD", "ADCD", "ORD",
  "ADDW", "BAND", "BIAND", "BOR", "BIOR", "BEOR", "BIEOR", "LDBT", "STBT",
  "STW", "TFM", "BITMD", "LDMD", "SUBE", "CMPE", "ADDE", "SUBF", "CMPF", 
  "ADDF", "DIVD", "DIVQ", "MULD"
#endif
};

struct EngineX09::Opcode EngineX09::codes[] = {
  // 00
  {_neg, _direct},
#ifdef H6309
  {_oim, _imm_direct},
  {_aim, _imm_direct},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_com, _direct},
  {_lsr, _direct},
#ifdef H6309
  {_eim, _direct},
#else
  {_undoc, _illegal},
#endif
  {_ror, _direct},
  {_asr, _direct},
  {_asl, _direct},
  {_rol, _direct},
  {_dec, _direct},
#ifdef H6309
  {_tim, _direct},
#else
  {_undoc, _illegal},
#endif
  {_inc, _direct},
  {_tst, _direct},
  {_jmp, _direct},
  {_clr, _direct},
  // 10
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_nop, _implied},
  {_sync, _implied},
#ifdef H6309
  {_sexw, _implied},
#else
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_lbra, _rel_word},
  {_lbsr, _rel_word},
  {_undoc, _illegal},
  {_daa, _implied},
  {_orcc, _imm_byte},
  {_undoc, _illegal},
  {_andcc, _imm_byte},
  {_sex, _implied},
  {_exg, _reg_post},
  {_tfr, _reg_post},
  // 20
  {_bra, _rel_byte},
  {_brn, _rel_byte},
  {_bhi, _rel_byte},
  {_bls, _rel_byte},
  {_bcc, _rel_byte},
  {_bcs, _rel_byte},
  {_bne, _rel_byte},
  {_beq, _rel_byte},
  {_bvc, _rel_byte},
  {_bvs, _rel_byte},
  {_bpl, _rel_byte},
  {_bmi, _rel_byte},
  {_bge, _rel_byte},
  {_blt, _rel_byte},
  {_bgt, _rel_byte},
  {_ble, _rel_byte},
  // 30
  {_leax, _indexed},
  {_leay, _indexed},
  {_leas, _indexed},
  {_leau, _indexed},
  {_pshs, _sys_post},
  {_puls, _sys_post},
  {_pshu, _usr_post},
  {_pulu, _usr_post},
  {_undoc, _illegal},
  {_rts, _implied},
  {_abx, _implied},
  {_rti, _implied},
  {_cwai, _imm_byte},
  {_mul, _implied},
  {_reset, _implied},
  {_swi, _implied},
  // 40
  {_nega, _implied},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_coma, _implied},
  {_lsra, _implied},
  {_undoc, _illegal},
  {_rora, _implied},
  {_asra, _implied},
  {_asla, _implied},
  {_rola, _implied},
  {_deca, _implied},
  {_undoc, _illegal},
  {_inca, _implied},
  {_tsta, _implied},
  {_undoc, _illegal},
  {_clra, _implied},
  // 50
  {_negb, _implied},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_comb, _implied},
  {_lsrb, _implied},
  {_undoc, _illegal},
  {_rorb, _implied},
  {_asrb, _implied},
  {_aslb, _implied},
  {_rolb, _implied},
  {_decb, _implied},
  {_undoc, _illegal},
  {_incb, _implied},
  {_tstb, _implied},
  {_undoc, _illegal},
  {_clrb, _implied},
  // 60
  {_neg, _indexed},
#ifdef H6309
  {_oim, _indexed},
  {_aim, _indexed},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_com, _indexed},
  {_lsr, _indexed},
#ifdef H6309
  {_eim, _indexed},
#else
  {_undoc, _illegal},
#endif
  {_ror, _indexed},
  {_asr, _indexed},
  {_asl, _indexed},
  {_rol, _indexed},
  {_dec, _indexed},
#ifdef H6309
  {_tim, _indexed},
#else
  {_undoc, _illegal},
#endif
  {_inc, _indexed},
  {_tst, _indexed},
  {_jmp, _indexed},
  {_clr, _indexed},
  // 70
  {_neg, _extended},
#ifdef H6309
  {_oim, _extended},
  {_aim, _extended},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_com, _extended},
  {_lsr, _extended},
#ifdef H6309
  {_eim, _extended},
#else
  {_undoc, _illegal},
#endif
  {_ror, _extended},
  {_asr, _extended},
  {_asl, _extended},
  {_rol, _extended},
  {_dec, _extended},
#ifdef H6309
  {_tim, _extended},
#else
  {_undoc, _illegal},
#endif
  {_inc, _extended},
  {_tst, _extended},
  {_jmp, _extended},
  {_clr, _extended},
  // 80
  {_suba, _imm_byte},
  {_cmpa, _imm_byte},
  {_sbca, _imm_byte},
  {_subd, _imm_word},
  {_anda, _imm_byte},
  {_bita, _imm_byte},
  {_lda, _imm_byte},
  {_undoc, _illegal},
  {_eora, _imm_byte},
  {_adca, _imm_byte},
  {_ora, _imm_byte},
  {_adda, _imm_byte},
  {_cmpx, _imm_word},
  {_bsr, _rel_byte},
  {_ldx, _imm_word},
  {_undoc, _illegal},
  // 90
  {_suba, _direct},
  {_cmpa, _direct},
  {_sbca, _direct},
  {_subd, _direct},
  {_anda, _direct},
  {_bita, _direct},
  {_lda, _direct},
  {_sta, _direct},
  {_eora, _direct},
  {_adca, _direct},
  {_ora, _direct},
  {_adda, _direct},
  {_cmpx, _direct},
  {_jsr, _direct},
  {_ldx, _direct},
  {_stx, _direct},
  // A0
  {_suba, _indexed},
  {_cmpa, _indexed},
  {_sbca, _indexed},
  {_subd, _indexed},
  {_anda, _indexed},
  {_bita, _indexed},
  {_lda, _indexed},
  {_sta, _indexed},
  {_eora, _indexed},
  {_adca, _indexed},
  {_ora, _indexed},
  {_adda, _indexed},
  {_cmpx, _indexed},
  {_jsr, _indexed},
  {_ldx, _indexed},
  {_stx, _indexed},
  // B0
  {_suba, _extended},
  {_cmpa, _extended},
  {_sbca, _extended},
  {_subd, _extended},
  {_anda, _extended},
  {_bita, _extended},
  {_lda, _extended},
  {_sta, _extended},
  {_eora, _extended},
  {_adca, _extended},
  {_ora, _extended},
  {_adda, _extended},
  {_cmpx, _extended},
  {_jsr, _extended},
  {_ldx, _extended},
  {_stx, _extended},
  // C0
  {_subb, _imm_byte},
  {_cmpb, _imm_byte},
  {_sbcb, _imm_byte},
  {_addd, _imm_word},
  {_andb, _imm_byte},
  {_bitb, _imm_byte},
  {_ldb, _imm_byte},
  {_undoc, _illegal},
  {_eorb, _imm_byte},
  {_adcb, _imm_byte},
  {_orb, _imm_byte},
  {_addb, _imm_byte},
  {_ldd, _imm_word},
#ifdef H6309
  {_ldq, _imm_quad},
#else
  {_undoc, _illegal},
#endif
  {_ldu, _imm_word},
  {_undoc, _illegal},
  // D0
  {_subb, _direct},
  {_cmpb, _direct},
  {_sbcb, _direct},
  {_addd, _direct},
  {_andb, _direct},
  {_bitb, _direct},
  {_ldb, _direct},
  {_stb, _direct},
  {_eorb, _direct},
  {_adcb, _direct},
  {_orb, _direct},
  {_addb, _direct},
  {_ldd, _direct},
  {_std, _direct},
  {_ldu, _direct},
  {_stu, _direct},
  // E0
  {_subb, _indexed},
  {_cmpb, _indexed},
  {_sbcb, _indexed},
  {_addd, _indexed},
  {_andb, _indexed},
  {_bitb, _indexed},
  {_ldb, _indexed},
  {_stb, _indexed},
  {_eorb, _indexed},
  {_adcb, _indexed},
  {_orb, _indexed},
  {_addb, _indexed},
  {_ldd, _indexed},
  {_std, _indexed},
  {_ldu, _indexed},
  {_stu, _indexed},
  // F0
  {_subb, _extended},
  {_cmpb, _extended},
  {_sbcb, _extended},
  {_addd, _extended},
  {_andb, _extended},
  {_bitb, _extended},
  {_ldb, _extended},
  {_stb, _extended},
  {_eorb, _extended},
  {_adcb, _extended},
  {_orb, _extended},
  {_addb, _extended},
  {_ldd, _extended},
  {_std, _extended},
  {_ldu, _extended},
  {_stu, _extended}
};

struct EngineX09::Opcode EngineX09::codes10[] = {
  // 00
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  // 10
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  // 20
  {_undoc, _illegal},
  {_lbrn, _rel_word},
  {_lbhi, _rel_word},
  {_lbls, _rel_word},
  {_lbcc, _rel_word},
  {_lbcs, _rel_word},
  {_lbne, _rel_word},
  {_lbeq, _rel_word},
  {_lbvc, _rel_word},
  {_lbvs, _rel_word},
  {_lbpl, _rel_word},
  {_lbmi, _rel_word},
  {_lbge, _rel_word},
  {_lblt, _rel_word},
  {_lbgt, _rel_word},
  {_lble, _rel_word},
  // 30
#ifdef H6309
  {_addr, _reg_reg},
  {_adcr, _reg_reg},
  {_subr, _reg_reg},
  {_sbcr, _reg_reg},
  {_andr, _reg_reg},
  {_orr, _reg_reg},
  {_eorr, _reg_reg},
  {_cmpr, _reg_reg},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
#ifdef H6309
  {_pshsw, _implied},
  {_pulsw, _implied},
  {_pshuw, _implied},
  {_puluw, _implied},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_swi2, _implied},
  // 40
#ifdef H6309
  {_negd, _implied},
#else
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_comd, _implied},
  {_lsrd, _implied},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
#ifdef H6309
  {_rord, _implied},
  {_asrd, _implied},
  {_asld, _implied},
  {_rold, _implied},
  {_decd, _implied},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
#ifdef H6309
  {_incd, _implied},
  {_tstd, _implied},
  {_undoc, _illegal},
  {_clrd, _implied},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  // 50
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_comw, _implied},
  {_lsrw, _implied},
  {_undoc, _illegal},
  {_rorw, _implied},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_rolw, _implied},
  {_decw, _implied},
  {_undoc, _illegal},
  {_incw, _implied},
  {_tstw, _implied},
  {_undoc, _illegal},
  {_clrw, _implied},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  // 60
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  // 70
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  // 80
#ifdef H6309
  {_subw, _imm_word},
  {_cmpw, _imm_word},
  {_sbcd, _imm_word},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_cmpd, _imm_word},
#ifdef H6309
  {_andd, _imm_word},
  {_bitd, _imm_word},
  {_ldw, _imm_word},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
#ifdef H6309
  {_eord, _imm_word},
  {_adcd, _imm_word},
  {_ord, _imm_word},
  {_addw, _imm_word},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_cmpy, _imm_word},
  {_undoc, _illegal},
  {_ldy, _imm_word},
  {_undoc, _illegal},
  // 90
#ifdef H6309
  {_subw, _direct},
  {_cmpw, _direct},
  {_sbcd, _direct},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_cmpd, _direct},
#ifdef H6309
  {_andd, _direct},
  {_bitd, _direct},
  {_ldw, _direct},
  {_stw, _direct},
  {_eord, _direct},
  {_adcd, _direct},
  {_ord, _direct},
  {_addw, _direct},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_cmpy, _direct},
  {_undoc, _illegal},
  {_ldy, _direct},
  {_sty, _direct},
  // A0
#ifdef H6309
  {_subw, _indexed},
  {_cmpw, _indexed},
  {_sbcd, _indexed},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_cmpd, _indexed},
#ifdef H6309
  {_andd, _indexed},
  {_bitd, _indexed},
  {_ldw, _indexed},
  {_stw, _indexed},
  {_eord, _indexed},
  {_adcd, _indexed},
  {_ord, _indexed},
  {_addw, _indexed},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_cmpy, _indexed},
  {_undoc, _illegal},
  {_ldy, _indexed},
  {_sty, _indexed},
  // B0
#ifdef H6309
  {_subw, _extended},
  {_cmpw, _extended},
  {_sbcd, _extended},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_cmpd, _extended},
#ifdef H6309
  {_andd, _extended},
  {_bitd, _extended},
  {_ldw, _extended},
  {_stw, _extended},
  {_eord, _extended},
  {_adcd, _extended},
  {_ord, _extended},
  {_addw, _extended},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_cmpy, _extended},
  {_undoc, _illegal},
  {_ldy, _extended},
  {_sty, _extended},
  // C0
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_lds, _imm_word},
  {_undoc, _illegal},
  // D0
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_ldq, _direct},
  {_stq, _direct},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_lds, _direct},
  {_sts, _direct},
  // E0
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_ldq, _indexed},
  {_stq, _indexed},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_lds, _indexed},
  {_sts, _indexed},
  // F0
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_ldq, _extended},
  {_stq, _extended},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_lds, _extended},
  {_sts, _extended}
};

struct EngineX09::Opcode EngineX09::codes11[] = {
  // 00
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  // 10
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  // 20
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  // 30
#ifdef H6309
  {_band, _single_bit},
  {_biand, _single_bit},
  {_bor, _single_bit},
  {_bior, _single_bit},
  {_beor, _single_bit},
  {_bieor, _single_bit},
  {_ldbt, _single_bit},
  {_stbt, _single_bit},
  {_tfm, _blk_move},
  {_tfm, _blk_move},
  {_tfm, _blk_move},
  {_tfm, _blk_move},
  {_bitmd, _imm_byte},
  {_ldmd, _imm_byte},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_swi3, _implied},
  // 40
  {_undoc, _illegal}, /* 11 40 */
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_come, _implied},
#else
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_dece, _implied},
#else
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
#ifdef H6309
  {_ince, _implied},
  {_tste, _implied},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
#ifdef H6309
  {_clre, _implied},
#else
  {_undoc, _illegal},
#endif
  // 50
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_comf, _implied},
#else
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_decf, _implied},
#else
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
#ifdef H6309
  {_incf, _implied},
  {_tstf, _implied},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
#ifdef H6309
  {_clrf, _implied},
#else
  {_undoc, _illegal},
#endif
  // 60
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  // 70
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  // 80
#ifdef H6309
  {_sube, _imm_byte},
  {_cmpe, _imm_byte},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_cmpu, _imm_word},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_lde, _imm_byte},
#else
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_adde, _imm_byte},
#else
  {_undoc, _illegal},
#endif
  {_cmps, _imm_word},
#ifdef H6309
  {_divd, _imm_byte},
  {_divq, _imm_word},
  {_muld, _imm_word},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  // 90
#ifdef H6309
  {_sube, _direct},
  {_cmpe, _direct},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_cmpu, _direct},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_lde, _direct},
  {_ste, _direct},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_adde, _direct},
#else
  {_undoc, _illegal},
#endif
  {_cmps, _direct},
#ifdef H6309
  {_divd, _direct},
  {_divq, _direct},
  {_muld, _direct},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  // A0
#ifdef H6309
  {_sube, _indexed},
  {_cmpe, _indexed},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_cmpu, _indexed},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_lde, _indexed},
  {_ste, _indexed},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_adde, _indexed},
#else
  {_undoc, _illegal},
#endif
  {_cmps, _indexed},
#ifdef H6309
  {_divd, _indexed},
  {_divq, _indexed},
  {_muld, _indexed},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  // B0
#ifdef H6309
  {_sube, _extended},
  {_cmpe, _extended},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_cmpu, _extended},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_lde, _extended},
  {_ste, _extended},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_adde, _extended},
#else
  {_undoc, _illegal},
#endif
  {_cmps, _extended},
#ifdef H6309
  {_divd, _extended},
  {_divq, _extended},
  {_muld, _extended},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  // C0
#ifdef H6309
  {_subf, _imm_byte},
  {_cmpf, _imm_byte},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_ldf, _imm_byte},
#else
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_addf, _imm_byte},
#else
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  // D0
#ifdef H6309
  {_subf, _direct},
  {_cmpf, _direct},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_ldf, _direct},
  {_stf, _direct},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_addf, _direct},
#else
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  // E0
#ifdef H6309
  {_subf, _indexed},
  {_cmpf, _indexed},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_ldf, _indexed},
  {_stf, _indexed},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  // F0
#ifdef H6309
  {_subf, _extended},
  {_cmpf, _extended},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_ldf, _extended},
  {_stf, _extended},
#else
  {_undoc, _illegal},
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
#ifdef H6309
  {_addf, _extended},
#else
  {_undoc, _illegal},
#endif
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal}
};

const char *EngineX09::reg[] = {
#ifdef H6309
  "d", "x", "y", "u", "s", "pc", "w", "v",
  "a", "b", "cc", "dp", "??", "??", "e", "f"
#else
  "d", "x", "y", "u", "s", "pc", "??", "??",
  "a", "b", "cc", "dp", "??", "??", "??", "??"
#endif
};

const char EngineX09::index_reg[] = {'x', 'y', 'u', 's'};

const char *EngineX09::off4[] = {
  "0", "1", "2", "3", "4", "5", "6", "7",
  "8", "9", "10", "11", "12", "13", "14", "15",
  "-16", "-15", "-14", "-13", "-12", "-11", "-10", "-9",
  "-8", "-7", "-6", "-5", "-4", "-3", "-2", "-1"
};

void EngineX09::initialise() {
  int numArgs = args->getArgC(Args::argument);
  const int req = Args::requires_argument;
  const int reqNum = Args::requires_argument | Args::numeric_argument;
  bool verbose;
  char labFile[MAXSTR];
  char cpuStr[MAXSTR];

  if (numArgs != 1) {
    Utils::abortf("Just one rom file expected\n");
  }

  parseopt_t mandatoryArgs[] = {
    {"cpu",        req,    cpuStr, 'c'},
    {"rom-start",  reqNum, NULL,   'b'}, 
    {"rom-size",   reqNum, NULL,   's'},
    {NULL,         0,      NULL,   0}
  }; 
 
  parseopt_t optionalArgs[] = {
    {"label-file", req, labFile,   'l'},
    {"help",       0,   NULL,      '?'},
    {"verbose",    0,   &verbose,  'v'},
    {NULL,         0,   NULL,      0}
  };

  try {
    args->parseArgs(mandatoryArgs, optionalArgs, true);

    if (args->hasArg("label-file")) {
      labels->readFile(labFile);
    }
  }
  catch (CommandLineException e) {
    Utils::abortf("Bad command line.\n");
  }

  // Read the rom image

  readVector(RESETVec, "Reset");
  readVector(NMIVec,   "NMI");
  readVector(SWIVec,   "SWI");
  readVector(IRQVec,   "IRQ");
  readVector(FIRQVec,  "FIRQ");
  readVector(SWI2Vec,  "SWI2");
  readVector(SWI3Vec,  "SWI3");

  mem->setType(SWI3Vec, Memory::WORD, 7);

  printf("6x09 engine ready.\n");
}

bool EngineX09::disassembleReglist(OutputItem *out, EngineX09::Opcode *opcode) {
  char regList[MAXSTR];
  int b = fetch8();
  // TODO: reverse order of list for PULL vs PUSH

  regList[0] = '\0';

  if (b & 0x80) {
    strncat(regList, "pc,", MAXSTR-1);
  }

  if (b & 0x40) {
    strncat(regList, (opcode->mode == _usr_post) ? "s," : "u,", MAXSTR-1);
  }

  if (b & 0x20) {
    strncat(regList, "y,", MAXSTR-1);
  }
	
  if (b & 0x10) {
    strncat(regList, "x,", MAXSTR-1);
  }

  if (b & 0x08) {
    strncat(regList, "dp,", MAXSTR-1);
  }

  if ((b & 0x06) == 0x06) {
    strncat(regList, "d,", MAXSTR-1);
  }
  else {
    if (b & 0x04) {
      strncat(regList, "b,", MAXSTR-1);
    }

    if (b & 0x02) {
      strncat(regList, "a,", MAXSTR-1);
    }
  }

  if (b & 0x01) {
    strncat(regList, "cc,", MAXSTR-1);
  }

  regList[strlen(regList) - 1] = '\0';
  out->setOperand("%s", regList);

  // PULU or PULS and what we pull includes the PC, so 
  // stop disassembling.
  if (b & 0x80) {
    return true;
  }

  return false;
}

void EngineX09::disassembleIndexed(OutputItem *out, int instruction) {
  int b = fetch8();
  char regName = index_reg[(b >> 5) & 0x3];
  long target;
  char label[MAXSTR];

  if ((b & 0x80) == 0) {
    out->setOperand("%s,%c", off4[instruction & 0x1f], regName);
    return;
  }

  switch (b & 0x1f) {
  case 0x00:
    out->setOperand(",%c+", regName);
    break;

  case 0x01:
    out->setOperand(",%c++", regName);
    break;

  case 0x02:
    out->setOperand(",-%c", regName);
    break;

  case 0x03:
    out->setOperand(",--%c", regName);
    break;

  case 0x04:
    out->setOperand(",%c", regName);
    break;

  case 0x05:
    out->setOperand("b,%c", regName);
    break;

  case 0x06:
    out->setOperand("b,%c", regName);
    break;

  case 0x08:
    target = fetch8Lab(label);
    out->setOperand("<$%s,%c", label, regName);
    break;

  case 0x09:
    target = fetch16Lab(label);
    out->setOperand("$%s,%c", label, regName);
    break;

  case 0x0b:
    out->setOperand("d,%c", regName);
    break;

  case 0x0c:
    target = fetch8RelLab(label);
    out->setOperand("%s,pcr", label);
    break;

  case 0x0d:
    target = fetch16RelLab(label);
    out->setOperand("%s,pcr", label);
    break;

  case 0x11:
    out->setOperand("[,%c++]", regName);
    break;

  case 0x13:
    out->setOperand("[,--%c]", regName);
    break;

  case 0x14:
    out->setOperand("[,%c]", regName);
    break;

  case 0x15:
    out->setOperand("[b,%c]", regName);
    break;

  case 0x16:
    out->setOperand("[a,%c]", regName);
    break;

  case 0x18:
    target = fetch8Lab(label);
    out->setOperand("[<%s,%c]", label, regName);
    break;

  case 0x19:
    target = fetch16Lab(label);
    out->setOperand("[%s,%c]", label, regName);
    break;

  case 0x1b:
    out->setOperand("[d,%c]", regName);
    break;

  case 0x1c:
    target = fetch8RelLab(label);
    out->setOperand("[<%s,pcr]", label);
    break;

  case 0x1d:
    target = fetch8RelLab(label);
    out->setOperand("[%s,pcr]", label);
    break;

  case 0x1f:
    target = fetch16RelLab(label);
    out->setOperand("[%s]", label);
    break;

  default:
    out->setOperand("???");
    break;
  }
}

int EngineX09::disassembleAsBytes(OutputItem *out, long addr, int count) {
  char bytes[MAXSTR];
  char *cp = bytes;
  int max = MAXSTR-1;
  int i;

  bytes[0] = EOS;

  for (i=0; i<count; i++) {
    snprintf(cp, max, "$%02x,", mem->getByte(addr + i));
    max -= 4;
    cp += 4;
  }

  max = strlen(bytes);
  if (max) {
    bytes[max-1] = EOS;
  }

  out->setInstruction("fcb");
  out->setOperand(bytes);
  mem->setType(addr, Memory::BYTE, count);

  return count;
}

int EngineX09::disassemble(long addr, OutputItem *out) {
  int instruction;
  EngineX09::Opcode *opcode;
  int immVal;
  int inst;
  char label[MAXSTR];
  long target;
  char regName;

  out->clear();
  out->setAddress(addr);

  if (!mem->isValidAddress(addr)) {
    Utils::abortf("disassemble() - Address $%x out of range.", addr);
  }

  if (labels->isLabel(pc)) {
    labels->lookupLabel(pc, label);
  }

  inst = fetch8();

  /* Is it a two byte instruction? All two byte instructions start
   * with 0x10 or 0x11 */

  if (inst == 0x10) {
    inst = fetch8();
    opcode = &(codes10[inst]);
  }
  else if (inst == 0x11) {
    inst = fetch8();
    opcode = &(codes11[inst]);
  }
  else {
    opcode = &(codes[inst]);
  }

  instruction = opcode->code;

  if (instruction == _illegal) {
    return -disassembleAsBytes(out, addr, pc - addr);
  }

  // If we've got this far, we have a valid instruction, yippee!
  out->setInstruction(mne[instruction]);

  switch (opcode->mode) {
  case _implied:
    // Special cases: RTS and RTI
    if ((instruction == _rts) || (instruction == _rti)) {
      return -mem->setType(addr, Memory::CODE, pc-addr);
    }
    break;

  case _imm_byte:
    out->setOperand("#$%02x", fetch8());
    break;

  case _imm_word:
    out->setOperand("#$%04x", fetch16());
    break;

  case _direct:
    target = fetch8Lab(label);

    if ((instruction == _jsr) || (instruction == _jmp)) {
      stackAddress(target);
      labels->createLabel(NULL, target);
    }

    out->setOperand("<%s", label);
    break;

  case _extended:
    target = fetch16Lab(label);

    if ((instruction == _jsr) || (instruction == _jmp)) {
      stackAddress(target);
      labels->createLabel(NULL, target);
    }

    out->setOperand("%s", label);
    break;

  case _indexed:
    disassembleIndexed(out, instruction);
    break;

  case _rel_byte:
    target = fetch8RelLab(label);
    stackAddress(target);
    out->setOperand("%s", label);

    if (instruction == _bra) {
      return -mem->setType(addr, Memory::CODE, pc-addr);
    }
    break;

  case _rel_word:
    target = fetch16RelLab(label);

    stackAddress(target);
    out->setOperand("%s", label);

    if (instruction == _lbra) {
      return -mem->setType(addr, Memory::CODE, pc-addr);
    }
    break;

  case _reg_post:
    {
      int b = fetch8();
      out->setOperand("%s,%s", reg[b >> 4], reg[b & 0x0f]);
    }
    break;

  case _usr_post:
  case _sys_post:
    if (disassembleReglist(out, opcode)) {
      return -mem->setType(addr, Memory::CODE, pc-addr);
    }
    break;

#ifdef H6309
  case _imm_direct:
    immVal = fetch8();
    target = fetch8Lab(label);
    out->setOperand("#$%02x,<%s", immVal, label);
    break;

  case _imm_quad:
    {
      dword_t quadVal = fetch32();
      out->setOperand("#$%08x", quadVal);
    }
    break;

  case _reg_reg:
    {
      unsigned regs = fetch8();
      unsigned r1 = (regs & 0xf0) >> 4;
      unsigned r2 = regs & 0x0f;

      out->setOperand("%s,%s", reg[r1], reg[r2]);
    }
    break;

  case _single_bit:
    {
      unsigned bits = fetch8();
      unsigned regbit = bits & 0x07;
      unsigned srcbit = (bits >> 3) & 0x07;
      unsigned regnum = (bits >> 6) & 0x03;
      static char *reg_name[4] = {"CC", "A", "B", "???"};

      target = fetch8Lab(label);
      out->setOperand("%s.%d,%s.%d", reg_name[regnum], regbit, label, srcbit);
    }
    break;

  case _blk_move:
    {
      unsigned regs = fetch8();
      unsigned src_reg = (regs >> 4) & 0x0f;
      unsigned dst_reg = regs & 0x0f;
      char *src_op = "+";
      char *dst_op = "+";

      if (instruction == 0x39) {
	src_op = dst_op = "-";
      }
      else if (instruction == 0x3a) {
	dst_op = "";
      }
      else if (instruction == 0x3b) {
	src_op = "";
      }

      out->setOperand("(%s%s,%s%s)", reg[src_reg], src_op, reg[dst_reg], dst_op);
    }
    break;
#endif
  }

  return mem->setType(addr, Memory::CODE, pc-addr);
}

