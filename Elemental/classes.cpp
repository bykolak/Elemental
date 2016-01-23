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
int cPlayer::X()
{
	return x;
}
int cPlayer::Y()
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



	al_draw_bitmap_region(playerPNG, curFrame*TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE, x, y, NULL);
	al_draw_bitmap_region(playerPNG,curFrame*TILE_SIZE,0, TILE_SIZE, TILE_SIZE, x, y, NULL); // draw player;
}
cGame::cGame()
{

	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			segment[t][i].changeTile(EMPTY_TILE);
		}
	arial10 = al_load_font("arial.ttf", 10, NULL);
	arial18 = al_load_font("arial.ttf", 18, NULL);

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
		
			if (segment[t][i].getTile() == FLOOR_TILE)
			{
				
					al_draw_bitmap_region(tilesPNG, segment[t][i].getTileID()*TILE_SIZE, TILE_Y, TILE_SIZE, TILE_SIZE, t*TILE_SIZE, i *TILE_SIZE, NULL);
				
				if (segment[t][i - 1].getTile() == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, t*TILE_SIZE, (i - 1)*TILE_SIZE, NULL);//north wall
				
				if (segment[t - 1][i].getTile() == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, 0, TILE_SIZE, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE, i *TILE_SIZE, NULL);//west wall
				
				if (segment[t + 1][i].getTile() == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE, i *TILE_SIZE, NULL);//east wall
				
				if (segment[t][i + 1].getTile() == WALL_TILE)
					al_draw_bitmap_region(tilesPNG, TILE_SIZE, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, t*TILE_SIZE, (i + 1)*TILE_SIZE, NULL);//south wall


				

				if (segment[t - 1][i - 1].getTile() == WALL_TILE && segment[t - 1][i].getTile() == WALL_TILE && segment[t ][i-1].getTile() == WALL_TILE)
				{
					al_draw_bitmap_region(tilesPNG, 0, 0, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE, (i - 1)*TILE_SIZE, NULL);//north-west wall
				}
							
				if (segment[t + 1][i - 1].getTile() == WALL_TILE && segment[t + 1][i].getTile() == WALL_TILE && segment[t][i-1].getTile() == WALL_TILE)
				{
					
					al_draw_bitmap_region(tilesPNG, TILE_SIZE * 2, 0, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE, (i - 1)*TILE_SIZE, NULL);//north-east wall
				}
									
				if (segment[t - 1][i + 1].getTile() == WALL_TILE && segment[t - 1][i].getTile() == WALL_TILE && segment[t][i + 1].getTile() == WALL_TILE)

					al_draw_bitmap_region(tilesPNG,0 , TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, (t - 1)*TILE_SIZE, (i + 1)*TILE_SIZE, NULL);//south-west wall
				
				if (segment[t + 1][i + 1].getTile() == WALL_TILE && segment[t + 1][i].getTile() == WALL_TILE && segment[t ][i+1].getTile() == WALL_TILE)

					al_draw_bitmap_region(tilesPNG, TILE_SIZE*2, TILE_SIZE*2, TILE_SIZE, TILE_SIZE, (t + 1)*TILE_SIZE, (i + 1)*TILE_SIZE, NULL);//south-east wall

			}
			if (segment[t][i].getObject() == DOOR)
			{
				drawDoor(t,i);
			}

		
		
		}
	player.draw();
	//al_draw_bitmap_region(tilesPNG, 0, TILE_SIZE * 12, TILE_SIZE, TILE_SIZE, player.X(), player.Y(), NULL); // draw player;
}

void cGame::drawDoor(int x, int y)
{
	ALLEGRO_BITMAP* door = NULL;
	if (segment[x][y - 1].getTile() == WALL_TILE && segment[x][y + 1].getTile() == WALL_TILE)//east -west
	{
		door = al_create_sub_bitmap(tilesPNG, TILE_SIZE*segment[x][y].getObjectID(), TILE_SIZE * 6, TILE_SIZE, TILE_SIZE);
		al_draw_rotated_bitmap(door, TILE_SIZE/2, TILE_SIZE/2, x *TILE_SIZE, y *TILE_SIZE+(TILE_SIZE/2), DEGREE_90, NULL);;
	}
		


	if (segment[x- 1][y].getTile() == WALL_TILE &&segment[x + 1][y].getTile() == WALL_TILE)//north-south
		al_draw_bitmap_region(tilesPNG, segment[x][y].getObjectID()*TILE_SIZE, 6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, x *TILE_SIZE, y *TILE_SIZE, NULL);
}

