#ifndef FAT_STRING_H_
#define FAT_STRING_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define FAT_STR_TRUE (1)
#define FAT_STR_FALSE (0)
#define FAT_STR_CHAR_NUM (256)
#define STR_FMT "%.*s"
#define STR_ARG(s) (int) (s).len, (s).data

typedef struct {
	const char *data;
	size_t len;
} str;

// == CHECKING ============================================================
/*
 * Function to verify if a given str struct is empty.
 * Returns 1 if true, 0 if false.
 */

static inline int str_is_empty(str s) {
	return ((s.len == 0) || (!s.data));
} /* str_is_empty() */

/*
 * Function to verify if two str structs are equal.
 * Returns 1 if true, 0 if false.
 */

static inline int str_equals(str a, str b) {
	if (a.len != b.len) return FAT_STR_FALSE;
	if (str_is_empty(a) || str_is_empty(b)) return (str_is_empty(a) == str_is_empty(b));
	return (memcmp(a.data, b.data, b.len) == 0);
} /* str_equals() */
// ============================================================ CHECKING ==

// == I/O =================================================================

/*
 * Function to write a str struct to a specified file stream.
 */

static inline void fput_str(str s, FILE *stream) {
	if ((!stream) || (str_is_empty(s))) return;
	fwrite(s.data, sizeof(char), s.len, stream);
} /* fput_str() */

/*
 * Function to print a str struct to stdout.
 */

static inline void print_str(str s) {
	fput_str(s, stdout);
} /* print_str() */
// ================================================================= I/O ==

// == CONVERSION ==========================================================

/*
 * Function to convert a standard char pointer into a str struct.
 */

static inline str to_str(const char *cstring) {
	return (str) {
		.data = (cstring) ? cstring : NULL,
		.len = (cstring) ? strlen(cstring) : 0
	};
} /* to_str() */
// ========================================================== CONVERSION ==

#endif // FAT_STRING_H_
