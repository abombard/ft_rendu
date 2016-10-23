#ifndef IMONITORDISPLAY_HPP
# define IMONITORDISPLAY_HPP

class IMonitorDisplay {
public:
	IMonitorDisplay(void) {};
	IMonitorDisplay( IMonitorDisplay const &src ) { static_cast<void>(src); };
	IMonitorDisplay &	operator=( IMonitorDisplay const & rhs ) { static_cast<void>(rhs); return *this; };
	IMonitorDisplay( int width, int height, int x, int y ) { static_cast<void>(width); static_cast<void>(height); static_cast<void>(x); static_cast<void>(y); }
	virtual void	update(std::list<int> const & info) = 0;
	virtual void	update(std::list<std::string> const & infoName, std::list<long long> const & info) = 0;
	virtual void	update(std::list<std::string> const & info) = 0;
	virtual ~IMonitorDisplay(void) {}
};

#endif
