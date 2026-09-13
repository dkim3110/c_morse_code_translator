#ifndef MORSE_H_
#define MORSE_H_

#include "string_view.h"

#define LOOKUP_LEN ('Z' + 1)

static char *lookup[] = {
	['0'] = "-----", 	['1'] = ".----",
	['2'] = "..---", 	['3'] = "...--",
	['4'] = "....-", 	['5'] = ".....",
	['6'] = "-....", 	['7'] = "--...",
	['8'] = "---..", 	['9'] = "----.",

	['A'] = ".-", 		['B'] = "-...",
	['C'] = "-.-.", 	['D'] = "-..",
	['E'] = ".", 			['F'] = "..-.",
	['G'] = "--.", 		['H'] = "....",
	['I'] = "..", 		['J'] = ".---",
	['K'] = "-.-", 		['L'] = ".-..",
	['M'] = "--", 		['N'] = "-.",
	['O'] = "---", 		['P'] = ".--.",
	['Q'] = "--.-", 	['R'] = ".-.",
	['S'] = "...", 		['T'] = "-",
	['U'] = "..-", 		['V'] = "...-",
	['W'] = ".--", 		['X'] = "-..-",
	['Y'] = "-.--", 	['Z'] = "--..",
};

typedef enum {
	HELP,
	MORSE,
	DEFAULT,
	UNKNOWN
} project_flag_t;

typedef struct {
	project_flag_t flag;
} config_t;

typedef struct {
	str short_name;
	str full_name;
} flag_t;

#endif // MORSE_H_
