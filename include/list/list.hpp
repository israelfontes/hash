/**
* @file     list.hpp
* @brief    Cabeçalho da lista.
*			Projeto de EDB - Lista Duplamente Encadeada.
* @author   Israel Medeiros Fontes
* @since    16/11/2017
* @date     23/11/2017
*/
#ifndef _LIST_HPP_
#define _LIST_HPP_
#include <iostream>


namespace sc{

	template <typename T>
	class list{
		private:

			struct Node{ 		//<! struct Node abstrai o modelo de nó.
				T data;			//<! Dado que o nó guarda.
				Node *prev; 	//<! Nó anterior ao nó atual.
				Node *next;		//<! Nó sucessor ao nó atual.
				
				/// Construtor do nó.
				Node(const T & d = T(), Node * p = nullptr, Node * n = nullptr):
					data(d), prev(p), next(n){ /* Empty */ }
			};
		/**
		* @brief Classe const_iterator que abstrai um iterador constante.
		*/
		class const_iterator{
			protected:
				Node *current; 	//<! Nó que o iterador constante aponta.
				/**
				* @brief Construtor do iterador constante passando o ponteiro do nó como parametro.
				* @param p Nó para onde o iterador irá apontar.
				*/
				const_iterator( Node * p ): current(p){}
				/**
				* @brief Torna possível o acesso dos elementos do const_iterator pela classe list.
				*/  
				friend class list<T>;

			public:
				/// Construtor padrão.
				const_iterator();
				/**
				* @brief Sobrecarga do operador de dereferência.
				* @return O nó que o iterador constante guarda.
				*/ 
				const Node * operator*() const;
				/**
				* @brief Sobrecarga do operador ++, ou proxímo elemento, é alterado antes do uso.
				* @return Um iterador constante que aponta para o próximo elemento do nó atual.
				*/
				const_iterator & operator++();
				/**
				* @brief Sobrecarga do operador ++, ou proxímo elemento, é alterado depois do uso.
				* @return Um iterador constante que aponta para o próximo elemento do nó atual.
				*/
				const_iterator operator++(int);
				/**
				* @brief Sobrecarga do operador --, ou elemento anterior, é alterado antes do uso.
				* @return Um iterador constante que aponta para o elemento anterior do nó atual.
				*/
				const_iterator & operator--();
				/**
				* @brief Sobrecarga do operador --, ou elemento anterior, é alterado depois do uso.
				* @return Um iterador constante que aponta para o elemento anterior do nó atual.
				*/
				const_iterator & operator--(int);
				/**
				* @brief Sobrecarga do operador ==. Compara se nós são iguais.
				* @return Comparação dos dois nós dos iteradores constantes.
				*/
				bool operator==(const const_iterator & rhs ) const;
				/**
				* @brief Sobrecarga do operador !=. Compara se nós são diferentes.
				* @return Comparação dos dois nós dos iteradores constantes.
				*/
				bool operator!=(const const_iterator & rhs ) const;
		};

		/**
		* @brief Classe iterador que abstrai um iterador herdando const_iterator.
		*/
		class iterator : public const_iterator{
			public:
				/// Construtor padrão que chama o construtor da classe const_iterator.
				iterator(): const_iterator(){}
				/**
				* @brief Sobrecarga do operador de dereferência.
				* @return O nó que o iterador guarda.
				*/ 
				Node * operator*() const;
				/**
				* @brief Sobrecarga do operador ++, ou proxímo elemento, é alterado antes do uso.
				* @return Um iterador que aponta para o próximo elemento do nó atual.
				*/
				iterator & operator++();
				/**
				* @brief Sobrecarga do operador ++, ou proxímo elemento, é alterado depois do uso.
				* @return Um iterador que aponta para o próximo elemento do nó atual.
				*/
				iterator operator++(int);
				/**
				* @brief Sobrecarga do operador --, ou elemento anterior, é alterado antes do uso.
				* @return Um iterador que aponta para o elemento anterior do nó atual.
				*/
				iterator & operator--();
				/**
				* @brief Sobrecarga do operador --, ou elemento anterior, é alterado depois do uso.
				* @return Um iterador que aponta para o elemento anterior do nó atual.
				*/
				iterator operator--(int);

