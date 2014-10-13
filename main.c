#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Mastermind
 * Usage: ./mastermind
 * Guesses the randomly generated number
 * Assumptions:
 * 1. Any input given is valid (aka they are no more than four digits with no repeating digits
 */

char* solution;



//maximum number of digits
const int DIGITS = 4;

/* checkGuess
 * pre: takes guess number
 * post: return array of size 2, with array[0] being the number of correct digits and array[1] being the number of correct digits that are not in the correct position
 */
int* checkGuess(char*);

/* solve
 * pre: takes guess
 * post: returns solution string
 */
char* solve(char*);

/* indexOfNumber
 * pre: takes string and integer
 * post: returns index of int character in string
 */
int indexOfNumber(char*, int);

void swap(char*, int first, int second);

int guessCount;

int main(int argc, char** argv)
{
    int i;
    int n;
    char result[4];
    guessCount = 0;

    if (argc != 2)
    {
        printf("Usage: ./mastermind {number}\n");
        return 0;
    }

    if (strlen(argv[1]) < 4 || strlen(argv[1]) > 4)
    {
        printf("Invalid input: your number must be four digits");
        return 0;
    }

    solution = argv[1];
    /* 
       printf("Guess: ");
       while (scanf("%s", &result))
       {
       if (strlen(result) == 4)
       checkGuess(result);
       printf("Guess: ");
       }

       printf("%d", n);
       */
    char* firstguess = strdup("1234");
    printf("Solved! Your number is %s\n", solve(firstguess));
    printf("Guesses: %d\n", guessCount);
}

int* checkGuess(char* guess)
{
    int i, j;
    int correctCount = 0;
    int misplacedCount = 0;
    int* returnArray;

    for (i=0; i<4; i++)
    {
        if (guess[i] == solution[i])
            correctCount++;
        else
        {
            for (j=0; j<4; j++)
            {
                if (guess[i] == solution[j])
                    misplacedCount++;
            }
        }
    }

    returnArray = (int*)malloc(2 * sizeof(int));
    returnArray[0] = correctCount;
    returnArray[1] = misplacedCount;

    guessCount++;

    printf("%d.\t%s\t|\t%dA %dB\n", guessCount, guess, returnArray[0], returnArray[1]);

    return returnArray;
}

char* solve(char* guess)
{
    int i;
    int digit;
    int* result;
    int lastCorrect;
    int lastMisplaced;
    char* lastguess;
    int swapped = 0;

    //index of guess that is current changing
    digit = 3;

    //List of possible digits
    int numbers[10];
    int  numbersIndex= 4;
    int startingIndex = 4;
    for (i=0; i<10; i++)
        numbers[i] = (i+1)%10;

    result = checkGuess(guess);

    while (result[0] != 4 && ( result[0] != 2 || result[1] != 2))
    {
        if (guessCount > 100)
            return "FAILURE";
        
        if (numbersIndex >= 10)
            numbersIndex = 0;

        lastguess = strdup(guess);
        lastCorrect = result[0];
        lastMisplaced = result[1];

        if (digit < 0)
            digit = 3;

        //Skip digits that have been marked as read
        do
        {
            if (numbersIndex==10)
                numbersIndex = 0;

            int oldIndex;
            if ((oldIndex = indexOfNumber(guess, numbers[numbersIndex%10])) > -1)
            {
                guess[oldIndex] = lastguess[digit];
                swapped = 1;
            }
            guess[digit] = numbers[numbersIndex%10] + '0';
            numbersIndex++;
            //printf("--%d--\n", numbers[numbersIndex-1]);
        }
        while ((numbers[numbersIndex-1] < 0) || (strcmp(guess, lastguess) == 0));

        result = checkGuess(guess);

        if ((result[0]-lastCorrect)==1)           //If there is a new correct digit
        {
            //Mark as read
            numbers[numbersIndex-1] = -1;

            digit--;
            startingIndex--;
            numbersIndex = startingIndex;
        }
        else if ((lastCorrect-result[0])==1)      //If we replaced a correct digit
        {
            int tmpDigit;

            //reset guess
            guess = lastguess;
            result[0] = lastCorrect;
            result[1] = lastMisplaced;
            if (swapped == 0)
            {
                //mark as read
                tmpDigit = (int)lastguess[digit] - '0';
                numbers[tmpDigit-1] = -1;
                numbersIndex = startingIndex;
                startingIndex--;

                digit--;
            }

        }
        else if ((lastMisplaced-result[1])==1)      //If we replaced a misplaced digit
        {
            int tmpDigit;
            numbers[numbersIndex-1] = -1;
            tmpDigit = (int)lastguess[digit] - '0';
            startingIndex = tmpDigit-1;

        }
        swapped = 0;
    }

    if (result[0] == 4)
        return guess;

    numbersIndex = 0;
    startingIndex = 0;

    while (result[0] != 4)
    {
        swap(guess, numbersIndex, startingIndex);

        numbersIndex++;

        if (numbersIndex == 4)
        {
            numbersIndex = 0;
            startingIndex++;
        }

        swap(guess, startingIndex, numbersIndex);
        result = checkGuess(guess);
    }

    return guess;
}

int indexOfNumber(char* str, int num)
{
    int index;

    if (str==NULL || num < 0)
        return -1;

    index = 0;

    while (*str!='\0')
    {
        if (str[0] == (num + '0'))
            return index;
        str++;
        index++;
    }

    return -1;
}

void swap(char* str, int first, int second)
{
    char tmp;

    tmp = str[first];

    str[first] = str[second];
    str[second] = tmp;
}
