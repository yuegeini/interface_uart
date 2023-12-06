#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 18


char* singleBit(char i);
void secCiph(char **a, int b);
void deCiphSecLevel(FILE *fp, int count);
char binToHex(char *inp);


char getHexNumber(int n);
void hexToBin2(char **to, char *from);


int main() {
    char package[] = "BB1F2EF9D3A5123456";//"AA0F 2EF9 D3A5"
    int countOfShots = 0;
    FILE* fp = fopen("data.txt", "w");

    for(int i = 0; package[i] != '\0'; i++) {
        countOfShots++;
    }
    char **binShotPackage = malloc(countOfShots * sizeof(char*));
    for(int i = 0; i < countOfShots; i++) {
        binShotPackage[i] = malloc(8 * sizeof(char));
    }

    hexToBin2(binShotPackage, package);
    secCiph(binShotPackage, countOfShots);

    for(int i = 0; i < countOfShots; i++) {
        // printf("%s\n", binShotPackage[i]);
        fputs(binShotPackage[i], fp);
    }
    fclose(fp);
    fp = fopen("data.txt", "r");
    deCiphSecLevel(fp, countOfShots);
    fclose(fp);

    for(int i = 0; i < countOfShots; i++) {
        free(binShotPackage[i]);
    }
    free(binShotPackage);

    return 0;
}

void deCiphSecLevel(FILE *fp, int count) {
    char c = getchar();
    char shot[8];
    int countOfShot = 0;
    int flag = 0;
    char *answer = malloc(count * sizeof(char));
    for(int i = 0; i < count && count == N; i++) {
        for(int j = 0; j < 8; j++) {
            c = getc(fp);
            if(c == EOF ||  c == 'x') {
                printf("error in %d block", i);
                flag = 1;
                break;
            }
            shot[j] = c;
        }
        shot[8] = '\0';
        if(flag) break;

        if(shot[4] == '1') shot[4] = shot[0];
        else shot[4] = shot[0] == '1' ? '0' : '1';
        
        if(shot[5] == '1') shot[5] = shot[1];
        else shot[5] = shot[1] == '1' ? '0' : '1';
        
        if(shot[6] == '1') shot[6] = shot[2];
        else shot[6] = shot[2] == '1' ? '0' : '1';
        
        if(shot[7] == '1') shot[7] = shot[3];
        else shot[7] = shot[3] == '1' ? '0' : '1';
        // shot[8] = '\0';
        printf("%s---", shot);
        char checkOfNum[4];
        checkOfNum[0] = shot[4];
        checkOfNum[1] = shot[5];
        checkOfNum[2] = shot[6];
        checkOfNum[3] = shot[7];
        // checkOfNum[4] = '\0';
        char numFromShot = binToHex(checkOfNum);
        // printf("===%s", shot);

        if(countOfShot == 15 && i != N - 1) countOfShot = 0;
        if(i == N - 1) countOfShot = 15;
        char numFromCount = getHexNumber(countOfShot);

        printf("%c==%c  in shot %d: \n", numFromCount, numFromShot, i);
        // printf("%s\n", shot);
        if(numFromCount != numFromShot) {
            printf("    ==%c!=%c    error in shot num %d: %s\n", numFromCount, numFromShot, i, shot);
            // if(shot[0] != '0') printf("23\n");
            // if(shot[7] != '1') printf("234\n");
            // if(shot[1] != prevParBit) printf("  2345  %c\n", prevParBit);
            // if(shot[6] != countOfParBit % 2) printf(" 23456   %d\n", countOfParBit);
            answer[i] = 'X';
        } else {
            answer[i] = binToHex(shot);
        }
        countOfShot++;
    }
    // if(N != count) printf("%d==%d", N, count);
    answer[count] = '\0';
    printf("\n%s\n", answer);
    free(answer);

    c = getc(fp);
    if(c != EOF) {
        printf("errorrrrrr");
    }
}

