#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 12


void hexToBin(char **to, char *from);
char* singleBit(char i);
char checkOfParityBit(char* a);
void secCiph(char **a, int b);
void deCiphSecLevel(FILE *fp, int count);
char binToHex(char *inp);


void getHexNumber(char* num, int n);
void hexToBin2(char **to, char *from);


int main() {
    char package[] = "AA1F2EF9D3A5";//"AA0F 2EF9 D3A5"
    int countOfShots = 0;
    FILE* fp = fopen("data.txt", "w");

    for(int i = 0; package[i] != '\0'; i++) {
        countOfShots++;
    }

    char **binShotPackage = malloc(countOfShots * sizeof(char*));
    for(int i = 0; i < countOfShots; i++) {
        binShotPackage[i] = malloc(8 * sizeof(char));
    }
    

    hexToBin(binShotPackage, package);
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
    char prevParBit = '0';
    char presParBit = '0';
    int countOfParBit = 0;
    int flag = 0;
    char *answer = malloc(count * sizeof(char));
    for(int i = 0; i < count; i++) {
        for(int j = 0; j < 8; j++) {
            c = getc(fp);
            if(c == EOF ||  c == 'x') {
                printf("error in %d block", i);
                flag = 1;
                break;
            }
            if(j > 1 && j < 6 && c == '1') {
                countOfParBit++;
            }
            shot[j] = c;
        }
        if(flag) break;

        if(shot[0] == '1') shot[0] = shot[2];
        else shot[0] = shot[2] == '1' ? '0' : '1';
        
        if(shot[1] == '1') shot[1] = shot[3];
        else shot[1] = shot[3] == '1' ? '0' : '1';
        
        if(shot[6] == '1') shot[6] = shot[4];
        else shot[6] = shot[4] == '1' ? '0' : '1';
        
        if(shot[7] == '1') shot[7] = shot[5];
        else shot[7] = shot[5] == '1' ? '0' : '1';
        shot[8] = '\0';
        
        // printf("in shot %d: %s, %c, %c, %d\n", i, shot, prevParBit, presParBit, countOfParBit);
        
        if(!(shot[0] == '0' && shot[7] == '1' && shot[1] == prevParBit && shot[6] == (countOfParBit % 2 == 0 ? '0' : '1'))) {
            printf("error in shot num %d: %s\n", i, shot);
            // if(shot[0] != '0') printf("23\n");
            // if(shot[7] != '1') printf("234\n");
            // if(shot[1] != prevParBit) printf("  2345  %c\n", prevParBit);
            // if(shot[6] != countOfParBit % 2) printf(" 23456   %d\n", countOfParBit);
            answer[i] = 'X';
        } else {
            answer[i] = binToHex(shot);
        }
        presParBit = countOfParBit % 2 == 0 ? '0' : '1';
        prevParBit = presParBit;
        countOfParBit = 0;
    }
    answer[count] = '\0';
    printf("\n%s\n", answer);
    free(answer);
}

char binToHex(char *inp) {
    char res;
    char *shot = malloc(4 * sizeof(char));
    shot[0] = inp[2];
    shot[1] = inp[3];
    shot[2] = inp[4];
    shot[3] = inp[5];
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
    free(shot);
    return res;
}
//01101000011010001100010111111011100101101111011011111010110011100110101101011010110100010010111
//01101000011010001100010111111011100101001111010011111010110011100110101101011010110100010010111
void secCiph(char **a, int b) {
    for(int i = 0; i < b; i++) {
        if(a[i][0] == a[i][2]) a[i][0] = '1';
        else a[i][0] = '0';

        if(a[i][1] == a[i][3]) a[i][1] = '1';
        else a[i][1] = '0';

        if(a[i][4] == a[i][6]) a[i][6] = '1';
        else a[i][6] = '0';

        if(a[i][5] == a[i][7]) a[i][7] = '1';
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

        getHexNumber(numberOfShot, numberOfShots);

        strcat(to[i], numberOfShot);
        numberOfShots++;
    }
    to[numberOfShots - 1][4] = '1';
    to[numberOfShots - 1][5] = '1';
    to[numberOfShots - 1][6] = '1';
    to[numberOfShots - 1][7] = '1';
}

void getHexNumber(char* num, int n) {
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

    num = singleBit(symb);

}



void hexToBin(char **to, char* from) {
    char prevParBit = '0';
    char presParBit = '0';
    char* binBit;
    for(int i = 0; from[i] != '\0'; i++) {
        to[i][0] = '0';
        to[i][1] = '\0';
        
        if(prevParBit == '0') strcat(to[i], "0");
        else strcat(to[i], "1");

        binBit = singleBit(from[i]);
        presParBit = checkOfParityBit(binBit);
        strcat(to[i], binBit);

        if(presParBit == '0') strcat(to[i], "0");
        else strcat(to[i], "1");

        strcat(to[i], "1"); //end
        prevParBit = presParBit;
        presParBit = '0';
    }
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
char checkOfParityBit(char* a) {
    int count = 0;
    for(int i = 0; i < 4; i++) {
        if(a[i] == '1') count++;
    }
    if(count % 2 == 0) return '0';
    else return '1';
}




// using namespace std;
// AA0F 2EF9 D3A5

// string hextobinary(string &package)
// {
//     string binpack = "";
//     int counter = 0;
//     for (auto i: package)
//     {
//             if (i == '0') binpack += "0000";
//             if (i == '1') binpack += "0001";
//             if (i == '2') binpack += "0010";
//             if (i == '3') binpack += "0011";
//             if (i == '4') binpack += "0100";
//             if (i == '5') binpack += "0101";
//             if (i == '6') binpack += "0110";
//             if (i == '7') binpack += "0111";
//             if (i == '8') binpack += "1000";
//             if (i == '9') binpack += "1001";
//             if (i == 'A') binpack += "1010";
//             if (i == 'B') binpack += "1011";
//             if (i == 'C') binpack += "1100";
//             if (i == 'D') binpack += "1101";
//             if (i == 'E') binpack += "1110";
//             if (i == 'F') binpack += "1111";
//             counter += 1;
//     }
//     if (counter < 14) {cout << "error in package integrity" << endl; exit(0);}
//     else return binpack;
// }

// char xorchar(char &binnumber)
// {
//     if (binnumber == '0') return '1';
//     else return '0';
// }

// vector <string> makeshots(string &data)
// {
//     vector <string> shots = {};
//     for (int i = 0; i < 48; i += 4)
//     {
//         string str;
//         str = data.substr(i, 4);
//         str = str + xorchar(str[0]) + xorchar(str[1]) + xorchar(str[2]) + xorchar(str[3]);
//         shots.push_back(str);
//     }
//     return shots;
// }

// int main()
// {
//     string package = "AA0F 2EF9 D3A5";
//     string binpackage = hextobinary(package);

//     vector <string> shots = makeshots(binpackage);

//     // shots[2][1] = '1';
    
//     for (auto i: shots)
//     {
//         for (int j = 0; j < 4; j++)
//         {
//             if (i[j] == i[j + 4]) {cout << "error in package content" << endl; exit(1);}
//         }
//     }
    
//     cout << "good" << endl;

//     return 1;
// }