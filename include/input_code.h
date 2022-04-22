/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_code.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:09:41 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/22 19:17:13 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_CODE_H
# define INPUT_CODE_H

# define MOUSE_LEFT			1
# define MOUSE_MIDDLE		2
# define MOUSE_RIGHT		3
# define MOUSE_WHEELUP		4
# define MOUSE_WHEELDOWN	5
# define MOUSE_LEFTWHEEL	6
# define MOUSE_RIGHTWHEEL	7
# define MOUSE_UPTHUMB		8
# define MOUSE_DOWNTHUMB	9

# ifdef __linux__
#  define KEY_SPACE			32

#  define KEY_COMMA			44
#  define KEY_MINUS			45
#  define KEY_PERIOD		46
#  define KEY_SLASH			47

/* Top row not Keypad */
#  define KEY_ZERO			48
#  define KEY_ONE			49
#  define KEY_TWO			50
#  define KEY_THREE			51
#  define KEY_FOUR			52
#  define KEY_FIVE			53
#  define KEY_SIX			54
#  define KEY_SEVEN			55
#  define KEY_EIGHT			56
#  define KEY_NINE			57

#  define KEY_SEMICOLON		59
#  define KEY_EQUAL			61

#  define KEY_LBRACKET		91
#  define KEY_BCKSLASH		92
#  define KEY_RBRACKET		93

#  define KEY_GRAVE			96

#  define KEY_A				97
#  define KEY_B				98
#  define KEY_C				99
#  define KEY_D				100
#  define KEY_E				101
#  define KEY_F				102
#  define KEY_G				103
#  define KEY_H				104
#  define KEY_I				105
#  define KEY_J				106
#  define KEY_K				107
#  define KEY_L				108
#  define KEY_M				109
#  define KEY_N				110
#  define KEY_O				111
#  define KEY_P				112
#  define KEY_Q				113
#  define KEY_R				114
#  define KEY_S				115
#  define KEY_T				116
#  define KEY_U				117
#  define KEY_V				118
#  define KEY_W				119
#  define KEY_X				120
#  define KEY_Y				121
#  define KEY_Z				122

#  define KEY_F1			65470
#  define KEY_F2			65471
#  define KEY_F3			65472
#  define KEY_F4			65473
#  define KEY_F5			65474
#  define KEY_F6			65475
#  define KEY_F7			65476
#  define KEY_F8			65477
#  define KEY_F9			65478
#  define KEY_F10			65479
#  define KEY_F11			65480
#  define KEY_F12			65481

#  define KEY_BACKSPACE		65288
#  define KEY_TAB			65289
#  define KEY_RETURN		65293
#  define KEY_ESC			65307

#  define KEY_LEFT			65361
#  define KEY_UP			65362
#  define KEY_RIGHT			65363
#  define KEY_DOWN			65364

#  define KEY_HOME			65360
#  define KEY_PGUP			65365
#  define KEY_PGDOWN		65366
#  define KEY_END			65367
#  define KEY_INS			65379
#  define KEY_DEL			65535

#  define KEY_MENU			65383
#  define KEY_LSHIFT		65505
#  define KEY_RSHIFT		65506
#  define KEY_LCTRL			65507
#  define KEY_RCTRL			65508
#  define KEY_CAPS			65509
#  define KEY_LMETA			65513
#  define KEY_RMETA			65514

#  define KEY_PAUSE			65299
#  define KEY_SCRLK			65300
#  define KEY_PRTSC			65301

# else
#  define KEY_SPACE 49

#  define KEY_COMMA 43
#  define KEY_MINUS 27
#  define KEY_PERIOD 47
#  define KEY_SLASH 44

#  define KEY_ZERO 29
#  define KEY_ONE 18
#  define KEY_TWO 19
#  define KEY_THREE 20
#  define KEY_FOUR 21
#  define KEY_FIVE 23
#  define KEY_SIX 22
#  define KEY_SEVEN 26
#  define KEY_EIGHT 28
#  define KEY_NINE 25

#  define KEY_SEMICOLON 41
#  define KEY_EQUAL 24

#  define KEY_LBRACKET 33
#  define KEY_BCKSLASH 42
#  define KEY_RBRACKET 30

#  define KEY_GRAVE 50

#  define KEY_A 0
#  define KEY_B 11
#  define KEY_C 8
#  define KEY_D 2
#  define KEY_E 14
#  define KEY_F 3
#  define KEY_G 5
#  define KEY_H 4
#  define KEY_I 34
#  define KEY_J 38
#  define KEY_K 40
#  define KEY_L 37
#  define KEY_M 46
#  define KEY_N 45
#  define KEY_O 31
#  define KEY_P 35
#  define KEY_Q 12
#  define KEY_R 15
#  define KEY_S 1
#  define KEY_T 17
#  define KEY_U 32
#  define KEY_V 9
#  define KEY_W 13
#  define KEY_X 7
#  define KEY_Y 16
#  define KEY_Z 6

#  define KEY_F1 122
#  define KEY_F2 120
#  define KEY_F3 99
#  define KEY_F4 118
#  define KEY_F5 96
#  define KEY_F6 97
#  define KEY_F7 98
#  define KEY_F8 100
#  define KEY_F9 101
#  define KEY_F10 109
#  define KEY_F11
#  define KEY_F12 111

#  define KEY_BACKSPACE 51
#  define KEY_TAB 48
#  define KEY_RETURN 36
#  define KEY_ESC 53

#  define KEY_LEFT 123
#  define KEY_UP 126
#  define KEY_RIGHT 124
#  define KEY_DOWN 125

#  define KEY_HOME 115
#  define KEY_PGUP 116
#  define KEY_PGDOWN 121
#  define KEY_END 119
#  define KEY_INS 114
#  define KEY_DEL 117

#  define KEY_MENU 110
#  define KEY_LSHIFT 257
#  define KEY_RSHIFT 258
#  define KEY_LCTRL 256
#  define KEY_RCTRL 269
#  define KEY_CAPS 272
#  define KEY_LMETA 261
#  define KEY_RMETA 262

#  define KEY_PAUSE 113
#  define KEY_SCRLK 107
#  define KEY_PRTSC 105
# endif

#endif
