#ifndef LIBRARY_H
	#define LIBRARY_H
	#include "../../header/dessine.h"
	#include "../../header/goban.h"
	#include "../../header/menu.h"
#endif

#include <string.h>


int largeur_fenetre;
int hauteur_fenetre;

GC      gc;
Display *display;
int     screen;
Window  win, root;
XWindowAttributes attr;


extern void draw_plateau(int width, int height);
extern bool getInitialized();
extern void refresh_plateau(int width, int height);
extern void refresh_manager(int width, int height);
extern void draw_menu_load(int width, int height);
extern void mouse_clicked(int bouton, int x, int y);
extern void key_pressed(KeySym code, char c, int x_souris, int y_souris);


int width_win()
{
	return largeur_fenetre;
}

int height_win()
{
	return hauteur_fenetre;
}

void init_win(int w, int h, char* message, float r, float g, float b)
{
	if ((display = XOpenDisplay ("")) == NULL)
	{
		fprintf (stderr, "Can't open Display\n");
		exit (1);
	}

	largeur_fenetre = w;
	hauteur_fenetre = h;
	// recupere param pour creation fenetre
	gc = DefaultGC (display, screen);
	screen = DefaultScreen (display);
	root = RootWindow (display, screen);

	int rr = 255*r;
	int gg = 255*g;
	int bb = 255*b;
	unsigned long col_pixel = rr<<16|gg<<8|bb;
	unsigned long black_pixel = BlackPixel (display, screen);
	// creation fenetre
	win = XCreateSimpleWindow (display, root, 0, 0, largeur_fenetre, hauteur_fenetre, 5, black_pixel, col_pixel);
	// filtre les evenements
	XSelectInput (display, win, ExposureMask|ButtonPressMask|KeyPressMask);
	// titre fenetre
	XStoreName (display, win, message);
	XMapWindow (display, win);
}


void event_loop()
{
	char buffer[8];
	KeySym touche;
	int nb;
	XEvent ev;

	while(1)
	{
		XNextEvent (display, &ev);
		XGetWindowAttributes(display, win, &attr);

		switch (ev.type)
		{
		case Expose :
			printf("\n\n===EXPOSE===\nlargeur = %d\nhauteur = %d\n",attr.width,attr.height);
			largeur_fenetre = attr.width;
			hauteur_fenetre = attr.height;
			if(getInitialized()) {
				refresh_plateau(largeur_fenetre, hauteur_fenetre);
			} else {
				refresh_manager(largeur_fenetre, hauteur_fenetre);
			}
			break;
		case ButtonPress:
			mouse_clicked(ev.xbutton.button,ev.xbutton.x,ev.xbutton.y);
			break;
		case KeyPress:
			if ( ev.xkey.keycode == 0x09 ) // ESC : on sort
				exit(0);
			nb = XLookupString((XKeyEvent*)&ev, buffer, 20, &touche, 0);
			buffer[nb] = 0;
			break;
		default :
			break;
		}
	}
}

void clear_win()
{
	XClearWindow(display, win);
}

void color(float r, float v, float b)
{
	int rr = 255*r;
	int vv = 255*v;
	int bb = 255*b;
	XSetForeground (display, gc, 256*256*rr+256*vv+bb);
}


void filled_rectangle(int x, int y, int w, int h)
{
	XFillRectangle(display,win,gc,x,y,w,h);
}

void rectangle(int x, int y, int w, int h)
{
	XDrawRectangle(display,win,gc,x,y,w,h);
}

void filled_circle(int x, int y, int r)
{
	XFillArc(display,win,gc,x-r,y-r,2*r,2*r,0,360*64);
}

void circle(int x, int y, int r)
{
	XDrawArc(display,win,gc,x-r,y-r,2*r,2*r,0,360*64);
}


void line(int x0, int y0, int x1, int y1)
{
	XDrawLine(display,win,gc,x0,y0,x1,y1);
}


void pixel(int x, int y)
{
	XDrawPoint(display,win,gc,x,y);
}

void string(int x, int y, char* chaine)
{
	XDrawString(display,win,gc,x,y, chaine, strlen(chaine));
}

void resize_window (int width, int height)
{
	if(height == 0) {
		height = attr.height;
	}
	if(width == 0) {
		width = attr.width;
	}
	XResizeWindow(display, win, width, height);
}

void xflush() {
	XFlush(display);
}
