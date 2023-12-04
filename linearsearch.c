#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Linear search must use unsorted file
// use for loop to go one by one to see if user input matches number
// Binary Search must use sorted list
// start with middle of sorted list
// determine if user input is above the middle number or less than
// Find the middle of the next section that the user's number is in
// continue this process until user number is found
// for both linear and binary search, print the index where the number was found
// worked with Jack Yuan
// Bubble sort
// swap counter to non-zero value
// move larger values to right
// repeat until swap counter is 0
// reset swap counter to 0
// if two adjacent elements ar enot in order, swap them and add one to the swap counter
// Selection sort
// must use for loop multiple times
// after the swap, the first index does not change for rest of process
// repeat to set  another min after each swap

#define SIZE1 5000
#define SIZE2 10000
#define SIZE3 50000
int *readFile(string fileName, int size, int size2);  //pointer to return and int array
int linearSearch(int array[], int guess, int size);  //linear search
int binarySearch(int array[], int size, int number);
int *bubbleSort(int array[], int size);
int *selectionSort(int array[], int size);
void printArray(int array[], int size);
void Menu();
int main(void)
{
    string fileName;
    int user_choice;
    int binaryIndex;

    do
    {
        Menu();
        user_choice = get_int("Enter you choice between 1-5: ");
        switch (user_choice)
        {
            case 1: // linear search
            fileName = "random10000.txt";
            int linearGuess = get_int ("Enter a number you want to be found using linear search: ");
            int *linearArray = readFile(fileName, SIZE2, 5);
             int linearindex = linearSearch(linearArray, linearGuess, SIZE2);
                if (linearindex != -1)
                    printf("Number %d has been found at index %d\n", linearGuess, linearindex);
                else
                    printf("Number %d could not be found in the array\n", linearGuess);
                break;

            case 2: // binary search
                fileName = "sorted10000.txt";
                int *binaryArray = readFile(fileName, SIZE2, 5);
                int binaryGuess = get_int("Enter a number you want to be found using binary search: ");
                binaryIndex = binarySearch(binaryArray, SIZE2, binaryGuess);
                if (binaryIndex != -1)
                {
                    printf("Your number %d has been found at index %d\n", binaryGuess, binaryIndex);
                }
                else
                {
                    printf("Your number could not be found.\n");
                }
                break;

            case 3: // selection sort
                fileName = "random10000.txt";
                int *selectionArray = readFile(fileName, SIZE2, 5);
                // Perform selection sort (implement selectionSort function)
                selectionSort(selectionArray, SIZE2);
                printf("Sorted array using selection sort:\n");
                printArray(selectionArray, SIZE2);
                break;

            case 4: // bubble sort
                fileName = "random10000.txt";
                int *bubblearray = readFile(fileName, SIZE2, 5);
                // Perform bubble sort (implement bubbleSort function)
                bubbleSort(bubblearray, SIZE2);
                printf("Sorted array using bubble sort:\n");
                printArray(bubblearray, SIZE2);
                break;

            case 5:
                printf("Exiting program.\n");
                break;
        }

    } while (user_choice != 5); // makes user need to put in 5 to end program

return 0;
}
int *readFile(string fileName, int size, int size2 )
    {

    FILE* file=(fopen(fileName, "r")); // reads file

    char line[size2];
    char options[size][size2]; // dimensions of file

    int  static numbers[SIZE2];  // file to be returned

    for (int i=0; i <size; i++)
    {
        fscanf(file, "%s", options[i]);
        // printf("%s \n", options[i]);
        numbers[i]= atoi(options[i]); // converts to integers
    }
    fclose(file);
   return numbers;
}
int linearSearch(int array[],int guess,int size )
{
    for(int i=0; i < size; i++) // goes through each element in array
    {
        if (array[i]== guess) // once user number matches with element
        {
            return i;
        }
    }
    return -1; // if number not found
}
int binarySearch(int array[], int size, int number)
{
int max = size - 1;
int min = 0;
int mid;

while (min <= max)
{
 mid = (max + min) / 2; // how to find middle number

if (array[mid] == number)
{
    return mid;
}
else if (array[mid] < number)
{
    min = mid + 1; // sets number above mid = min
}
else
{
    max = mid - 1; // sets number below mid = max
}

}
return -1; // if number not found
}
int *selectionSort(int array[], int size)
{
    int indx=0;
    for(int i=0; i<size ; i++)
    {
        int min= size + 1;
        for(int j=i; j< size; j++)
        {
            if(array[j]<min)
            {
                min = array[j];
                indx=j;
            }
        }
        // make the swap
        int temp = array[i];
        array[i]=min;
        array[indx]=temp;
    }
    return array; // returns array once sorted
}
int *bubbleSort(int array[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
    for (int j = 0; j < size - i - 1; j++)
    {
        if (array[j] > array[j + 1])
        {
            int temp = array[j];
            array[j] = array[j+1];
            array[j+1] = temp;
        }
    }
    }
    return array; // returns array once sorted
}
void printArray(int array[], int size)
{
    for (int i=0; i < size; i++) // goes through each element because it needs to print each element
    {
        printf(" %i \n",array[i] ); // prints the sorted array
    }
}
void Menu() // display menu for user to see which option to choose
{
 printf("=====================================\n");
 printf("#               MENU                #\n");
 printf("#   1) Find number using linear search                 #\n");
 printf("#   2) Find number using binary search                #\n");
 printf("#   3) Sort a list using selection sort  #\n");
 printf("#   4) Sort a list using bubble sort    #\n");
 printf("#   5) Exit                         #\n");
 printf("=====================================\n");
}
