# include "gbc.h"

int main(void)
{
	// static t_gbc	collector;
	// printf("id: %d\n", collector.id);
	// printf("addr: %p\n", collector.addr);
	// printf("next: %p\n", (void *)collector.next);

	int		**test;
	t_gbc	*test2;

	test = gb_malloc(sizeof(int *) * 10);
	test[0] = gb_malloc(sizeof(int) * 1);
	test[0][0] = 1;
	test[1] = gb_malloc(sizeof(int) * 1);
	test[1][0] = 2;
	test[2] = gb_malloc(sizeof(int) * 1);
	test[2][0] = 3;
	printf("test[0]: %d\n", test[0][0]);
	printf("test[1]: %d\n", test[1][0]);
	printf("test[2]: %d\n", test[2][0]);
	gb_free(test[1]);

	test2 = gb_malloc(sizeof(t_gbc) * 1);
	test2->addr = gb_malloc(sizeof(int) * 1);
	*(int *)test2->addr = 4;
	printf("test2->addr: %d\n", *(int *)test2->addr);

	gb_clear();
}
