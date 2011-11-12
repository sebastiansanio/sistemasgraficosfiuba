#include <GL/glew.h>
#include <GL/freeglut.h>

#include <myWindow.h>
   
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#define PI 3.14159265
#define pasotoroide 8
#define PASOCUADRADO 0.05
#define PASOTITA (PI/10)
#define PASOPHI (PI/10)
#define PASOALTURA 0.1
#define PASOTAPA 0.1

using glm::mat4;
using glm::vec3;

enum Figura { CUBO, TOROIDE, CILINDRO, ESFERA };

float anglex = 0;
float angley = 0;

mat4 rotationMatrix;

float positionData[] = 
{
    -0.8f, -0.8f, 0.0f,
     0.8f, -0.8f, 0.0f,
     0.0f,  0.8f, 0.0f
};

GLuint positionBufferHandle;

float normalData[] = 
{
    -0.8f, -0.8f, 0.0f,
     0.8f, -0.8f, 0.0f,
     0.0f,  0.8f, 0.0f
};

GLuint normalBufferHandle;

float colorData[] = 
{
     1.0f,  0.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
     0.0f,  0.0f, 1.0f
};
GLuint colorBufferHandle;

GLuint programHandle;

// Handle to the vertex array object
GLuint vaoHandle;

int opcion = 0;

Figura opcionFigura = CUBO;

float DoblarXEje = 0.5;
float DoblarAngulo = 0.0;

float RetorcerAng = PI;

float RuidoAmplitud = 0.02;
float RuidoInvLongOnda = 40.0;
float RuidoFase = 0.0;

float EsfRadio = 0.7;
float EsfFactor = 0.0;

const char* loadShaderAsString(const char* file)
{
    std::ifstream shader_file(file, std::ifstream::in);
    std::string str((std::istreambuf_iterator<char>(shader_file)), std::istreambuf_iterator<char>());
    return str.c_str();
}

myWindow::myWindow()
{
}

void myWindow::OnRender(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	rotationMatrix = glm::rotate((glm::rotate(mat4(1.0f), angley, vec3(1.0f,0.0f,0.0f))), anglex, vec3(0.0f,1.0f,0.0f));

	GLuint location =glGetUniformLocation(programHandle,"RotationMatrix");
	if( location >= 0 )
	{
		glUniformMatrix4fv(location, 1, GL_FALSE,
		&rotationMatrix[0][0]);
	}

	GLfloat modelview[16];

	//glGetFloatv(GL_MODELVIEW_MATRIX,modelview);

	location =glGetUniformLocation(programHandle,"opcion");
	glUniform1i(location,opcion);

	location =glGetUniformLocation(programHandle,"DoblarXEje");
	glUniform1f(location,DoblarXEje);

	location =glGetUniformLocation(programHandle,"DoblarAngulo");
	glUniform1f(location,DoblarAngulo);

	location =glGetUniformLocation(programHandle,"RetorcerAng");
	glUniform1f(location,RetorcerAng);

	location =glGetUniformLocation(programHandle,"RuidoAmplitud");
	glUniform1f(location,RuidoAmplitud);

	location =glGetUniformLocation(programHandle,"RuidoInvLongOnda");
	glUniform1f(location,RuidoInvLongOnda);

	location =glGetUniformLocation(programHandle,"RuidoFase");
	glUniform1f(location,RuidoFase);

	location =glGetUniformLocation(programHandle,"EsfRadio");
	glUniform1f(location,EsfRadio);

	location =glGetUniformLocation(programHandle,"EsfFactor");
	glUniform1f(location,EsfFactor);
 
    if(opcionFigura == CUBO){
		myWindow::drawCube(0.5,0.0,1.0,0.0);
	} else if(opcionFigura == TOROIDE){
		myWindow::drawToroide(0.4,0.15,1.0,0.0,0.0);
	} else if(opcionFigura == ESFERA){
		myWindow::drawEsfera(0.5,0.0,0.0,1.0);
	} else if(opcionFigura == CILINDRO){
		myWindow::drawCilindro(0.3,0.5,1.0,0.0,0.8);
	}

    //gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //glutWireTeapot(1.0);
	glutSwapBuffers();
}

