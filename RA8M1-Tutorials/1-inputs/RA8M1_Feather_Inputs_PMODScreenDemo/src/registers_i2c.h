/*
 *****************************************************************************
 * Copyright by ams OSRAM AG                                                       *
 * All rights are reserved.                                                  *
 *                                                                           *
 * IMPORTANT - PLEASE READ CAREFULLY BEFORE COPYING, INSTALLING OR USING     *
 * THE SOFTWARE.                                                             *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT         *
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS         *
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  *
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT          *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.      *
 *****************************************************************************
 */

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!         THIS FILE IS AUTOMATICALLY GENERATED         !!
// !!              DO NOT EDIT THIS FILE                   !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef REGISTERS_I2C_H
#define REGISTERS_I2C_H

#define ENABLE_REG 0xe0
#define ENABLE__cpu_reset__MASK  0x80
#define ENABLE__cpu_reset__WIDTH 1
#define ENABLE__cpu_reset__SHIFT 7
#define ENABLE__cpu_reset__RESET 0
#define ENABLE__cpu_reset 128
#define ENABLE__cpu_ready__MASK  0x40
#define ENABLE__cpu_ready__WIDTH 1
#define ENABLE__cpu_ready__SHIFT 6
#define ENABLE__cpu_ready__RESET 0
#define ENABLE__cpu_ready 64
#define ENABLE__powerup_select__MASK  0x30
#define ENABLE__powerup_select__WIDTH 2
#define ENABLE__powerup_select__SHIFT 4
#define ENABLE__powerup_select__RESET 0
// Enumeration for powerup_select
#define ENABLE__powerup_select__no_override 0 // Do what is selected in the boot_select fuses
#define ENABLE__powerup_select__start_boot_monitor 1 // Always start the boot monitor, do not go to sleep
#define ENABLE__powerup_select__start_app_in_ram 2 // Start the application that is in RAM
#define ENABLE__powerup_select__reserved 3 // Reserved for future use

#define ENABLE__pinmux_unlock__MASK  0x8
#define ENABLE__pinmux_unlock__WIDTH 1
#define ENABLE__pinmux_unlock__SHIFT 3
#define ENABLE__pinmux_unlock__RESET 0
#define ENABLE__pinmux_unlock 8
#define ENABLE__timed_standby_mode__MASK  0x4
#define ENABLE__timed_standby_mode__WIDTH 1
#define ENABLE__timed_standby_mode__SHIFT 2
#define ENABLE__timed_standby_mode__RESET 0
#define ENABLE__timed_standby_mode 4
#define ENABLE__standby_mode__MASK  0x2
#define ENABLE__standby_mode__WIDTH 1
#define ENABLE__standby_mode__SHIFT 1
#define ENABLE__standby_mode__RESET 0
#define ENABLE__standby_mode 2
#define ENABLE__pon__MASK  0x1
#define ENABLE__pon__WIDTH 1
#define ENABLE__pon__SHIFT 0
#define ENABLE__pon__RESET 1
#define ENABLE__pon 1

#define INT_STATUS 0xe1
#define INT_STATUS__int8__MASK  0x80
#define INT_STATUS__int8__WIDTH 1
#define INT_STATUS__int8__SHIFT 7
#define INT_STATUS__int8__RESET 0
#define INT_STATUS__int8 128
#define INT_STATUS__int7__MASK  0x40
#define INT_STATUS__int7__WIDTH 1
#define INT_STATUS__int7__SHIFT 6
#define INT_STATUS__int7__RESET 0
#define INT_STATUS__int7 64
#define INT_STATUS__int6__MASK  0x20
#define INT_STATUS__int6__WIDTH 1
#define INT_STATUS__int6__SHIFT 5
#define INT_STATUS__int6__RESET 0
#define INT_STATUS__int6 32
#define INT_STATUS__int5__MASK  0x10
#define INT_STATUS__int5__WIDTH 1
#define INT_STATUS__int5__SHIFT 4
#define INT_STATUS__int5__RESET 0
#define INT_STATUS__int5 16
#define INT_STATUS__int4__MASK  0x8
#define INT_STATUS__int4__WIDTH 1
#define INT_STATUS__int4__SHIFT 3
#define INT_STATUS__int4__RESET 0
#define INT_STATUS__int4 8
#define INT_STATUS__int3__MASK  0x4
#define INT_STATUS__int3__WIDTH 1
#define INT_STATUS__int3__SHIFT 2
#define INT_STATUS__int3__RESET 0
#define INT_STATUS__int3 4
#define INT_STATUS__int2__MASK  0x2
#define INT_STATUS__int2__WIDTH 1
#define INT_STATUS__int2__SHIFT 1
#define INT_STATUS__int2__RESET 0
#define INT_STATUS__int2 2
#define INT_STATUS__int1__MASK  0x1
#define INT_STATUS__int1__WIDTH 1
#define INT_STATUS__int1__SHIFT 0
#define INT_STATUS__int1__RESET 0
#define INT_STATUS__int1 1

#define INT_ENAB 0xe2
#define INT_ENAB__int8_enab__MASK  0x80
#define INT_ENAB__int8_enab__WIDTH 1
#define INT_ENAB__int8_enab__SHIFT 7
#define INT_ENAB__int8_enab__RESET 0
#define INT_ENAB__int8_enab 128
#define INT_ENAB__int7_enab__MASK  0x40
#define INT_ENAB__int7_enab__WIDTH 1
#define INT_ENAB__int7_enab__SHIFT 6
#define INT_ENAB__int7_enab__RESET 0
#define INT_ENAB__int7_enab 64
#define INT_ENAB__int6_enab__MASK  0x20
#define INT_ENAB__int6_enab__WIDTH 1
#define INT_ENAB__int6_enab__SHIFT 5
#define INT_ENAB__int6_enab__RESET 0
#define INT_ENAB__int6_enab 32
#define INT_ENAB__int5_enab__MASK  0x10
#define INT_ENAB__int5_enab__WIDTH 1
#define INT_ENAB__int5_enab__SHIFT 4
#define INT_ENAB__int5_enab__RESET 0
#define INT_ENAB__int5_enab 16
#define INT_ENAB__int4_enab__MASK  0x8
#define INT_ENAB__int4_enab__WIDTH 1
#define INT_ENAB__int4_enab__SHIFT 3
#define INT_ENAB__int4_enab__RESET 0
#define INT_ENAB__int4_enab 8
#define INT_ENAB__int3_enab__MASK  0x4
#define INT_ENAB__int3_enab__WIDTH 1
#define INT_ENAB__int3_enab__SHIFT 2
#define INT_ENAB__int3_enab__RESET 0
#define INT_ENAB__int3_enab 4
#define INT_ENAB__int2_enab__MASK  0x2
#define INT_ENAB__int2_enab__WIDTH 1
#define INT_ENAB__int2_enab__SHIFT 1
#define INT_ENAB__int2_enab__RESET 0
#define INT_ENAB__int2_enab 2
#define INT_ENAB__int1_enab__MASK  0x1
#define INT_ENAB__int1_enab__WIDTH 1
#define INT_ENAB__int1_enab__SHIFT 0
#define INT_ENAB__int1_enab__RESET 0
#define INT_ENAB__int1_enab 1

