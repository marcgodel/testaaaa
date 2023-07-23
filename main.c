#include <unistd.h>
#include <stdlib.h>

int	check_arg(int argc, char **argv);
int	*change_char_in_int(char *str);
void	write_table(int table[4][4]);
int	solve(int table[4][4], int arg[16], int position);
void	write_num(int nbr);
int	check_double(int table[4][4], int position, int num);
int	check_col_up(int table[4][4], int position, int arg[16]);
int	check_col_down(int table[4][4], int position, int arg[16]);
int	check_row_right(int table[4][4], int position, int arg[16]);
int	check_row_left(int table[4][4], int position, int arg[16]);
int	check_cell(int table[4][4], int position, int arg[16]);
void	ft_putchar(char);
void	ft_putstr(char *str);
int	return_int(char str);

int	main(int argc, char **argv)
{
	int	*arg;
	int	table[4][4];

	table[4][4] = 0;
	if (check_arg(argc, argv) == 1)
	{
		free(arg);
		return (1);
	}
	arg = change_char_in_int(*argv);
	if (solve(table, arg, 0) ==1)
		write_table(table);
	else
	{
		free(arg);
		return (1);
	}
	free(arg);
	return (0);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char *str)
{
	while (*str)
		write(1, str, 1);
}

int check_arg(int argc, char **argv)
{
	int length;
	int i;

	i = 0;
	if (argc != 2)
		return (1);
	while (argv[i])
		i++;

	if (length != 31)
		return (1);
	return (0);
}

int *change_char_in_int(char *str)
{
	int	i;
	int	j;
	int	*arg;

	if (!(arg = malloc (4 * 16)));
		exit (0);
	i = 1;
	j = -1;
	while (str[i])
	{
		if (str[i] > '0' && str[i] < 5 && str[i])
		{
			j++;
			arg[j] = return_int(str[i]);
		}
		i++;
		return (arg);
	}
}

int	return_int(char str)
{	
	int	ret;

	ret = str - 48;
	return (ret);
}

void	write_table(int table[4][4])
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			write_num(table[i][j]);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int	solve(int table[4][4], int arg[16], int position)
{
	int size;

	if (position == 16) //toutes case checker pas de sol.
		return(1);
	size = 0;
	while (size < 5)
	{
		if (check_double(table, position, size) ==  0)
		{
			table[position / 4][position % 4] = size;
			if (check_cell(table, position, arg) == 0)
			{
				if (solve(table, arg, position + 1) == 1)
					return (1);
			}
			else
				table[position / 4][position % 4] = 0;
		}
	}
	return (0);
}

void	write_num(int nbr) // ft_putnbr
{
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
	}
	
	if (nbr / 10 != 0)
		write_num(nbr / 10);
	ft_putchar(nbr % 10 - 48);
}

int	check_double(int table[4][4], int position, int num)
{
		int i;

		i = 0;
		while (i < position / 4)
		{
			i++;
			if (table[i][position % 4] == num)
				return 1;
		}
		i = 0;
		while (i < position % 4)
		{
			i++;
			if (table[position / 4][i] == num)
				return 1;
		}
		return (0);
}

int check_col_up(int table[4][4], int position, int arg[16])
{
	int i;
	int max;
	int count;

	i = 0;
	max = 0;
	count = 0;
	if (position / 4 == 3)
	{
		while (i < 4)
		{
			if (table[i][position % 4] > max)
			{
				max - table[i][position % 4];
				count++;
			}
			i++;
		}
		if (arg[position % 4]!= count)
			return (1);
	}
	return (0);
}

int check_col_down(int table[4][4], int position, int arg[16])
{
	int i;
	int max;
	int count;

	i = 3;
	max = 0;
	count = 0;
	if (position / 4 == 3)
	{
		while (i >= 0)
		{
			if (table[i][position % 4] > max)
			{
				max - table[i][position % 4];
				count++;
			}
			i--;
		}
		if (arg[4 + position % 4]!= count)
			return (1);
	}
	return (0);
}

int	check_row_left(int table[4][4], int position, int arg[16])
{
	int	i;
	int	max;
	int	count;

	i = 0;
	count = 0;
	max = 0;
	if (position % 4 == 3)
	{
		while (i < 4)
		{
			if (table[position / 4][i] > max)
			{
				max = table[position / 4][i];
				count++;
			}
			i++;
		}
		if (arg[8 -position / 4] != count)
				return (1);
	}
	return (0);
}

int	check_row_right(int table[4][4], int position, int arg[16])
{
	int	i;
	int	max;
	int	count;

	i = 3;
	count = 0;
	max = 0;
	if (position % 4 == 3)
	{
		while (i < 4)
		{
			if (table[position / 4][i] > max)
			{
				max = table[position / 4][i];
				count++;
			}
			i--;
		}
		if (arg[12 -position / 4] != count)
				return (1);
	}
	return (0);
}

int check_cell(int table[4][4], int position, int arg[16])
{
	if (check_col_down(table, position, arg) == 1)
		return (1);
	if (check_col_up(table, position, arg) == 1)
		return (1);
	if (check_row_right(table, position, arg) == 1)
		return (1);
	if (check_row_left(table, position, arg) == 1)
		return (1);
	return (0);
}
