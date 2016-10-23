#ifndef NETWORKINFO_HPP
# define NETWORKINFO_HPP

# include "AMonitorModule.hpp"
# include <sys/sysctl.h>
# include <netinet/in.h>
# include <net/if.h>
# include <net/route.h>

template< typename S >
class NetworkInfo : public AMonitorModule<S> {
public:
	NetworkInfo( S & screen ) : AMonitorModule<S>(screen) {
		
		AMonitorModule<S>::setDisplay(screen, 50, 6, 0, 29);
	}
	
	NetworkInfo( NetworkInfo const &src ) : AMonitorModule<S>(src) { }
	
	virtual ~NetworkInfo(void) {
		if (this->_display)
			delete this->_display;
	}
	
	NetworkInfo &	operator=( NetworkInfo const &rhs ) {
		if ( this != &rhs ) {
			this->_info = rhs._info;
		}
		return *this;
	}

	virtual void		update( void ) {

		this->_input.clear();
		this->_infos.clear();
		this->_infosName.clear();

		// ****** Network Info ****** //
		int mib[] = {
			CTL_NET,
			PF_ROUTE,
			0,
			0,
			NET_RT_IFLIST2,
			0
		};
		size_t len;
		if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0)
			return ;
		char buf[len];
		if (sysctl(mib, 6, buf, &len, NULL, 0) < 0)
			return ;
		char *lim = buf + len;
		char *next = NULL;
		long totalibytes = 0;
		long totalobytes = 0;
		for (next = buf; next < lim; ) {
			struct if_msghdr *ifm = (struct if_msghdr *)next;
			next += ifm->ifm_msglen;
			if (ifm->ifm_type == RTM_IFINFO2) {
				struct if_msghdr2 *if2m = (struct if_msghdr2 *)ifm;
				totalibytes += if2m->ifm_data.ifi_ibytes;
				totalobytes += if2m->ifm_data.ifi_obytes;
			}
		}

		this->_infosName.push_back("Network throughput input (Kb): ");
		this->_infos.push_back(static_cast<long long>(totalibytes / 8192));
		this->_infosName.push_back("Network throughput output (Kb): ");
		this->_infos.push_back(static_cast<long long>(totalobytes / 8192));

		this->_input.push_back(static_cast<int>(totalibytes / 100000));
		this->_display->update(this->_infosName, this->_infos);
		this->_display->update(this->_input);
	}

private:
	NetworkInfo( void );
	std::list<long long>		_infos;
	std::list<std::string> 		_infosName;
	std::list<int>				_input;

protected: 
	
};

# endif
