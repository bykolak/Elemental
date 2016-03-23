#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_ttf.h>
#include "classes.h"
#include "define.h"


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
	frameDelay = 5;
	animationDirection = 1;
	posX = 768;
	posY = 288;
	facing = NORTH;
	size = 64;
	is_moving = false;
	status = SPRITE_NOT_ACTIVE;
	animationDelay = 0;
	type = CRYSTAL;
	currentHP = 100;
	maxHP = 100;
	currentEP = 30;
	maxEP = 100;
	currentMP = 100;
	maxMP = 150;
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


}
void cSprite::update()
{
	if (status != SPRITE_NOT_ACTIVE && status != SPRITE_DEAD)
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

		if (orderX*TILE_SIZE > posX)		{	posX += PLAYER_SPEED;	}
		if (orderX*TILE_SIZE < posX)		{	posX -= PLAYER_SPEED;	}
		if (orderY*TILE_SIZE > posY)		{	posY += PLAYER_SPEED;	}
		if (orderY*TILE_SIZE < posY)		{	posY -= PLAYER_SPEED;	}

		if (orderX * TILE_SIZE == posX && orderY * TILE_SIZE == posY)
		{

			is_moving = false;
			animationDelay++;
			status = SPRITE_IDLE;
		}
	}
}
void cSprite::draw(int scrollX, int scrollY)
{
	if (status != SPRITE_DEAD || status != SPRITE_NOT_ACTIVE)
	{
		switch (status)
		{
		case SPRITE_MOVE: {al_draw_bitmap_region(spritePNG, curFrame*size + MOVE_X, facing*size + MOVE_Y + (SPRITESHEET_Y *type), size, size, posX + (TILE_SIZE - size) / 2 - scrollX, posY + (TILE_SIZE - size) / 2 - scrollY, NULL); break; }
		case SPRITE_ATTACK: {al_draw_bitmap_region(spritePNG, curFrame*size + ATTACK_X, facing*size + ATTACK_Y + (SPRITESHEET_Y *type), size, size, posX + (TILE_SIZE - size) / 2 - scrollX, posY + (TILE_SIZE - size) / 2 - scrollY, NULL); break; }
		case SPRITE_DEAD: {al_draw_bitmap_region(spritePNG, DEAD_X, DEAD_Y + (SPRITESHEET_Y * type), size, size, posX + (TILE_SIZE - size) / 2 - scrollX, posY + (TILE_SIZE - size) / 2 - scrollY, NULL); break; }
		case SPRITE_HURT: {break; }
		case SPRITE_DYING: {break; }
		case SPRITE_PRIMARY_SKILL: {al_draw_bitmap_region(spritePNG, curFrame*size + PRIMARY_SKILL_X, facing*size + PRIMARY_SKILL_Y + (SPRITESHEET_Y *type), size, size, posX + (TILE_SIZE - size) / 2 - scrollX, posY + (TILE_SIZE - size) / 2 - scrollY, NULL); break; }
		case SPRITE_SECONDARY_SKILL: {al_draw_bitmap_region(spritePNG, curFrame*size + SECONDARY_SKILL_X, facing*size + SECONDARY_SKILL_Y + (SPRITESHEET_Y *type), size, size, posX + (TILE_SIZE - size) / 2 - scrollX, posY + (TILE_SIZE - size) / 2 - scrollY, NULL); break; }
		case SPRITE_ULTIMATE_SKILL: {al_draw_bitmap_region(spritePNG, curFrame*size + ULTIMATE_SKILL_X, facing*size + ULTIMATE_SKILL_Y + (SPRITESHEET_Y *type), size, size, posX + (TILE_SIZE - size) / 2 - scrollX, posY + (TILE_SIZE - size) / 2 - scrollY, NULL); break; }
		case SPRITE_IDLE:
		{
			if (animationDelay > IDLE_WAIT)
			{
				al_draw_bitmap_region(spritePNG, curFrame*size + IDLE_X, facing*size + IDLE_Y + (SPRITESHEET_Y *type), size, size, posX + (TILE_SIZE - size) / 2 - scrollX, posY + (TILE_SIZE - size) / 2 - scrollY, NULL); break;
			}
			else
			{
				al_draw_bitmap_region(spritePNG, IDLE_X, facing*size + IDLE_Y + (SPRITESHEET_Y *type), size, size, posX + (TILE_SIZE - size) / 2 - scrollX, posY + (TILE_SIZE - size) / 2 - scrollY, NULL); break;
			}

		}
		}
	}
}

