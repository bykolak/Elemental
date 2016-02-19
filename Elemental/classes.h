#ifndef CLASSES_H
#define CLASSES_H

#include "define.h"

class cSprite
{
	friend class cTile;
	friend class cGame;
private:
	
	int x;//segment x where sprite is
	int y;//segment y where sprite is
	int maxFrame;// maximum number of frames (usually 5)
	int frame;// 
	int curFrame;//current frame
	int frameCount;
	int frameDelay;
	int animationDirection;//
	
public:
	bool moving;
	int posX;
	int posY;
	ALLEGRO_BITMAP * playerPNG = NULL;
	int orderX;
	int orderY;
	cSprite();
	void loadPNG();
	int X(); //get x
	int Y(); // get y
	void incX(int value);//increase x by value
	void incY(int value);//increase y by value
	void setX(int X); //change x
	void setY(int Y);
	void update();
	void draw();

};
class cTile
{
	friend class cGame;
	friend class cSprite;
private:

	int tile; //can take values of enum TILE_TYPE
	int tile_ID;//can take values of enum ID_TYPE
	int tile_state;//can take values of enum TILE_STATE
	int object; //can take value of TILE_OBJECT
	int object_ID;//can take value of ID_OBJECT
	int status;
	int frameCount;
	int frameDelay;
	int animationDirection;
public:
	int maxFrame;
	int curFrame;
	cTile();
	cTile(int t, int ti, int s, int o, int oi,int stat); //constructor
	
	void draw(ALLEGRO_BITMAP *BMP); //draw it to screen
	void change(int value, int tile_vars); //changes all private vars of cTile use tile_vars with enum TILE_VARS
	int get(int tile_vars);//returns all private vars of cTile use tile_vars with enum TILE_VARS
	void inc(int value, int tile_vars);//increase by value all private vars of cTile use tile_vars with enum TILE_VARS
	void set(int t, int ti, int s,int o,int oi,int st); //tile, tile_ID,state,object,object_ID,status
	void update(); //updates frames and 
	void setAnimation(int maxframe, int framedelay, int animationdirection); //sets all parameters regarding animation
};

class cGame
{
	friend class cTile;
	friend class cSprite;
private:
	ALLEGRO_BITMAP * tilesPNG = NULL;
	ALLEGRO_FONT * arial18 = NULL;
	ALLEGRO_FONT * arial10 = NULL;
	

public:
	bool collision[MAX_DIRECTION];
	int scrollX;
	int scrollY;
	int mx;
	int my;
	cTile segment[MAP_X][MAP_Y];
	cSprite sprite[MAX_SPRITES];
	bool keys[MAX_KEYS];

	cGame();
	void new_order(int x, int y);//issue new move/attack order
	//bool wallCollision(int X, int Y, int spr);
	void loadgraphics();
	void draw();//draw map on screen;
	void drawDoor(int tx,int ty);
	void show_debug();//draw debug information about mouseover tile.
	void loadGame();
	void saveGame();
	void updateSegment();
	//void openDoors(int xx,int yy);
};
#endif