void  myWindow::OnIdle()
{
	RetorcerAng+=0.01;
	if(RetorcerAng>(2*PI)) RetorcerAng -= (2*PI);
	RuidoFase+=0.002;
	if(RuidoFase>(2*PI)) RuidoFase -= (2*PI);
	DoblarAngulo+=0.01;
	if(DoblarAngulo > PI) DoblarAngulo -= PI;
	EsfFactor+=0.005;
	if(EsfFactor > 1) EsfFactor -= 1;
	myWindow::OnRender();
}

// When OnInit is called, a render context (in this case GLUT-Window) 
// is already available!
void  myWindow::OnInit()
{
	glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

    GLuint vboHandles[3];
    glGenBuffers(3, vboHandles);
    positionBufferHandle = vboHandles[0];
    colorBufferHandle = vboHandles[1];
	normalBufferHandle = vboHandles[2];

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), positionData, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), colorData, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), normalData, GL_STATIC_DRAW );

    // Create and set-up the vertex array objet
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray( vaoHandle );

    // Enable the vertex attributes array
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

    // Map index 0 to the position buffer
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    // Map index 1 to the color buffer
    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	// Map index 2 to the normal buffer
    glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle);
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	// ********************************************
    // Compiling the shader programms
    //*********************************************

	// Do your GLEW experiments here:
    if (GLEW_ARB_shading_language_100) 
    { 
        std::cout << "GLEW_ARB_shading_language_100" << std::endl;
        int major, minor, revision;
        const GLubyte* sVersion = glGetString(GL_SHADING_LANGUAGE_VERSION_ARB);
        if (glGetError() == GL_INVALID_ENUM)
        {
            major = 1; minor = 0; revision=51;
        }
        else
        {
            std::string version((char*)sVersion);
            std::cout << version.c_str() << std::endl;
        }

        // Load vertex Shader
        GLuint vertShader = glCreateShader (GL_VERTEX_SHADER);
        if ( 0 == vertShader )
        {
            std::cout << "Error creating vertex shader" << std::endl;
        }

        std::ifstream v_shader_file("PassThroughVShader.vert", std::ifstream::in);
        std::string v_str((std::istreambuf_iterator<char>(v_shader_file)), std::istreambuf_iterator<char>());
        const char* vs_code_array[] = {v_str.c_str()};
        
        glShaderSource( vertShader, 1, vs_code_array, NULL);

        // Compilar el shader
        glCompileShader( vertShader );

        // verificar resultado de la compilacion
        GLint vs_compilation_result;
        glGetShaderiv( vertShader, GL_COMPILE_STATUS, &vs_compilation_result );
        if( GL_FALSE == vs_compilation_result )
        {
            std::cout << "Vertex shader compilation failed!\n" << std::endl;
            GLint logLen;
            glGetShaderiv( vertShader, GL_INFO_LOG_LENGTH, &logLen );
            if( logLen > 0 )
            {
                char * log = (char *)malloc(logLen);
                GLsizei written;
                glGetShaderInfoLog(vertShader, logLen, &written, log);
                std::cout << "Shader log: " << log << std::endl;
                free(log);
            }
        }

         // Load fragment Shader
        GLuint fragShader = glCreateShader (GL_FRAGMENT_SHADER);
        if ( 0 == fragShader )
        {
            std::cout << "Error creating fragment shader" << std::endl;
        }

        std::ifstream f_shader_file("BasicFShader.frag", std::ifstream::in);
        std::string f_str((std::istreambuf_iterator<char>(f_shader_file)), std::istreambuf_iterator<char>());
        const char* fs_code_array[] = {f_str.c_str()};
        
        glShaderSource( fragShader, 1, fs_code_array, NULL);

        // Compilar el shader
        glCompileShader( fragShader );

        // verificar resultado de la compilacion
        GLint fs_compilation_result;
        glGetShaderiv( fragShader, GL_COMPILE_STATUS, &fs_compilation_result );
        if( GL_FALSE == fs_compilation_result )
        {
            std::cout << "Fragment shader compilation failed!\n" << std::endl;
            GLint logLen;
            glGetShaderiv( fragShader, GL_INFO_LOG_LENGTH, &logLen );
            if( logLen > 0 )
            {
                char * log = (char *)malloc(logLen);
                GLsizei written;
                glGetShaderInfoLog(fragShader, logLen, &written, log);
                std::cout << "Shader log: " << log << std::endl;
                free(log);
            }
        }
	// *******************************************

    // *******************************************
    // Linking the shader programms
    // *******************************************
        programHandle = glCreateProgram();
        if ( 0 == programHandle )
        {
            std::cout << "Error creating program object" << std::endl;
        }
        else
        {
            glAttachShader( programHandle, vertShader );
            glAttachShader( programHandle, fragShader );

            // *******************************************
            // Binding Input Data with input variables
            // *******************************************
        
                // Bind index 0 to the shader input variable "VertexPosition"
                glBindAttribLocation( programHandle, 0, "VertexPosition" );

                // Bind index 1 to the shader input variable "VertexColor"
                glBindAttribLocation( programHandle, 1, "VertexColor" );

				// Bind index 2 to the shader input variable "VertexNorm"
                glBindAttribLocation( programHandle, 2, "VertexNorm" );

            // *******************************************

            glLinkProgram( programHandle );

            GLint status;
            glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
            if( GL_FALSE == status )
            {
                std::cout << "Failed to link shader program!\n" << std::endl;
                GLint logLen;
                glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);
                if( logLen > 0 )
                {
                    char * log = (char *)malloc(logLen);
                    GLsizei written;
                    glGetProgramInfoLog(programHandle, logLen, &written, log);
                    std::cout << "Program log: \n%s" << std::endl;
                    free(log);
                }
            }
            else
            {
                glUseProgram( programHandle );
            }
        }
    }

	rotationMatrix = glm::rotate((glm::rotate(mat4(1.0f), angley, vec3(1.0f,0.0f,0.0f))), anglex, vec3(0.0f,1.0f,0.0f));
}

