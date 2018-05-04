#ifndef HITABLE_LIST_H  
#define HITABLE_LIST_H  
  
#include "hitable.h" 

class hitable_list:public hitable
{
public:
    hitable **list;//hitable_list是所有能够被光线撞击的物体的列表/集合
    int list_size;
public: 
    hitable_list(){}
    hitable_list(hitable ** l, int n) 
    {
        list = l;
        list_size = n;
    }

    virtual bool hit(const Ray & r, float tmin, float tmax, hit_record & rec ) const;
};

#endif // HITABLE_LIST_H  