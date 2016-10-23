#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include <iostream>
#include <list>
#include <string>
#include "AMonitorDisplay.hpp"

class SdlDisplay : public Display {
private:
	SdlWin &	_screen;
	SdlDisplay(void);
	SdlDisplay( SdlDisplay const &src );
	SdlDisplay &	operator=( SdlDisplay const & rhs );
	
public:
	SdlDisplay( SdlWin & screen, int width, int height, int x, int y ) : Display(width , height, x * 10, y * 20), _screen(screen) {}
	void			draw_line(int x, int y, int x_max, int y_max) {
		while (x < x_max) {
			_screen.putPixel(x, y, 0xFF0000);
			++x;
		}
		while (y < y_max) {
			_screen.putPixel(x, y, 0xFF0000);
			++y;
		}
	}

	void			draw_rectangle(int x, int y, int w, int h) {
		draw_line(x, y, w, y);
		draw_line(x, y, x, h);
		draw_line(x, h, w, h);
		draw_line(w, y, w, h);
	}

	virtual void	update(std::list<int> const & info) {
		(void)info;
	}

	virtual void	update(std::list<std::string> const & infoName, std::list<long long> const & info) {
		draw_rectangle(_x, _y, _x + 398, _y + (_height * 18));
		int y = this->_y + 1;
		std::list<std::string>::const_iterator itn = infoName.begin();
		for (std::list<long long>::const_iterator it = info.begin(); it != info.end(); ++it, ++itn) {
			this->_screen.ft_write_on_screen(*itn, 22, this->_x + 10, y, 0xFFFFFF);
			y += 22;
			if (*it) {
				this->_screen.ft_write_on_screen(std::to_string(*it), 22, this->_x + 20, y, 0xFFFFFF);
				y += 22;
			}
		}
	}
	virtual void	update(std::list<std::string> const & info) {
		draw_rectangle(_x, _y, _x + 398, _y + (_height * 17));
		int y = this->_y + 1;
		for (std::list<std::string>::const_iterator it = info.begin(); it != info.end(); ++it) {
			this->_screen.ft_write_on_screen(*it, 22, this->_x + 10, y, 0xFFFFFF);
			y += 22;
		}

	}
	virtual ~SdlDisplay(void) {}
};

class NcursesDisplay : public Display{
	private:
		NcWin &		_screen;
		NcursesDisplay(void);
		NcursesDisplay( NcursesDisplay const &src );
		NcursesDisplay &	operator=( NcursesDisplay const & rhs );

	public:
		NcursesDisplay( NcWin & screen, int width, int height, int x, int y ) : Display(width, height, x, y), _screen(screen) {}
		virtual void	update(std::list<int> const & info) {
			static_cast<void>(info);
		}
		virtual void	update(std::list<std::string> const & infoName, std::list<long long> const & info) {
			_screen.drawBorder(this->_x, this->_y, this->_width, this->_height);
			int y = this->_y + 1;
			std::list<std::string>::const_iterator itn = infoName.begin();
			for (std::list<long long>::const_iterator it = info.begin(); it != info.end(); ++it, ++itn) {
				this->_screen.draw(*itn, this->_x + 1, y++);
				if (*it)
					this->_screen.draw(std::to_string(*it), this->_x + 1, y++);
			}
		}
		virtual void	update(std::list<std::string> const & info) {
			_screen.drawBorder(this->_x, this->_y, this->_width, this->_height);
			int y = this->_y + 1;
			for (std::list<std::string>::const_iterator it = info.begin(); it != info.end(); ++it) {
				this->_screen.draw(*it, this->_x + 1, y);
				y += 1;
			}
		}
		virtual ~NcursesDisplay(void) {}

};

#endif
