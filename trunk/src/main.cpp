///
/// 66.71 Sistemas Graficos
/// Framework de trabajo para el TP1
/// 2do Cuatrimestre 2011
///
/// info@sg6671.com.ar
///

#include <GL/glut.h>
#include <math.h>
#include "arbol.h"
#include "suelo.h"

float angulo=0;
float radio= 21;
arbol* arbol1;
float posX = -1;
float posY = -1;

// Variables que controlan la ubicación de la cámara en la Escena 3D
float eye[3] = {21.0, 0.0, 5.0};
float at[3]  = { 0.0,  0.0, 0.0};
float up[3]  = { 0.0,  0.0, 1.0};

// Variables asociadas a única fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {10.0f, 10.0f, 8.0f};
float light_ambient[4] = {0.05f, 0.05f, 0.05f, 1.0f};

// Color de la esfera en movimiento dentro de la escena
float color_esfera[4] = {0.5f, 0.5f, 0.2f, 1.0f};

// Variable asociada al movimiento de rotación de la esfera alrededor del eje Z
float rotate_sphere = 0;

// Variables de control
bool view_grid = false;
bool view_axis = false;
bool edit_panel = false;


// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)

// Tamaño de la ventana
GLfloat window_size[2];
#define W_WIDTH window_size[0]
#define W_HEIGHT window_size[1]

#define TOP_VIEW_POSX	((int)((float)W_WIDTH*0.60f))
#define TOP_VIEW_W		((int)((float)W_WIDTH*0.40f))
#define TOP_VIEW_POSY	((int)((float)W_HEIGHT*0.60f))
#define TOP_VIEW_H		((int)((float)W_HEIGHT*0.40f))

void arrows(int key, int x, int y)
{
    switch (key)
    {
	  case 100:
		  if(up[1]!=1){
			  angulo=angulo-0.1;
			  eye[0] = radio*cos(angulo);
			  eye[1]= radio*sin(angulo);
			  glutPostRedisplay();
		  }
		  break;

	  case 102:
		  if(up[1]!=1){
			  angulo=angulo+0.1;
			  eye[0] = radio*cos(angulo);
			  eye[1]= radio*sin(angulo);
			  glutPostRedisplay();
		  }
		  break;

	  case 101:
		  if(radio>=2){
			  radio -= 0.5;
			  eye[0] = radio*cos(angulo);
			  eye[1]= radio*sin(angulo);
			  glutPostRedisplay();
		  }
	  	  break;

	  case 103:
		  radio += 0.5;
		  eye[0] = radio*cos(angulo);
		  eye[1]= radio*sin(angulo);
	  	  glutPostRedisplay();
	  	  break;
	  default:
		  break;
    }
}


void DrawAxis()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		// X
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(15.0, 0.0, 0.0);
		// Y
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 15.0, 0.0);
		// Z
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 15.0);
	glEnd();
	glEnable(GL_LIGHTING);
}

void DrawAxis2DTopView()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
		// X
		glColor3f(0.0f, 0.5f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.1f, 0.1f, 0.1f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glEnable(GL_LIGHTING);
}


void DrawXYGrid()
{
	int i;
	glDisable(GL_LIGHTING);
	glColor3f(0.25f, 0.2f, 0.2f);
	glBegin(GL_LINES);
	for(i=-20; i<21; i++)
	{
		glVertex3f((float)i, -20.0f, 0.0f);
		glVertex3f((float)i,  20.0f, 0.0f);
		glVertex3f(-20.0f, (float)i, 0.0f);
		glVertex3f( 20.0f, (float)i, 0.0f);
	}
	glEnd();
	glEnable(GL_LIGHTING);
}


void Set3DEnv()
{
	glViewport (0, 0, (GLsizei) W_WIDTH, (GLsizei) W_HEIGHT);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) W_WIDTH/(GLfloat) W_HEIGHT, 0.10, 100.0);
}

