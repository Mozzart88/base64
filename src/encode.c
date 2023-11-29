#include "base64.h"
#define shift1 8
#define shift_in(block, c) (block << shift1) | c
#define shift2 6
#define mask 0x3f
#define BLOCK_SIZE 24
#define shift(offset) BLOCK_SIZE - offset * shift2
#define get_index(blk, offset) (blk >> (shift(offset))) & mask
#define count_res_len(len) ((3 - len%3) + len) / 3 * 4
static char base64_encode_byte(uint8_t byte)
{
    const char base64_chars[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    return base64_chars[byte];
}

static uint32_t	get_block(const uint8_t *data, ssize_t data_length)
{
	uint32_t block;
	int j;
	block = 0;
	j = 0;
	while (j < 3)
	{
		if (data_length-- > 0)
			block = shift_in(block, *data);
		else
			block <<= shift1;
		++j;
		++data;
	}
	return block;
}

static char	*parse_block(uint32_t block, char *tmp, ssize_t data_length)
{
	int j;
	j = 0;
	while (j++ < 4) {
		if (data_length-- >= 0)
			*tmp = base64_encode_byte(get_index(block, j));
		else
			*tmp = '=';
		++tmp;
	}
	return tmp;
}

char *base64_encode(const uint8_t *data, ssize_t data_length)
{
	uint32_t block;
	char *res = NULL;
	char *tmp;
	
	if ((res = (char*)malloc(count_res_len(data_length))) == NULL)
		return NULL;
	bzero(res, count_res_len(data_length));	
	tmp = res;
	while (data_length > 0)
	{
		block = get_block(data, data_length);
		tmp = parse_block(block, tmp, data_length);
		data_length -= 3;
		data += 3;
    }
	return res;
}
