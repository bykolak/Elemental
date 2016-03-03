#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "classes.h"
#include "define.h"

ALLEGRO_DISPLAY *display = NULL;

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
	cGame game;
	game.mx = 0;
	game.my = 0;
	game.loadgraphics();
	game.sprite[PLAYER].loadPNG();
	game.loadGame();
	bool bound = false;
	int color = 0;
	//===========MAIN LOOP
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//==========INPUT
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) // checks for window Xed
		{
			game.saveGame();
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) //checks if mouse moved 
		{
			game.mx = ev.mouse.x / TILE_SIZE;
			game.my = ev.mouse.y / TILE_SIZE;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{ 
				game.new_order();
			}
				
			if (ev.mouse.button & 2)	{  }//if right mouse button pressed
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_1: game.keys[CLEAR_TILE] = true; break; 
			case ALLEGRO_KEY_2: game.keys[CLEAR_OBJECT] = true; break;
			case ALLEGRO_KEY_3: game.keys[CREATE_FLOOR] = true; break;
			case ALLEGRO_KEY_4: game.keys[CREATE_WALL] = true; break;
			case ALLEGRO_KEY_5: game.keys[CREATE_DOOR] = true; break;
			}
			if (x < 0) x = 0;
			if (y < 0) y = 0;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_1: game.keys[CLEAR_TILE] = false; break;
			case ALLEGRO_KEY_2: game.keys[CLEAR_OBJECT] = false; break;
			case ALLEGRO_KEY_3: game.keys[CREATE_FLOOR] = false; break;
			case ALLEGRO_KEY_4: game.keys[CREATE_WALL] = false; break;
			case ALLEGRO_KEY_5: game.keys[CREATE_DOOR] = false; break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (game.keys[CLEAR_TILE])
			{ 
				game.segment[game.mx][game.my].set(CLEAR_TILE);
			}
			if (game.keys[CLEAR_OBJECT])
			{ 
				game.segment[game.mx][game.my].set(CLEAR_OBJECT);
			}
			if (game.keys[CREATE_FLOOR])
			{
				game.segment[game.mx][game.my].set(CREATE_FLOOR);
			}
			if (game.keys[CREATE_WALL])
			{
				game.segment[game.mx][game.my].set(CREATE_WALL);
			}
			if (game.keys[CREATE_DOOR])
			{
				game.segment[game.mx][game.my].set(CREATE_DOOR);
			}
			game.updateSegment();
			
		//	for (int i = 0; i > MAX_SPRITES; i++)
		//	{
				game.sprite[PLAYER].update();
		//	}
			
			render = true;
		}
		//=========RENDERER
		if (render && al_is_event_queue_empty(event_queue))
		{
			game.draw();
			game.show_debug();
			al_flip_display();
			al_clear_to_color(al_map_rgb(color, color, color));
			render = false;
		}

	}
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}