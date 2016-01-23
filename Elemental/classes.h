#ifndef CLASSES_H
#define CLASSES_H

#include "define.h"

class cPlayer
{
private:
	
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int frame;
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int animationColumns;
	int animationDirection;
public:
	ALLEGRO_BITMAP * playerPNG = NULL;
	cPlayer();
	void loadPNG();
	
	int X(); //get x
	int Y(); // get y
	void changeX(float X); //change x
	void changeY(float Y);
	void update();
	void draw();
};
class cTile
{
private:

	int tile; //can take values of enum TILE_TYPE
	int tile_ID;//can take values of enum ID_TYPE
	int tile_state;//can take values of enum TILE_STATE
	int object; //can take value of TILE_OBJECT
	int object_ID;//can take value of ID_OBJECT

public:

	cTile();
	cTile(int t, int ti, int s, int o, int oi); //constructor

	void draw(ALLEGRO_BITMAP *BMP); //draw it to screen
	
	void changeTile(int temp); //change "tile"
	void changeTileID(int temp);//changes "tile_ID"
	void changeTileState(int temp);//changes "state"
	void changeObject(int temp);//changes "object"
	void changeObjectID(int temp);//changes "object_ID"
	int getTile(); //get "tile"
	int getTileID();//get "tile_ID"
	int getTileState();//get "state"
	int getObject();//get "object"
	int getObjectID();//get "object_ID"
	void incTile(int temp); //increase "tile" and when reaches MAX_TILE_TYPES go to zero
	void incTileID(int temp);//increase "tile_ID" and when reaches MAX_TILE_ID go to zero
	void incObject(int temp);
	void setSegment(int t, int ti, int s,int o,int oi); //tile, tile_ID,state,object,object_ID


};

class cGame
{
private:
	ALLEGRO_BITMAP * tilesPNG = NULL;
	ALLEGRO_FONT * arial18 = NULL;
	ALLEGRO_FONT * arial10 = NULL;
	

public:
	cTile segment[MAP_X][MAP_Y];
	cPlayer player;
	cGame();
	void loadgraphics();
	void draw();//draw map on screen;
	void drawDoor(int x,int y);
	void show_debug(int mx, int my);//draw debug information about mouseover tile.
	void loadGame();
	void saveGame();
};
#endif
