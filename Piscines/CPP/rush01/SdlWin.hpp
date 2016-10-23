#ifndef SDLWIN_HPP
# define SDLWIN_HPP

# include <iostream>
# include <exception>
# include <SDL.h>
# include <SDL_ttf.h>
class SdlWin {
public:
	SdlWin(int width, int height);
	SdlWin( SdlWin const &src );
	~SdlWin(void);
	
	SdlWin &	operator=( SdlWin const & rhs );

	SDL_Window		*getWin() const;
	int				getWidth() const;
	int				getHeight() const;
	int			event( void ) const;
	void		putPixel(int x, int y, int col);
	void		flip();
	void		clear();

	void		ft_write_tty(const char *str);
	void		ft_write_on_screen(std::string str, int h, int x, int y, int color);
	void		ft_init_sdl_rect(int w, int h, int x, int y);
	void		ft_init_sdl_color(int r, int g, int b);
	void		draw_rectangle(int x,int y, int width, int height, int color);
	class SdlError {
		virtual const char* what() const throw() {
			return "Error loading Sdl";
		}
	};

private:
	SdlWin(void);
	SDL_Window	*_win;
	SDL_Renderer *_renderer;
	int			_width;
	int			_height;
	TTF_Font			*_font;
	SDL_Color 			color;
	SDL_Rect			pos;

protected: 

};

std::ostream &	operator<<( std::ostream & o, SdlWin const & i );

# endif
