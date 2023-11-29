#include "base64.h"
#define getOutputLength(len) len * 3 / 4

static int8_t base64_decode_char(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c - 'A';
	if (c >= 'a' && c <= 'z')
		return c - 'a' + 26;
	if (c >= '0' && c <= '9')
		return c - '0' + 52;
	if (c == '+')
		return 62;
	if (c == '/')
		return 63;
	if (c == '=')
		return 0;
	return -1;
}

static size_t countChars(const char *str)
{
	size_t res = 0;

	while (str[res] && str[res] != '=')
		++res;
	return res;
}

static int createBlock(const char *input)
{
	uint8_t j;
	int block;

	j = 0;
	block = 0;
	while (j < 4)
	{
		int8_t c = base64_decode_char(input[j]);
		if (c < 0)
			return -1;
		block = (block << 6) | c;
		++j;
	}
	return block;
}

size_t parseBlock(uint8_t *output, int block, size_t max)
{
	const uint8_t charMask = 0xFF;
	const uint8_t blockMask = 0x18;
	const uint8_t maxOffset = 0x10;
	uint8_t offset = 0x10;
	size_t i = 0;

	while (offset && i < max)
	{
		offset = maxOffset >> (i % 3) & blockMask;
		output[i++] = (block >> offset) & charMask;
	}

	return i;
}

size_t base64_decode(const char *input, uint8_t **dst)
{
	size_t inputLength;
	size_t outputLength;
	size_t index;
	size_t i;
	int block;

	if (dst == NULL || input == NULL)
		return 0;
	inputLength = countChars(input);
	outputLength = getOutputLength(inputLength);
	if (*dst == NULL)
	{
		if ((*dst = (uint8_t*)malloc(outputLength)) == NULL)
			return 0;
		bzero(*dst, outputLength);
	}
	index = 0;
	i = 0;
	while (i < inputLength)
	{
		if ((block = createBlock(input + i)) < 0)
			return 0;
		index += parseBlock((*dst + index), block, outputLength - index);
		i += 4;
	}

	return index;
}
