/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 10:41:04 by esoulard          #+#    #+#             */
/*   Updated: 2021/04/09 12:45:35 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The goal is to create an efficient key-value handling algorithm.
**
** Following this tutorial https://www.geeksforgeeks.org/c-program-hashing-chaining/
** and mixing it up with this one https://www.tutorialspoint.com/cplusplus-program-to-implement-hash-tables
** Hash tables are said to be pretty fast for db handling, storing and searching.
** Let's try it!
*/

#include <string>
#include <iostream>
#include <list>

#define SIZE 20000000

class Pair {

    public:

        Pair(std::string k, std::string v): _key(k), _val(v) {};

        std::string &getKey()   { return _key; };
        std::string &getVal()   { return _val; };


    private:

        std::string _key;
        std::string _val;

};

class HashTable {

    public:

        HashTable(int buckets) {
            
            _bucket_list = new std::list<Pair>[SIZE];
        };// constructor

        long int &hashFunction(std::string &key) {
            
            long int hash = 37; // a prime number
            long int prime_a = 71; //another prime number
            
            for (char &c : key)
                hash = (hash * prime_a + c) % SIZE;
           
            return hash;
        }

        void add_entry(char *key, char *value) {

            std::string s_key(key);
            long int index = hashFunction(s_key);

            std::list<Pair>::iterator it = get_entry(s_key, index);
            if (it == _bucket_list[index].end())
                return ;
                
            *value = '\0'; //removing the '='
            ++value;

            _bucket_list[index].push_back(Pair(std::string(key), std::string(value)));
        }

        std::list<Pair>::iterator &get_entry(std::string &key, long int index) {
            
            if (index == -1)
                index = hashFunction(key);

            std::list<Pair>::iterator it;
            std::list<Pair>::iterator ite = _bucket_list[index].end();

            if (_bucket_list[index].size()) {

                it = _bucket_list[index].begin();
                while (it != ite) {
                    if ((*it).getKey() == key)
                        break;
                    ++it;
                }
            }
            else
                return ite;
            if (it == ite)
                return ite;
    
            return it;
        }

        void delete_entry(std::string &key) {
            
            long int index = hashFunction(key);
            std::list<Pair>::iterator it = get_entry(key, index); 
            
            if (it == _bucket_list[index].end())
                return ;

            _bucket_list[index].erase(it);
        }

    private:

        // array containing buckets
        std::list<Pair>   *_bucket_list; 


};

int main() {

    HashTable db(SIZE);
    std::string in_str;
    char *in_c;
    char *equal;

    while (1) {
        
        equal = NULL;

        std::getline(std::cin, in_str);
        if (!std::cin)
            break ;

        in_c = &in_str[0];
        if (in_c[0] == '!') 
            db.delete_entry(&in_str[1]);
        else if ((equal = strchr(in_c, '=')))
            db.add_entry(in_c, equal);
        else
            db.get_entry(in_str);

        in_str = std::string("");
        in_c[0] = '\0';
    }
    return 0;
}