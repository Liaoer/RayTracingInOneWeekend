#include "camera.h"

Camera::Camera()
{
    lower_left_corner = Vec3(-2.0, -1.0, -1.0);
    horizontal = Vec3(4.0,0.0,0.0);
    vertical = Vec3(0.0,2.0,0.0);
    origin = Vec3(0.0, 0.0, 0.0);
}
