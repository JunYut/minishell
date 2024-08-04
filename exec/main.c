# include "append.h"
# include "libft.h"

int main()
{
	char *str1 = "Hello, ";
	char *str2 = "world!";
	char *str3 = ft_strjoin(str1, str2);
	printf("%s\n", str3);
	free(str3);
	return 0;
}