#define ID_REG 0xe3
#define ID__id__MASK  0x3f
#define ID__id__WIDTH 6
#define ID__id__SHIFT 0
#define ID__id__RESET 08

#define REVID 0xe4
#define REVID__rev_id__MASK  0x7
#define REVID__rev_id__WIDTH 3
#define REVID__rev_id__SHIFT 0
#define REVID__rev_id__RESET 0

#define CTRL0 0xe5
#define CTRL0__foundry_page__MASK  0x80
#define CTRL0__foundry_page__WIDTH 1
#define CTRL0__foundry_page__SHIFT 7
#define CTRL0__foundry_page__RESET 0
#define CTRL0__foundry_page 128
#define CTRL0__p2ram_fusenr__MASK  0x60
#define CTRL0__p2ram_fusenr__WIDTH 2
#define CTRL0__p2ram_fusenr__SHIFT 5
#define CTRL0__p2ram_fusenr__RESET 0
#define CTRL0__spare_e5_2__MASK  0x10
#define CTRL0__spare_e5_2__WIDTH 1
#define CTRL0__spare_e5_2__SHIFT 4
#define CTRL0__spare_e5_2__RESET 0
#define CTRL0__spare_e5_2 16
#define CTRL0__skip_initwait__MASK  0x8
#define CTRL0__skip_initwait__WIDTH 1
#define CTRL0__skip_initwait__SHIFT 3
#define CTRL0__skip_initwait__RESET 0
#define CTRL0__skip_initwait 8
#define CTRL0__cp_enable__MASK  0x4
#define CTRL0__cp_enable__WIDTH 1
#define CTRL0__cp_enable__SHIFT 2
#define CTRL0__cp_enable__RESET 0
#define CTRL0__cp_enable 4
#define CTRL0__spare_e5__MASK  0x3
#define CTRL0__spare_e5__WIDTH 2
#define CTRL0__spare_e5__SHIFT 0
#define CTRL0__spare_e5__RESET 0

#define VCSEL_CFG 0xe6
#define VCSEL_CFG__sel_vcdrv_pls_source__MASK  0x80
#define VCSEL_CFG__sel_vcdrv_pls_source__WIDTH 1
#define VCSEL_CFG__sel_vcdrv_pls_source__SHIFT 7
#define VCSEL_CFG__sel_vcdrv_pls_source__RESET 0
#define VCSEL_CFG__sel_vcdrv_pls_source 128
#define VCSEL_CFG__vcsel_incr_glow_curr__MASK  0x40
#define VCSEL_CFG__vcsel_incr_glow_curr__WIDTH 1
#define VCSEL_CFG__vcsel_incr_glow_curr__SHIFT 6
#define VCSEL_CFG__vcsel_incr_glow_curr__RESET 0
#define VCSEL_CFG__vcsel_incr_glow_curr 64
#define VCSEL_CFG__en_vcdrv_shunt_s__MASK  0x20
#define VCSEL_CFG__en_vcdrv_shunt_s__WIDTH 1
#define VCSEL_CFG__en_vcdrv_shunt_s__SHIFT 5
#define VCSEL_CFG__en_vcdrv_shunt_s__RESET 0
#define VCSEL_CFG__en_vcdrv_shunt_s 32
#define VCSEL_CFG__en_vcdrv_shunt_w__MASK  0x10
#define VCSEL_CFG__en_vcdrv_shunt_w__WIDTH 1
#define VCSEL_CFG__en_vcdrv_shunt_w__SHIFT 4
#define VCSEL_CFG__en_vcdrv_shunt_w__RESET 0
#define VCSEL_CFG__en_vcdrv_shunt_w 16
#define VCSEL_CFG__spare_e6__MASK  0xc
#define VCSEL_CFG__spare_e6__WIDTH 2
#define VCSEL_CFG__spare_e6__SHIFT 2
#define VCSEL_CFG__spare_e6__RESET 0
#define VCSEL_CFG__vcsel_poweron__MASK  0x2
#define VCSEL_CFG__vcsel_poweron__WIDTH 1
#define VCSEL_CFG__vcsel_poweron__SHIFT 1
#define VCSEL_CFG__vcsel_poweron__RESET 0
#define VCSEL_CFG__vcsel_poweron 2
#define VCSEL_CFG__vcsel_enable__MASK  0x1
#define VCSEL_CFG__vcsel_enable__WIDTH 1
#define VCSEL_CFG__vcsel_enable__SHIFT 0
#define VCSEL_CFG__vcsel_enable__RESET 0
#define VCSEL_CFG__vcsel_enable 1

#define VCSEL_CFG2 0xe7
#define VCSEL_CFG2__vcsel_pulsewidth__MASK  0xc0
#define VCSEL_CFG2__vcsel_pulsewidth__WIDTH 2
#define VCSEL_CFG2__vcsel_pulsewidth__SHIFT 6
#define VCSEL_CFG2__vcsel_pulsewidth__RESET 0
#define VCSEL_CFG2__vcsel_ipulse__MASK  0x3f
#define VCSEL_CFG2__vcsel_ipulse__WIDTH 6
#define VCSEL_CFG2__vcsel_ipulse__SHIFT 0
#define VCSEL_CFG2__vcsel_ipulse__RESET 0

#define VCSEL_CFG3 0xe8
#define VCSEL_CFG3__ss_amplitude__MASK  0xf8
#define VCSEL_CFG3__ss_amplitude__WIDTH 5
#define VCSEL_CFG3__ss_amplitude__SHIFT 3
#define VCSEL_CFG3__ss_amplitude__RESET 0
#define VCSEL_CFG3__spare_e8_2__MASK  0x4
#define VCSEL_CFG3__spare_e8_2__WIDTH 1
#define VCSEL_CFG3__spare_e8_2__SHIFT 2
#define VCSEL_CFG3__spare_e8_2__RESET 0
#define VCSEL_CFG3__spare_e8_2 4
#define VCSEL_CFG3__vcsel_ss_rounds__MASK  0x3
#define VCSEL_CFG3__vcsel_ss_rounds__WIDTH 2
#define VCSEL_CFG3__vcsel_ss_rounds__SHIFT 0
#define VCSEL_CFG3__vcsel_ss_rounds__RESET 0
// Enumeration for vcsel_ss_rounds
#define VCSEL_CFG3__vcsel_ss_rounds__single 0 // change modulation delay after each vcsel pulse round
#define VCSEL_CFG3__vcsel_ss_rounds__double 1 // after two pulse rounds
#define VCSEL_CFG3__vcsel_ss_rounds__triple 2 // after three pulse rounds
#define VCSEL_CFG3__vcsel_ss_rounds__quadruple 3 // after four pulse rounds


