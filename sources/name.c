/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 18:08:32 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/10 14:28:56 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "polygons.h"

char	*machin_sup_simple(char *num, char *str, int i)
{
	if (num[i] == '0')
		str = ft_strjoin2(str, "gon", 0);
	else if (num[i] == '1')
		str = ft_strjoin2(str, "henagon", 0);
	else if (num[i] == '2')
		str = ft_strjoin2(str, "digon", 0);
	else if (num[i] == '3')
		str = ft_strjoin2(str, "trigon", 0);
	else if (num[i] == '4')
		str = ft_strjoin2(str, "tretragon", 0);
	else if (num[i] == '5')
		str = ft_strjoin2(str, "pentagon", 0);
	else if (num[i] == '6')
		str = ft_strjoin2(str, "hexagon", 0);
	else if (num[i] == '7')
		str = ft_strjoin2(str, "heptagon", 0);
	else if (num[i] == '8')
		str = ft_strjoin2(str, "octagon", 0);
	else if (num[i] == '9')
		str = ft_strjoin2(str, "enneagon", 0);
	return (str);
}

char	*machin_sup_double(char *num, char *str, int i)
{
	if (num[i] == '1')
		str = ft_strjoin2(str, "deca", 0);
	else if (num[i] == '2')
		str = ft_strjoin2(str, "icosi", 0);
	else if (num[i] == '3')
		str = ft_strjoin2(str, "triaconta", 0);
	else if (num[i] == '4')
		str = ft_strjoin2(str, "tetraconta", 0);
	else if (num[i] == '5')
		str = ft_strjoin2(str, "pentaconta", 0);
	else if (num[i] == '6')
		str = ft_strjoin2(str, "hexaconta", 0);
	else if (num[i] == '7')
		str = ft_strjoin2(str, "heptaconta", 0);
	else if (num[i] == '8')
		str = ft_strjoin2(str, "octaconta", 0);
	else if (num[i] == '9')
		str = ft_strjoin2(str, "enneaconta", 0);
	if (num[i + 1] != '0')
		str = ft_strjoin2(str, "kai", 0);
	return (machin_sup_simple(num, str, ++i));
}

char	*machin_sup_triple(char *num, char *str, int i)
{
	if (num[i] == '1')
		str = ft_strjoin2(str, "hecta", 0);
	else if (num[i] == '2')
		str = ft_strjoin2(str, "dihecta", 0);
	else if (num[i] == '3')
		str = ft_strjoin2(str, "trihecta", 0);
	else if (num[i] == '4')
		str = ft_strjoin2(str, "tetrahecta", 0);
	else if (num[i] == '5')
		str = ft_strjoin2(str, "pentahecta", 0);
	else if (num[i] == '6')
		str = ft_strjoin2(str, "hexahecta", 0);
	else if (num[i] == '7')
		str = ft_strjoin2(str, "heptahecta", 0);
	else if (num[i] == '8')
		str = ft_strjoin2(str, "octahecta", 0);
	else if (num[i] == '9')
		str = ft_strjoin2(str, "enneahecta", 0);
	return (machin_sup_double(num, str, ++i));
}

char	*machin_basic(int num, char *str)
{
	str = (num == 11) ? ft_strjoin2(str, "hendecagon", 0) : str;
	str = (num == 12) ? ft_strjoin2(str, "dodecagon", 0) : str;
	str = (num == 13) ? ft_strjoin2(str, "Tridecagon", 0) : str;
	str = (num == 14) ? ft_strjoin2(str, "tetradecagon", 0) : str;
	str = (num == 15) ? ft_strjoin2(str, "pentadecagon", 0) : str;
	str = (num == 16) ? ft_strjoin2(str, "hexadecagon", 0) : str;
	str = (num == 17) ? ft_strjoin2(str, "heptadecagon", 0) : str;
	str = (num == 18) ? ft_strjoin2(str, "octadecagon", 0) : str;
	str = (num == 19) ? ft_strjoin2(str, "enneadecagon", 0) : str;
	str = (num == 20) ? ft_strjoin2(str, "icosagon", 0) : str;
	str = (num == 100) ? ft_strjoin2(str, "hectogon", 0) : str;
	return (str);
}

char	*dispatch_num(int num)
{
	char *str;
	char *number;

	number = ft_itoa(num);
	str = (char *)malloc(sizeof(char) * 1);
	str[0] = '\0';
	if ((num > 10 && num <= 20) || num == 100)
		str = machin_basic(num, str);
	else if (num > 99)
		str = machin_sup_triple(number, str, 0);
	else if (num == 10 || num > 20)
		str = machin_sup_double(number, str, 0);
	else if (num > 0)
	    str = machin_sup_simple(number, str, 0);
    free(number);
	if (str[0] >= 97 && str[0] <= 122)
		str[0] -= 32;
	return (str);
}
