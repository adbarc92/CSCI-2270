int secondLargest( int arr[], int size )
{
    int secondLargest = (-999999);
    int largest = (-999998);
    
    for(int i = 0; i < size; ++i)
    {
        if( arr[i] > largest)
        {
            largest = arr[i];
        }
        else
            continue;
    }
    for(int i = 0; i < size; ++i)
    {
        if(arr[i] == largest)
            continue;
        else
        {
            if (arr[i] > secondLargest);
                secondLargest = arr[i];
        }
    }
    return secondLargest;
}