#include "infix.h"
/*#define TESTING_CONVERTERS*/

/**
 * str_to_intarray - convert a string of numbers to a 32 bit int array
 * @num_str: a string of only integers
 *
 * Description: This function converts a string of numbers to an array of
 * unsigned 32 bit integers.
 * The array will be in little endian style whereby the lower value numbers
 * will be placed in the lower indices. Index 0 will have a value greater
 * than 0 indicating the size of the array.
 *
 * Return: an array of 32 bit ints, NULL on failure
 */
mid_uint *str_to_intarray(lo_uint *num_str)
{
	size_t array_sz = 0, len = 0, h = 0;
	int i = 0, g = 0;
	mid_uint *array = NULL;

	if (!num_str)
		return (NULL);

	num_str += pad_char((char *)num_str, "0");
	for (len = 0; num_str[len] >= '0' && num_str[len] <= '9'; len++)
		;

	if (!len)
	{
		print_help(); /*Insufficient digits*/
		return (NULL);
	}

	array_sz = (len / MID_MAX_DIGITS) + ((len % MID_MAX_DIGITS) ? 1 : 0);
	array = calloc((array_sz + 2), sizeof(*array));
	if (!array)
	{
		perror("Malloc Fail");
		return (NULL);
	}

	/*Index 0 will have the size of the array*/
	array[0] = array_sz;
	/*The number in the string will be read from the least significant digit*/
	for (h = 1, g = (len - 1); h <= array_sz && g >= 0; h++)
	{
		for (i = 0; i < MID_MAX_DIGITS && (g - i) >= 0; i++)
			array[h] += (num_str[g - i] - '0') * (mid_uint)(pow(10, i));

		g -= i;
	}

	return (array);
}

/**
 * intarr_to_str - convert a 32 bit int array to a string of numbers
 * @array: a 32 bit array
 *
 * Description: This function converts an array of unsigned 32 bit integers
 * to a string.
 * The array should be in little endian style whereby the lower value numbers
 * will be placed in the lower indices. Index 0 will have a value greater
 * than 0 indicating the size of the array.
 *
 * Return: a string of numbers, NULL on failure
 */
lo_uint *intarr_to_str(mid_uint *array)
{
	size_t array_sz = 0, len = 0, g = 0, h = 0, i = 0;
	lo_uint *num_str = NULL, negative = '\0';
	ssize_t temp = 0, div = 1;

	if (!array)
		return (NULL);

	array_sz = array[0];
	/*Checking if the number is negative*/
	if (array[array_sz] & MID_NEGBIT)
	{
		array[array_sz] ^= MID_NEGBIT;
		len += 1;
		negative = '-';
	}

	trim_intarr(&array);
	array_sz = array[0];
	len += array_sz * MID_MAX_DIGITS;
	num_str = calloc((len + 1), sizeof(*num_str));
	if (!num_str)
	{
		perror("Malloc Fail");
		return (NULL);
	}

	if (negative)
		num_str++;

	temp = array[array_sz];
	while (temp / div >= 10)
		div *= 10;

	for (h = array_sz, g = 0; h > 0 && g < len; h--)
	{
		temp = array[h];
		for (i = 0; div && (g + i) < len; i++)
		{
			num_str[g + i] = (temp / div) + '0';
			temp %= div;
			div /= 10;
		}

		g += i;
		div = (MID_MAX_VAL / 10);
	}

	if (negative)
	{
		num_str--;
		num_str[0] = '-';
	}

	return (num_str);
}

/**
 * trim_intarr - trims empty spaces from the end of an int array
 * @arr: pointer to the mid_uint arrary
 */
void trim_intarr(mid_uint **arr)
{
	size_t arr_sz = 0;

	if (!arr || !(*arr))
		return;

	arr_sz = (*arr)[0];
	while (!(*arr)[arr_sz] && arr_sz > 1)
		--arr_sz;

	(*arr)[0] = arr_sz;
}

#ifdef TESTING_CONVERTERS
/**
 * pad_char - calculates length of initial padding characters in a string
 * @str: the string to check
 * @ch: the character
 *
 * Return: number of padding characters
 */
size_t pad_char(char *str, char *ch)
{
	size_t zeros = 0, len = 0;

	if (str)
	{
		len = strlen(str);
		zeros = strspn(str, ch);
		if (len && (zeros == len))
			zeros--;
	}

	return (zeros);
}

/**
 * main - testing entry point
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	size_t i = 0, g = 0;
	mid_uint *ntemp = NULL, len = 0;
	lo_uint *stemp = NULL;
	char *nstr[] = {
		"123456789",
		"12345678912",
		"1000000000",
		"909897004000000000078234587",
		"0",
		"12",
		"00000678",
		"00000678912",
		"000000000003456",
		"00000100000000200000000300000000004000000",
		NULL,
	};

	while (nstr[g])
	{
		printf("%s\n", &nstr[g][pad_char(nstr[g], "0")]);
		/*ntemp = str_to_intarray((lo_uint *)(&nstr[g][pad_char(nstr[g], "0")]));*/
		/*printf("%s\n", nstr[g]);*/
		ntemp = str_to_intarray((lo_uint *)nstr[g]);
		if (!ntemp)
			return (EXIT_FAILURE);

		len = ntemp[0];
		for (i = len; i > 0; i--)
		{
			if (i < len)
				printf("%09d", (mid_uint)ntemp[i]);
			else
				printf("%d", (mid_uint)ntemp[i]);
		}

		printf(" [%d: Blocks]\n", (int)len);
		stemp = intarr_to_str(ntemp);
		free(ntemp);
		if (stemp)
			printf("%s\n\n", (char *)stemp);
		else
			return (EXIT_FAILURE);

		free(stemp);
		ntemp = NULL;
		stemp = NULL;
		g++;
	}

	return (EXIT_SUCCESS);
}
#endif
