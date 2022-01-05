
#include <iostream>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<string>
#include<time.h>
#pragma warning (disable: 4996)

int M = 5000;
using namespace std;

struct URL {
    string data = "";
    int* idlk = new int[M];
    int count;
};

struct HastTable {
    int key;
    URL* table = new URL[M];
};

int n;
int* index;
int** matrix;
int* move_id;
HastTable* hast ;
int m;
URL url;

int string_tokey(string S)
{
    int key = 0;
    for (int i = 1; i < S.length(); i++)
        key += S[i] * i;
    key = int(key) % (M);
    int i = 1;
    while (hast->table[index[key]].data != S && index[key] != 0)
    {
        key = (key + i) % M;
        i++;
    }
    return key;
}
void insertParent(string S)
{
    int key = string_tokey(S);
    index[key] = n;
    hast->table[n].data = S;
    n++;
}
void insertChild(string url1, string url2)
{
    int key1 = string_tokey(url1);
    if (index[key1] == 0)
    {
        hast->table[n].data = url1;
        index[key1] = n;
        n++;
    }
    int key2 = string_tokey(url2);

    if (index[key2] == 0)
    {
        hast->table[n].data = url2;
        index[key2] = n;
        n++;
    }

    int count = hast->table[index[key1]].count;
    hast->table[index[key1]].idlk[count] = index[key2];
    hast->table[index[key1]].count++;
}

double insert(string s[], int count)
{
    M = count * 2;
    n = 1;
    m = 0;
    hast = new HastTable;
    index = new int[M];
    for (int i = 0; i < M; i++)
    {
        index[i] = 0;
        for (int j = 0; j < M; j++)
            hast->table[i].idlk[j] = 0;
        hast->table[i].count = 1;
    }
    double time;
    clock_t start, end;
    start = clock();
    insertParent(s[0]);
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    for (int i = 1; i < count; i++)
    {
        start = clock();
        insertChild(s[rand() % i], s[i]);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
    }
    return time;
}

static const char alphanum[] =
"0123456789"
"!@#$%^&*."
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom()  
{

    return alphanum[rand() % stringLength];
}

int main()
{
    int count = 50;
    while (count <= 500)
    {
        double time = 0;
        for (int i = 0; i < 100; i++)
        {
            string* s = new string[count];
            for (int j = 0; j < count; j++)
            {
                int m = rand() % 15 + 15;
                for (int z = 0; z < m; z++)
                {
                    s[j]+= genRandom();
                }
            }
            double time_use =  insert(s, count);
            time += time_use;
        }
        time = (double)time / 100;
        cout << time << endl;
        count += 50;
    }
    return 0;

}