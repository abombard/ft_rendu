# include "SdlWin.hpp"
# include <SDL_ttf.h>

SdlWin::SdlWin( int width, int height ) : _width(width), _height(height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw SdlWin::SdlError();
	this->_win = SDL_CreateWindow("THUG LIFE", SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (this->_win == 0)
		throw SdlWin::SdlError();
	this->_renderer = SDL_CreateRenderer(this->_win, 0, SDL_RENDERER_ACCELERATED);
	if (TTF_Init() == -1)
		throw SdlWin::SdlError();
	if ((this->_font = TTF_OpenFont("ComicSans.ttf", 24)) == NULL)
		throw SdlWin::SdlError();
}

SdlWin::SdlWin( SdlWin const &src )
{
	*this = src;
}

SdlWin::~SdlWin(void)
{
	SDL_DestroyWindow(this->_win);
	SDL_Quit();
	TTF_Quit();
}

void		SdlWin::ft_write_tty(const char* str)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;

	surface = NULL;
	texture = NULL;
	if ((surface = TTF_RenderText_Blended(this->_font, str, this->color)) == NULL)
	{
		exit(-1);
	}
	if ((texture = SDL_CreateTextureFromSurface(this->_renderer, surface)) == 0)
	{
		exit(-1);
	}
	SDL_FreeSurface(surface);
	if (SDL_RenderCopy(this->_renderer, texture, NULL, &this->pos) < 0)
	{
		exit(-1);

	}
	SDL_DestroyTexture(texture);
}

void	SdlWin::draw_rectangle(int x, int y, int width, int height, int color)  {

	for (int xx = x; xx < width; ++xx) {

		for (int yy = y; yy < height; ++yy) {

			this->putPixel(x, y, color);
		}
	}
}

void    SdlWin::ft_write_on_screen(std::string str, int h, int x, int y, int color)
{

	ft_init_sdl_rect(str.length() * ((h + h) / 5), h, x, y);
	ft_init_sdl_color(color & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF);
	ft_write_tty(str.c_str());
}

void		SdlWin::ft_init_sdl_rect(int w, int h, int x, int y)
{
	this->pos.h = h;
	this->pos.w = w;
	this->pos.x = x;
	this->pos.y = y;
}

void		SdlWin::ft_init_sdl_color(int r, int g, int b)
{
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;	
}
int			SdlWin::event( void ) const{

	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		return -1;
	return 0;
}

SdlWin &	SdlWin::operator=( SdlWin const &rhs )
{
	if ( this != &rhs )
	{

	}
	return *this;
}

SDL_Window		*SdlWin::getWin() const {
	return this->_win;
}

int				SdlWin::getWidth() const {
	return this->_width;
}

int				SdlWin::getHeight() const {
	return this->_height;
}

void		SdlWin::putPixel(int x, int y, int col) {

	SDL_SetRenderDrawColor(this->_renderer, (col&0xFF0000)>>16, (col&0x00FF00)>>8, (col&0x0000FF),255);
	SDL_RenderDrawPoint(this->_renderer, x, y);
}

void		SdlWin::clear( void ) {

	SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->_renderer);
}

void		SdlWin::flip( void ) { 

	SDL_RenderPresent(this->_renderer);
}
