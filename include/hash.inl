/*
* @file hash.inl
* @author Israel Fontes
* @brief Implementação da classe HashTbl.
*/

using namespace ac;

/// Função auxiliar que verifica a primalidade de um número.
bool primo(int n){
  int limit;
  limit = (int)sqrt(n);
  for(int i=2;i<=limit;++i) if(n%i==0) return false;
  return true;
}

template<class KeyType, class DataType, class KeyHash, class KeyEqual>
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::HashTbl(int tbl_size){

	if( !primo(tbl_size) ){ 
		while(!primo(++tbl_size)){} /// Avançe até ser um primo.
	}
	
	m_data_table = new std::forward_list<Entry>[tbl_size]; /// Aloca a memória a partir do número primo
	m_size = tbl_size; /// Salva o tamanho da tabela alocada
	m_count = 0; /// Quantidade de elementos inicial
}

template<typename KeyType, typename DataType, class KeyHash, class KeyEqual>
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::~HashTbl(){
	delete [] m_data_table; /// Deleta a memória
}

template < typename KeyType, typename DataType, class KeyHash, class KeyEqual >
bool HashTbl< KeyType, DataType, KeyHash, KeyEqual >::insert ( const KeyType & k_, const DataType & d_ ) {

	if (m_count/m_size > 1.0) rehash(); /// Se a carga da tabela for maior que 1, redefina a tabela com o dobro do tamanho.
	Entry new_entry(k_,d_);

	auto end( KeyHash()(k_) % m_size ); /// Busca o endereço na tabela
	for( auto it = m_data_table[end].begin(); it!= m_data_table[end].end(); ++it ){

		if( KeyEqual()(it->m_key, new_entry.m_key) ){ /// Se o Entry a ser inserido já existir, sobrescreva.
			it->m_data = new_entry.m_data;
			return false;
		}
	}

	++m_count; 
	m_data_table[end].push_front(new_entry); /// Insere o Entry na frente da lista
	
	return true;
}

template<typename KeyType, typename DataType, class KeyHash, class KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::remove(const KeyType & k_){
		
	auto end( KeyHash()(k_) % m_size );
	auto b_begin = m_data_table[end].before_begin(); /// Iterator antes do begin
	
	for(auto it(m_data_table[end].begin()); it != m_data_table[end].end(); ++it){
	    
	    if (KeyEqual()((*it).m_key, k_)){ /// Se o Entry com a chave passada for encontrado, apague-o da lista
	        ++it;
	        m_data_table[end].erase_after(b_begin, it);
	        --m_count;
	        return true;
	    }
	    
	    ++b_begin;
	}
	return false;
}

template<typename KeyType, typename DataType, class KeyHash, class KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::retrieve(const KeyType & k_, DataType & d_) const{

	auto end( KeyHash()(k_) % m_size );

	for(auto it = m_data_table[end].begin(); it != m_data_table[end].end(); ++it){
		if( KeyEqual()(it->m_key, k_) ) { /// Se a chave 
			d_ = it->m_data;
			return true;
		}
	}
	return false;
}

template<typename KeyType, typename DataType, class KeyHash, class KeyEqual>
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::clear(void){

	for(auto i(0u); i < m_size; ++i) m_data_table[i].~forward_list(); /// Destroi todos as listas da tabela
	m_count = 0;
}

template<typename KeyType, typename DataType, class KeyHash, class KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::empty(void) const{
	return m_count == 0;
}

template<typename KeyType, typename DataType, class KeyHash, class KeyEqual>
unsigned long int HashTbl<KeyType, DataType, KeyHash, KeyEqual>::count(void) const{
	return m_count;
}

template<typename KeyType, typename DataType, class KeyHash, class KeyEqual>
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::rehash(void){

	HashTbl<KeyType, DataType, KeyHash, KeyEqual> * tmp = new HashTbl<KeyType, DataType, KeyHash, KeyEqual>(2*m_size); /// Aloca uma nova HashTbl com o dobro do tamanho da Hash atual

	/// Copia os elementos da tabela antiga para nova
	for(auto i (0u); i < m_size; ++i){
		for(auto it = m_data_table[i].begin(); it!= m_data_table[i].end(); ++it){
			tmp->insert(it->m_key, it->m_data);
		}
	}
	this->~HashTbl(); /// Destroi a tabela antiga.

	/// Copia a tabela nova para antiga
	this->m_data_table = tmp->m_data_table; 
	this->m_size = tmp->m_size;
	this->m_count = tmp->m_count;
}