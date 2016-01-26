#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_ttf.h>
#include "classes.h"
#include "define.h"
cPlayer::cPlayer()
{
	x = 0;
	y = 0;
	frame = 0;
	maxFrame = 23;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 5;
	animationDirection = 1;


}
void cPlayer::loadPNG()
{
	playerPNG = al_load_bitmap("proto.png");
	if (!al_load_bitmap("proto.png"))
	{

	}
	
}
float cPlayer::X()
{
	return x;
}
float cPlayer::Y()
{
	return y;
}
void cPlayer::changeX(float X)
{
	x += X;
}
void cPlayer::changeY(float Y)
{
	y += Y;
}
void cPlayer::update()
{
	if (++frameCount >= frameDelay)
	{
		curFrame += animationDirection;
		if (curFrame >= maxFrame)
			curFrame = 0;
		else if (curFrame <= 0)
			curFrame = maxFrame - 1;

		frameCount = 0;
	}
	
	

}
void cPlayer::draw()
{


	
	al_draw_bitmap_region(playerPNG, curFrame*TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE, x-15, y-15, NULL);
	al_draw_bitmap_region(playerPNG,curFrame*TILE_SIZE,0, TILE_SIZE, TILE_SIZE, x-15, y-15, NULL); // draw player;
	al_draw_rectangle(x, y, x + PLAYER_SIZE, y + PLAYER_SIZE, RED, 1);
}

