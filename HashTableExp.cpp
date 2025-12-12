#include <iostream>
#include"HashTable.h"

using namespace std;
using namespace hashTable;

int main()
{
    HashTable ht;
    int key = 0, value = 0;
    int keys[10]; 

    for (int i = 0; i < 10; i++)
    {
        cout << "Please enter key and value for pair " << i + 1 << ": ";
        cin >> key >> value;

        keys[i] = key;      
        ht.insert(key, value);
    }

    ht.display();
    cout << "Size of the hash table: " << ht.size() << endl;

    cout << "\nSearching all elements:\n";
    for (int i = 0; i < 10; i++)
    {
        int result = ht.getIndex(keys[i]); 
        if (result != -1)
            cout << "Key " << keys[i] << " found with value = " << result << endl;
        else
            cout << "Key " << keys[i] << " not found.\n";
    }

    ht.remove(9);

    return 0;
}