cGame::cGame()
{

	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			segment[t][i].tile = EMPTY_TILE;
		}
	arial10 = al_load_font("arial.ttf", 10, NULL);
	arial18 = al_load_font("arial.ttf", 18, NULL);
	for (int i = 0; i < MAX_KEYS; i++)	keys[i] = false; 
	scroll.x = 0;
	scroll.y= 0;
	scroll.is_scrolling = false;
}
void cGame::showUI()
{
	
	for (int i = 0; i < BUTTON_INVENTORY; i++)	
	{
		float percentHP = ((float)sprite[i].currentHP / (float)sprite[i].maxHP);
		float percentEnergy = ((float)sprite[i].currentEP / (float)sprite[i].maxEP);
		float percentMP = ((float)sprite[i].currentMP / (float)sprite[i].maxMP);
		al_draw_textf(arial10, GREEN, 0, 260+ (i*15), NULL, "percentHP:%f", percentHP);
		al_draw_bitmap_region(uiPNG, 0, 5 * PORTRAIT_SIZE, 2 * PORTRAIT_SIZE, PORTRAIT_SIZE, buttons[i].x, buttons[i].y, 0);
		al_draw_bitmap_region(uiPNG, PORTRAIT_SIZE*i, 0, HEALTH_BAR_X,PORTRAIT_SIZE, buttons[i].x, buttons[i].y, 0);
		al_draw_bitmap_region(uiPNG, HEALTH_BAR_X, HEALTH_BAR_Y, HEALTH_BAR_WIDTH * percentHP, BAR_HEIGHT, buttons[i].x+HEALTH_BAR_X, buttons[i].y+10, NULL);
		al_draw_bitmap_region(uiPNG, ENERGY_BAR_X, ENERGY_BAR_Y, ENERGY_BAR_WIDTH * percentEnergy, BAR_HEIGHT, buttons[i].x + ENERGY_BAR_X, buttons[i].y + 55, NULL);
		al_draw_bitmap_region(uiPNG, MANA_BAR_X, MANA_BAR_Y, MANA_BAR_WIDTH * percentMP, BAR_HEIGHT, buttons[i].x + MANA_BAR_X, buttons[i].y + 100, NULL);
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
		if (buttons[i].flags)	{	currentSprite = i;	}
	}
}
void cGame::newOrder() 
{
	if (sprite[currentSprite].status == SPRITE_IDLE)
	{
		int playerX = sprite[currentSprite].x;
		int playerY = sprite[currentSprite].y;
		int dirX = 0;
		int dirY = 0;
		int face = 0;
		bool move = false;
		if (mouseX < playerX)		{		dirX = -1; dirY = 0; face = WEST;		}
		if (mouseX > playerX)		{		dirX = 1; dirY = 0; face = EAST;		}
		if (mouseY < playerY)		{		dirX = 0; dirY = -1; face = NORTH;		}
		if (mouseY > playerY)		{		dirX = 0; dirY = 1; face = SOUTH;		}

		if (segment[playerX + dirX][playerY + dirY].tile == FLOOR_TILE &&
			mouseX == playerX + dirX &&
			mouseY == playerY + dirY &&
			!sprite[currentSprite].is_moving && 
			segment[playerX + dirX][playerY + dirY].object != DECORATION &&
			spriteCollision(playerX + dirX, playerY+dirY) < 0)		{		move = true;	}
		
		if (move)
		{
			if (segment[playerX + dirX][playerY + dirY].object == DOOR && segment[playerX + dirX][playerY + dirY].status == CLOSED_DOOR)
			{
				segment[playerX + dirX][playerY + dirY].status = OPENING_DOOR;
			}
			sprite[currentSprite].orderX = mouseX;
			sprite[currentSprite].orderY = mouseY;
			sprite[currentSprite].x += dirX;
			sprite[currentSprite].y += dirY;
			sprite[currentSprite].is_moving = true;
			sprite[currentSprite].facing = face;
			sprite[currentSprite].status = SPRITE_MOVE;
			sprite[currentSprite].animationDelay = 0;
		}
		else if (spriteCollision(playerX + dirX, playerY + dirY) >= 0 && mouseX == playerX + dirX && mouseY == playerY + dirY)
		{
			attack(currentSprite, spriteCollision(playerX + dirX, playerY + dirY));
		}
	}
}
void cGame::attack(int attacking, int attacked)
{
	sprite[attacked].status = SPRITE_DEAD;
	sprite[attacking].status = SPRITE_IDLE;
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
		
			if (segment[t][i].tile == FLOOR_TILE)
			{
				al_draw_bitmap_region(tilesPNG, segment[t][i].tile_ID*TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE, t*TILE_SIZE - scroll.x, i *TILE_SIZE - scroll.y, NULL);
				
				if (t - 1 >= 0 && i - 1 >= 0)
				{
					if (segment[t][i - 1].tile == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, t*TILE_SIZE - scroll.x, (i - 1)*TILE_SIZE - scroll.y, NULL);//north wall

					if (segment[t - 1][i].tile == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, 0, TILE_SIZE, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE - scroll.x, i *TILE_SIZE - scroll.y, NULL);//west wall

					if (segment[t + 1][i].tile == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE - scroll.x, i *TILE_SIZE - scroll.y, NULL);//east wall

					if (segment[t][i + 1].tile == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, TILE_SIZE, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, t*TILE_SIZE - scroll.x, (i + 1)*TILE_SIZE - scroll.y, NULL);//south wall
					
					if (segment[t - 1][i - 1].tile == WALL_TILE && segment[t - 1][i].tile == WALL_TILE && segment[t][i - 1].tile == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, 0, 0, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE - scroll.x, (i - 1)*TILE_SIZE - scroll.y, NULL);//north-west wall
					
					if (segment[t + 1][i - 1].tile == WALL_TILE && segment[t + 1][i].tile == WALL_TILE && segment[t][i - 1].tile == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, 0, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE - scroll.x, (i - 1)*TILE_SIZE - scroll.y, NULL);//north-east wall
					
					if (segment[t - 1][i + 1].tile == WALL_TILE && segment[t - 1][i].tile == WALL_TILE && segment[t][i + 1].tile == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, 0, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE - scroll.x, (i + 1)*TILE_SIZE - scroll.y, NULL);//south-west wall

					if (segment[t + 1][i + 1].tile == WALL_TILE && segment[t + 1][i].tile == WALL_TILE && segment[t][i + 1].tile == WALL_TILE)
						al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE - scroll.x, (i + 1)*TILE_SIZE - scroll.y, NULL);//south-east wall
				}
			}
			if (segment[t][i].object == DOOR)			{	drawDoor(t,i);	} //draw doors
