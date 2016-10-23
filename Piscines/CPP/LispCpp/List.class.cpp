# include "List.class.hpp"

List::List(void *elem) : _index(0), _elem(elem), _prev(NULL), _next(NULL)
{

}

List::List( List const &src )
{
	*this = src;
}

List::~List(void)
{

}

List &	List::operator=( List const &rhs )
{
	if ( this != &rhs )
	{
		this->_index = rhs.getIndex();
		this->_elem = rhs.getElem();
		this->_next = rhs.getNext();
		this->_prev = rhs.getPrev();
	}
	return *this;
}

int		List::getIndex() const 		{ return this->_index; }
void	*List::getElem() const		{ return this->_elem; }
List	*List::getNext() const		{ return this->_next; }
List	*List::getPrev() const		{ return this->_prev; }

void	List::setIndex(int n)		{ this->_index = n; }
void	List::setElem(void *elem)	{ this->_elem = elem; }
void	List::setNext(List *node)	{ this->_next = node; }
void	List::setPrev(List *node)	{ this->_prev = node; }

std::ostream &	operator<<( std::ostream & o, List const & i )
{
	o << "Im a node containing " << *(int*)i.getElem() << std::endl;
	return o;
}
