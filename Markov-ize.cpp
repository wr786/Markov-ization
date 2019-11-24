#include<iostream>
#include<cstdio>
#include<string>
#include<map>
using namespace std;
#define SPAN 900
// 乐音体系数字化，百位数代表乐音长度，98代表休止符
// 备注：每个音的用三位数表示，百位表示时值，剩下的两位数对应乐音体系中的1-97的数字，特别地，休止符用98表示
// 在一阶情况下，第4~6位为第一个，第7~9位为第二个
// 在二阶情况下，第1~3位为第一个，第4~6位为第二个，第7~9位第三个
// double matrix[SPAN * SPAN * SPAN + SPAN * SPAN + SPAN];
map<long long, double> matrix; 
int visrow[SPAN*SPAN + SPAN], viscol[SPAN], numrow, numcol;
// 一阶
void Markovize_1() {
    int note_pre, note_suf;
    cin >> note_pre;
    while(cin >> note_suf) { // 第SPAN-1位代表sum
        matrix[note_pre*SPAN + note_suf]++;
        matrix[note_pre*SPAN + SPAN-1]++; // 直接在读入的时候求和，加速
        note_pre = note_suf;
        if(!visrow[note_pre]) numrow++;
        if(!viscol[note_suf]) numcol++;
        visrow[note_pre]++; viscol[note_suf]++;
    }
    for(int i=0; i<SPAN-1; i++) {
        if(!matrix[i*SPAN + SPAN-1]) continue; // prone
        for(int j=0; j<SPAN-1; j++)  // 变为转移概率 
            if(matrix[i*SPAN + j]) {
                matrix[i*SPAN + j] /= matrix[i*SPAN + SPAN-1];
            }
                
    }
    // 输出
    cout << 1*10000 + numrow*100 + numcol; // 代表这是1阶矩阵
    for(int j=0; j<SPAN-1; j++) { // 初始化上指标
        if(viscol[j]) {
            cout << "\t" << j;
        }
    }
    cout << endl;
    for(int i=0; i<SPAN-1; i++) {
        if(visrow[i]) {
            cout << i;
            for(int j=0; j<SPAN-1; j++) {
                if(!viscol[j]) continue;
                cout << "\t";
                if(matrix[i*SPAN + j]) {
                    printf("%.2lf", matrix[i*SPAN + j]);
                }
                else {
                    printf("0");
                }
             }
            cout << endl;
        }
    }
}

void Markovize_2() {
    int note_pre1, note_pre2, note_suf;
    cin >> note_pre1 >> note_pre2;
    while(cin >> note_suf) { // 第SPAN-1位代表sum
        matrix[note_pre1*SPAN*SPAN + note_pre2*SPAN + note_suf]++;
        matrix[note_pre1*SPAN*SPAN + note_pre2*SPAN + SPAN-1]++;
        if(!visrow[note_pre1*SPAN + note_pre2]) numrow++;
        if(!viscol[note_suf]) numcol++;
        visrow[note_pre1*SPAN + note_pre2]++; viscol[note_suf]++;
        note_pre1 = note_pre2;
        note_pre2 = note_suf;
    }
    for(int i=0; i<SPAN-1; i++)
        for(int j=0; j<SPAN-1; j++) {  
            if(!matrix[i*SPAN*SPAN + j*SPAN + SPAN-1]) continue;
            for(int k=0; k<SPAN-1; k++)  // 变为转移概率 
            if(matrix[i*SPAN*SPAN + j*SPAN + k]) {
                matrix[i*SPAN*SPAN + j*SPAN + k] /= matrix[i*SPAN*SPAN + j*SPAN + SPAN-1];
            }
        }
    // 输出
    cout << 2*10000 + numrow*100 + numcol; // 代表这是二阶
    for(int k=0; k<SPAN-1; k++) { // 初始化上指标
        if(viscol[k]) {
            cout << "\t" << k;
        }
    }
    cout << endl;
    for(int i=0; i<SPAN-1; i++)
        for(int j=0; j<SPAN-1; j++) {
        if(visrow[i*SPAN + j]) {
            cout << i << " " << j;
            for(int k=0; k<SPAN-1; k++) {
                if(!viscol[k]) continue;
                cout << "\t";
                if(matrix[i*SPAN*SPAN + j*SPAN + k]) {
                    printf("%.2lf", matrix[i*SPAN*SPAN + j*SPAN + k]);
                }
                else {
                    printf("0");
                }
             }
            cout << endl;
        }
    }
}

int main() {
    cout << "Please enter the rank you want(1/2):\n";
    int op; cin >> op;
    // 打开文件读写
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    if(op == 1) Markovize_1();
    else Markovize_2();
    return 0;
}