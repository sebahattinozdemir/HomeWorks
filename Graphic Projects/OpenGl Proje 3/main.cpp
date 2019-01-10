#include "helper.h"
#include <glm/ext.hpp>

static GLFWwindow * win = NULL;

// Shaders
GLuint idProgramShader;
GLuint idFragmentShader;
GLuint idVertexShader;
GLuint idJpegTexture;
GLuint idMVPMatrix;
GLuint idPosition;

GLuint idlightPosition;
GLuint idtextureWidth;
GLuint idtextureHeight;
GLuint idheightFactor;
GLuint idcameraPosition;

glm::mat4 view_matrix;
glm::mat4 normal_matrix;
glm::mat4 projection_matrix ;
glm::mat4 model_matrix ;
glm::mat4 mvp ;
GLint normalMatrix ;
GLint cameraPosition;
GLint mvpLoc ;
GLint mvLoc ;
GLuint vertexbuffer;

GLfloat camPos[3] ; 
GLfloat lightPosition[3] ; 

long sizeofVertex;
GLfloat *vertex;
float heightFactor = 10.0f;
float kMoveSpeed = 0.25f;
float kHeightFactor = 0.5f ;

bool fullScreen ;
long windowWidth ;
long windowHeight ;


int resizeWindowWidth ;
int resizeWindowHeight ;
float windowAspect;

GLFWvidmode *mode;
const GLFWmonitor *monitor;

GLuint vertexAttribBuffer;
GLuint indexBuffer;
  
int widthTexture, heightTexture;

struct Camera{

	glm::vec3 gaze;
	glm::vec3 up;
	glm::vec3 left;
	glm::vec3 position;
	GLfloat   speed;
	GLdouble  aspectRatio;
	GLdouble  nearDistance;
	GLdouble  farDistance;
	GLdouble  angle;

};

Camera camera;
	
void initScreen(){

	fullScreen = true;
	windowWidth = 600;
	windowHeight = 600;
	resizeWindowWidth = 0;
	resizeWindowHeight = 0;
}

void init(int textureHeight, int textureWidth) {
    
   
   int i = 0;
   int j= 0;
   int x = 0;
   GLuint VertexArrayID;

   sizeofVertex = sizeof(GLfloat) * widthTexture * heightTexture * 2*3 * 3;

   vertex = new GLfloat[widthTexture * heightTexture * 2*3 * 3]; // 2*w*d triangles and 3*2*w*d vertices
   
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    idPosition = glGetAttribLocation(idProgramShader, "position");
    glEnableVertexAttribArray(idPosition);

   
    glGenBuffers(1, &vertexAttribBuffer);
    glGenBuffers(1, &indexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexAttribBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);



  while(i<heightTexture) {
    
    j=0;
    while(j<widthTexture) {
      

      vertex[x++] = j;  
      vertex[x++] = 0.0f;  
      vertex[x++] = (i + 1.0);  
      vertex[x++] = (j + 1.0);  
      vertex[x++] = 0.0f;  
      vertex[x++] = (i+1.0);  
      vertex[x++] = (j + 1.0);  
      vertex[x++] = 0.0f;  
      vertex[x++] = i; 
       
      vertex[x++] = (j + 1.0);  
      vertex[x++] = 0.0f;  
      vertex[x++] = i; 
      vertex[x++] = j;  
      vertex[x++] = 0.0f;  
      vertex[x++] = i; 
      vertex[x++] = j;  
      vertex[x++] = 0.0f;  
      vertex[x++] = (i + 1.0);  
    
      j++;
    }
    
  	i++;
  }

   camera.gaze = glm::vec3(0, 0, 1);
   camera.up = glm::vec3(0, 1, 0);
   camera.left = glm::cross(camera.up, camera.gaze);
   camera.position=glm::vec3(widthTexture/2.0, widthTexture/10.0, -widthTexture/4.0);
   camera.speed = 0.0f;
   camera.aspectRatio = 1;
   camera.nearDistance = 0.1;
   camera.farDistance = 1000;
   camera.angle = 45.0;

   glBufferData(GL_ARRAY_BUFFER, sizeofVertex, vertex, GL_STATIC_DRAW);
   glVertexAttribPointer(idPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

}
	
    
void cameraSet() {

    camPos[0] = camera.position.x;
    camPos[1] = camera.position.y;
    camPos[2] = camera.position.z;

    lightPosition[0] = (float)widthTexture/2.0f ;
    lightPosition[1] = (float)widthTexture+(float)heightTexture;
    lightPosition[2] = (float)heightTexture/2.0f, 1.0f ;
    

    view_matrix = glm::lookAt(camera.position, glm::vec3(camera.position + camera.gaze * camera.nearDistance), camera.up);
	normal_matrix = glm::inverseTranspose(view_matrix);
    projection_matrix = glm::perspective(glm::radians(45.0f),1.0f,0.1f,1000.0f);
	model_matrix = glm::mat4(1.0f);
    mvp = projection_matrix * view_matrix * model_matrix;

    
    normalMatrix = glGetUniformLocation(idProgramShader, "normalMatrix");
    cameraPosition = glGetUniformLocation(idProgramShader, "cameraPosition");
    mvpLoc = glGetUniformLocation(idProgramShader, "MVP");
    mvLoc = glGetUniformLocation(idProgramShader, "MV");
    
    idlightPosition = glGetUniformLocation(idProgramShader, "lightPosition");
    idtextureWidth = glGetUniformLocation(idProgramShader, "widthTexture");
    idtextureHeight = glGetUniformLocation(idProgramShader, "heightTexture");
    idheightFactor = glGetUniformLocation(idProgramShader, "heightFactor");
    idcameraPosition = glGetUniformLocation(idProgramShader, "cameraPosition");
    
    
    glUniform3fv(idcameraPosition, 1, camPos);
    glUniform1i(idtextureWidth, widthTexture);  
    glUniform1i(idtextureHeight, heightTexture);
    glUniform1f(idheightFactor, heightFactor); 
    glUniformMatrix4fv(normalMatrix, 1, GL_FALSE, &normal_matrix[0][0]);
    glUniform3fv(cameraPosition, 1, &camera.position[0]);
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &view_matrix[0][0]);    
    glUniform3fv(idlightPosition, 1, lightPosition);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  
}


