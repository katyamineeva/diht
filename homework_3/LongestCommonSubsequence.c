#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;

struct Node
{
    int length;
    int cur_i;
    int cur_j;
    int prev_i;
    int prev_j;
};

Node max(Node a, Node b)
{
    if (a.length > b.length)
    {
        return a;
    }
    return b;
}


char* recoverAns(int strLen1, int strLen2, char* str1, char* str2, Node** dp)
{

    int len = dp[strLen1][strLen2].length;
    char* ans = (char*) malloc((len + 1) * sizeof(char));
    ans[len] = '\0';
    int ind, x, tmp;
    int i = strLen1;
    int j = strLen2;
    for (ind = len - 1; ind >= 0; --ind)
    {
        x = dp[i][j].cur_i - 1;
        ans[ind] = str1[x];
        tmp = dp[i][j].prev_i;
        j = dp[i][j].prev_j;
        i = tmp;
    }
    return ans;
}

char* getLCS(int strLen1, int strLen2, char* str1, char* str2)
{
    int i, j;
    Node** dp = (Node**) malloc((strLen1 + 1) * sizeof(Node*));
    for (i = 0; i <= strLen1; ++i)
    {
        dp[i] = (Node*) malloc((strLen2 + 1) * sizeof(Node));
    }

    for (i = 0; i <= strLen1; ++i)
    {
        dp[i][0].length = 0;
    }
    for (j = 0; j <= strLen2; ++j)
    {
        dp[0][j].length = 0;
    }

    for (i = 1; i <= strLen1; ++i)
    {
        for (j = 1; j <= strLen2; ++j)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                dp[i][j].length = dp[i - 1][j - 1].length + 1;
                dp[i][j].prev_i = dp[i - 1][j - 1].cur_i;
                dp[i][j].prev_j = dp[i - 1][j - 1].cur_j;
                dp[i][j].cur_i = i;
                dp[i][j].cur_j = j;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    char* ans = recoverAns(strLen1, strLen2, str1, str2, dp);

    for (i = 0; i <= strLen1; ++i)
    {
        free(dp[i]);
    }
    free(dp);

    return ans;

}


void readStrings(int* strLen1, int* strLen2, char** str1, char** str2)
{
    FILE* input = fopen("input.txt", "r");

    fscanf(input, "%d", strLen1);
    *str1 = (char*) malloc((*strLen1 + 1) * sizeof(char));
    fscanf(input, "%s", str1);

    fscanf(input, "%d", strLen2);
    *str2 = (char*) malloc((*strLen2 + 1) * sizeof(char));
    fscanf(input, "%s", str2);

    fclose(input);
}

void writeString(char* str)
{
    FILE* output = fopen("output.txt", "w");

    fprintf(output, "%s", str);

    fclose(output);
}

int main()
{
    int strLen1, strLen2;
    char** str1 = (char**) malloc(sizeof(char*));
    char** str2 = (char**) malloc(sizeof(char*));

    readStrings(&strLen1, &strLen2, str1, str2);
    char* seq = getLCS(strLen1, strLen2, str1, str2);
    writeString(seq);

    free(seq);
    free(str1);
    free(str2);
    return 0;
}
