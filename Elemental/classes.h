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

class cTile
{
	friend class cGame;
protected:
	int type; //can take values of enum TILE_TYPE
	int style;//can take values of enum ID_TYPE
public:
	cTile();
	void set(int editor); //pass enum EDITOR values only
};

class cObject : public cTile
{
	friend class cGame;
protected:
	int status;
	int facing;
	int x;
	int y;
	int frameCount;
	int frameDelay;
	int animationDirection;
	int maxFrame;
	int curFrame;
public:
	cObject();
	bool collision(int xx, int yy);
	void create(int xx, int yy, int type,int _style);
	void draw();
	void update(); //updates aniamtion sequence
	int getStatus();
	void changeStatus(int x);
};

class cSprite : public cObject
{
	friend class cGame;
public:
	cSprite();
	void load(ALLEGRO_BITMAP * bitmap);
	void create(int x, int y, int type, int status);
	void rotate(int newFace);
	void update();
	void draw(int scrollX, int scrollY);
private:
	int frame;
	int attackAnimationCounter; //how many times play the animation
	float rotation;
	float rotationDirection;
	int rotateCounter;
	int maxRotate;
	bool is_moving;// if true player is moving from one tile to another
	int posX;//sprite position x on screen
	int posY;//sprite position y on screen
	int size;//width and height of sprite
	int animationDelay;
	int orderX;
	int orderY;
	//statistics
	int currentHP;
	int maxHP;
	int currentMP;
	int maxMP;
	int currentEP;
	int maxEP;
	int physicalDamage;
	int magicalDamage;
	int armorPoints;
	int level;
	int experiencePoints;
	int statusEffect;
	int actionPoints;
};


class cGame
{
	friend class cTile;
	friend class cSprite;
	friend class cButton;
	friend class cObject;
private:
//	ALLEGRO_BITMAP * tilesPNG = NULL;
	//ALLEGRO_BITMAP * spritePNG = NULL;
	ALLEGRO_BITMAP * uiPNG = NULL;
	ALLEGRO_FONT * arial18 = NULL;
	ALLEGRO_FONT * arial13 = NULL;
	ALLEGRO_FONT * arial10 = NULL;
	int mouseX;
	int mouseY;
	int mouseOnScreenX;
	int mouseOnScreenY;
public:
	cButton buttons[MAX_BUTTONS];
	//sScroll scroll;
	cTile segment[MAP_X][MAP_Y];
	cSprite sprite[MAX_SPRITES];
	cObject object[MAX_OBJECTS];;
	bool keys[MAX_KEYS];
	int currentSprite = 0;
	int currentObject = 0;
	int collisionObject = 0;
	//int collisionSprite = 0;
	cGame();
	~cGame();
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
	int spriteCollision(int x, int y,bool debug);
	int objectCollision(int xx, int yy);
	void updateMouse(int X, int Y);
	//void openDoors(int xx,int yy);
};
#endif
