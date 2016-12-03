#define SIZE
int AnsLen =
char** ans;
void CreateArray()
{
    ans = (char**) malloc(AnsLen * sizeof(char*));
    int i;
    for (i = 0; i < AnsLen; ++i)
    {
        ans[i] = (char*) malloc(SIZE * sizeof(char));
    }
}