char binToHex(char *inp) {
    char res;
    char *shot;
    shot[0] = inp[0];
    shot[1] = inp[1];
    shot[2] = inp[2];
    shot[3] = inp[3];
    shot[4] = '\0';
    // printf("\n%s\n", shot);
    if (strcmp(shot, "0000") == 0) res = '0';
    else if (strcmp(shot, "0001") == 0) res = '1';
    else if (strcmp(shot, "0010") == 0) res = '2';
    else if (strcmp(shot, "0011") == 0) res = '3';
    else if (strcmp(shot, "0100") == 0) res = '4';
    else if (strcmp(shot, "0101") == 0) res = '5';
    else if (strcmp(shot, "0110") == 0) res = '6';
    else if (strcmp(shot, "0111") == 0) res = '7';
    else if (strcmp(shot, "1000") == 0) res = '8';
    else if (strcmp(shot, "1001") == 0) res = '9';
    else if (strcmp(shot, "1010") == 0) res = 'A';
    else if (strcmp(shot, "1011") == 0) res = 'B';
    else if (strcmp(shot, "1100") == 0) res = 'C';
    else if (strcmp(shot, "1101") == 0) res = 'D';
    else if (strcmp(shot, "1110") == 0) res = 'E';
    else if (strcmp(shot, "1111") == 0) res = 'F';
    else {
        // printf("ALLARM\n");
        res = 'Z';
    }
    // free(shot);
    return res;
}
//01101000011010001100010111111011100101101111011011111010110011100110101101011010110100010010111
//01101000011010001100010111111011100101001111010011111010110011100110101101011010110100010010111
void secCiph(char **a, int b) {
    for(int i = 0; i < b; i++) {
        if(a[i][0] == a[i][4]) a[i][4] = '1';
        else a[i][4] = '0';

        if(a[i][1] == a[i][5]) a[i][5] = '1';
        else a[i][5] = '0';

        if(a[i][2] == a[i][6]) a[i][6] = '1';
        else a[i][6] = '0';

        if(a[i][3] == a[i][7]) a[i][7] = '1';
        else a[i][7] = '0';
    }
}

void hexToBin2(char **to, char* from) {
    char* binBit;
    int numberOfShots = 0;
    for(int i = 0; from[i] != '\0'; i++) {
        to[i][0] = '\0';

        binBit = singleBit(from[i]);
        strcat(to[i], binBit);

        char* numberOfShot;
        if(numberOfShots == 15) numberOfShots = 0;
        char num = getHexNumber(numberOfShots);
        
        binBit = singleBit(num);
        to[i][4] = '\0';
        strcat(to[i], binBit);
        numberOfShots++;
        to[i][8] = '\0';
    }
    to[N - 1][4] = '1';
    to[N - 1][5] = '1';
    to[N - 1][6] = '1';
    to[N - 1][7] = '1';
    to[N - 1][8] = '\0';
}

char getHexNumber( int n) {
    char symb;
    
    if (n == 0) symb = '0';
    else if (n == 1) symb = '1';
    else if (n == 2) symb = '2';
    else if (n == 3) symb = '3';
    else if (n == 4) symb = '4';
    else if (n == 5) symb = '5';
    else if (n == 6) symb = '6';
    else if (n == 7) symb = '7';
    else if (n == 8) symb = '8';
    else if (n == 9) symb = '9';
    else if (n == 10) symb = 'A';
    else if (n == 11) symb = 'B';
    else if (n == 12) symb = 'C';
    else if (n == 13) symb = 'D';
    else if (n == 14) symb = 'E';
    else if (n == 15) symb = 'F';
    else {
        // printf("ALLARM\n");
        symb = 'Z';
    }
    return symb;

}


char* singleBit(char i) {
    char* binpack;
        if (i == '0') binpack = "0000";
        else if (i == '1') binpack = "0001";
        else if (i == '2') binpack = "0010";
        else if (i == '3') binpack = "0011";
        else if (i == '4') binpack = "0100";
        else if (i == '5') binpack = "0101";
        else if (i == '6') binpack = "0110";
        else if (i == '7') binpack = "0111";
        else if (i == '8') binpack = "1000";
        else if (i == '9') binpack = "1001";
        else if (i == 'A') binpack = "1010";
        else if (i == 'B') binpack = "1011";
        else if (i == 'C') binpack = "1100";
        else if (i == 'D') binpack = "1101";
        else if (i == 'E') binpack = "1110";
        else if (i == 'F') binpack = "1111";
        else binpack = "xxxx";
    return binpack;
}

