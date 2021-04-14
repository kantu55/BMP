#include  "bitmap.h"

main(int argc, char** argv) {
	int i, j;

	/* �摜�f�[�^���i�[����\���̕ϐ��ւ̃|�C���^  */
	img *tmp1, *tmp2;

	tmp1 = (img *)malloc(sizeof(img));
	tmp2 = (img *)malloc(sizeof(img));

	/* �R�}���h���C�������ŗ^����ꂽ������� filename �ɐݒ� */
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