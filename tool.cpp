#include "tool.h"

c_tool::c_tool()
{
}

c_tool::~c_tool()
{
}

void	c_tool::disk(SDL_Surface* surface, int cx, int cy, int rayon, unsigned long color)
{
	int	d;
	int	y;
	int	x;

	d = 3 - (2 * rayon);
	x = 0;
	y = rayon;

	while (y >= x)
	{
		line_horizontal(surface, cx - x, cy - y, 2 * x + 1, color);
		line_horizontal(surface, cx - x, cy + y, 2 * x + 1, color);
		line_horizontal(surface, cx - y, cy - x, 2 * y + 1, color);
		line_horizontal(surface, cx - y, cy + x, 2 * y + 1, color);
	 	if (d < 0)
			d = d + (4 * x) + 6;
		else
		{
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}

void	c_tool::rectangle(SDL_Surface* surface, int x, int y, int w, int h, unsigned long color)
{
	line_horizontal(surface, x, y, w, color);
	line_horizontal(surface, x, y + h - 1, w, color);
	line_vertical(surface, x, y + 1, h - 2, color);
	line_vertical(surface, x + w - 1, y + 1, h - 2, color);
}


void	c_tool::cercle(SDL_Surface* surface, int cx, int cy, int rayon, unsigned long color)
{
	int d;
	int y;
	int x;

	d = 5 - (4 * rayon);
	x = 0;
	
	y = rayon;
	while (x <= y)
	{
		set_pixel(surface, x + cx, y + cy, color);
		set_pixel(surface, y + cx, x + cy, color);
		set_pixel(surface, -x + cx, y +cy, color);
		set_pixel(surface, -y + cx, x + cy, color);
		set_pixel(surface, x + cx, -y + cy, color);
		set_pixel(surface, y + cx, -x + cy, color);
		set_pixel(surface, -x + cx, -y + cy, color);
		set_pixel(surface, -y + cx, -x + cy, color);

		if (d > 0)
		{
			y--;
			d = d - 8 * y;
		}
		x++;
		d = d + 8 * x + 4;
	}
}

unsigned long  c_tool::get_pixel(SDL_Surface* surface, int x, int y)
{
	int		bpp;
	unsigned char*	p;

	bpp = surface->format->BytesPerPixel;

	p = (unsigned char*)surface->pixels + y * surface->pitch + x * bpp;
	return *(unsigned long*)p;
}

void	c_tool::set_pixel(SDL_Surface *surface, int x, int y, unsigned long color)
{
	int		bpp;
	unsigned char*	p;

	bpp = surface->format->BytesPerPixel;

	if (x >= 0 && x < surface->w && y >= 0 && y < surface->h)
	{
		p = (unsigned char*)surface->pixels + y * surface->pitch + x * bpp;
		if (bpp == 4)
			*(unsigned long*)p = color;
	}
}

void c_tool::line_vertical(SDL_Surface* surface, int x, int y, int size, unsigned long color)
{
	SDL_Rect	r;

	r.y = y;
	r.x = x;
	r.w = 1;
	r.h = size;

	if (SDL_FillRect(surface, &r, color) == -1)
	{
		std::cout << "Tool | line_vertical | Error: " << SDL_GetError() << std::cout;
		return;
	}
}
void c_tool::line_horizontal(SDL_Surface* surface, int x, int y, int size, unsigned long color)
{
	SDL_Rect	r;

	r.y = y;
	r.x = x;
	r.w = size;
	r.h = 1;

	if (SDL_FillRect(surface, &r, color) == -1)
	{
		std::cout << "Tool | line_horizontal | Error: " << SDL_GetError() << std::cout;
		return;
	}
}

void c_tool::pen(SDL_Surface* surface, int x, int y, int size, unsigned long color)
{
	SDL_Rect	r;

	r.x = x;
	r.y = y;
	r.w = size;
	r.h = size;

	if (SDL_FillRect(surface, &r, color) == -1)
	{
		std::cout << "Tool | pen | Error: " << SDL_GetError() << std::cout;
		return;
	}
}

void c_tool::gum(SDL_Surface* surface, int x, int y, int size)
{
	SDL_Rect	r;

	r.x = x;
	r.y = y;
	r.w = size;
	r.h = size;

	if (SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, 255, 255, 255)) == -1)
	{
		std::cout << "Tool | gum | Error: " << SDL_GetError() << std::cout;
		return;
	}
}

int	c_tool::id_abs(int x)
{
	return	((x) > 0 ? (x) : (-x));
}

void	c_tool::change_int(int* x, int* y)
{
	int	t;
	t = *x;
	*x = *y;
	*y = t;
}

