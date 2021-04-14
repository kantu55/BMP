#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HEADERSIZE   54               /* �w�b�_�̃T�C�Y 54 = 14 + 40         */
#define PALLETSIZE 1024               /* �p���b�g�̃T�C�Y                    */
#define MAXWIDTH   4096               /* ��(pixel)�̏��                     */
#define MAXHEIGHT  4096               /* ����(pixel) �̏��                  */

/* x �� y �̌����̂��߂� �}�N���֐� */
#define SWAP(x,y) {typeof(x) temp; temp=x; x=y; y=temp;}

unsigned char Bmp_headbuf[HEADERSIZE];/* �w�b�_���i�[���邽�߂̕ϐ�          */
unsigned char Bmp_Pallet[PALLETSIZE]; /* �J���[�p���b�g���i�[                */

char Bmp_type[2];                     /* �t�@�C���^�C�v "BM"                 */
unsigned long Bmp_size;               /* bmp�t�@�C���̃T�C�Y (�o�C�g)        */
unsigned int Bmp_info_header_size; /* ���w�b�_�̃T�C�Y = 40             */
unsigned int Bmp_header_size;      /* �w�b�_�T�C�Y = 54*/
long Bmp_height;                      /* ���� (�s�N�Z��)                     */
long Bmp_width;                       /* ��   (�s�N�Z��)                     */
unsigned short Bmp_planes;          /* �v���[���� ��� 1                   */
unsigned short Bmp_color;          /* �F (�r�b�g)     24                  */
long Bmp_comp;                        /* ���k���@         0                  */
long Bmp_image_size;                  /* �摜�����̃t�@�C���T�C�Y (�o�C�g)   */
long Bmp_xppm;                        /* �����𑜓x (ppm)                    */
long Bmp_yppm;                        /* �����𑜓x (ppm)                    */

typedef struct {                      /* 1�s�N�Z��������̐ԗΐ̊e�P�x     */
	unsigned char r;
	unsigned char g;
	unsigned char b;
} color;

typedef struct {
	long height;
	long width;
	color data[MAXHEIGHT][MAXWIDTH];
} img;

void ReadBmp(char *filename, img *imgp);
void WriteBmp(char *filename, img *tp);
void PrintBmpInfo(char *filename);
void HMirror(img *sp, img *tp);
void VMirror(img *sp, img *tp);
void Rotate90(int a, img *sp, img *tp);
void Shrink(int a, img *sp, img *tp);
void Mosaic(int a, img *sp, img *tp);
void Gray(img *sp, img *tp);
void Diminish(img *sp, img *tp, unsigned char x);
void WriteImg(char* filename, img *tp);