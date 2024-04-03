#include <stdio.h>
#include <stdlib.h>

int findJudge(int N, int** trust, int trustSize, int* trustColSize) {
    int* trust_count = (int*)calloc(N + 1, sizeof(int));
    int* trusted_by_count = (int*)calloc(N + 1, sizeof(int));

    for (int i = 0; i < trustSize; ++i) {
        trust_count[trust[i][0]]++;
        trusted_by_count[trust[i][1]]++;
    }

    for (int i = 1; i <= N; ++i) {
        if (trust_count[i] == 0 && trusted_by_count[i] == N - 1) {
            free(trust_count);
            free(trusted_by_count);
            return i;
        }
    }

    free(trust_count);
    free(trusted_by_count);
    return -1;
}

int main() {
    
    int N = 4;
    int trust[][2] = {{1, 3}, {1, 4}, {2, 3}, {2, 4}, {4, 3}};
    int trustSize = sizeof(trust) / sizeof(trust[0]);
    int trustColSize = 2;

    int judge = findJudge(N, trust, trustSize, &trustColSize);
    printf("The town judge is: %d\n", judge);

    return 0;
}