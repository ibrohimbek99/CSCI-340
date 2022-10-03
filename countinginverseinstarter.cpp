

/*
Ibrahim Pulatov
Professor Haque
CSCI 340 
Counting inverse
*/
#include <bits/stdc++.h>
#include<iostream>
#include<cstdio> 
using namespace std;

int mergeSortAndCountInv(int arr[], int l, int r); 
int merge(int arr[], int l, int m, int r); 

int merge(int arr[], int l, int m, int r) 
{ 
	int i, j, k, inv_count = 0; ; 
	int n1 = m - l + 1; 
	int n2 = r - m; 

	/* create temp arrays */
	int * L = new int[n1];
	int * R = new int[n2];
 

	/* Copy data to temp arrays L[] and R[] */
  for(int i = 0; i < n1; i++){
    L[i] = arr[l+i];
  }

  for(int i = 0; i < n1; i++){
    R[i] = arr[m+1+i];
  }

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2) 
	{
    if(L[i] <= R[j])
    {
      arr[k] = L[i];
      i++;
      
    }
    else{
      arr[k] = R[j];
      j++;
      inv_count = inv_count + (m - i + 1); //count the inversion
    }
    k++;
    
	} 

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1) 
	{ 
    arr[k] = L[i];
    i++;
    k++;
	} 

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2) 
	{ 
    arr[k] = R[j];
    j++;
    k++;
	} 
	delete [] L;
	delete [] R;
    return inv_count;
} 

int mergeSortAndCountInv(int arr[], int l, int r) 
{ 
	int inv_count = 0;
  int m;
	if (l < r) 
	{ 
    m = (r+l)/2;
    inv_count += mergeSortAndCountInv(arr, l, m); //how many inversions in the left subarray
    inv_count += mergeSortAndCountInv(arr, m +1 , r); // how many inversions in the right subarray
    inv_count += merge(arr, l ,m, r); //how many inversions after merging
	} 
	return inv_count; 
} 

/* Function to print an array */
void printArray(int A[], int size) 
{
  int i;
    for (i=0; i < size; i++)
        cout<<A[i]<< "  ";
    cout<<endl;

} 

/* Driver program to test above functions */
int main() 
{ 
  ifstream file;
  int arr_size;
  file.open("input.txt",ios::in); 
  if(!file) 
    { 
        cout<<"Error in creating file!!!"; 
        return 0; 
    } 
    cout<<"File opened successfully."; 
    file>> arr_size;
    int arr[arr_size];
    for(int i = 0; i < arr_size; i++)
    {
        file>>arr[i];
    }
    
	cout<<"Given array is \n";
	printArray(arr, arr_size); 

cout<<"Number of inversions are \n"<< mergeSortAndCountInv(arr, 0, arr_size - 1); 

	return 0; 
} 
