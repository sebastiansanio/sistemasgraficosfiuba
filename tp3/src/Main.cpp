#include "Camera.h"
#include "Scene.h"
#include "Curves/BSpline.h"

int anchoVentana;
int altoVentana;

float ultPosMouseX = -1;
float ultPosMouseY = -1;

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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//BasicProgram::Instance();
}


void display(void)
{
	anchoVentana=1024;
	altoVentana=768;
	glViewport (0, 0, (GLsizei) anchoVentana, (GLsizei) altoVentana);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) anchoVentana/(GLfloat) altoVentana, 0.10, 100.0);
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
	anchoVentana = w;
	altoVentana = h;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLdouble) w/(GLdouble) h, 0.10, 100.0);
}

void keyboard (unsigned char key, int x, int y) {
   switch (key) {
      case 'r':
         exit(0);
         break;
      case 'q':
    	  Camera::Instance()->upz();
    	  glutPostRedisplay();
    	  break;
      case 'e':
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
      case 'w':
    	  Camera::Instance()->forward();
		  glutPostRedisplay();
		  break;
      case 's':
    	  Camera::Instance()->backward();
		  glutPostRedisplay();
		  break;
      case 'z':
		  Camera::Instance()->toCaminante();
		  glutPostRedisplay();
		  break;
      case 'x':
		  Camera::Instance()->toCentro();
		  glutPostRedisplay();
		  break;
      case 'p':
		  Bullet::Instance()->addPack();
		  glutPostRedisplay();
		  break;
     default:
         break;
   }
}

void mouseClick(int button, int state, int x, int y) {
	ultPosMouseX = (x+0.0)/anchoVentana;
	ultPosMouseY = (y+0.0)/altoVentana;
}

void mouseMotion(int x, int y){
	float nuevoX = (x+0.0)/anchoVentana;
	float nuevoY = (y+0.0)/altoVentana;
	if(ultPosMouseX == -1 && ultPosMouseY == -1) {
		ultPosMouseX = nuevoX;
		ultPosMouseY = nuevoY;
	} else {
		//Toda la ventana son 180 grados
		float angleX = (nuevoX-ultPosMouseX) * 180;
		float angleY = (nuevoY-ultPosMouseY) * 180;
		ultPosMouseX = nuevoX;
		ultPosMouseY = nuevoY;
		Camera::Instance()->rotate(angleX,angleY);
	}

}

void timerFunc(int value){
	Scene::Instance()->advanceMotion();
	glutTimerFunc(30,timerFunc,0);
	glutPostRedisplay();

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
   glutTimerFunc(30,timerFunc,0);
   glutMotionFunc(mouseMotion);
   glutMouseFunc(mouseClick);

   //Inicializando GLEW
   GLenum err = glewInit();
   if( GLEW_OK != err ) {
	   fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(err) );
   }

  printVersion();

   //Iniciando la aplicacion
   init ();

   glutMainLoop();
   return 0;
}
