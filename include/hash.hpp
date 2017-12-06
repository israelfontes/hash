/**!
* @file hash.hpp
* @author Israel Fontes
* @brief Implementação da estrutura de dados Tabela de Dispersão (Table Hash).
*/

#ifndef _HASH_HPP_
#define _HASH_HPP_

#include <cmath> /// sqrt()
#include <forward_list> /// Forward List
#include <iostream> /// Stream

namespace ac{

	/*
	* @brief Classe HashEntry: Estrutura que forma um bucket da tabela.
	* Sendo formado por uma Chave e seu Dado associado.
	*/
	template<class KeyType, class DataType>
	class HashEntry{
		public:
			HashEntry(KeyType k_, DataType d_): m_key(k_), m_data(d_){/* Empty */} /// Construtor
			KeyType m_key; //<! Chave
			DataType m_data; //<! Dado
	};

	/**
	* @brief Classe HashTbl: Estrutura Tabela de Dispersão. 
	* Dispersa os dados na tabela a partir da chave associada a cada dado.
	*/
	template < class KeyType, class DataType, class KeyHash, class KeyEqual>
	class HashTbl{
		public:	
			using Entry = HashEntry<KeyType, DataType>; 

			HashTbl(int tbl_size = DEFAULT_SIZE); /// Construtor
			virtual ~HashTbl(); /// Destrutor

			/*
			* @brief Insere um Entry na tabela.
			* @param k_ Chave do Entry.
			* @param d_ Dado do Entry.
			* @return True se o Entry não existir e for inserido, false caso contrário.
			*/
			bool insert(const KeyType & k_, const DataType & d_);
			
			/*
			* @brief Remove Entry a partir de sua chave.
			* @param k_ Chave do Entry a ser removido.
			* @return True se for removido, False caso não encontre a chave.
			*/ 
			bool remove(const KeyType & k_);

			/*
			* @brief Recupera o dado a partir da chave.
			* @param k_ Chave a ser Procurada
			* @param d_ Onde guardar o dado recuperado.
			* @return True se o dado existir, false caso contrário.
			*/
			bool retrieve(const KeyType & k_, DataType & d_) const;
			
			/*
			* @brief Limpa a tabela.
			*/
			void clear(void);
			
			/*
			* @brief Verifica se ela está vazia.
			* @return True se estiver vazia, false caso contrário.
			*/
			bool empty(void) const;

			/*
			* @return Quantidade de elementos armazenados.
			*/
			unsigned long int count (void) const;
			

			void print() const; /// Debug

			/*
			* @brief sobrecarga do operador de inserção.
			*/
			friend std::ostream& operator<< (std::ostream &o, const HashTbl<KeyType, DataType, KeyHash, KeyEqual> &hash){

				for(auto i(0u); i < hash.m_size; ++i){
					if(hash.m_data_table[i].empty()){
							o << "(" << i << "): "<< "[ Empty ]" << std::endl;
					}

					for(auto it = hash.m_data_table[i].begin(); it != hash.m_data_table[i].end(); ++it){
							o << "(" << i << "): " << (*it).m_data << std::endl;	
					}			
				}

				return o;	
			}

		private:
			/*
			* @brief Aloca uma nova tabela com o dobro de mémoria e reposiciona os 
			* elementos a partir da antiga tabela e apaga a antiga.
			*/
			void rehash(void);
			unsigned int m_size; //<! Tamanho da tabela.
			unsigned int m_count; //<! Elementos armazenados.

			std::forward_list<Entry> * m_data_table; //<! Tabela de listas de Entry's
			static const short DEFAULT_SIZE = 11; //<! Tamanho padrão para iniciar a tabela.
	};
}
// End Hash
#include "hash.inl"
#endif