#define CP_CFG 0xe9
#define CP_CFG__cp_unregulated__MASK  0x80
#define CP_CFG__cp_unregulated__WIDTH 1
#define CP_CFG__cp_unregulated__SHIFT 7
#define CP_CFG__cp_unregulated__RESET 0
#define CP_CFG__cp_unregulated 128
#define CP_CFG__cp_vdd_hvchp__MASK  0x7f
#define CP_CFG__cp_vdd_hvchp__WIDTH 7
#define CP_CFG__cp_vdd_hvchp__SHIFT 0
#define CP_CFG__cp_vdd_hvchp__RESET 0

#define LDO_CTRL 0xea
#define LDO_CTRL__override_ldo_dig_en__MASK  0x80
#define LDO_CTRL__override_ldo_dig_en__WIDTH 1
#define LDO_CTRL__override_ldo_dig_en__SHIFT 7
#define LDO_CTRL__override_ldo_dig_en__RESET 0
#define LDO_CTRL__override_ldo_dig_en 128
#define LDO_CTRL__override_ldo_ana_en__MASK  0x40
#define LDO_CTRL__override_ldo_ana_en__WIDTH 1
#define LDO_CTRL__override_ldo_ana_en__SHIFT 6
#define LDO_CTRL__override_ldo_ana_en__RESET 0
#define LDO_CTRL__override_ldo_ana_en 64
#define LDO_CTRL__override_ldo_lp_hpmode__MASK  0x20
#define LDO_CTRL__override_ldo_lp_hpmode__WIDTH 1
#define LDO_CTRL__override_ldo_lp_hpmode__SHIFT 5
#define LDO_CTRL__override_ldo_lp_hpmode__RESET 0
#define LDO_CTRL__override_ldo_lp_hpmode 32
#define LDO_CTRL__ldo_tdcana_enable__MASK  0x10
#define LDO_CTRL__ldo_tdcana_enable__WIDTH 1
#define LDO_CTRL__ldo_tdcana_enable__SHIFT 4
#define LDO_CTRL__ldo_tdcana_enable__RESET 0
#define LDO_CTRL__ldo_tdcana_enable 16

#define VCSEL_STATUS 0xeb
#define VCSEL_STATUS__cp_overload__MASK  0x80
#define VCSEL_STATUS__cp_overload__WIDTH 1
#define VCSEL_STATUS__cp_overload__SHIFT 7
#define VCSEL_STATUS__cp_overload__RESET 0
#define VCSEL_STATUS__cp_overload 128
#define VCSEL_STATUS__vcdrv_overload__MASK  0x40
#define VCSEL_STATUS__vcdrv_overload__WIDTH 1
#define VCSEL_STATUS__vcdrv_overload__SHIFT 6
#define VCSEL_STATUS__vcdrv_overload__RESET 0
#define VCSEL_STATUS__vcdrv_overload 64
#define VCSEL_STATUS__vcsel_powered__MASK  0x10
#define VCSEL_STATUS__vcsel_powered__WIDTH 1
#define VCSEL_STATUS__vcsel_powered__SHIFT 4
#define VCSEL_STATUS__vcsel_powered__RESET 0
#define VCSEL_STATUS__vcsel_powered 16
#define VCSEL_STATUS__vcsel_ledk_fail__MASK  0x8
#define VCSEL_STATUS__vcsel_ledk_fail__WIDTH 1
#define VCSEL_STATUS__vcsel_ledk_fail__SHIFT 3
#define VCSEL_STATUS__vcsel_ledk_fail__RESET 0
#define VCSEL_STATUS__vcsel_ledk_fail 8
#define VCSEL_STATUS__vcsel_leda_fail__MASK  0x4
#define VCSEL_STATUS__vcsel_leda_fail__WIDTH 1
#define VCSEL_STATUS__vcsel_leda_fail__SHIFT 2
#define VCSEL_STATUS__vcsel_leda_fail__RESET 0
#define VCSEL_STATUS__vcsel_leda_fail 4
#define VCSEL_STATUS__vcsel_ledk_fail_detected__MASK  0x2
#define VCSEL_STATUS__vcsel_ledk_fail_detected__WIDTH 1
#define VCSEL_STATUS__vcsel_ledk_fail_detected__SHIFT 1
#define VCSEL_STATUS__vcsel_ledk_fail_detected__RESET 0
#define VCSEL_STATUS__vcsel_ledk_fail_detected 2
#define VCSEL_STATUS__vcsel_leda_fail_detected__MASK  0x1
#define VCSEL_STATUS__vcsel_leda_fail_detected__WIDTH 1
#define VCSEL_STATUS__vcsel_leda_fail_detected__SHIFT 0
#define VCSEL_STATUS__vcsel_leda_fail_detected__RESET 0
#define VCSEL_STATUS__vcsel_leda_fail_detected 1

#define CLOCK 0xec
#define CLOCK__pll_clk_select__MASK  0x40
#define CLOCK__pll_clk_select__WIDTH 1
#define CLOCK__pll_clk_select__SHIFT 6
#define CLOCK__pll_clk_select__RESET 0
#define CLOCK__pll_clk_select 64
#define CLOCK__pll_on__MASK  0x20
#define CLOCK__pll_on__WIDTH 1
#define CLOCK__pll_on__SHIFT 5
#define CLOCK__pll_on__RESET 0
#define CLOCK__pll_on 32
#define CLOCK__enab_pllclk__MASK  0x10
#define CLOCK__enab_pllclk__WIDTH 1
#define CLOCK__enab_pllclk__SHIFT 4
#define CLOCK__enab_pllclk__RESET 0
#define CLOCK__enab_pllclk 16
#define CLOCK__pll_lost_lock__MASK  0x8
#define CLOCK__pll_lost_lock__WIDTH 1
#define CLOCK__pll_lost_lock__SHIFT 3
#define CLOCK__pll_lost_lock__RESET 0
#define CLOCK__pll_lost_lock 8
#define CLOCK__enable_500khz_mode__MASK  0x4
#define CLOCK__enable_500khz_mode__WIDTH 1
#define CLOCK__enable_500khz_mode__SHIFT 2
#define CLOCK__enable_500khz_mode__RESET 0
#define CLOCK__enable_500khz_mode 4
#define CLOCK__clock_spare__MASK  0x3
#define CLOCK__clock_spare__WIDTH 2
#define CLOCK__clock_spare__SHIFT 0
#define CLOCK__clock_spare__RESET 0

