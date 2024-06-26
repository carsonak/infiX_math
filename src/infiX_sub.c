#include "infiX.h"

static u4b_array *subtract_negatives(u4b_array *n1, u4b_array *n2)
	ATTR_NONNULL;

/**
 * infiX_subtraction - subtract large numbers stored in arrays
 * @n1: number to be subtracted
 * @n2: number to subtract
 *
 * Return: pointer to the diff, NULL on failure
 */
u4b_array *infiX_subtraction(u4b_array *n1, u4b_array *n2)
{
	size_t n1_i = 0, n2_i = 0, diff_i = 0, result_len = 0;
	ssize_t n1_is_bigger = 0;
	int64_t byt_diff = 0;
	u4b_array *diff = NULL;

	if (!n1 || !n2)
		return (NULL);

	trim_u4b_array(n1);
	trim_u4b_array(n2);
	if (n1->is_negative || n2->is_negative)
		return (subtract_negatives(n1, n2));

	/*result_len = max(n1->len, n2->len)*/
	result_len = (n1->len > n2->len) ? n1->len : n2->len;
	/*If both arrays are of the same length then;*/
	/*result_len = n1->len - */
	/*(length of continuous matches in n1 and n2 from msd down to lsd).*/
	if (n1->len == n2->len)
		while (result_len > 2 && n1->array[result_len - 1] == n2->array[result_len - 1])
			result_len--;

	diff = alloc_u4b_array(result_len);
	if (!diff)
		return (NULL);

	n1_is_bigger = cmp_u4barray(n1, n2);
	if (n1_is_bigger <= 0)
		diff->is_negative = 1;

	while ((n1_i < n1->len || n2_i < n2->len) && diff_i < diff->len)
	{
		if (n1_is_bigger > 0) /*then; n1 - n2*/
		{
			if (n2_i < n2->len)
				byt_diff += (int64_t)n1->array[n1_i] - n2->array[n2_i];
			else
				byt_diff += n1->array[n1_i];
		}
		else /*n2 - n1*/
		{
			if (n1_i < n1->len)
				byt_diff += (int64_t)n2->array[n2_i] - n1->array[n1_i];
			else
				byt_diff += n2->array[n2_i];
		}

		if (byt_diff < 0) /*borrow 1 from next.*/
		{
			byt_diff += MAX_VAL_u4b;
			diff->array[diff_i] = byt_diff % MAX_VAL_u4b;
			byt_diff = -1;
		}
		else
		{
			diff->array[diff_i] = byt_diff % MAX_VAL_u4b;
			byt_diff = 0;
		}

		++n1_i;
		++n2_i;
		++diff_i;
	}

	trim_u4b_array(diff);
	return (diff);
}

/**
 * subtract_negatives - subtraction of only signed numbers (negative numbers)
 * @n1: number to be subtracted
 * @n2: number to subtract
 *
 * Return: 1 if action taken (error or processed results), 0 if no action taken
 */
u4b_array *subtract_negatives(u4b_array *n1, u4b_array *n2)
{
	u4b_array *result = NULL;

	if (n1->is_negative && n2->is_negative)
	{
		/*-8 - -5 = -8 + 5 = 5-8*/
		n1->is_negative = 0;
		n2->is_negative = 0;
		result = infiX_subtraction(n2, n1);
		n1->is_negative = 1;
		n2->is_negative = 1;
	}
	else if (n1->is_negative)
	{
		/*-8 - 5 = -(8+5)*/
		n1->is_negative = 0;
		result = infiX_addition(n1, n2);
		n1->is_negative = 1;
		if (result)
			result->is_negative = 1;
	}
	else if (n2->is_negative)
	{
		/*8 - -5 = 8+5*/
		n2->is_negative = 0;
		result = infiX_addition(n1, n2);
		n2->is_negative = 1;
	}

	return (result);
}
