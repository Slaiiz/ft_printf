#include <stdarg.h>
#include <stdio.h>
#include "libft.h"

void 	test(const char *s, ...)
{
	va_list	argp;

	va_start(argp, s);
	printf(s, argp);
	va_end(argp);
	va_start(argp, s);
	ft_printf(s, argp);
	va_end(argp);
	ft_putstr("\n");
}

int		main(void)
{
	test("---[{red;bu}%d{eoc;}]---[{green}%s{eoc}]---\n", 42, "Ecole 42");
	test("%#04x %.8x %#.8x\n", 42, 98, 3789);
	test("{green;b}%-#04x{eoc} {yellow}%.8x{eoc}\n", 123, 255);
	test("%s\n", "Øˆ¨ÁÓÔÏÎÓÒ\n");
	test("%%\n");
	test("%.1hhp\n", "40123");
	test("%.5s\n", "");
	test(">%6d<\n", 64);
	test(">%-6d<\n", 64);
	test(">%06d<\n", 64);
	test(">%0-6d<\n", 64);
	test("{red;bux}Red{;} {green}Green {blue;bx}Blue{;} {;x}Blue2{eoc;}\n");
	test("{red}{;b}Bold{;} {;u}Underlined{;} {;i}Italic{;} {;x}Blink{eoc;}\n");
	test("%0#12.8x\n", 65535);
	test("{cyan}%#08x{eoc}\n", 42);
	test("{cyan}%#8x{eoc}\n", 42);
	test("{cyan}%#-08x{eoc}\n", 42);
	test("{cyan}%#-8x{eoc}\n", 42);
	test("%c\n", 42);
	test("%d\n", 63);
	test("%d\n", -63);
	test("%d\n", -62);
	test("%hhd\n", 128);
	test("%hhd\n", 128);
	test("%s%s%s%s%s\n", "this", "is", "a", "multi", "string");
	test("%x\n", -42);
	test("%10x\n", 42);
	test("%hhp\n", 12);
	test("%++ d\n", -12);
	test("%05d\n", -42);
	test("hai%# 10.2o\n", 42);
	test("%5.2s is a string\n", "this");
	test("\n%d\n", "@moulitest: %s", NULL);
	test("%d-%d\n", 42, 43);
	test("%d\n", "\n");
	test("{cyan}%#.x\n", 0);
	test("% d\n", -42);
	test("%03.2d\n", 0);
	test("@moulitest: %5.x, %5.0x", 0, 0);
	test(">>%x\n", 0);
	test(">>%x\n", 1);
	return (0);
}
