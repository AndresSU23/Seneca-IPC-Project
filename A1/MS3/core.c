/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 1
Full Name  : David Andres Sanchez Umbarila
Student ID#: 140273228
Email      : dasanchez-umbarila@myseneca.ca
Section    : NBB

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"

// As demonstrated in the course notes:
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer
// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("\n<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

int inputInt()
{
    char newline = 'x';
    int value;
    do
    {
        scanf("%d%c", &value, &newline);
        if (newline != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (newline != '\n');

    return value;
}

int inputIntPositive()
{
    char newline = 'x';
    int value;
    do
    {
        scanf("%d%c", &value, &newline);
        if (newline != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        else if (value <= 0)
        {
            printf("ERROR! Value must be > 0: ");
        }

    } while (newline != '\n' || value <= 0);

    return value;
}

int inputIntRange(int intLower, int intUpper)
{
    char newline = 'x';
    int value;
    do
    {
        scanf("%d%c", &value, &newline);
        if (newline != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        else if (value < intLower || value > intUpper)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", intLower, intUpper);
        }

    } while (newline != '\n' || value < intLower || value > intUpper);

    return value;
}

char inputCharOption(const char validChars[])
{
    char valueChar;
    int flag = 1, i;
    while (flag)
    {
        scanf("%c%*c", &valueChar);
        i = 0;
        while (validChars[i] != '\0')
        {
            if (valueChar == validChars[i])
            {
                flag = 0;
            }
            i++;
        }
        if (flag)
        {
            printf("ERROR: Character must be one of [");
            i = 0;
            while (validChars[i] != '\0')
            {
                printf("%c", validChars[i]);
                i++;
            }
            printf("]: ");
        }
    }
    return valueChar;
}

void inputCString(char *stringPointer, int charMin, int charMax)
{
    int flag = 1, size;
    do
    {
        char validation[20] = {'\0'};
        scanf("%[^\n]%*c", validation);
        size = strlen(validation);

        if ((charMin == charMax) && (size != charMax))
        {
            printf("ERROR: String length must be exactly %d chars: ", charMax);
        }
        else if ((charMin != charMax) && (charMax < size))
        {
            printf("ERROR: String length must be no more than %d chars: ", charMax);
        }
        else if ((charMin != charMax) && (size < charMin))
        {
            printf("ERROR: String length must be between %d and %d chars: ", charMin, charMax);
        }

        else
        {
            flag = 0;
            strcpy(stringPointer, validation);
        }

    } while (flag);
}

void displayFormattedPhone(const char phoneNumber[])
{
    int i = 0, nonDigit = 0;
    if (phoneNumber == NULL)
    {
        printf("(___)___-____");
    }
    else
    {
        while (phoneNumber[i] != '\0')
        {
            if ((int)phoneNumber[i] < 48 || (int)phoneNumber[i] > 57)
            {
                nonDigit = 1;
            }
            i++;
        }

        if (i != 10 || nonDigit)
        {
            printf("(___)___-____");
        }
        else
        {
            printf("(%c%c%c)%c%c%c-%c%c%c%c",
                   phoneNumber[0], phoneNumber[1], phoneNumber[2],
                   phoneNumber[3], phoneNumber[4], phoneNumber[5],
                   phoneNumber[6], phoneNumber[7], phoneNumber[8], phoneNumber[9]);
        }
    }
}
