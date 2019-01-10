#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "hw2_types.h"
#include "hw2_math_ops.h"
#include "hw2_file_ops.h"
#include <iostream>


Camera cameras[100];
int numberOfCameras = 0;

Model models[1000];
int numberOfModels = 0;

Color colors[100000];
int numberOfColors = 0;

Translation translations[1000];
int numberOfTranslations = 0;

Rotation rotations[1000];
int numberOfRotations = 0;

Scaling scalings[1000];
int numberOfScalings = 0;

Vec3 vertices[100000];
int numberOfVertices = 0;

Color backgroundColor;

// backface culling setting, default disabled
int backfaceCullingSetting = 0;

Color **image;



/*
	Initializes image with background color
*/
void initializeImage(Camera cam) {
    int i, j;

    for (i = 0; i < cam.sizeX; i++)
        for (j = 0; j < cam.sizeY; j++) {
            image[i][j].r = backgroundColor.r;
            image[i][j].g = backgroundColor.g;
            image[i][j].b = backgroundColor.b;

        }
}

/*
	Transformations, culling, rasterization are done here.
	You can define helper functions inside this file (rasterizer.cpp) only.
	Using types in "hw2_types.h" and functions in "hw2_math_ops.cpp" will speed you up while working.
*/
void makeArraysEqual(double m1[4][4],double m2[4][4]){
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m1[i][j] = m2[i][j];
        }
    }
}

int findMin(double n1,double n2,double n3){

    if( n1<=n2 && n1<=n3 )
        return n1;

    if( n2<=n1 && n2<=n3 )
        return n2;

    if( n3<=n1 && n3<=n2 )
        return n3;

    }


int findMax(double n1,double n2,double n3){

    if( n1>=n2 && n1>=n3 )
        return n1;

    if( n2>=n1 && n2>=n3 )
        return n2;

    if( n3>=n1 && n3>=n2 )
        return n3;

    }

double findFxy(double x,double y, double Vertex0[3],double Vertex1[3]){

/*fxy = x*(y0-y1) + y*(x1-x0) + x0*y1 - y0*x1 */

double y0 = Vertex0[1];
double y1 = Vertex1[1];
double x1 = Vertex1[0];
double x0 = Vertex0[0];

double result = x*(y0-y1) + y * (x1-x0) + x0*y1 - y0*x1;

return result;

}


void myMultiplyMatrixWithMatrix(double r[4][4], double m1[4][4], double m2[4][4]) {
    int i, j, k;
    double total;
    double m[4][4];

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) {
            total = 0;
            for (k = 0; k < 4; k++)
                total += m1[i][k] * m2[k][j];
            m[i][j] = total;
        }
    makeArraysEqual(r,m);

}

