#include "libft.h"

int	main(void)
{
	ft_printf("---[{red;bu}%d{eoc;}]---[{green}%s{eoc}]---\n", 42, "Ecole 42");
	ft_printf("%#04x %.8x %#.8x\n", 42, 98, 3789);
	ft_printf("{green;b}%-#04x{eoc} {yellow}%.8x{eoc}\n", 123, 255);
	ft_printf("%s\n", "Øˆ¨ÁÓÔÏÎÓÒ\n");
	ft_printf("%%\n");
	ft_printf("%.1hhp\n", "40123");
	ft_printf("%.5s\n", "");
	ft_printf(">%6d<\n", 64);
	ft_printf(">%-6d<\n", 64);
	ft_printf(">%06d<\n", 64);
	ft_printf(">%0-6d<\n", 64);
	ft_printf("{red;bux}Red{;} {green}Green {blue;bx}Blue{;} {;x}Blue2{eoc;}\n");
	ft_printf("{red}{;b}Bold{;} {;u}Underlined{;} {;i}Italic{;} {;x}Blink{eoc;}\n");
	ft_printf("%0#12.8x\n", 65535);
	ft_printf("{cyan}%#08x{eoc}\n", 42);
	ft_printf("{cyan}%#8x{eoc}\n", 42);
	ft_printf("{cyan}%#-08x{eoc}\n", 42);
	ft_printf("{cyan}%#-8x{eoc}\n", 42);
	ft_printf("%c\n", 42);
	ft_printf("%d\n", 63);
	ft_printf("%d\n", -63);
	ft_printf("%d\n", -62);
	ft_printf("%hhd\n", 128);
	ft_printf("%hhd\n", 128);
	ft_printf("%s%s%s%s%s\n", "this", "is", "a", "multi", "string");
	ft_printf("%x\n", -42);
	ft_printf("%10x\n", 42);
	ft_printf("%hhp\n", 12);
	ft_printf("%++ d\n", -12);
	ft_printf("%05d\n", -42);
	ft_printf("hai%# 10.2o\n", 42);
	ft_printf("%5.2s is a string\n", "this");
	ft_printf("\n%d\n", "@moulitest: %s", NULL);
	ft_printf("%d-%d\n", 42, 43);
	ft_printf("%d\n", "\n");
	ft_printf("{cyan}%#.x\n", 0);
	ft_printf("% d\n", -42);
	ft_printf("%03.2d\n", 0);
	ft_printf("@moulitest: %5.x, %5.0x", 0, 0);
	ft_printf(">>%x\n", 0);
	ft_printf(">>%x\n", 1);
	return (0);
}
