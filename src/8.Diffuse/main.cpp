#include "svpng.inc"
#include <iostream>
 
#include "sphere.h"  
#include "hitable_list.h"
#include <float.h> 
#include "camera.h"


#define W 800
#define H 400

Vec3 Random_in_unitt_cube()
{
    Vec3 p;
    do
    {
        p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1,1,1);

    } while (p.squared_length() >= 1.0 );
    return p;
}


Vec3 color(const Ray& r, hitable * world)
{
    hit_record rec;
    if (world->hit(r, 0.0, FLT_MAX, rec)){
          //todo
          Vec3 target = rec.p + rec.normal + Random_in_unitt_cube();
          return 0.5 * color(Ray(rec.p, target - rec.p), world);
    }
    else
    {
        // 无撞点：将颜色设置为背景色  
        Vec3 unit_direction = unit_vector(r.Direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);//white, light blue
    }
}

void showProgress(int num , int sum )
{
    std::cout << (sum - num) * 100 / sum << "%" << std::endl;
}

Vec3 Gamma_Correct(Vec3 col, int SamplingRate)
{
    float gammafactor = float(SamplingRate);
    col /= gammafactor ;
    return Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
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
        showProgress(j,H);
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
            //gamma 矫正
            col = Gamma_Correct(col,SamplingRate);
            
            p[0] = int(255.99*col[0]);
            p[1] = int(255.99*col[1]);
            p[2] = int(255.99*col[2]);

        }
    }
    svpng(fopen("bg.png", "wb"), W, H, img, 0);
    std::cout << "finished" << std::endl;
}