#define MISC0 0xed
#define MISC0__spare_ed__MASK  0x78
#define MISC0__spare_ed__WIDTH 4
#define MISC0__spare_ed__SHIFT 3
#define MISC0__spare_ed__RESET 0
#define MISC0__set_uvcomp_dig_ib5x__MASK  0x7
#define MISC0__set_uvcomp_dig_ib5x__WIDTH 3
#define MISC0__set_uvcomp_dig_ib5x__SHIFT 0
#define MISC0__set_uvcomp_dig_ib5x__RESET 0

#define VCSEL_CFG4 0xee
#define VCSEL_CFG4__override_vcsel_rstn__MASK  0x80
#define VCSEL_CFG4__override_vcsel_rstn__WIDTH 1
#define VCSEL_CFG4__override_vcsel_rstn__SHIFT 7
#define VCSEL_CFG4__override_vcsel_rstn__RESET 0
#define VCSEL_CFG4__override_vcsel_rstn 128
#define VCSEL_CFG4__vcsel_output_inv__MASK  0x40
#define VCSEL_CFG4__vcsel_output_inv__WIDTH 1
#define VCSEL_CFG4__vcsel_output_inv__SHIFT 6
#define VCSEL_CFG4__vcsel_output_inv__RESET 0
#define VCSEL_CFG4__vcsel_output_inv 64
#define VCSEL_CFG4__vcsel_start_edge__MASK  0x20
#define VCSEL_CFG4__vcsel_start_edge__WIDTH 1
#define VCSEL_CFG4__vcsel_start_edge__SHIFT 5
#define VCSEL_CFG4__vcsel_start_edge__RESET 1
#define VCSEL_CFG4__vcsel_start_edge 32
#define VCSEL_CFG4__vcsel_frame_len__MASK  0x1f
#define VCSEL_CFG4__vcsel_frame_len__WIDTH 5
#define VCSEL_CFG4__vcsel_frame_len__SHIFT 0
#define VCSEL_CFG4__vcsel_frame_len__RESET 3

#define P2RAM_CONTROL 0xef
#define P2RAM_CONTROL__p2ram_analog__MASK  0x80
#define P2RAM_CONTROL__p2ram_analog__WIDTH 1
#define P2RAM_CONTROL__p2ram_analog__SHIFT 7
#define P2RAM_CONTROL__p2ram_analog__RESET 0
#define P2RAM_CONTROL__p2ram_analog 128
#define P2RAM_CONTROL__p2ram_gload__MASK  0x40
#define P2RAM_CONTROL__p2ram_gload__WIDTH 1
#define P2RAM_CONTROL__p2ram_gload__SHIFT 6
#define P2RAM_CONTROL__p2ram_gload__RESET 0
#define P2RAM_CONTROL__p2ram_gload 64
#define P2RAM_CONTROL__p2ram_burn__MASK  0x8
#define P2RAM_CONTROL__p2ram_burn__WIDTH 1
#define P2RAM_CONTROL__p2ram_burn__SHIFT 3
#define P2RAM_CONTROL__p2ram_burn__RESET 0
#define P2RAM_CONTROL__p2ram_burn 8
#define P2RAM_CONTROL__p2ram_load__MASK  0x4
#define P2RAM_CONTROL__p2ram_load__WIDTH 1
#define P2RAM_CONTROL__p2ram_load__SHIFT 2
#define P2RAM_CONTROL__p2ram_load__RESET 0
#define P2RAM_CONTROL__p2ram_load 4
#define P2RAM_CONTROL__p2ram_state__MASK  0x3
#define P2RAM_CONTROL__p2ram_state__WIDTH 2
#define P2RAM_CONTROL__p2ram_state__SHIFT 0
#define P2RAM_CONTROL__p2ram_state__RESET 0
// Enumeration for p2ram_state
#define P2RAM_CONTROL__p2ram_state__idle 0 // IDLE    
#define P2RAM_CONTROL__p2ram_state__foundry 2 // FOUNDRY 
#define P2RAM_CONTROL__p2ram_state__locked 3 // LOCKED  


#define RESETREASON 0xf0
#define RESETREASON__soft_reset__MASK  0x80
#define RESETREASON__soft_reset__WIDTH 1
#define RESETREASON__soft_reset__SHIFT 7
#define RESETREASON__soft_reset__RESET 0
#define RESETREASON__soft_reset 128
#define RESETREASON__rrsn_power_on_timer__MASK  0x20
#define RESETREASON__rrsn_power_on_timer__WIDTH 1
#define RESETREASON__rrsn_power_on_timer__SHIFT 5
#define RESETREASON__rrsn_power_on_timer__RESET 0
#define RESETREASON__rrsn_power_on_timer 32
#define RESETREASON__rrsn_power_on_i2c__MASK  0x10
#define RESETREASON__rrsn_power_on_i2c__WIDTH 1
#define RESETREASON__rrsn_power_on_i2c__SHIFT 4
#define RESETREASON__rrsn_power_on_i2c__RESET 0
#define RESETREASON__rrsn_power_on_i2c 16
#define RESETREASON__rrsn_watchdog__MASK  0x8
#define RESETREASON__rrsn_watchdog__WIDTH 1
#define RESETREASON__rrsn_watchdog__SHIFT 3
#define RESETREASON__rrsn_watchdog__RESET 0
#define RESETREASON__rrsn_watchdog 8
#define RESETREASON__rrsn_cpu_reset__MASK  0x4
#define RESETREASON__rrsn_cpu_reset__WIDTH 1
#define RESETREASON__rrsn_cpu_reset__SHIFT 2
#define RESETREASON__rrsn_cpu_reset__RESET 0
#define RESETREASON__rrsn_cpu_reset 4
#define RESETREASON__rrsn_soft_reset__MASK  0x2
#define RESETREASON__rrsn_soft_reset__WIDTH 1
#define RESETREASON__rrsn_soft_reset__SHIFT 1
#define RESETREASON__rrsn_soft_reset__RESET 0
#define RESETREASON__rrsn_soft_reset 2
#define RESETREASON__rrsn_coldstart__MASK  0x1
#define RESETREASON__rrsn_coldstart__WIDTH 1
#define RESETREASON__rrsn_coldstart__SHIFT 0
#define RESETREASON__rrsn_coldstart__RESET 0
#define RESETREASON__rrsn_coldstart 1