void	c_tool::draw_line(SDL_Surface* surface, int source_x, int source_y, int dest_x, int dest_y, unsigned long color, c_interface* init)
{
	int	d;
	int	dx;
	int	dy;
	int	aincr;
	int	bincr;
	int	xincr;
	int	yincr;
	int	x;
	int	y;

	if (id_abs(dest_x - source_x) < id_abs(dest_y - source_y))
	{
    		if (source_y > dest_y)
		{
			change_int(&source_x, &dest_x);
			change_int(&source_y, &dest_y);
		}
		xincr = dest_x > source_x ? 1 : -1;
		dy = dest_y - source_y;
		dx = id_abs(dest_x - source_x);
		d = 2 * dx - dy;
		aincr = 2 * (dx - dy);
		bincr = 2 * dx;
		x = source_x;
		y = source_y;
		if (init->type_tool == 1)
			disk(surface, x, y, init->size_tool, color);
		if (init->type_tool == 2)
			pen(surface, x, y, init->size_tool, color);
		if (init->type_tool == 5)
			gum(surface, x, y, init->size_tool);
		if (init->type_tool == 6)
			line_horizontal(surface, x, y, init->size_tool, color);
		if (init->type_tool == 7)
			line_vertical(surface, x, y, init->size_tool, color);
 		for (y = source_y + 1; y <= dest_y; ++y)
		{
			if (d >= 0)
			{
				x += xincr;
				d += aincr;
			}
			else
				d += bincr;
			if (init->type_tool == 1)
				disk(surface, x, y, init->size_tool, color);
			if (init->type_tool == 2)
				pen(surface, x, y, init->size_tool, color);
			if (init->type_tool == 5)
				gum(surface, x, y, init->size_tool);
			if (init->type_tool == 6)
				line_horizontal(surface, x, y, init->size_tool, color);
			if (init->type_tool == 7)
				line_vertical(surface, x, y, init->size_tool, color);
		}
	}
	else
	{
		if (source_x > dest_x)
		{
			change_int(&source_x, &dest_x);
			change_int(&source_y, &dest_y);
		}
		yincr = dest_y > source_y ? 1 : -1;
		dx = dest_x - source_x;
		dy = id_abs(dest_y - source_y);
		d = 2 * dy - dx;
		aincr = 2 * (dy - dx);
		bincr = 2 * dy;
		x = source_x;
		y = source_y;
		if (init->type_tool == 1)
			disk(surface, x, y, init->size_tool, color);
		if (init->type_tool == 2)
			pen(surface, x, y, init->size_tool, color);
		if (init->type_tool == 5)
			gum(surface, x, y, init->size_tool);
		if (init->type_tool == 6)
			line_horizontal(surface, x, y, init->size_tool, color);
		if (init->type_tool == 7)
			line_vertical(surface, x, y, init->size_tool, color);
 		for (x = source_x+1; x <= dest_x; ++x)
		{
			if (d >= 0)
			{
				y += yincr;
				d += aincr;
			}
			else
				d += bincr;
 			if (init->type_tool == 1)
				disk(surface, x, y, init->size_tool, color);
			if (init->type_tool == 2)
				pen(surface, x, y, init->size_tool, color);
			if (init->type_tool == 5)
				gum(surface, x, y, init->size_tool);
			if (init->type_tool == 6)
				line_horizontal(surface, x, y, init->size_tool, color);
			if (init->type_tool == 7)
				line_vertical(surface, x, y, init->size_tool, color);
    		}
	}
}

char	c_tool::selection(SDL_Event event, c_interface* init)
{
	int             continu;
	SDL_Rect        positionClic;
	SDL_Rect        positionDeplacement;
	SDL_Rect        positionRectangle;
	bool		click;

	click = false;
	continu = 1;
	while (continu)
	{
        	SDL_WaitEvent(&event);
	        if (event.type)
		{
			if (SDL_QUIT)
			{
/*				SDL_FreeSurface(init->close);
				SDL_FreeSurface(init->tab);
				SDL_FreeSurface(init->palette);
				SDL_FreeSurface(init->opt);
				SDL_FreeSurface(init->actu_color_left);
				SDL_FreeSurface(init->actu_color_right);
				SDL_FreeSurface(init->work);
				SDL_FreeSurface(init->get_screen());*/
				continu = 0;
			}
			if (SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					positionClic.x = event.button.x;
					positionClic.y = event.button.y;
					click = true;
				}
			}
			else if (SDL_MOUSEMOTION &&
				(event.motion.x >= 150) && (event.motion.y >= 25) &&
				(event.motion.x <= init->work_w + 150) && (event.motion.y <= init->work_h + 25))
			{
				if (click == true)
				{
					positionDeplacement.x = event.motion.x;
					positionDeplacement.y = event.motion.y;
					positionRectangle.w = abs(positionDeplacement.x - positionClic.x);
					positionRectangle.h = abs(positionDeplacement.y - positionClic.y);
					if(positionDeplacement.x < positionClic.x)
						positionRectangle.x = positionDeplacement.x;
					else
						positionRectangle.x = positionClic.x;
				}
			}
			else if (SDL_MOUSEBUTTONUP &&
				(event.motion.x >= 150) && (event.motion.y >= 25) &&
				(event.motion.x <= init->work_w + 150) && (event.motion.y <= init->work_h + 25))
				{
					if (event.button.button == SDL_BUTTON_LEFT)
						click = 0;
				}
			}
			if (SDL_FillRect(init->get_screen(), &positionRectangle, SDL_MapRGB(init->get_screen()->format, 136, 136, 136)) == -1)
			{
				std::cout << "Tool | selection | Error: " << SDL_GetError() << std::endl;
				return -1;
			}
			if (SDL_Flip(init->get_screen()) == -1)
			{
				std::cout << "Tool | selection | Error: " << SDL_GetError() << std::endl;
				return -1;
			}
	}
	return 0;
}

