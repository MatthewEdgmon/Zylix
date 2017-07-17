/**
 * bitmap_font.h - Basic attempt at font.
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __BITMAP_FONT_H__
#define __BITMAP_FONT_H__

#include <stdint.h>

#define BITMAP_FONT_CHARACTER_WIDTH  8
#define BITMAP_FONT_CHARACTER_HEIGHT 16
#define BITMAP_FONT_CHARACTER_LENGTH (8 * 16)

typedef struct {
    char character;
    uint32_t* bitmap_font_character;
} bitmap_font_table_entry_t;

extern uint64_t bitmap_font_table_length;

extern uint32_t bitmap_font_20_blank[];
extern uint32_t bitmap_font_21_exclamation[];
extern uint32_t bitmap_font_22_double_quote[];
extern uint32_t bitmap_font_23_hashtag[];
extern uint32_t bitmap_font_24_dollar[];
extern uint32_t bitmap_font_25_percent[];
extern uint32_t bitmap_font_26_ampersand[];
extern uint32_t bitmap_font_27_single_quote[];
extern uint32_t bitmap_font_28_left_parentheses[];
extern uint32_t bitmap_font_29_right_parentheses[];
extern uint32_t bitmap_font_2A_star[];
extern uint32_t bitmap_font_2B_plus[];
extern uint32_t bitmap_font_2C_comma[];
extern uint32_t bitmap_font_2D_dash[];
extern uint32_t bitmap_font_2E_period[];
extern uint32_t bitmap_font_2F_right_slash[];
extern uint32_t bitmap_font_30_0[];
extern uint32_t bitmap_font_31_1[];
extern uint32_t bitmap_font_32_2[];
extern uint32_t bitmap_font_33_3[];
extern uint32_t bitmap_font_34_4[];
extern uint32_t bitmap_font_35_5[];
extern uint32_t bitmap_font_36_6[];
extern uint32_t bitmap_font_37_7[];
extern uint32_t bitmap_font_38_8[];
extern uint32_t bitmap_font_39_9[];
extern uint32_t bitmap_font_3A_colon[];
extern uint32_t bitmap_font_3B_semicolon[];
extern uint32_t bitmap_font_3C_left_arrow[];
extern uint32_t bitmap_font_3D_equal[];
extern uint32_t bitmap_font_3E_right_arrow[];
extern uint32_t bitmap_font_3F_question_mark[];
extern uint32_t bitmap_font_40_at[];
extern uint32_t bitmap_font_41_A[];
extern uint32_t bitmap_font_42_B[];
extern uint32_t bitmap_font_43_C[];
extern uint32_t bitmap_font_44_D[];
extern uint32_t bitmap_font_45_E[];
extern uint32_t bitmap_font_46_F[];
extern uint32_t bitmap_font_47_G[];
extern uint32_t bitmap_font_48_H[];
extern uint32_t bitmap_font_49_I[];
extern uint32_t bitmap_font_4A_J[];
extern uint32_t bitmap_font_4B_K[];
extern uint32_t bitmap_font_4C_L[];
extern uint32_t bitmap_font_4D_M[];
extern uint32_t bitmap_font_4E_N[];
extern uint32_t bitmap_font_4F_O[];
extern uint32_t bitmap_font_50_P[];
extern uint32_t bitmap_font_51_Q[];
extern uint32_t bitmap_font_52_R[];
extern uint32_t bitmap_font_53_S[];
extern uint32_t bitmap_font_54_T[];
extern uint32_t bitmap_font_55_U[];
extern uint32_t bitmap_font_56_V[];
extern uint32_t bitmap_font_57_W[];
extern uint32_t bitmap_font_58_X[];
extern uint32_t bitmap_font_59_Y[];
extern uint32_t bitmap_font_5A_Z[];
extern uint32_t bitmap_font_5B_left_bracket[];
extern uint32_t bitmap_font_5C_left_slash[];
extern uint32_t bitmap_font_5D_right_bracket[];
extern uint32_t bitmap_font_5E_carrot[];
extern uint32_t bitmap_font_5F_underscore[];
extern uint32_t bitmap_font_60_quote[];
extern uint32_t bitmap_font_61_a[];
extern uint32_t bitmap_font_62_b[];
extern uint32_t bitmap_font_63_c[];
extern uint32_t bitmap_font_64_d[];
extern uint32_t bitmap_font_65_e[];
extern uint32_t bitmap_font_66_f[];
extern uint32_t bitmap_font_67_g[];
extern uint32_t bitmap_font_68_h[];
extern uint32_t bitmap_font_69_i[];
extern uint32_t bitmap_font_6A_j[];
extern uint32_t bitmap_font_6B_k[];
extern uint32_t bitmap_font_6C_l[];
extern uint32_t bitmap_font_6D_m[];
extern uint32_t bitmap_font_6E_n[];
extern uint32_t bitmap_font_6F_o[];
extern uint32_t bitmap_font_70_p[];
extern uint32_t bitmap_font_71_q[];
extern uint32_t bitmap_font_72_r[];
extern uint32_t bitmap_font_73_s[];
extern uint32_t bitmap_font_74_t[];
extern uint32_t bitmap_font_75_u[];
extern uint32_t bitmap_font_76_v[];
extern uint32_t bitmap_font_77_w[];
extern uint32_t bitmap_font_78_x[];
extern uint32_t bitmap_font_79_y[];
extern uint32_t bitmap_font_7A_z[];
extern uint32_t bitmap_font_7B_left_curly_bracket[];
extern uint32_t bitmap_font_7C_pipe[];
extern uint32_t bitmap_font_7D_right_curly_bracket[];
extern uint32_t bitmap_font_7E_tilde[];
extern uint32_t bitmap_font_7F_DEL[];

extern bitmap_font_table_entry_t bitmap_font_table[];

#endif /* __BITMAP_FONT_H__ */
