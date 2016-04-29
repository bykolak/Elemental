#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_ttf.h>
#include "classes.h"
#include "define.h"

extern ALLEGRO_BITMAP * spritePNG;
extern ALLEGRO_BITMAP * tilesPNG;
extern sScroll scroll;

cObject::cObject()
{
	type = 0;
	style = 0;
	status = 0;
	facing = NORTH;
	x = 0;
	y = 0;
	frameCount = 0;
	frameDelay = 10;
	animationDirection = 1;
	maxFrame = 6;
	curFrame = 0;
}

bool cObject::collision(int xx, int yy)
{
	if (x == xx && yy == y && type>EMPTY_OBJECT)
		return true;
	else return false;
}

void cObject::create(int xx, int yy, int _type,int _style)
{
	x = xx;
	y = yy;
	type = _type;
	style = _style;
	if (type != EMPTY_TYPE)
	{
		status = OBJECT_ACTIVE;
	}
	if (type == EMPTY_TYPE)
	{
		status = OBJECT_NOT_ACTIVE;
	}
	if (type == DOOR)
	{
		status = CLOSED_DOOR;
	}

}

int cGame::objectCollision(int xx, int yy)
{
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		if (object[i].collision(xx,yy))
			return i;
	}
	return -1;
}


void cObject::draw() //IS002
{
	ALLEGRO_BITMAP* door = NULL;
	if (type == DECORATION)
	{
		al_draw_bitmap_region(tilesPNG, 0, 9 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x*TILE_SIZE - scroll.x, y *TILE_SIZE - scroll.y, NULL);
	}
	if (type == DOOR)
	{
		int addX = 0;
		int addY = 0;
		if (facing == NORTH)
		{
			addY = TILE_SIZE /2;
		}
		if (facing == WEST)
		{
			addX = -(TILE_SIZE / 2);
		}
		//float degree = 0.0;
		//if (facing == NORTH || SOUTH) { degree = 0.0; }
		//if (facing == WEST || EAST) { degree = DEGREE_90*2; }
		door = al_create_sub_bitmap(tilesPNG, 0, 576, TILE_SIZE, TILE_SIZE);
		al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x * TILE_SIZE - scroll.x + (TILE_SIZE / 2)+addX, y * TILE_SIZE - scroll.y + (TILE_SIZE / 2)+addY,facing*DEGREE_90, NULL);
		al_destroy_bitmap(door);
		
	}
	
	
	/*if (direction == NORTH || SOUTH)
	{
		door = al_create_sub_bitmap(tilesPNG, TILE_SIZE*style, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
		al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2) - scroll.y, DEGREE_90, NULL);
		al_destroy_bitmap(door);
	}
	if (direction == WEST || EAST)
	{
		door = al_create_sub_bitmap(tilesPNG, TILE_SIZE*style, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
		al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2) - scroll.y, DEGREE_90, NULL);
		al_destroy_bitmap(door);
	}*/

	/*if (segment[x][y - 1].type == WALL_TILE && segment[x][y + 1].type == WALL_TILE)//east -west
	{
		
		if (segment[x][y].status == CLOSED_DOOR)
		{
		door = al_create_sub_bitmap(tilesPNG, TILE_SIZE*segment[x][y].style, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
		al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2) - scroll.y, DEGREE_90, NULL);
		al_destroy_bitmap(door);
		}

		if (segment[x][y].status == OPENING_DOOR || segment[x][y].status == CLOSING_DOOR)
		{
		door = al_create_sub_bitmap(tilesPNG, segment[x][y].curFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
		al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE  - scroll.x, y *TILE_SIZE + (TILE_SIZE /2 )  - scroll.y, DEGREE_90, NULL);
		al_destroy_bitmap(door);
		}
		if (segment[x][y].status == OPEN_DOOR)
		{
		door = al_create_sub_bitmap(tilesPNG, segment[x][y].maxFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
		al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE+10  - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2)  - scroll.y, DEGREE_90, NULL);
		al_destroy_bitmap(door);
		}
		if (segment[x][y].status == LOCKED_BRONZE_DOOR || segment[x][y].status == LOCKED_SILVER_DOOR || segment[x][y].status == LOCKED_GOLD_DOOR){}
		if (segment[x][y].status == BLOCKED_DOOR){}

		}

		if (segment[x - 1][y].type == WALL_TILE &&segment[x + 1][y].type == WALL_TILE)//north-south
		{
		/*	if (segment[x][y].status == OPEN_DOOR)
		al_draw_bitmap_region(tilesPNG, 6 * TILE_SIZE, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x *TILE_SIZE  - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2) - 10 - scroll.y, NULL);

		if (segment[x][y].status == CLOSED_DOOR)
		al_draw_bitmap_region(tilesPNG, 0, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x*TILE_SIZE  - scroll.x, y*TILE_SIZE + (TILE_SIZE / 2) - scroll.y, NULL);

		if (segment[x][y].status == OPENING_DOOR || segment[x][y].status == CLOSING_DOOR)
		al_draw_bitmap_region(tilesPNG, segment[x][y].curFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE, x*TILE_SIZE  - scroll.x, y*TILE_SIZE + (TILE_SIZE / 2) - 10 - scroll.y, NULL);

		if (segment[x][y].status == LOCKED_BRONZE_DOOR || segment[x][y].status == LOCKED_SILVER_DOOR || segment[x][y].status == LOCKED_GOLD_DOOR){}
		if (segment[x][y].status == BLOCKED_DOOR){}
	}*/

}

//=====cButton methods
cButton::cButton()//constructor
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	type = 0;
	flags = false;
	buttonPNG = NULL;
	buttonPressedPNG = NULL;
}

void cButton::update(int _mouse_x, int _mouse_y, int i) //if inside button then change flags to true else make it false
{
	if (_mouse_x >= x && _mouse_x <= x + width && _mouse_y >= y && _mouse_y <= y + height)
	{	flags = true;	}
	else	
	{	flags = false;	}
}

void cButton::create(ALLEGRO_BITMAP *temp, int id)
{
	
	buttonPNG = temp;
	for (int i = BUTTON_THORWAL; i < BUTTON_PRIMARY_SKILL; i++)
	{
		if (id >= BUTTON_THORWAL && id < BUTTON_INVENTORY)
		{
			x = SCREEN_WIDTH - PORTRAIT_SIZE  * 2;
			y = (PORTRAIT_SIZE*id) + (MARGIN*id) + MARGIN;
			width = PORTRAIT_SIZE;
			height = PORTRAIT_SIZE;
			type = 1;
		}
		if (id == BUTTON_INVENTORY)
		{
			x = SCREEN_WIDTH - PORTRAIT_SIZE - (2 * MARGIN);
			y = SCREEN_HEIGHT - PORTRAIT_SIZE - (2 * MARGIN);
			width = PORTRAIT_SIZE;
			height = PORTRAIT_SIZE;
			type = 2;
		}
		if (id >= BUTTON_PRIMARY_SKILL && id <= BUTTON_ULTIMATE_SKILL)
		{
			x =(SCREEN_WIDTH -560) +(SKILL_SIZE*(id - BUTTON_PRIMARY_SKILL) + (MARGIN * id)) ;
			y =SCREEN_HEIGHT-PORTRAIT_SIZE;
			width = SKILL_SIZE;
			height = SKILL_SIZE;
			type = 3;
		}
	}
		
	if (id == BUTTON_SCROLL_NORTH) { x = 0; y = 0; width = SCREEN_WIDTH; height = 50; type = 0; }
	if (id == BUTTON_SCROLL_WEST) { x = 0; y = 0; width = 50; height = SCREEN_HEIGHT; type = 0; }
	
	if (id == BUTTON_SCROLL_EAST) { x = SCREEN_WIDTH - 50; y = 0; width = 50; height = SCREEN_HEIGHT; type = 0; }
	if (id == BUTTON_SCROLL_SOUTH) { x = 0; y = SCREEN_HEIGHT - 50; width = SCREEN_WIDTH; height = 50; type = 0; }
}

