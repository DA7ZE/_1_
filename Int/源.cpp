#include "head.h"

#include "Int.h"

void test()
{
	Int t(1234567);
	t.div_(2);
	t.print_();
	cout << endl;

	/////////////////////////////
	int a = 123456;
	int b = 987654;
	int c = a * b;

	cout << "int c = " << c << endl;


	Int z;
	Int::mul_(z, a, b);

	cout << "Int z = ";
	z.print_();
	cout << endl << endl;
	//////////////////////////////////////////////////////////

	Int::mul_(z, 11223344, 4002222);

	cout << "Int z = ";
	z.print_();
	cout << endl;

	Int::mul_(z, 11223344, 2001111);
	z.add_(z);

	cout << "Int z = ";
	z.print_();
	cout << endl << endl;

	//////////////////////////////////////////////////////////
	for (int x = 91234; ; x++) {
		Int::mul_(z, x, x);

		cout << x << "^2 = ";
		z.print_();
		cout << endl;
	}
}//test()

int main()
{
	test();

}//main()