void lineRasterization(int x0, int y0, int x1, int y1, int i, int k, Vec3 c0, Vec3 c1){
        
        int y ;
        int x ;    
       
       Vec3 c;
       c.x = c0.x;
       c.y = c0.y;
       c.z = c0.z;
       

        double alpha;       
       
        Vec3 temp;
        int a, b, d1, d2, d; float m;
        
        if (x1 < x0) {
             d = x0; 
             x0 = x1;
             x1 = d;
             d = y0;
             y0 = y1;
             y1 = d; 
             temp.x = c0.x;
             temp.y = c0.y;
             temp.z = c0.z;
             c0.x = c1.x;
             c0.y = c1.y;
             c0.z = c1.z;
            c1.x = temp.x;
            c1.y = temp.y;
            c1.z = temp.z;

        }
        
        a = y0 - y1; 
        b = x1 - x0; 
        m = (float)a / (x0 - x1); x = x0, y = y0;



        if(y0<y1){
            if (m > 0 && m <= 1)
            {
                
                d = 2 * a + b;
                d1 = 2 * a; 
                d2 = 2 * (a + b);
                
                while (x < x1)
                {
                    if (d <= 0) {
                        x++;
                        y++;
                        d += d2;
                    }
                    else { 
                        x++; 
                        d += d1;
                    }
                    
                    alpha =  double(x-x0) / (x1-x0);
                    c.x = (1-alpha)*c0.x + alpha*c1.x;
                    c.y = (1-alpha)*c0.y + alpha*c1.y;
                    c.z = (1-alpha)*c0.z + alpha*c1.z;
                        

                    image[x][y].r = c.x;
                    image[x][y].g = c.y;
                    image[x][y].b = c.z;
                
                }
            }
            else
            {
                d = a + 2 * b; 
                d1 = 2 * (a + b);
                d2 = 2 * b;
                
                while (y < y1)
                {
                    if (d > 0) { 
                        x++;
                        y++;
                        d += d1; 
                    }
                    else { 
                    
                    y++;
                    d += d2; 
                    }
                                
                    alpha =  double(x-x0) / (x1-x0);
                    c.x = (1-alpha)*c0.x + alpha*c1.x;
                    c.y = (1-alpha)*c0.y + alpha*c1.y;
                    c.z = (1-alpha)*c0.z + alpha*c1.z;

                
                    image[x][y].r = c.x;
                    image[x][y].g = c.y;
                    image[x][y].b = c.z;
                
                }
            }
            
        }
        else{
            if (m < 0 && m >= -1)
            {
                d = 2 * a - b; 
                d1 = 2 * a - 2 * b;
                d2 = 2 * a;
                
                while (x < x1)
                {
                    if (d > 0) { 
                        x++;
                        y--; 
                        d += d1;
                    
                    }
                    else { 
                    
                    x++;
                    d += d2;
                    }
                     
                    alpha =  double(x-x0) / (x1-x0);
                    c.x = (1-alpha)*c0.x + alpha*c1.x;
                    c.y = (1-alpha)*c0.y + alpha*c1.y;
                    c.z = (1-alpha)*c0.z + alpha*c1.z;

                
                    image[x][y].r = c.x;
                    image[x][y].g = c.y;
                    image[x][y].b = c.z;
                }
            }
            else
            {
                d = a - 2 * b;
                d1 = -2 * b; 
                d2 = 2 * (a - b);
            
                while (y > y1)
                {
                    if (d <= 0) { 
                        
                        x++;
                        y--; 
                        d += d2; 
                    }
                    
                    else { 
                    
                    y--;
                    d += d1; 
                    
                    }
                    
                    alpha =  double(x-x0) / (x1-x0);
                    c.x = (1-alpha)*c0.x + alpha*c1.x;
                    c.y = (1-alpha)*c0.y + alpha*c1.y;
                    c.z = (1-alpha)*c0.z + alpha*c1.z;

                    image[x][y].r = c.x;
                    image[x][y].g = c.y;
                    image[x][y].b = c.z;
                    
                }
            }
            
        }

	
}



