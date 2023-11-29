#include "base64.h"

typedef struct	s_data {
	size_t		len;
	uint8_t		*data;
}				t_data;

void test_encode(void)
{
	const int data_len = 32;
	const int tests_count = 6;
	const t_data test_data[tests_count][data_len] = {
		{{13, (uint8_t*)"Hello, World!"}},
		{{32,(uint8_t*)		"\x53\x61\x6c\x74\x65\x64\x5f\x5f\xc6\x27\xe0\x24\x91\x27\x9c\xe4\xb2\x4b\x2b\xa6\x9e\x96\x0a\xab\x60\x27\xeb\x94\x8d\x15\x0a\x61"}},
		{{32,(uint8_t*)"\x53\x61\x6c\x74\x65\x64\x5f\x5f\x80\xb8\x71\xf6\x83\xaf\xd2\xab\xab\xb2\x42\xaa\x78\xfd\xdb\x70\xe5\x39\x47\xad\xbd\xe6\x3f\x70"}},
		{{32,(uint8_t*)"\x53\x61\x6c\x74\x65\x64\x5f\x5f\xdd\xf9\xe7\x4e\xba\xd2\x94\xd5\x77\x50\xd9\x15\xe6\x68\xd4\xba\x4f\x2c\x59\xef\x71\xf2\x4d\xf0"}},
		{{32,(uint8_t*)"\x53\x61\x6c\x74\x65\x64\x5f\x5f\x62\x7b\x1f\xcb\xb9\x1d\x27\x9a\xaf\xa7\xf9\xd2\x11\xbe\xb8\x16\x55\xfc\xce\x6d\x04\x2a\x72\x50"}},
		{{32,(uint8_t*)"\x53\x61\x6c\x74\x65\x64\x5f\x5f\x59\x21\xd9\x5e\x80\xe1\x61\x8a\x58\x19\x9a\x1c\xaf\x56\x0a\x85\x56\x2e\x08\xdb\x47\x92\xaa\x30"}}
		};
	const char expected[tests_count][45] = {
		"SGVsbG8sIFdvcmxkIQ==",
		"U2FsdGVkX1/GJ+AkkSec5LJLK6aelgqrYCfrlI0VCmE=",
		"U2FsdGVkX1+AuHH2g6/Sq6uyQqp4/dtw5TlHrb3mP3A=",
		"U2FsdGVkX1/d+edOutKU1XdQ2RXmaNS6TyxZ73HyTfA=",
		"U2FsdGVkX19iex/LuR0nmq+n+dIRvrgWVfzObQQqclA=",
		"U2FsdGVkX19ZIdlegOFhilgZmhyvVgqFVi4I20eSqjA=",
		};
	
	char *actual = NULL;

	uint8_t i = 0;
	write(STDOUT_FILENO, "Test encode: ", 13);
	while (i < tests_count)
	{
		t_data test_d = *(test_data[i]);
		actual = base64_encode(test_d.data, test_d.len);
		if (strcmp(actual, expected[i]) == 0)
		{
			write(STDOUT_FILENO, ".", 1);
		} else {
			write(STDOUT_FILENO, "X", 1);
		}
		bzero(actual, 45);
		free(actual);
		++i;
	}
	write(STDOUT_FILENO, "\n", 1);
}
