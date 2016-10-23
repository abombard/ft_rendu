#ifndef AMONITORDISPLAY_HPP
# define AMONITORDISPLAY_HPP

# include <iostream>
# include <list>
# include <string>
# include "IMonitorDisplay.hpp"

class Display : public IMonitorDisplay { // A DECLARER DANS UN FICHIER SEPARAY
protected:
	int			_width;
	int			_height;
	int			_x;
	int			_y;
private:
	Display(void);
	Display( Display const &src );
	Display &	operator=( Display const & rhs );
	
public:
	Display( int width, int height, int x, int y ) : _width(width), _height(height), _x(x), _y(y) {
		
	}
	virtual void	update(std::list<int> const & info) = 0;
	virtual void	update(std::list<std::string> const & infoName, std::list<long long> const & info) = 0;
	virtual void	update(std::list<std::string> const & info) = 0;
	virtual ~Display(void) {}
};

#endif
