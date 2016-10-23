#ifndef TIMEINFO_HPP
# define TIMEINFO_HPP

# include "AMonitorModule.hpp"

template< typename S >
class TimeInfo : public AMonitorModule<S> {
public:
	TimeInfo( S & screen ) : AMonitorModule<S>(screen) {
		AMonitorModule<S>::setDisplay(screen, 50, 3, 0, 22);
	}
	
	TimeInfo( TimeInfo const &src ) : AMonitorModule<S>(src) { }
	
	virtual ~TimeInfo(void) {
		if (this->_display)
			delete this->_display;
	}
	
	TimeInfo &	operator=( TimeInfo const &rhs ) {
		if ( this != &rhs ) {
			this->_info = rhs._info;
		}
		return *this;
	}
	
	virtual void		update( void ) {
		time_t t = time(NULL);
		tm* tm = localtime(&t);
		std::string ret = "[" + std::to_string(tm->tm_mday) + "/"
			+ std::to_string(tm->tm_mon + 1) + "/"
			+ std::to_string(tm->tm_year + 1900)
			+ "/" + "_" + std::to_string(tm->tm_hour)
			+ ":" + std::to_string(tm->tm_min) + ":"
			+ std::to_string(tm->tm_sec) + "] ";
		this->_infos.remove(*this->_infos.begin());
		this->_infos.push_back(ret);
		this->_display->update(this->_infos);
	}

private:
	TimeInfo( void );
	std::list<std::string>	_infos;
	
protected: 
	
};


# endif