void myWindow::drawTriangle(float r, float g, float b)
{
	colorData[0] = r;
	colorData[1] = g;
	colorData[2] = b;
	colorData[3] = r;
	colorData[4] = g;
	colorData[5] = b;
	colorData[6] = r;
	colorData[7] = g;
	colorData[8] = b;

	glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), positionData, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), colorData, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), normalData, GL_STATIC_DRAW );

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle);
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle);
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glDrawArrays( GL_TRIANGLES, 0, 3);
}

void myWindow::drawToroide(float radio1, float radio2, float r, float g, float b){
	for(float beta = 0; beta < (2*PI); beta+=(PASOTITA)){
		for(float alfa = 0; alfa < (2*PI); alfa+=(PASOPHI)){
			float cosalfa = cos(alfa);
			float cosbeta = cos(beta);
			float cosalfapaso = cos(alfa+(PASOPHI));
			float cosbetapaso = cos(beta+(PASOTITA));
			float sinalfa = sin(alfa);
			float sinbeta = sin(beta);
			float sinalfapaso = sin(alfa+(PASOPHI));
			float sinbetapaso = sin(beta+(PASOTITA));

			float x11 = (radio1 + radio2 * cosalfa) * cosbeta;
			float y11 = (radio1 + radio2 * cosalfa) * sinbeta;
			float z11 = radio2 * sinalfa;

			float xNorm11 = (radio2 * cosalfa) * cosbeta;
			float yNorm11 = (radio2 * cosalfa) * sinbeta;
			float zNorm11 = radio2 * sinalfa;

			float x12 = (radio1 + radio2 * cosalfapaso) * cosbeta;
			float y12 = (radio1 + radio2 * cosalfapaso) * sinbeta;
			float z12 = radio2 * sin(alfa+(PASOPHI));

			float xNorm12 = (radio2 * cosalfapaso) * cosbeta;
			float yNorm12 = (radio2 * cosalfapaso) * sinbeta;
			float zNorm12 = radio2 * sinalfapaso;

			float x21 = (radio1 + radio2 * cosalfa) * cosbetapaso;
			float y21 = (radio1 + radio2 * cosalfa) * sinbetapaso;
			float z21 = radio2 * sinalfa;

			float xNorm21 = (radio2 * cosalfa) * cosbetapaso;
			float yNorm21 = (radio2 * cosalfa) * sinbetapaso;
			float zNorm21 = radio2 * sinalfa;

			float x22 = (radio1 + radio2 * cosalfapaso) * cosbetapaso;
			float y22 = (radio1 + radio2 * cosalfapaso) * sinbetapaso;
			float z22 = radio2 * sinalfapaso;

			float xNorm22 = (radio2 * cosalfapaso) * cosbetapaso;
			float yNorm22 = (radio2 * cosalfapaso) * sinbetapaso;
			float zNorm22 = radio2 * sinalfapaso;
			
			positionData[0]=x11;
			positionData[1]=y11;
			positionData[2]=z11;
			positionData[3]=x12;
			positionData[4]=y12;
			positionData[5]=z12;
			positionData[6]=x22;
			positionData[7]=y22;
			positionData[8]=z22;

			normalData[0]=xNorm11;
			normalData[1]=yNorm11;
			normalData[2]=zNorm11;
			normalData[3]=xNorm12;
			normalData[4]=yNorm12;
			normalData[5]=zNorm12;
			normalData[6]=xNorm22;
			normalData[7]=yNorm22;
			normalData[8]=zNorm22;

			drawTriangle(r,g,b);

			positionData[0]=x11;
			positionData[1]=y11;
			positionData[2]=z11;
			positionData[3]=x21;
			positionData[4]=y21;
			positionData[5]=z21;
			positionData[6]=x22;
			positionData[7]=y22;
			positionData[8]=z22;

			normalData[0]=xNorm11;
			normalData[1]=yNorm11;
			normalData[2]=zNorm11;
			normalData[3]=xNorm21;
			normalData[4]=yNorm21;
			normalData[5]=zNorm21;
			normalData[6]=xNorm22;
			normalData[7]=yNorm22;
			normalData[8]=zNorm22;

			drawTriangle(r,g,b);
		}
	}
}

