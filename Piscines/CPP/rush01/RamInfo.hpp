#ifndef RAMINFO_HPP
# define RAMINFO_HPP

# include "AMonitorModule.hpp"

template< typename S >
class RamInfo : public AMonitorModule<S> {
public:
	RamInfo( S & screen ) : AMonitorModule<S>(screen) {
			AMonitorModule<S>::setDisplay(screen, 50, 6, 0, 4);
	}
	
	RamInfo( RamInfo const &src ) : AMonitorModule<S>(src) { }
	
	virtual ~RamInfo(void) {
		if (this->_display)
			delete this->_display;
	}
	
	RamInfo &	operator=( RamInfo const &rhs ) {
		if ( this != &rhs ) {
			this->_info = rhs._info;
		}
		return *this;
	}
	
	virtual void		update( void ) {
		long long 	buf = 0;
		size_t 		size = sizeof(buf);

		this->_infos.clear();
		this->_infosName.clear();

/*		// ****** Total Ram ****** //
		size = sizeof(buf);
		if ( sysctlbyname("hw.memsize", &buf, &size, NULL, 0) == 0 ) {
			this->_infosName.push_back("Ram Total: ");
			this->_infos.push_back(static_cast<long long>(buf));
		}
*/
		// ****** Phys MEM ****** //
		size = sizeof(buf);
		if ( sysctlbyname("hw.physmem", &buf, &size, NULL, 0) == 0 ) {
			this->_infosName.push_back("Ram Total (Kb): ");
			this->_infos.push_back(static_cast<long long>(buf / 8192));
		}

		// ****** Used MEM ****** //
		size = sizeof(buf);
		if ( sysctlbyname("hw.usermem", &buf, &size, NULL, 0) == 0 ) {
			this->_infosName.push_back("Ram Used (Kb): ");
			this->_infos.push_back(static_cast<long long>(buf / 8192));
		}
		this->_display->update(this->_infosName, this->_infos);
	}

private:
	RamInfo( void );
	std::list<long long>		_infos;
	std::list<std::string> 	_infosName;
	
protected: 
	
};


# endif
