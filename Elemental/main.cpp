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

	int screen_width = SCREEN_WIDTH;
	int screen_height = SCREEN_HEIGHT;
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
	//float x = 0;
	//float y = 500;
	cGame game;
	game.mouseX = 0;
	game.mouseY = 0;
	
	game.loadgraphics();
	//game.sprite[PLAYER].loadPNG();
	game.loadGame();
	bool bound = false;
	int color = 0;
	game.scrollY = 0;
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
			game.mouseX = (ev.mouse.x + game.scrollX) / TILE_SIZE;
			game.mouseY = (ev.mouse.y + game.scrollY) / TILE_SIZE;
			game.mouseOnScreenX = ev.mouse.x;
			game.mouseOnScreenY = ev.mouse.y;
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
				case ALLEGRO_KEY_X: game.currentSprite++; break;
				case ALLEGRO_KEY_Z: game.currentSprite--; break;
				
			}
			if (game.currentSprite > MAX_SPRITES - 1)		{ game.currentSprite = 0; }
			if (game.currentSprite < 0)		{ game.currentSprite = MAX_SPRITES - 1; }
		
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
				game.segment[game.mouseX][game.mouseY].set(CLEAR_TILE);
			}
			if (game.keys[CLEAR_OBJECT])
			{ 
				game.segment[game.mouseX][game.mouseY].set(CLEAR_OBJECT);
			}
			if (game.keys[CREATE_FLOOR])
			{
				game.segment[game.mouseX][game.mouseY].set(CREATE_FLOOR);
			}
			if (game.keys[CREATE_WALL])
			{
				game.segment[game.mouseX][game.mouseY].set(CREATE_WALL);
			}
			if (game.keys[CREATE_DOOR])
			{
				game.segment[game.mouseX][game.mouseY].set(CREATE_DOOR);
			}
			game.updateSegment();
			
			for (int i = 0; i < MAX_SPRITES; i++)
			{
				game.sprite[i].update();
			}
			//IS004

			if (game.buttons[BUTTON_SCROLL_NORTH].overButton(game.mouseOnScreenX, game.mouseOnScreenY))
					{
						game.scrollY-=SCROLL_SPEED;
					}
			if (game.buttons[BUTTON_SCROLL_WEST].overButton(game.mouseOnScreenX, game.mouseOnScreenY))
					{
						game.scrollX -= SCROLL_SPEED;
					}
			if (game.buttons[BUTTON_SCROLL_EAST].overButton(game.mouseOnScreenX, game.mouseOnScreenY))
					{
						game.scrollX += SCROLL_SPEED;
					}
			if (game.buttons[BUTTON_SCROLL_SOUTH].overButton(game.mouseOnScreenX, game.mouseOnScreenY))
					{
						game.scrollY += SCROLL_SPEED;
					}
					if (game.scrollX < 0 - (SCREEN_WIDTH / 2))
					{
						game.scrollX = 0 - (SCREEN_WIDTH / 2);
					}
					if (game.scrollY < 0 - (SCREEN_HEIGHT / 2))
					{
						game.scrollY = 0 - (SCREEN_HEIGHT / 2);
					}

					if (game.scrollX >(MAP_X - 5) * TILE_SIZE)
					{
						game.scrollX = (MAP_X - 5)*TILE_SIZE;
					}
					if (game.scrollY > (MAP_Y-5)*TILE_SIZE)
					{
						game.scrollY = (MAP_Y-5)*TILE_SIZE;
					}
			render = true;
		}
		//=========RENDERER
		if (render && al_is_event_queue_empty(event_queue))
		{
			game.draw();
			game.show_debug();
			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				if (game.buttons[i].overButton(game.mouseOnScreenX, game.mouseOnScreenY))
					game.buttons[i].drawButton();
			}
			
			al_flip_display();
			al_clear_to_color(al_map_rgb(color, color, color));
			render = false;
		}

	}
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}