/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcWin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/27 18:46:11 by abombard          #+#    #+#             */
/*   Updated: 2015/06/28 18:14:11 by ncharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NcWin.hpp"

NcWin::NcWin( int width, int height ) :
	_width(width), _height(height)
{
	initscr();
	raw();
	noecho();
	nonl();
	timeout(0);
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	curs_set(0);
	this->_screen = newwin(height, width, 0, 0);
}

NcWin::~NcWin( void ) {
	wborder(this->_screen, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	delwin(this->_screen);
	endwin();
}

NcWin &	NcWin::operator=( NcWin const & rhs ) {
	this->_screen = rhs.getNcWin();
	return *this;
}

void	NcWin::draw(std::string str, int x, int y) const{

	mvwprintw(this->_screen, y, x, str.c_str());
}

void	NcWin::clear( void ) {

	werase(this->_screen);
}

void	NcWin::flip( void ) {

	wrefresh(this->_screen);
}

int		NcWin::event( void ) const {

	char c = getch();
	if (c == 'q')
		return -1;
	return 0;
}

void	NcWin::drawBorder( int x, int y, int width, int height ) const {
	
	this->draw("+", x, y);
	this->draw("+", x + width - 1, y);
	this->draw("+", x, y + height - 1);
	this->draw("+", x + width - 1, y + height - 1);
	for (int xx = x + 1; xx < x + width - 1; xx++) { this->draw("-", xx, y); }
	for (int xx = x + 1; xx < x + width - 1; xx++) { this->draw("-", xx, y + height - 1); }
	for (int yy = y + 1; yy < y + height - 1; yy++) { this->draw("|", x, yy); }
	for (int yy = y + 1; yy < y + height - 1; yy++) { this->draw("|", x + width - 1, yy); }
}

WINDOW	*NcWin::getNcWin( void ) const { return this->_screen; }
int		NcWin::getWidth( void ) const { return this->_width; }
int		NcWin::getHeight( void ) const { return this->_height; }
