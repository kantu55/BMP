#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<math.h>
#include"bitmap.h"

//filename§ŒBitmap•’•°•§•ÅEÚ∆…§ﬂπ˛§ﬂ°¢π‚§µ§»…˝°¢RGBæ Û§ÚimgπΩ¬§¬Œ§À∆˛§ÅEÅE
Image *Read_Bmp(char *filename)
{
	unsigned int i = 0;
	unsigned int j = 0;
	int real_width;					//•«°º•øæÂ§Œ1π‘ ¨§Œ•–•§•»øÅE
	unsigned int width, height;			//≤Ë¡ÅEŒ≤£§»Ωƒ§Œ•‘•Ø•ª•ÅEÅE
	unsigned int color;			//≤øbit§ŒBitmap•’•°•§•ÅE«§¢§ÅE´
	FILE *fp;
	unsigned char header_buf[HEADERSIZE];	//•ÿ•√•¿æ Û§ÚºË§ÅE˛§ÅE
	unsigned char *bmp_line_data;  //≤Ë¡ÅE«°º•ø1π‘ ¨
	Image *img;

	if ((fp = fopen(filename, "rb")) == NULL) {
		fprintf(stderr, "Error: %s could not read.", filename);
		return NULL;
	}

	fread(header_buf, sizeof(unsigned char), HEADERSIZE, fp); //•ÿ•√•¿…Ù ¨¡¥§∆§ÚºË§ÅE˛§ÅE
	//∫«ΩÈ§Œ2•–•§•»§¨BM(Bitmap•’•°•§•ÅEŒ∞ÅE§«§¢§ÅE´
	if (strncmp(header_buf, "BM", 2)) 
	{
		fprintf(stderr, "Error: %s is not Bitmap file.", filename);
		return NULL;
	}

	memcpy(&width, header_buf + 18, sizeof(img->width)); //≤Ë¡ÅEŒ∏´§øÃ‹æÂ§Œ…˝§ÚºË∆¿
	memcpy(&height, header_buf + 22, sizeof(img->height)); //≤Ë¡ÅEŒπ‚§µ§ÚºË∆¿
	memcpy(&color, header_buf + 28, sizeof(unsigned int)); //≤øbit§ŒBitmap§«§¢§ÅE´§ÚºË∆¿

	printf("%d\n", color);

	if (color != 8 && color != 4) {
		fprintf(stderr, "Error: %s is not 24bit color image", filename);
		return NULL;
	}

	real_width = width * 3 + width % 4;


	//≤Ë¡ÅEŒ1π‘ ¨§ŒRGBæ Û§ÚºË§√§∆§Ø§ÅEø§·§Œ•–•√•’•°§Ú∆∞≈™§ÀºË∆¿
	if ((bmp_line_data = (unsigned char *)malloc(sizeof(unsigned char)*real_width)) == NULL) {
		fprintf(stderr, "Error: Allocation error.\n");
		return NULL;
	}

	//RGBæ Û§ÚºË§ÅE˛§‡§ø§·§Œ•–•√•’•°§Ú∆∞≈™§ÀºË∆¿
	if ((img = Create_Image(width, height)) == NULL) {
		free(bmp_line_data);
		fclose(fp);
		return NULL;
	}

	//Bitmap•’•°•§•ÅEŒRGBæ Û§œ∫∏≤º§´§È±¶§ÿ°¢≤º§´§ÈæÂ§À ¬§Û§«§§§ÅE	
	for (i = 0; i < height; i++) {
		fread(bmp_line_data, 1, real_width, fp);
		for (j = 0; j < width; j++) {
			img->data[(height - i - 1)*width + j].b = bmp_line_data[j * 3];
			img->data[(height - i - 1)*width + j].g = bmp_line_data[j * 3 + 1];
			img->data[(height - i - 1)*width + j].r = bmp_line_data[j * 3 + 2];
		}
	}

free(bmp_line_data);

fclose(fp);

return img;
}

