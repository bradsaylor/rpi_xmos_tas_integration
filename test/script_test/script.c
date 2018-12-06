#include <stdio.h>

int main(int arc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    char str[10];

    while(fscanf(fp, "%s", str) != EOF)
    {
	printf("%s\n", str);
    }

    return 0;
}
