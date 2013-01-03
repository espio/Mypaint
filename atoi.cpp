int	id_atoi(char* str)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + str[i] - '0';
		i = i + 1;
	}
	return number;
}