int Write_Bmp(char *filename, Image *img)
{
	int i, j;
	FILE *fp;
	int real_width;
	unsigned char *bmp_line_data; 
	unsigned char header_buf[HEADERSIZE]; //•ÿ•√•¿§Ú≥ «º§π§ÅE
	unsigned int file_size;
	unsigned int offset_to_data;
	unsigned long info_header_size;
	unsigned int planes;
	unsigned int color;
	unsigned long compress;
	unsigned long data_size;
	long xppm;
	long yppm;

	/*if ((fp = fopen(filename, "wb")) == NULL) {
		fprintf(stderr, "Error: %s could not open.", filename);
	}*/

	fp = fopen(filename, "wb");

	real_width = img->width * 3 + img->width % 4;

	file_size = img->height * real_width + HEADERSIZE;
	offset_to_data = HEADERSIZE;
	info_header_size = INFOHEADERSIZE;
	planes = 1;
	color = 16;
	compress = 0;
	data_size = img->height * real_width;
	xppm = 1;
	yppm = 1;

	header_buf[0] = 'B';
	header_buf[1] = 'M';
	memcpy(header_buf + 2, &file_size, sizeof(file_size));
	header_buf[6] = 0;
	header_buf[7] = 0;
	header_buf[8] = 0;
	header_buf[9] = 0;
	memcpy(header_buf + 10, &offset_to_data, sizeof(file_size));
	header_buf[11] = 0;
	header_buf[12] = 0;
	header_buf[13] = 0;

	memcpy(header_buf + 14, &info_header_size, sizeof(info_header_size));
	header_buf[15] = 0;
	header_buf[16] = 0;
	header_buf[17] = 0;
	memcpy(header_buf + 18, &img->width, sizeof(img->width));
	memcpy(header_buf + 22, &img->height, sizeof(img->height));
	memcpy(header_buf + 26, &planes, sizeof(planes));
	memcpy(header_buf + 28, &color, sizeof(color));
	memcpy(header_buf + 30, &compress, sizeof(compress));
	memcpy(header_buf + 34, &data_size, sizeof(data_size));
	memcpy(header_buf + 38, &xppm, sizeof(xppm));
	memcpy(header_buf + 42, &yppm, sizeof(yppm));
	header_buf[46] = 0;
	header_buf[47] = 0;
	header_buf[48] = 0;
	header_buf[49] = 0;
	header_buf[50] = 0;
	header_buf[51] = 0;
	header_buf[52] = 0;
	header_buf[53] = 0;

	//•ÿ•√•¿§ŒΩÒ§≠π˛§ﬂ
	fwrite(header_buf, sizeof(unsigned char), HEADERSIZE, fp);

	if ((bmp_line_data = (unsigned char *)malloc(sizeof(unsigned char)*real_width)) == NULL) {
		fprintf(stderr, "Error: Allocation error.\n");
		fclose(fp);
		return 1;
	}

	//RGBæ Û§ŒΩÒ§≠π˛§ﬂ
	for (i = 0; i < img->height; i++) {
		for (j = 0; j < img->width; j++) {
			bmp_line_data[j * 3] = img->data[(img->height - i - 1)*img->width + j].b;
			bmp_line_data[j * 3 + 1] = img->data[(img->height - i - 1)*img->width + j].g;
			bmp_line_data[j * 3 + 2] = img->data[(img->height - i - 1)*img->width + j].r;
		}
		//RGBæ Û§ÅE•–•§•»§Œ«‹øÙ§ÀπÁ§ÅEª§∆§§§ÅE		
		for (j = img->width * 3; j < real_width; j++) {
			bmp_line_data[j] = 0;
		}
		fwrite(bmp_line_data, sizeof(unsigned char), real_width, fp);
	}

free(bmp_line_data);

fclose(fp);

return 0;
}

Image *Create_Image(int width, int height)
{
	Image *img;

	if ((img = (Image *)malloc(sizeof(Image))) == NULL) {
		fprintf(stderr, "Allocation error\n");
		return NULL;
	}

	if ((img->data = (Rgb*)malloc(sizeof(Rgb)*width*height)) == NULL) {
		fprintf(stderr, "Allocation error\n");
		free(img);
		return NULL;
	}

	img->width = width;
	img->height = height;

	return img;
}

//∆∞≈™§ÀºË∆¿§∑§øRGBæ Û§Œ≥´ ÅE
void Free_Image(Image *img)
{
	free(img->data);
	free(img);
}

