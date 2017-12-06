/**
* @file     iterator.inl
* @brief    Implementação do iterator.
* @author   Israel Medeiros Fontes
* @since    16/11/2017
* @date     22/11/2017
*/

template<typename T>
typename sc::list<T>::Node * sc::list<T>::iterator::operator*() const{ return this->current; }

template<typename T>
typename sc::list<T>::iterator & sc::list<T>::iterator::operator++(){ 
	this->current = (this->current)->next; 
	return *this; 
}

template<typename T>
typename sc::list<T>::iterator sc::list<T>::iterator::operator++(int){ 
	iterator temp(*this); 
	operator++(); 
	return temp; 
}

template<typename T>
typename sc::list<T>::iterator & sc::list<T>::iterator::operator--(){ 
	this->current = (this->current)->prev; 
	return *this; 
}

template<typename T>
typename sc::list<T>::iterator sc::list<T>::iterator::operator--(int){ 
	const_iterator temp(*this); 
	operator--(); 
	return temp; 
}