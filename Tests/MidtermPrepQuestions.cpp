#include <iostream>

// Arrays

// Question 1: Remove all products in an array of structs with price matching given argument "target;" shift to fill gap, return size of array

struct Product {
   std::string pname;
   int price;
};

struct node
{
    int value;
    node *next;
    node *prev;
};

int ShiftArray(Product arr[],int size,int target)
{
    for ( int i = 0; i < size; ++i )
    {
        if (arr[i].price == target)
        {
            for (int j = i; j < size-1; ++j)
            {
                arr[j] = arr[j+1];
            }
            size--;
        }
    }
    return size;
}

// Question 2:
	// Return most common repeating element in an array of structs
	// Takes two arguments

std::string commonRepeatingElement( Product arr[], int length )
{
    int highestCount = 0;
    std::string mostCommonProduct;
    std::string currentProduct;
    
    for(int i = 0; i < length; ++i)
    {
        currentProduct = arr[i].pname;
        int count = 0;
        for(int j = i; j < length; ++j)
        {
            if ( arr[i].pname == arr[j].pname )
            {
                count+=arr[i].price;
            }
        }
        if(count > highestCount)
        {
            highestCount = count;
            mostCommonProduct = currentProduct;
        }
    }
    return mostCommonProduct;
}

// Question 3: Copy all elements of an array to a new array except for specified value

int* CopyArray(int array[], int length, int value)
{
    int* newArray = new int[length];
    int index = 0;
    
    for(int i = 0; i < length; ++i)
    {
        if(array[i] == value)
            continue;
        else
            newArray[index] = array[i];
        	index++;
    }

    return newArray;
}

// Question 4: Find second-largest element

int secondLargest( int arr[], int size )
{
    int secondLargest = (-999999);
    int largest = (-999998);
    
    for(int i = 0; i < size; ++i)
    {
        if( arr[i] > largest)
        {
            secondLargest = largest;
            largest = arr[i];
        }
        else if (arr[i] > secondLargest) // This only runs if the above IF doesn't not run
        {
            secondLargest = arr[i];
        }
    }

    return secondLargest;
}

// Linked Lists

// Linked Lists #2

// Question 1: Delete nodes in a linked list with values matching argument

node * DeleteNode(node *head, int value)
{
	for (node* currentNode = head; currentNode != NULL; currentNode = currentNode->next)
	{
		node* tmpNode;
		if ( currentNode->value == value )
		{
			tmpNode = currentNode;
			if (currentNode->prev == nullptr) // if head
			{
				currentNode->prev->next = currentNode->next;
				currentNode->next->prev = currentNode->prev;
			}
			if (currentNode->next == nullptr) // if tail
			{
				currentNode->prev->next = currentNode->next;
				currentNode->next->prev = currentNode->prev;
			}
			else
			{
				currentNode->prev->next = currentNode->next;
				currentNode->next->prev = currentNode->prev;
			}
			
			
			currentNode = currentNode->prev;
			delete tmpNode;
		}
	}
	return head;
}