void myWindow::drawRectangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, float r, float g, float b)
{
	positionData[0] = x1;
	positionData[1] = y1;
	positionData[2] = z1;
	positionData[3] = x2;
	positionData[4] = y2;
	positionData[5] = z2;
	positionData[6] = x3;
	positionData[7] = y3;
	positionData[8] = z3;

	myWindow::drawTriangle(r,g,b);

	positionData[3] = x4;
	positionData[4] = y4;
	positionData[5] = z4;

	myWindow::drawTriangle(r,g,b);
}

void myWindow::drawCube(float lado, float r, float g, float b)
{
	//Dibuja pequeños cuadrados de PASOCUADRADO de ancho
	//Cara inferior y superior e
	//En x
	for(float i = (-lado/2); i <= ((lado/2)-PASOCUADRADO); i+=PASOCUADRADO)
	{
		float x=i;
		float xhasta=i+PASOCUADRADO;
		//En y
		for(float j = (-lado/2); j <= ((lado/2)-PASOCUADRADO); j+=PASOCUADRADO)
		{
			float y=j;
			float yhasta=j+PASOCUADRADO;
			float z=(-lado/2);
			
			normalData[0]=0.0;
			normalData[1]=0.0;
			normalData[2]=-1.0;
			normalData[3]=0.0;
			normalData[4]=0.0;
			normalData[5]=-1.0;
			normalData[6]=0.0;
			normalData[7]=0.0;
			normalData[8]=-1.0;

			myWindow::drawRectangle(x,y,z,x,yhasta,z,xhasta,yhasta,z,xhasta,y,z,r,g,b);

			//Una vez que dibuje las dos caras hago lo mismo pero cambio los ejes

			normalData[0]=0.0;
			normalData[1]=-1.0;
			normalData[2]=0.0;
			normalData[3]=0.0;
			normalData[4]=-1.0;
			normalData[5]=0.0;
			normalData[6]=0.0;
			normalData[7]=-1.0;
			normalData[8]=0.0;

			myWindow::drawRectangle(x,z,y,x,z,yhasta,xhasta,z,yhasta,xhasta,z,y,r,g,b);

			normalData[0]=-1.0;
			normalData[1]=0.0;
			normalData[2]=0.0;
			normalData[3]=-1.0;
			normalData[4]=0.0;
			normalData[5]=0.0;
			normalData[6]=-1.0;
			normalData[7]=0.0;
			normalData[8]=0.0;

			myWindow::drawRectangle(z,y,x,z,yhasta,x,z,yhasta,xhasta,z,y,xhasta,r,g,b);

			z=(lado/2);

			normalData[0]=0.0;
			normalData[1]=0.0;
			normalData[2]=1.0;
			normalData[3]=0.0;
			normalData[4]=0.0;
			normalData[5]=1.0;
			normalData[6]=0.0;
			normalData[7]=0.0;
			normalData[8]=1.0;

			myWindow::drawRectangle(x,y,z,x,yhasta,z,xhasta,yhasta,z,xhasta,y,z,r,g,b);

			//Una vez que dibuje las dos caras hago lo mismo pero cambio los ejes

			normalData[0]=0.0;
			normalData[1]=1.0;
			normalData[2]=0.0;
			normalData[3]=0.0;
			normalData[4]=1.0;
			normalData[5]=0.0;
			normalData[6]=0.0;
			normalData[7]=1.0;
			normalData[8]=0.0;

			myWindow::drawRectangle(x,z,y,x,z,yhasta,xhasta,z,yhasta,xhasta,z,y,r,g,b);

			normalData[0]=1.0;
			normalData[1]=0.0;
			normalData[2]=0.0;
			normalData[3]=1.0;
			normalData[4]=0.0;
			normalData[5]=0.0;
			normalData[6]=1.0;
			normalData[7]=0.0;
			normalData[8]=0.0;

			myWindow::drawRectangle(z,y,x,z,yhasta,x,z,yhasta,xhasta,z,y,xhasta,r,g,b);
		}
	}
}

