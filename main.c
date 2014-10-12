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

    returnArray = malloc(2 * sizeof(int));
    returnArray[0] = correctCount;
    returnArray[1] = misplacedCount;

    guessCount++;

    printf("%s\t|\t%dA %dB\n", guess, returnArray[0], returnArray[1]);

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
    
    //index of guess that is current changing
    digit = 3;
    
    //List of possible digits
    int numbers[9];
    int  numbersIndex= 4;
    int startingIndex = 4;
    for (i=0; i<10; i++)
        numbers[i] = (i+1)%10;

    result = checkGuess(guess);

    while (result[0] != 4)
    {
        if (numbersIndex >= 10)
        {
            //numbersIndex = startingIndex-1;
            numbersIndex = 0;
        }

        lastguess = strdup(guess);
        lastCorrect = result[0];
        lastMisplaced = result[1];
        
        //Skip digits that have been marked as read
        do
        {
            guess[digit] = numbers[numbersIndex%10] + '0';
            numbersIndex++;

        }
        while (numbers[numbersIndex-1] == -1);
     
        result = checkGuess(guess);
        
        if ((result[0]-lastCorrect)==1)           //If there is a new correct digit
        {
            //Mark as read
            numbers[numbersIndex-1] = -1;
            
            digit--;
            startingIndex--;
            numbersIndex = startingIndex;
        }
        else if ((lastCorrect-result[0])==1)      //If we replaced a correct digit)
        {
            int tmpDigit;

            //reset guess
            guess = lastguess;
            result[0] = lastCorrect;
            result[1] = lastMisplaced;

            //mark as read
            tmpDigit = (int)lastguess[digit] - '0';
            numbers[tmpDigit-1] = -1;
            numbersIndex = startingIndex;
            startingIndex--;
            
            digit--;

        }
        else if ((lastMisplaced-result[1])==1)      //If we replaced a misplaced digit
        {
            int tmpDigit;
            numbers[numbersIndex-1] = -1;
            tmpDigit = (int)lastguess[digit] - '0';
            startingIndex = tmpDigit-1;
            
        }
        else if (result[1] == 0)
        {
            numbers[numbersIndex-1] = -1;
        }
    }
    
    return guess;
}
