#ifndef BASE64_H
# define BASE64_H

# ifndef _UNISTD_H_
#  include <unistd.h>
# endif
# ifndef _STDLIB_H_
#  include <stdlib.h>
# endif
# ifndef _STRINGS_H_
#  include <strings.h>
# endif

size_t	base64_decode(const char *input, uint8_t **dst);
char 	*base64_encode(const uint8_t *data, ssize_t data_length);
#endif