void myWindow::drawEsfera(float radio, float r, float g, float b){
	for(float tita = 0; tita < PI; tita+=(PASOTITA)){
		for(float phi = 0; phi < (2*PI); phi+=(PASOPHI)){
			float costita = cos(tita);
			float costitapaso = cos(tita+(PASOTITA));
			float cosphi = cos(phi);
			float cosphipaso = cos(phi+(PASOPHI));

			float sintita = sin(tita);
			float sintitapaso = sin(tita+(PASOTITA));
			float sinphi = sin(phi);
			float sinphipaso = sin(phi+(PASOPHI));

			float x11 = radio * sintita * cosphi;
			float y11 = radio * sintita * sinphi;
			float z11 = radio * costita;

			float x12 = radio * sintitapaso * cosphi;
			float y12 = radio * sintitapaso * sinphi;
			float z12 = radio * costitapaso;

			float x21 = radio * sintita * cosphipaso;
			float y21 = radio * sintita * sinphipaso;
			float z21 = radio * costita;

			float x22 = radio * sintitapaso * cosphipaso;
			float y22 = radio * sintitapaso * sinphipaso;
			float z22 = radio * costitapaso;

			positionData[0]=x11;
			positionData[1]=y11;
			positionData[2]=z11;
			positionData[3]=x12;
			positionData[4]=y12;
			positionData[5]=z12;
			positionData[6]=x22;
			positionData[7]=y22;
			positionData[8]=z22;

			normalData[0]=x11;
			normalData[1]=y11;
			normalData[2]=z11;
			normalData[3]=x12;
			normalData[4]=y12;
			normalData[5]=z12;
			normalData[6]=x22;
			normalData[7]=y22;
			normalData[8]=z22;

			drawTriangle(r,g,b);

			positionData[0]=x11;
			positionData[1]=y11;
			positionData[2]=z11;
			positionData[3]=x21;
			positionData[4]=y21;
			positionData[5]=z21;
			positionData[6]=x22;
			positionData[7]=y22;
			positionData[8]=z22;

			normalData[0]=x11;
			normalData[1]=y11;
			normalData[2]=z11;
			normalData[3]=x21;
			normalData[4]=y21;
			normalData[5]=z21;
			normalData[6]=x22;
			normalData[7]=y22;
			normalData[8]=z22;

			drawTriangle(r,g,b);
		}
	}
}

