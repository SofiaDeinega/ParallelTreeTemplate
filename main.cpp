#include <iostream>
#include <set>
#include <cassert>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <math.h>


using namespace std;

int* a = new int[1000];
int N, res, sum1, sum2, s1, s2; // sum1, sum2 - суммарные веса каждой кучи; 
string heap1, heap2; // две кучи, представленные в виде последовательности камней 

// перевод чисел в строковый формат
template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

unsigned int start_time = clock(); // засекаем время

// рекурсивное распределение камней по кучам
void rec(int n, int sum1, int sum2, string str1, string str2)
{
    if (n == N)
    {
        if (abs(sum1 - sum2) <= res) {
            res = abs(sum1 - sum2);
            s1 = sum1;
            s2 = sum2;
            heap1 = str1;
            heap2 = str2;
        }
        return;
    }
    rec(n + 1, sum1 + a[n], sum2, str1 + " " + toString(a[n]), str2);
    rec(n + 1, sum1, sum2 + a[n], str1, str2 + " " + toString(a[n]));
}


int main()
{
    cout << "Enter file's name: " << endl;
    char* name = new char[20];
    cin >> name;
    ofstream fout("output.txt");
    ifstream  ifs(name);

    int s = 0; // общая сумма
    N = 0;
    heap1 = "";
    heap2 = "";

    while (!ifs.eof()) {
        ifs >> a[N];        // считывание из файла
        s += a[N];   // считаем вес
        cout << a[N] << " ";
        N = 1 + N;     // считаем кол-во камней
    }
    ifs.close();
    res = 20000000;
    s1 = s2 = 0;  // до распределения кучи нулевые
    rec(0, 0, 0, "", "");

    unsigned int end_time = clock();
    unsigned int s_time = end_time - start_time;

    // запись в файл полученных результатов
    fout << " sum1: " << toString(s1) << "\n";
    fout << " sum2: " << toString(s2) << "\n";
    fout << " dif: " << toString(res) << "\n";
    fout << " heap1: " << toString(heap1) << "\n";
    fout << " heap2: " << toString(heap2) << "\n";
    fout << " time: " << toString(s_time) << "\n";
    fout.close();
    cout << endl << "Complete" << endl;
    cout << "sum1:" << s1 << " sum2:" << s2 << " dif:" << res << endl;
    cout << " heap1: " << heap1 << endl << " heap2: " << heap2;

    return 0;
}