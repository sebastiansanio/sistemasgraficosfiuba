#pragma once

#include <glutwindow.h>

class myWindow : public cwc::glutWindow
{
public:
	myWindow();

	virtual void OnRender(void);
	virtual void OnIdle();

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit();

	virtual void OnResize(int w, int h);
	virtual void OnClose(void);
	virtual void OnMouseDown(int button, int x, int y);
	virtual void OnMouseUp(int button, int x, int y);
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y);

	virtual void OnKeyDown(int nKey, char cAscii);

	virtual void OnKeyUp(int nKey, char cAscii);

	void drawToroide(float radio1, float radio2, float r, float g, float b);

	void drawTriangle(float r, float g, float b);

	void drawRectangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, float r, float g, float b);

	void drawCube(float lado, float r, float g, float b);

	void drawEsfera(float radio, float r, float g, float b);

	void drawCilindro(float radio, float altura, float r, float g, float b);

	void drawTapaCilindro(float radio, float altura, float r, float g, float b);
};