void cButton::draw()//draw button on screen
{
		
	if (flags)
	{
		if( type == 1 || type==2)
	{
		al_draw_ellipse(x + (PORTRAIT_SIZE / 2), y + (PORTRAIT_SIZE / 2), PORTRAIT_SIZE / 2, PORTRAIT_SIZE / 2, WHITE, 3);
	}
		if (type == 3)
		{
			al_draw_ellipse(x + (SKILL_SIZE /2) , y + (SKILL_SIZE / 2), SKILL_SIZE / 2, SKILL_SIZE / 2, WHITE, 3);
		}
	}
}

cSprite::cSprite()
{
	x = 8;
	y = 3;
	orderX = 8;
	orderY = 3;
	frame = 0;
	maxFrame = 6;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 10;
	attackAnimationCounter = 0; //how many times play the animation
	rotation = 0;
	rotationDirection = 1;
	animationDirection = 1;
	posX = 768;
	posY = 288;
	facing = NORTH;
	size = 64;
	is_moving = false;
	status = SPRITE_NOT_ACTIVE;
	animationDelay = 0;
	type = EMPTY_SPRITE;
	currentHP = 100;
	maxHP = 100;
	currentEP = 30;
	maxEP = 100;
	currentMP = 100;
	maxMP = 150;
	physicalDamage = 10;

}
void cSprite::load(ALLEGRO_BITMAP * bitmap)
{
	spritePNG = bitmap;	
}
void cSprite::create(int _x, int _y,int _type, int _status)
{
	orderX = _x;
	orderY = _y;
	x = _x;
	y = _y;
	posX = x*TILE_SIZE;
	posY = y*TILE_SIZE;
	status = _status;
	type = _type;
	frameDelay =5;
	if (type == CRYSTAL)
	{
		physicalDamage = 19;
		currentHP = 120;
		maxHP = 120;
		currentMP = 200;
		maxMP = 200;
		currentEP = 0;
		maxEP = 0;
	}
	if (type == WEREBULL)
	{
		physicalDamage = 39;
		currentHP = 240;
		maxHP = 240;
		currentMP = 0;
		maxMP = 0;
		currentEP = 100;
		maxEP = 100;
	}
	if (type == AMFIR)
	{
		currentHP = 80;
		maxHP = 80;
		currentMP = 300;
		maxMP = 300;
		currentEP = 0;
		maxEP = 0;
	}
	if (type == THORWAL)
	{
		physicalDamage = 39;
		currentHP = 100;
		maxHP = 100;
		currentMP = 0;
		maxMP = 0;
		currentEP = 100;
		maxEP = 100;
	}
	if (type == GOBLIN)
	{
		physicalDamage = 6;
		currentHP = 45;
		maxHP = 45;
		currentMP = 0;
		maxMP = 0;
	}
	if (type == SKELETON)
	{
		physicalDamage = 12;
		currentHP = 45;
		maxHP = 45;
		currentMP = 40;
		maxMP = 40;
	}
}
void cSprite::rotate(int newFace)
{
	switch (facing)
	{
	case NORTH:
	{
		if (newFace == WEST)  { maxRotate = 90; rotationDirection = -1; }
		if (newFace == EAST)  { maxRotate = 90; rotationDirection = 1;  }
		if (newFace == SOUTH) { maxRotate = 180; rotationDirection = 1; }
		break;
	}
	case WEST:
	{
		if (newFace == EAST)  { maxRotate = 180; rotationDirection = 1; }
		if (newFace == NORTH) { maxRotate = 90; rotationDirection = 1;  }
		if (newFace == SOUTH) { maxRotate = 90; rotationDirection = -1; }
		break;
	}
	case EAST:
	{
		if (newFace == WEST)  { maxRotate = 180; rotationDirection = 1; }
		if (newFace == NORTH) { maxRotate = 90; rotationDirection = -1; }
		if (newFace == SOUTH) { maxRotate = 90; rotationDirection = 1;  }
		break;
	}
	case SOUTH:
	{
		if (newFace == WEST)  { maxRotate = 90; rotationDirection = 1;  }
		if (newFace == EAST)  { maxRotate = 90; rotationDirection = -1; }
		if (newFace == NORTH) { maxRotate = 180; rotationDirection = 1; }
		break;
	}

	}
}
void cSprite::update()
{
	
	if (status > SPRITE_DEAD)
	{
		if (status == SPRITE_IDLE && animationDelay > IDLE_WAIT)
		{
			if (++frameCount >= frameDelay)
			{
				curFrame += animationDirection;
				if (curFrame >= maxFrame)
				{
					curFrame = 0;
					animationDelay = 0;
				}
				else if (curFrame <= 0)	curFrame = maxFrame - 1;
				frameCount = 0;
			}
		}
		if (status == SPRITE_MOVE )
		{
			if (++frameCount >= frameDelay)
			{
				curFrame += animationDirection;
				if (curFrame >= maxFrame)
				{
					curFrame = 0;
					animationDelay = 0;
				}
				else if (curFrame <= 0)	curFrame = maxFrame - 1;
				frameCount = 0;
			}
		}
		if (status == SPRITE_ATTACK)
		{
			
			if (++frameCount >= frameDelay)
			{
				curFrame += animationDirection;
				if (curFrame >= maxFrame)
				{
					attackAnimationCounter++;
					curFrame = 0;
					animationDelay = 0;
					if (attackAnimationCounter > 1)
					{
						status = SPRITE_IDLE;
						attackAnimationCounter = 0;
					}
				}
				else if (curFrame <= 0)	curFrame = maxFrame - 1;
				frameCount = 0;
			}
		}
		if (status == SPRITE_ROTATE)
		{
			if (rotateCounter < maxRotate) { rotation += DEGREE_9* rotationDirection; rotateCounter+=9; }
			else { status = SPRITE_MOVE; rotateCounter = 0; }
		
		}
		if (status == SPRITE_MOVE)
		{
			if (orderX*TILE_SIZE > posX) { posX += PLAYER_SPEED; }
			if (orderX*TILE_SIZE < posX) { posX -= PLAYER_SPEED; }
			if (orderY*TILE_SIZE > posY) { posY += PLAYER_SPEED; }
			if (orderY*TILE_SIZE < posY) { posY -= PLAYER_SPEED; }
		}
		if (is_moving && orderX * TILE_SIZE == posX && orderY * TILE_SIZE == posY)
		{
			is_moving = false;
			animationDelay++;
			status = SPRITE_IDLE;
			curFrame = 0;
		}
	}
	if (currentHP > maxHP)
		currentHP = maxHP;
}
void cSprite::draw(int scrollX, int scrollY)
{
	ALLEGRO_BITMAP *bitmap = NULL;
	if (status>SPRITE_NOT_ACTIVE)
	{
		switch (status)
		{
		case SPRITE_MOVE:
		{
			bitmap = al_create_sub_bitmap(spritePNG, curFrame*size + MOVE_X, MOVE_Y + (SPRITESHEET_Y *type), size, size);
			al_draw_rotated_bitmap(bitmap, size / 2, size / 2, posX + (TILE_SIZE - size) / 2 - scrollX + size / 2, posY + (TILE_SIZE - size) / 2 - scrollY + size / 2, rotation, NULL);
			al_destroy_bitmap(bitmap);
			break; 
		}
		case SPRITE_ATTACK:
		{
			bitmap = al_create_sub_bitmap(spritePNG, curFrame*size + ATTACK_X, ATTACK_Y + (SPRITESHEET_Y *type), size, size);
			al_draw_rotated_bitmap(bitmap, size / 2, size / 2, posX + (TILE_SIZE - size) / 2 - scrollX + size / 2, posY + (TILE_SIZE - size) / 2 - scrollY + size / 2, rotation, NULL);
			al_destroy_bitmap(bitmap);
			break;
		}
		case SPRITE_DEAD: {al_draw_bitmap_region(spritePNG, DEAD_X, DEAD_Y + (SPRITESHEET_Y * type), size, size, posX + (TILE_SIZE - size) / 2 - scrollX, posY + (TILE_SIZE - size) / 2 - scrollY, NULL); 
			break; }
		case SPRITE_HURT: {break; }
		case SPRITE_DYING: {break; }
		case SPRITE_PRIMARY_SKILL: {al_draw_bitmap_region(spritePNG, curFrame*size + PRIMARY_SKILL_X, facing*size + PRIMARY_SKILL_Y + (SPRITESHEET_Y *type), size, size, posX + (TILE_SIZE - size) / 2 - scrollX, posY + (TILE_SIZE - size) / 2 - scrollY, NULL); break; }
		case SPRITE_SECONDARY_SKILL: {al_draw_bitmap_region(spritePNG, curFrame*size + SECONDARY_SKILL_X, facing*size + SECONDARY_SKILL_Y + (SPRITESHEET_Y *type), size, size, posX + (TILE_SIZE - size) / 2 - scrollX, posY + (TILE_SIZE - size) / 2 - scrollY, NULL); break; }
		case SPRITE_ULTIMATE_SKILL: {al_draw_bitmap_region(spritePNG, curFrame*size + ULTIMATE_SKILL_X, facing*size + ULTIMATE_SKILL_Y + (SPRITESHEET_Y *type), size, size, posX + (TILE_SIZE - size) / 2 - scrollX, posY + (TILE_SIZE - size) / 2 - scrollY, NULL); break; }
		case SPRITE_IDLE:
		{
			if (animationDelay > IDLE_WAIT)
			{
				bitmap = al_create_sub_bitmap(spritePNG, curFrame*size + IDLE_X, IDLE_Y + (SPRITESHEET_Y *type), size, size);
				al_draw_rotated_bitmap(bitmap, size / 2, size / 2, posX + (TILE_SIZE - size) / 2 - scrollX + size / 2, posY + (TILE_SIZE - size) / 2 - scrollY + size / 2, rotation, NULL);
				al_destroy_bitmap(bitmap);
			}
			else
			{
				bitmap = al_create_sub_bitmap(spritePNG, curFrame*size + IDLE_X, IDLE_Y + (SPRITESHEET_Y *type), size, size);
				al_draw_rotated_bitmap(bitmap, size / 2, size / 2, posX + (TILE_SIZE - size) / 2 - scrollX + size / 2, posY + (TILE_SIZE - size) / 2 - scrollY + size / 2, rotation, NULL);
				al_destroy_bitmap(bitmap);
			}

		}
		case SPRITE_ROTATE: 
		{
			bitmap = al_create_sub_bitmap(spritePNG,curFrame*size + MOVE_X,  MOVE_Y + (SPRITESHEET_Y *type), size, size);
			al_draw_rotated_bitmap(bitmap, size / 2, size / 2, posX + (TILE_SIZE - size) / 2 - scrollX + size / 2, posY + (TILE_SIZE - size) / 2 - scrollY + size / 2, rotation, NULL);
			al_destroy_bitmap(bitmap);
			break; 
		}
		}
	}	
}

