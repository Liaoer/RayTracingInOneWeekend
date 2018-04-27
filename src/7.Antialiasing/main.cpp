#include "svpng.inc"
#include <iostream>
 
#include "sphere.h"  
#include "hitable_list.h"
#include <float.h> 
#include "camera.h"

#define W 800
#define H 400

Vec3 color(const Ray& r, hitable * world)
{
    hit_record rec;
    if (world->hit(r, 0.0, FLT_MAX, rec)){
        //有撞点：即为球体，将球体颜色设置为球在该点的单位法向量的色彩表映射值
        return 0.5 * Vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    }
    else
    {
        // 无撞点：将颜色设置为背景色  
        Vec3 unit_direction = unit_vector(r.Direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);//white, light blue
    }
}

unsigned char img[W * H * 3];

int main(){

    unsigned char* p = img;
    
     // 声明
    Camera cam;

    int SamplingRate = 100;//采样次数

    /*将所有能够被撞击的物体信息保存在列表中*/
    hitable *list[2];
    list[0] = new sphere(Vec3(0, 0, -1), 0.5);
    list[1] = new sphere(Vec3(0, -100.5, -1), 100);
    hitable *world = new hitable_list(list, 2);

    for (int j = H-1; j >=0 ; j--){
        for (int i = 0; i < W; i++,p += 3)
        {
            Vec3 col(0, 0, 0);
            for (int s = 0; s < SamplingRate ; s++)
            {
                float u = float(i + drand48()) / float(W);
                float v = float(j + drand48()) / float(H);

                Ray r = cam.getRay(u, v);
                Vec3 p = r.point_at_parameter(2.0);

                col += color(r, world);
            }
            col /= float(SamplingRate);
            //float u = float(i) / float(W);
            //float v = float(j) / float(H);
            /*产生光线*/
            //Ray r = cam.getRay(u, v);

            /*设置光线颜色*/  
            //Vec3 col = color(r,world);
            
            p[0] = int(255.99*col[0]);
            p[1] = int(255.99*col[1]);
            p[2] = int(255.99*col[2]);

        }
    }
    svpng(fopen("bg.png", "wb"), W, H, img, 0);
    std::cout << "finished" << std::endl;
}
