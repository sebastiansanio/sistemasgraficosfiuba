#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include <myWindow.h>
   
#include <iostream>
#include <fstream>

#include <math.h>

using glm::mat4;
using glm::vec3;

GLuint positionBufferHandle;

GLuint colorBufferHandle;

GLuint programHandle;

float anguloy = 0;
float angulox = 0;
int xpresionado = 0;
int ypresionado = 0;

const char* loadShaderAsString(const char* file)
{
    std::ifstream shader_file(file, std::ifstream::in);
    std::string str((std::istreambuf_iterator<char>(shader_file)), std::istreambuf_iterator<char>());
    return str.c_str();
}

myWindow::myWindow()
{
}

void myWindow::dibujarCuadrado()
{
		GLuint vaoHandle;
	float positionData[] = {
		-0.5, 0.5, -0.5,
		-0.5, -0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, 0.5, -0.5,
		-0.5, 0.5, -0.5,
		-0.5, 0.5, -0.5,
		-0.5, -0.5, -0.5,
		-0.5, -0.5, 0.5,
		-0.5, -0.5, 0.5,
		-0.5, 0.5, 0.5,
		-0.5, 0.5, -0.5,
		-0.5, 0.5, 0.5,
		-0.5, -0.5, 0.5,
		0.5, -0.5, 0.5,
		-0.5, 0.5, 0.5,
		0.5, 0.5, 0.5,
		0.5, -0.5, 0.5,
		0.5, -0.5, 0.5,
		0.5, 0.5, 0.5,
		0.5, 0.5, -0.5,
		0.5, -0.5, 0.5,
		0.5, -0.5, -0.5,
		0.5, 0.5, -0.5,
		-0.5, 0.5, -0.5,
		-0.5, 0.5, 0.5,
		0.5, 0.5, 0.5,
		-0.5, 0.5, -0.5,
		0.5, 0.5, -0.5,
		0.5, 0.5, 0.5,
		-0.5, -0.5, -0.5,
		-0.5, -0.5, 0.5,
		0.5, -0.5, 0.5,
		-0.5, -0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, -0.5, 0.5,
	};

	float colorData[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f
	};

	// Create the buffer objects
	GLuint vboHandles[2];
	glGenBuffers(2, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint colorBufferHandle = vboHandles[1];
	// Populate the position buffer
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), positionData, GL_STATIC_DRAW);
	// Populate the color buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), colorData, GL_STATIC_DRAW);
	// Create and set-up the vertex array object
	glGenVertexArrays( 1, &vaoHandle );
	glBindVertexArray(vaoHandle);
	// Enable the vertex attribute arrays
	glEnableVertexAttribArray(0); // Vertex position
	glEnableVertexAttribArray(1); // Vertex color
	// Map index 0 to the position buffer
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
	// Map index 1 to the color buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );

	glClear(GL_COLOR_BUFFER_BIT);
	mat4 rotationMatrixy = mat4(1.0f);
	rotationMatrixy = glm::rotate( rotationMatrixy, anguloy, glm::vec3(0.0f,1.0f,0.0f) );
	GLuint location1 =glGetUniformLocation(programHandle, "RotationMatrixy");
	if( location1 >= 0 )
	{
		glUniformMatrix4fv(location1, 1, GL_FALSE, &rotationMatrixy[0][0]);
	}

	mat4 rotationMatrixx = mat4(1.0f);
	rotationMatrixx = glm::rotate( rotationMatrixx, angulox, glm::vec3(1.0f,0.0f,0.0f) );
	GLuint location2 =glGetUniformLocation(programHandle, "RotationMatrixx");
	if( location2 >= 0 )
	{
		glUniformMatrix4fv(location2, 1, GL_FALSE, &rotationMatrixx[0][0]);
	}


    glBindVertexArray( vaoHandle );
    glDrawArrays( GL_TRIANGLES, 0, 36);
}

void myWindow::OnRender(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	myWindow::dibujarCuadrado();
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
	xpresionado = x;
	ypresionado = y;
}

void myWindow::OnMouseUp(int button, int x, int y)
{
	anguloy += (x - xpresionado)/2;
	angulox += (y - ypresionado)/2;
	angulox = fmodf(angulox, 360.0);
	anguloy = fmodf(anguloy, 360.0);
}

void myWindow::OnMouseWheel(int nWheelNumber, int nDirection, int x, int y)
{
}

void myWindow::OnKeyDown(int nKey, char cAscii)
{       
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
