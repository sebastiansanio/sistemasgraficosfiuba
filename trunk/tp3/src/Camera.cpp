/*
 * Camera.cpp
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#include "Camera.h"

Camera* Camera::instance = 0;// Inicializar el puntero
Camera* Camera::Instance ()
{
  if (instance == 0)  // ¿Es la primera llamada?
  {
    instance = new Camera(); // Creamos la instancia
  }
  return instance; // Retornamos la dirección de la instancia
}

Camera::Camera() {
	ratio=10.0f;
	anglehor=0.0f;
	anglevert= 3.1416/2; //(3.1416 * 3) / 4;

	inverseTemp = new float*[4];
	for(int i=0;i<4; i++){
		inverseTemp[i] = new float[4];
	}

	matrixTemp = new float*[4];
	for(int i=0;i<4; i++){
		matrixTemp[i] = new float[4];
	}

	calcPosition();
}

void Camera::setPosition(){
	gluLookAt(eye[0],eye[1],eye[2],at[0],at[1],at[2],up[0],up[1],up[2]);
	glGetFloatv (GL_MODELVIEW_MATRIX, viewMatrix);
	invertViewMatrix();
}

float* Camera::transformViewCoord(float x, float y, float z){
	//cout << "xyz: " << x << " " << y << " " << z << endl;
	transf[0] = (viewMatrix[0] * x) + (viewMatrix[4] * y) + (viewMatrix[8] * z) + viewMatrix[12];
	transf[1] = (viewMatrix[1] * x) + (viewMatrix[5] * y) + (viewMatrix[9] * z) + viewMatrix[13];
	transf[2] = (viewMatrix[2] * x) + (viewMatrix[6] * y) + (viewMatrix[10] * z) + viewMatrix[14];

	/*cout << "eyepos: " << transf[0] << " " << transf[1] << " " << transf[2] << endl;

	x = (inverseViewMatrix[0] * transf[0]) + (inverseViewMatrix[4] * transf[1]) + (inverseViewMatrix[8] * transf[2]) + inverseViewMatrix[12];
	y = (inverseViewMatrix[1] * transf[0]) + (inverseViewMatrix[5] * transf[1]) + (inverseViewMatrix[9] * transf[2]) + inverseViewMatrix[13];
	z = (inverseViewMatrix[2] * transf[0]) + (inverseViewMatrix[6] * transf[1]) + (inverseViewMatrix[10] * transf[2]) + inverseViewMatrix[14];

	cout << "xyz2: " << x << " " << y << " " << z << endl;*/

	return transf;
}

void Camera::invertViewMatrix(){

	for(int i=0; i<4 ; i++){
		for(int j=0; j<4 ; j++){
			matrixTemp[i][j]=viewMatrix[i+(4*j)];
		}
	}

	MatrixInversion(matrixTemp,4,inverseTemp);

	for(int i=0; i<4 ; i++){
		for(int j=0; j<4 ; j++){
			inverseViewMatrix[i+(4*j)] = inverseTemp[i][j];
		}
	}
}

// matrix inversion
// the result is put in Y
void Camera::MatrixInversion(float **A, int order, float **Y)
{
    // get the determinant of a
    double det = 1.0/CalcDeterminant(A,order);

    // memory allocation
    float *temp = new float[(order-1)*(order-1)];
    float **minor = new float*[order-1];
    for(int i=0;i<order-1;i++)
        minor[i] = temp+(i*(order-1));

    for(int j=0;j<order;j++)
    {
        for(int i=0;i<order;i++)
        {
            // get the co-factor (matrix) of A(j,i)
            GetMinor(A,minor,j,i,order);
            Y[i][j] = det*CalcDeterminant(minor,order-1);
            if( (i+j)%2 == 1)
                Y[i][j] = -Y[i][j];
        }
    }

    // release memory
    //delete [] minor[0];
    delete [] temp;
    delete [] minor;
}

// calculate the cofactor of element (row,col)
int Camera::GetMinor(float **src, float **dest, int row, int col, int order)
{
    // indicate which col and row is being copied to dest
    int colCount=0,rowCount=0;

    for(int i = 0; i < order; i++ )
    {
        if( i != row )
        {
            colCount = 0;
            for(int j = 0; j < order; j++ )
            {
                // when j is not the element
                if( j != col )
                {
                    dest[rowCount][colCount] = src[i][j];
                    colCount++;
                }
            }
            rowCount++;
        }
    }

    return 1;
}

// Calculate the determinant recursively.
double Camera::CalcDeterminant( float **mat, int order)
{
    // order must be >= 0
	// stop the recursion when matrix is a single element
    if( order == 1 )
        return mat[0][0];

    // the determinant value
    float det = 0;

    // allocate the cofactor matrix
    float **minor;
    minor = new float*[order-1];
    for(int i=0;i<order-1;i++)
        minor[i] = new float[order-1];

    for(int i = 0; i < order; i++ )
    {
        // get minor of element (0,i)
        GetMinor( mat, minor, 0, i , order);
        // the recusion is here!

        det += (i%2==1?-1.0:1.0) * mat[0][i] * CalcDeterminant(minor,order-1);
        //det += pow( -1.0, i ) * mat[0][i] * CalcDeterminant( minor,order-1 );
    }

    // release memory
    for(int i=0;i<order-1;i++)
        delete [] minor[i];
    delete [] minor;

    return det;
}

void Camera::upz(){
	anglevert+=0.05;
	if(anglevert > 3.14) anglevert = 3.14;
	calcPosition();
}
void Camera::downz(){
	anglevert-=0.05;
	if(anglevert < 0.05) anglevert = 0.05;
	calcPosition();
}
void Camera::left(){
	anglehor-=0.05;
	if(anglehor < 0) anglehor = (3.14 * 2);
	calcPosition();
}

void Camera::right(){
	anglehor+=0.05;
	if(anglehor > (3.14 * 2)) anglehor = 0;
	calcPosition();
}

void Camera::nearRatio(){
	ratio-=0.2;
	if(ratio < 0.2) ratio = 0.2;
	calcPosition();
}

void Camera::farRatio(){
	ratio+=0.2;
	calcPosition();
}

void Camera::calcPosition(){
	eye[0]= ratio * cos(anglehor) * sin(anglevert);
	eye[1]= ratio * sin(anglehor) * sin(anglevert);
	eye[2]= -ratio * cos(anglevert);

	at[0] = 0.0;
	at[1] = 0.0;
	at[2] = 5.0;

	up[0] = 0.0;
	up[1] = 0.0;
	up[2] = 1.0;
}

Camera::~Camera() {
	for(int i=0;i<4; i++){
		delete [] matrixTemp[i];
	}

	delete [] matrixTemp;

	for(int i=0;i<4; i++){
		delete [] inverseTemp[i];
	}

	delete [] inverseTemp;
}

