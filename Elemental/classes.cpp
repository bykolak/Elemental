#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_ttf.h>
#include "classes.h"
#include "define.h"
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
	status = SPRITE_IDLE;
	animationDelay = 0;
}
void cSprite::loadPNG()
{
	playerPNG = al_load_bitmap("sprite.png");
	if (!al_load_bitmap("sprite.png"))
	{

	}
	
}
void cSprite::update()
{
	
	if (status == SPRITE_IDLE && animationDelay>IDLE_WAIT)
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

	if (orderY*TILE_SIZE  < posY)
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
void cSprite::draw()
{
		//al_draw_bitmap_region(playerPNG, curFrame*TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE, posX, posY, NULL);
	int file_x = 0;
	int file_y = 0;
	switch (status)
	{
	case SPRITE_MOVE: {al_draw_bitmap_region(playerPNG, curFrame*size + MOVE_X, facing*size + MOVE_Y, size, size, posX, posY, NULL); break; }
	case SPRITE_ATTACK: {break; }
	case SPRITE_DEFEND: {break; }
	case SPRITE_HURT: {break; }
	case SPRITE_DYING: {break; }
	case SPRITE_PRIMARY_SKILL: {break; }
	case SPRITE_SECONDARY_SKILL: {break; }
	case SPRITE_ULTIMATE_SKILL: {break; }
	case SPRITE_IDLE:
	{
		if (animationDelay > IDLE_WAIT)
		{
			al_draw_bitmap_region(playerPNG, curFrame*size + IDLE_X, facing*size + IDLE_Y, size, size, posX, posY, NULL);
		}
		else
		{
			al_draw_bitmap_region(playerPNG, IDLE_X, facing*size + IDLE_Y, size, size, posX, posY, NULL); break;
		}

	}
	}
	
	al_draw_rectangle(posX, posY, posX + size , posY + size, RED, 1);
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
	scrollX = 0;
	scrollY = 0;
}
void cGame::new_order()
{
	int px = sprite[PLAYER].x;
	int py = sprite[PLAYER].y;
	
	if (segment[px + 1][py].tile == FLOOR_TILE && mx == px + 1 && my==py && !sprite[PLAYER].is_moving)
	{
		if (segment[px + 1][py].object == DOOR &&segment[px + 1][py].status == CLOSED_DOOR)
		{
			segment[px + 1][py].status = OPENING_DOOR; 
		}

		sprite[PLAYER].orderX = mx;
		sprite[PLAYER].orderY = my;
		sprite[PLAYER].x += 1;
		sprite[PLAYER].is_moving = true;
		sprite[PLAYER].facing = EAST;
		sprite[PLAYER].status = SPRITE_MOVE;
		sprite[PLAYER].animationDelay = 0;
	}
	
	if (segment[px - 1][py].tile == FLOOR_TILE && mx == px - 1 && my == py)
	{
		if (segment[px - 1][py].object == DOOR &&segment[px - 1][py].status == CLOSED_DOOR)
		{
			segment[px - 1][py].status = OPENING_DOOR;
		}
		sprite[PLAYER].orderX = mx;
		sprite[PLAYER].orderY = my;
		sprite[PLAYER].x -= 1;
		sprite[PLAYER].is_moving = true;
		sprite[PLAYER].facing = WEST;
		sprite[PLAYER].status = SPRITE_MOVE;
		sprite[PLAYER].animationDelay = 0;
	}
	
	if (segment[px][py + 1].tile == FLOOR_TILE && my == py + 1 && mx == px)
	{
		if (segment[px][py + 1].object == DOOR &&segment[px][py + 1].status == CLOSED_DOOR)
		{
			segment[px][py + 1].status = OPENING_DOOR;
		}
		sprite[PLAYER].orderX = mx;
		sprite[PLAYER].orderY = my;
		sprite[PLAYER].y += 1;
		sprite[PLAYER].is_moving = true;
		sprite[PLAYER].facing = SOUTH;
		sprite[PLAYER].status = SPRITE_MOVE;
		sprite[PLAYER].animationDelay = 0;
	}
	
	if (segment[px][py - 1].tile == FLOOR_TILE && my == py - 1 && mx == px)
	{
		if (segment[px][py - 1].object == DOOR &&segment[px][py - 1].status == CLOSED_DOOR)
		{
			segment[px][py - 1].status = OPENING_DOOR;
		}
		sprite[PLAYER].orderX = mx;
		sprite[PLAYER].orderY = my;
		sprite[PLAYER].y -= 1;
		sprite[PLAYER].is_moving = true;
		sprite[PLAYER].facing = NORTH;
		sprite[PLAYER].status = SPRITE_MOVE;
		sprite[PLAYER].animationDelay = 0;
	}

}
void cGame::loadgraphics()
{
	tilesPNG = al_load_bitmap("tiles.png");
	if (!al_load_bitmap("tiles.png"))
	{
		
	}
	
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
				
				al_draw_bitmap_region(tilesPNG, segment[t][i].tile_ID*TILE_SIZE, TILE_FILE_Y, TILE_SIZE, TILE_SIZE, t*TILE_SIZE+scrollX, i *TILE_SIZE, NULL);
				
				if (segment[t][i - 1].tile == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, t*TILE_SIZE+scrollX, (i - 1)*TILE_SIZE, NULL);//north wall
				
				if (segment[t - 1][i].tile == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, 0, TILE_SIZE, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE, i *TILE_SIZE, NULL);//west wall
				
				if (segment[t + 1][i].tile == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE, i *TILE_SIZE, NULL);//east wall
				
				if (segment[t][i + 1].tile == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, TILE_SIZE, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, t*TILE_SIZE+scrollX, (i + 1)*TILE_SIZE, NULL);//south wall
	

				if (segment[t - 1][i - 1].tile == WALL_TILE && segment[t - 1][i].tile == WALL_TILE && segment[t ][i-1].tile == WALL_TILE)
				{
					al_draw_bitmap_region(tilesPNG, 0, 0, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE, (i - 1)*TILE_SIZE, NULL);//north-west wall
				}
							
				if (segment[t + 1][i - 1].tile == WALL_TILE && segment[t + 1][i].tile == WALL_TILE && segment[t][i-1].tile == WALL_TILE)
				{
					
					al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, 0, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE, (i - 1)*TILE_SIZE, NULL);//north-east wall
				}
									
				if (segment[t - 1][i + 1].tile == WALL_TILE && segment[t - 1][i].tile == WALL_TILE && segment[t][i + 1].tile == WALL_TILE)

					al_draw_bitmap_region(tilesPNG,0 , TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE, (i + 1)*TILE_SIZE, NULL);//south-west wall
				
				if (segment[t + 1][i + 1].tile == WALL_TILE && segment[t + 1][i].tile == WALL_TILE && segment[t ][i+1].tile == WALL_TILE)

					al_draw_bitmap_region(tilesPNG, TILE_SIZE*2, TILE_SIZE*2, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE, (i + 1)*TILE_SIZE, NULL);//south-east wall

			}
			if (segment[t][i].object == DOOR)
			{
				drawDoor(t,i);
			}

		
		
		}
	sprite[PLAYER].draw();
	
}
void cGame::drawDoor(int x, int y)
{
	ALLEGRO_BITMAP* door = NULL;

	if (segment[x][y - 1].tile == WALL_TILE && segment[x][y + 1].tile == WALL_TILE)//east -west
	{
		door = al_create_sub_bitmap(tilesPNG, TILE_SIZE*segment[x][y].object_ID, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
		if (segment[x][y].status==CLOSED_DOOR)
		al_draw_rotated_bitmap(door, TILE_SIZE/2, TILE_SIZE/2, x *TILE_SIZE, y *TILE_SIZE+(TILE_SIZE/2), DEGREE_90, NULL);
		if (segment[x][y].status == OPENING_DOOR || segment[x][y].status == CLOSING_DOOR)
		{
			door = al_create_sub_bitmap(tilesPNG, segment[x][y].curFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
			al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE, y *TILE_SIZE + (TILE_SIZE / 2), DEGREE_90, NULL);
		}
		if (segment[x][y].status == OPEN_DOOR)
		{
			door = al_create_sub_bitmap(tilesPNG, segment[x][y].maxFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
			al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE, y *TILE_SIZE + (TILE_SIZE / 2), DEGREE_90, NULL);
		}
		if (segment[x][y].status == LOCKED_BRONZE_DOOR || segment[x][y].status == LOCKED_SILVER_DOOR || segment[x][y].status == LOCKED_GOLD_DOOR){}
		if (segment[x][y].status == BLOCKED_DOOR){}

	}
		


	if (segment[x - 1][y].tile == WALL_TILE &&segment[x + 1][y].tile == WALL_TILE)//north-south
	{
		if (segment[x][y].status == OPEN_DOOR)
		{ 
			al_draw_bitmap_region(tilesPNG, 6*TILE_SIZE, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x *TILE_SIZE, y *TILE_SIZE, NULL); 
		}
		if (segment[x][y].status == CLOSED_DOOR)
		{
			al_draw_bitmap_region(tilesPNG, 0, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x*TILE_SIZE, y*TILE_SIZE, NULL);
		}
			
		if (segment[x][y].status == OPENING_DOOR || segment[x][y].status == CLOSING_DOOR)
		{
			al_draw_bitmap_region(tilesPNG, segment[x][y].curFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE,x*TILE_SIZE,y*TILE_SIZE,NULL);
		}
		
		if (segment[x][y].status == LOCKED_BRONZE_DOOR || segment[x][y].status == LOCKED_SILVER_DOOR || segment[x][y].status == LOCKED_GOLD_DOOR){}
		if (segment[x][y].status == BLOCKED_DOOR){}
	}
		
}
void cGame::show_debug()
{
	al_draw_text(arial10, GREEN, 50, 0, NULL, "1-Clear Tile 2-Clear Object 3-Create Floor 4-Create Wall 5-Create Door");
	al_draw_textf(arial10, GREEN, 0, 0, NULL, "player.X:%d", sprite[PLAYER].x);
	al_draw_textf(arial10, GREEN, 0, 15, NULL, "player.Y:%d", sprite[PLAYER].y);
	al_draw_textf(arial10, GREEN, 0, 30, NULL, "player.posX:%d", sprite[PLAYER].posX);
	al_draw_textf(arial10, GREEN, 0, 45, NULL, "player.posY:%d", sprite[PLAYER].posY);
	al_draw_textf(arial10, GREEN, 0, 60, NULL, "orderX:%d", sprite[PLAYER].orderX);
	al_draw_textf(arial10, GREEN, 0, 75, NULL, "orderY:%d", sprite[PLAYER].orderY);
	al_draw_textf(arial10, GREEN, 0, 90, NULL, "player.facing:%d", sprite[PLAYER].facing);
	al_draw_textf(arial10, GREEN, 0, 105, NULL, "player.animationDelay:%d", sprite[PLAYER].animationDelay);
	al_draw_textf(arial10, GREEN, mx*TILE_SIZE, my*TILE_SIZE - 30, NULL, "x:%d", mx);
	al_draw_textf(arial10, GREEN, mx*TILE_SIZE, my*TILE_SIZE - 15, NULL, "y:%d", my);
	al_draw_textf(arial10, RED, mx*TILE_SIZE, my*TILE_SIZE, NULL, "tile:%d", segment[mx][my].tile);
	al_draw_textf(arial10, RED, mx*TILE_SIZE, my*TILE_SIZE + 15, NULL, "tile_ID:%d", segment[mx][my].tile_ID);
	al_draw_textf(arial10, RED, mx*TILE_SIZE, my*TILE_SIZE + 30, NULL, "Object:%d", segment[mx][my].object);
	al_draw_textf(arial10, RED, mx*TILE_SIZE, my*TILE_SIZE + 45, NULL, "Object_ID:%d", segment[mx][my].object_ID);

	/*for (int i = 0; i < MAX_KEYS; i++)
	{
		ALLEGRO_COLOR color;
		if (keys[i]) color = GREEN;
		else color = RED;
		switch (i)
		{
		case UP:al_draw_text(arial10, color, sprite[PLAYER].X()*TILE_SIZE, sprite[PLAYER].Y()*TILE_SIZE + (i * 10), NULL, "UP"); break;
		case DOWN:al_draw_text(arial10, color, sprite[PLAYER].X()*TILE_SIZE, sprite[PLAYER].Y()*TILE_SIZE + (i * 10), NULL, "DOWN"); break;
		case LEFT:al_draw_text(arial10, color, sprite[PLAYER].X()*TILE_SIZE, sprite[PLAYER].Y()*TILE_SIZE + (i * 10), NULL, "LEFT"); break;
		case RIGHT:al_draw_text(arial10, color, sprite[PLAYER].X()*TILE_SIZE, sprite[PLAYER].Y()*TILE_SIZE + (i * 10), NULL, "RIGHT"); break;
		case OPEN:al_draw_text(arial10, color, sprite[PLAYER].X()*TILE_SIZE, sprite[PLAYER].Y()*TILE_SIZE + (i * 10), NULL, "OPEN"); break;
		case MAX_KEYS:break;
		}
	}
	*/
	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			if (segment[t][i].object==DOOR)
			al_draw_textf(arial10, BLUE, t*TILE_SIZE, i*TILE_SIZE, NULL, ":%d", segment[t][i].status);
		}
	al_draw_rectangle(mx*TILE_SIZE, my*TILE_SIZE, (mx*TILE_SIZE) + TILE_SIZE, (my*TILE_SIZE)+TILE_SIZE, RED, 1); //mouse over rectangle

}
void cGame::saveGame()
{
		ALLEGRO_FILE* save_game = al_fopen("test.map", "wb");
		int x = sprite[PLAYER].x;
		int y = sprite[PLAYER].y;
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
void cGame::updateSegment()
{
	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			segment[t][i].update();
		}
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