void SetPanelTopEnv()
{
	glViewport (TOP_VIEW_POSX, TOP_VIEW_POSY, (GLsizei) TOP_VIEW_W, (GLsizei) TOP_VIEW_H);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
	gluOrtho2D(-0.10, 1.05, -0.10, 1.05);
}


void init(void)
{

	dl_handle = glGenLists(3);

	glClearColor (0.02f, 0.02f, 0.04f, 0.0f);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

	// Generación de las Display Lists
	glNewList(DL_AXIS, GL_COMPILE);
		DrawAxis();
	glEndList();
	glNewList(DL_GRID, GL_COMPILE);
		DrawXYGrid();
	glEndList();
	glNewList(DL_AXIS2D_TOP, GL_COMPILE);
		DrawAxis2DTopView();
	glEndList();
}



void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///////////////////////////////////////////////////
	// Escena 3D
	Set3DEnv();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);

	if (view_axis)
		glCallList(DL_AXIS);

	if (view_grid)
		glCallList(DL_GRID);


	//
	///////////////////////////////////////////////////

    ///////////////////////////////////////////////////
	//
	// Draw here
	//
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	suelo::dibujar();
	arbol1->dibujar();

	//
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	// Panel 2D para la vista superior
	if (edit_panel)
	{
		SetPanelTopEnv();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt (0, 0, 0.5, 0, 0, 0, 0, 1, 0);
		glCallList(DL_AXIS2D_TOP);
	}
	//
	///////////////////////////////////////////////////



	glutSwapBuffers();
}

void reshape (int w, int h)
{
   	W_WIDTH  = (float)w;
	W_HEIGHT = (float)h;
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'e':
         exit(0);
         break;
//
//	  case 'g':
//		  view_grid = !view_grid;
//		  glutPostRedisplay();
//		  break;
//
//	  case 'a':
//		  view_axis = !view_axis;
//		  glutPostRedisplay();
//		  break;
//
//	  case 'e':
//		  edit_panel = !edit_panel;
//		  glutPostRedisplay();
//		  break;
//
//	  case 'w':
//		  arbol1->envejecer();
//		  glutPostRedisplay();
//	  	  break;

	  case 'r':
		  delete arbol1;
		  arbol1=new arbol(1.0,0.1,0,0);
		  break;

	  case 'p':
		  arbol1->crecimiento();
		  break;

	  case 'q':
		  arbol1->aumentarCrecimiento();
		  break;

	  case 'a':
		  arbol1->disminuirCrecimiento();
		  break;

     default:
         break;
   }
}

void mouseRotacion(int x,int y){

	if (posX==-1){
		posX = x;
		posY = y;

	}
	else{
		  angulo+=((x-posX)/100);
		  eye[0] = radio*cos(angulo);
		  eye[1]= radio*sin(angulo);
		  posX=x;
		  posY=y;
		  glutPostRedisplay();
	}
}

void mouseInclinacion(int x,int y){
	if (posX==-1){
		posX = x;
		posY = y;

	}
	else{
		  angulo+=((x-posX)/100);
		  eye[0] = radio*cos(angulo);
		  eye[1]= radio*sin(angulo);
		  eye[2]+=((posY-y)/5);
		  if(eye[2]<0)
			  eye[2]=0.5;
		  posY=y;
		  posX=x;

		  glutPostRedisplay();
	}
}

void tiempo(int value){
	  arbol1->envejecer();
	  glutTimerFunc(50,tiempo,0);
	  glutPostRedisplay();
}

int main(int argc, char** argv)
{

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (1024, 768);
   glutInitWindowPosition (0, 0);

   glutCreateWindow ("Sistemas Graficos");
   //glutFullScreen();
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(arrows);
   glutPassiveMotionFunc(mouseRotacion);
   glutMotionFunc(mouseInclinacion);
   glutTimerFunc(50,tiempo,0);

   suelo::inicializar();
   arbol1=new arbol(1.0,0.1,0,0);

   glClearColor(0.0,0.6,0.7,0.0);
   glutMainLoop();
   return 0;
}