cGame::cGame()
{

	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			segment[t][i].change(EMPTY_TILE,TILE);
		}
	arial10 = al_load_font("arial.ttf", 10, NULL);
	arial18 = al_load_font("arial.ttf", 18, NULL);
	for (int i = 0; i < MAX_KEYS; i++)	keys[i] = false; 
	scrollX = 0;
	scrollY = 0;
}
bool cGame::wallCollision(float dirX, float dirY, int spr)
{
	int x = (sprite[spr].X() + dirX) / TILE_SIZE;
	int y = (sprite[spr].Y() + dirY) / TILE_SIZE;
	int x2 = (sprite[spr].X() + PLAYER_SIZE + dirX) / TILE_SIZE;
	int y2 = (sprite[spr].Y() + PLAYER_SIZE + dirY) / TILE_SIZE;
	if (segment[x][y].get(TILE) == WALL_TILE ||
		segment[x2][y2].get(TILE) == WALL_TILE ||
		segment[x][y2].get(TILE) == WALL_TILE ||
		segment[x2][y].get(TILE) == WALL_TILE) return false;
	else 
		if (segment[x][y].get(OBJECT) == DOOR && segment[x][y].get(STATUS)==CLOSED_DOOR ||
			segment[x2][y2].get(OBJECT) == DOOR && segment[x2][y2].get(STATUS) == CLOSED_DOOR ||
			segment[x][y2].get(OBJECT) == DOOR && segment[x][y2].get(STATUS) == CLOSED_DOOR ||
			segment[x2][y].get(OBJECT) == DOOR && segment[x2][y].get(STATUS) == CLOSED_DOOR) return false;
	else return true;

}
void cGame::loadgraphics()
{
	//segmentsBMP = al_load_bitmap("segments64.png");
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
		
			if (segment[t][i].get(TILE) == FLOOR_TILE)
			{
				
					al_draw_bitmap_region(tilesPNG, segment[t][i].get(TILE_ID)*TILE_SIZE, TILE_Y, TILE_SIZE, TILE_SIZE, t*TILE_SIZE+scrollX, i *TILE_SIZE, NULL);
				
				if (segment[t][i - 1].get(TILE) == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, t*TILE_SIZE+scrollX, (i - 1)*TILE_SIZE, NULL);//north wall
				
				if (segment[t - 1][i].get(TILE) == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, 0, TILE_SIZE, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE, i *TILE_SIZE, NULL);//west wall
				
				if (segment[t + 1][i].get(TILE) == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE, i *TILE_SIZE, NULL);//east wall
				
				if (segment[t][i + 1].get(TILE) == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, TILE_SIZE, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, t*TILE_SIZE+scrollX, (i + 1)*TILE_SIZE, NULL);//south wall


				

				if (segment[t - 1][i - 1].get(TILE) == WALL_TILE && segment[t - 1][i].get(TILE) == WALL_TILE && segment[t ][i-1].get(TILE) == WALL_TILE)
				{
					al_draw_bitmap_region(tilesPNG, 0, 0, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE, (i - 1)*TILE_SIZE, NULL);//north-west wall
				}
							
				if (segment[t + 1][i - 1].get(TILE) == WALL_TILE && segment[t + 1][i].get(TILE) == WALL_TILE && segment[t][i-1].get(TILE) == WALL_TILE)
				{
					
					al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, 0, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE, (i - 1)*TILE_SIZE, NULL);//north-east wall
				}
									
				if (segment[t - 1][i + 1].get(TILE) == WALL_TILE && segment[t - 1][i].get(TILE) == WALL_TILE && segment[t][i + 1].get(TILE) == WALL_TILE)

					al_draw_bitmap_region(tilesPNG,0 , TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE, (i + 1)*TILE_SIZE, NULL);//south-west wall
				
				if (segment[t + 1][i + 1].get(TILE) == WALL_TILE && segment[t + 1][i].get(TILE) == WALL_TILE && segment[t ][i+1].get(TILE) == WALL_TILE)

					al_draw_bitmap_region(tilesPNG, TILE_SIZE*2, TILE_SIZE*2, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE, (i + 1)*TILE_SIZE, NULL);//south-east wall

			}
			if (segment[t][i].get(OBJECT) == DOOR)
			{
				drawDoor(t,i);
			}

		
		
		}
	sprite[PLAYER].draw();
	//al_draw_bitmap_region(tilesPNG, 0, TILE_SIZE * 12, TILE_SIZE, TILE_SIZE, player.X(), player.Y(), NULL); // draw player;
}
void cGame::drawDoor(int x, int y)
{
	ALLEGRO_BITMAP* door = NULL;
	if (segment[x][y - 1].get(TILE) == WALL_TILE && segment[x][y + 1].get(TILE) == WALL_TILE)//east -west
	{
		door = al_create_sub_bitmap(tilesPNG, TILE_SIZE*segment[x][y].get(OBJECT_ID), TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
		if (segment[x][y].get(STATUS)==CLOSED_DOOR)
		al_draw_rotated_bitmap(door, TILE_SIZE/2, TILE_SIZE/2, x *TILE_SIZE, y *TILE_SIZE+(TILE_SIZE/2), DEGREE_90, NULL);
		if (segment[x][y].get(STATUS) == OPENING_DOOR || segment[x][y].get(STATUS) == CLOSING_DOOR)
		{
			door = al_create_sub_bitmap(tilesPNG, segment[x][y].curFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
			al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE, y *TILE_SIZE + (TILE_SIZE / 2), DEGREE_90, NULL);
		}
		if (segment[x][y].get(STATUS) == OPEN_DOOR)
		{
			door = al_create_sub_bitmap(tilesPNG, segment[x][y].maxFrame*TILE_SIZE, TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
		//	al_draw_bitmap_region(tilesPNG, 6*TILE_SIZE, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x *TILE_SIZE, y *TILE_SIZE, NULL);
			al_draw_rotated_bitmap(door, TILE_SIZE / 2, TILE_SIZE / 2, x *TILE_SIZE, y *TILE_SIZE + (TILE_SIZE / 2), DEGREE_90, NULL);
		}
		if (segment[x][y].get(STATUS) == LOCKED_BRONZE_DOOR || segment[x][y].get(STATUS) == LOCKED_SILVER_DOOR || segment[x][y].get(STATUS) == LOCKED_GOLD_DOOR){}
		if (segment[x][y].get(STATUS) == BLOCKED_DOOR){}

	}
		


	if (segment[x - 1][y].get(TILE) == WALL_TILE &&segment[x + 1][y].get(TILE) == WALL_TILE)//north-south
	{
		al_draw_bitmap_region(tilesPNG, segment[x][y].curFrame*TILE_SIZE, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x *TILE_SIZE, y *TILE_SIZE, NULL);
		if (segment[x][y].get(STATUS) == OPEN_DOOR){ al_draw_bitmap_region(tilesPNG, 6*TILE_SIZE, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x *TILE_SIZE, y *TILE_SIZE, NULL); }

	}
		
}
void cGame::show_debug(int mx, int my)
{
	al_draw_textf(arial10, GREEN, 0, 0, NULL, "player.x:%f", sprite[PLAYER].X());
	al_draw_textf(arial10, GREEN, 0, 15, NULL, "player.y:%f", sprite[PLAYER].Y());
	al_draw_textf(arial10, GREEN, mx*TILE_SIZE, my*TILE_SIZE - 30, NULL, "x:%d", mx);
	al_draw_textf(arial10, GREEN, mx*TILE_SIZE, my*TILE_SIZE - 15, NULL, "y:%d", my);
	al_draw_textf(arial10, RED, mx*TILE_SIZE, my*TILE_SIZE, NULL, "tile:%d", segment[mx][my].get(TILE));
	al_draw_textf(arial10, RED, mx*TILE_SIZE, my*TILE_SIZE + 15, NULL, "tile_ID:%d", segment[mx][my].get(TILE_ID));
	al_draw_textf(arial10, RED, mx*TILE_SIZE, my*TILE_SIZE + 30, NULL, "Object:%d", segment[mx][my].get(OBJECT));
	al_draw_textf(arial10, RED, mx*TILE_SIZE, my*TILE_SIZE + 45, NULL, "Object_ID:%d", segment[mx][my].get(OBJECT_ID));
	
	for (int i = 0; i < MAX_KEYS; i++)
	{
		ALLEGRO_COLOR color;
		if (keys[i]) color = GREEN;
		else color = RED;
		switch (i)
		{
		case UP:al_draw_text(arial10, color, sprite[PLAYER].X(), sprite[PLAYER].Y() + (i * 10), NULL, "UP"); break;
		case DOWN:al_draw_text(arial10, color, sprite[PLAYER].X(), sprite[PLAYER].Y() + (i * 10), NULL, "DOWN"); break;
		case LEFT:al_draw_text(arial10, color, sprite[PLAYER].X(), sprite[PLAYER].Y() + (i * 10), NULL, "LEFT"); break;
		case RIGHT:al_draw_text(arial10, color, sprite[PLAYER].X(), sprite[PLAYER].Y() + (i * 10), NULL, "RIGHT"); break;
		case OPEN:al_draw_text(arial10, color, sprite[PLAYER].X(), sprite[PLAYER].Y() + (i * 10), NULL, "OPEN"); break;
		case MAX_KEYS:break;
		}
			
		
	}

	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			if (segment[t][i].get(OBJECT)==DOOR)
			al_draw_textf(arial10, BLUE, t*TILE_SIZE+scrollX, i*TILE_SIZE, NULL, ":%d", segment[t][i].get(STATUS));
		}

}
void cGame::saveGame()
{
		ALLEGRO_FILE* save_game = al_fopen("test.map", "wb");
		int x = sprite[PLAYER].X();
		int y = sprite[PLAYER].Y();
		al_fwrite(save_game, &x , sizeof(int));
		al_fwrite(save_game, &y, sizeof(int));
	
		for (int i = 0; i < MAP_Y; i++)
			for (int t = 0; t < MAP_X; t++)
			{
				int tile =segment[t][i].get(TILE);
				int tile_ID= segment[t][i].get(TILE_ID);
				int tile_state = segment[t][i].get(TILE_STATE);
				int object = segment[t][i].get(OBJECT);
				int object_ID = segment[t][i].get(OBJECT_ID);
				int status = segment[t][i].get(STATUS);
				al_fwrite(save_game, &tile, sizeof(int));
				al_fwrite(save_game, &tile_ID, sizeof(int));
				al_fwrite(save_game, &tile_state, sizeof(int));
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
	int tile_state=0;
	int object=0;
	int object_ID=0;
	int status = 0;
	
	al_fread(save_game, &x, sizeof(int));
	al_fread(save_game, &y, sizeof(int));
	sprite[PLAYER].changeX(x);
	sprite[PLAYER].changeY(y);
	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			al_fread(save_game, &tile, sizeof(int));
			al_fread(save_game, &tile_ID, sizeof(int));
			al_fread(save_game, &tile_state, sizeof(int));
			al_fread(save_game, &object, sizeof(int));
			al_fread(save_game, &object_ID, sizeof(int));
			al_fread(save_game, &status, sizeof(int));
			segment[t][i].change(tile,TILE);
			segment[t][i].change(tile_ID,TILE_ID);
			segment[t][i].change(tile_state,TILE_STATE);
			segment[t][i].change(object,OBJECT);
			segment[t][i].change(object_ID,OBJECT_ID);
			segment[t][i].change(status,STATUS);
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
void cGame::openDoors(int xx, int yy)
{
	

	if (segment[xx][yy].get(STATUS) == CLOSED_DOOR)	segment[xx][yy].change(OPENING_DOOR, STATUS);
	if (segment[xx][yy - 1].get(STATUS) == CLOSED_DOOR)	segment[xx][yy - 1].change(OPENING_DOOR, STATUS);
	if (segment[xx - 1][yy].get(STATUS) == CLOSED_DOOR)segment[xx - 1][yy].change(OPENING_DOOR, STATUS);
	if (segment[xx + 1][yy].get(STATUS) == CLOSED_DOOR)segment[xx + 1][yy].change(OPENING_DOOR, STATUS);
	if (segment[xx][yy + 1].get(STATUS) == CLOSED_DOOR)segment[xx][yy + 1].change(OPENING_DOOR, STATUS);
//	if (sprite[PLAYER].X() / TILE_SIZE == xx && sprite[PLAYER].Y() / TILE_SIZE == yy)
	
	//	if (segment[xx][yy].get(STATUS) == OPEN_DOOR)	segment[xx][yy].change(CLOSING_DOOR, STATUS);
		if (segment[xx][yy - 1].get(STATUS) == OPEN_DOOR)	segment[xx][yy - 1].change(CLOSING_DOOR, STATUS);
		if (segment[xx - 1][yy].get(STATUS) == OPEN_DOOR)segment[xx - 1][yy].change(CLOSING_DOOR, STATUS);
		if (segment[xx + 1][yy].get(STATUS) == OPEN_DOOR)segment[xx + 1][yy].change(CLOSING_DOOR, STATUS);
		if (segment[xx][yy + 1].get(STATUS) == OPEN_DOOR)segment[xx][yy + 1].change(CLOSING_DOOR, STATUS);
	
	keys[OPEN] = false;
}

cTile::cTile()
{
	
	int x=0;
	int y=0;
	int type=0;
	int ID_type=0;
	int state=0;
	int object=0;
	int ID_object=0;
	int status = 0;
}
cTile::cTile(int t, int ti, int s, int o, int oi, int stat)
{
	tile = t;
	tile_ID = ti;
	tile_state = s;
	object = o;
	object_ID = oi;
	status = s;
}
void cTile::draw(ALLEGRO_BITMAP *BMP)
{
	al_draw_bitmap_region(BMP, tile_state * 32, 0, 32, 32, 100, 100, NULL);
}
void cTile::change(int value, int tile_vars)
{
	switch (tile_vars)
	{
	case TILE: {tile = value; break; }
	case TILE_ID: {tile_ID = value; break; }
	case TILE_STATE: {tile_state = value; break; }
	case OBJECT: {object = value; break; }
	case OBJECT_ID: {object_ID = value; break; }
	case STATUS: {status = value; break; }
	case FRAME_COUNT: {frameCount = value; break; }
	case FRAME_DELAY: {frameDelay = value; break; }
	case ANIMATION_DIRECTION: {animationDirection = value; break; }
	}
		

}
int cTile::get(int tile_vars)
{
	switch (tile_vars)
	{
	case TILE: { return tile ; break; }
	case TILE_ID: { return tile_ID; break; }
	case TILE_STATE: { return tile_state; break; }
	case OBJECT: { return object; break; }
	case OBJECT_ID: { return object_ID; break; }
	case STATUS: { return status; break; }
	case FRAME_COUNT: { return frameCount; break; }
	case FRAME_DELAY: { return frameDelay; break; }
	case ANIMATION_DIRECTION: { return animationDirection; break; }
	}
	return NULL;
}
void cTile::inc(int value, int tile_vars)
{
	switch (tile_vars)
	{
	case TILE: 
	{
		tile += value; 
		if (tile >= MAX_TILE_TYPES) tile = 0;
		if (tile < 0) tile = MAX_TILE_TYPES - 1; break; 
	}
	case TILE_ID: 
	{
		tile_ID += value;
		if (tile_ID >= TILES_IN_ROW) tile_ID = 0;
		if (tile_ID < 0) tile_ID = TILES_IN_ROW - 1; break;
	}
	case TILE_STATE: {tile_state += value; break; }
	case OBJECT: 
	{
		object += value; 
		if (object >= MAX_TILE_OBJECT) object = 0;
		if (object < 0) object = MAX_TILE_OBJECT - 1; break; 
	}
	case OBJECT_ID: {object_ID += value; break; }//MAX_OBJECT_ID todo
	case STATUS: {status += value; break; }
	case FRAME_COUNT: {frameCount += value; break; }
	case FRAME_DELAY: {frameDelay += value; break; }
	case ANIMATION_DIRECTION: {animationDirection += value; break; }//todo -1,1
	}
}
void cTile::set(int t, int ti, int s, int o, int oi, int st)
{
	tile = t;
	tile_ID = ti;
	tile_state = s;
	object = o;
	object_ID = oi;
	status = st;

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
void cTile::setAnimation(int maxframe, int framedelay, int animationdirection)
{
	maxFrame = maxframe;
	curFrame = 0;
	frameCount = 0;
	frameDelay = framedelay;
	animationDirection = animationdirection;

}