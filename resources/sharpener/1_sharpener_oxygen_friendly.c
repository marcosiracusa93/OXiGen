#include <stdio.h>
#include <stdlib.h>
#include "../MaxJFunctions.h"

#define WIDTH 360
#define HEIGHT 480
#define SIZE WIDTH*HEIGHT

#define TOLERANCE 1

void sharpen(
	unsigned char r_in[SIZE], unsigned char g_in[SIZE], unsigned char b_in[SIZE], 
	unsigned char r_out[SIZE], unsigned char g_out[SIZE], unsigned char b_out[SIZE]);

void read_bmp(char* filename, unsigned char *in);
void write_bmp(char* filename, unsigned char *out);
int validate_result(char* golden_filename, char* output_filename, int skip_borders);
void deinterleave(unsigned char rgb_in[SIZE][3], 
	unsigned char r_out[SIZE], unsigned char g_out[SIZE], unsigned char b_out[SIZE]);
void interleave(unsigned char rgb_out[SIZE][3], 
	unsigned char r_in[SIZE], unsigned char g_in[SIZE], unsigned char b_in[SIZE]);

int main(int argc, char* argv[])
{
	if(argc < 3) {
		printf("missing arguments: input_file.bmp output_file.bmp [golden_output_file.bmp]\n");
		exit(1);
	}

	unsigned char in[SIZE][3];
	unsigned char out[SIZE][3];
	unsigned char r_in[SIZE];
	unsigned char g_in[SIZE];
	unsigned char b_in[SIZE];
	unsigned char r_out[SIZE];
	unsigned char g_out[SIZE];
	unsigned char b_out[SIZE];

	char *input_filename = argv[1];
	char *output_filename = argv[2];

	read_bmp(input_filename, (unsigned char*)in);
	deinterleave(in, r_in, g_in, b_in);

	sharpen(r_in, g_in, b_in, r_out, g_out, b_out);

	interleave(out, r_out, g_out, b_out);
	write_bmp(output_filename, (unsigned char*)out);

	if(argc >= 4) {
		// check result against golden solution
		char *golden_output_filename = argv[3];
		int valid = validate_result(golden_output_filename, output_filename, 1);
		if(!valid) {
			return 1;
		}
	}

	return 0;
}

// Kernel function

void sharpen(
	unsigned char r_in[SIZE], unsigned char g_in[SIZE], unsigned char b_in[SIZE], 
	unsigned char r_out[SIZE], unsigned char g_out[SIZE], unsigned char b_out[SIZE])
{
	float gray[SIZE];
	float blur_y[SIZE];
	float blur_x[SIZE];
	float sharpen[SIZE];
	float ratio[SIZE];
	
	for(int i = 0; i < SIZE; i++) {
		gray[i] = 0.1 * r_in[i] + 0.6 * g_in[i] + 0.3 * b_in[i];
	}

	for(int i = WIDTH; i < SIZE - WIDTH; i++) {
		blur_y[i] = (gray[i - WIDTH] + gray[i] + gray[i + WIDTH]) / 3;
	}

	for(int i = WIDTH; i < SIZE - WIDTH; i++) {
		blur_x[i] = (blur_y[i - 1] + blur_y[i] + blur_y[i + 1]) / 3;
	}

	for(int i = WIDTH; i < SIZE - WIDTH; i++) {
		sharpen[i] = fabs(2 * gray[i] - blur_x[i]);
	}




	for(int i = WIDTH; i < SIZE - WIDTH; i++) {
		ratio[i] = sharpen[i] / (gray[i] + 1);
	}

	for(int i = WIDTH; i < SIZE - WIDTH; i++) {
		r_out[i] = fmin(ratio[i] * r_in[i], 255);
		g_out[i] = fmin(ratio[i] * g_in[i], 255);
		b_out[i] = fmin(ratio[i] * b_in[i], 255);
	}
}

// Auxiliary functions

void deinterleave(unsigned char rgb_in[SIZE][3], 
	unsigned char r_out[SIZE], unsigned char g_out[SIZE], unsigned char b_out[SIZE])
{
	for(int i = 0; i < SIZE; i++) {
		r_out[i] = rgb_in[i][0];
		g_out[i] = rgb_in[i][1];
		b_out[i] = rgb_in[i][2];
	}
}

void interleave(unsigned char rgb_out[SIZE][3], 
	unsigned char r_in[SIZE], unsigned char g_in[SIZE], unsigned char b_in[SIZE])
{
	for(int i = 0; i < SIZE; i++) {
		rgb_out[i][0] = r_in[i];
		rgb_out[i][1] = g_in[i];
		rgb_out[i][2] = b_in[i];
	}
}

void write_bmp(char* filename, unsigned char *out)
{
	unsigned char header[] = {
		0x42,0x4d,0x38,0xf9,0x15,0x00,0x00,0x00,
		0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
		0x00,0x00,0x58,0x02,0x00,0x00,0x20,0x03,
		0x00,0x00,0x01,0x00,0x18,0x00,0x00,0x00,
		0x00,0x00,0x02,0xf9,0x15,0x00,0x12,0x0b,
		0x00,0x00,0x12,0x0b,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00
	};
	*(int*)&header[18] = WIDTH;
	*(int*)&header[22] = HEIGHT;

    FILE* f = fopen(filename, "wb");
    if(!f) {
    	printf("Unable to open: '%s0 for writing", filename);
    	exit(1);
    }

    fwrite(header, sizeof(unsigned char), 54, f); // write the 54-byte header
    int size = 3 * WIDTH * HEIGHT;
	fwrite(out, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);
}

void read_bmp(char* filename, unsigned char *in)
{
    FILE* f = fopen(filename, "rb");
    if(!f) {
    	printf("Unable to open: '%s0 for reading", filename);
    	exit(1);
    }
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    if(width != WIDTH || height != HEIGHT) {
    	printf("Invalid input file\n");
    	printf("Image size is: %d X %d\n", width, height);
    	printf("Expected: %d X %d\n", WIDTH, HEIGHT);
    	exit(1);
    }

    int size = 3 * width * height;
    fread(in, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);
}

int validate_result(char* golden_filename, char* output_filename, int skip_borders)
{
	unsigned char out[HEIGHT * WIDTH * 3];
	unsigned char golden[HEIGHT * WIDTH * 3];

	read_bmp(output_filename, out);
	read_bmp(golden_filename, golden);

	int max_diff = 0;
	int errors = 0;

	for(int i = 0; i < HEIGHT * WIDTH * 3; i++) {
		int x = (i / 3) % WIDTH;
		int y = (i / 3) / WIDTH;

		if(skip_borders && (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1)) {
			continue;
		}

		int diff = abs(((unsigned char*)out)[i] - ((unsigned char*)golden)[i]);
		if(diff > TOLERANCE) {
			errors++;
			if(diff > max_diff) {
				max_diff = diff;
			}
		}
	}

	if(errors > 0) {
		printf("Validation failed. Detected %d missmatching pixels. Maximum error: %d\n", errors, max_diff);
		return 0;
	} else {
		printf("Validation passed!\n");
		return 1;
	}
}
