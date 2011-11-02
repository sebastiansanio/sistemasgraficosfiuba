#include <GL/glew.h>
#include <GL/freeglut.h>

#include <myWindow.h>
   
#include <iostream>
#include <fstream>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#define PI 3.14159265
#define pasotoroide 8

using glm::mat4;
using glm::vec3;

float anglex = 0;
float angley = 0;

mat4 rotationMatrix;

GLuint programHandle;

const char* loadShaderAsString(const char* file)
{
    std::ifstream shader_file(file, std::ifstream::in);
    std::string str((std::istreambuf_iterator<char>(shader_file)), std::istreambuf_iterator<char>());
    return str.c_str();
}

myWindow::myWindow()
{

}

void myWindow::drawTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float * colorData){
	GLuint colorBufferHandle;
	GLuint positionBufferHandle;
	GLuint vaoHandle;
	float positionData[] = 
	{
    x1, y1, z1,
    x2, y2, z2,
    x3, y3, z3
	};

	GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    positionBufferHandle = vboHandles[0];
    colorBufferHandle = vboHandles[1];

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), positionData, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), colorData, GL_STATIC_DRAW );

    // Create and set-up the vertex array objet
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray( vaoHandle );

    // Enable the vertex attributes array
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Map index 0 to the position buffer
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    // Map index 1 to the color buffer
    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	GLuint location =glGetUniformLocation(programHandle,"RotationMatrix");
	if( location >= 0 )
	{
		glUniformMatrix4fv(location, 1, GL_FALSE,
		&rotationMatrix[0][0]);
	}

	glBindVertexArray( vaoHandle );
    glDrawArrays( GL_TRIANGLES, 0, 3);
}

void myWindow::drawCube(float lado, float r, float g, float b)
{
	//Tienen que pasarle los puntos x, y, z de los 8 vertices en un orden especifico
	float colorData[] =
	{
		r, g, b,
		r, g, b,
		r, g, b
	};

	float origx = -(lado*0.5);
	float origy = lado*0.5;
	float origz = lado*0.5;
	
	//Cara superior

	myWindow::drawTriangle(origx,origy,origz,origx,origy-lado,origz,origx+lado,origy-lado,origz,colorData);
	myWindow::drawTriangle(origx,origy,origz,origx+lado,origy,origz,origx+lado,origy-lado,origz,colorData);
	
	//Cara inferior

	myWindow::drawTriangle(origx,origy,origz-lado,origx,origy-lado,origz-lado,origx+lado,origy-lado,origz-lado,colorData);
	myWindow::drawTriangle(origx,origy,origz-lado,origx+lado,origy,origz-lado,origx+lado,origy-lado,origz-lado,colorData);

	//Cara izquierda

	myWindow::drawTriangle(origx,origy,origz,origx,origy,origz-lado,origx,origy-lado,origz-lado,colorData);
	myWindow::drawTriangle(origx,origy,origz,origx,origy-lado,origz,origx,origy-lado,origz-lado,colorData);

	//Cara derecha

	myWindow::drawTriangle(origx+lado,origy,origz,origx+lado,origy,origz-lado,origx+lado,origy-lado,origz-lado,colorData);
	myWindow::drawTriangle(origx+lado,origy,origz,origx+lado,origy-lado,origz,origx+lado,origy-lado,origz-lado,colorData);

	//Tapa arriba

	myWindow::drawTriangle(origx,origy,origz,origx,origy,origz-lado,origx+lado,origy,origz-lado,colorData);
	myWindow::drawTriangle(origx,origy,origz,origx+lado,origy,origz,origx+lado,origy,origz-lado,colorData);

	//Tapa abajo

	myWindow::drawTriangle(origx,origy-lado,origz,origx,origy-lado,origz-lado,origx+lado,origy-lado,origz-lado,colorData);
	myWindow::drawTriangle(origx,origy-lado,origz,origx+lado,origy-lado,origz,origx+lado,origy-lado,origz-lado,colorData);
}