#define PINMUX0 0xf1
#define PINMUX0__sclfunc__MASK  0xf0
#define PINMUX0__sclfunc__WIDTH 4
#define PINMUX0__sclfunc__SHIFT 4
#define PINMUX0__sclfunc__RESET 0
// Enumeration for sclfunc
#define PINMUX0__sclfunc__scl 0 // SCL
#define PINMUX0__sclfunc__gpio2 1 // GPIO2
#define PINMUX0__sclfunc__swc 2 // SWC
#define PINMUX0__sclfunc__testmux0 8 // Testmux0
#define PINMUX0__sclfunc__testmux1 9 // Testmux1
#define PINMUX0__sclfunc__testmux2 10 // Testmux2
#define PINMUX0__sclfunc__testmux3 11 // Testmux3
#define PINMUX0__sclfunc__testmux4 12 // Testmux4
#define PINMUX0__sclfunc__testmux5 13 // Testmux5
#define PINMUX0__sclfunc__testmux6 14 // Testmux6
#define PINMUX0__sclfunc__testmux7 15 // Testmux7

#define PINMUX0__sdafunc__MASK  0xf
#define PINMUX0__sdafunc__WIDTH 4
#define PINMUX0__sdafunc__SHIFT 0
#define PINMUX0__sdafunc__RESET 0
// Enumeration for sdafunc
#define PINMUX0__sdafunc__sda 0 // SDA
#define PINMUX0__sdafunc__gpio3 1 // GPIO3
#define PINMUX0__sdafunc__swd 2 // SWD
#define PINMUX0__sdafunc__testmux0 8 // Testmux0
#define PINMUX0__sdafunc__testmux1 9 // Testmux1
#define PINMUX0__sdafunc__testmux2 10 // Testmux2
#define PINMUX0__sdafunc__testmux3 11 // Testmux3
#define PINMUX0__sdafunc__testmux4 12 // Testmux4
#define PINMUX0__sdafunc__testmux5 13 // Testmux5
#define PINMUX0__sdafunc__testmux6 14 // Testmux6
#define PINMUX0__sdafunc__testmux7 15 // Testmux7


#define PINMUX1 0xf2
#define PINMUX1__intfunc__MASK  0xf0
#define PINMUX1__intfunc__WIDTH 4
#define PINMUX1__intfunc__SHIFT 4
#define PINMUX1__intfunc__RESET 0
// Enumeration for intfunc
#define PINMUX1__intfunc__int 0 // INT
#define PINMUX1__intfunc__gpio4 1 // GPIO4
#define PINMUX1__intfunc__swc 2 // SWC
#define PINMUX1__intfunc__uart 3 // UART
#define PINMUX1__intfunc__testmux0 8 // Testmux0
#define PINMUX1__intfunc__testmux1 9 // Testmux1
#define PINMUX1__intfunc__testmux2 10 // Testmux2
#define PINMUX1__intfunc__testmux3 11 // Testmux3
#define PINMUX1__intfunc__testmux4 12 // Testmux4
#define PINMUX1__intfunc__testmux5 13 // Testmux5
#define PINMUX1__intfunc__testmux6 14 // Testmux6
#define PINMUX1__intfunc__testmux7 15 // Testmux7

#define PINMUX1__gpio0func__MASK  0xf
#define PINMUX1__gpio0func__WIDTH 4
#define PINMUX1__gpio0func__SHIFT 0
#define PINMUX1__gpio0func__RESET 0
// Enumeration for gpio0func
#define PINMUX1__gpio0func__gpio0 0 // GPIO0
#define PINMUX1__gpio0func__swd 1 // SWD
#define PINMUX1__gpio0func__vcsel_clk 2 // VCSEL_CLK
#define PINMUX1__gpio0func__uart 3 // UART
#define PINMUX1__gpio0func__sync_out 4 // SYNC_OUT
#define PINMUX1__gpio0func__testmux0 8 // Testmux0
#define PINMUX1__gpio0func__testmux1 9 // Testmux1
#define PINMUX1__gpio0func__testmux2 10 // Testmux2
#define PINMUX1__gpio0func__testmux3 11 // Testmux3
#define PINMUX1__gpio0func__testmux4 12 // Testmux4
#define PINMUX1__gpio0func__testmux5 13 // Testmux5
#define PINMUX1__gpio0func__testmux6 14 // Testmux6
#define PINMUX1__gpio0func__testmux7 15 // Testmux7


#define PINMUX2 0xf3
#define PINMUX2__gpio1func__MASK  0xf0
#define PINMUX2__gpio1func__WIDTH 4
#define PINMUX2__gpio1func__SHIFT 4
#define PINMUX2__gpio1func__RESET 0
// Enumeration for gpio1func
#define PINMUX2__gpio1func__gpio1 0 // GPIO1
#define PINMUX2__gpio1func__swc 1 // SWC
#define PINMUX2__gpio1func__reserved 2 // reserved2
#define PINMUX2__gpio1func__uart 3 // UART
#define PINMUX2__gpio1func__sync_out 4 // SYNC_OUT
#define PINMUX2__gpio1func__testmux0 8 // Testmux0
#define PINMUX2__gpio1func__testmux1 9 // Testmux1
#define PINMUX2__gpio1func__testmux2 10 // Testmux2
#define PINMUX2__gpio1func__testmux3 11 // Testmux3
#define PINMUX2__gpio1func__testmux4 12 // Testmux4
#define PINMUX2__gpio1func__testmux5 13 // Testmux5
#define PINMUX2__gpio1func__testmux6 14 // Testmux6
#define PINMUX2__gpio1func__testmux7 15 // Testmux7


#define EXTCLK 0xf4
#define EXTCLK__en_vcdrv_ext_clk_input__MASK  0x8
#define EXTCLK__en_vcdrv_ext_clk_input__WIDTH 1
#define EXTCLK__en_vcdrv_ext_clk_input__SHIFT 3
#define EXTCLK__en_vcdrv_ext_clk_input__RESET 0
#define EXTCLK__en_vcdrv_ext_clk_input 8
#define EXTCLK__en_vcdrv_ext_clk_output__MASK  0x4
#define EXTCLK__en_vcdrv_ext_clk_output__WIDTH 1
#define EXTCLK__en_vcdrv_ext_clk_output__SHIFT 2
#define EXTCLK__en_vcdrv_ext_clk_output__RESET 0
#define EXTCLK__en_vcdrv_ext_clk_output 4
#define EXTCLK__extclk_pin__MASK  0x2
#define EXTCLK__extclk_pin__WIDTH 1
#define EXTCLK__extclk_pin__SHIFT 1
#define EXTCLK__extclk_pin__RESET 0
#define EXTCLK__extclk_pin 2
// Enumeration for extclk_pin
#define EXTCLK__extclk_pin__gpio0 0 // GPIO0
#define EXTCLK__extclk_pin__int 1 // INT

