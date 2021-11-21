#include <bits/stdc++.h>
#define maxInputLetters 100
#define maxInputTerms 16

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    // cout.tie(NULL);
    // cin.tie(NULL);
    cout << "Your literals are A, B, C and D capital or small letters (you can mix in between) in addition to these letters you only can enter the plus sign \"+\" and the apostrophe sign to negate the literal (e.g., A' or b') \n";
    int flag = 0; // General Purpose flag
    char arr[maxInputLetters] = "", terms[maxInputTerms][8] = {};
    cin >> arr;

    // divide into terms
    int lastTermIndex = 0;
    for (int i = 0; arr[i] != '\0'; i++, lastTermIndex++)
    {
        for (int j = 0; !(arr[i] == '+' || arr[i] == '\0'); j++)
        {
            terms[lastTermIndex][j] = arr[i];
            if (!(arr[i] == '+' || arr[i] == '\'' || arr[i] == 'a' || arr[i] == 'b' || arr[i] == 'c' || arr[i] == 'd' || arr[i] == 'A' || arr[i] == 'B' || arr[i] == 'C' || arr[i] == 'D'))
            {
                cout << "Wrong input" << endl;
                return 1;
            }
            i++; // bypass the + sign
        }
    }

    // calc the num of the lit of each term
    int numOfLiterals[maxInputTerms] = {0};
    for (int i = 0; i < lastTermIndex; i++)
    {
        flag = 0;
        for (int j = 0; terms[i][j] != '\0'; j++)
        {
            if (terms[i][j] != '\'')
                flag++;
        }
        numOfLiterals[i] = flag;
    }

    // calc the binary of each term
    // initiate the termsBinaryValue array with -1 to be like {{-1, -1, -1, -1},...}
    int termsBinaryValue[maxInputTerms][4];
    for (int i = 0; i < maxInputTerms; i++)
    {
        for (int j = 0; j < 4; j++)
            termsBinaryValue[i][j] = -1;
    }

    // convert to binary
    for (int i = 0; i < lastTermIndex + 1; i++)
    {
        for (int j = 0; j < 2 * numOfLiterals[i]; j++) // maximum iteration is applied when all lit are negated
        {
            if ((terms[i][j] == 'a' || terms[i][j] == 'A') && terms[i][j + 1] != '\'')
                termsBinaryValue[i][0] = 1;
            else if ((terms[i][j] == 'a' || terms[i][j] == 'A') && terms[i][j + 1] == '\'')
            {
                termsBinaryValue[i][0] = 0;
                j++;
            }
            else if ((terms[i][j] == 'b' || terms[i][j] == 'B') && terms[i][j + 1] != '\'')
                termsBinaryValue[i][1] = 1;
            else if ((terms[i][j] == 'b' || terms[i][j] == 'B') && terms[i][j + 1] == '\'')
            {
                termsBinaryValue[i][1] = 0;
                j++;
            }
            else if ((terms[i][j] == 'c' || terms[i][j] == 'C') && terms[i][j + 1] != '\'')
                termsBinaryValue[i][2] = 1;
            else if ((terms[i][j] == 'c' || terms[i][j] == 'C') && terms[i][j + 1] == '\'')
            {
                termsBinaryValue[i][2] = 0;
                j++;
            }
            else if ((terms[i][j] == 'd' || terms[i][j] == 'D') && terms[i][j + 1] != '\'')
                termsBinaryValue[i][3] = 1;
            else if ((terms[i][j] == 'd' || terms[i][j] == 'D') && terms[i][j + 1] == '\'')
            {
                termsBinaryValue[i][3] = 0;
                j++;
            }
        }
    }

    // Generate values from terms
    int permutations[8][3] = {{0, 0, 0},
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
    int map[4][4] = {{0, 1, 3, 2},
                     {4, 5, 7, 6},
                     {12, 13, 15, 14},
                     {8, 9, 11, 10}};
    int kMap[4][4] = {0};
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
        cout << endl;
    }
    return 0;
}