void cGame::show_debug(int mx, int my)
{
	al_draw_textf(arial10, GREEN, 0, 0, NULL, "player.x:%d", player.X());
	al_draw_textf(arial10, GREEN, 0, 15, NULL, "player.y:%d", player.Y());
	al_draw_textf(arial10, GREEN, mx*TILE_SIZE, my*TILE_SIZE - 30, NULL, "x:%d", mx);
	al_draw_textf(arial10, GREEN, mx*TILE_SIZE, my*TILE_SIZE - 15, NULL, "y:%d", my);
	al_draw_textf(arial10, RED, mx*TILE_SIZE, my*TILE_SIZE, NULL, "tile:%d", segment[mx][my].getTile());
	al_draw_textf(arial10, RED, mx*TILE_SIZE, my*TILE_SIZE + 15, NULL, "tile_ID:%d", segment[mx][my].getTileID());
	al_draw_textf(arial10, RED, mx*TILE_SIZE, my*TILE_SIZE + 30, NULL, "Object:%d", segment[mx][my].getObject());
	al_draw_textf(arial10, RED, mx*TILE_SIZE, my*TILE_SIZE + 45, NULL, "Object_ID:%d", segment[mx][my].getObjectID());
}

void cGame::saveGame()
{
		ALLEGRO_FILE* save_game = al_fopen("test.map", "wb");
		int x=player.X();
		int y = player.Y();
		al_fwrite(save_game, &x , sizeof(int));
		al_fwrite(save_game, &y, sizeof(int));
	
		for (int i = 0; i < MAP_Y; i++)
			for (int t = 0; t < MAP_X; t++)
			{
				int tile =segment[t][i].getTile();
				int tile_ID= segment[t][i].getTileID();
				int tile_state = segment[t][i].getTileState();
				int object = segment[t][i].getObject();
				int object_ID = segment[t][i].getObjectID();
		
				al_fwrite(save_game, &tile, sizeof(int));
				al_fwrite(save_game, &tile_ID, sizeof(int));
				al_fwrite(save_game, &tile_state, sizeof(int));
				al_fwrite(save_game, &object, sizeof(int));
				al_fwrite(save_game, &object_ID, sizeof(int));
				
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
	
	al_fread(save_game, &x, sizeof(int));
	al_fread(save_game, &y, sizeof(int));
	player.changeX(x);
	player.changeY(y);
	for (int i = 0; i < MAP_Y; i++)
		for (int t = 0; t < MAP_X; t++)
		{
			al_fread(save_game, &tile, sizeof(int));
			al_fread(save_game, &tile_ID, sizeof(int));
			al_fread(save_game, &tile_state, sizeof(int));
			al_fread(save_game, &object, sizeof(int));
			al_fread(save_game, &object_ID, sizeof(int));
			segment[t][i].changeTile(tile);
			segment[t][i].changeTileID(tile_ID);
			segment[t][i].changeTileState(tile_state);
			segment[t][i].changeObject(object);
			segment[t][i].changeObjectID(object_ID);
		}
	al_fclose(save_game);
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
}
cTile::cTile(int t, int ti, int s, int o, int oi)
{
	tile = t;
	tile_ID = ti;
	tile_state = s;
	object = o;
	object_ID = oi;
}
void cTile::draw(ALLEGRO_BITMAP *BMP)
{
	al_draw_bitmap_region(BMP, tile_state * 32, 0, 32, 32, 100, 100, NULL);
}
void cTile::changeTileState(int _state)
{
	tile_state += _state;
	if (tile_state < 0) tile_state = 0;
	if (tile_state > 14) tile_state = 14;
}
void cTile::changeTile(int temp)
{
	tile = temp;
}
void cTile::incTile(int temp)
{
	tile += temp;
	if (tile >= MAX_TILE_TYPES) tile = 0;
	if (tile < 0) tile = MAX_TILE_TYPES - 1;

}
void cTile::incTileID(int temp)
{
	tile_ID += temp;
	if (tile_ID >= TILES_IN_ROW) tile_ID = 0;
	if (tile_ID < 0) tile_ID = TILES_IN_ROW - 1;

}
void cTile::incObject(int temp)
{
	object += temp;
	if (object >= MAX_TILE_OBJECT) object = 0;
	if (object < 0) object = MAX_TILE_OBJECT - 1;

}
void cTile::changeTileID(int temp)
{
	tile_ID = temp;
}

void cTile::changeObjectID(int temp)
{
	object_ID = temp;
}
int cTile::getObjectID()
{
	return object_ID;
}
int cTile::getTileID()
{
	return tile_ID;
}
void cTile::changeObject(int _object)
{
	object = _object;
}
int cTile::getTileState()
{
	return tile_state;
}

int cTile::getTile()
{
	return tile;
}
int cTile::getObject()
{
	return object;
}

void cTile::setSegment(int t, int ti, int s, int o, int oi)
{
	tile = t;
	tile_ID = ti;
	tile_state = s;
	object = o;
	object_ID = oi;

}

