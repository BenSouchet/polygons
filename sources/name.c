/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 18:08:32 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/11 12:11:17 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "polygons.h"

static char	*one_numeral(char *num, char *str, int i)
{
	if (num[i] == '0')
		str = ft_strjoin(str, "gon", 0);
	else if (num[i] == '1')
		str = ft_strjoin(str, "henagon", 0);
	else if (num[i] == '2')
		str = ft_strjoin(str, "digon", 0);
	else if (num[i] == '3')
		str = ft_strjoin(str, "trigon", 0);
	else if (num[i] == '4')
		str = ft_strjoin(str, "tretragon", 0);
	else if (num[i] == '5')
		str = ft_strjoin(str, "pentagon", 0);
	else if (num[i] == '6')
		str = ft_strjoin(str, "hexagon", 0);
	else if (num[i] == '7')
		str = ft_strjoin(str, "heptagon", 0);
	else if (num[i] == '8')
		str = ft_strjoin(str, "octagon", 0);
	else if (num[i] == '9')
		str = ft_strjoin(str, "enneagon", 0);
	return (str);
}

static char	*two_numerals(char *num, char *str, int i)
{
	if (num[i] == '1')
		str = ft_strjoin(str, "deca", 0);
	else if (num[i] == '2')
		str = ft_strjoin(str, "icosi", 0);
	else if (num[i] == '3')
		str = ft_strjoin(str, "triaconta", 0);
	else if (num[i] == '4')
		str = ft_strjoin(str, "tetraconta", 0);
	else if (num[i] == '5')
		str = ft_strjoin(str, "pentaconta", 0);
	else if (num[i] == '6')
		str = ft_strjoin(str, "hexaconta", 0);
	else if (num[i] == '7')
		str = ft_strjoin(str, "heptaconta", 0);
	else if (num[i] == '8')
		str = ft_strjoin(str, "octaconta", 0);
	else if (num[i] == '9')
		str = ft_strjoin(str, "enneaconta", 0);
	if (num[i + 1] != '0')
		str = ft_strjoin(str, "kai", 0);
	return (one_numeral(num, str, ++i));
}

static char	*three_numerals(char *num, char *str, int i)
{
	if (num[i] == '1')
		str = ft_strjoin(str, "hecta", 0);
	else if (num[i] == '2')
		str = ft_strjoin(str, "dihecta", 0);
	else if (num[i] == '3')
		str = ft_strjoin(str, "trihecta", 0);
	else if (num[i] == '4')
		str = ft_strjoin(str, "tetrahecta", 0);
	else if (num[i] == '5')
		str = ft_strjoin(str, "pentahecta", 0);
	else if (num[i] == '6')
		str = ft_strjoin(str, "hexahecta", 0);
	else if (num[i] == '7')
		str = ft_strjoin(str, "heptahecta", 0);
	else if (num[i] == '8')
		str = ft_strjoin(str, "octahecta", 0);
	else if (num[i] == '9')
		str = ft_strjoin(str, "enneahecta", 0);
	return (two_numerals(num, str, ++i));
}

static char	*special_numerals(int num, char *str)
{
	str = (num == 11) ? ft_strjoin(str, "hendecagon", 0) : str;
	str = (num == 12) ? ft_strjoin(str, "dodecagon", 0) : str;
	str = (num == 13) ? ft_strjoin(str, "Tridecagon", 0) : str;
	str = (num == 14) ? ft_strjoin(str, "tetradecagon", 0) : str;
	str = (num == 15) ? ft_strjoin(str, "pentadecagon", 0) : str;
	str = (num == 16) ? ft_strjoin(str, "hexadecagon", 0) : str;
	str = (num == 17) ? ft_strjoin(str, "heptadecagon", 0) : str;
	str = (num == 18) ? ft_strjoin(str, "octadecagon", 0) : str;
	str = (num == 19) ? ft_strjoin(str, "enneadecagon", 0) : str;
	str = (num == 20) ? ft_strjoin(str, "icosagon", 0) : str;
	str = (num == 100) ? ft_strjoin(str, "hectogon", 0) : str;
	return (str);
}

char		*dispatch_num(int num)
{
	char *str;
	char *number;

	number = ft_itoa(num);
	str = (char *)malloc(sizeof(char) * 1);
	str[0] = '\0';
	if ((num > 10 && num <= 20) || num == 100)
		str = special_numerals(num, str);
	else if (num > 99)
		str = three_numerals(number, str, 0);
	else if (num == 10 || num > 20)
		str = two_numerals(number, str, 0);
	else if (num > 0)
		str = one_numeral(number, str, 0);
	free(number);
	if (str[0] >= 97 && str[0] <= 122)
		str[0] -= 32;
	return (str);
}
