#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static void	error_end(void)
{
	printf("Unexpected end of input\n");
	exit(1);
}

static void	error_token(char c)
{
	printf("Unexpected token '%c'\n", c);
	exit(1);
}

/* parse_factor が parse_expr を呼ぶため前方宣言が必要 */
static long	parse_expr(char *expr, int *pos);

static long	parse_factor(char *expr, int *pos)
{
	char	c;
	long	val;

	c = expr[*pos];
	if (c == '\0')
		error_end();
	if (c == '(')
	{
		(*pos)++;
		val = parse_expr(expr, pos);
		if (expr[*pos] == '\0')
			error_end();
		if (expr[*pos] != ')')
			error_token(expr[*pos]);
		(*pos)++;
		return (val);
	}
	if (isdigit((unsigned char)c) != 0)
	{
		(*pos)++;
		return (c - '0');
	}
	error_token(c);
	return (0);
}

static long	parse_term(char *expr, int *pos)
{
	long	val;

	val = parse_factor(expr, pos);
	while (expr[*pos] == '*')
	{
		(*pos)++;
		val *= parse_factor(expr, pos);
	}
	return (val);
}

static long	parse_expr(char *expr, int *pos)
{
	long	val;

	val = parse_term(expr, pos);
	while (expr[*pos] == '+')
	{
		(*pos)++;
		val += parse_term(expr, pos);
	}
	return (val);
}

int	main(int ac, char *av[])
{
	int		pos;
	long	result;

	if (ac != 2)
		return (1);
	pos = 0;
	result = parse_expr(av[1], &pos);
	if (av[1][pos] != '\0')
		error_token(av[1][pos]);
	printf("%ld\n", result);
	return (0);
}
