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

bool cButton::overButton(int _mouse_x, int _mouse_y) //if inside button then change flags to true else make it false
{
	if (_mouse_x >= x && _mouse_x <= x + width && _mouse_y >= y && _mouse_y <= y + height)
	{
		flags = true;
		return true;
	}
	else
	{
		flags = false;
		return false;
	}
}

void cButton::createButton(ALLEGRO_BITMAP *temp, int _x, int _y, int _width, int _height, int _type)
{
	
	buttonPNG = temp;
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	type = _type;
}

void cButton::drawButton()//draw button on screen
{
		
	if (flags && type>0)
	{
	
		al_draw_rectangle(x, y, x + width, y + height, WHITE, 3); //
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
}
void cSprite::loadSprite(ALLEGRO_BITMAP * bitmap)
{
	spritePNG = bitmap;	
}
void cSprite::create(int _x, int _y,int sprite_type)
{
	orderX = _x;
	orderY = _y;
	x = _x;
	y = _y;
	status = SPRITE_MOVE;
	type = sprite_type;

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

		if (orderX*TILE_SIZE > posX)
		{
			posX += PLAYER_SPEED;
		}

		if (orderX*TILE_SIZE < posX)
		{
			posX -= PLAYER_SPEED;
		}

		if (orderY*TILE_SIZE > posY)
		{
			posY += PLAYER_SPEED;
		}

		if (orderY*TILE_SIZE < posY)
		{
			posY -= PLAYER_SPEED;
		}

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
void cGame::new_order() //IS001
{
	if (sprite[currentSprite].status != SPRITE_DEAD && sprite[currentSprite].status != SPRITE_NOT_ACTIVE)
	{
		int px = sprite[currentSprite].x;
		int py = sprite[currentSprite].y;
		if (segment[px + 1][py].tile == FLOOR_TILE && mouseX == px + 1 && mouseY == py && !sprite[currentSprite].is_moving && spriteCollision(px + 1, py) < 0)
		{
			if (segment[px + 1][py].object == DOOR &&segment[px + 1][py].status == CLOSED_DOOR)
			{
				segment[px + 1][py].status = OPENING_DOOR;
			}

			sprite[currentSprite].orderX = mouseX;
			sprite[currentSprite].orderY = mouseY;
			sprite[currentSprite].x += 1;
			sprite[currentSprite].is_moving = true;
			sprite[currentSprite].facing = EAST;
			sprite[currentSprite].status = SPRITE_MOVE;
			sprite[currentSprite].animationDelay = 0;
		}
		else if (spriteCollision(px, py - 1) >= 0)
		{
			attack(currentSprite, spriteCollision(px, py - 1));
		}

		if (segment[px - 1][py].tile == FLOOR_TILE && mouseX == px - 1 && mouseY == py && !sprite[currentSprite].is_moving && spriteCollision(px - 1, py) < 0)
		{
			if (segment[px - 1][py].object == DOOR &&segment[px - 1][py].status == CLOSED_DOOR)
			{
				segment[px - 1][py].status = OPENING_DOOR;
			}
			sprite[currentSprite].orderX = mouseX;
			sprite[currentSprite].orderY = mouseY;
			sprite[currentSprite].x -= 1;
			sprite[currentSprite].is_moving = true;
			sprite[currentSprite].facing = WEST;
			sprite[currentSprite].status = SPRITE_MOVE;
			sprite[currentSprite].animationDelay = 0;
		}
		else if (spriteCollision(px, py - 1) >= 0)
		{
			attack(currentSprite, spriteCollision(px, py - 1));
		}

		if (segment[px][py + 1].tile == FLOOR_TILE && mouseY == py + 1 && mouseX == px && !sprite[currentSprite].is_moving && spriteCollision(px, py + 1) < 0)
		{
			if (segment[px][py + 1].object == DOOR &&segment[px][py + 1].status == CLOSED_DOOR)
			{
				segment[px][py + 1].status = OPENING_DOOR;
			}
			sprite[currentSprite].orderX = mouseX;
			sprite[currentSprite].orderY = mouseY;
			sprite[currentSprite].y += 1;
			sprite[currentSprite].is_moving = true;
			sprite[currentSprite].facing = SOUTH;
			sprite[currentSprite].status = SPRITE_MOVE;
			sprite[currentSprite].animationDelay = 0;
		}
		else if (spriteCollision(px, py - 1) >= 0)
		{
			attack(currentSprite, spriteCollision(px, py - 1));
		}

		if (segment[px][py - 1].tile == FLOOR_TILE && mouseY == py - 1 && mouseX == px && !sprite[currentSprite].is_moving && spriteCollision(px, py - 1) < 0)
		{
			if (segment[px][py - 1].object == DOOR &&segment[px][py - 1].status == CLOSED_DOOR)
			{
				segment[px][py - 1].status = OPENING_DOOR;
			}
			sprite[currentSprite].orderX = mouseX;
			sprite[currentSprite].orderY = mouseY;
			sprite[currentSprite].y -= 1;
			sprite[currentSprite].is_moving = true;
			sprite[currentSprite].facing = NORTH;
			sprite[currentSprite].status = SPRITE_MOVE;
			sprite[currentSprite].animationDelay = 0;
		}
		else if (spriteCollision(px, py - 1) >= 0)
		{
			attack(currentSprite, spriteCollision(px, py - 1));
		}
	}
}
void cGame::attack(int attacking, int attacked)
{
	sprite[attacked].status = SPRITE_DEAD;
}
void cGame::loadgraphics()
{
	tilesPNG = al_load_bitmap("tiles.png");
	if (!al_load_bitmap("tiles.png"))
	{
		
	}
	spritePNG = al_load_bitmap("sprite.png");
	if (!al_load_bitmap("sprite.png"))
	{

	}
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		sprite[i].loadSprite(spritePNG); 
	}
	
	uiPNG = al_load_bitmap("ui.png");
	if (!al_load_bitmap("ui.png"))
	{
	}
	
	//IS003
	buttons[BUTTON_SCROLL_NORTH].createButton(uiPNG,0, 0, SCREEN_WIDTH, 50,1);
	buttons[BUTTON_SCROLL_WEST].createButton(uiPNG, 0, 0, 50, SCREEN_HEIGHT, 0);
	buttons[BUTTON_SCROLL_EAST].createButton(uiPNG, SCREEN_WIDTH - 50, 0, 50, SCREEN_HEIGHT, 0);
	buttons[BUTTON_SCROLL_SOUTH].createButton(uiPNG, 0, SCREEN_HEIGHT - 50, SCREEN_WIDTH, 50, 0);
	
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
				
				al_draw_bitmap_region(tilesPNG, segment[t][i].tile_ID*TILE_SIZE, TILE_FILE_Y, TILE_SIZE, TILE_SIZE, t*TILE_SIZE - scroll.x, i *TILE_SIZE - scroll.y, NULL);
				
				if (segment[t][i - 1].tile == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, t*TILE_SIZE - scroll.x, (i - 1)*TILE_SIZE - scroll.y, NULL);//north wall
				
				if (segment[t - 1][i].tile == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, 0, TILE_SIZE, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE - scroll.x, i *TILE_SIZE - scroll.y, NULL);//west wall
				
				if (segment[t + 1][i].tile == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE - scroll.x, i *TILE_SIZE - scroll.y, NULL);//east wall
				
				if (segment[t][i + 1].tile == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, TILE_SIZE, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, t*TILE_SIZE - scroll.x, (i + 1)*TILE_SIZE - scroll.y, NULL);//south wall
	

				if (segment[t - 1][i - 1].tile == WALL_TILE && segment[t - 1][i].tile == WALL_TILE && segment[t ][i-1].tile == WALL_TILE)
				{
					al_draw_bitmap_region(tilesPNG, 0, 0, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE - scroll.x, (i - 1)*TILE_SIZE - scroll.y, NULL);//north-west wall
				}
							
				if (segment[t + 1][i - 1].tile == WALL_TILE && segment[t + 1][i].tile == WALL_TILE && segment[t][i-1].tile == WALL_TILE)
				{
					
					al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, 0, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE  - scroll.x, (i - 1)*TILE_SIZE  - scroll.y, NULL);//north-east wall
				}
									
				if (segment[t - 1][i + 1].tile == WALL_TILE && segment[t - 1][i].tile == WALL_TILE && segment[t][i + 1].tile == WALL_TILE)

					al_draw_bitmap_region(tilesPNG, 0, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE  - scroll.x, (i + 1)*TILE_SIZE  - scroll.y, NULL);//south-west wall
				
				if (segment[t + 1][i + 1].tile == WALL_TILE && segment[t + 1][i].tile == WALL_TILE && segment[t ][i+1].tile == WALL_TILE)

					al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE  - scroll.x, (i + 1)*TILE_SIZE  - scroll.y, NULL);//south-east wall

			}
			if (segment[t][i].object == DOOR)
			{
				drawDoor(t,i);
			}

		}
	
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		sprite[i].draw(scroll.x,scroll.y);
	}
	for (int i = 0; i < MAX_BUTTONS; i++) buttons[i].drawButton();
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
			al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE  - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2)  - scroll.y, DEGREE_90, NULL);
		}
		if (segment[x][y].status == OPEN_DOOR)
		{
			door = al_create_sub_bitmap(tilesPNG, segment[x][y].maxFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
			al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE  - scroll.x, y *TILE_SIZE + (TILE_SIZE / 2)  - scroll.y, DEGREE_90, NULL);
		}
		if (segment[x][y].status == LOCKED_BRONZE_DOOR || segment[x][y].status == LOCKED_SILVER_DOOR || segment[x][y].status == LOCKED_GOLD_DOOR){}
		if (segment[x][y].status == BLOCKED_DOOR){}

	}


	if (segment[x - 1][y].tile == WALL_TILE &&segment[x + 1][y].tile == WALL_TILE)//north-south
	{
		if (segment[x][y].status == OPEN_DOOR)
		{ 
			al_draw_bitmap_region(tilesPNG, 6 * TILE_SIZE, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x *TILE_SIZE  - scroll.x, y *TILE_SIZE  - scroll.y, NULL);
		}
		if (segment[x][y].status == CLOSED_DOOR)
		{
			al_draw_bitmap_region(tilesPNG, 0, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x*TILE_SIZE  - scroll.x, y*TILE_SIZE  - scroll.y, NULL);
		}
			
		if (segment[x][y].status == OPENING_DOOR || segment[x][y].status == CLOSING_DOOR)
		{
			al_draw_bitmap_region(tilesPNG, segment[x][y].curFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE, x*TILE_SIZE  - scroll.x, y*TILE_SIZE  - scroll.y, NULL);
		}
		
		if (segment[x][y].status == LOCKED_BRONZE_DOOR || segment[x][y].status == LOCKED_SILVER_DOOR || segment[x][y].status == LOCKED_GOLD_DOOR){}
		if (segment[x][y].status == BLOCKED_DOOR){}
	}
		
}
void cGame::show_debug()
{
	al_draw_text(arial10, RED, 100, 0, NULL, "DEBUG BUTTONS");
	al_draw_text(arial10, RED, 100, 12, NULL, "1-Clear Tile   2-Clear Object   3-Create Floor   4-Create Wall   5-Create Door   6-Force move currentSprite   Z-currentSprite--   X-currentSprite++");
	al_draw_textf(arial10, GREEN, 0, 0, NULL, "currentSprite.X:%d", sprite[currentSprite].x);
	al_draw_textf(arial10, GREEN, 0, 15, NULL, "currentSprite.Y:%d", sprite[currentSprite].y);
	al_draw_textf(arial10, GREEN, 0, 30, NULL, "currentSprite.posX:%d", sprite[currentSprite].posX);
	al_draw_textf(arial10, GREEN, 0, 45, NULL, "currentSprite.posY:%d", sprite[currentSprite].posY);
	al_draw_textf(arial10, GREEN, 0, 60, NULL, "currentSprite.orderX:%d", sprite[currentSprite].orderX);
	al_draw_textf(arial10, GREEN, 0, 75, NULL, "currentSprite.orderY:%d", sprite[currentSprite].orderY);
	al_draw_textf(arial10, GREEN, 0, 90, NULL, "currentSprite.facing:%d", sprite[currentSprite].facing);
	al_draw_textf(arial10, GREEN, 0, 105, NULL, "currentSprite.animationDelay:%d", sprite[currentSprite].animationDelay);
	al_draw_textf(arial10, GREEN, 0, 120, NULL, "currentSprite:%d", currentSprite);
	
	al_draw_textf(arial10, GREEN, 180, 15, NULL, "scroll.x:%d", scroll.x);
	al_draw_textf(arial10, GREEN, 180, 30, NULL, "scroll.y:%d", scroll.y);
	
	al_draw_textf(arial10, GREEN, 0, 165, NULL, "mouse_over.x:%d", mouseX);
	al_draw_textf(arial10, GREEN, 0, 180, NULL, "mouse_over.y:%d", mouseY);
	al_draw_textf(arial10, GREEN, mouseX*TILE_SIZE - scroll.x, mouseY*TILE_SIZE - scroll.y, NULL, "tile:%d", segment[mouseX][mouseY].tile);
	al_draw_textf(arial10, GREEN, mouseX*TILE_SIZE - scroll.x+45, mouseY*TILE_SIZE - scroll.y, NULL, "tile_ID:%d", segment[mouseX][mouseY].tile_ID);
	al_draw_textf(arial10, GREEN, mouseX*TILE_SIZE - scroll.x, mouseY*TILE_SIZE - scroll.y + 15, NULL, "Object:%d", segment[mouseX][mouseY].object);
	al_draw_textf(arial10, GREEN, mouseX*TILE_SIZE - scroll.x+45, mouseY*TILE_SIZE - scroll.y + 15, NULL, "Object_ID:%d", segment[mouseX][mouseY].object_ID);
	al_draw_textf(arial10, RED, 0, 135, NULL, "mouseOnScreenX:%d", mouseOnScreenX);
	al_draw_textf(arial10, RED, 0, 150, NULL, "mouseOnScreenY:%d", mouseOnScreenY);
	al_draw_rectangle(sprite[currentSprite].posX + (TILE_SIZE - sprite[currentSprite].size) / 2 - scroll.x, sprite[currentSprite].posY + (TILE_SIZE - sprite[currentSprite].size) / 2 - scroll.y, sprite[currentSprite].posX + (TILE_SIZE - sprite[currentSprite].size) / 2 - scroll.x + sprite[currentSprite].size, sprite[currentSprite].posY + (TILE_SIZE - sprite[currentSprite].size) / 2 - scroll.y + sprite[currentSprite].size, RED, 1);//red box around selected player

	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			if (segment[t][i].object==DOOR)
			al_draw_textf(arial10, BLUE, t*TILE_SIZE - scroll.x, i*TILE_SIZE - scroll.y, NULL, ":%d", segment[t][i].status);
		}
	al_draw_rectangle(mouseX*TILE_SIZE - scroll.x, mouseY*TILE_SIZE - scroll.y, (mouseX*TILE_SIZE - scroll.x) + TILE_SIZE, (mouseY*TILE_SIZE - scroll.y) + TILE_SIZE, RED, 1); //mouse over rectangle

}
void cGame::saveGame()
{
		ALLEGRO_FILE* save_game = al_fopen("test.map", "wb");
		int x = sprite[CRYSTAL].x;
		int y = sprite[CRYSTAL].y;
		al_fwrite(save_game, &x , sizeof(int));
		al_fwrite(save_game, &y, sizeof(int));
	
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
		al_fclose(save_game);
	


}
void cGame::loadGame()
{
	ALLEGRO_FILE* save_game = al_fopen("test.map", "rb");
	int x = 0;
	int y = 0;
	int tile=0;
	int tile_ID=0;
	int object=0;
	int object_ID=0;
	int status = 0;
	
	al_fread(save_game, &x, sizeof(int));
	al_fread(save_game, &y, sizeof(int));
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
	al_fclose(save_game);
}
void cGame::update()
{
	if (keys[CLEAR_TILE])
	{
		segment[mouseX][mouseY].set(CLEAR_TILE);
	}

	if (keys[CLEAR_OBJECT])
	{
		segment[mouseX][mouseY].set(CLEAR_OBJECT);
	}

	if (keys[CREATE_FLOOR])
	{
		segment[mouseX][mouseY].set(CREATE_FLOOR);
	}

	if (keys[CREATE_WALL])
	{
		segment[mouseX][mouseY].set(CREATE_WALL);
	}
	if (keys[CREATE_DOOR])
	{
		segment[mouseX][mouseY].set(CREATE_DOOR);
	}


	if (keys[CREATE_SPRITE_0] && spriteCollision(mouseX, mouseY)<0)
	{
		sprite[currentSprite].create(mouseX,mouseY,CRYSTAL);
	}
	
	if (keys[CREATE_SPRITE_1] && spriteCollision(mouseX, mouseY)<0)
	{
		sprite[currentSprite].create(mouseX, mouseY, WEREBULL);
	}
	
	if (keys[CREATE_SPRITE_2] && spriteCollision(mouseX, mouseY)<0)
	{
		sprite[currentSprite].create(mouseX, mouseY, AMFIR);
	}
	
	if (keys[CREATE_SPRITE_3] && spriteCollision(mouseX, mouseY)<0)
	{
		sprite[currentSprite].create(mouseX, mouseY, THORWAL);
	}
	
	if (keys[CREATE_SPRITE_4] && spriteCollision(mouseX,mouseY)<0)
	{
		sprite[currentSprite].create(mouseX, mouseY, ENEMY_0);
	}



	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			segment[t][i].update();
		}
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		sprite[i].update();
	}


	if (buttons[BUTTON_SCROLL_NORTH].overButton(mouseOnScreenX, mouseOnScreenY))
	{
		scroll.y -= SCROLL_SPEED;
	}
	if (buttons[BUTTON_SCROLL_WEST].overButton(mouseOnScreenX, mouseOnScreenY))
	{
		scroll.x -= SCROLL_SPEED;
	}
	if (buttons[BUTTON_SCROLL_EAST].overButton(mouseOnScreenX, mouseOnScreenY))
	{
		scroll.x += SCROLL_SPEED;
	}
	if (buttons[BUTTON_SCROLL_SOUTH].overButton(mouseOnScreenX, mouseOnScreenY))
	{
		scroll.y += SCROLL_SPEED;
	}
	if (scroll.x < 0 - (SCREEN_WIDTH / 2))
	{
		scroll.x = 0 - (SCREEN_WIDTH / 2);
	}
	if (scroll.y < 0 - (SCREEN_HEIGHT / 2))
	{
		scroll.y = 0 - (SCREEN_HEIGHT / 2);
	}

	if (scroll.x >(MAP_X - 5) * TILE_SIZE)
	{
		scroll.x = (MAP_X - 5)*TILE_SIZE;
	}
	if (scroll.y > (MAP_Y - 5)*TILE_SIZE)
	{
		scroll.y = (MAP_Y - 5)*TILE_SIZE;
	}
}
int cGame::spriteCollision(int x, int y)
{
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		if (sprite[i].x == x && sprite[i].y == y)
			return i;
		
	}
	return -1;
}
void cGame::updateMouse(int X, int Y)
{

	mouseX = (X + scroll.x) / TILE_SIZE;
	mouseY = (Y + scroll.y) / TILE_SIZE;
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
			if (curFrame <= 0) curFrame = 0;
				
			frameCount = 0;
			
		}
	}

	if (object == DOOR && status == CLOSING_DOOR)
	{
		if (++frameCount >= frameDelay)
		{
			if (curFrame >=0)	curFrame += animationDirection;
			if (curFrame >= maxFrame)		{ 	curFrame = maxFrame; }
			if (curFrame <= 0) { curFrame = 0; status = CLOSED_DOOR; }

			frameCount = 0;
		}
	}
}