cGame::cGame()
{

	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			segment[t][i].type = EMPTY_TILE;
		}
	arial10 = al_load_font("luculent.ttf", 12, NULL);
	arial18 = al_load_font("Oswald-Regular.ttf", 18, NULL);
	for (int i = 0; i < MAX_KEYS; i++)	keys[i] = false; 
	scroll.x = 0;
	scroll.y= 0;
	scroll.is_scrolling = false;
}
cGame::~cGame()
{
	al_destroy_bitmap(tilesPNG);
	al_destroy_bitmap(spritePNG);
	al_destroy_bitmap(uiPNG);
	al_destroy_font(arial18);
	al_destroy_font(arial10);
}
void cGame::showUI()
{
	
	for (int i = 0; i < BUTTON_INVENTORY; i++)	
	{
		float percentHP = ((float)sprite[i].currentHP / (float)sprite[i].maxHP);
		float percentEnergy = ((float)sprite[i].currentEP / (float)sprite[i].maxEP);
		float percentMP = ((float)sprite[i].currentMP / (float)sprite[i].maxMP);
		//al_draw_textf(arial10, GREEN, 0, 260+ (i*15), NULL, "percentHP:%f", percentHP);
		al_draw_bitmap_region(uiPNG, 0, 5 * PORTRAIT_SIZE, 2 * PORTRAIT_SIZE, PORTRAIT_SIZE, buttons[i].x, buttons[i].y, 0);
		al_draw_bitmap_region(uiPNG, PORTRAIT_SIZE*i, 0, HEALTH_BAR_X,PORTRAIT_SIZE, buttons[i].x, buttons[i].y, 0);
		//DRAW STAT BARS AND TEXT current/max
		al_draw_bitmap_region(uiPNG, HEALTH_BAR_X, HEALTH_BAR_Y, HEALTH_BAR_WIDTH * percentHP, BAR_HEIGHT, buttons[i].x+HEALTH_BAR_X, buttons[i].y+10, NULL);
		al_draw_textf(arial10, WHITE, buttons[i].x + HEALTH_BAR_X + (HEALTH_BAR_WIDTH / 2), buttons[i].y + 9, ALLEGRO_ALIGN_CENTRE, "%d / %d", sprite[i].currentHP, sprite[i].maxHP);
		al_draw_bitmap_region(uiPNG, ENERGY_BAR_X, ENERGY_BAR_Y, ENERGY_BAR_WIDTH * percentEnergy, BAR_HEIGHT, buttons[i].x + ENERGY_BAR_X, buttons[i].y + 55, NULL);
		al_draw_textf(arial10, BLACK, buttons[i].x + HEALTH_BAR_X + (HEALTH_BAR_WIDTH / 2), buttons[i].y + 55, ALLEGRO_ALIGN_CENTRE, "%d / %d", sprite[i].currentEP, sprite[i].maxEP);
		al_draw_bitmap_region(uiPNG, MANA_BAR_X, MANA_BAR_Y, MANA_BAR_WIDTH * percentMP, BAR_HEIGHT, buttons[i].x + MANA_BAR_X, buttons[i].y + 100, NULL);
		al_draw_textf(arial10, WHITE, buttons[i].x + MANA_BAR_X + (MANA_BAR_WIDTH / 2), buttons[i].y + 99, ALLEGRO_ALIGN_CENTRE, "%d / %d", sprite[i].currentMP, sprite[i].maxMP);
	}
	//if (i == BUTTON_INVENTORY)
		al_draw_bitmap_region(uiPNG, BUTTON_INVENTORY*PORTRAIT_SIZE, 0, PORTRAIT_SIZE, PORTRAIT_SIZE, buttons[BUTTON_INVENTORY].x, buttons[BUTTON_INVENTORY].y, 0);
	for (int i = BUTTON_PRIMARY_SKILL; i <= BUTTON_ULTIMATE_SKILL; i++)	
	{	al_draw_bitmap_region(uiPNG, 0, PORTRAIT_SIZE * (i - BUTTON_INVENTORY), PORTRAIT_SIZE, PORTRAIT_SIZE, buttons[i].x, buttons[i].y, 0);	}
}
void cGame::useUI()
{
	for (int i = 0; i < BUTTON_INVENTORY; i++)
	{
		if (buttons[i].flags) { currentSprite = i; scroll.x = sprite[i].posX - (SCREEN_WIDTH/2); scroll.y = sprite[i].posY - (SCREEN_HEIGHT/2);}
	}
}
void cGame::newOrder() 
{
	int playerX = sprite[currentSprite].x;
	int playerY = sprite[currentSprite].y;
	int dirX = 0;
	int dirY = 0;
	int newFace = 0;
	bool move = false;
	int _rotationDirection = 0;

	
	if (mouseX < playerX) { dirX = -1; dirY = 0; newFace = WEST; }
	if (mouseX > playerX) { dirX = 1; dirY = 0; newFace = EAST; }
	if (mouseY < playerY) { dirX = 0; dirY = -1; newFace = NORTH;}
	if (mouseY > playerY) { dirX = 0; dirY = 1; newFace = SOUTH;}
	
switch (sprite[currentSprite].facing)
	{
	case NORTH:
	{
		if (newFace == WEST) { sprite[currentSprite].maxRotate = 90; _rotationDirection = -1; }
		if (newFace == EAST) { sprite[currentSprite].maxRotate = 90; _rotationDirection = 1; }
		if (newFace == SOUTH) { sprite[currentSprite].maxRotate = 180; _rotationDirection = 1; }
		break;
	}
	case WEST:
	{
		if (newFace == EAST)  { sprite[currentSprite].maxRotate = 180; _rotationDirection = 1; }
		if (newFace == NORTH) { sprite[currentSprite].maxRotate = 90; _rotationDirection = 1; }
		if (newFace == SOUTH) { sprite[currentSprite].maxRotate = 90; _rotationDirection = -1; }
		break;
	}
	case EAST:
	{
		if (newFace == WEST) { sprite[currentSprite].maxRotate = 180; _rotationDirection = 1; }
		if (newFace == NORTH) { sprite[currentSprite].maxRotate = 90; _rotationDirection = -1; }
		if (newFace == SOUTH) { sprite[currentSprite].maxRotate = 90; _rotationDirection = 1; }
		break;
	}
	case SOUTH:
	{
		if (newFace == WEST)  { sprite[currentSprite].maxRotate = 90; _rotationDirection = 1; }
		if (newFace == EAST)  { sprite[currentSprite].maxRotate = 90; _rotationDirection = -1; }
		if (newFace == NORTH) { sprite[currentSprite].maxRotate = 180; _rotationDirection = 1; }
		break;
	}

	}
	
	if (sprite[currentSprite].status == SPRITE_IDLE)
	{
		
		if (segment[playerX + dirX][playerY + dirY].type == FLOOR_TILE &&
			mouseX == playerX + dirX &&
			mouseY == playerY + dirY &&
			!sprite[currentSprite].is_moving && 
			//objectCollision(mouseX,mouseY)<EMPTY_OBJECT &&
	//segment[playerX + dirX][playerY + dirY].object != DECORATION &&
			spriteCollision(playerX + dirX, playerY+dirY, false) < 0)		{		move = true;	}
		
		if (move)
		{
			int temp = objectCollision(playerX + dirX, playerY + dirY);

			if (object[temp].type == DOOR && object[temp].getStatus() == CLOSED_DOOR)
			{
				object[temp].changeStatus(OPENING_DOOR);
			}
			sprite[currentSprite].orderX = mouseX;
			sprite[currentSprite].orderY = mouseY;
			sprite[currentSprite].x += dirX;
			sprite[currentSprite].y += dirY;
			sprite[currentSprite].is_moving = true;
			if (sprite[currentSprite].facing != newFace)//if facing going to change
			{
				sprite[currentSprite].status = SPRITE_ROTATE;
				sprite[currentSprite].facing = newFace;
				sprite[currentSprite].rotationDirection = _rotationDirection;
			}
			else sprite[currentSprite].status = SPRITE_MOVE;
			
			
			sprite[currentSprite].animationDelay = 0;
		}
		else if (spriteCollision(playerX + dirX, playerY + dirY,false) >AMFIR && mouseX == playerX + dirX && mouseY == playerY + dirY)
		{
			//sprite[currentSprite].facing = newFace;              // needs rework
			attack(currentSprite, spriteCollision(playerX + dirX, playerY + dirY, false));
		}
	
		if (spriteCollision(mouseX, mouseY, false) <= AMFIR && spriteCollision(mouseX, mouseY, false) >= THORWAL)// if clicked on hero then change currentSprite
		{
			currentSprite = spriteCollision(mouseX, mouseY, false);
		}
	}
}
void cGame::attack(int attacking, int attacked)
{
	if (attacking != attacked)
	{
		sprite[attacking].status = SPRITE_ATTACK;
		sprite[attacked].currentHP -= sprite[attacking].physicalDamage;
		sprite[attacking].currentHP -= sprite[attacked].physicalDamage / 2;
	}
	
}
void cGame::loadGraphics()
{
	//load bitmaps
	tilesPNG = al_load_bitmap("tiles.png");
	if (!al_load_bitmap("tiles.png"))	{	}
	spritePNG = al_load_bitmap("sprite.png");
	if (!al_load_bitmap("sprite.png"))	{	}
	uiPNG = al_load_bitmap("ui.png");
	if (!al_load_bitmap("ui.png"))	{	}

	for (int i = 0; i < MAX_SPRITES; i++)	{	sprite[i].load(spritePNG); 	}//load sprites
	for (int i = 0; i < MAX_BUTTONS; i++)	{	buttons[i].create(uiPNG,i);	} //create buttons
}
void cGame::draw()
{
	int startX = 0;
	int startY = 0;
	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			if (segment[t][i].type == WALL_TILE)
			{
			//	al_draw_bitmap_region(tilesPNG, (segment[t][i].tile_ID-1)*TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE, t*TILE_SIZE - scroll.x, i *TILE_SIZE - scroll.y, NULL);
			}
			if (segment[t][i].type == FLOOR_TILE)
			{
				al_draw_bitmap_region(tilesPNG, segment[t][i].style*TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE, t*TILE_SIZE - scroll.x, i *TILE_SIZE - scroll.y, NULL);
				
				if (t - 1 >= 0 && i - 1 >= 0)
				{
					if (segment[t][i - 1].type == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, t*TILE_SIZE - scroll.x, (i - 1)*TILE_SIZE - scroll.y, NULL);//north wall

					if (segment[t - 1][i].type == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, 0, TILE_SIZE, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE - scroll.x, i *TILE_SIZE - scroll.y, NULL);//west wall

					if (segment[t + 1][i].type == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE - scroll.x, i *TILE_SIZE - scroll.y, NULL);//east wall

					if (segment[t][i + 1].type == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, TILE_SIZE, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, t*TILE_SIZE - scroll.x, (i + 1)*TILE_SIZE - scroll.y, NULL);//south wall
					
					if (segment[t - 1][i - 1].type == WALL_TILE && segment[t - 1][i].type == WALL_TILE && segment[t][i - 1].type == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, 0, 0, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE - scroll.x, (i - 1)*TILE_SIZE - scroll.y, NULL);//north-west wall
					
					if (segment[t + 1][i - 1].type == WALL_TILE && segment[t + 1][i].type == WALL_TILE && segment[t][i - 1].type == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, 0, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE - scroll.x, (i - 1)*TILE_SIZE - scroll.y, NULL);//north-east wall
					
					if (segment[t - 1][i + 1].type == WALL_TILE && segment[t - 1][i].type == WALL_TILE && segment[t][i + 1].type == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, 0, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE - scroll.x, (i + 1)*TILE_SIZE - scroll.y, NULL);//south-west wall

					if (segment[t + 1][i + 1].type == WALL_TILE && segment[t + 1][i].type == WALL_TILE && segment[t][i + 1].type == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE - scroll.x, (i + 1)*TILE_SIZE - scroll.y, NULL);//south-east wall	
				}
			}
		}
	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			if (segment[t][i].type == FLOOR_TILE)
			{
				if (segment[t + 1][i + 1].type == WALL_TILE && segment[t + 1][i].type == FLOOR_TILE && segment[t][i + 1].type == FLOOR_TILE)
				{
					al_draw_bitmap_region(tilesPNG, TILE_SIZE, TILE_SIZE, TILE_SIZE / 2, TILE_SIZE / 2, (t + 1)*TILE_SIZE - scroll.x, (i + 1)*TILE_SIZE - scroll.y, NULL);
				}
				if (segment[t + 1][i - 1].type == WALL_TILE && segment[t + 1][i].type == FLOOR_TILE && segment[t][i - 1].type == FLOOR_TILE)
				{
					al_draw_bitmap_region(tilesPNG, TILE_SIZE, TILE_SIZE + (TILE_SIZE / 2), TILE_SIZE / 2, TILE_SIZE / 2, (t + 1)*TILE_SIZE - scroll.x, (i - 1)*TILE_SIZE - scroll.y + (TILE_SIZE / 2), NULL);
				}
				if (segment[t][i - 1].type == WALL_TILE && segment[t + 1][i - 1].type == FLOOR_TILE && segment[t + 1][i].type == FLOOR_TILE)
				{
					al_draw_bitmap_region(tilesPNG, TILE_SIZE + (TILE_SIZE / 2), TILE_SIZE + (TILE_SIZE / 2), TILE_SIZE / 2, TILE_SIZE / 2, (t)*TILE_SIZE - scroll.x + (TILE_SIZE / 2), (i - 1)*TILE_SIZE - scroll.y + (TILE_SIZE / 2), NULL);
				}
				if (segment[t][i + 1].type == WALL_TILE && segment[t + 1][i].type == FLOOR_TILE && segment[t + 1][i + 1].type == FLOOR_TILE)
				{
					al_draw_bitmap_region(tilesPNG, TILE_SIZE + (TILE_SIZE / 2), TILE_SIZE, TILE_SIZE / 2, TILE_SIZE / 2, (t)*TILE_SIZE - scroll.x + (TILE_SIZE / 2), (i + 1)*TILE_SIZE - scroll.y, NULL);
				}
			}
		}

	for (int i = 0; i < MAX_SPRITES; i++)
	{
		if (sprite[i].status == SPRITE_DEAD)
			sprite[i].draw(scroll.x, scroll.y);
		object[i].draw();

	}
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		if (sprite[i].status > SPRITE_DEAD)
		{
			sprite[i].draw(scroll.x, scroll.y);
			float percentHP = ((float)sprite[i].currentHP / (float)sprite[i].maxHP);
			float percentMP = ((float)sprite[i].currentMP / (float)sprite[i].maxMP);
			al_draw_bitmap_region(uiPNG, HEALTH_BAR_X + 4, HEALTH_BAR_Y, (TILE_SIZE - MARGIN)* percentHP, BAR_HEIGHT/2, sprite[i].posX - scroll.x, sprite[i].posY - scroll.y, NULL);
			al_draw_bitmap_region(uiPNG, MANA_BAR_X + 4, MANA_BAR_Y, (TILE_SIZE - MARGIN)* percentMP, BAR_HEIGHT / 2, sprite[i].posX  - scroll.x, sprite[i].posY - scroll.y+ BAR_HEIGHT/2, NULL);
		//	al_draw_bitmap_region(uiPNG, HEALTH_BAR_X, HEALTH_BAR_Y, HEALTH_BAR_WIDTH * percentHP, BAR_HEIGHT, buttons[i].x + HEALTH_BAR_X, buttons[i].y + 10, NULL);
		}
		
	}

	showUI();
	for (int i = 0; i < MAX_BUTTONS; i++) buttons[i].draw();
}
/*void cGame::drawDoor(int x, int y) //IS002
{
	ALLEGRO_BITMAP* door = NULL;

	if (segment[x][y - 1].type == WALL_TILE && segment[x][y + 1].type == WALL_TILE)//east -west
	{
	
		if (segment[x][y].status == CLOSED_DOOR)
		{
			door = al_create_sub_bitmap(tilesPNG, TILE_SIZE*segment[x][y].style, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
			al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2) - scroll.y, DEGREE_90, NULL);
			al_destroy_bitmap(door);
		}
			
		if (segment[x][y].status == OPENING_DOOR || segment[x][y].status == CLOSING_DOOR)
		{
			door = al_create_sub_bitmap(tilesPNG, segment[x][y].curFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
			al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE  - scroll.x, y *TILE_SIZE + (TILE_SIZE /2 )  - scroll.y, DEGREE_90, NULL);
			al_destroy_bitmap(door);
		}
		if (segment[x][y].status == OPEN_DOOR)
		{
			door = al_create_sub_bitmap(tilesPNG, segment[x][y].maxFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
			al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE+10  - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2)  - scroll.y, DEGREE_90, NULL);
			al_destroy_bitmap(door);
		}
		if (segment[x][y].status == LOCKED_BRONZE_DOOR || segment[x][y].status == LOCKED_SILVER_DOOR || segment[x][y].status == LOCKED_GOLD_DOOR){}
		if (segment[x][y].status == BLOCKED_DOOR){}

	}

	if (segment[x - 1][y].type == WALL_TILE &&segment[x + 1][y].type == WALL_TILE)//north-south
	{
	/*	if (segment[x][y].status == OPEN_DOOR)
		 	al_draw_bitmap_region(tilesPNG, 6 * TILE_SIZE, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x *TILE_SIZE  - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2) - 10 - scroll.y, NULL);
		
		if (segment[x][y].status == CLOSED_DOOR)
			al_draw_bitmap_region(tilesPNG, 0, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x*TILE_SIZE  - scroll.x, y*TILE_SIZE + (TILE_SIZE / 2) - scroll.y, NULL);
					
		if (segment[x][y].status == OPENING_DOOR || segment[x][y].status == CLOSING_DOOR)
			al_draw_bitmap_region(tilesPNG, segment[x][y].curFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE, x*TILE_SIZE  - scroll.x, y*TILE_SIZE + (TILE_SIZE / 2) - 10 - scroll.y, NULL);
				
		if (segment[x][y].status == LOCKED_BRONZE_DOOR || segment[x][y].status == LOCKED_SILVER_DOOR || segment[x][y].status == LOCKED_GOLD_DOOR){}
		if (segment[x][y].status == BLOCKED_DOOR){}
	}

}*/
void cGame::showDebug()
{	
		al_draw_text(arial10, RED, 100, 0, NULL, "DEBUG BUTTONS");
		al_draw_text(arial10, RED, 250, 12, NULL, "1-Clear Tile    2-Clear Object    3-Create Floor    4-Create Wall    5-Create Door    6-CRYSTAL   7-WEREBULL   8-AMFIR   9-THORWAL   0-GOBLIN   Q-SKELETON");
		al_draw_text(arial10, RED, 250, 24, NULL, "P-currentSprite--   O-currentSprite++   I-Clear Sprite   Z-Decrease HP    C-Increase HP   B-Create Barrel   L-Load Map   S-Save Map");
		al_draw_textf(arial10, GREEN, 0, 0, NULL, "currentSprite.X:%d", sprite[currentSprite].x);
		al_draw_textf(arial10, GREEN, 0, 15, NULL, "currentSprite.Y:%d", sprite[currentSprite].y);
		al_draw_textf(arial10, GREEN, 0, 30, NULL, "currentSprite.posX:%d", sprite[currentSprite].posX);
		al_draw_textf(arial10, GREEN, 0, 45, NULL, "currentSprite.posY:%d", sprite[currentSprite].posY);
		al_draw_textf(arial10, GREEN, 0, 60, NULL, "currentSprite.orderX:%d", sprite[currentSprite].orderX);
		al_draw_textf(arial10, GREEN, 0, 75, NULL, "currentSprite.orderY:%d", sprite[currentSprite].orderY);
		al_draw_textf(arial10, GREEN, 0, 90, NULL, "currentSprite.facing:%d", sprite[currentSprite].facing);
		al_draw_textf(arial10, GREEN, 0, 105, NULL, "currentSprite.animationDelay:%d", sprite[currentSprite].animationDelay);
		al_draw_textf(arial10, GREEN, 0, 120, NULL, "currentSprite:%d", currentSprite);
		al_draw_textf(arial10, GREEN, 0, 230, NULL, "currentHP:%d", sprite[currentSprite].currentHP);
		al_draw_textf(arial10, GREEN, 0, 245, NULL, "maxHP:%d", sprite[currentSprite].maxHP);
		al_draw_textf(arial10, GREEN, 0, 260, NULL, "curFrame:%d", sprite[currentSprite].curFrame);
		al_draw_textf(arial10, GREEN, 0, 275, NULL, "status:%d", sprite[currentSprite].status);
		al_draw_textf(arial10, GREEN, 0, 290, NULL, "rotation:%d", sprite[currentSprite].rotation);
		al_draw_textf(arial10, GREEN, 0, 305, NULL, "rotationDirection:%d", sprite[currentSprite].rotationDirection);
		al_draw_textf(arial10, GREEN, 180, 15, NULL, "scroll.x:%d", scroll.x);
		al_draw_textf(arial10, GREEN, 180, 30, NULL, "scroll.y:%d", scroll.y);

		al_draw_textf(arial10, GREEN, 0, 165, NULL, "mouse_over.x:%d", mouseX);
		al_draw_textf(arial10, GREEN, 0, 180, NULL, "mouse_over.y:%d", mouseY);
		al_draw_textf(arial10, GREEN, 0, 215, NULL, "collisionMouse: %d", spriteCollision(mouseX, mouseY,true));
		/*
		al_draw_textf(arial10, GREEN, mouseX*TILE_SIZE - scroll.x, mouseY*TILE_SIZE - scroll.y, NULL, "tile:%d", segment[mouseX][mouseY].tile);
		al_draw_textf(arial10, GREEN, mouseX*TILE_SIZE - scroll.x + 45, mouseY*TILE_SIZE - scroll.y, NULL, "tile_ID:%d", segment[mouseX][mouseY].tile_ID);
		al_draw_textf(arial10, GREEN, mouseX*TILE_SIZE - scroll.x, mouseY*TILE_SIZE - scroll.y + 15, NULL, "Object:%d", segment[mouseX][mouseY].object);
		al_draw_textf(arial10, GREEN, mouseX*TILE_SIZE - scroll.x + 45, mouseY*TILE_SIZE - scroll.y + 15, NULL, "Object_ID:%d", segment[mouseX][mouseY].object_ID);
		al_draw_textf(arial10, RED, 0, 135, NULL, "mouseOnScreenX:%d", mouseOnScreenX);
		al_draw_textf(arial10, RED, 0, 150, NULL, "mouseOnScreenY:%d", mouseOnScreenY);
		*/
		al_draw_rectangle(sprite[currentSprite].posX + (TILE_SIZE - sprite[currentSprite].size) / 2 - scroll.x, sprite[currentSprite].posY + (TILE_SIZE - sprite[currentSprite].size) / 2 - scroll.y, sprite[currentSprite].posX + (TILE_SIZE - sprite[currentSprite].size) / 2 - scroll.x + sprite[currentSprite].size, sprite[currentSprite].posY + (TILE_SIZE - sprite[currentSprite].size) / 2 - scroll.y + sprite[currentSprite].size, RED, 1);//red box around selected player

		for (int i = 0; i < MAX_OBJECTS; i++)
			{
				al_draw_textf(arial10, RED, object[i].x*TILE_SIZE - scroll.x, object[i].y*TILE_SIZE - scroll.y, NULL, "status:   %d   facing:    %d", object[i].status, object[i].facing);
				al_draw_textf(arial10, RED, object[i].x*TILE_SIZE - scroll.x, object[i].y*TILE_SIZE - scroll.y+20, NULL, "type:%d   style:%d", object[i].type, object[i].style);
				
			}
		al_draw_rectangle(mouseX*TILE_SIZE - scroll.x, mouseY*TILE_SIZE - scroll.y, (mouseX*TILE_SIZE - scroll.x) + TILE_SIZE, (mouseY*TILE_SIZE - scroll.y) + TILE_SIZE, RED, 1); //mouse over rectangle	
}
void cGame::saveGame()
{
		ALLEGRO_FILE* save_game = al_fopen("test.map", "wb");
			for (int i = 0; i < MAP_Y; i++)
			for (int t = 0; t < MAP_X; t++)
			{
				int tile =segment[t][i].type;
				int tile_ID= segment[t][i].type;
				//int object = segment[t][i].object;
//temp//		//int object_ID = segment[t][i].object_ID;
				//int status = segment[t][i].status;
				al_fwrite(save_game, &tile, sizeof(int));
				al_fwrite(save_game, &tile_ID, sizeof(int));
				/*al_fwrite(save_game, &object, sizeof(int));
				al_fwrite(save_game, &object_ID, sizeof(int));
				al_fwrite(save_game, &status, sizeof(int));*/
			}
		for (int i = 0; i < MAX_SPRITES; i++)
		{
			int x = sprite[i].x;
			int y = sprite[i].y;
			int status = sprite[i].status;
			int type = sprite[i].type;
			al_fwrite(save_game, &x, sizeof(int));
			al_fwrite(save_game, &y, sizeof(int));
			al_fwrite(save_game, &status, sizeof(int));
			al_fwrite(save_game, &type, sizeof(int));
		}
		al_fclose(save_game);
}
void cGame::loadGame()
{
	ALLEGRO_FILE* save_game = al_fopen("test.map", "rb");
	int tile=0;
	int tile_ID=0;
	int object=0;
	int object_ID=0;
	int status = 0;
	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			al_fread(save_game, &tile, sizeof(int));
			al_fread(save_game, &tile_ID, sizeof(int));
			al_fread(save_game, &object, sizeof(int));
			al_fread(save_game, &object_ID, sizeof(int));
			al_fread(save_game, &status, sizeof(int));
			segment[t][i].type = tile;
			segment[t][i].style = tile_ID; 
			//	segment[t][i].object = object;
//temp//	//	if	(segment[t][i].object == DOOR)		{	segment[t][i].set(CREATE_DOOR);	}
		//	segment[t][i].object_ID = object_ID;
		//	segment[t][i].status = status;
		}
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		int x = 0;
		int y = 0;
		int status = 0;
		int type = 0;
		al_fread(save_game, &x, sizeof(int));
		al_fread(save_game, &y, sizeof(int));
		al_fread(save_game, &status, sizeof(int));
		al_fread(save_game, &type, sizeof(int));
		sprite[i].create(x, y, type, status);
		//sprite[i].create(0, 0, EMPTY_SPRITE, SPRITE_NOT_ACTIVE);
	}
	al_fclose(save_game);
}
void cGame::update()
{
	//DEBUG MODE
	bool noCollision=false;
	if (spriteCollision(mouseX, mouseY, true) < 0 && objectCollision(mouseX, mouseY) < 0 && segment[mouseX][mouseY].type == FLOOR_TILE)
		noCollision = true;
	else
		noCollision = false;

	if (keys[CLEAR_TILE])	{		segment[mouseX][mouseY].set(CLEAR_TILE);	}
	if (keys[CLEAR_OBJECT])	{ object[objectCollision(mouseX, mouseY)].create(0, 0, EMPTY_OBJECT,NO_STYLE); }
	if (keys[CLEAR_SPRITE]) {		sprite[spriteCollision(mouseX, mouseY,true)].create(0,0, EMPTY_SPRITE, SPRITE_NOT_ACTIVE); }
	if (keys[CREATE_FLOOR])	{		segment[mouseX][mouseY].set(CREATE_FLOOR);	}
	if (keys[CREATE_WALL])	{		segment[mouseX][mouseY].set(CREATE_WALL);	}
	if (keys[CREATE_DOOR]) { object[currentObject].create(mouseX,mouseY, DOOR, NO_STYLE); currentObject++; }
	if (keys[CREATE_SPRITE_0]	&& noCollision) { sprite[currentSprite].create(mouseX, mouseY, CRYSTAL, SPRITE_IDLE); }
	if (keys[CREATE_SPRITE_1]	&& noCollision) { sprite[currentSprite].create(mouseX, mouseY, WEREBULL, SPRITE_IDLE); }
	if (keys[CREATE_SPRITE_2]	&& noCollision) { sprite[currentSprite].create(mouseX, mouseY, AMFIR, SPRITE_IDLE); }
	if (keys[CREATE_SPRITE_3]	&& noCollision) { sprite[currentSprite].create(mouseX, mouseY, THORWAL, SPRITE_IDLE); }
	if (keys[CREATE_SPRITE_4]	&& noCollision) { sprite[currentSprite].create(mouseX, mouseY, GOBLIN, SPRITE_IDLE); }
	if (keys[CREATE_SPRITE_5]	&& noCollision) { sprite[currentSprite].create(mouseX, mouseY, SKELETON, SPRITE_IDLE); }
	if (keys[CREATE_DECORATION] && noCollision)
	{
		object[currentObject].create(mouseX, mouseY, DECORATION,BARREL_0);
		currentObject++;
	}
	if (keys[DECREASE_HP]) 	{	sprite[currentSprite].currentHP--;	}
	if (keys[INCREASE_HP]) 	{ 	sprite[currentSprite].currentHP++;	}
	if (keys[DECREASE_SPRITE]) { currentSprite--; if (sprite[currentSprite].currentHP < 0) sprite[currentSprite].currentHP = 0;	}
	if (keys[INCREASE_SPRITE]) { currentSprite++; }
	if (keys[SELECT_SPRITE]) { currentSprite = spriteCollision(mouseX, mouseY,true); }
	if (keys[LOAD_MAP]) { loadGame(); }
	if (keys[SAVE_MAP]) { saveGame(); }
	if (keys[FACE_VERTICAL]) { if(objectCollision(mouseX, mouseY) >-1) object[objectCollision(mouseX, mouseY)].facing = NORTH; }
	if (keys[FACE_HORIZONTAL]) { if (noCollision) object[objectCollision(mouseX, mouseY)].facing = WEST; }

	if (currentObject > MAX_OBJECTS - 1) { currentObject = 0; }
	if (currentSprite > MAX_SPRITES - 1) { currentSprite = 0; }
	if (currentSprite < 0) { currentSprite = MAX_SPRITES - 1; }

//	for (int i = 0; i < MAP_Y; i++)		for (int t = 0; t < MAP_X; t++)		{	segment[t][i].update();		}//updates tiles
	for (int i = 0; i < MAX_SPRITES; i++)	
	{
		if (sprite[i].currentHP<0)	sprite[i].status = SPRITE_DEAD;		
		if (sprite[i].currentHP > 0 && sprite[i].status == SPRITE_DEAD)
		{
			sprite[i].status = SPRITE_IDLE;
		}
		if (sprite[i].status>SPRITE_NOT_ACTIVE)		sprite[i].update();	}//updates sprites

	for (int i = 0; i < MAX_BUTTONS; i++)										
	{		
		buttons[i].update(mouseOnScreenX, mouseOnScreenY,i);	//updates flags
		if (buttons[BUTTON_SCROLL_NORTH].flags)	 { scroll.y -= SCROLL_SPEED; }
		if (buttons[BUTTON_SCROLL_WEST].flags)	 { scroll.x -= SCROLL_SPEED; }
		if (buttons[BUTTON_SCROLL_EAST].flags)	 { scroll.x += SCROLL_SPEED; }
		if (buttons[BUTTON_SCROLL_SOUTH].flags)  { scroll.y += SCROLL_SPEED; }
	}
	if (scroll.x < 0 - (SCREEN_WIDTH / 2))	{		scroll.x = 0 - (SCREEN_WIDTH / 2);	}
	if (scroll.y < 0 - (SCREEN_HEIGHT / 2))	{		scroll.y = 0 - (SCREEN_HEIGHT / 2);	}
	if (scroll.x >(MAP_X - 5) * TILE_SIZE)	{		scroll.x = (MAP_X - 5)*TILE_SIZE;	}
	if (scroll.y > (MAP_Y - 5)*TILE_SIZE)	{		scroll.y = (MAP_Y - 5)*TILE_SIZE;	}
}
void cGame::updateKeyboard(int keycode, bool key_status)
{
		switch (keycode)
		{
		case ALLEGRO_KEY_1: {keys[CLEAR_TILE] = key_status; break; }
		case ALLEGRO_KEY_2: {keys[CLEAR_OBJECT] = key_status; break; }
		case ALLEGRO_KEY_3: {keys[CREATE_FLOOR] = key_status; break; }
		case ALLEGRO_KEY_4: {keys[CREATE_WALL] = key_status; break; }
		case ALLEGRO_KEY_5: {keys[CREATE_DOOR] = key_status; break; }
		case ALLEGRO_KEY_6: {keys[CREATE_SPRITE_0] = key_status; break; }
		case ALLEGRO_KEY_7: {keys[CREATE_SPRITE_1] = key_status; break; }
		case ALLEGRO_KEY_8: {keys[CREATE_SPRITE_2] = key_status; break; }
		case ALLEGRO_KEY_9: {keys[CREATE_SPRITE_3] = key_status; break; }
		case ALLEGRO_KEY_0: {keys[CREATE_SPRITE_4] = key_status; break; }
		case ALLEGRO_KEY_Q: {keys[CREATE_SPRITE_5] = key_status; break; }
		case ALLEGRO_KEY_X: {keys[CREATE_DECORATION] = key_status; break; }
		case ALLEGRO_KEY_Z: {keys[DECREASE_HP] = key_status; break; }
		case ALLEGRO_KEY_C: {keys[INCREASE_HP] = key_status;  break; }
		case ALLEGRO_KEY_P: {keys[INCREASE_SPRITE] = key_status; break; }
		case ALLEGRO_KEY_O: {keys[DECREASE_SPRITE] = key_status; break; }
		case ALLEGRO_KEY_U: {keys[SELECT_SPRITE] = key_status; break; }
		case ALLEGRO_KEY_I: {keys[CLEAR_SPRITE] = key_status; break; }
		case ALLEGRO_KEY_L: {keys[LOAD_MAP] = key_status; break; }
		case ALLEGRO_KEY_S: {keys[SAVE_MAP] = key_status; break; }
		case ALLEGRO_KEY_W: {keys[FACE_VERTICAL] = key_status; break; }
		case ALLEGRO_KEY_E: {keys[FACE_HORIZONTAL] = key_status; break; }
		}	
}