#define EXTCLK__extclk_mode__MASK  0x1
#define EXTCLK__extclk_mode__WIDTH 1
#define EXTCLK__extclk_mode__SHIFT 0
#define EXTCLK__extclk_mode__RESET 0
#define EXTCLK__extclk_mode 1

#define GPIO_DRVSTR 0xf5
#define GPIO_DRVSTR__en_temp_sensor__MASK  0xc0
#define GPIO_DRVSTR__en_temp_sensor__WIDTH 2
#define GPIO_DRVSTR__en_temp_sensor__SHIFT 6
#define GPIO_DRVSTR__en_temp_sensor__RESET 0
#define GPIO_DRVSTR__gpio1_dvrstr__MASK  0xc
#define GPIO_DRVSTR__gpio1_dvrstr__WIDTH 2
#define GPIO_DRVSTR__gpio1_dvrstr__SHIFT 2
#define GPIO_DRVSTR__gpio1_dvrstr__RESET 0
#define GPIO_DRVSTR__gpio0_dvrstr__MASK  0x3
#define GPIO_DRVSTR__gpio0_dvrstr__WIDTH 2
#define GPIO_DRVSTR__gpio0_dvrstr__SHIFT 0
#define GPIO_DRVSTR__gpio0_dvrstr__RESET 0

#define BVTCCFG 0xf6
#define BVTCCFG__bvtc_rquench__MASK  0x38
#define BVTCCFG__bvtc_rquench__WIDTH 3
#define BVTCCFG__bvtc_rquench__SHIFT 3
#define BVTCCFG__bvtc_rquench__RESET 0
#define BVTCCFG__bvtc_vex__MASK  0x7
#define BVTCCFG__bvtc_vex__WIDTH 3
#define BVTCCFG__bvtc_vex__SHIFT 0
#define BVTCCFG__bvtc_vex__RESET 0

#define BVTC1 0xf7
#define BVTC1__bvtc1_comp_vth__MASK  0x40
#define BVTC1__bvtc1_comp_vth__WIDTH 1
#define BVTC1__bvtc1_comp_vth__SHIFT 6
#define BVTC1__bvtc1_comp_vth__RESET 0
#define BVTC1__bvtc1_comp_vth 64
#define BVTC1__bvtc1_comp_vtl__MASK  0x20
#define BVTC1__bvtc1_comp_vtl__WIDTH 1
#define BVTC1__bvtc1_comp_vtl__SHIFT 5
#define BVTC1__bvtc1_comp_vtl__RESET 0
#define BVTC1__bvtc1_comp_vtl 32
#define BVTC1__lock_bvtc1_comp__MASK  0x10
#define BVTC1__lock_bvtc1_comp__WIDTH 1
#define BVTC1__lock_bvtc1_comp__SHIFT 4
#define BVTC1__lock_bvtc1_comp__RESET 0
#define BVTC1__lock_bvtc1_comp 16
#define BVTC1__reset_bvtc1_comp__MASK  0x8
#define BVTC1__reset_bvtc1_comp__WIDTH 1
#define BVTC1__reset_bvtc1_comp__SHIFT 3
#define BVTC1__reset_bvtc1_comp__RESET 0
#define BVTC1__reset_bvtc1_comp 8
#define BVTC1__en_bvtc1_comp_vth__MASK  0x4
#define BVTC1__en_bvtc1_comp_vth__WIDTH 1
#define BVTC1__en_bvtc1_comp_vth__SHIFT 2
#define BVTC1__en_bvtc1_comp_vth__RESET 0
#define BVTC1__en_bvtc1_comp_vth 4
#define BVTC1__en_bvtc1_comp_vtl__MASK  0x2
#define BVTC1__en_bvtc1_comp_vtl__WIDTH 1
#define BVTC1__en_bvtc1_comp_vtl__SHIFT 1
#define BVTC1__en_bvtc1_comp_vtl__RESET 0
#define BVTC1__en_bvtc1_comp_vtl 2
#define BVTC1__en_bvdetect1__MASK  0x1
#define BVTC1__en_bvdetect1__WIDTH 1
#define BVTC1__en_bvdetect1__SHIFT 0
#define BVTC1__en_bvdetect1__RESET 0
#define BVTC1__en_bvdetect1 1

#define BVTC2 0xf8
#define BVTC2__bvtc2_comp_vth__MASK  0x40
#define BVTC2__bvtc2_comp_vth__WIDTH 1
#define BVTC2__bvtc2_comp_vth__SHIFT 6
#define BVTC2__bvtc2_comp_vth__RESET 0
#define BVTC2__bvtc2_comp_vth 64
#define BVTC2__bvtc2_comp_vtl__MASK  0x20
#define BVTC2__bvtc2_comp_vtl__WIDTH 1
#define BVTC2__bvtc2_comp_vtl__SHIFT 5
#define BVTC2__bvtc2_comp_vtl__RESET 0
#define BVTC2__bvtc2_comp_vtl 32
#define BVTC2__lock_bvtc2_comp__MASK  0x10
#define BVTC2__lock_bvtc2_comp__WIDTH 1
#define BVTC2__lock_bvtc2_comp__SHIFT 4
#define BVTC2__lock_bvtc2_comp__RESET 0
#define BVTC2__lock_bvtc2_comp 16
#define BVTC2__reset_bvtc2_comp__MASK  0x8
#define BVTC2__reset_bvtc2_comp__WIDTH 1
#define BVTC2__reset_bvtc2_comp__SHIFT 3
#define BVTC2__reset_bvtc2_comp__RESET 0
#define BVTC2__reset_bvtc2_comp 8
#define BVTC2__en_bvtc2_comp_vth__MASK  0x4
#define BVTC2__en_bvtc2_comp_vth__WIDTH 1
#define BVTC2__en_bvtc2_comp_vth__SHIFT 2
#define BVTC2__en_bvtc2_comp_vth__RESET 0
#define BVTC2__en_bvtc2_comp_vth 4
#define BVTC2__en_bvtc2_comp_vtl__MASK  0x2
#define BVTC2__en_bvtc2_comp_vtl__WIDTH 1
#define BVTC2__en_bvtc2_comp_vtl__SHIFT 1
#define BVTC2__en_bvtc2_comp_vtl__RESET 0
#define BVTC2__en_bvtc2_comp_vtl 2
#define BVTC2__en_bvdetect2__MASK  0x1
#define BVTC2__en_bvdetect2__WIDTH 1
#define BVTC2__en_bvdetect2__SHIFT 0
#define BVTC2__en_bvdetect2__RESET 0
#define BVTC2__en_bvdetect2 1

