#ifndef IMONITORMODULE_HPP
# define IMONITORMODULE_HPP

# include <iostream>

template < typename S >
class IMonitorModule {
public:
	IMonitorModule(void) {};
	IMonitorModule( S & screen ) { static_cast<void>(screen); };
	IMonitorModule( IMonitorModule const &src ) { static_cast<void>(src); };
	virtual ~IMonitorModule(void) {};
	virtual IMonitorModule &operator=( IMonitorModule const & rhs ) { static_cast<void>(rhs); return *this; };
	
	virtual void		update( void ) = 0;

};

# endif
