#include<stdio.h>
#include<stdlib.h>

int max(int a, int b)
{
    if (a < b)
    {
        return b;
    }
    return a;
}

int* recoverLIS(int* dp, int* array, int ind, int subSeqLen)
{
    int* seq = (int*) malloc(subSeqLen * sizeof(int));
    int length = subSeqLen;
    seq[length - 1] = array[ind];
    --length;
    int i;
    for (i = ind - 1; i >= 0; --i)
    {
        if (dp[i] == length && array[i] <= seq[length])
        {
            seq[length - 1] = array[i];
            --length;
        }
    }
    free(dp);
    return seq;
}


int* getLIS(int* array, int arrLen, int* subSeqLen)
{
    int* dp = (int*) malloc(arrLen * sizeof(int));
    int curMaxInd = 0;
    int i, j;
    for (i = 0; i < arrLen; ++i)
    {
        dp[i] = 1;
    }

    for (i = 0; i < arrLen; ++i)
    {
        for (j = 0; j < i; ++j)
        {
            if (array[j] <= array[i])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        if (dp[i] > dp[curMaxInd])
        {
            curMaxInd = i;
        }
    }
    *subSeqLen = dp[curMaxInd];
    int* ans = recoverLIS(dp, array, curMaxInd, *subSeqLen);
    return ans;
}

int* readData(int* arrLen)
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", arrLen);


    int* a = (int*) malloc(*arrLen * sizeof(int));
    int i;
    for (i = 0; i < *arrLen; ++i)
    {
        fscanf(input, "%d", &a[i]);
    }
    fclose(input);
    return a;
}

void writeData(int* a, int subSeqLen)
{
    FILE* output = fopen("output.txt", "w");

    int i;
    for (i = 0; i < subSeqLen; ++i)
    {
        fprintf(output, "%d ", a[i]);
    }
    fclose(output);
}

int main()
{
    int arrLen, subSeqLen;
    int* array = readData(&arrLen);
    int* subSeq = getLIS(array, arrLen, &subSeqLen);
    writeData(subSeq, subSeqLen);

    free(subSeq);
    free(array);
    return 0;
}
