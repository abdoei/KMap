#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    // cout.tie(NULL);
    // cin.tie(NULL);
    cout << "Your literals are A, B, C and D capital or small letters (you can mix in between) in addition to these letters you only can enter the plus sign \"+\" and the apostrophe sign to negate the literal (e.g., A' or b') \n";
    int maxInputLetters = 100, maxInputTerms = 16;
    char arr[maxInputLetters] = "", terms[maxInputTerms][8] = {};
    cin >> arr;

    // divide into terms
    int i = 0;
    int termsIndex = 0;
    while (arr[i] != '\0')
    {
        int j = 0;
        while (!(arr[i] == '+' || arr[i] == '\0'))
        {
            terms[termsIndex][j] = arr[i];
            i++;
            j++;
        }
        termsIndex++;
        i++;
    }
    // termsIndex--;

    // calc num of lit of each term
    int numOfLiterals[maxInputTerms] = {0};
    for (int i = 0; i < termsIndex + 1; i++)
    {
        int flag = 0;
        for (int j = 0; terms[i][j] != '\0'; j++)
        {
            if (terms[i][j] != '\'')
                flag++;
        }
        numOfLiterals[i] = flag;
    }

    // calc the binary of each term
    int termsValue[maxInputTerms][4];
    for (int i = 0; i < maxInputTerms; i++)
    {
        for (int j = 0; j < 4; j++)
            termsValue[i][j] = -1;
    }
    for (int i = 0; i < termsIndex + 1; i++)
    {
        for (int j = 0; j < 2 * numOfLiterals[i]; j++) // maximum iteration is applied when all lit are negated
        {
            if ((terms[i][j] == 'a' || terms[i][j] == 'A') && terms[i][j + 1] != '\'')
            {
                termsValue[i][0] = 1;
            }
            else if ((terms[i][j] == 'a' || terms[i][j] == 'A') && terms[i][j + 1] == '\'')
            {
                termsValue[i][0] = 0;
                j++;
            }
            else if ((terms[i][j] == 'b' || terms[i][j] == 'B') && terms[i][j + 1] != '\'')
                termsValue[i][1] = 1;
            else if ((terms[i][j] == 'b' || terms[i][j] == 'B') && terms[i][j + 1] == '\'')
            {
                termsValue[i][1] = 0;
                j++;
            }
            else if ((terms[i][j] == 'c' || terms[i][j] == 'C') && terms[i][j + 1] != '\'')
                termsValue[i][2] = 1;
            else if ((terms[i][j] == 'c' || terms[i][j] == 'C') && terms[i][j + 1] == '\'')
            {
                termsValue[i][2] = 0;
                j++;
            }
            else if ((terms[i][j] == 'd' || terms[i][j] == 'D') && terms[i][j + 1] != '\'')
                termsValue[i][3] = 1;
            else if ((terms[i][j] == 'd' || terms[i][j] == 'D') && terms[i][j + 1] == '\'')
            {
                termsValue[i][3] = 0;
                j++;
            }
        }
    }

    // Generate values from terms
    // int net1[2][1] = {{0}, {1}};
    // int net2[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    int net3[16][4] = {{0, 0, 0, 0},
                       {1, 0, 0, 0},
                       {0, 1, 0, 0},
                       {1, 1, 0, 0},
                       {0, 0, 1, 0},
                       {1, 0, 1, 0},
                       {0, 1, 1, 0},
                       {1, 1, 1, 0},
                       {0, 0, 0, 1},
                       {1, 0, 0, 1},
                       {0, 1, 0, 1},
                       {1, 1, 0, 1},
                       {0, 0, 1, 1},
                       {1, 0, 1, 1},
                       {0, 1, 1, 1},
                       {1, 1, 1, 1}};
    int finalValues[16] = {};
    int flag;
    for (int i = 0; i < termsIndex; i++)
    {
        flag = 0;
        int weights[4] = {8, 4, 2, 1};
        for (int k = 0; k < 4; k++)
        {
            if (termsValue[i][k] == 1)
            {
                flag += termsValue[i][k] * weights[k];
                weights[k] = 0;
            }
            else if (termsValue[i][k] == 0)
                weights[k] = 0;
        }
        for (int j = 0; j < pow(2, 4 - numOfLiterals[i]); j++)
        {
            int temp = 0;
            int lastUnknownIndex = 0;
            for (int l = 0; l < 4; l++)
            {
                if (termsValue[i][l] == -1)
                {
                    temp -= termsValue[i][l] * weights[l] * net3[j][lastUnknownIndex];
                    lastUnknownIndex++;
                }
            }
            finalValues[flag + temp] = 1;
        }
    }

    // arrange the terms
    int map[4][4] = { {0, 1, 3, 2},
                      {4, 5, 7, 6},
                      {12, 13, 15, 14},
                      {8, 9, 11, 10}};
    int kMap[4][4] = {0};
    for (int i = 0; i < 4; i++)
    {
        for(int j = 0;j<4;j++)
        {
            kMap[i][j] = finalValues[map[i][j]];
        }
    }

    // for (int i = 0; i < termsIndex; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //         cout << termsValue[i][j] << ",";
    //     cout << endl;
    // }
    // for (int i = 0; i < 16; i++)
    // {
    //     // if(!(i%3))   cout << endl;
    //     cout << finalValues[i] << ",";
    // }
    cout << endl;
    for (int i = 0; i < 4; i++)
    {
        for(int j = 0;j<4;j++)
        {
            cout << kMap[i][j] << ", ";
        }
        cout << endl;
    }
    return 0;
}