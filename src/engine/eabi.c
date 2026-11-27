/* GCC PowerPC EABI runtime (eabi.asm), 0x8025FA24-0x8025FABC: the out-of-line register save and
   restore sequences. A function that saves r(N)..r31 points r11 at its frame and calls
   _savegpr_N, which stores the registers below r11 and returns; _restgpr_N loads them back.
   The CodeWarrior-built VM library (src/dolphin/vm) is the only caller. Hand-written assembly:
   each sequence is one function, with the later entry points as global labels inside it. */

/* From GCC 2.95.3 gcc/config/rs6000/eabi.asm:
 *   Copyright (C) 1995, 1996, 1998 Free Software Foundation, Inc.
 *   Written By Michael Meissner
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * In addition to the permissions in the GNU General Public License, the
 * Free Software Foundation gives you unlimited permission to link the
 * compiled version of this file with other programs, and to distribute
 * those programs without any restriction coming from the use of this
 * file.  (The General Public License restrictions do apply in other
 * respects; for example, they cover modification of the file, and
 * distribution when not linked into another program.)
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *    As a special exception, if you link this library with files
 *    compiled with GCC to produce an executable, this does not cause
 *    the resulting executable to be covered by the GNU General Public License.
 *    This exception does not however invalidate any other reasons why
 *    the executable file might be covered by the GNU General Public License.
 */

asm(
"    .section \".text\"\n"
"    .align 2\n"
);

asm(
"    .globl _savegpr_14\n"
"    .type _savegpr_14,@function\n"
"_savegpr_14:\n"
"    stw     14,-72(11)\n"
"    .globl _savegpr_15\n"
"_savegpr_15:\n"
"    stw     15,-68(11)\n"
"    .globl _savegpr_16\n"
"_savegpr_16:\n"
"    stw     16,-64(11)\n"
"    .globl _savegpr_17\n"
"_savegpr_17:\n"
"    stw     17,-60(11)\n"
"    .globl _savegpr_18\n"
"_savegpr_18:\n"
"    stw     18,-56(11)\n"
"    .globl _savegpr_19\n"
"_savegpr_19:\n"
"    stw     19,-52(11)\n"
"    .globl _savegpr_20\n"
"_savegpr_20:\n"
"    stw     20,-48(11)\n"
"    .globl _savegpr_21\n"
"_savegpr_21:\n"
"    stw     21,-44(11)\n"
"    .globl _savegpr_22\n"
"_savegpr_22:\n"
"    stw     22,-40(11)\n"
"    .globl _savegpr_23\n"
"_savegpr_23:\n"
"    stw     23,-36(11)\n"
"    .globl _savegpr_24\n"
"_savegpr_24:\n"
"    stw     24,-32(11)\n"
"    .globl _savegpr_25\n"
"_savegpr_25:\n"
"    stw     25,-28(11)\n"
"    .globl _savegpr_26\n"
"_savegpr_26:\n"
"    stw     26,-24(11)\n"
"    .globl _savegpr_27\n"
"_savegpr_27:\n"
"    stw     27,-20(11)\n"
"    .globl _savegpr_28\n"
"_savegpr_28:\n"
"    stw     28,-16(11)\n"
"    .globl _savegpr_29\n"
"_savegpr_29:\n"
"    stw     29,-12(11)\n"
"    .globl _savegpr_30\n"
"_savegpr_30:\n"
"    stw     30,-8(11)\n"
"    .globl _savegpr_31\n"
"_savegpr_31:\n"
"    stw     31,-4(11)\n"
"    blr\n"
"    .size _savegpr_14,.-_savegpr_14\n"
);

asm(
"    .globl _restgpr_14\n"
"    .type _restgpr_14,@function\n"
"_restgpr_14:\n"
"    lwz     14,-72(11)\n"
"    .globl _restgpr_15\n"
"_restgpr_15:\n"
"    lwz     15,-68(11)\n"
"    .globl _restgpr_16\n"
"_restgpr_16:\n"
"    lwz     16,-64(11)\n"
"    .globl _restgpr_17\n"
"_restgpr_17:\n"
"    lwz     17,-60(11)\n"
"    .globl _restgpr_18\n"
"_restgpr_18:\n"
"    lwz     18,-56(11)\n"
"    .globl _restgpr_19\n"
"_restgpr_19:\n"
"    lwz     19,-52(11)\n"
"    .globl _restgpr_20\n"
"_restgpr_20:\n"
"    lwz     20,-48(11)\n"
"    .globl _restgpr_21\n"
"_restgpr_21:\n"
"    lwz     21,-44(11)\n"
"    .globl _restgpr_22\n"
"_restgpr_22:\n"
"    lwz     22,-40(11)\n"
"    .globl _restgpr_23\n"
"_restgpr_23:\n"
"    lwz     23,-36(11)\n"
"    .globl _restgpr_24\n"
"_restgpr_24:\n"
"    lwz     24,-32(11)\n"
"    .globl _restgpr_25\n"
"_restgpr_25:\n"
"    lwz     25,-28(11)\n"
"    .globl _restgpr_26\n"
"_restgpr_26:\n"
"    lwz     26,-24(11)\n"
"    .globl _restgpr_27\n"
"_restgpr_27:\n"
"    lwz     27,-20(11)\n"
"    .globl _restgpr_28\n"
"_restgpr_28:\n"
"    lwz     28,-16(11)\n"
"    .globl _restgpr_29\n"
"_restgpr_29:\n"
"    lwz     29,-12(11)\n"
"    .globl _restgpr_30\n"
"_restgpr_30:\n"
"    lwz     30,-8(11)\n"
"    .globl _restgpr_31\n"
"_restgpr_31:\n"
"    lwz     31,-4(11)\n"
"    blr\n"
"    .size _restgpr_14,.-_restgpr_14\n"
);
