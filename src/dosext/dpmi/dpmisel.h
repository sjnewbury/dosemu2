/*
 * (C) Copyright 1992, ..., 2014 the "DOSEMU-Development-Team".
 *
 * for details see file COPYING in the DOSEMU distribution
 */

#ifndef DPMISEL_H
#define DPMISEL_H

extern char _binary_dpmisel_o_bin_end[];
extern char _binary_dpmisel_o_bin_size[];
extern char _binary_dpmisel_o_bin_start[];

#define DPMI_SEL_OFF(x) (x-DPMI_sel_code_start)

extern const unsigned    DPMI_sel_code_start;
extern const unsigned    DPMI_save_restore_pm;
extern const unsigned    DPMI_raw_mode_switch_pm;
extern const unsigned    DPMI_return_from_rm_callback;
extern const unsigned    DPMI_VXD_start;
extern const unsigned    DPMI_VXD_end;
extern const unsigned    DPMI_return_from_RSPcall;
extern const unsigned    DPMI_return_from_LDTcall;
extern const unsigned    DPMI_return_from_LDTExitCall;
extern const unsigned    DPMI_return_from_int_1c;
extern const unsigned    DPMI_return_from_int_23;
extern const unsigned    DPMI_return_from_int_24;
extern const unsigned    DPMI_return_from_rm_callback;
extern const unsigned    DPMI_return_from_ext_exception;
extern const unsigned    DPMI_return_from_exception;
extern const unsigned    DPMI_return_from_rm_ext_exception;
extern const unsigned    DPMI_return_from_rm_exception;
extern const unsigned    DPMI_return_from_pm;
extern const unsigned    DPMI_API_extension;
extern const unsigned    DPMI_exception;
extern const unsigned    DPMI_ext_exception;
extern const unsigned    DPMI_rm_exception;
extern const unsigned    DPMI_interrupt;
extern const unsigned    DPMI_vtmr_irq;
extern const unsigned    DPMI_vtmr_post_irq;
extern const unsigned    DPMI_vrtc_irq;
extern const unsigned    DPMI_vrtc_post_irq;
extern const unsigned    DPMI_reinit;
extern const unsigned    DPMI_sel_end;

extern const unsigned    DPMI_VXD_start;
extern const unsigned    DPMI_VXD_VMM;
extern const unsigned    DPMI_VXD_PageFile;
extern const unsigned    DPMI_VXD_Reboot;
extern const unsigned    DPMI_VXD_VDD;
extern const unsigned    DPMI_VXD_VMD;
extern const unsigned    DPMI_VXD_VXDLDR;
extern const unsigned    DPMI_VXD_SHELL;
extern const unsigned    DPMI_VXD_VCD;
extern const unsigned    DPMI_VXD_VTD;
extern const unsigned    DPMI_VXD_CONFIGMG;
extern const unsigned    DPMI_VXD_ENABLE;
extern const unsigned    DPMI_VXD_APM;
extern const unsigned    DPMI_VXD_VTDAPI;
extern const unsigned    DPMI_VXD_end;

extern const unsigned    MSDOS_pmc_start;
extern const unsigned    MSDOS_fault;
extern const unsigned    MSDOS_pagefault;
extern const unsigned    MSDOS_API_call;
extern const unsigned    MSDOS_API_WINOS2_call;
extern const unsigned    MSDOS_LDT_call16;
extern const unsigned    MSDOS_LDT_call32;
extern const unsigned    MSDOS_RSP_call16;
extern const unsigned    MSDOS_RSP_call32;
extern const unsigned    MSDOS_rmcb_call_start;
extern const unsigned    MSDOS_rmcb_call0;
extern const unsigned    MSDOS_rmcb_call1;
extern const unsigned    MSDOS_rmcb_call2;
extern const unsigned    MSDOS_rmcb_ret0;
extern const unsigned    MSDOS_rmcb_ret1;
extern const unsigned    MSDOS_rmcb_ret2;
extern const unsigned    MSDOS_rmcb_call_end;
extern const unsigned    MSDOS_hlt_start;
extern const unsigned    MSDOS_hlt_end;
extern const unsigned    MSDOS_pmc_end;
extern const unsigned    DPMI_call;
extern const unsigned    DPMI_call_args;
extern const unsigned    DPMI_call_args16;
extern const unsigned    DPMI_msdos;

extern const unsigned    DPMI_sel_code_end;

#endif