if(segment[t][i].object== DECORATION)
{ 
	al_draw_bitmap_region(tilesPNG, 0, 9 * TILE_SIZE, TILE_SIZE, TILE_SIZE, t*TILE_SIZE - scroll.x, i *TILE_SIZE - scroll.y, NULL);
}
		}
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		if (sprite[i].status == SPRITE_DEAD)
			sprite[i].draw(scroll.x, scroll.y);
	}
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		if (sprite[i].status!=SPRITE_DEAD)
		sprite[i].draw(scroll.x,scroll.y);
	}

	showUI();
	for (int i = 0; i < MAX_BUTTONS; i++) buttons[i].draw();
}
void cGame::drawDoor(int x, int y) //IS002
{
	ALLEGRO_BITMAP* door = NULL;

	if (segment[x][y - 1].tile == WALL_TILE && segment[x][y + 1].tile == WALL_TILE)//east -west
	{
		door = al_create_sub_bitmap(tilesPNG, TILE_SIZE*segment[x][y].object_ID, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
		if (segment[x][y].status==CLOSED_DOOR)
			al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE  - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2)  - scroll.y, DEGREE_90, NULL);
		if (segment[x][y].status == OPENING_DOOR || segment[x][y].status == CLOSING_DOOR)
		{
			door = al_create_sub_bitmap(tilesPNG, segment[x][y].curFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
			al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE  - scroll.x, y *TILE_SIZE + (TILE_SIZE /2 )  - scroll.y, DEGREE_90, NULL);
		}
		if (segment[x][y].status == OPEN_DOOR)
		{
			door = al_create_sub_bitmap(tilesPNG, segment[x][y].maxFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
			al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE+10  - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2)  - scroll.y, DEGREE_90, NULL);
		}
		if (segment[x][y].status == LOCKED_BRONZE_DOOR || segment[x][y].status == LOCKED_SILVER_DOOR || segment[x][y].status == LOCKED_GOLD_DOOR){}
		if (segment[x][y].status == BLOCKED_DOOR){}

	}

	if (segment[x - 1][y].tile == WALL_TILE &&segment[x + 1][y].tile == WALL_TILE)//north-south
	{
		if (segment[x][y].status == OPEN_DOOR)
		 	al_draw_bitmap_region(tilesPNG, 6 * TILE_SIZE, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x *TILE_SIZE  - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2) - 10 - scroll.y, NULL);
		
		if (segment[x][y].status == CLOSED_DOOR)
			al_draw_bitmap_region(tilesPNG, 0, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x*TILE_SIZE  - scroll.x, y*TILE_SIZE + (TILE_SIZE / 2) - scroll.y, NULL);
					
		if (segment[x][y].status == OPENING_DOOR || segment[x][y].status == CLOSING_DOOR)
			al_draw_bitmap_region(tilesPNG, segment[x][y].curFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE, x*TILE_SIZE  - scroll.x, y*TILE_SIZE + (TILE_SIZE / 2) - 10 - scroll.y, NULL);
				
		if (segment[x][y].status == LOCKED_BRONZE_DOOR || segment[x][y].status == LOCKED_SILVER_DOOR || segment[x][y].status == LOCKED_GOLD_DOOR){}
		if (segment[x][y].status == BLOCKED_DOOR){}
	}
		
}
void cGame::showDebug()
{	
		al_draw_text(arial10, RED, 100, 0, NULL, "DEBUG BUTTONS");
		al_draw_text(arial10, RED, 100, 12, NULL, "1-Clear Tile   2-Clear Object   3-Create Floor   4-Create Wall   5-Create Door   6-Force move currentSprite   Z-currentSprite--   X-currentSprite++");
		al_draw_text(arial10, RED, 100, 24, NULL, "6-Create Crystal 7-Create Werebull  8-Create Thorwal   9-Create Amfir   0-Create Enemy");
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

		al_draw_textf(arial10, GREEN, 180, 15, NULL, "scroll.x:%d", scroll.x);
		al_draw_textf(arial10, GREEN, 180, 30, NULL, "scroll.y:%d", scroll.y);

		al_draw_textf(arial10, GREEN, 0, 165, NULL, "mouse_over.x:%d", mouseX);
		al_draw_textf(arial10, GREEN, 0, 180, NULL, "mouse_over.y:%d", mouseY);
		al_draw_textf(arial10, GREEN, 0, 215, NULL, "collisionMouse: %d", spriteCollision(mouseX, mouseY));
		al_draw_textf(arial10, GREEN, mouseX*TILE_SIZE - scroll.x, mouseY*TILE_SIZE - scroll.y, NULL, "tile:%d", segment[mouseX][mouseY].tile);
		al_draw_textf(arial10, GREEN, mouseX*TILE_SIZE - scroll.x + 45, mouseY*TILE_SIZE - scroll.y, NULL, "tile_ID:%d", segment[mouseX][mouseY].tile_ID);
		al_draw_textf(arial10, GREEN, mouseX*TILE_SIZE - scroll.x, mouseY*TILE_SIZE - scroll.y + 15, NULL, "Object:%d", segment[mouseX][mouseY].object);
		al_draw_textf(arial10, GREEN, mouseX*TILE_SIZE - scroll.x + 45, mouseY*TILE_SIZE - scroll.y + 15, NULL, "Object_ID:%d", segment[mouseX][mouseY].object_ID);
		al_draw_textf(arial10, RED, 0, 135, NULL, "mouseOnScreenX:%d", mouseOnScreenX);
		al_draw_textf(arial10, RED, 0, 150, NULL, "mouseOnScreenY:%d", mouseOnScreenY);
		al_draw_rectangle(sprite[currentSprite].posX + (TILE_SIZE - sprite[currentSprite].size) / 2 - scroll.x, sprite[currentSprite].posY + (TILE_SIZE - sprite[currentSprite].size) / 2 - scroll.y, sprite[currentSprite].posX + (TILE_SIZE - sprite[currentSprite].size) / 2 - scroll.x + sprite[currentSprite].size, sprite[currentSprite].posY + (TILE_SIZE - sprite[currentSprite].size) / 2 - scroll.y + sprite[currentSprite].size, RED, 1);//red box around selected player

		for (int i = 0; i < MAP_Y; i++)
			for (int t = 0; t < MAP_X; t++)
			{
				if (segment[t][i].object == DOOR)
					al_draw_textf(arial10, BLUE, t*TILE_SIZE - scroll.x, i*TILE_SIZE - scroll.y, NULL, ":%d", segment[t][i].status);
			}
		al_draw_rectangle(mouseX*TILE_SIZE - scroll.x, mouseY*TILE_SIZE - scroll.y, (mouseX*TILE_SIZE - scroll.x) + TILE_SIZE, (mouseY*TILE_SIZE - scroll.y) + TILE_SIZE, RED, 1); //mouse over rectangle	
}
void cGame::saveGame()
{
		ALLEGRO_FILE* save_game = al_fopen("test.map", "wb");
			for (int i = 0; i < MAP_Y; i++)
			for (int t = 0; t < MAP_X; t++)
			{
				int tile =segment[t][i].tile;
				int tile_ID= segment[t][i].tile_ID;
				int object = segment[t][i].object;
				int object_ID = segment[t][i].object_ID;
				int status = segment[t][i].status;
				al_fwrite(save_game, &tile, sizeof(int));
				al_fwrite(save_game, &tile_ID, sizeof(int));
				al_fwrite(save_game, &object, sizeof(int));
				al_fwrite(save_game, &object_ID, sizeof(int));
				al_fwrite(save_game, &status, sizeof(int));
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
			segment[t][i].tile = tile;
			segment[t][i].tile_ID = tile_ID; 
			segment[t][i].object = object;
			if	(segment[t][i].object == DOOR)		{	segment[t][i].set(CREATE_DOOR);	}
			segment[t][i].object_ID = object_ID;
			segment[t][i].status = status;
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
	}
	al_fclose(save_game);
}
void cGame::update()
{
	//DEBUG MODE
	if (keys[CLEAR_TILE])	{		segment[mouseX][mouseY].set(CLEAR_TILE);	}
	if (keys[CLEAR_OBJECT])	{		segment[mouseX][mouseY].set(CLEAR_OBJECT);	}
	if (keys[CREATE_FLOOR])	{		segment[mouseX][mouseY].set(CREATE_FLOOR);	}
	if (keys[CREATE_WALL])	{		segment[mouseX][mouseY].set(CREATE_WALL);	}
	if (keys[CREATE_DOOR])	{		segment[mouseX][mouseY].set(CREATE_DOOR);	}
	if (keys[CREATE_SPRITE_0] && spriteCollision(mouseX, mouseY)<0)	{		sprite[currentSprite].create(mouseX,mouseY,CRYSTAL,SPRITE_IDLE);	}
	if (keys[CREATE_SPRITE_1] && spriteCollision(mouseX, mouseY)<0)	{		sprite[currentSprite].create(mouseX, mouseY, WEREBULL, SPRITE_IDLE);}
	if (keys[CREATE_SPRITE_2] && spriteCollision(mouseX, mouseY)<0)	{		sprite[currentSprite].create(mouseX, mouseY, AMFIR, SPRITE_IDLE);	}
	if (keys[CREATE_SPRITE_3] && spriteCollision(mouseX, mouseY)<0)	{		sprite[currentSprite].create(mouseX, mouseY, THORWAL, SPRITE_IDLE);	}
	if (keys[CREATE_SPRITE_4] && spriteCollision(mouseX,mouseY)<0)	{		sprite[currentSprite].create(mouseX, mouseY, ENEMY_0, SPRITE_IDLE);	}
	if (keys[CREATE_DECORATION] && spriteCollision(mouseX, mouseY) < 0)	{			segment[mouseX][mouseY].object = DECORATION;	}
	if (keys[DECREASE_HP]) 
	{
		for (int i = THORWAL; i <= AMFIR; i++)
		{
			sprite[i].currentHP--;
			sprite[i].currentEP--;
			sprite[i].currentMP--;
		}
		
	}
	if (keys[INCREASE_HP]) 
	{ 
		for (int i = THORWAL; i <= AMFIR; i++)
		{
			sprite[i].currentHP++;
			sprite[i].currentEP++;
			sprite[i].currentMP++;
		}
	}
	if (keys[DECREASE_SPRITE]) { currentSprite--; }
	if (keys[INCREASE_SPRITE]) { currentSprite++; }
	
	for (int i = THORWAL; i <= AMFIR; i++)
	{
		if (sprite[i].currentHP < 0) sprite[i].currentHP = 0;
		if (sprite[i].currentHP > sprite[i].maxHP) sprite[i].currentHP = sprite[i].maxHP;

		if (sprite[i].currentEP < 0) sprite[i].currentEP = 0;
		if (sprite[i].currentEP > sprite[i].maxEP) sprite[i].currentEP = sprite[i].maxEP;

		if (sprite[i].currentMP < 0) sprite[i].currentMP = 0;
		if (sprite[i].currentMP > sprite[i].maxMP) sprite[i].currentMP = sprite[i].maxMP;
	}
	if (currentSprite > MAX_SPRITES - 1) { currentSprite = 0; }
	if (currentSprite < 0) { currentSprite = MAX_SPRITES - 1; }

	for (int i = 0; i < MAP_Y; i++)		for (int t = 0; t < MAP_X; t++)		{	segment[t][i].update();		}//updates tiles
	for (int i = 0; i < MAX_SPRITES; i++)	{		if (sprite[i].status!=SPRITE_DEAD || sprite[i].status != SPRITE_NOT_ACTIVE)		sprite[i].update();	}//updates sprites

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
		case ALLEGRO_KEY_X: {keys[CREATE_DECORATION] = key_status; break; }
		case ALLEGRO_KEY_Z: {keys[DECREASE_HP] = key_status; break; }
		case ALLEGRO_KEY_C: {keys[INCREASE_HP] = key_status;  break; }
		case ALLEGRO_KEY_P: {keys[INCREASE_SPRITE] = key_status; key_status; break; }
		case ALLEGRO_KEY_O: {keys[DECREASE_SPRITE] = key_status; break; }
		}
		if (sprite[THORWAL].currentHP > sprite[THORWAL].maxHP)
			sprite[THORWAL].currentHP = sprite[THORWAL].maxHP;
		
}

