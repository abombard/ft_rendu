# include <iostream>
# include <unistd.h>
# include "SdlWin.hpp"
# include "NcWin.hpp"
# include "UserInfo.hpp"
# include "OSInfo.hpp"
# include "TimeInfo.hpp"
# include "CpuInfo.hpp"
# include "RamInfo.hpp"
# include "NetworkInfo.hpp"

template < typename T >
void	loop(T & screen) {
	UserInfo<T> 	userInfo(screen);
	OSInfo<T>		osInfo(screen);
	TimeInfo<T>		timeInfo(screen);
	CpuInfo<T>		cpuInfo(screen);
	RamInfo<T>		ramInfo(screen);
	NetworkInfo<T>	networkInfo(screen);

	while (1) {
		screen.clear();
		userInfo.update();
		osInfo.update();
		timeInfo.update();
		cpuInfo.update();
		ramInfo.update();
		networkInfo.update();
		screen.flip();
		if (screen.event() == -1)
			break ;
		usleep(170000);
	}
}

void	sig_handler(int sig)
{
	static_cast<void>(sig);
}

int main(int ac, char **av) {
	signal(SIGINT, &sig_handler);
	signal(SIGTERM, &sig_handler);	
	signal(SIGSTOP, &sig_handler);
	signal(SIGTSTP, &sig_handler);
	if (ac == 2) {
		std::string s(av[1]);
		if ( s.compare("ncurses") == 0 ) {
			NcWin win(800, 600);
			loop(win);
		}
	}
	else {
		SdlWin window(400, 700);
		loop(window);
	}
	return (0);
}
