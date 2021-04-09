/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 10:41:04 by esoulard          #+#    #+#             */
/*   Updated: 2021/04/09 14:42:58 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The goal is to create an efficient key-value handling algorithm.
** did this following the 42 HotRace challenge, for which i did a BST, which was not the 
** most efficient algo :(
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

        long int hashFunction(std::string &key) {
            
            long int hash = 37; // a prime number
            long int prime_a = 71; //another prime number
            
            std::string::iterator ite = key.end();
            for (std::string::iterator c = key.begin(); c != ite; ++c)
                hash = (hash * prime_a + *c) % SIZE;

            return hash;
        }

        void add_entry(std::string &input, size_t eq_pos) {

            std::string key = input.substr(0, eq_pos);
            long int index = hashFunction(key);

            std::list<Pair>::iterator it = get_entry(key, index);
            if (it != _bucket_list[index].end())
                return ;
                
            std::string value = input.substr(eq_pos + 1);

            _bucket_list[index].push_back(Pair(key, value));
        }

        std::list<Pair>::iterator get_entry(std::string &key, long int index) {

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

        void print_entry(std::string &key) {

            long int index = hashFunction(key);    
            std::list<Pair>::iterator it = get_entry(key, index);
        
            if (it != _bucket_list[index].end())
                std::cout << (*it).getVal() << "\n";
            else
                std::cout << key << ": Not found\n";
            
            
        };

        void delete_entry(std::string &key) {
            
            std::string toDel = key.substr(1);
            long int index = hashFunction(toDel);
            std::list<Pair>::iterator it = get_entry(toDel, index); 
            
            if (it == _bucket_list[index].end())
                return ;

            _bucket_list[index].erase(it);
        }

    private:

        // array containing buckets, each bucket is supposed to hold only one value but can hold a few if theres hash collision
        std::list<Pair>   *_bucket_list; 


};

int main() {

    HashTable                   db(SIZE);
    std::string                 in_str;
    std::string::iterator       c;
    size_t                      equal;

    // std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL);

    while (1) {

        std::getline(std::cin, in_str);
        if (!std::cin)
            break ;

        c = in_str.begin();
        
        if (*c == '!') 
            db.delete_entry(in_str); 
        else if ((equal = in_str.find('=')) != std::string::npos)
            db.add_entry(in_str, equal);
        else
            db.print_entry(in_str);

        in_str.clear();
    }
    return 0;
}