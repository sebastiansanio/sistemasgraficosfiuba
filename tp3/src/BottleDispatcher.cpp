#include "BottleDispatcher.h"
#include "Curves/Coordinate.h"

BottleDispatcher* BottleDispatcher::instance = 0;
BottleDispatcher* BottleDispatcher::Instance ()
{
  if (instance == 0)
  {
    instance = new BottleDispatcher();
  }
  return instance;
}


BottleDispatcher::BottleDispatcher(){

	double height = 6;
	double width = 2;
	double length = 3.5;

	double entranceHeightFromFloor = 0.7;
	double entranceHeight = 1.5;
	double entranceWidth = 1.2;

	double exitHeightFromFloor = 4.5;
	double exitHeight = 1.2;
	double exitWidth = 3;

	double entranceWidthLocation = (width-entranceWidth)/2;
	double exitWidthLocation = (length-exitWidth)/2;

	program = TextureProgram::Instance();
	trianglesEstimated = 24;

	this->positionArray = new float[trianglesEstimated*9];
	this->colorArray = new float[trianglesEstimated*9];
	this->normalArray = new float[trianglesEstimated*9];
	this->textureArray = new float[trianglesEstimated*6];

	int posCounter = 0;
	int texPosCounter = 0;

	Coordinate* frontNormal = new Coordinate(1,0,0);
	Coordinate* backNormal = new Coordinate(-1,0,0);
	Coordinate* leftNormal = new Coordinate(0,-1,0);
	Coordinate* rightNormal = new Coordinate(0,1,0);
	Coordinate* floorNormal = new Coordinate(0,0,-1);
	Coordinate* roofNormal = new Coordinate(0,0,1);

	//Floor
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=0;
	normalArray[posCounter]=floorNormal->getX();
	normalArray[posCounter+1]=floorNormal->getY();
	normalArray[posCounter+2]=floorNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=0;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1;
	normalArray[posCounter+3]=floorNormal->getX();
	normalArray[posCounter+4]=floorNormal->getY();
	normalArray[posCounter+5]=floorNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=0;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=0;
	normalArray[posCounter+6]=floorNormal->getX();
	normalArray[posCounter+7]=floorNormal->getY();
	normalArray[posCounter+8]=floorNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=0;
	normalArray[posCounter]=floorNormal->getX();
	normalArray[posCounter+1]=floorNormal->getY();
	normalArray[posCounter+2]=floorNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=0;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1;
	normalArray[posCounter+3]=floorNormal->getX();
	normalArray[posCounter+4]=floorNormal->getY();
	normalArray[posCounter+5]=floorNormal->getZ();

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=0;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=1;
	normalArray[posCounter+6]=floorNormal->getX();
	normalArray[posCounter+7]=floorNormal->getY();
	normalArray[posCounter+8]=floorNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;


	//Roof
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=height;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=0;
	normalArray[posCounter]=roofNormal->getX();
	normalArray[posCounter+1]=roofNormal->getY();
	normalArray[posCounter+2]=roofNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1;
	normalArray[posCounter+3]=roofNormal->getX();
	normalArray[posCounter+4]=roofNormal->getY();
	normalArray[posCounter+5]=roofNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=1;
	normalArray[posCounter+6]=roofNormal->getX();
	normalArray[posCounter+7]=roofNormal->getY();
	normalArray[posCounter+8]=roofNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=height;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=0;
	normalArray[posCounter]=roofNormal->getX();
	normalArray[posCounter+1]=roofNormal->getY();
	normalArray[posCounter+2]=roofNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1;
	normalArray[posCounter+3]=roofNormal->getX();
	normalArray[posCounter+4]=roofNormal->getY();
	normalArray[posCounter+5]=roofNormal->getZ();

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=0;
	normalArray[posCounter+6]=roofNormal->getX();
	normalArray[posCounter+7]=roofNormal->getY();
	normalArray[posCounter+8]=roofNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	//Back
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=1-0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=backNormal->getX();
	normalArray[posCounter+1]=backNormal->getY();
	normalArray[posCounter+2]=backNormal->getZ();

	positionArray[posCounter+3]=0;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=0;
	textureArray[texPosCounter+2]=1-1;
	textureArray[texPosCounter+3]=1-0;
	normalArray[posCounter+3]=backNormal->getX();
	normalArray[posCounter+4]=backNormal->getY();
	normalArray[posCounter+5]=backNormal->getZ();

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=1-1;
	textureArray[texPosCounter+5]=1-1;
	normalArray[posCounter+6]=backNormal->getX();
	normalArray[posCounter+7]=backNormal->getY();
	normalArray[posCounter+8]=backNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=1-0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=backNormal->getX();
	normalArray[posCounter+1]=backNormal->getY();
	normalArray[posCounter+2]=backNormal->getZ();

	positionArray[posCounter+3]=0;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1-1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=backNormal->getX();
	normalArray[posCounter+4]=backNormal->getY();
	normalArray[posCounter+5]=backNormal->getZ();

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=1-0;
	textureArray[texPosCounter+5]=1-1;
	normalArray[posCounter+6]=backNormal->getX();
	normalArray[posCounter+7]=backNormal->getY();
	normalArray[posCounter+8]=backNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;


	//Lateral
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=leftNormal->getX();
	normalArray[posCounter+1]=leftNormal->getY();
	normalArray[posCounter+2]=leftNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=0;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=leftNormal->getX();
	normalArray[posCounter+4]=leftNormal->getY();
	normalArray[posCounter+5]=leftNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=0;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=1-0;
	normalArray[posCounter+6]=leftNormal->getX();
	normalArray[posCounter+7]=leftNormal->getY();
	normalArray[posCounter+8]=leftNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=leftNormal->getX();
	normalArray[posCounter+1]=leftNormal->getY();
	normalArray[posCounter+2]=leftNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=0;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=leftNormal->getX();
	normalArray[posCounter+4]=leftNormal->getY();
	normalArray[posCounter+5]=leftNormal->getZ();

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=1-1;
	normalArray[posCounter+6]=leftNormal->getX();
	normalArray[posCounter+7]=leftNormal->getY();
	normalArray[posCounter+8]=leftNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	//Other lateral down
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=width;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=1-0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=rightNormal->getX();
	normalArray[posCounter+1]=rightNormal->getY();
	normalArray[posCounter+2]=rightNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=exitHeightFromFloor;
	textureArray[texPosCounter+2]=1-1;
	textureArray[texPosCounter+3]=1-exitHeightFromFloor/height;
	normalArray[posCounter+3]=rightNormal->getX();
	normalArray[posCounter+4]=rightNormal->getY();
	normalArray[posCounter+5]=rightNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=0;
	textureArray[texPosCounter+4]=1-1;
	textureArray[texPosCounter+5]=1-0;
	normalArray[posCounter+6]=rightNormal->getX();
	normalArray[posCounter+7]=rightNormal->getY();
	normalArray[posCounter+8]=rightNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=width;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=1-0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=rightNormal->getX();
	normalArray[posCounter+1]=rightNormal->getY();
	normalArray[posCounter+2]=rightNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=exitHeightFromFloor;
	textureArray[texPosCounter+2]=1-1;
	textureArray[texPosCounter+3]=1-exitHeightFromFloor/height;
	normalArray[posCounter+3]=rightNormal->getX();
	normalArray[posCounter+4]=rightNormal->getY();
	normalArray[posCounter+5]=rightNormal->getZ();

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=exitHeightFromFloor;
	textureArray[texPosCounter+4]=1-0;
	textureArray[texPosCounter+5]=1-exitHeightFromFloor/height;
	normalArray[posCounter+6]=rightNormal->getX();
	normalArray[posCounter+7]=rightNormal->getY();
	normalArray[posCounter+8]=rightNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;


	//Other lateral up
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=width;
	positionArray[posCounter+2]=exitHeightFromFloor+exitHeight;
	textureArray[texPosCounter]=1-0;
	textureArray[texPosCounter+1]=1-(exitHeightFromFloor+exitHeight)/height;
	normalArray[posCounter]=rightNormal->getX();
	normalArray[posCounter+1]=rightNormal->getY();
	normalArray[posCounter+2]=rightNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1-1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=rightNormal->getX();
	normalArray[posCounter+4]=rightNormal->getY();
	normalArray[posCounter+5]=rightNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=exitHeightFromFloor+exitHeight;
	textureArray[texPosCounter+4]=1-1;
	textureArray[texPosCounter+5]=1-(exitHeightFromFloor+exitHeight)/height;
	normalArray[posCounter+6]=rightNormal->getX();
	normalArray[posCounter+7]=rightNormal->getY();
	normalArray[posCounter+8]=rightNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=width;
	positionArray[posCounter+2]=exitHeightFromFloor+exitHeight;
	textureArray[texPosCounter]=1-0;
	textureArray[texPosCounter+1]=1-(exitHeightFromFloor+exitHeight)/height;
	normalArray[posCounter]=rightNormal->getX();
	normalArray[posCounter+1]=rightNormal->getY();
	normalArray[posCounter+2]=rightNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1-1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=rightNormal->getX();
	normalArray[posCounter+4]=rightNormal->getY();
	normalArray[posCounter+5]=rightNormal->getZ();

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=1-0;
	textureArray[texPosCounter+5]=1-1;
	normalArray[posCounter+6]=rightNormal->getX();
	normalArray[posCounter+7]=rightNormal->getY();
	normalArray[posCounter+8]=rightNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	//Other lateral left
	positionArray[posCounter]=exitWidthLocation+exitWidth;
	positionArray[posCounter+1]=width;
	positionArray[posCounter+2]=exitHeightFromFloor;
	textureArray[texPosCounter]=1-(exitWidthLocation+exitWidth)/length;
	textureArray[texPosCounter+1]=1-exitHeightFromFloor/height;
	normalArray[posCounter]=rightNormal->getX();
	normalArray[posCounter+1]=rightNormal->getY();
	normalArray[posCounter+2]=rightNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=exitHeightFromFloor+exitHeight;
	textureArray[texPosCounter+2]=1-1;
	textureArray[texPosCounter+3]=1-(exitHeightFromFloor+exitHeight)/height;
	normalArray[posCounter+3]=rightNormal->getX();
	normalArray[posCounter+4]=rightNormal->getY();
	normalArray[posCounter+5]=rightNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=exitHeightFromFloor;
	textureArray[texPosCounter+4]=1-1;
	textureArray[texPosCounter+5]=1-exitHeightFromFloor/height;
	normalArray[posCounter+6]=rightNormal->getX();
	normalArray[posCounter+7]=rightNormal->getY();
	normalArray[posCounter+8]=rightNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=exitWidthLocation+exitWidth;
	positionArray[posCounter+1]=width;
	positionArray[posCounter+2]=exitHeightFromFloor;
	textureArray[texPosCounter]=1-(exitWidthLocation+exitWidth)/length;
	textureArray[texPosCounter+1]=1-exitHeightFromFloor/height;
	normalArray[posCounter]=rightNormal->getX();
	normalArray[posCounter+1]=rightNormal->getY();
	normalArray[posCounter+2]=rightNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=exitHeightFromFloor+exitHeight;
	textureArray[texPosCounter+2]=1-1;
	textureArray[texPosCounter+3]=1-(exitHeightFromFloor+exitHeight)/height;
	normalArray[posCounter+3]=rightNormal->getX();
	normalArray[posCounter+4]=rightNormal->getY();
	normalArray[posCounter+5]=rightNormal->getZ();

	positionArray[posCounter+6]=exitWidthLocation+exitWidth;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=exitHeightFromFloor+exitHeight;
	textureArray[texPosCounter+4]=1-(exitWidthLocation+exitWidth)/length;
	textureArray[texPosCounter+5]=1-(exitHeightFromFloor+exitHeight)/height;
	normalArray[posCounter+6]=rightNormal->getX();
	normalArray[posCounter+7]=rightNormal->getY();
	normalArray[posCounter+8]=rightNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;


	//Other lateral Right
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=width;
	positionArray[posCounter+2]=exitHeightFromFloor;
	textureArray[texPosCounter]=1-0;
	textureArray[texPosCounter+1]=1-exitHeightFromFloor/height;
	normalArray[posCounter]=rightNormal->getX();
	normalArray[posCounter+1]=rightNormal->getY();
	normalArray[posCounter+2]=rightNormal->getZ();

	positionArray[posCounter+3]=exitWidthLocation;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=exitHeightFromFloor+exitHeight;
	textureArray[texPosCounter+2]=1-exitWidthLocation/length;
	textureArray[texPosCounter+3]=1-(exitHeightFromFloor+exitHeight)/height;
	normalArray[posCounter+3]=rightNormal->getX();
	normalArray[posCounter+4]=rightNormal->getY();
	normalArray[posCounter+5]=rightNormal->getZ();

	positionArray[posCounter+6]=exitWidthLocation;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=exitHeightFromFloor;
	textureArray[texPosCounter+4]=1-exitWidthLocation/length;
	textureArray[texPosCounter+5]=1-exitHeightFromFloor/height;
	normalArray[posCounter+6]=rightNormal->getX();
	normalArray[posCounter+7]=rightNormal->getY();
	normalArray[posCounter+8]=rightNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=width;
	positionArray[posCounter+2]=exitHeightFromFloor;
	textureArray[texPosCounter]=1-0;
	textureArray[texPosCounter+1]=1-exitHeightFromFloor/height;
	normalArray[posCounter]=rightNormal->getX();
	normalArray[posCounter+1]=rightNormal->getY();
	normalArray[posCounter+2]=rightNormal->getZ();

	positionArray[posCounter+3]=exitWidthLocation;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=exitHeightFromFloor+exitHeight;
	textureArray[texPosCounter+2]=1-exitWidthLocation/length;
	textureArray[texPosCounter+3]=1-(exitHeightFromFloor+exitHeight)/height;
	normalArray[posCounter+3]=rightNormal->getX();
	normalArray[posCounter+4]=rightNormal->getY();
	normalArray[posCounter+5]=rightNormal->getZ();

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=exitHeightFromFloor+exitHeight;
	textureArray[texPosCounter+4]=1-0;
	textureArray[texPosCounter+5]=1-(exitHeightFromFloor+exitHeight)/height;
	normalArray[posCounter+6]=rightNormal->getX();
	normalArray[posCounter+7]=rightNormal->getY();
	normalArray[posCounter+8]=rightNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	//Front down
	positionArray[posCounter]=length;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=frontNormal->getX();
	normalArray[posCounter+1]=frontNormal->getY();
	normalArray[posCounter+2]=frontNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=0;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-0;
	normalArray[posCounter+3]=frontNormal->getX();
	normalArray[posCounter+4]=frontNormal->getY();
	normalArray[posCounter+5]=frontNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=entranceHeightFromFloor;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=1-entranceHeightFromFloor/height;
	normalArray[posCounter+6]=frontNormal->getX();
	normalArray[posCounter+7]=frontNormal->getY();
	normalArray[posCounter+8]=frontNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=length;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=frontNormal->getX();
	normalArray[posCounter+1]=frontNormal->getY();
	normalArray[posCounter+2]=frontNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=entranceHeightFromFloor;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-entranceHeightFromFloor/height;
	normalArray[posCounter+3]=frontNormal->getX();
	normalArray[posCounter+4]=frontNormal->getY();
	normalArray[posCounter+5]=frontNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=entranceHeightFromFloor;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=1-entranceHeightFromFloor/height;
	normalArray[posCounter+6]=frontNormal->getX();
	normalArray[posCounter+7]=frontNormal->getY();
	normalArray[posCounter+8]=frontNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;



	//Front up
	positionArray[posCounter]=length;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter]=frontNormal->getX();
	normalArray[posCounter+1]=frontNormal->getY();
	normalArray[posCounter+2]=frontNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+3]=frontNormal->getX();
	normalArray[posCounter+4]=frontNormal->getY();
	normalArray[posCounter+5]=frontNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=1-1;
	normalArray[posCounter+6]=frontNormal->getX();
	normalArray[posCounter+7]=frontNormal->getY();
	normalArray[posCounter+8]=frontNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=length;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter]=frontNormal->getX();
	normalArray[posCounter+1]=frontNormal->getY();
	normalArray[posCounter+2]=frontNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=frontNormal->getX();
	normalArray[posCounter+4]=frontNormal->getY();
	normalArray[posCounter+5]=frontNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=1-1;
	normalArray[posCounter+6]=frontNormal->getX();
	normalArray[posCounter+7]=frontNormal->getY();
	normalArray[posCounter+8]=frontNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	//Front medium left
	positionArray[posCounter]=length;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=entranceHeightFromFloor;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-entranceHeightFromFloor/height;
	normalArray[posCounter]=frontNormal->getX();
	normalArray[posCounter+1]=frontNormal->getY();
	normalArray[posCounter+2]=frontNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=entranceWidthLocation;
	positionArray[posCounter+5]=entranceHeightFromFloor;
	textureArray[texPosCounter+2]=entranceWidthLocation/width;
	textureArray[texPosCounter+3]=1-entranceHeightFromFloor/height;
	normalArray[posCounter+3]=frontNormal->getX();
	normalArray[posCounter+4]=frontNormal->getY();
	normalArray[posCounter+5]=frontNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=entranceWidthLocation;
	positionArray[posCounter+8]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+4]=entranceWidthLocation/width;
	textureArray[texPosCounter+5]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+6]=frontNormal->getX();
	normalArray[posCounter+7]=frontNormal->getY();
	normalArray[posCounter+8]=frontNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=length;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=entranceHeightFromFloor;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-entranceHeightFromFloor/height;
	normalArray[posCounter]=frontNormal->getX();
	normalArray[posCounter+1]=frontNormal->getY();
	normalArray[posCounter+2]=frontNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=entranceWidthLocation;
	positionArray[posCounter+5]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+2]=entranceWidthLocation/width;
	textureArray[texPosCounter+3]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+3]=frontNormal->getX();
	normalArray[posCounter+4]=frontNormal->getY();
	normalArray[posCounter+5]=frontNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+6]=frontNormal->getX();
	normalArray[posCounter+7]=frontNormal->getY();
	normalArray[posCounter+8]=frontNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	//Front medium right
	positionArray[posCounter]=length;
	positionArray[posCounter+1]=entranceWidthLocation+entranceWidth;
	positionArray[posCounter+2]=entranceHeightFromFloor;
	textureArray[texPosCounter]=(entranceWidthLocation+entranceWidth)/width;
	textureArray[texPosCounter+1]=1-entranceHeightFromFloor/height;
	normalArray[posCounter]=frontNormal->getX();
	normalArray[posCounter+1]=frontNormal->getY();
	normalArray[posCounter+2]=frontNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=entranceHeightFromFloor;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-entranceHeightFromFloor/height;
	normalArray[posCounter+3]=frontNormal->getX();
	normalArray[posCounter+4]=frontNormal->getY();
	normalArray[posCounter+5]=frontNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+6]=frontNormal->getX();
	normalArray[posCounter+7]=frontNormal->getY();
	normalArray[posCounter+8]=frontNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=length;
	positionArray[posCounter+1]=entranceWidthLocation+entranceWidth;
	positionArray[posCounter+2]=entranceHeightFromFloor;
	textureArray[texPosCounter]=(entranceWidthLocation+entranceWidth)/width;
	textureArray[texPosCounter+1]=1-entranceHeightFromFloor/height;
	normalArray[posCounter]=frontNormal->getX();
	normalArray[posCounter+1]=frontNormal->getY();
	normalArray[posCounter+2]=frontNormal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+3]=frontNormal->getX();
	normalArray[posCounter+4]=frontNormal->getY();
	normalArray[posCounter+5]=frontNormal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=entranceWidthLocation+entranceWidth;
	positionArray[posCounter+8]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+4]=(entranceWidthLocation+entranceWidth)/width;
	textureArray[texPosCounter+5]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+6]=frontNormal->getX();
	normalArray[posCounter+7]=frontNormal->getY();
	normalArray[posCounter+8]=frontNormal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	delete backNormal;
	delete frontNormal;
	delete leftNormal;
	delete rightNormal;
	delete floorNormal;
	delete roofNormal;

	glGenBuffers(1, &bufferPositionHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 9) * sizeof (float), this->positionArray, GL_STATIC_DRAW );
	glGenBuffers(1, &bufferColorHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 9) * sizeof (float), this->colorArray, GL_STATIC_DRAW );
	glGenBuffers(1, &bufferNormalHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 9) * sizeof (float), this->normalArray, GL_STATIC_DRAW );
	glGenBuffers(1, &bufferTextureHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferTextureHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 6) * sizeof (float), this->textureArray, GL_STATIC_DRAW );

}

void BottleDispatcher::print(){
	program->setTexture(4);
	program->setActualProgram();

	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glVertexAttribPointer( VERTEX_NOR_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glVertexAttribPointer( VERTEX_COL_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glVertexAttribPointer( VERTEX_POS_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferTextureHandler);
	glVertexAttribPointer( VERTEX_TEX_ATTR_INDEX, 2 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glDrawArrays( GL_TRIANGLES, 0, trianglesEstimated * 3);

}

BottleDispatcher::~BottleDispatcher(){

}
