#include "svpng.inc"
#include "ray.h"
#include <iostream>

#define W 200
#define H 100

Vec3 color(const Ray& r)
{

    Vec3 unit_direction = unit_vector(r.Direction());

    // 因为y的值是 -1到1 ，我们这里使用了一个常见的saturate技巧，重新映射到 (0,1) 
    float t = 0.5 * (unit_direction.y() + 1.0) ;

    //t=0时，color=vec3(1,1,1)，乘以255后对应的RGB为（255，255，255）  
    //t=1时，color=vec3(0.5,0.7,1)，乘以255后对应的RGB为（127.5，178.5，255）  
    //如上两个颜色分别对应着“白色”和“浅蓝色”。  
    //画面颜色=(1-t)*“白色”+ t*“浅蓝色”，即画面颜色为“白色”和“浅蓝色”（沿着Y方向）的线性插值的结果。如果要换成X或者Z方向，将上面的.y()改成.x()或者.z()即可。 
    //若要换其他颜色，设置对应的RGB值即可。 
    return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}

unsigned char img[W * H * 3];

int main(){

    unsigned char* p = img;
    // 左下角的坐标 
    Vec3 lower_left_corner(-2.0 , -1.0 , - 1.0 );

    // 水平方向的大小
    Vec3 horizontal(4.0, 0.0, 0.0);

    // 垂直方向的大小 
    Vec3 vertical(0.0,2.0,0.0);

    // 原点坐标 
    Vec3 origin(0.0, 0.0, 0.0);

    for (int j = H-1; j >=0 ; j--){
        for (int i = 0; i < W; i++,p += 3)
        {
            float u = float(i) / float(W);
            float v = float(j) / float(H);
            // 射线
            Ray r(origin, lower_left_corner + u* horizontal + v * vertical);

            // 追踪 
            Vec3 col = color(r);
            
            p[0] = int(255.99*col[0]);
            p[1] = int(255.99*col[1]);
            p[2] = int(255.99*col[2]);

        }
    }
    svpng(fopen("bg.png", "wb"), W, H, img, 0);
    std::cout << "finished" << std::endl;
}
