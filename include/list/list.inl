/**
* @file     list.inl
* @brief    Implementação do list.
* @author   Israel Medeiros Fontes
* @since    16/11/2017
* @date     22/11/2017
*/

template <typename T>
sc::list<T>::list(){ 
	m_head = new Node();
	m_tail = new Node();
	m_head->prev = nullptr;
	m_tail->next = nullptr;	
	m_head->next = m_tail;
	m_tail->prev = m_head;
	m_size = 0;
}

template <typename T>
sc::list<T>::~list(){ 
	this->clear();
	delete this->m_head;
	delete this->m_tail;
}

template <typename T>
sc::list<T>::list( size_t count ){
	m_head = new Node();
	m_tail = new Node();
	m_head->prev = nullptr;
	m_tail->next = nullptr;	
	m_head->next = m_tail;
	m_tail->prev = m_head;
	T *t = new T();
	for(size_t i = 0; i < count; ++i) push_back(*t);
}

template <typename T>
sc::list<T>::list( const list & other ){
	m_head = new Node();
	m_tail = new Node();
	m_head->prev = nullptr;
	m_tail->next = nullptr;	
	m_head->next = m_tail;
	m_tail->prev = m_head;
	m_size = other.size();
	for(const_iterator it = other.cbegin(); it != other.cend(); ++it) { push_front( (*it)->data );}
}

template <typename T>
typename sc::list<T> & sc::list<T>::operator=( const list & other ){ 
	clear();
	for(const_iterator it = other.cbegin(); it != other.cend(); ++it) { push_front( (*it)->data );}
	this->m_size = other.size();
	return *this; 
}

template <typename T> 
typename sc::list<T>::iterator sc::list<T>::begin(){ return iterator( m_head->next ); }

template <typename T>
typename sc::list<T>::const_iterator sc::list<T>::cbegin() const{ return const_iterator( m_head->next ); }

template <typename T>
typename sc::list<T>::iterator sc::list<T>::end(){ return iterator( m_tail ); }

template <typename T>
typename sc::list<T>::const_iterator sc::list<T>::cend() const{ return const_iterator( m_tail ); }

template <typename T>
size_t sc::list<T>::size() const{ return m_size; }

template <typename T>
bool sc::list<T>::empty() const{ return m_size==0; }

template <typename T>
void sc::list<T>::clear(){ 
	while( m_tail->prev != m_head ) pop_front();
	m_size = 0; 
}

template <typename T>
T & sc::list<T>::front(){ return (m_tail->prev)->data; }

template <typename T>
const T & sc::list<T>::front() const{ return (m_tail->prev)->data; }

template <typename T>
T & sc::list<T>::back(){ return (m_head->next)->data; }

template <typename T>
const T & sc::list<T>::back() const{ return (m_head->next)->data; }

template <typename T>
void sc::list<T>::push_back( const T & value ){ 
	Node * tmp = m_tail->prev;
	tmp->next = new Node( value, tmp, m_tail );
	m_tail->prev = tmp->next;
	++m_size;
}

template <typename T>
void sc::list<T>::push_front( const T& value ){
	Node * tmp = m_head->next;
	tmp->prev = new Node( value, m_head, tmp );
	m_head->next = tmp->prev;
	++m_size;
}

template <typename T>
void sc::list<T>::pop_back(){
	if(!empty()){
		Node * tmp = m_tail->prev;
		(tmp->prev)->next = m_tail;
		m_tail->prev = tmp->prev;
		delete tmp;
		--m_size;	
	}	
}

template <typename T>
void sc::list<T>::pop_front(){
	if(!empty()){
		Node * tmp = m_head->next;
		(tmp->next)->prev = m_head;
		m_head->next = tmp->next;
		delete tmp;
		--m_size;
	}
}

template <typename T>
void sc::list<T>::assign( const T & value ){
	for(iterator it = begin(); it != ++end(); ++it)
		(*it)->data = value;
}

template <typename T>
typename sc::list<T>::iterator sc::list<T>::insert( const_iterator itr, const T & value ){
	iterator it = this->begin();
	if(itr == this->cend()) return nullptr;

	while(it != itr){
		if( it == this->end() ) return nullptr;
		++it;
	}

	Node *tmp = (*it)->next;
	(*it)->next = new Node( value, (*it), tmp );
	tmp->prev = (*it)->next;
	++m_size;
	return iterator((*it)->next);
}

template <typename T>
typename sc::list<T>::iterator sc::list<T>::erase( const_iterator itr ){
	iterator it = this->begin();
	if(itr == this->cend()) return nullptr;
	
	while(it != itr){
		if( it == this->end() ) return nullptr;  
		++it;
	}

	(*it)->prev->next = (*it)->next;
	(*it)->next->prev = (*it)->prev;

	--m_size;
	return ++it;
}

template <typename T>
typename sc::list<T>::const_iterator sc::list<T>::erase( const_iterator first, const_iterator last ){
	while(first != last) first = erase(first);
	return first;
}

template <typename T>
typename sc::list<T>::const_iterator sc::list<T>::find( const T & value ){
	for(const_iterator it = this->cbegin(); it != this->cend(); ++it){
		if( (*it)->data == value ) return it;
	}
	return nullptr;
}

template <typename T>
bool sc::list<T>::operator==( const list & other ){
	if(other.size() != this->size()) return false;

	const_iterator it_this = this->cbegin();
	for( const_iterator it = other.cbegin(); it != other.cend(); ++it ){
		if( (*it_this)->data !=  (*it)->data) return false;
		++it_this;
	}

	return true;
}

template <typename T>
bool sc::list<T>::operator!=( const list & other ){
	if(other.size() != this->size()) return true;

	const_iterator it_this = this->cbegin();
	for( const_iterator it = other.cbegin(); it != other.cend(); ++it ){
		if( (*it_this)->data !=  (*it)->data) return true;
		++it_this;
	}

	return false;
}