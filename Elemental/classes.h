#ifndef CLASSES_H
#define CLASSES_H

#include "define.h"

class cButton
{
private:

	int width;
	int height;
	bool flags;
	ALLEGRO_BITMAP *buttonPNG;
	ALLEGRO_BITMAP *buttonPressedPNG;
	ALLEGRO_FONT * arial18;
public:
	int x;
	int y;
	int type;
	int state;
	const char* text;
	cButton();//constructor
	bool getFlags();//return state of flag
	void toggleFlags();//flips value of a flag;
	void changeFlags(bool _value);//change flag to specific value
	bool overButton(int _mouse_x, int _mouse_y); //if inside button then change flags to true else make it false
	void changeButtonSize(int _x, int _y, int _width, int _height); //sets all button parameters
	void createButton(ALLEGRO_BITMAP *temp, ALLEGRO_FONT * font);//creates bitmap for button
	void drawButton();//draw button on screen
	int getWidth();
	int getHeight();
};
class cSprite
{
	friend class cTile;
	friend class cGame;
private:
	
	int x;//segment x where sprite is
	int y;//segment y where sprite is
	int maxFrame;// maximum number of frames (6 for player)
	int frame;
	int curFrame;//current frame
	int frameCount;
	int frameDelay;//how many cycles wait for putting next frame
	int animationDirection;//direction which program iterates through spritesheet 1 is RIGHT and -1 is LEFT
	bool is_moving;// if true player is moving from one tile to another
	int posX;//sprite position x on screen
	int posY;//sprite position y on screen
	int facing;//can take values of enum DIRECTION
	int size;//width and height of sprite
	int status;//can take value of enum SPRITE_STATUS
	int animationDelay;
	int orderX;
	int orderY;
	ALLEGRO_BITMAP * spritePNG = NULL;
public:
	
	cSprite();
	void loadSprite(ALLEGRO_BITMAP * bitmap);
	void update();
	void draw(int scrollX, int scrollY);
	


};
class cTile
{
	friend class cGame;
	friend class cSprite;
private:

	int tile; //can take values of enum TILE_TYPE
	int tile_ID;//can take values of enum ID_TYPE
	int object; //can take value of TILE_OBJECT
	int object_ID;//can take value of ID_OBJECT
	int status;
	int frameCount;
	int frameDelay;
	int animationDirection;
	int maxFrame;
	int curFrame;
public:
	cTile();
	void set(int editor); //pass enum EDITOR values only
	void update(); //updates aniamtion sequence
	//void setAnimation(int maxframe, int framedelay, int animationdirection); //sets all parameters regarding animation
};

class cGame
{
	friend class cTile;
	friend class cSprite;
private:
	ALLEGRO_BITMAP * tilesPNG = NULL;
	ALLEGRO_BITMAP * spritePNG = NULL;
	ALLEGRO_BITMAP * uiPNG = NULL;
	ALLEGRO_FONT * arial18 = NULL;
	ALLEGRO_FONT * arial10 = NULL;
	

public:
	cButton buttons[MAX_BUTTONS];
	int currentSprite = 0;
	bool collision[MAX_DIRECTION];
	int scrollX;
	int scrollY;
	int scrollDelay;
	int scrollCounter;
	bool is_scrolling;
	int mx;
	int my;
	int mpx;
	int mpy;
	cTile segment[MAP_X][MAP_Y];
	cSprite sprite[MAX_SPRITES];
	bool keys[MAX_KEYS];

	cGame();
	void new_order();//issue new move/attack order
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
