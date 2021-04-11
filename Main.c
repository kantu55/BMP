#define _CRT_SECURE_NO_WARNINGS


#include"bitmap.h"
#include<stdlib.h>
#include<stdio.h>
#include <string.h>

void pop(char *s1, char *s2)
{
	char *p = s1;
	p = strstr(s1, s2);
	if (p != NULL)
	{
		strcpy(p, p + strlen(s2));
		pop(p + 1, s2);
	}
}

int main(int argc, char *argv[])
{
	char input[] = "input_image.bmp";
	int len = strlen(input);

	Image *colorimg;

	if ((colorimg = Read_Bmp(input)) == NULL) {
		exit(1);
	}

	pop(input, ".bmp");

	strcat(input, ".jpg");

	if (Write_Bmp(input, colorimg))
	{
		exit(1);
	}

	Free_Image(colorimg);

	return 0;
}
