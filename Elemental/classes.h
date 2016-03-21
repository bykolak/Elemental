#ifndef CLASSES_H
#define CLASSES_H

#include "define.h"
struct sScroll
{
	int x = 0;
	int y = 0;
	bool is_scrolling = false;
};
class cButton
{
	friend class cGame;
private:
	int x;
	int y;
	int width;
	int height;
	int type;
	bool flags;
	ALLEGRO_BITMAP *buttonPNG;
	ALLEGRO_BITMAP *buttonPressedPNG;	
public:
	cButton();//constructor
	void update(int _mouse_x, int _mouse_y, int i); //if inside button then change flags to true else make it false
	void create(ALLEGRO_BITMAP *temp, int id);//create
	void draw();//draw button on screen

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
	int type; //use with enum SPRITE_TYPE
	int animationDelay;
	int orderX;
	int orderY;
	ALLEGRO_BITMAP * spritePNG = NULL;
public:
	cSprite();
	void load(ALLEGRO_BITMAP * bitmap);
	void create(int x, int y, int type, int status);
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
	friend class cButton;
private:
	ALLEGRO_BITMAP * tilesPNG = NULL;
	ALLEGRO_BITMAP * spritePNG = NULL;
	ALLEGRO_BITMAP * uiPNG = NULL;
	ALLEGRO_FONT * arial18 = NULL;
	ALLEGRO_FONT * arial10 = NULL;
	int mouseX;
	int mouseY;
	int mouseOnScreenX;
	int mouseOnScreenY;
public:
	cButton buttons[MAX_BUTTONS];
	sScroll scroll;
	cTile segment[MAP_X][MAP_Y];
	cSprite sprite[MAX_SPRITES];
	bool keys[MAX_KEYS];
	int currentSprite = 0;

	cGame();
	void showUI();
	void useUI();
	void newOrder();//issue new move/attack order
	void attack(int attacking,int attacked);
	void loadGraphics();
	void draw();//draw map on screen;
	void drawDoor(int tx,int ty);
	void showDebug();//draw debug information about mouseover tile.
	void loadGame();
	void saveGame();
	void update();
	void updateKeyboard(int keycode, bool key_status);
	int spriteCollision(int x, int y);
	void updateMouse(int X, int Y);
	//void openDoors(int xx,int yy);
};
#endif
