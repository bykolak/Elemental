#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "classes.h"
#include "define.h"

ALLEGRO_DISPLAY *display = NULL;
//ALLEGRO_BITMAP *segmentsBMP = NULL;


int main(int argc, char **argv)
{
	//main loop bools
	
	bool done = false;
	bool render = true;
	al_init();

	int screen_width = WIDTH;
	int screen_height = HEIGHT;
	display = al_create_display(screen_width, screen_height);
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	// LOADING GRAPHICS
	al_init_image_addon();
	int FPS = 60;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	float x = 0;
	float y = 500;
	int mx = 0;
	int my = 0;
	//cSegment segment(10, 10, 0);
	cGame map;
	map.loadgraphics();
	map.sprite[PLAYER].loadPNG();
	map.loadGame();
	int color = 0;
	//===========MAIN LOOP
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//==========INPUT
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) // checks for window Xed
		{
			map.saveGame();
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) //checks if mouse moved 
		{
			mx = ev.mouse.x / TILE_SIZE;
			my = ev.mouse.y / TILE_SIZE;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1) { map.segment[mx][my].change(EMPTY_OBJECT,OBJECT); }	//{ map.segment[mx][my].incTile(1); }//if left mouse button pressed			
			if (ev.mouse.button & 2)	{ map.segment[mx][my].change(CLOSED_DOOR,STATUS); map.segment[mx][my].change(DOOR,OBJECT); map.segment[mx][my].setAnimation(6, 3, 1); }//if right mouse button pressed
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_W: map.keys[UP] = true; break; //   map.generateNew(); break;
			case ALLEGRO_KEY_S: map.keys[DOWN] = true; break;
			case ALLEGRO_KEY_A: map.keys[LEFT] = true; break;
			case ALLEGRO_KEY_D: map.keys[RIGHT] = true; break;
			case ALLEGRO_KEY_E: map.keys[OPEN] = true; break;
			}
			if (x < 0) x = 0;
			if (y < 0) y = 0;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_W: map.keys[UP] = false; break;
			case ALLEGRO_KEY_S: map.keys[DOWN] = false; break;
			case ALLEGRO_KEY_A: map.keys[LEFT] = false; break;
			case ALLEGRO_KEY_D: map.keys[RIGHT] = false; break;
			case ALLEGRO_KEY_E: map.keys[OPEN] = false; break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (map.keys[UP])
			{ 
				if (map.wallCollision(NULL, -PLAYER_SPEED, PLAYER))
				{
					map.sprite[PLAYER].changeY(-PLAYER_SPEED);
				//	map.scrollY -= PLAYER_SPEED;
				}
		//		else if (map.wallCollision(PLAYER_SPEED, NULL, PLAYER)) map.sprite[PLAYER].changeX(PLAYER_SPEED);
				
			}
			if (map.keys[DOWN])
			{ 
				if (map.wallCollision(NULL, PLAYER_SPEED, PLAYER))
				{
					map.sprite[PLAYER].changeY(PLAYER_SPEED);
				//	map.scrollY += PLAYER_SPEED;
				}
			//	else if (map.wallCollision(PLAYER_SPEED, NULL, PLAYER)) map.sprite[PLAYER].changeX(PLAYER_SPEED);
			}
			if (map.keys[LEFT])
			{
				if (map.wallCollision(-PLAYER_SPEED, NULL, PLAYER))
				{
					map.sprite[PLAYER].changeX(-PLAYER_SPEED);
					//
				}
			}
			if (map.keys[RIGHT])
			{
				if (map.wallCollision(PLAYER_SPEED, NULL, PLAYER))
				{
					map.sprite[PLAYER].changeX(PLAYER_SPEED);
					//map.scrollX += PLAYER_SPEED;
				}
			}

			int xx = map.sprite[PLAYER].X() / TILE_SIZE;
			int yy = map.sprite[PLAYER].Y() / TILE_SIZE;

			
			if (map.keys[OPEN])
			{
				map.openDoors(xx, yy);

			}			// { color++; if (color > 255) color = 0; } //change background
			
			
			map.sprite[PLAYER].update();
			map.updateSegment();
			render = true;
		}
		//=========RENDERER
		if (render && al_is_event_queue_empty(event_queue))
		{
			map.draw();
			map.show_debug(mx, my);
			//		map.show_generable(mx,my);
			//	al_draw_textf(arial18, BLACK, 0, 0, NULL, "Segment: %i", segment.getState());
			al_flip_display();
			al_clear_to_color(al_map_rgb(color, color, color));
			render = false;
		}

	}
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}