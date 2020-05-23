#include <stdio.h>
#include <string.h>
#include <cctype.h>

int main(void)
{
	char user_name[20];
	double f_pizza, f_other, e_books;

	printf("What is your name?\n");
	scanf_s("%19s", user_name, 20);
	user_name[0] = toupper(user_name[0]);
	printf("%s, that is a very nice name.", user_name);
	getchar();
	getchar();

	return 0;
}