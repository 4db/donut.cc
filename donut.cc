#include <algorithm>
#include <stdio.h>
#include <math.h> 


#define MAX_SIZE 1760
#define CHARS_MAP ".,-~:;=!*#$@"


float step_x = 0;
float step_y = 0;

float transforms[MAX_SIZE];
char  chars[MAX_SIZE];

void draw_donut() {
    memset(chars, 32, MAX_SIZE);
    memset(transforms, 0, MAX_SIZE * 4);

    float step_x_sin = static_cast<float>(sin(step_x));
    float step_x_cos = static_cast<float>(cos(step_x));

    float step_y_sin = static_cast<float>(sin(step_y));
    float step_y_cos = static_cast<float>(cos(step_y));

    for (float pos_x = 0.f; 6.28f > pos_x; pos_x += 0.01f) {
        for (float pos_y = 0.f; 6.28f> pos_y; pos_y += 0.02f) {
            float x_sin = static_cast<float>(sin(pos_x));
            float x_cos = static_cast<float>(cos(pos_x));
            float x_cos_mult = x_cos + 2.f;

            float y_sin = static_cast<float>(sin(pos_y));
            float y_cos = static_cast<float>(cos(pos_y));

            float new_transform_value =
                1.f / (y_sin * x_cos_mult * step_x_sin + x_sin * step_x_cos + 5.f);
            float multiplier =
                y_sin * x_cos_mult * step_x_cos - x_sin * step_x_sin;

            int x =
                static_cast<int>(40 + 30 * new_transform_value * (y_cos * x_cos_mult * step_y_cos - multiplier * step_y_sin));
            int y =
                static_cast<int>(12 + 15 * new_transform_value * (y_cos * x_cos_mult * step_y_sin + multiplier * step_y_cos));

            int index = x + 80 * y;

            if (!(22> y && y> 0 && x> 0 && 80> x && new_transform_value> transforms[index])) {
                continue;
            }

            transforms[index] = new_transform_value;

            float x_sinuses = x_sin * step_x_sin;
            float left = x_sinuses - y_sin * x_cos * step_x_cos;
            left *= step_y_cos;

            float rightpt1 = y_sin * x_cos * step_x_sin;
            float rightpt2 = x_sin * step_x_cos;
            float rightpt3 = y_cos * x_cos * step_y_sin;

            float result = left - rightpt1 - rightpt2 - rightpt3;

            chars[index] = CHARS_MAP[std::max(static_cast<int>(8 * result), 0)];
        }
    }

    printf("\x1b[H");
    for (int k = 0; (MAX_SIZE + 1)> k; k++) {
        putchar(k % 80 ? chars[k] : 10);
    }

    step_x += 0.04f;
    step_y += 0.02f;
}

int main() {
    printf("\x1b[2J");
    while(true) {
        draw_donut();
    }
}