void drawFunc() {
    

    int w, h;
   	GLfloat newPositonOfCamera[3] ;

    glfwGetFramebufferSize(win, &w, &h);
    glViewport(0, 0, w, h);
    
    glClearColor(0, 0, 0, 1);
    glClearDepth(1.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
    glUniform1f(idheightFactor, heightFactor); 
    
    camera.position += camera.speed * camera.gaze;
    
    cameraSet();

    newPositonOfCamera[0] = camera.position.x ;
    newPositonOfCamera[1] = camera.position.y ;
    newPositonOfCamera[2] = camera.position.z ;
    
    glUniform3fv(idcameraPosition, 1, newPositonOfCamera);

    glEnableClientState(GL_VERTEX_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, vertex);

    glDrawArrays(GL_TRIANGLES, 0, 6 * widthTexture * heightTexture);

    glDisableClientState(GL_VERTEX_ARRAY);

}

void toggleFullscreen(GLFWwindow *window) {

      if (fullScreen) {
            

            glfwSetWindowMonitor(window, const_cast<GLFWmonitor*>(monitor),0,
            	0,mode->width, mode->height,mode->refreshRate);
            resizeWindowWidth = mode->width;
            resizeWindowHeight = mode->height;
            

            fullScreen = true;
        } else {

        	resizeWindowWidth = windowWidth;
            resizeWindowHeight = windowHeight;
            glfwSetWindowMonitor(window, nullptr, 0, 0, windowWidth, windowHeight, 0);


            fullScreen = false;
            
        }
        
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    
    GLint heightFactorLocation;

    if(action == GLFW_PRESS || action == GLFW_REPEAT){

      
      switch(key){
	         
	        case GLFW_KEY_W:
	             camera.gaze = glm::rotate(camera.gaze, -0.01f, camera.left);
	        	 camera.up = glm::rotate(camera.up, -0.01f, camera.left);
	          break; 
	        case GLFW_KEY_A:
	             camera.gaze = glm::rotate(camera.gaze, 0.01f, camera.up);        
	        	 camera.left = glm::rotate(camera.left, 0.01f, camera.up);
	          break; 
	         case GLFW_KEY_S :
	             camera.gaze = glm::rotate(camera.gaze, 0.01f, camera.left);
	             camera.up = glm::rotate(camera.up, 0.01f, camera.left);
	          break; 	        
	        case GLFW_KEY_D:
	             camera.gaze = glm::rotate(camera.gaze, -0.01f, camera.up);
	        	 camera.left = glm::rotate(camera.left, -0.01f, camera.up);
	          break; 
	        case GLFW_KEY_O:
	             heightFactor += kHeightFactor;
	        	 heightFactorLocation = glGetUniformLocation(idProgramShader, "heightFactor");
	        	 glUniform1f(heightFactorLocation, heightFactor);
	          break; 
	        case GLFW_KEY_L:
	             heightFactor -= kHeightFactor;
	        	 heightFactorLocation = glGetUniformLocation(idProgramShader, "heightFactor");
	        	 glUniform1f(heightFactorLocation, heightFactor);
	          break;        
	       case GLFW_KEY_U:
	             camera.speed += kMoveSpeed;
	          break; 
	       
	        case GLFW_KEY_J:
	             camera.speed -= kMoveSpeed;
	          break; 
	       case GLFW_KEY_ESCAPE:
	             glfwSetWindowShouldClose(window, GLFW_TRUE);
	          break;

	       case GLFW_KEY_F:
	             toggleFullscreen(window);

	          break;   
	           
      }
     
    }
}

static void errorCallback(int error,
  const char * description) {
  fprintf(stderr, "Error: %s\n", description);
}


int main(int argc, char * argv[]) {

  if (argc != 2) {
    printf("Only one texture image expected!\n");
    exit(-1);
  }

  glfwSetErrorCallback(errorCallback);

  if (!glfwInit()) {
    exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

  win = glfwCreateWindow(600, 600, "CENG477 - HW3", NULL, NULL);

  if (!win) {
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(win);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

    glfwTerminate();
    exit(-1);
  }

  glfwSetKeyCallback(win, keyCallback);
  

  initShaders();
  initScreen();
  glEnable(GL_DEPTH_TEST);
  
  glUseProgram(idProgramShader);
  initTexture(argv[1], & widthTexture, & heightTexture);
  glEnable(GL_CULL_FACE);
  
  init(heightTexture, widthTexture);
  glShadeModel(GL_SMOOTH);

  while (!glfwWindowShouldClose(win)) {
    
        glfwSwapBuffers(win);
        drawFunc();  
        glfwPollEvents();
        
  }

  glfwDestroyWindow(win);
  glfwTerminate();

  return 0;
}
