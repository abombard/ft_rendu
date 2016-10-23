// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Lisp.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 23:07:51 by abombard          #+#    #+#             //
//   Updated: 2015/06/21 17:00:42 by abombard         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "Lisp.class.hpp"

int Lisp::it = 0;

Lisp::Lisp(void) : _Beg(NULL), _End(NULL), _size(0), _cur(NULL)
{

}

Lisp::Lisp( Lisp const &src )
{
	*this = src;
}

Lisp::~Lisp(void)
{
	List *tmp = this->getBeg();
	List *next;

	while (tmp)
	{
		next = tmp->getNext();
		delete tmp;
		tmp = next;
	}
}

Lisp &	Lisp::operator=( Lisp const &rhs )
{
	List	*tmp;

	if ( this != &rhs )
	{
		tmp = rhs.getBeg();
		while (tmp)
		{
			this->push(tmp);
			tmp = tmp->getNext();
		}
	}
	return *this;
}

List	*Lisp::reset()
{
	Lisp::it = 0;
	this->_cur = this->getBeg();
	return this->_cur;
}

std::ostream &	operator<<( std::ostream & o, Lisp & i )
{
	int x = 0;

	std::cout << "This is a list of " << i.size() << " elem:" << std::endl;
	while (x < i.size())
	{
		o << "Elem " << x << ": " << *(int*)i.get(x) << std::endl;
		x++;
	}
	return o;
}

List	*Lisp::getBeg() const		{ return this->_Beg; }
List	*Lisp::getEnd() const		{ return this->_End; }
int		Lisp::size() const			{ return this->_size; }

void	Lisp::add(void *elem)
{
	List	*tmp;

	if (!elem)
		return this->Err("push", "elem Null");

	tmp = new List(elem);

	if (!tmp)
		return ;

	if (!this->getBeg())
	{
		this->_Beg = tmp;
		this->_End = tmp;
	}
	else
	{
		tmp->setNext(this->_Beg);
		this->_Beg->setPrev(tmp);
		this->_Beg = tmp;
	}
	this->_size += 1;
	this->orderIndex();
}

void	Lisp::push(void *elem)
{
	List	*tmp;

	if (!elem)
		return this->Err("push", "elem Null");

	tmp = new List(elem);

	if (!tmp)
		return ;

	if (!this->getBeg())
	{
		this->_Beg = tmp;
		this->_End = tmp;
	}
	else
	{
		this->_End->setNext(tmp);
		tmp->setIndex(this->_End->getIndex() + 1);
		tmp->setPrev(this->_End);
		this->_End = tmp;
	}
	this->_size += 1;
}

void	Lisp::del(int n)
{
	List	*tmp;
	List	*next;
	List	*prev;

	if (n < 0 || n >= this->size())
		return this->Err("del", "n out of index range");

	tmp = this->getBeg();

	while (tmp->getIndex() != n)
		tmp = tmp->getNext();

	if (tmp == this->getBeg())
		this->_Beg = this->_Beg->getNext();
	else if (tmp == this->getEnd())
		this->_End = this->_End->getPrev();

	next = tmp->getNext();
	prev = tmp->getPrev();

	if (prev)
		prev->setNext(next);
	if (next)
		next->setPrev(prev);
	delete tmp;

	this->_size -= 1;
	this->orderIndex();
}

void	*Lisp::get(int n)
{
	if (n < 0 || n >= this->size())
		return (NULL);
	if (n == 0)
	{
		this->_cur = this->getBeg();
		return this->_cur->getElem();
	}
	this->_cur = this->_cur->getNext();
	return this->_cur->getElem();
}

// **************** PRIVATE **************** //

void	Lisp::Err(std::string fun, std::string s)
{
	std::cout << "Error: " << fun << ": " << s << std::endl;
}

void	Lisp::orderIndex()
{
	List *tmp = this->getBeg();
	int i = 0;

	while (tmp)
	{
		tmp->setIndex(i++);
		tmp = tmp->getNext();
	}
}
