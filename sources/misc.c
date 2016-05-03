#include "polygons.h"

char *machin_sup_simple(char *num, char *str, int i)
{
    if (num[i] == '0')
        str = ft_strjoin(str, "gon");
    else if (num[i] == '1')
        str = ft_strjoin(str, "henagon");
    else if (num[i] == '2')
        str = ft_strjoin(str, "digon");
    else if (num[i] == '3')
        str = ft_strjoin(str, "trigon");
    else if (num[i] == '4')
        str = ft_strjoin(str, "tretragon");
    else if (num[i] == '5')
        str = ft_strjoin(str, "pentagon");
    else if (num[i] == '6')
        str = ft_strjoin(str, "hexagon");
    else if (num[i] == '7')
        str = ft_strjoin(str, "heptagon");
    else if (num[i] == '8')
        str = ft_strjoin(str, "octagon");
    else if (num[i] == '9')
        str = ft_strjoin(str, "enneagon");
    return (str);
}

char *machin_sup_double(char *num, char *str, int i)
{
    if (num[i] == '1')
        str = ft_strjoin(str, "deca");
    else if (num[i] == '2')
        str = ft_strjoin(str, "icosi");
    else if (num[i] == '3')
        str = ft_strjoin(str, "triaconta");
    else if (num[i] == '4')
        str = ft_strjoin(str, "tetraconta");
    else if (num[i] == '5')
        str = ft_strjoin(str, "pentaconta");
    else if (num[i] == '6')
        str = ft_strjoin(str, "hexaconta");
    else if (num[i] == '7')
        str = ft_strjoin(str, "heptaconta");
    else if (num[i] == '8')
        str = ft_strjoin(str, "octaconta");
    else if (num[i] == '9')
        str = ft_strjoin(str, "enneaconta");
    if (num[i + 1] != '0')
        str = ft_strjoin(str, "kai");
    return (machin_sup_simple(num, str, ++i));
}

char *machin_sup_triple(char *num, char *str, int i)
{
    if (num[i] == '1')
        str = ft_strjoin(str, "hecta");
    else if (num[i] == '2')
        str = ft_strjoin(str, "dihecta");
    else if (num[i] == '3')
        str = ft_strjoin(str, "trihecta");
    else if (num[i] == '4')
        str = ft_strjoin(str, "tetrahecta");
    else if (num[i] == '5')
        str = ft_strjoin(str, "pentahecta");
    else if (num[i] == '6')
        str = ft_strjoin(str, "hexahecta");
    else if (num[i] == '7')
        str = ft_strjoin(str, "heptahecta");
    else if (num[i] == '8')
        str = ft_strjoin(str, "octahecta");
    else if (num[i] == '9')
        str = ft_strjoin(str, "enneahecta");
    return (machin_sup_double(num, str, ++i));
}

char    *machin_basic(int num, char *str)
{
    str = (num == 11) ? ft_strjoin(str, "hendecagon") : str;
    str = (num == 12) ? ft_strjoin(str, "dodecagon") : str;
    str = (num == 13) ? ft_strjoin(str, "Tridecagon") : str;
    str = (num == 14) ? ft_strjoin(str, "tetradecagon") : str;
    str = (num == 15) ? ft_strjoin(str, "pentadecagon") : str;
    str = (num == 16) ? ft_strjoin(str, "hexadecagon") : str;
    str = (num == 17) ? ft_strjoin(str, "heptadecagon") : str;
    str = (num == 18) ? ft_strjoin(str, "octadecagon") : str;
    str = (num == 19) ? ft_strjoin(str, "enneadecagon") : str;
    str = (num == 20) ? ft_strjoin(str, "icosagon") : str;
    str = (num == 100) ? ft_strjoin(str, "hectogon") : str;
    return (str);
}

char    *dispatch_num(int num)
{
    char *str;

    str = (char *)malloc(sizeof(char) * 1);
    if ((num > 10 && num <= 20) || num == 100)
        return (machin_basic(num, str));
    else if (num > 99)
        return (machin_sup_triple(ft_itoa(num), str, 0));
    else if (num == 10 || num > 20)
        return (machin_sup_double(ft_itoa(num), str, 0));
    else if (num > 0)
        return (machin_sup_simple(ft_itoa(num), str, 0));
    return (str);
}
