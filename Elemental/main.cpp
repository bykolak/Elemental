#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "classes.h"
#include "define.h"
#include <iostream>
#include <exception>

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP * spritePNG = NULL;
ALLEGRO_BITMAP * tilesPNG = NULL;
sScroll scroll;
int main()
{
	//main loop bools
	
	bool done = false;
	bool render = true;
//INITIALIZATION
	al_init();
	int screen_width = SCREEN_WIDTH;
	int screen_height = SCREEN_HEIGHT;
	display = al_create_display(screen_width, screen_height);
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
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
	cGame *game = new cGame();
	game->loadGraphics();
	game->loadGame();
//	sScroll scroll;
	//===========MAIN LOOP
	while (!done)
	{
		
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//==========INPUT
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) // checks for window Xed
		{
			//game->saveGame();
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) //checks if mouse moved 
		{	
			game->updateMouse(ev.mouse.x,ev.mouse.y);
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)//if mouse button is pressed
		{

			if (ev.mouse.button & 1) //if left mouse button is pressed
			{ 
				game->updateMouse(ev.mouse.x, ev.mouse.y);
				
				game->useUI();
				game->newOrder();
			}
				
			if (ev.mouse.button & 2)	{  }//if right mouse button pressed
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)//if keyboard button is pressed
		{
			game->updateKeyboard(ev.keyboard.keycode, true);
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)//if keyboard button is released
		{
			game->updateKeyboard(ev.keyboard.keycode, false);
		}
		//========UPDATE LOGIC
		else if (ev.type == ALLEGRO_EVENT_TIMER) //if timer ticks
		{
			game->update();
			render = true;
		}
		//=========RENDERER
		if (render && al_is_event_queue_empty(event_queue))
		{
			game->draw();
			game->showDebug();
			al_flip_display();
			al_clear_to_color(BLACK);
			render = false;
		}

	}
	delete game;
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}