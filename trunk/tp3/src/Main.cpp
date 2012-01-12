#include "Camera.h"
#include "Scene.h"

void OnIdle (void)
{
}

void printVersion(){
	const GLubyte *renderer = glGetString( GL_RENDERER );
	const GLubyte *vendor = glGetString( GL_VENDOR );
	const GLubyte *version = glGetString( GL_VERSION );
	const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf("GL Vendor : %s\n", vendor);
	printf("GL Renderer : %s\n", renderer);
	printf("GL Version (string) : %s\n", version);
	printf("GL Version (integer) : %d.%d\n", major, minor);
	printf("GLSL Version : %s\n", glslVersion);
}

void init(void)
{
	glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	BasicProgram::Instance();
}


void display(void)
{
	glViewport (0, 0, (GLsizei) 1024, (GLsizei) 768);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) 1024/(GLfloat) 768, 0.10, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/

	Camera::Instance()->setPosition();

	Scene::Instance()->printScene();

	/*BasicProgram::Instance()->updateModelViewProjection();
	BasicProgram::Instance()->drawTriangle();*/

	glutSwapBuffers();
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLdouble) w/(GLdouble) h, 0.10, 100.0);
}

void keyboard (unsigned char key, int x, int y) {
   switch (key) {
      case 'q':
         exit(0);
         break;
      case 'w':
    	  Camera::Instance()->upz();
    	  glutPostRedisplay();
    	  break;
      case 's':
    	  Camera::Instance()->downz();
		  glutPostRedisplay();
		  break;
      case 'a':
    	  Camera::Instance()->left();
		  glutPostRedisplay();
		  break;
      case 'd':
    	  Camera::Instance()->right();
		  glutPostRedisplay();
		  break;
      case 'z':
    	  Camera::Instance()->nearRatio();
		  glutPostRedisplay();
		  break;
      case 'x':
    	  Camera::Instance()->farRatio();
		  glutPostRedisplay();
		  break;
      case 'e':
    	  BasicProgram::Instance()->setPositionValue(0,-0.5);
    	  BasicProgram::Instance()->setPositionValue(3,0.5);
    	  BasicProgram::Instance()->setPositionValue(7,0.5);
    	  BasicProgram::Instance()->setColorValue(0,1.0);
    	  BasicProgram::Instance()->setColorValue(2,1.0);
    	  BasicProgram::Instance()->setColorValue(4,1.0);
    	  BasicProgram::Instance()->setColorValue(6,1.0);
    	  BasicProgram::Instance()->setColorValue(8,1.0);
    	  glutPostRedisplay();
    	  break;
     default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (1024, 768);
   glutInitWindowPosition (0, 0);

   glutCreateWindow (argv[0]);
   //glutFullScreen();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(OnIdle);

   //Inicializando GLEW
   GLenum err = glewInit();
   if( GLEW_OK != err ) {
	   fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(err) );
   }

   //Iniciando la aplicacion
   init ();

   glutMainLoop();
   return 0;
}
