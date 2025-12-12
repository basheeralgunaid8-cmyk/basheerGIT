#pragma once
#include <iostream>
#define MAX_SIZE 10
using namespace std;
namespace hashTable
{
    class HashNode
    {
    public:
        int key;
        int value;
        HashNode* next;  // if there is a collision happened
    };

    class HashTable
    {
    private:
        HashNode* Table[MAX_SIZE];

    public:
        // constructor
        HashTable()
        {
            for (int i = 0; i < MAX_SIZE; i++)
            {
                Table[i] = nullptr;
            }
        }

        int HashFunction(int key)
        {
            return key % MAX_SIZE;
        }

        void insert(int key, int value)
        {
            int index = HashFunction(key);
            HashNode* newNode = new HashNode();
            newNode->key = key;
            newNode->value = value;
            newNode->next = nullptr;

            if (Table[index] == nullptr)
            {
                Table[index] = newNode;
            }
            else
            {
                newNode->next = Table[index];
                Table[index] = newNode;
            }
        }

        int getIndex(int key)
        {
            int index = HashFunction(key);
            HashNode* node = Table[index];

            while (node != nullptr)
            {
                if (node->key == key)
                {
                    return node->value;  // Return value if key is found
                }
                node = node->next;
            }

            return -1;  // Return -1 if key is not found
        }

        void remove(int key)
        {
            int index = HashFunction(key);
            HashNode* Temp = Table[index];
            HashNode* prev = nullptr;
            // Check if the key is at the head of the list
            while (Temp != nullptr)
            {
                if (Temp->key == key)
                {
                    if (prev == nullptr)  // Deleting the first node
                    {
                        Table[index] = Temp->next;
                    }
                    else
                    {
                        prev->next = Temp->next;
                    }
                    delete Temp;  // Free the memory
                    cout << "Key " << key << " removed successfully.\n";
                    return;
                }
                prev = Temp;
                Temp = Temp->next;
            }

            cout << "Key " << key << " not found.\n";
        }
        int size()
        {
            int count = 0;
            for (int i = 0; i < MAX_SIZE; i++)
            {
                HashNode* node = Table[i];
                while (node != nullptr)
                {
                    count++;
                    node = node->next;
                }
            }
            return count;
        }

        void display()
        {
            for (int i = 0; i < MAX_SIZE; i++)
            {
                HashNode* node = Table[i];
                if (node != nullptr)
                {
                    cout << "Index " << i << ": ";
                    while (node != nullptr)
                    {
                        cout << "(" << node->key << ", " << node->value << ") ";
                        node = node->next;
                    }
                    cout << endl;
                }
            }
        }
    };
}
