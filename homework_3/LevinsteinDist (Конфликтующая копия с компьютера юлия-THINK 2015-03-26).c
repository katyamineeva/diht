int levenshteinDistance(char* str1, char* str2, int strLen1, int strLen2; deleteCost, insertCost, replaceCost, transposeCost: int):
    // ��������� ������� �������
    s[m] - str1
    t[n] - str2
    if (S == "")
        if (T == "")
            return 0
        else
            return N
    else if (T == "")
        return M
    D: int[0..M + 1][0..N + 1]   // ��������
    INF = M + N                  // ������� ���������

    // ���� ��������
    D[0][0] = INF
    for i = 0 to M
        D[i + 1][1] = i
        D[i + 1][0] = INF
    for j = 0 to N
        D[1][j + 1] = j
        D[0][j + 1] = INF

    lastPosition: int[0..���������� ��������� �������� � S � T]
    //��� ������� �������� C �������� ������ �������� lastPosition[C]

    foreach (char Letter in (S + T))
        lastPosition[Letter] = 0

    for i = 1 to M
        last = 0
        for j = 1 to N
            i' = lastPosition[T[j]]
            j' = last
            if S[i] == T[j]
                D[i + 1][j + 1] = D[i][j]
                last = j
            else
                D[i + 1][j + 1] = min(D[i][j] + replaceCost, D[i + 1][j] + insertCost, D[i][j + 1] + deleteCost)
            D[i + 1][j + 1] = min(D[i + 1][j + 1], D[i'][j'] + (i - i' - 1) \cdot deleteCost + transposeCost + (j - j' - 1) \cdot insertCost)
        lastPosition[S[i]] = i

    return D[M + 1][N + 1]
