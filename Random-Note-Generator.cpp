// author: wr786
#include<cstdio>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<map>
#include<string>
#include<sstream>
using namespace std;
#define NOTEMAX 100
double matrix[NOTEMAX*1000 + NOTEMAX][NOTEMAX]; // 转移概率矩阵
map<int, int> hashMapCol, hashMapRow;

int main() {
    cout << "Please enter the num of notes you want to generate:\n";
    int num; cin >> num;
    // 读入转移矩阵
    freopen("output.txt", "r", stdin);
    freopen("#output.txt", "w", stdout);
    string firstline; getline(cin, firstline);
    istringstream iss; iss.str(firstline);
    int type; iss >> type; 
    int rank = type / 10000, numrow = (type/100)%100, numcol = type%100;// 阶数，行数，列数
    for(int j=1; j<=numcol; j++)
        iss >> hashMapCol[j];
    for(int i=1; i<=numrow; i++) {
        int rownum; cin >> rownum; hashMapRow[i] = rownum;
        if(rank == 2) {
            cin >> rownum; hashMapRow[i] = hashMapRow[i]*1000 + rownum; // /1000代表第一个音符，%1000代表第二个音符
        } 
        for(int j=1; j<=numcol; j++) {
            cin >> matrix[i][j];
        }
    }
    // 处理 
    int lastnote = -1;
    srand((unsigned)time(NULL)); // 重置随机数种子
    while(num--) {
        double pos = (double)(rand() % 100) / 100; // 随机出的概率
        while(pos < 1e-6) pos = (double)(rand() % 100) / 100;
        if(lastnote == -1) { // 代表我们需要先随机出第一个音符
            int firstnote = (int)(pos * numrow);
            if(rank == 1) // 一阶
                cout << hashMapRow[firstnote];
            else { // 二阶
                cout << hashMapRow[firstnote] / 1000 << " " << hashMapRow[firstnote] % 1000;
            }
            lastnote = firstnote;
        } else {
            double possum = 0;
            for(int j=1; j<=numcol; j++) {
                possum += matrix[lastnote][j];
                if(possum >= pos) {
                    cout << hashMapCol[j];
                    int nextnote;
                    for(int i=1; i<=numrow; i++) 
                        if(rank == 2) {
                            if(hashMapRow[i] == (hashMapRow[lastnote]%1000)*1000 + hashMapCol[j])
                                nextnote = i;
                        } else {
                            if(hashMapRow[i] == hashMapCol[j])
                                nextnote = i;
                        }
                    lastnote = nextnote; // 这样对二阶也适用！
                    break;
                }
                if(j == numcol) cout << pos << ">" << possum << endl;
            }
        }
        cout << " ";
    }
}