int cGame::spriteCollision(int x, int y,bool debug)
{
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		if (sprite[i].x == x && sprite[i].y == y &&sprite[i].status==SPRITE_IDLE)
			return i;
		if (debug)
		{
			if (sprite[i].x == x && sprite[i].y == y)
				return i;
		}
	}
	return -1;
}
void cGame::updateMouse(int X, int Y)
{
	mouseX = (X + scroll.x) / TILE_SIZE;
	mouseY = (Y + scroll.y) / TILE_SIZE;
	if (mouseX > MAP_X - 1)		{	mouseX = MAP_X - 1;		}// make sure that mouseX and mouseY
	if (mouseX < 0)				{	mouseX = 0;				}// will not takes any negtive values
	if (mouseY > MAP_Y - 1)		{	mouseY = MAP_Y - 1;		}// or values that are bigger than
	if (mouseY < 0)				{	mouseY = 0;				}// last element of segment[][] array
	mouseOnScreenX = X;
	mouseOnScreenY = Y;
}
cTile::cTile()
{
	type = 0;
	style = 0;
}
void cTile::set(int value)
{
	if (value == CLEAR_TILE)
	{
		type = EMPTY_TILE;
		style = EMPTY_TYPE;
	}
	if (value == CREATE_FLOOR)
	{
		type = FLOOR_TILE;
		style = FLOOR_0;
	}
	
	if (value == CREATE_WALL)
	{
		type = WALL_TILE;
		style = WALL_0;
	}
}
void cObject::update()
{
	if (status == CLOSING_DOOR) animationDirection = -1;
	if (status == OPENING_DOOR) animationDirection = 1;
	if (type == DOOR && status == OPENING_DOOR) 
	{
		if (++frameCount >= frameDelay)
		{
			if (curFrame<maxFrame)	curFrame += animationDirection;
			if (curFrame >= maxFrame)		{ status = OPEN_DOOR;	curFrame = maxFrame; }
			if (curFrame <= 0) { curFrame = 0; }
			frameCount = 0;
		}
	}

	if (type == DOOR && status == CLOSING_DOOR)
	{
		if (++frameCount >= frameDelay)
		{
			if (curFrame >=0)	curFrame += animationDirection;
			if (curFrame >= maxFrame)			{	 curFrame = maxFrame; }
			if (curFrame <= 0) {	curFrame = 0;	status = CLOSED_DOOR; }
			frameCount = 0;
		}
	}
}

int cObject::getStatus()
{
	return status;
}

void cObject::changeStatus(int x)
{
	status = x;
}