#define VCSEL_CFG5 0xf9
#define VCSEL_CFG5__vcsel_start__MASK  0xf0
#define VCSEL_CFG5__vcsel_start__WIDTH 4
#define VCSEL_CFG5__vcsel_start__SHIFT 4
#define VCSEL_CFG5__vcsel_start__RESET 0
#define VCSEL_CFG5__vcsel_length__MASK  0xf
#define VCSEL_CFG5__vcsel_length__WIDTH 4
#define VCSEL_CFG5__vcsel_length__SHIFT 0
#define VCSEL_CFG5__vcsel_length__RESET 0

#define DBGTMUX01 0xfa
#define DBGTMUX01__dbg1mux__MASK  0x70
#define DBGTMUX01__dbg1mux__WIDTH 3
#define DBGTMUX01__dbg1mux__SHIFT 4
#define DBGTMUX01__dbg1mux__RESET 0
// Enumeration for dbg1mux
#define DBGTMUX01__dbg1mux__vcdrv_check_eyesafe 0 // VCDRV_CHECK_EYESAFE_1V2_D  
#define DBGTMUX01__dbg1mux__pll_fdivt 1 // PLL_FDIVT_1V2_D            
#define DBGTMUX01__dbg1mux__i2c_p2ram 2 // i2c.p2ram                         
#define DBGTMUX01__dbg1mux__n_reset_adc 3 // N_RESET_ADC_1V2_D          
#define DBGTMUX01__dbg1mux__bvtc2_comp_vth 4 // BVTC2_COMP_VTH_1V2_D       
#define DBGTMUX01__dbg1mux__i2c_bank 5 // i2c_bank                     
#define DBGTMUX01__dbg1mux__uvcomp_tm1 6 // UVCOMP_TM_1V2_D[1]         
#define DBGTMUX01__dbg1mux__sda_test_del_rise 7 // SDA_TEST_DEL_RISE_1V2_D    

#define DBGTMUX01__dbg0mux__MASK  0x7
#define DBGTMUX01__dbg0mux__WIDTH 3
#define DBGTMUX01__dbg0mux__SHIFT 0
#define DBGTMUX01__dbg0mux__RESET 0
// Enumeration for dbg0mux
#define DBGTMUX01__dbg0mux__chp_overload 0 // CHP_OVERLOAD_1V2_D         
#define DBGTMUX01__dbg0mux__clk_40m 1 // CLK_40M_1V2_D              
#define DBGTMUX01__dbg0mux__i2c_p2ram 2 // i2c.p2ram                         
#define DBGTMUX01__dbg0mux__set_adc_track_extend 3 // SET_ADC_TRACK_EXTEND_1V2_D 
#define DBGTMUX01__dbg0mux__bvtc2_comp_vtl 4 // BVTC2_COMP_VTL_1V2_D       
#define DBGTMUX01__dbg0mux__i2c_bank_request 5 // i2c_bank_request             
#define DBGTMUX01__dbg0mux__uvcomp_tm2 6 // UVCOMP_TM_1V2_D[2]         
#define DBGTMUX01__dbg0mux__sda_test_del_fall 7 // SDA_TEST_DEL_FALL_1V2_D    


#define DBGTMUX23 0xfb
#define DBGTMUX23__dbg3mux__MASK  0x70
#define DBGTMUX23__dbg3mux__WIDTH 3
#define DBGTMUX23__dbg3mux__SHIFT 4
#define DBGTMUX23__dbg3mux__RESET 0
// Enumeration for dbg3mux
#define DBGTMUX23__dbg3mux__leda_fail 0 // LEDA_FAIL_1V2_D            
#define DBGTMUX23__dbg3mux__en_osc 1 // EN_OSC_1V2_D               
#define DBGTMUX23__dbg3mux__gpio0_pad2dig 2 // GPIO0_PAD2DIG_1V2_D        
#define DBGTMUX23__dbg3mux__adc_sdata 3 // ADC_SDATA_1V2_D            
#define DBGTMUX23__dbg3mux__bvtc1_comp_vth 4 // BVTC1_COMP_VTH_1V2_D       
#define DBGTMUX23__dbg3mux__sys_lockup 5 // sys_lockup                   
#define DBGTMUX23__dbg3mux__en_vcseldrv 6 // EN_VCSELDRV_1V2_D          
#define DBGTMUX23__dbg3mux__scl_test_del_rise 7 // SCL_TEST_DEL_RISE_1V2_D    

#define DBGTMUX23__dbg2mux__MASK  0x7
#define DBGTMUX23__dbg2mux__WIDTH 3
#define DBGTMUX23__dbg2mux__SHIFT 0
#define DBGTMUX23__dbg2mux__RESET 0
// Enumeration for dbg2mux
#define DBGTMUX23__dbg2mux__ledk_fail 0 // LEDK_FAIL_1V2_D            
#define DBGTMUX23__dbg2mux__osc_okay 1 // OSC_OKAY_1V2_D             
#define DBGTMUX23__dbg2mux__gpio0_anaen 2 // GPIO0_ANAEN_1V2_D          
#define DBGTMUX23__dbg2mux__adc_start_con 3 // ADC_START_CON_1V2_D        
#define DBGTMUX23__dbg2mux__bvtc1_comp_vtl 4 // BVTC1_COMP_VTL_1V2_D       
#define DBGTMUX23__dbg2mux__sys_halted 5 // sys_halted                   
#define DBGTMUX23__dbg2mux__en_chp 6 // EN_CHP_1V2_D               
#define DBGTMUX23__dbg2mux__scl_test_del_fall 7 // SCL_TEST_DEL_FALL_1V2_d    


#define DBGTMUX45 0xfc
#define DBGTMUX45__dbg5mux__MASK  0x70
#define DBGTMUX45__dbg5mux__WIDTH 3
#define DBGTMUX45__dbg5mux__SHIFT 4
#define DBGTMUX45__dbg5mux__RESET 0
// Enumeration for dbg5mux
#define DBGTMUX45__dbg5mux__vpulse_vcsel 0 // VPULSE_VCSEL_1V2_D         
#define DBGTMUX45__dbg5mux__clk_160m 1 // CLK_160M_1V2_D             
#define DBGTMUX45__dbg5mux__sda_pad2dig3 2 // SDA_PAD2DIG3_1V2_D         
#define DBGTMUX45__dbg5mux__adc_data4 3 // ADC_DATA_1V2_D[4]          
#define DBGTMUX45__dbg5mux__reset_bvtc1_comp 4 // RESET_BVTC1_COMP_1V2_D     
#define DBGTMUX45__dbg5mux__uvcomp_tm0 5 // UVCOMP_TM_1V2_D[0]         
#define DBGTMUX45__dbg5mux__en_pll 6 // EN_PLL_1V2_D               
#define DBGTMUX45__dbg5mux__scl_pad2dig1 7 // SCL_PAD2DIG1_1V2_D         

