# hash_table
Just coding a hash table to grasp the concept

**See [Challenge HotRace repository ft. my sad BST map](https://github.com/42esoulard/Challenge-HotRace)**

- /!\ disclaimer: this redo is just for fun and personnal growth, so I used std::list (which is forbidden in the subject).


 - The goal is to create an efficient key-value handling algorithm. 
 did this following the 42 HotRace challenge, for which i implemented a BST, which was not the 
 most efficient way :( So here is a redo in the shape of a hashtable!

 - Following this tutorial https://www.geeksforgeeks.org/c-program-hashing-chaining/
 and mixing it up with this one https://www.tutorialspoint.com/cplusplus-program-to-implement-hash-tables

 - Hash tables are said to be pretty fast for db handling, storing and searching.. and now I must say they are!
 
 This one here is a fixed array of lists. Each key is hashed into an index, which we try to make as unique as possible.
 If bad luck (or bad hashing algorithm) makes it so that two keys end up with the same hash, we can always extend the 
 corresponding list to accomodate for it! But this mustn't happen too often or we'll lose some speed handling the list.

- Compile with -O3 for best results, uncomment the "sync_with_stdio(false)" in main if you're reckless!
