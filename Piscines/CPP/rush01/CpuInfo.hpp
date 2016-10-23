#ifndef CPUINFO_HPP
# define CPUINFO_HPP

# include "AMonitorModule.hpp"
# include <sys/types.h>
# include <sys/sysctl.h>
# include <mach/vm_statistics.h>
# include <mach/mach_types.h>
# include <mach/mach_init.h>
# include <mach/mach_host.h>

template< typename S >
class CpuInfo : public AMonitorModule<S> {
public:
	CpuInfo( S & screen ) : AMonitorModule<S>(screen) {
		this->_previousTotalTicks = 0;
		this->_previousIdleTicks = 0;
		AMonitorModule<S>::setDisplay(screen, 390, 12, 0, 10);
	}
	
	CpuInfo( CpuInfo const &src ) : AMonitorModule<S>(src) { }
	
	virtual ~CpuInfo(void) {
		if (this->_display)
			delete this->_display;
	}
	
	CpuInfo &	operator=( CpuInfo const &rhs ) {
		if ( this != &rhs ) {
			this->_info = rhs._info;
		}
		return *this;
	}

	float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
		{
			unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
			unsigned long long idleTicksSinceLastTime  = idleTicks - _previousIdleTicks;
			float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);
			_previousTotalTicks = totalTicks;
			_previousIdleTicks  = idleTicks;
			return ret;
		}
	
	float GetCPULoad()
		{
			host_cpu_load_info_data_t cpuinfo;
			mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
			if ( host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpuinfo, &count) == KERN_SUCCESS )
			{
				unsigned long long totalTicks = 0;
				for (int i = 0; i < CPU_STATE_MAX; i++)
					totalTicks += cpuinfo.cpu_ticks[i];
				return CalculateCPULoad( cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks );
			}
			else return -1.0f;
		}
	
	virtual void		update( void ) {
		long long 	buf = 0;
		char		s[100];
		size_t		s_len = 100;
		size_t 		size = sizeof(buf);

		this->_infos.clear();
		this->_infosName.clear();

		// ******** CPU NAME ************ //
		if (sysctlbyname("machdep.cpu.brand_string", s, &s_len, NULL, 0) == 0) {
			this->_infosName.push_back(s);
			this->_infos.push_back(static_cast<long long>(0));
		}
		// ******** ACTIVE CPU ******** //
		if (sysctlbyname("hw.activecpu", &buf, &size, NULL, 0) == 0) {
			this->_infosName.push_back("Active Cores: ");
			this->_infos.push_back(static_cast<long long>(buf));
		}
		// ******* CPU FREQUENCY ****** //
		size = sizeof(buf);
		if (sysctlbyname("hw.cpufrequency", &buf, &size, NULL, 0) == 0) {
			this->_infosName.push_back("cpufrequency (Hz): ");
			this->_infos.push_back(static_cast<long long>(buf));
		}
		// ******* CLOCK RATE ****** //
		buf = static_cast<long long>(GetCPULoad() * 100.f);
		buf = buf == 100 ? 100 : buf + 1;
		this->_infosName.push_back("CPU load (\%): ");
		this->_infos.push_back(static_cast<long long>(buf));
		// ****** BUS FREQUENCY ****** //
		size = sizeof(buf);
		if ( sysctlbyname("hw.busfrequency", &buf, &size, NULL, 0) == 0 ) {
			this->_infosName.push_back("Bus Frequency (Hz): ");
			this->_infos.push_back(static_cast<long long>(buf));
		}
		this->_display->update(this->_infosName, this->_infos);
	}

private:
	CpuInfo( void );
	std::list<long long>		_infos;
	std::list<std::string> 	_infosName;
	unsigned long long _previousTotalTicks;
	unsigned long long _previousIdleTicks;
	
protected: 
	
};


# endif