int cGame::spriteCollision(int x, int y)
{
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		if (sprite[i].x == x && sprite[i].y == y &&sprite[i].status==SPRITE_IDLE)
			return i;
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
	tile = 0;
	tile_ID = 0;
	object = 0;
	object_ID = 0;
	status = 0;
	frameCount = 0;
	frameDelay = 0;
	animationDirection = 0;
	maxFrame = 0;
	curFrame = 0;	
}
void cTile::set(int value)
{
	if (value == CLEAR_TILE)
	{
		tile = EMPTY_TILE;
		tile_ID = EMPTY_TYPE;
	}
	if (value == CLEAR_OBJECT)
	{
		object = EMPTY_OBJECT;
		object_ID = EMPTY_ID;
	}

	if (value == CREATE_FLOOR)
	{
		tile = FLOOR_TILE;
		tile_ID = FLOOR_0;
	}
	if (value == CREATE_WALL)
	{
		tile = WALL_TILE;
		tile_ID = WALL_0;
	}
	if (value == CREATE_DOOR)
	{
		status = CLOSED_DOOR;
		object = DOOR;
		maxFrame = 6;
		frameDelay = 3;
		animationDirection = 1;
		curFrame = 0;
		frameCount = 0;
	}

}
void cTile::update()
{
	if (status == CLOSING_DOOR) animationDirection = -1;
	if (status == OPENING_DOOR) animationDirection = 1;
	if (object == DOOR && status == OPENING_DOOR) 
	{
		if (++frameCount >= frameDelay)
		{
			if (curFrame<maxFrame)	curFrame += animationDirection;
			if (curFrame >= maxFrame)		{ status = OPEN_DOOR;	curFrame = maxFrame; }
			if (curFrame <= 0) { curFrame = 0; }
			frameCount = 0;
		}
	}

	if (object == DOOR && status == CLOSING_DOOR)
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
