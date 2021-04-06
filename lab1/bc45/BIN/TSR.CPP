#include <dos.h>
void test();
int main(void)
{
	keep(0, (_SS + (_SP/16) - _psp));
	test();
	return 0;
}
void test()
{
	char aa[60000];

	int a;
	a=1;
	a++;
	a--;
}