#define DBGTMUX45__dbg4mux__MASK  0x7
#define DBGTMUX45__dbg4mux__WIDTH 3
#define DBGTMUX45__dbg4mux__SHIFT 0
#define DBGTMUX45__dbg4mux__RESET 0
// Enumeration for dbg4mux
#define DBGTMUX45__dbg4mux__psw_on 0 // PSW_ON_1V2_D               
#define DBGTMUX45__dbg4mux__pll_locked 1 // PLL_LOCKED_1V2_D           
#define DBGTMUX45__dbg4mux__gpio1_pad2dig 2 // GPIO1_PAD2DIG_1V2_D        
#define DBGTMUX45__dbg4mux__adc_eoc 3 // ADC_EOC_1V2_D              
#define DBGTMUX45__dbg4mux__reset_bvtc2_comp 4 // RESET_BVTC2_COMP_1V2_D     
#define DBGTMUX45__dbg4mux__sys_sleeping 5 // sys_sleeping                 
#define DBGTMUX45__dbg4mux__en_ldo_tdc 6 // EN_LDO_TDC_1V2_D           
#define DBGTMUX45__dbg4mux__scl_pad2dig3 7 // SCL_PAD2DIG3_1V2_D         


#define DBGTMUX67 0xfd
#define DBGTMUX67__dbg7mux__MASK  0x70
#define DBGTMUX67__dbg7mux__WIDTH 3
#define DBGTMUX67__dbg7mux__SHIFT 4
#define DBGTMUX67__dbg7mux__RESET 0
// Enumeration for dbg7mux
#define DBGTMUX67__dbg7mux__vdd3v3_dig_ready 0 // VDD3V3_DIG_READY_1V2_D      
#define DBGTMUX67__dbg7mux__clk_5m 1 // CLK_5M_1V2_D               
#define DBGTMUX67__dbg7mux__sda_pad2dig0 2 // SDA_PAD2DIG0_1V2_D         
#define DBGTMUX67__dbg7mux__clk_adc_1m25 3 // CLK_ADC_1M25_1V2_D         
#define DBGTMUX67__dbg7mux__en_bvtc1 4 // EN_BVTC1_1V2_D             
#define DBGTMUX67__dbg7mux__por_tm 5 // POR_TM_1V2_D               
#define DBGTMUX67__dbg7mux__i2c_pon 6 // i2c.pon                           
#define DBGTMUX67__dbg7mux__scl_pad2dig0 7 // SCL_PAD2DIG0_1V2_D         

#define DBGTMUX67__dbg6mux__MASK  0x7
#define DBGTMUX67__dbg6mux__WIDTH 3
#define DBGTMUX67__dbg6mux__SHIFT 0
#define DBGTMUX67__dbg6mux__RESET 0
// Enumeration for dbg6mux
#define DBGTMUX67__dbg6mux__clamp_active 0 // CLAMP_ACTIVE_1V2_D         
#define DBGTMUX67__dbg6mux__clk_vcdrv_160m 1 // CLK_VCDRV_160M_1V2_D       
#define DBGTMUX67__dbg6mux__sda_pad2dig1 2 // SDA_PAD2DIG1_1V2_D         
#define DBGTMUX67__dbg6mux__adc_converting 3 // ADC_CONVERTING_1V2_D       
#define DBGTMUX67__dbg6mux__en_bvtc2 4 // EN_BVTC2_1V2_D             
#define DBGTMUX67__dbg6mux__vcdrv_tmx_dig 5 // VCDRV_TMX_DIG_1V2_D        
#define DBGTMUX67__dbg6mux__i2c_cpu_ready 6 // i2c.cpu_ready                     
#define DBGTMUX67__dbg6mux__scl_pad2dig0 7 // SCL_PAD2DIG0_1V2_D         


#define PASSWORD 0xfe
#define PASSWORD__atpg_mode__MASK  0x80
#define PASSWORD__atpg_mode__WIDTH 1
#define PASSWORD__atpg_mode__SHIFT 7
#define PASSWORD__atpg_mode__RESET 0
#define PASSWORD__atpg_mode 128
#define PASSWORD__chainlen_write_hi__MASK  0x40
#define PASSWORD__chainlen_write_hi__WIDTH 1
#define PASSWORD__chainlen_write_hi__SHIFT 6
#define PASSWORD__chainlen_write_hi__RESET 0
#define PASSWORD__chainlen_write_hi 64
#define PASSWORD__chainlen_write_lo__MASK  0x20
#define PASSWORD__chainlen_write_lo__WIDTH 1
#define PASSWORD__chainlen_write_lo__SHIFT 5
#define PASSWORD__chainlen_write_lo__RESET 0
#define PASSWORD__chainlen_write_lo 32
#define PASSWORD__rg_password2__MASK  0x2
#define PASSWORD__rg_password2__WIDTH 1
#define PASSWORD__rg_password2__SHIFT 1
#define PASSWORD__rg_password2__RESET 0
#define PASSWORD__rg_password2 2
#define PASSWORD__password__MASK  0x1
#define PASSWORD__password__WIDTH 1
#define PASSWORD__password__SHIFT 0
#define PASSWORD__password__RESET 0
#define PASSWORD__password 1

#define CTRLOCC 0xff
#define CTRLOCC__chain_sel__MASK  0xe0
#define CTRLOCC__chain_sel__WIDTH 3
#define CTRLOCC__chain_sel__SHIFT 5
#define CTRLOCC__chain_sel__RESET 0
#define CTRLOCC__pll_bypass__MASK  0x10
#define CTRLOCC__pll_bypass__WIDTH 1
#define CTRLOCC__pll_bypass__SHIFT 4
#define CTRLOCC__pll_bypass__RESET 0
#define CTRLOCC__pll_bypass 16
#define CTRLOCC__refclk_div2__MASK  0x8
#define CTRLOCC__refclk_div2__WIDTH 1
#define CTRLOCC__refclk_div2__SHIFT 3
#define CTRLOCC__refclk_div2__RESET 0
#define CTRLOCC__refclk_div2 8
#define CTRLOCC__ate_is_refclk__MASK  0x4
#define CTRLOCC__ate_is_refclk__WIDTH 1
#define CTRLOCC__ate_is_refclk__SHIFT 2
#define CTRLOCC__ate_is_refclk__RESET 0
#define CTRLOCC__ate_is_refclk 4

#endif // REGISTERS_I2C_H