void forwardRenderingPipeline(Camera cam) {


    for(int i = 0 ; i < numberOfModels; i++ ){
    double mMatrix[4][4] = {
                            {1,0,0,0},
                            {0,1,0,0},
                            {0,0,1,0},
                            {0,0,0,1}};
      /********Modeling Transformation**********/
        for(int j = 0 ; j< models[i].numberOfTransformations;j++){

            if(models[i].transformationTypes[j]=='s'){

                Scaling s = scalings[models[i].transformationIDs[j]];
                

                double smatrix[4][4] = {
                        {s.sx,0,0,0},
                        {0,s.sy,0,0},
                        {0,0,s.sz,0},
                        {0,0,0,1}
                      };
                myMultiplyMatrixWithMatrix(mMatrix,smatrix,mMatrix);
            }

            if(models[i].transformationTypes[j]=='t'){

                Translation t = translations[models[i].transformationIDs[j]];

                double tmatrix[4][4] = {

                        {1,0,0,t.tx},
                        {0,1,0,t.ty},
                        {0,0,1,t.tz},
                        {0,0,0,1}};
                myMultiplyMatrixWithMatrix(mMatrix,tmatrix,mMatrix);
            }

            if(models[i].transformationTypes[j]=='r'){

                Rotation r = rotations[models[i].transformationIDs[j]];
                double translationMatrix[4][4] = {
                        {1,0,0,r.ux},
                        {0,1,0,r.uy},
                        {0,0,1,r.uz},
                        {0,0,0,1}};

                double cosa = r.uz/lengthOfVec3(Vec3 {r.ux,r.uy,r.uz});
                double sina = r.uy/lengthOfVec3(Vec3 {r.ux,r.uy,r.uz});
                double rxa[4][4] = {
                        {1,0,0,0},
                        {0,cosa,-sina,0},
                        {0,sina,cosa,0},
                        {0,0,0,1}};

                double cosb = sqrt(r.uy*r.uy + r.uz*r.uz)/lengthOfVec3(Vec3 {r.ux,r.uy,r.uz});
                double sinb = r.ux / lengthOfVec3(Vec3 {r.ux,r.uy,r.uz});
                double ryb[4][4] = {
                        {cosb,0,-sinb,0},
                        {0,1,0,0},
                        {sinb,0,cosb,0},
                        {0,0,0,1}};

                double minusryb[4][4] = {
                        {cosb,0,sinb,0},
                        {0,1,0,0},
                        {-sinb,0,cosb,0},
                        {0,0,0,1}};

                double minusrxa[4][4] = {
                        {1,0,0,0},
                        {0,cosa,sina,0},
                        {0,-sina,cosa,0},
                        {0,0,0,1}};

                double minusTranslationMatrix[4][4] = {
                        {1,0,0,-r.ux},
                        {0,1,0,-r.uy},
                        {0,0,1,-r.uz},
                        {0,0,0,1}};

                double costheta = cos((r.angle*M_PI/180));
                double sintheta = sin((r.angle*M_PI/180));
                double rztheta[4][4] = {
                        {costheta,-sintheta,0,0},
                        {sintheta,costheta,0,0},
                        {0,0,1,0},
                        {0,0,0,1}};

                double r0[4][4],r1[4][4],r2[4][4],r3[4][4],r4[4][4],rmatrix[4][4];

                multiplyMatrixWithMatrix(r0,translationMatrix,minusrxa);
                multiplyMatrixWithMatrix(r1,ryb,rztheta);
                multiplyMatrixWithMatrix(r2,minusryb,rxa);
                multiplyMatrixWithMatrix(r3,r2,minusTranslationMatrix);
                multiplyMatrixWithMatrix(r4,r0,r1);
                multiplyMatrixWithMatrix(rmatrix,r4,r3);

                //if rotation is selected then multiply with rmatrix
                myMultiplyMatrixWithMatrix(mMatrix,rmatrix,mMatrix);

                
            }
        }
/********Camera Transformation**********/
    
    double Mcam [4][4]{

        {cam.u.x, cam.u.y, cam.u.z,-1.0*(cam.u.x*cam.pos.x+cam.u.y*cam.pos.y+cam.u.z*cam.pos.z)},
        {cam.v.x, cam.v.y, cam.v.z,-1.0*(cam.v.x*cam.pos.x+cam.v.y*cam.pos.y+cam.v.z*cam.pos.z)},
        {cam.w.x, cam.w.y, cam.w.z,-1.0*(cam.w.x*cam.pos.x+cam.w.y*cam.pos.y+cam.w.z*cam.pos.z)},
        {0, 0, 0, 1}

    };

    

 /********Perspective  Transformation**********/
  
    double Mper [4][4]{

        {(2.0*cam.n)/(cam.r - cam.l), 0, (cam.r + cam.l)/(cam.r - cam.l), 0},
        {0, (2.0*cam.n)/(cam.t - cam.b), (cam.t + cam.b)/(cam.t - cam.b), 0},
        {0, 0, -1.0*(cam.f + cam.n)/(cam.f - cam.n), -1.0*(2.0*cam.f*cam.n)/(cam.f - cam.n)},
        {0, 0, -1.0, 0}

    } ;
   

/********ViewPort Transformation**********/

    double Mviewport [4][4] = {

        {cam.sizeX/2.0, 0, 0, (cam.sizeX-1)/2.0},
        {0, cam.sizeY/2.0, 0, (cam.sizeY-1)/2.0},
        {0, 0, 1.0/2.0, 1.0/2.0},
        {0, 0, 0, 0}
    };

    

    for(int k = 0 ; k < models[i].numberOfTriangles ; k++){
        
        //Vertex1
            double V1 [4] = {
            vertices[models[i].triangles[k].vertexIds[0]].x,
            vertices[models[i].triangles[k].vertexIds[0]].y,
            vertices[models[i].triangles[k].vertexIds[0]].z,
            1.0
            };
     
        // Vertex 2
            double V2 [4] = {
            vertices[models[i].triangles[k].vertexIds[1]].x,
            vertices[models[i].triangles[k].vertexIds[1]].y,
            vertices[models[i].triangles[k].vertexIds[1]].z,
            1.0
            };

       // Vertex 3
            double V3 [4] = {
            vertices[models[i].triangles[k].vertexIds[2]].x,
            vertices[models[i].triangles[k].vertexIds[2]].y,
            vertices[models[i].triangles[k].vertexIds[2]].z,
            1.0
            };
     
         // Vertex 1 manipulation
            double Vertex11[4], v1[4], v11[4];
            multiplyMatrixWithVec4d(v1,mMatrix,V1);
            multiplyMatrixWithVec4d(v11,Mcam,v1);
            multiplyMatrixWithVec4d(Vertex11,Mper,v11);
          
         
       //Perspective Divide
       double Vertex1[4];
       Vertex11[0]/=Vertex11[3];
       Vertex11[1]/=Vertex11[3];
       Vertex11[2]/=Vertex11[3];
       Vertex11[3] = 1.0  ;
       multiplyMatrixWithVec4d(Vertex1,Mviewport,Vertex11);
        
       // Vertex 2 manipulation
       double Vertex22[4];
       double v2[4];
       double v22[4];
       double Vertex2[4];
       multiplyMatrixWithVec4d(v2,mMatrix,V2);
       multiplyMatrixWithVec4d(v22,Mcam,v2);
       multiplyMatrixWithVec4d(Vertex22,Mper,v22);
       
       
       //Perspective Divide
       Vertex22[0]/=Vertex22[3];
       Vertex22[1]/=Vertex22[3];
       Vertex22[2]/=Vertex22[3];
       Vertex22[3] = 1.0  ;
       multiplyMatrixWithVec4d(Vertex2,Mviewport,Vertex22);

       // Vertex 3 manipulation
       double Vertex33[4], v3[4],v33[4];
       double Vertex3[4];
       multiplyMatrixWithVec4d(v3,mMatrix,V3);
       multiplyMatrixWithVec4d(v33,Mcam,v3);
       multiplyMatrixWithVec4d(Vertex33,Mper,v33);
       
       

       //Perspective Divide
       Vertex33[0]/=Vertex33[3];
       Vertex33[1]/=Vertex33[3];
       Vertex33[2]/=Vertex33[3];
       Vertex33[3] = 1.0;
       multiplyMatrixWithVec4d(Vertex3,Mviewport,Vertex33);


       if(backfaceCullingSetting)
       {
           Vec3 v12;
           v12.x = Vertex2[0] - Vertex1[0];
           v12.y = Vertex2[1] - Vertex1[1];
           v12.z = Vertex2[2] - Vertex1[2];

           Vec3 v13;
           v13.x = Vertex3[0] - Vertex1[0];
           v13.y = Vertex3[1] - Vertex1[1];
           v13.z = Vertex3[2] - Vertex1[2];
           
           Vec3 n = crossProductVec3(v12,v13);

            n = normalizeVec3(n);
        
           Vec3 v;
           v.x =  Vertex1[0];
           v.y = Vertex1[1];
           v.z = Vertex1[2];
            
           double result = dotProductVec3(n, v);
           
           if(result<0){

               continue;
           }
           

       }

       /***********Triangle Rasterization***********/
       if(models[i].type==1){

        
        double alfa;
        double beta;
        double gama;
        
        int ymin = findMin(Vertex1[1],Vertex2[1],Vertex3[1]);
        int ymax = findMax(Vertex1[1],Vertex2[1],Vertex3[1]);

        int xmin = findMin(Vertex1[0],Vertex2[0],Vertex3[0]);
        int xmax = findMax(Vertex1[0],Vertex2[0],Vertex3[0]);
        
       
        for(int y = ymin; y <= ymax; y++){
           
            for(int x = xmin ; x <= xmax ; x++){                
           
                alfa = findFxy(x,y,Vertex2,Vertex3) / findFxy(Vertex1[0],Vertex1[1],Vertex2,Vertex3) ;
                beta = findFxy(x,y,Vertex3,Vertex1) / findFxy(Vertex2[0],Vertex2[1],Vertex3,Vertex1) ;
                gama = findFxy(x,y,Vertex1,Vertex2) / findFxy(Vertex3[0],Vertex3[1],Vertex1,Vertex2) ;

                if(alfa >= 0 && beta >= 0 && gama>=0){
                   

                   double V1ColorR = colors[vertices[models[i].triangles[k].vertexIds[0]].colorId].r;
                   double V1ColorG = colors[vertices[models[i].triangles[k].vertexIds[0]].colorId].g;
                   double V1ColorB = colors[vertices[models[i].triangles[k].vertexIds[0]].colorId].b;

                   double V2ColorR = colors[vertices[models[i].triangles[k].vertexIds[1]].colorId].r;
                   double V2ColorG = colors[vertices[models[i].triangles[k].vertexIds[1]].colorId].g;
                   double V2ColorB = colors[vertices[models[i].triangles[k].vertexIds[1]].colorId].b;

                   double V3ColorR = colors[vertices[models[i].triangles[k].vertexIds[2]].colorId].r;
                   double V3ColorG = colors[vertices[models[i].triangles[k].vertexIds[2]].colorId].g;
                   double V3ColorB = colors[vertices[models[i].triangles[k].vertexIds[2]].colorId].b;

                   image[x][y].r = round(alfa*V1ColorR + beta*V2ColorR + gama*V3ColorR);
                   image[x][y].g = round(alfa*V1ColorG + beta*V2ColorG + gama*V3ColorG);
                   image[x][y].b = round(alfa*V1ColorB + beta*V2ColorB + gama*V3ColorB);

                }
            }

        }

       }
       /***********Line Rasterization***********/

       else if(models[i].type==0){
        

        int x0 = round(Vertex1[0]);
        int y0 = round(Vertex1[1]);
        int x1 = round(Vertex2[0]);
        int y1 = round(Vertex2[1]);
        int x2 = round(Vertex3[0]);
        int y2 = round(Vertex3[1]);

        Vec3 c0 ;
        c0.x = colors[vertices[models[i].triangles[k].vertexIds[0]].colorId].r;
        c0.y = colors[vertices[models[i].triangles[k].vertexIds[0]].colorId].g;
        c0.z = colors[vertices[models[i].triangles[k].vertexIds[0]].colorId].b;

        Vec3 c1 ;
        c1.x = colors[vertices[models[i].triangles[k].vertexIds[1]].colorId].r;
        c1.y = colors[vertices[models[i].triangles[k].vertexIds[1]].colorId].g;
        c1.z = colors[vertices[models[i].triangles[k].vertexIds[1]].colorId].b;

        Vec3 c2 ;
        c2.x = colors[vertices[models[i].triangles[k].vertexIds[2]].colorId].r;
        c2.y = colors[vertices[models[i].triangles[k].vertexIds[2]].colorId].g;
        c2.z = colors[vertices[models[i].triangles[k].vertexIds[2]].colorId].b;
       

        lineRasterization (x0, y0, x1, y1, i, k, c0, c1);
        lineRasterization (x1, y1, x2, y2, i, k, c1, c2);
        lineRasterization (x2, y2, x0, y0, i, k, c2, c0);

        
       }

    }

    }


}




