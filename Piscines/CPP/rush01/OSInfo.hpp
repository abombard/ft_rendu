#ifdef _WIN32
const char *os = "Win32";
   #ifdef _WIN64
const char *os = "Win64";
   #endif
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
const char *os = "iOS Simulator";
    #elif TARGET_OS_IPHONE
const char *os = "iOS Device";
    #elif TARGET_OS_MAC
const char *os = "Mac Os";
    #else
const char *os = "unsupported platform";
    #endif
#elif __linux
const char *os = "Linux";
#elif __unix // all unices not caught above
const char *os = "Unix";
#elif __posix
const char *os = "Posix";
#endif

#ifndef OSINFO_HPP
# define OSINFO_HPP

# include "AMonitorModule.hpp"
# include <sys/utsname.h>

template< typename S >
class OSInfo : public AMonitorModule<S> {
public:
	OSInfo( S & screen ) : AMonitorModule<S>(screen) {
		if (os) {
			this->_infos.push_back(os);
			if (!std::strcmp(os, "Mac Os") || !std::strcmp(os, "Linux")) {
				struct utsname	sys;
				if ( uname(&sys) == 0 ) {
					std::string version(sys.version);
					this->_infos.push_back(version.substr(0, version.find(':')));
				}
			}
		}
		AMonitorModule<S>::setDisplay(screen, 50, 4, 0, 25);
	}
	
	OSInfo( OSInfo const &src ) : AMonitorModule<S>(src) { }
	
	virtual ~OSInfo(void) {
		if (this->_display)
			delete this->_display;
	}
	
	OSInfo &	operator=( OSInfo const &rhs ) {
		if ( this != &rhs ) {
			this->_info = rhs._info;
		}
		return *this;
	}
	
	virtual void		update( void ) {
		this->_display->update(this->_infos);
	}

private:
	OSInfo( void );
	std::list<std::string>	_infos;
	
protected: 
	
};


# endif
