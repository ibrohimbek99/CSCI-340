  /*
Ibrahim Pulatov
Professor Haque
CSCI 340
3/5/2022
C++ Program to Implement Hash Tables
 */
#include<iostream>
#include <fstream>
#include<cstdlib>
#include<string>
#include<cstdio>
using namespace std;
// Hash table size 
const int TABLE_SIZE = 13;
const int PRIME = 11;
//const float LOAD_FACTOR = 0.8;

enum EntryType {Legitimate, Empty, Deleted};

/*
 * HashEntry Class Declaration
 */
class HashEntry
{
    public:
        int key;
        enum EntryType info;
};
 
/*
 * HashMap Class Declaration
 */
class HashMap
{
    private:
        int current_size;
        HashEntry *htable;
    public:   
        HashMap()
	    {
        htable = new HashEntry[TABLE_SIZE];
        for(int i = 0; i < TABLE_SIZE; i++){
          htable[i].info = Empty;
          htable[i].key = 0;
        }
        
        current_size = 0;
      }
    
    
    	// function to calculate first hash 
    	int hash1(int key) 
    	{ 
          return (key % TABLE_SIZE);
    	} 
    
    	// function to calculate second hash 
    	int hash2(int key) 
    	{ 
          return (1 + (key % PRIME));
    	} 
        
        // Insert the key in hashtable
        void Insert(int key)
	    {
        //HashEntry *htable;
        int index1 = hash1(key);
        if(htable[index1].info == Empty){
          htable[index1].key = key;
          htable[index1].info = Legitimate;
          current_size++;
        }

        else{
          int index2 = hash2(key);
          int i = 1;
  
          while(1){
            int newindex = ((index1 + (i*index2)) % TABLE_SIZE);
            if(htable[newindex].info == Empty){
              htable[newindex].key = key;
              htable[newindex].info = Legitimate;
              current_size++;
              break;
            }
            i++;
          }
        }   
	    }
        
        //Search the key
        int Search(int key)
	    {
        int index1 = hash1(key);
        if(htable[index1].info == Empty){
          return -1;
        }
        else if((htable[index1].info == Legitimate) && 
          (htable[index1].key == key)){
          return index1;
          }
        else{
          int index2 = hash2(key);
          int i = 1;
          

          while(1){
            int newindex = index1 + i*index2;
            if(htable[newindex].info == Empty){
              return -1;
            }
            else if((htable[newindex].info == Legitimate) && 
                    (htable[newindex].key == key)){
              return newindex;
              break;
            }
            i++;
          }
        }
        return -1;
    	}
        
        //Delete the given key from hashtable
        void Remove(int key)
	    {
        int index = Search(key);
        if(index == -1){
          cout<<"It hasn't been found"<<endl;
        }
        else{
          htable[index].key = 0;
          htable[index].info = Deleted;
          current_size--;
        }

    	}
        
        //Print all the elements in the hashtable
        void Display() 
        { 
           for (int i = 0; i < TABLE_SIZE; i++)
          {
           cout << i <<"-->"<< htable[i].key<<"  "<<endl;
          }
        }
         
        
        //Delete the hashtable
        ~HashMap()
	    {  
          for(int i = 0; i < TABLE_SIZE; i++){
            htable[i].key = 0;
            htable[i].info = Deleted;
          }
          delete[] htable;
        }
      
      // void Rehash(){
      //   HashMap temp;
      //   temp.Display();
      //   if(LOAD_FACTOR > 0.8){
      //     for(int i = 0; i < 2*TABLE_SIZE;i++){
      //       if(htable[i].info == Legitimate){
      //         temp.Insert(htable[i].key);
      //       }
      //     }
      //    delete[] htable;   
      //   }
      //   return temp;
      // }
};
/*
 * Main Contains Menu
 */
int main()
{
    HashMap hash;
    int key, flag;
    int choice;
    // write code for taking input from file
    //Insret keys received from files and call the display function
    //Delete keys received from files and call the display function
    //Search keys received from files and call the display function
  ifstream file;
  int numInserted, numDeleted, numSearched;
  file.open("input.txt",ios::in); 
  if(!file) 
    { 
        cout<<"Error in creating file!!!"<< endl;
        return 0; 
    } 
    cout<<"File opened successfully."<< endl; 
    file>> numInserted;
    file>> numDeleted;
    file>> numSearched;
  int arr[numInserted];
  int a[numDeleted];
  int s[numSearched];
  //putting numbers into array
  for(int i = 0; i < numInserted; i++)
    {
        file>> arr[i];
    }
  
  cout<< "Inserting numbers into hashtable from file"<<endl;
  // putting numbers into hashtable from the array
  for (int i = 0; i < numInserted; i++){
    hash.Insert(arr[i]);
  }
  hash.Display();
  cout<<endl;
  
  for(int i = 0; i < numDeleted; i++)
    {
        file>> a[i];
    }
  cout<< "Removing numbers from hashtable"<<endl;
  for (int i = 0; i < numDeleted; i++){
    hash.Remove(a[i]);
  }
  hash.Display();
  cout<<endl;
  
  cout<< "Searching numbers in the hashtable"<<endl;
  for(int i = 0; i < numSearched; i++)
    {
        file>> s[i];
    }
  for (int i = 0; i < numSearched; i++){
    hash.Search(s[i]);
    if(hash.Search(s[i]) != -1){
      cout<< "Found at index "<< hash.Search(s[i])<<endl;
    }
    else{
      cout<<"It hasn't been found"<<endl;
    }
  }
  
    while (1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Hash Table"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Insert element into the table"<<endl;
        cout<<"2.Search element from the key"<<endl;
        cout<<"3.Delete element at a key"<<endl;
        cout<<"4.Display all the elements"<<endl;
        cout<<"5.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Enter element to be inserted: "<< endl;
                cin>>key;
                hash.Insert(key);
                hash.Display();
                break;
            
            case 2:
                cout<<"Enter element to be searched: "<< endl;
                cin>>key;   
                if (hash.Search(key) == -1)
                  cout << "The key hasn't been found"<< endl;
                else
                cout<< "The element was found at index #"<<hash.Search(key)<<endl; 
                break;
          
            case 3:
                cout<<"Enter element to be removed: "<<endl;
                cin>>key;
                hash.Remove(key);
                cout<< "The key was removed"<<endl;
                hash.Display();
                break;
            
            case 4:
                hash.Display();
                break;
            
            case 5:
                exit(1);
          // case 6:
          // hash.Rehash();
          // break;
            
            default:
               cout<<"\nEnter correct option\n";
       }
    }
    
    return 0;
}