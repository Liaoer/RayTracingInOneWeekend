#include "svpng.inc"
#include "vec3.h"
#include <iostream>

#define W 512
#define H 512

unsigned char img[W * H * 3];

int main(){
    unsigned char* p = img;
    for (int i = 0; i < H; i++){
        for (int j = 0; j < W; j++, p += 3){
            // float r = float(i) / float(W);
            // float g = float(j) / float(H);
            // float b = 0.2;
            Vec3 color(float(i) / float(W),float(j) / float(H), 0.2);
            p[0] = int(255.0f*color[0]);
            p[1] = int(255.0f*color[1]);
            p[2] = int(255.0f*color[2]);
        }
    }
    svpng(fopen("rainbow.png", "wb"), W, H, img, 0);
}