void myWindow::drawCilindro(float radio, float altura, float r, float g, float b){
	for(float alto = -altura; alto < (altura-(PASOALTURA/2)); alto+=(PASOALTURA)){
		for(float phi = 0; phi < (2*PI); phi+=(PASOPHI)){
			float x11 = radio * sin(phi);
			float z11 = radio * cos(phi);		
			float y11 = alto;

			float x12 = radio * sin(phi+(PASOPHI));
			float z12 = radio * cos(phi+(PASOPHI));		
			float y12 = alto;

			float x21 = radio * sin(phi);
			float z21 = radio * cos(phi);		
			float y21 = alto+(PASOALTURA);

			float x22 = radio * sin(phi+(PASOPHI));
			float z22 = radio * cos(phi+(PASOPHI));
			float y22 = alto+(PASOALTURA);

			positionData[0]=x11;
			positionData[1]=y11;
			positionData[2]=z11;
			positionData[3]=x12;
			positionData[4]=y12;
			positionData[5]=z12;
			positionData[6]=x22;
			positionData[7]=y22;
			positionData[8]=z22;

			normalData[0]=x11;
			normalData[1]=0;
			normalData[2]=z11;
			normalData[3]=x12;
			normalData[4]=0;
			normalData[5]=z12;
			normalData[6]=x22;
			normalData[7]=0;
			normalData[8]=z22;

			drawTriangle(r,g,b);

			positionData[0]=x11;
			positionData[1]=y11;
			positionData[2]=z11;
			positionData[3]=x21;
			positionData[4]=y21;
			positionData[5]=z21;
			positionData[6]=x22;
			positionData[7]=y22;
			positionData[8]=z22;

			normalData[0]=x11;
			normalData[1]=0;
			normalData[2]=z11;
			normalData[3]=x21;
			normalData[4]=0;
			normalData[5]=z21;
			normalData[6]=x22;
			normalData[7]=0;
			normalData[8]=z22;

			drawTriangle(r,g,b);
		}
	}
	myWindow::drawTapaCilindro(radio,altura,r,g,b);
	myWindow::drawTapaCilindro(radio,-altura,r,g,b);
}

