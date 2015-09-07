#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#define USE_CONSOLE
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

const double FPS = 100;
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;
const int BALL_SIZE = 200;

void fatal_error(char* message) {
	fprintf(stderr, "%s\n", message);
	fprintf(stderr, "Sorry.\n");

#ifdef WIN32
	fprintf(stderr, "Press ENTER to exit the program.\n");
	getchar();
#endif

	exit(EXIT_FAILURE);
}

int inuti(double x, double y, double x1, double y1, double x2, double y2) {
	int x_inuti;
	int y_inuti;

	if (x1 < x2)
		x_inuti = x > x1 && x < x2;
	else
		x_inuti = x > x2 && x < x1;
	if (y1 < y2)
		y_inuti = y > y1 && y < y2;
	else
		y_inuti = y > y2 && y < y1;
	return x_inuti && y_inuti;
}


int main(int argc, char *argv[]) {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	double x_pos = SCREEN_WIDTH / 2;
	double y_pos = SCREEN_HEIGHT / 2;
	double delta_x = 2.5;
	double delta_y = 0.5;
	double mouse_x = -1;
	double mouse_y = -1;
	int please_redraw = 1;

	if (!al_init()) {
		fatal_error("Couldn't initialize allegro.");
	}

	if (!al_init_primitives_addon()) {
		fatal_error("Couldn't initialize allegro addons.");
	}

	if (!al_install_keyboard()) {
		fatal_error("Couldn't initialize keyboard.");
	}

	if (!al_install_mouse()) {
		fatal_error("Couldn't initialize mouse.");
	}

	timer = al_create_timer(1.0 / FPS);
	if (timer == NULL) {
		fatal_error("Couldn't create timer.");
	}

	// Attempts full screen
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (display == NULL) {
		// Attempts a window instead
		fprintf(stderr, "Fullscreen failed, trying a window...\n");
		al_set_new_display_flags(ALLEGRO_WINDOWED);
		display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
		if (display == NULL) {
			fatal_error("Couldn't create display.");
		}
	}

	event_queue = al_create_event_queue();
	if (event_queue == NULL) {
		al_destroy_display(display);
		al_destroy_timer(timer);
		fatal_error("Couldn't create event_queue.");
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	// The big game loop

	while (1) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			x_pos += delta_x;
			y_pos += delta_y;
			please_redraw = 1;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
			ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
			mouse_x = ev.mouse.x;
			mouse_y = ev.mouse.y;
			please_redraw = 1;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			break;
		}

		if (please_redraw && al_is_event_queue_empty(event_queue)) {
			please_redraw = 0;

			al_set_target_bitmap(al_get_backbuffer(display));

			al_clear_to_color(al_map_rgb(0, 255, 0));
			al_draw_filled_rectangle(x_pos, y_pos, x_pos + BALL_SIZE, y_pos + BALL_SIZE, al_map_rgb(20, 140, 50));
			al_draw_filled_rectangle(mouse_x, mouse_y, mouse_x + 10, mouse_y + 10, al_map_rgb(0, 0, 0));

			al_flip_display();
		}
		
		/* Pointer-stop */
		if (inuti(mouse_x, mouse_y, x_pos, y_pos, x_pos + BALL_SIZE, y_pos + BALL_SIZE) == 1){
			delta_x = 0;
			delta_y = 0;
		}
		else if ((inuti(mouse_x, mouse_y, x_pos, y_pos, x_pos + BALL_SIZE, y_pos + BALL_SIZE) == 0) && (delta_x == 0 && delta_y == 0)){
			delta_x = 2.5;
			delta_y = 0.5;
		}

		if (x_pos + BALL_SIZE >= SCREEN_WIDTH){ //Right side
			delta_x = (-1.0)*delta_x;
			delta_y = (1.0)*delta_y;
		}
		else if (x_pos <= 0){ // Left
			delta_x = (-1.0)*delta_x;
			delta_y = (1.0)*delta_y;
		}
		else if (y_pos <= 0){ // Upper side
			delta_x = (1.0)*delta_x;
			delta_y = (-1.0)*delta_y;
		}
		else if (y_pos + BALL_SIZE >= SCREEN_HEIGHT){ //Lower side
			delta_x = (1.0)*delta_x;
			delta_y = (-1.0)*delta_y;
		}
	}
		
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	printf("Goodbye.\n");
#ifdef WIN32
	printf("Press ENTER to exit the program.\n");
	_getch();
#endif

	return EXIT_SUCCESS;
}