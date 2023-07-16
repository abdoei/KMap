#include <bits/stdc++.h>
#define maxInputLetters 100
#define maxInputTerms 16

using namespace std;

// function prototypes
void enterance_message();
void prepair_input(char arr[], char const dummy_arr[]);
int divide_terms(char const arr[], char terms[][8], int numOfLiterals[], int* lastTermIndex);
void convertToBinary(int termsBinaryValue[][4], char terms[][8], int lastTermIndex);

int main()
{
    int flag = 0; // General Purpose flag
    enterance_message();

    char dummy_arr[maxInputLetters] = "A'B'CD+A'BCD+ABCD+AB'CD+AB C'D'+ABC'D+ ABCD' ", terms[maxInputTerms][8] = {};
    // we use getline to get the input with spaces or not
    cin.getline(dummy_arr, maxInputLetters);
    
    // removing spaces
    char arr[maxInputLetters] = "";

    prepair_input(arr, dummy_arr);
    
    // in case of truncation
    cout << "your input is: " << endl;
    cout << arr << endl;

    int lastTermIndex = 0;
    int numOfLiterals[maxInputTerms] = {0};
    if(divide_terms(arr, terms, numOfLiterals, &lastTermIndex))
        return 1;
    
    // calc the binary of each term
    int termsBinaryValue[maxInputTerms][4];
    convertToBinary(termsBinaryValue, terms, lastTermIndex);



    // Generate values from terms
    bool permutations[8][3] =  {{0, 0, 0},
                                {1, 0, 0},
                                {0, 1, 0},
                                {1, 1, 0},
                                {0, 0, 1},
                                {1, 0, 1},
                                {0, 1, 1},
                                {1, 1, 1}};
    int finalValues[16] = {};

    // looping through the entered terms to ...
    for (int i = 0; i < lastTermIndex; i++)
    {
        flag = 0;
        int weights[4] = {8, 4, 2, 1};

        // modify the masking weights
        for (int k = 0; k < 4; k++)
        {
            if (termsBinaryValue[i][k] == 1)
            {
                flag += termsBinaryValue[i][k] * weights[k]; // store the sum of the constant literal weights
                weights[k] = 0;                              // then eleminate the corresponding weight not to calculate it multiple times
            }
            else if (termsBinaryValue[i][k] == 0)
                weights[k] = 0;
        }

        // Looping through the absent literals permutations
        for (int j = 0; j < pow(2, 4 - numOfLiterals[i]); j++)
        {
            int temp = 0;             // store the sum of the variable literals for each different permutation
            int lastUnknownIndex = 0; // index to focus on from where to get the next value of the permutation (the permutations were rearranged to be valid for different cases (i.e., one absent literal, two or three))
            for (int l = 0; l < 4; l++)
            {
                if (termsBinaryValue[i][l] == -1)
                {
                    temp -= termsBinaryValue[i][l] * weights[l] * permutations[j][lastUnknownIndex];
                    lastUnknownIndex++;
                }
            }
            finalValues[flag + temp] = 1;
        }
    }

    // rearrange the terms in the kMap
    short map[4][4] = { {0, 1, 3, 2},
                        {4, 5, 7, 6},
                        {12, 13, 15, 14},
                        {8, 9, 11, 10}};

    
    bool kMap[4][4] = {0};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            kMap[i][j] = finalValues[map[i][j]];
        }
    }

    cout << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << kMap[i][j] << ", ";
        }
        // backspace to remove the last comma
        cout << "\b\b\b";
        cout << endl;
    }
    return 0;
}

// function to print the enterance message
void enterance_message(){
        cout << "Your literals are A, B, C and D capital or small letters (you can mix in between) in addition to these letters you only can enter the plus sign \"+\" and the apostrophe sign to negate the literal (e.g., A' or b') \n";
    cout << "For example A'B'CD+A'BCD+ABCD+AB'CD+ABC'D'+ABC'D+ABCD' will give you the following kMap: \n\n";
    cout << "0, 0, 1, 0, \n";
    cout << "0, 0, 1, 0, \n";
    cout << "1, 1, 1, 1, \n";
    cout << "0, 0, 1, 0, \n";
}
// remove the spaces and capitalize the input
void prepair_input(char arr[], char const dummy_arr[]){
    for (int i = 0, j = 0; dummy_arr[i] != '\0'; i++)
    {
        if (dummy_arr[i] != ' ')
        {
            arr[j] = dummy_arr[i];
            j++;
        }
    }

    // capitalize the input
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] >= 'a' && arr[i] <= 'd')
            arr[i] -= 32;
    }
}

// function to divide the input into terms and calculate the number of literals in each term
int divide_terms(char const arr[], char terms[][8], int numOfLiterals[], int* lastTermIndex){
    
    for (int i = 0; arr[i] != '\0'; i++, (*lastTermIndex)++)
    {
        for (int j = 0; !(arr[i] == '+' || arr[i] == '\0'); j++)
        {
            terms[*lastTermIndex][j] = arr[i];
            if (!(arr[i] == '+' || arr[i] == '\'' || arr[i] == 'A' || arr[i] == 'B' || arr[i] == 'C' || arr[i] == 'D'))
            {
                cout << "Wrong input" << endl;
                return 1;
            }
            i++; // bypass the + sign
        }
    }

    int flag;
    // calc the num of the literals in each term
    for (int i = 0; i < *lastTermIndex; i++)
    {
        flag = 0;
        for (int j = 0; terms[i][j] != '\0'; j++)
        {
            if (terms[i][j] != '\'')
                flag++;
        }
        numOfLiterals[i] = flag;
    }
    return 0;
}

// function to convert the terms to binary
void convertToBinary(int termsBinaryValue[][4], char terms[][8], int lastTermIndex){

    // initiate the termsBinaryValue array with -1 to be like {{-1, -1, -1, -1},...}
    for (int i = 0; i < maxInputTerms; i++)
    {
        for (int j = 0; j < 4; j++) termsBinaryValue[i][j] = -1;
    }

    // convert to binary
    for (int i = 0; i < lastTermIndex + 1; i++)
    {
        for (int j = 0; j < 2 * 4; j++) // maximum iteration is applied when all lit are negated
        {
                 if ((terms[i][j] == 'A') && terms[i][j + 1] != '\'')
                termsBinaryValue[i][0] = 1;
            else if ((terms[i][j] == 'A') && terms[i][j + 1] == '\'')
            {
                termsBinaryValue[i][0] = 0;
                j++;
            }
            else if ((terms[i][j] == 'B') && terms[i][j + 1] != '\'')
                termsBinaryValue[i][1] = 1;
            else if ((terms[i][j] == 'B') && terms[i][j + 1] == '\'')
            {
                termsBinaryValue[i][1] = 0;
                j++;
            }
            else if ((terms[i][j] == 'C') && terms[i][j + 1] != '\'')
                termsBinaryValue[i][2] = 1;
            else if ((terms[i][j] == 'C') && terms[i][j + 1] == '\'')
            {
                termsBinaryValue[i][2] = 0;
                j++;
            }
            else if ((terms[i][j] == 'D') && terms[i][j + 1] != '\'')
                termsBinaryValue[i][3] = 1;
            else if ((terms[i][j] == 'D') && terms[i][j + 1] == '\'')
            {
                termsBinaryValue[i][3] = 0;
                j++;
            }
        }
    }
}

