#ifndef AMONITORMODULE_HPP
# define AMONITORMODULE_HPP

# include <iostream>
# include <list>
# include "IMonitorModule.hpp"
# include <unistd.h>
# include "SdlWin.hpp"
# include "NcWin.hpp"
# include "Display.hpp"

template < typename S >
class AMonitorModule : public IMonitorModule<S> {
public:
	AMonitorModule( S & screen ) : _screen(screen) { }
	AMonitorModule( AMonitorModule const &src ) : _screen(src._screen) { }
	virtual ~AMonitorModule<S>(void) {};
	AMonitorModule &	operator=( AMonitorModule const & rhs ) { *this = rhs; return *this; }
	
	virtual void		update( void ) = 0;

	void		setDisplay(SdlWin & win, int width, int height, int x, int y) {
		this->_display = new SdlDisplay(win, width, height, x, y);
	}
	
	void		setDisplay(NcWin & win, int width, int height, int x, int y) {
		this->_display = new NcursesDisplay(win, width, height, x, y);
	}
	

private:
	AMonitorModule(void);
	
protected: 
	S	&					_screen;
	Display	*				_display;

};

# endif