void myWindow::drawToroide(float radio1, float radio2, float r, float g, float b){
	float colorData[] =
	{
		r, g, b,
		r, g, b,
		r, g, b
	};
	float x, y, z;
	

	//Primero completa el vector que tiene la circunferencia
	float circunferencia[pasotoroide*3];
	float paso2 = (2*PI)/pasotoroide;
	float angulo2=0;
	for(int vertice = 0; vertice < (pasotoroide*3); vertice += 3)
	{
		x=(radio2*cos(angulo2)) + radio1;
		z=radio2*sin(angulo2);
		y= 0;
		circunferencia[vertice] = x;
		circunferencia[vertice+1] = y;
		circunferencia[vertice+2] = z;
		angulo2+=paso2;
	}

	//Crea el vector que va a tener la circunferencia rotada
	float circunferenciaactual[pasotoroide*3];

	//Crea el vector que va a tener la circunferencia que se roto anteriormente y le da como valor inicial la circunferencia original
	float circunferenciaanterior[pasotoroide*3];

	for(int i = 0; i < (pasotoroide*3); i+=1)
	{
		circunferenciaanterior[i] = circunferencia[i];
	}

	//Comienza, para cada angulo
	float paso1 = (2*PI)/20.0;
	for(float angulo1 = 0; angulo1 < ((2*PI)+paso1); angulo1 += paso1)
	{
		//Recorre de a tres puntos, para cada uno lo rota en el eje z y lo guarda en el vector que tiene la circunferencia modificada
		for(int vertice2 = 0; vertice2 < (pasotoroide*3); vertice2 += 3)
		{
			float xmod, ymod;
			x = circunferencia[vertice2];
			y = circunferencia[vertice2+1];
			z = circunferencia[vertice2+2];
			
			xmod=(cos(angulo1)*x)-(sin(angulo1)*y);
			ymod=(sin(angulo1)*x)+(cos(angulo1)*y);
			x = xmod;
			y = ymod;

			circunferenciaactual[vertice2] = x;
			circunferenciaactual[vertice2+1] = y;
			circunferenciaactual[vertice2+2] = z;
		}
		
		//Ahora tiene la circunferencia actual y la anterior, recorre de a tres puntos y usando el siguiente dibuja un cuadrado

		for(int vertice2 = 0; vertice2 < (pasotoroide*3); vertice2 += 3)
		{
			float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;

			//El proximo vertice empieza en 3 posiciones

			int verticeprox = vertice2 + 3;

			//Si el proximo vertice en su tercera posicion alcanza la cantidad de vertices del toroide se usa el vertice 0
			if((verticeprox+2) >= (pasotoroide*3)) verticeprox = 0;

			x1 = circunferenciaactual[vertice2];
			y1 = circunferenciaactual[vertice2+1];
			z1 = circunferenciaactual[vertice2+2];

			x2 = circunferenciaanterior[vertice2];
			y2 = circunferenciaanterior[vertice2+1];
			z2 = circunferenciaanterior[vertice2+2];

			x3 = circunferenciaanterior[verticeprox];
			y3 = circunferenciaanterior[verticeprox+1];
			z3 = circunferenciaanterior[verticeprox+2];

			x4 = circunferenciaactual[verticeprox];
			y4 = circunferenciaactual[verticeprox+1];
			z4 = circunferenciaactual[verticeprox+2];

			myWindow::drawTriangle(x1,y1,z1,x2,y2,z2,x3,y3,z3,colorData);
			myWindow::drawTriangle(x1,y1,z1,x4,y4,z4,x3,y3,z3,colorData);
		}

		//Se copia la circunferencia actual en la anterior

		for(int i = 0; i < (pasotoroide*3); i+=1)
		{
			circunferenciaanterior[i] = circunferenciaactual[i];
		}
	}
}

void myWindow::OnRender(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	rotationMatrix = glm::rotate((glm::rotate(mat4(1.0f), angley, vec3(1.0f,0.0f,0.0f))), anglex, vec3(0.0f,1.0f,0.0f));

	myWindow::drawToroide(0.35,0.1,1.0,0.0,0.0);
    //gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //glutWireTeapot(1.0);
	glutSwapBuffers();
}

void  myWindow::OnIdle()
{
}

// When OnInit is called, a render context (in this case GLUT-Window) 
// is already available!
void  myWindow::OnInit()
{
	glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

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
