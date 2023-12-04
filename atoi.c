#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int size = strlen(input);
    if (strlen(input) == 0)
    {
        return 0;
    }
    int final_character = input[size - 1] -48; // 1st step (gets number)


    // 2nd step (remove the last character from the string)


    input[size - 1] = '\0';

    return  final_character+ 10 * convert(input); // final step (return final value plus 10 time integer value of new string that was shortened)

}
