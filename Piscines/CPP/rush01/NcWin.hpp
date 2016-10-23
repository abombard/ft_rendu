/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcWin.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/27 18:44:56 by abombard          #+#    #+#             */
/*   Updated: 2015/06/27 20:20:05 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <string>
#include <iostream>
#include "ncurses.h"

class NcWin {

	private:
		NcWin( void );
		int		_width;
		int		_height;
		WINDOW	*_screen;

	protected:

	public:
		NcWin( int width, int height );
		virtual ~NcWin( void );

		NcWin &	operator=( NcWin const & rhs );

		void	drawBorder( int x, int y, int width, int height ) const;
		void	draw(std::string str, int x, int y) const;
		void	clear( void );
		void	flip( void );
		int		event( void ) const;

		WINDOW	*getNcWin( void ) const;
		int		getWidth( void ) const;
		int		getHeight( void ) const;
};

#endif
