#include  "bitmap.h"

main(int argc, char** argv) {
	int i, j;

	/* 画像データを格納する構造体変数へのポインタ  */
	img *tmp1, *tmp2;

	tmp1 = (img *)malloc(sizeof(img));
	tmp2 = (img *)malloc(sizeof(img));

	/* コマンドライン引数で与えられた文字列を filename に設定 */
	char *filename = argv[1];

	tmp1->height = 200;
	tmp1->width = 300;
	for (i = 0; i < tmp1->height; i++)
		for (j = 0; j < tmp1->width; j++) {
			tmp1->data[i][j].r = rand() % 256;
			tmp1->data[i][j].g = rand() % 256;
			tmp1->data[i][j].b = rand() % 256;
		}

	WriteBmp("noise.bmp", tmp1);

	WriteImg("test.img", tmp1);

	PrintBmpInfo("noise.bmp");

}