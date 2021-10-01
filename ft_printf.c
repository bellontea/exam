#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

int width;
int prec;
int res;

int ft_strlen(char *str)
{
	int count = 0;
	while (str && *str)
	{
		count++;
		str++;
	}
	return (count);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char *s, int len)
{
	int i = 0;
	while (i < len)
	{
		ft_putchar(s[i]);
		res++;
		i++;
	}
}

void print_s(char *s)
{
	int len = ft_strlen(s);
	if (!s && prec != 0)
	{
		len = 6;
		if (prec != -1 && prec < len)
			len = prec;
		if (width > len)
		{
			width = width - len;
			while (width)
			{
				ft_putchar(' ');
				res++;
				width--;
			}
		}
		ft_putstr("(null)", len);
		return ;
	}
	if (prec >= 0 && prec < len)
		len = prec;
	if (width > len)
	{
		width = width - len;
		while (width)
		{
			ft_putchar(' ');
			res++;
			width--;
		}
	}
	ft_putstr(s, len);
}

int size_d(unsigned int d)
{
	int size = 0;
	if (d == 0)
		return (1);
	while (d)
	{
		size++;
		d = d / 10;
	}
	return (size);
}

int size_d_base(int d)
{
	int size = 0;
	if (d == 0)
		return (1);
	while (d)
	{
		size++;
		d = d / 16;
	}
	return (size);
}

char *itoa(int d)
{
	int len = size_d(d);
	int minus = 1;
	if (d < 0)
	{
		minus = -1;
		len++;
	}
	char *num = malloc(len + 1);
	num[len] = '\0';
	len--;
	if (d == 0)
	{
		num[0] = '0';
		return (num);
	}
	while (d != 0 && len >= 0)
	{
		num[len] = ((d % 10) * minus) + '0';
		d = d / 10;
		len--;
	}
	if (minus == -1)
		num[0] = '-';
	return (num);
}

void print_d(int d)
{
	if (prec == 0 && d == 0)
	{
		while (width)
		{
			ft_putchar(' ');
			res++;
			width--;
		}
		return ;
	}
	char *num = itoa(d);
	int len = ft_strlen(num);
	if (prec > 0 && prec > len)
		prec = prec - len;
	else
		prec = 0;
	if (width > (len + prec))
	{
		width = width - len - prec;
		while (width)
		{
			ft_putchar(' ');
			res++;
			width--;
		}
	}
	if (prec)
		while (prec)
		{
			ft_putchar('0');
			res++;
			prec--;
		}
	ft_putstr(num, len);
	free(num);
}

char *itoa_base(unsigned int d)
{
	int len = size_d_base(d);
	char *base = "0123456789abcdef";
	char *num = malloc(len + 1);
	num[len] = '\0';
	len--;
	if (d == 0)
	{
		num[0] = '0';
		return (num);
	}
	while (d != 0 && len >= 0)
	{
		num[len] = base[d % 16];
		d = d / 16;
		len--;
	}
	return (num);
}

void print_x(unsigned int x)
{
	if (prec == 0 && x == 0)
	{
		while (width)
		{
			ft_putchar(' ');
			res++;
			width--;
		}
		return ;
	}
	char *num = itoa_base(x);
	int len = ft_strlen(num);
	if (prec > 0 && prec > len)
		prec = prec - len;
	else
		prec = 0;
	if (width > (len + prec))
	{
		width = width - len - prec;
		while (width)
		{
			ft_putchar(' ');
			res++;
			width--;
		}
	}
	if (prec)
		while (prec)
		{
			ft_putchar('0');
			res++;
			prec--;
		}
	ft_putstr(num, len);
	free(num);
}

void check_format(const char *format, int *i, va_list arg)
{
	if (format + *i && format[*i])
	{
		while (format + *i && (format[*i] >= '0' && format[*i] <= '9'))
		{
			width = width * 10 + (format[*i] - '0');
			(*i)++;
		}
		if (format + *i && format[*i] == '.')
		{
			(*i)++;
			prec = 0;
			while (format + *i && (format[*i] >= '0' && format[*i] <= '9'))
			{
				prec = prec * 10 + (format[*i] - '0');
				(*i)++;
			}
		}
		if (format[*i] == 's')
			print_s(va_arg(arg, char *));
		else if (format[*i] == 'd')
			print_d(va_arg(arg, int));
		else if (format[*i] == 'x')
			print_x(va_arg(arg, unsigned int));
		(*i)++;
	}
}

int ft_printf(const char *format, ... )
{
	va_list arg;
	int i = 0;
	va_start(arg, format);
	res = 0;

	while (format + i && format[i])
	{
		width = 0;
		prec = -1;
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			check_format(format, &i, arg);
			continue ;
		}
		ft_putchar(format[i]);
		res++;
		i++;
	}
	return (res);
}