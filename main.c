#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WIDTH  20
#define HEIGHT 20

typedef float Layer[HEIGHT][WIDTH];

static Layer inputs;
static Layer weights;

static inline int clampi(int x, int low, int high)
{
    if (x < low)  x = low;
    if (x > high) x = high;
    return x;
}

void layer_fill_rect(Layer layer, int x, int y, int w, int h, float value)
{
    assert(w > 0);
    assert(h > 0);
    int x0 = clampi(x, 0, WIDTH - 1);
    int y0 = clampi(y, 0, HEIGHT - 1);
    int x1 = clampi(x0 + w - 1, 0, WIDTH - 1);
    int y1 = clampi(y0 + w - 1, 0, HEIGHT - 1);

    for (int x = x0; x <= x1; ++x) {
        for (int y = y0; y <=y1; ++y) {
            layer[x][y] = value;
        }
    }

}

void save_layer_as_ppm(Layer layer, const char *file_path)
{
    FILE *f = fopen(file_path, "wb");
    if (f == NULL) {
        fprintf(stderr, "ERROR: Could not open file %s: %m\n",
                file_path);
        exit(1);
    }



    fclose(file_path);
}

float feed_forward(Layer input, Layer weights)
{
    float output = 0.0f;

    for (int x = 0; x < HEIGHT; ++x) {
        for (int y = 0; y < WIDTH; ++y) {
            output += input[x][y] * weights[x][y];
        }
    }

    return output;
}

int main(void)
{
    float output = feed_forward(inputs, weights);
    printf("output = %f\n", output);

    return 0;
}
