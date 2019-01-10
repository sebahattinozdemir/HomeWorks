#include "parser.h"

parser::Vec3f operator+(const parser::Vec3f& v1, const parser::Vec3f& v2){
    parser::Vec3f result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;

    return result;
}

parser::Vec3f operator-(const parser::Vec3f& v1, const parser::Vec3f& v2){
    parser::Vec3f result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;

    return result;
}

parser::Vec3f operator*(const parser::Vec3f& v1, float alpha){
    parser::Vec3f result;
    result.x = v1.x * alpha;
    result.y = v1.y * alpha;
    result.z = v1.z * alpha;

    return result;
}

class ray_intersection_result{
public:
    bool hits;
    float tmin;
    parser::Material material;
    parser::Vec3f rayNormal;
    parser::Vec3f rayPos;
    parser::Vec3f origin;
    ray_intersection_result();
    ray_intersection_result(bool hits, float tmin, const parser::Material &material, const parser::Vec3f &rayNormal,
                            const parser::Vec3f &rayPos);
};


class Ray {
private:
    parser::Vec3f origin;
    parser::Vec3f direction;
public:
    const parser::Vec3f &getOrigin() const;

    const parser::Vec3f &getDirection() const;

    Ray(const parser::Vec3f& origin, const parser::Vec3f& direction){
        this->origin = origin;
        this->direction = direction;
    };

};
