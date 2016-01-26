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
	int maxFrame;
	int frame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int animationColumns;
	int animationDirection;
public:
	ALLEGRO_BITMAP * playerPNG = NULL;
	
	cPlayer();
	void loadPNG();
	
	float X(); //get x
	float Y(); // get y
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
private:
	ALLEGRO_BITMAP * tilesPNG = NULL;
	ALLEGRO_FONT * arial18 = NULL;
	ALLEGRO_FONT * arial10 = NULL;
	

public:
	cTile segment[MAP_X][MAP_Y];
	cPlayer sprite[MAX_SPRITES];
	bool keys[MAX_KEYS];
	float scrollX;
	float scrollY;
	cGame();
	bool wallCollision(float dirX, float dirY, int spr);
	void loadgraphics();
	void draw();//draw map on screen;
	void drawDoor(int tx,int ty);
	void show_debug(int mx, int my);//draw debug information about mouseover tile.
	void loadGame();
	void saveGame();
	void updateSegment();
	void openDoors(int xx,int yy);
};
#endif