void myWindow::drawTapaCilindro(float radio, float altura, float r, float g, float b){
	for(float raux = 0; raux < radio; raux+=(PASOTAPA)){
		for(float phi = 0; phi < (2*PI); phi+=(PASOPHI)){
			float x11 = raux * sin(phi);
			float z11 = raux * cos(phi);		
			float y11 = altura;

			float x12 = raux * sin(phi+(PASOPHI));
			float z12 = raux * cos(phi+(PASOPHI));		
			float y12 = altura;

			float x21 = (raux+(PASOTAPA)) * sin(phi);
			float z21 = (raux+(PASOTAPA)) * cos(phi);		
			float y21 = altura;

			float x22 = (raux+(PASOTAPA)) * sin(phi+(PASOPHI));
			float z22 = (raux+(PASOTAPA)) * cos(phi+(PASOPHI));		
			float y22 = altura;

			positionData[0]=x11;
			positionData[1]=y11;
			positionData[2]=z11;
			positionData[3]=x12;
			positionData[4]=y12;
			positionData[5]=z12;
			positionData[6]=x22;
			positionData[7]=y22;
			positionData[8]=z22;

			normalData[0]=0;
			normalData[1]=y11;
			normalData[2]=0;
			normalData[3]=0;
			normalData[4]=y12;
			normalData[5]=0;
			normalData[6]=0;
			normalData[7]=y22;
			normalData[8]=0;

			drawTriangle(r,g,b);

			positionData[0]=x11;
			positionData[1]=y11;
			positionData[2]=z11;
			positionData[3]=x21;
			positionData[4]=y21;
			positionData[5]=z21;
			positionData[6]=x22;
			positionData[7]=y22;
			positionData[8]=z22;

			normalData[0]=0;
			normalData[1]=y11;
			normalData[2]=0;
			normalData[3]=0;
			normalData[4]=y21;
			normalData[5]=0;
			normalData[6]=0;
			normalData[7]=y22;
			normalData[8]=0;

			drawTriangle(r,g,b);
		}
	}
}

void myWindow::OnResize(int w, int h) 
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLdouble) w/(GLdouble) h, 0.10, 100.0);
}

void  myWindow::OnClose(void)
{
}

void myWindow::OnMouseDown(int button, int x, int y)
{
}

void myWindow::OnMouseUp(int button, int x, int y)
{
}

void myWindow::OnMouseWheel(int nWheelNumber, int nDirection, int x, int y)
{
}

void myWindow::OnKeyDown(int nKey, char cAscii)
{
	if (nKey == 100){
		anglex+=2;
		myWindow::OnRender();
	} else if (nKey == 101){
		angley+=2;
		myWindow::OnRender();
	} else if (nKey == 102){
		anglex-=2;
		myWindow::OnRender();
	} else if (nKey == 103){
		angley-=2;
		myWindow::OnRender();
	} else if (cAscii == 'z'){
		opcionFigura=CUBO;
		anglex=0;
		angley=0;
		myWindow::OnRender();
	} else if (cAscii == 'x'){
		opcionFigura=TOROIDE;
		anglex=0;
		angley=0;
		myWindow::OnRender();
	} else if (cAscii == 'c'){
		opcionFigura=CILINDRO;
		anglex=0;
		angley=0;
		myWindow::OnRender();
	} else if (cAscii == 'v'){
		opcionFigura=ESFERA;
		anglex=0;
		angley=0;
		myWindow::OnRender();
	} else if (cAscii == 'g'){
		opcion=0;
		anglex=0;
		angley=0;
		myWindow::OnRender();
	} else if (cAscii == 'h'){
		opcion=1;
		anglex=0;
		angley=0;
		myWindow::OnRender();
	} else if (cAscii == 'j'){
		opcion=2;
		anglex=0;
		angley=0;
		myWindow::OnRender();
	} else if (cAscii == 'k'){
		opcion=3;
		anglex=0;
		angley=0;
		myWindow::OnRender();
	}  else if (cAscii == 'l'){
		opcion=4;
		anglex=0;
		angley=0;
		myWindow::OnRender();
	}


	if (cAscii == 27) // 0x1b = ESC
	{
		this->Close(); // Close Window!
	}
};

void myWindow::OnKeyUp(int nKey, char cAscii)
{
	if (cAscii == 'f')
	{
		SetFullscreen(true);
	}
	else if (cAscii == 'w')
	{
		SetFullscreen(false);
	}
};
