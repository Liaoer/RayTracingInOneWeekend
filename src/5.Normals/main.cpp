#include "svpng.inc"
#include "ray.h"
#include <iostream>

#define W 800
#define H 400

/*球的方程
R^2 = x^2 + y^2 + z^2
这是球心在000的情况，如果我们假设球心的坐标为 C = (cx,cy,cz) ， 那么等式变为
R^2 = (x-cx)^2 + (y-cy)^2 + (z-cz)^2
在图形学中，我们可以描述为
R^2 = dot( p - C , p - C )
p又是关于t的函数 P = A + t * B ，这是光线追踪方程 。
所以带入可以得到

R^2 = dot( (A + t B - C) , (A + t B - C) )
最后，R，A ， B , C都是我们指定的参数，我们要知道的是 t 的值. 只要解出这个方程 .
根据代数知识 ,可以推出
dot(B,B) t ^ 2 + 2 dot( B , A-C ) * t + dot(A-C,A-C) - R^2 = 0*/

float hit_sphere(const Vec3& center, float radius, const Ray& r)
{

    Vec3 oc = r.Origin() - center;

    float a = dot(r.Direction(), r.Direction());

    float b = 2.0 * dot(oc, r.Direction());

    float c = dot(oc, oc) - radius*radius;

    float discriminant = b*b - 4*a*c;

    if (discriminant < 0)
        return -1;
    else
        return (-b - sqrt(discriminant)) / (2.0 * a);

}

Vec3 color(const Ray& r)
{
    Vec3 sphereorgin(0,0,-1);
    float t = hit_sphere(sphereorgin, 0.5, r);
    if (t > 0.0) 
    {//t>0，表示有具有实际意义的根。r.point_at_parameter(t)通过t的值获得交点P的坐标，P的坐标减去球心的坐标即得到法向量，然后标准化后得到单位法向量，然后将单位法向量映射成色彩表
        // 计算法线 
        Vec3 N = unit_vector(r.point_at_parameter(t) - sphereorgin );
        // 同样把 -1 - 1 重映射到 0-1
        return 0.5 * Vec3(N.x()+1 , N.y()+1 ,N.z()+1 );
    }

    Vec3 unit_direction = unit_vector(r.Direction());

    // 因为y的值是 -1到1 ，我们这里使用了一个常见的saturate技巧，重新映射到 (0,1) 
    t = 0.5 * (unit_direction.y() + 1.0) ;

    //t=0时，color=vec3(1,1,1)，乘以255后对应的RGB为（255，255，255）  
    //t=1时，color=vec3(0.5,0.7,1)，乘以255后对应的RGB为（127.5，178.5，255）  
    return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);//white, light blue
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
