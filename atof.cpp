double	id_atof(const char* str)
{
	double	ret;
	int	signe;

	ret = 0;
	signe = 1;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			signe = signe * -1;
			++str;
		}
	}
	while ((*str >= '0' && *str <='9') || *str == ',' || *str == '.')
	{
		if (*str == ',' || *str == '.')
			ret = '.';
		else
			ret = ret * 10 + *str - '0';
		++str;
	}
	return (signe * ret);
}
