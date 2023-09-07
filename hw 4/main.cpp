#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int T_SIZE = 8192;

int hash_1(string const &key, int tableSize) {
    return (key.size() * key.size() * 4) % tableSize;
}

int hash_2(string const &key, int tableSize) {
    return (key[0] + 27 * key[1] + 729 * key[2]) % tableSize;
}

int hash_3(string const &key, int tableSize) {
    return(key.size() * key[0] + key.size() * key[1] - key.size() * key[2] +
           key.size() * key[3] + key.size() * key[0]) % tableSize;
}

int main() {

    string  linTable[T_SIZE], quadTable[T_SIZE];
    string curr;
    int lProbeCnt, qProbeCnt;

    fstream dictFile("dict.txt", ios::in);
    lProbeCnt = qProbeCnt = 0;

    //hash_1
    while (dictFile >> curr) {
        int hVal = hash_1(curr, T_SIZE);
        for (int i = 0; i < T_SIZE; ++i) {
            int lNdx = (hVal + i) % T_SIZE;
            lProbeCnt++;
            if (linTable[lNdx] == "") {
                linTable[lNdx] = curr;
                break;
            }
        }
        for (int i = 0; i < T_SIZE; ++i) {
            int qNdx = (hVal + (i * i)) % T_SIZE;
            qProbeCnt++;
            if (quadTable[qNdx] == "") {
                quadTable[qNdx] = curr;
                break;
            }
        }

    }
    cout << "Linear Probing Hash_1, Table size: " << T_SIZE << ", Count: "<< lProbeCnt << endl;
    cout << "Quadratic Probing Hash_1, Table size: " << T_SIZE << ", Count: "<< qProbeCnt << endl << endl;

    //hash_2
    //reset
    std::fill_n(linTable, T_SIZE, "");
    std::fill_n(quadTable, T_SIZE, "");
    dictFile.clear();
    dictFile.seekg(0, dictFile.beg);
    lProbeCnt = qProbeCnt = 0;

    while (dictFile >> curr) {
        int hVal = hash_2(curr, T_SIZE);
        for (int i = 0; i < T_SIZE; ++i) {
            int lNdx = (hVal + i) % T_SIZE;
            lProbeCnt++;
            if (linTable[lNdx] == "") {
                linTable[lNdx] = curr;
                break;
            }
        }
        for (int i = 0; i < T_SIZE; ++i) {
            int qNdx = (hVal + (i * i)) % T_SIZE;
            qProbeCnt++;
            if (quadTable[qNdx] == "") {
                quadTable[qNdx] = curr;
                break;
            }
        }
    }

    cout << "Linear Probing Hash_2, Table size: " << T_SIZE << ", Count: "<< lProbeCnt << endl;
    cout << "Quadratic Probing Hash_2, Table size: " << T_SIZE << ", Count: "<< qProbeCnt << endl << endl;


    //hash_3
    //reset

    std::fill_n(linTable, T_SIZE, "");
    std::fill_n(quadTable, T_SIZE, "");
    dictFile.clear();
    dictFile.seekg(0, dictFile.beg);
    lProbeCnt = qProbeCnt = 0;


    while (dictFile >> curr) {
        int hVal = hash_3(curr, T_SIZE);
        for (int i = 0; i < T_SIZE; ++i) {
            int lNdx = (hVal + i) % T_SIZE;
            lProbeCnt++;
            if (linTable[lNdx] == "") {
                linTable[lNdx] = curr;
                break;
            }
        }
        for (int i = 0; i < T_SIZE; ++i) {
            int qNdx = (hVal + (i * i)) % T_SIZE;
            qProbeCnt++;
            if (quadTable[qNdx] == "") {
                quadTable[qNdx] = curr;
                break;
            }
        }

    }
    cout << "Linear Probing Hash_3, Table size: " << T_SIZE << ", Count: "<< lProbeCnt << endl;
    cout << "Quadratic Probing Hash_3, Table size: " << T_SIZE << ", Count: "<< qProbeCnt << endl << endl;

    dictFile.close();

    return 0;
}