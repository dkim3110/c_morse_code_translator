#include "morse.h"
#include "dynamic_array.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EXIT_HELP (2)
#define EXIT_FLAG (3)

static flag_t g_flags_list[] = {
	[HELP] = {{.data = "-h", .len = 2}, {.data = "--help", .len = 6}},
	[MORSE] = {{.data = "-m", .len = 2}, {.data = "--morse", .len = 7}},
};

static void print_help_message(char *program) {
	char *sample_text = "string to translate";
	fputs(
		"\n"
		"DESCRIPTION:\n"
		" A simple command-line utility to translate Morse code to and from English.\n"
		"\n"
		, stderr
	);
	fprintf(stderr,
			"USAGE:\n"
			" %s [flag] %s\n"
			" %s %s [flag]\n"
			"\n"
			, program, sample_text
			, program, sample_text
	);
	fputs(
			"FLAGS:\n"
			" -h, --help\tPrints this help message; overrides all arguments\n"
			" -m, --morse\tTranslates Morse code into English; must not contain alphanumeric characters\n"
			" [no flags]\tTranslates English into Morse code; ignores non-alphanumeric characters\n"
			"\n"
			, stderr
	);
}

static int parse_args(int argc, char *argv[], project_flag_t *project_flag) {
	for (int n = 1; n < argc; n++) {
		str arg = to_str(argv[n]);
		if ((str_equals(arg, g_flags_list[HELP].short_name)) ||
				(str_equals(arg, g_flags_list[HELP].full_name))) return EXIT_HELP;
	}

	for (int n = 1; n < argc; n++) {
		str arg = to_str(argv[n]);
		if ((str_equals(arg, g_flags_list[MORSE].short_name)) ||
				(str_equals(arg, g_flags_list[MORSE].full_name))) {
			*project_flag = MORSE;
			return EXIT_FLAG;
		}

		if ((argv[n][0] == '-') && (isalnum(argv[n][1]))) {
			*project_flag = UNKNOWN;
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

static void alpha_to_morse(int argc, char **argv) {
	for (int n = 1; n < argc; n++) {
		int check = -1;

		for (int m = 0; argv[n][m] != '\0'; m++) {
			char curr = toupper(argv[n][m]);
			if ((curr < '0') || (curr > 'Z')) continue;
			if ((curr < 'A') && (curr > '9')) continue;

			char *alpha = lookup[(unsigned char) curr];
			if (!alpha) continue;

			check = fputs(alpha, stdout);
			putchar(' ');
		}

		if ((check >= 0) && (n < argc - 1)) fputs("/ ", stdout);
	}

	putchar('\n');
}

static void morse_to_alpha(int argc, char **argv) {
	if (argc < 3) return;
	char *code = NULL;

	for (int n = 1; n < argc; n++) {
		str word = to_str(argv[n]);

		if ((str_equals(word, g_flags_list[MORSE].short_name)) ||
				(str_equals(word, g_flags_list[MORSE].full_name))) continue;

		if (argv[n][0] == '/') {
			arr_push(code, ' ');
			continue;
		}

		for (size_t m = 0; m < word.len; m++) {
			if (isalnum(word.data[m])) {
				fputs("-fatal: string is not Morse code\n", stderr);
				return;
			}
		}

		for (char c = '0'; c < LOOKUP_LEN; c++) {
			if ((c < 'A') && (c > '9')) continue;

			str prefix = to_str(lookup[(unsigned char) c]);

			if (str_equals(word, prefix)) {
				if (!arr_push(code, c)) {
					fputs("-fatal: failed to allocate memory\n", stdout);
					goto free_array;
				}
			}
		}
	}

	arr_push(code, '\0');
	fputs(code, stdout);
	putchar('\n');
free_array:
	arr_free(code);
}

int main(int argc, char *argv[]) {
	project_flag_t project_flag = {DEFAULT};

	int check_args = parse_args(argc, argv, &project_flag);

	if (check_args == EXIT_HELP) {
		print_help_message(argv[0]);
		return EXIT_HELP;
	}

	if (check_args == EXIT_FAILURE) {
		if (project_flag == UNKNOWN) fputs("-fatal: unknown flag\n", stderr);
		return EXIT_FAILURE;
	}

	if (argc < 2) {
too_few_args:
		fputs("-fatal: no arguments given\n", stderr);
		return EXIT_FAILURE;
	}

	switch (project_flag) {
		case MORSE:
			if (argc < 3) goto too_few_args;
			morse_to_alpha(argc, argv);
			break;
		default:
			alpha_to_morse(argc, argv);
			break;
	}

	return EXIT_SUCCESS;
}
