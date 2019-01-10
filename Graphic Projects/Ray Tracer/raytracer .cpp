#include <iostream>
#include <math.h>
#include <cfloat>
#include "parser.h"
#include "ppm.h"
#include "raytracer.h"

using namespace parser;

ray_intersection_result::ray_intersection_result() : hits(false), tmin(FLT_MAX) {};

ray_intersection_result::ray_intersection_result(bool hits, float tmin, const Material &material,
                                                 const Vec3f &rayNormal, const Vec3f &rayPos) : hits(hits), tmin(tmin),
                                                                                                material(material),
                                                                                                rayNormal(rayNormal),
                                                                                                rayPos(rayPos) {};

const Vec3f &Ray::getOrigin() const {
    return origin;
}

const Vec3f &Ray::getDirection() const {
    return direction;
}

//calculate determinant of a matrix return a scalar
float calculateDeterminant(float matrix[3][3]){
    float result = 0;
    int i ;
    for(i=0;i<3;i++){
          result = result + (matrix[0][i]*(matrix[1][(i+1)%3]*matrix[2][(i+2)%3] - matrix[1][(i+2)%3]*matrix[2][(i+1)%3]));
    }
    return result;
}

//calculate dot product of two vectors return a scalar
float calculateDotProduct(const Vec3f& v1, const Vec3f& v2){

       return  v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

//get vertex from indices
Vec3f vertexFromIndices(int vertex, const Scene &scene){

     return scene.vertex_data[vertex-1];
}

//normalize a vector (divide to its magnitude)
Vec3f normalize(Vec3f v){
    float mag = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    v.x = v.x/mag;
    v.y = v.y/mag;
    v.z = v.z/mag;
    return v;
}

//calculate cross product and return a vector
Vec3f calculateCrossProduct(const Vec3f &vec1, const Vec3f &vec2){

    Vec3f result;
    result.x = vec1.y * vec2.z - vec1.z * vec2.y;
    result.y = (vec1.z * vec2.x - vec1.x * vec2.z);
    result.z = vec1.x * vec2.y - vec1.y * vec2.x;

    return result;
}

//compute ray-sphere intersection return a ray
bool ray_intersects_sphere(Sphere& sphere, Ray& ray,const Scene& scene,ray_intersection_result& rir){

    Vec3f o = ray.getOrigin();
    Vec3f d = ray.getDirection();
    Vec3f c = vertexFromIndices(sphere.center_vertex_id, scene);
    float r = sphere.radius;

    float det;
    det = calculateDotProduct(d,(o-c))*calculateDotProduct(d,(o-c))-calculateDotProduct(d,d)*(calculateDotProduct(o-c,o-c)-r*r);

    //std::cout << det << std::endl;
    if(det >= 0.0){
        float t1 = (calculateDotProduct(d*-1,(o-c))+sqrt(det))/calculateDotProduct(d,d);
        float t2 = (calculateDotProduct(d*-1,(o-c))-sqrt(det))/calculateDotProduct(d,d);
        float t;
        if (t1 < t2)
            t = t1;
        else
            t = t2;
        if(t >= 0){
            Vec3f rayPosition = ray.getOrigin() + ray.getDirection() * t;

            parser::Vec3f rayMinusCenter = rayPosition-c;
            Vec3f rayNormal = rayMinusCenter*(1.0/sphere.radius);
            rir.tmin = t;
            rir.hits = true;
            rir.rayNormal = normalize(rayNormal);
            rir.rayPos = rayPosition;
            rir.material = scene.materials[sphere.material_id-1];

            return true;
        }
        else{
            return false;
        }
    }else{
        return false;
    }
}

//compute ray-triangle intersection return a ray
bool ray_intersects_triangle(Triangle triangle, Ray& ray, const Scene& scene, Material& material,ray_intersection_result& rir){
    Vec3f v0 = vertexFromIndices(triangle.indices.v0_id,scene);
    Vec3f v1 = vertexFromIndices(triangle.indices.v1_id,scene);
    Vec3f v2 = vertexFromIndices(triangle.indices.v2_id,scene);

    Vec3f d = ray.getDirection();
    Vec3f o = ray.getOrigin();

    //Cramer's rule
    float matrixA[3][3] = {
            {v0.x-v1.x, v0.x-v2.x, d.x},
            {v0.y-v1.y, v0.y-v2.y, d.y},
            {v0.z-v1.z, v0.z-v2.z, d.z}
    };

    float matrixBeta[3][3] = {
            {v0.x-o.x, v0.x-v2.x, d.x},
            {v0.y-o.y, v0.y-v2.y, d.y},
            {v0.z-o.z, v0.z-v2.z, d.z}

    };

    float matrixGamma[3][3] = {
            {v0.x-v1.x, v0.x-o.x, d.x},
            {v0.y-v1.y, v0.y-o.y, d.y},
            {v0.z-v1.z, v0.z-o.z, d.z}

    };

    float matrixT[3][3] = {
            {v0.x-v1.x, v0.x-v2.x, v0.x-o.x},
            {v0.y-v1.y, v0.y-v2.y, v0.y-o.y},
            {v0.z-v1.z, v0.z-v2.z, v0.z-o.z}

    };

    float detA = calculateDeterminant(matrixA);
    if(detA == 0.0)
        return false;
    float detGamma = calculateDeterminant(matrixGamma);
    float detBeta = calculateDeterminant(matrixBeta);
    float detT = calculateDeterminant(matrixT);

    float beta = detBeta/detA;
    float gamma = detGamma/detA;
    float t = detT/detA;
    Vec3f rayNormal = calculateCrossProduct(v2-v1,v0-v1);
    rayNormal = normalize(rayNormal);

    if(t > 0 && (beta + gamma) <= 1 && beta >= 0 && gamma >= 0){
        if (t < rir.tmin) {
            rir.tmin = t;
            rir.rayPos = ray.getOrigin() + ray.getDirection() * rir.tmin;
            rir.rayNormal = rayNormal;
            rir.hits = true;
            rir.material = material;
            return  true;
        }
        return false;
    }
    else{
        return false;
    }
}

bool ray_intersects_face(const Face& face , const Scene& scene, Ray& ray, Material &material,ray_intersection_result& rir){

    Vec3f v0 = vertexFromIndices(face.v0_id,scene);
    Vec3f v1 = vertexFromIndices(face.v1_id,scene);
    Vec3f v2 = vertexFromIndices(face.v2_id,scene);

    Vec3f direction = ray.getDirection();
    Vec3f origin = ray.getOrigin();

    //Cramer's rule
    float matrixA[3][3] = {
            {v0.x-v1.x, v0.x-v2.x, direction.x},
            {v0.y-v1.y, v0.y-v2.y, direction.y},
            {v0.z-v1.z, v0.z-v2.z, direction.z}
    };

    float betaMatrix[3][3] = {
            {v0.x-origin.x, v0.x-v2.x, direction.x},
            {v0.y-origin.y, v0.y-v2.y, direction.y},
            {v0.z-origin.z, v0.z-v2.z, direction.z}
    };

    float gamaMatrix[3][3] = {
            {v0.x-v1.x, v0.x-origin.x, direction.x},
            {v0.y-v1.y, v0.y-origin.y, direction.y},
            {v0.z-v1.z, v0.z-origin.z, direction.z}
    };

    float tMatrix[3][3] = {
            {v0.x-v1.x, v0.x-v2.x, v0.x-origin.x},
            {v0.y-v1.y, v0.y-v2.y, v0.y-origin.y},
            {v0.z-v1.z, v0.z-v2.z, v0.z-origin.z}
    };

    float detA = calculateDeterminant(matrixA);
    if(detA == 0.0)
        return false;
    float detGama = calculateDeterminant(gamaMatrix);
    float detBeta = calculateDeterminant(betaMatrix);
    float detT = calculateDeterminant(tMatrix);

    float beta = detBeta/detA;
    float gamma = detGama/detA;
    float t = detT/detA;
    Vec3f rayNormal = calculateCrossProduct(v2-v1,v0-v1);
    rayNormal = normalize(rayNormal);

    if(t > 0 && (beta + gamma) <= 1 && beta >= 0 && gamma >= 0){
        if (t < rir.tmin) {
            rir.tmin = t;
            rir.rayPos = origin + direction * rir.tmin;
            rir.rayNormal = rayNormal;
            rir.hits = true;
            rir.material = material;
            return  true;
        }

        return true;
    }else {
        return false;
    }

}

float lengthOfVector(const parser::Vec3f& v1){

    return sqrtf(v1.x*v1.x+v1.y*v1.y+v1.z*v1.z);
}

float distanceOfVectors(const parser::Vec3f& v1, const parser::Vec3f& v2){
    float result = 0;
    float a = (v1.x-v2.x);
    float b = (v1.y-v2.y);
    float c = (v1.z-v2.z);

    return sqrtf(a*a + b*b + c*c);
}

ray_intersection_result doesIntersect(Ray ray,  Scene scene){

// Ray Hit
ray_intersection_result rir;
rir.tmin = FLT_MAX;
rir.hits = false;
rir.origin = ray.getOrigin();
bool r = false;
//intersect with spheres
for (int i = 0; i < scene.spheres.size(); ++i) {
    Sphere *sphere = &scene.spheres[i];
    r = ray_intersects_sphere(*sphere,ray,scene,rir);
}
if(!r)

//intersect with triangles
if(!r)
    for (int j = 0; j < scene.triangles.size(); ++j) {
        Triangle *triangle = &scene.triangles[j];
        r = ray_intersects_triangle(*triangle,ray,scene,scene.materials[triangle->material_id-1],rir);
    }

//intersect with faces
    for (int l = 0; l < scene.meshes.size(); ++l) {
        Mesh *mesh = &(scene.meshes[l]);

        for(int k = 0; k < mesh->faces.size(); ++k) {
            Face *face = &mesh->faces[k];
            r = ray_intersects_face(*face, scene, ray, scene.materials[mesh->material_id-1],rir);
        }
    }

  return rir;
}
parser::Vec3f coloring(Ray& ray, int counterForDepth, ray_intersection_result& rir, parser::Scene& scene, parser::Camera& camera){

    parser::Vec3f color;
    if (counterForDepth < 0) {
        color.x = 0;
        color.y = 0;
        color.z = 0;
        return color;
    }

    color.x = rir.material.ambient.x * scene.ambient_light.x;
    color.y = rir.material.ambient.y * scene.ambient_light.y;
    color.z = rir.material.ambient.z * scene.ambient_light.z;

    unsigned long lightSize = scene.point_lights.size();
    int l;
    int j,m,k;
    for(l=0;l<lightSize;l++){
        parser::PointLight *pointLight = &(scene.point_lights[l]);
        parser::Vec3f pointToRayHit = pointLight->position - rir.rayPos;

        parser::Vec3f Wi= (pointToRayHit) * (1/(lengthOfVector(pointToRayHit)));

        bool sphereShadowFlag = false;
        bool dummyFlag = false;
        bool meshShadowFlag = false;

        Ray shadowRay(rir.rayPos + Wi * scene.shadow_ray_epsilon, Wi);
        ray_intersection_result shadowHitInfo ;                     // bu ne aq

        float tLight = (pointLight->position - shadowRay.getOrigin()).x / shadowRay.getDirection().x;


        //Sphere Shadow
        unsigned long sphereSize = scene.spheres.size();
        for(j=0; j<sphereSize;j++){
            parser::Sphere *sphere = &scene.spheres[j];
            ray_intersects_sphere(*sphere,shadowRay,scene,shadowHitInfo);
            // if shadow hit object
            if(shadowHitInfo.hits){
                if(tLight > shadowHitInfo.tmin){
                    sphereShadowFlag = true;
                    dummyFlag = true;
                }

            }
        }

        // Mesh Shadow
        if(!dummyFlag){
            //Mesh
            unsigned long meshSize = scene.meshes.size(),f1;
            for(k = 0; k<meshSize;k++){

                parser::Mesh *mesh = &(scene.meshes[k]);

                unsigned long faceSize= mesh->faces.size();
                //Each face
                for(f1=0;f1<faceSize;f1++){

                    parser::Face *face = &mesh->faces[f1];
                    ray_intersects_face(*face,scene,shadowRay,scene.materials[mesh->material_id-1],shadowHitInfo);
                    // if shadow hit object
                    if(shadowHitInfo.hits){
                        if(tLight > shadowHitInfo.tmin){
                            meshShadowFlag = true;
                            dummyFlag = true;
                        }

                    }

                }

            }
        }


        //TriangleShadow
        if(!dummyFlag){
            //Triangle
            unsigned long triangleSize = scene.triangles.size();
            for(m=0; m<triangleSize;m++){
                parser::Triangle *triangle = &scene.triangles[m];
                ray_intersects_triangle(*triangle,shadowRay,scene,scene.materials[triangle->material_id-1],shadowHitInfo);

                if(shadowHitInfo.hits){
                    if(tLight > shadowHitInfo.tmin){
                        dummyFlag = true;
                    }

                }

            }
        }

        if(!dummyFlag){

            parser::Vec3f cameraToRayHit = rir.origin - rir.rayPos;
            parser::Vec3f Wo = cameraToRayHit * (1/lengthOfVector(cameraToRayHit));

            parser::Vec3f normal = normalize(rir.rayNormal);

            float cosTheta =std::max(0.0f, calculateDotProduct(Wi, normal));
            parser::Vec3f h = (Wi + Wo) *(1/ lengthOfVector(Wi + Wo));
            float cosAlpha = std::min(1.0f,std::max(0.0f,calculateDotProduct(normal,h)));

            parser::Vec3f radiance = pointLight->intensity * (1/((powf(distanceOfVectors(pointLight->position,rir.rayPos),2))));



            parser::Vec3f Wr = (Wo * -1) + (normal * (calculateDotProduct(normal, Wo)) * 2);

            // Diffusing
            color.x += rir.material.diffuse.x * cosTheta * radiance.x;
            color.y += rir.material.diffuse.y * cosTheta * radiance.y;
            color.z += rir.material.diffuse.z * cosTheta * radiance.z;

            //Specular
            float phongOp = powf(cosAlpha,rir.material.phong_exponent);
            color.x += rir.material.specular.x *phongOp * radiance.x;
            color.y += rir.material.specular.y *phongOp * radiance.y;
            color.z += rir.material.specular.z *phongOp * radiance.z;

        }


    }

//Reflection

    ray_intersection_result rir1 = doesIntersect(ray,scene);

    parser::Vec3f cameraToRayHit = rir1.origin - rir1.rayPos;
    cameraToRayHit = normalize(cameraToRayHit);

    parser::Vec3f Wo = cameraToRayHit * (1/lengthOfVector(cameraToRayHit));
    Wo = normalize(Wo);


    parser::Vec3f normal = normalize(rir1.rayNormal);

    parser::Vec3f Wr = (Wo * -1) + (normal * (calculateDotProduct(normal, Wo)) * 2);
    Wr=normalize(Wr);

    Ray reflectionRay(rir1.rayPos + Wr * scene.shadow_ray_epsilon, Wr);

    parser::Vec3f reflectionColor;
    reflectionColor.x= 0;
    reflectionColor.y= 0;
    reflectionColor.z =0;

   reflectionColor = coloring(reflectionRay,counterForDepth-1,rir,scene,camera);

    if(rir1.material.mirror.x > 0 || rir1.material.mirror.y > 0 || rir1.material.mirror.z > 0 ){
      color.x += reflectionColor.x * rir1.material.mirror.x;
      color.y += reflectionColor.y * rir1.material.mirror.y;
      color.z += reflectionColor.z * rir1.material.mirror.z;
    }
    if (color.x > 255.0) {
        color.x = 255.0;
    }

    if (color.y > 255.0) {
        color.y = 255.0;
    }

    if (color.z > 255.0) {
        color.z = 255.0;
    }

    return color;


}




int main(int argc, char* argv[])
{
    Scene scene;
    //Load the scene file from xml
    scene.loadFromXml(argv[1]);

    //compute normals of triangles

    unsigned char* image;
    unsigned long numOfCameras = scene.cameras.size();
    for (int i = 0; i < numOfCameras; ++i) {
        Camera camera = scene.cameras[i];
        //computing eye rays
        Vec3f m,q,u;
        u = calculateCrossProduct(camera.up,camera.gaze*-1);
        u = normalize(u);
        m = camera.position + (camera.gaze*camera.near_distance);
        q = m + u * camera.near_plane.x
            + camera.up * camera.near_plane.w;
        int imageWidth = camera.image_width;
        int imageHeight = camera.image_height;
        image = new unsigned char [imageWidth * imageHeight * 3];
        for (int j = 0; j < imageHeight; ++j) {

            for (int k = 0; k < imageWidth; ++k) {

                double su,sv;
                su = (camera.near_plane.y-camera.near_plane.x)*(k+0.5)/imageWidth;
                sv = (camera.near_plane.w-camera.near_plane.z)*(j+0.5)/imageHeight;

                Vec3f s = q + u*su-camera.up*sv;
                //construct the ray
                Vec3f o = camera.position;
                Vec3f d = s - camera.position;
                d = normalize(d);
                Ray ray(o, d);

                ray_intersection_result rir = doesIntersect(ray,scene);
                if (!rir.hits) {
                    image[3*(j*imageHeight+k)] = (unsigned char)scene.background_color.x;
                    image[3*(j*imageHeight+k)+1] = (unsigned char)scene.background_color.y;
                    image[3*(j*imageHeight+k)+2] = (unsigned char)scene.background_color.z;

                }else{

                    parser::Vec3f color;
                    color = coloring(ray,scene.max_recursion_depth,rir,scene,camera);

                    image[3*(j*imageHeight+k)] = (unsigned char) color.x;
                    image[3*(j*imageHeight+k)+1] = (unsigned char) color.y;
                    image[3*(j*imageHeight+k)+2] = (unsigned char) color.z;
                }

            }
        }
        write_ppm(camera.image_name.c_str(), image, imageWidth, imageHeight);
    }

    return 0;
}