int main(int argc, char **argv) {
    int i, j;

    if (argc < 2) {
        std::cout << "Usage: ./rasterizer <scene file> <camera file>" << std::endl;
        return 1;
    }

    // read camera and scene files
    readSceneFile(argv[1]);
    readCameraFile(argv[2]);

    image = 0;

    for (i = 0; i < numberOfCameras; i++) {

        // allocate memory for image
        if (image) {
			for (j = 0; j < cameras[i].sizeX; j++) {
		        delete image[j];
		    }

			delete[] image;
		}

        image = new Color*[cameras[i].sizeX];

        if (image == NULL) {
            std::cout << "ERROR: Cannot allocate memory for image." << std::endl;
            exit(1);
        }

        for (j = 0; j < cameras[i].sizeX; j++) {
            image[j] = new Color[cameras[i].sizeY];
            if (image[j] == NULL) {
                std::cout << "ERROR: Cannot allocate memory for image." << std::endl;
                exit(1);
            }
        }


        // initialize image with basic values
        initializeImage(cameras[i]);

        // do forward rendering pipeline operations
        forwardRenderingPipeline(cameras[i]);

        // generate PPM file
        writeImageToPPMFile(cameras[i]);

        // Converts PPM image in given path to PNG file, by calling ImageMagick's 'convert' command.
        // Notice that os_type is not given as 1 (Ubuntu) or 2 (Windows), below call doesn't do conversion.
        // Change os_type to 1 or 2, after being sure that you have ImageMagick installed.
        convertPPMToPNG(cameras[i].outputFileName, 99);
    }

    return 0;

}
