#include <stdio.h>
#include <stdlib.h>
#include "../MaxJFunctions.h"

#define WIDTH 360
#define HEIGHT 480
#define SIZE WIDTH*HEIGHT
#define V 2

#define TOLERANCE 0

void sharpen(unsigned char in[SIZE/V][3*V], unsigned char out[SIZE/V][3*V]);
void read_bmp(char* filename, unsigned char *in);
void write_bmp(char* filename, unsigned char *out);
int validate_result(char* golden_filename, char* output_filename, int skip_borders);

int main(int argc, char* argv[])
{
    if(argc < 3) {
        printf("missing arguments: input_file.bmp output_file.bmp [golden_output_file.bmp]\n");
        exit(1);
    }

    unsigned char in[SIZE/V][3*V];
    unsigned char out[SIZE/V][3*V];

    char *input_filename = argv[1];
    char *output_filename = argv[2];

    read_bmp(input_filename, (unsigned char*)in);
    sharpen(in, out);
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

void sharpen(unsigned char in[SIZE/V][3*V], unsigned char out[SIZE/V][3*V])
{
    float gray[SIZE/V][V];
    float blur_y[SIZE/V][V];
    float blur_x[SIZE/V][V];
    float sharpen[SIZE/V][V];
    float ratio[SIZE/V][V];
    float unsharp[SIZE/V][3*V];

    for(int i = 0; i < SIZE/V; i++) {
        for (int v = 0; v < V; v++) {
            gray[i][v] = 0.1 * in[i][3*v + 0] + 0.6 * in[i][3*v + 1] + 0.3 * in[i][3*v + 2];
        }
    }
    for(int i = WIDTH/V; i < (SIZE - WIDTH)/V; i++) {
        for (int v = 0; v < V; v++) {
            blur_y[i][v] = (gray[i - WIDTH][v] + gray[i][v] + gray[i + WIDTH][v]) / 3;
        }
    }

    for(int i = WIDTH/V; i < (SIZE - WIDTH)/V; i++) {
        for (int v = 0; v < V; v++) {
            blur_x[i][v] = (blur_y[i - 1][v] + blur_y[i][v] + blur_y[i + 1][v]) / 3;
        }
    }

    for(int i = 0; i < SIZE/V; i++) {
        for (int v = 0; v < V; v++) {
            sharpen[i][v] = fabs(2 * gray[i][v] - blur_x[i][v]);
        }
    }

    for(int i = 0; i < SIZE/V; i++) {
        for (int v = 0; v < V; v++) {
            ratio[i][v] = sharpen[i][v] / (gray[i][v] + 1);
        }
    }

    for(int i = 0; i < SIZE/V; i++) {
        for (int c = 0; c < 3; c++) {
            for (int v = 0; v < V; v++) {
                unsharp[i][c + 3*v] = ratio[i][v] * in[i][c + 3*v];
            }
        }
    }

    for(int i = 0; i < SIZE/V; i++) {
        for (int c = 0; c < 3; c++) {
            for (int v = 0; v < V; v++) {
                out[i][c + 3*v] = (unsigned char) fmin(unsharp[i][c + 3*v], 255);
            }
        }
    }
}

// Auxiliary functions

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
