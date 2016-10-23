#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>

class List {
public:
	List(void *elem);
	List( List const &src );
	~List(void);
	
	List &	operator=( List const & rhs );

	int		getIndex() const;
	void	*getElem() const;
	List	*getNext() const;
	List	*getPrev() const;

	void	setIndex(int n);
	void	setElem(void *elem);
	void	setNext(List *node);
	void	setPrev(List *node);

private:
	List(void);
	int		_index;
	void	*_elem;
	List	*_prev;
	List	*_next;

protected: 
	
};

std::ostream &	operator<<( std::ostream & o, List const & i );

# endif
