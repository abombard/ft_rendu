#ifndef USERINFO_HPP
# define USERINFO_HPP

# include "AMonitorModule.hpp"

template< typename S >
class UserInfo : public AMonitorModule<S> {
	public:
	UserInfo( S & screen ) : AMonitorModule<S>(screen) {
		char	buf[256];

		gethostname(buf, 256);
		this->_infos.push_back(std::string("HostName: ") + std::string(buf));
		this->_infos.push_back(std::string("UserName: ") + std::string(getenv("USER")));
		AMonitorModule<S>::setDisplay(screen, 50, 4, 0, 0);
	}
	
	UserInfo( UserInfo const &src ) : AMonitorModule<S>(src) { }
	
	virtual ~UserInfo(void) {
		if (this->_display)
			delete this->_display;
	}
	
	UserInfo &	operator=( UserInfo const &rhs ) {
		if ( this != &rhs ) {
			this->_info = rhs._info;
		}
		return *this;
	}
	
	virtual void		update( void ) {
		this->_display->update(this->_infos);
	}

private:
	UserInfo( void );
	std::list<std::string>	_infos;
	
protected: 
	
};


# endif