			protected:
				/**
				* @brief Construtor do iterador constante passando o ponteiro do nó como parametro.
				* @param p Nó para onde o iterador irá apontar.
				*/
				iterator(Node *p): const_iterator(p){/* Empty */}
				/**
				* @brief Torna possível o acesso dos elementos do const_iterator pela classe list.
				*/  
				friend class list<T>;
		};

		private:
			size_t m_size = 0; //<! Quantidade de elementos da lista.
			Node * m_head; 	   //<! Nó cabeça da lista.
			Node * m_tail;	   //<! Nó calda da lista.

		public:
			/// Construtor padrão.
			list();

			/// Destrutor padrão.
			~list();

			/**
			* @brief Construtor a partir da quantidade de nós a serem criados.
			* @param count Quantidade de elementos.
			*/
			explicit list ( size_t count );
			
			/**
			* @brief Construtor cópia.
			* @param other Lista a ser copiada.
			*/
			explicit list( const list & other);

			/**
			* @brief Sobrecarga do operador de igualdade =
			* @param other Lista que será copiada.
			*/
			list &operator=( const list & other );

			/**
			* @return iterator apontando para o primeiro nó da lista.
			*/
			iterator begin();
			
			/**
			* @return const_iterator apontando para o primeiro nó da lista.
			*/
			const_iterator cbegin() const;
			
			/**
			* @return iterator apontando para o nó após o último da lista, que é a calda da lista.
			*/
			iterator end();

			/**
			* @return const_iterator apontando para o nó após o último da lista, que é a calda da lista.
			*/
			const_iterator cend() const;

			/**
			* @return Tamanho da lista.
			*/
			size_t size() const;
			
			/**
			* @return Verificação se existem nós na lista.
			*/
			bool empty() const;

			/**
			* @brief Apaga todos os elementos da lista.
			*/
			void clear();
			
			/** 
			* @return Retorna o dado contido no nó da frente da lista.
			*/
			T & front();

			/** 
			* @return Retorna o dado constante contido no nó da frente da lista.
			*/
			const T & front() const;

			/** 
			* @return Retorna o dado contido no nó de trás da lista.
			*/
			T & back();

			/** 
			* @return Retorna o dado constante contido no nó de trás da lista.
			*/
			const T & back() const;

			/**
			* @brief Insere um nó a partir do dado na frente da lista.
			* @param value Dado a ser inserido no nó e consequentimente na lista.
			*/
			void push_front( const T & value );
			
			/**
			* @brief Insere um nó a partir do dado atrás da lista.
			* @param value Dado a ser inserido no nó e consequentimente na lista.
			*/
			void push_back( const T & value );

			/**
			* @brief Apaga o nó que está mais a frente da lista.
			*/
			void pop_front();
			
			/**
			* @brief Apaga o nó que está mais atrás da lista.
			*/
			void pop_back();

			/**
			* @brief Substitui o dado de todos os nós da lista pelo dado passado por parametro.
			* @param value Valor que nós irão assumir.
			*/
			void assign( const T & value );

			/**
			* @brief Insere um nó com o valor passado após o nó que iterador aponta.
			* @param itr Iterador que aponta para posição anterior que será inserido o novo nó.
			*/ 
			iterator insert( const_iterator itr, const T & value );
			
			/** 
			* @brief Apaga o nó que iterador aponta.
			* @param itr iterador que aponta para a ser apagado.
			*/
			iterator erase( const_iterator itr);
			
			/**
			* @brief Apaga um conjunto de nós.
			* @param first const_iterator para o primeiro nó do conjunto.
			* @param last const_iterator para o último nó do conjunto a ser apagado.
			*/
			const_iterator erase( const_iterator first, const_iterator last );
			
			/**
			* @brief Procura pelo nó com o valor passado.
			* @return const_iterator para o nó caso o encontre, caso não encontre, retorna nullptr.
			*/
			const_iterator find( const T & value );	

			/** 
			* @brief Sobrecarga do operador ==. Verifica se duas listas são iguais.
			* @return Resultado booleano da verificação.
			*/
			bool operator==( const list & other );
			
			/** 
			* @brief Sobrecarga do operador !=. Verifica se duas listas são diferentes.
			* @return Resultado booleano da verificação.
			*/
			bool operator!=( const list & other );
	};
}

#include "const_iterator.inl"
#include "iterator.inl"
#include "list.inl"

#endif