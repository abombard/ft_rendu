// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Lisp.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 23:08:04 by abombard          #+#    #+#             //
//   Updated: 2015/06/21 17:00:52 by abombard         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LISP_HPP
# define LISP_HPP

# include <iostream>
# include "List.class.hpp"

class Lisp {
public:
	Lisp(void);
	Lisp( Lisp const &src );
	~Lisp(void);

	static int it;

	Lisp &	operator=( Lisp const & rhs );
	List	*reset();

	List	*getBeg() const;
	List	*getEnd() const;
	int		size() const;
	void	*get(int n);

	void	add(void *elem);
	void	push(void *elem);
	void	del(int n);

private:
	List	*_Beg;
	List	*_End;
	int		_size;
	List	*_cur;
	
	void	Err(std::string fun, std::string s);
	void	orderIndex();
protected: 
	
};

std::ostream &	operator<<( std::ostream & o, Lisp & i );

# endif
