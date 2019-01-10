#version 410

in vec3 position;

// Data from CPU
uniform mat4 MVP; // ModelViewProjection Matrix
uniform mat4 MV; // ModelView idMVPMatrix
uniform vec4 cameraPosition;
uniform float heightFactor;

// Texture-related data
uniform sampler2D rgbTexture;
uniform int widthTexture;
uniform int heightTexture;


// Output to Fragment Shader
out vec2 textureCoordinate; // For texture-color
out vec3 vertexNormal; // For Lighting computation
out vec3 ToLightVector; // Vector from Vertex to Light;
out vec3 ToCameraVector; // Vector from Vertex to Camera;


void main()
{

   vec3 pos = vec3(0, 0, 0);
  
   vec3 neighboors[6];
   vec3 normals[6];
   vec4 textureColor;
   vec3 lightPosition;

   vec2 coord1;
   vec2 coord2;
   vec2 coord3;
   vec2 coord4;
   vec2 coord5;
   vec2 coord6;
   vec2 tempCoord; 
   vec4 color;

   textureCoordinate = vec2(1-position.x/widthTexture, 1-position.z/heightTexture);
   textureColor = texture(rgbTexture,textureCoordinate);
   lightPosition = vec3(widthTexture/2, widthTexture+heightTexture, heightTexture/2);

   pos = vec3(position.x, (0.2126 * textureColor.x + 0.7152 * textureColor.y + 0.0722 * textureColor.z) * heightFactor, position.z);

   
   coord1 = vec2(pos.x-1, pos.z);
   coord2 = vec2(pos.x, pos.z-1);
   coord3 = vec2(pos.x+1, pos.z+1);
   coord4 = vec2(pos.x+1, pos.z);
   coord5 = vec2(pos.x, pos.z+1) ;
   coord6 = vec2(pos.x-1, pos.z+1) ;

   if ( coord1.x == widthTexture+1 || coord1.y == heightTexture+1 ||coord1.x == -1 || coord1.y == -1){

    neighboors[0] = vec3(0, 0, 0);
   }
    else{
     tempCoord = vec2(1-coord1.x/widthTexture, 1-coord1.y/heightTexture);
     color = texture(rgbTexture, tempCoord);
     neighboors[0] =  vec3(coord1.x, (0.2126 * color.x + 0.7152 * color.y + 0.0722 * color.z) * heightFactor, coord1.y)-pos;
  }

   
   if (coord1.x == widthTexture+1 || coord1.y == heightTexture+1 ||coord1.x == -1 || coord1.y == -1){

    neighboors[1] = vec3(0, 0, 0);
   }
    else{
     tempCoord = vec2(1-coord2.x/widthTexture, 1-coord2.y/heightTexture);
     color = texture(rgbTexture, tempCoord);
     neighboors[1] =  vec3(coord2.x, (0.2126 * color.x + 0.7152 * color.y + 0.0722 * color.z) * heightFactor, coord2.y)-pos;
  }
   
   if (coord1.x == widthTexture+1 || coord1.y == heightTexture+1 ||coord1.x == -1 || coord1.y == -1){

    neighboors[2] = vec3(0, 0, 0);
   }
    else{
     tempCoord = vec2(1-coord3.x/widthTexture, 1-coord3.y/heightTexture);
     color = texture(rgbTexture, tempCoord);
     neighboors[2] =  vec3(coord3.x, (0.2126 * color.x + 0.7152 * color.y + 0.0722 * color.z) * heightFactor, coord3.y)-pos;
  }
   
   if (coord1.x == widthTexture+1 || coord1.y == heightTexture+1 ||coord1.x == -1 || coord1.y == -1){

    neighboors[3] = vec3(0, 0, 0);
   }
    else{
     tempCoord = vec2(1-coord4.x/widthTexture, 1-coord4.y/heightTexture);
     color = texture(rgbTexture, tempCoord);
     neighboors[3] =  vec3(coord4.x, (0.2126 * color.x + 0.7152 * color.y + 0.0722 * color.z) * heightFactor, coord4.y)-pos;
  }

   if (coord1.x == widthTexture+1 || coord1.y == heightTexture+1 ||coord1.x == -1 || coord1.y == -1){

    neighboors[4] = vec3(0, 0, 0);
   }
    else{
     tempCoord = vec2(1-coord5.x/widthTexture, 1-coord5.y/heightTexture);
     color = texture(rgbTexture, tempCoord);
     neighboors[4] =  vec3(coord5.x, (0.2126 * color.x + 0.7152 * color.y + 0.0722 * color.z) * heightFactor, coord5.y)-pos;
   }   
    
   if (coord1.x == widthTexture+1 || coord1.y == heightTexture+1 ||coord1.x == -1 || coord1.y == -1){

    neighboors[5] = vec3(0, 0, 0);
   }
    else{
     tempCoord = vec2(1-coord6.x/widthTexture, 1-coord6.y/heightTexture);
     color = texture(rgbTexture, tempCoord);
     neighboors[5] =  vec3(coord6.x, (0.2126 * color.x + 0.7152 * color.y + 0.0722 * color.z) * heightFactor, coord6.y)-pos;
   }


   normals[0] = cross(neighboors[1], neighboors[0]);
   normals[1] = cross(neighboors[2], neighboors[1]);
   normals[2] = cross(neighboors[3], neighboors[2]);
   normals[3] = cross(neighboors[4], neighboors[3]);
   normals[4] = cross(neighboors[5], neighboors[4]);
   normals[5] = cross(neighboors[0], neighboors[5]);
   
   vertexNormal = normalize(normals[0] + normals[1] + normals[2] + normals[3] + normals[4] + normals[5]);
   
   ToLightVector = normalize((lightPosition - pos));
   ToCameraVector = normalize((cameraPosition.xyz - pos));
   
   gl_Position = MVP * vec4(pos.xyz, 1.0);
}
