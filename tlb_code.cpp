//  main.cpp
//  Computer Architecture and Organisation
//  Created by Sukrit Jindal (22125037)

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>
#include <deque>
#define ulli unsigned long long int

using namespace std;

int main(int argc, char * argv[]) {
    string Page_Table_Add (argv[1]), TLB_Access_Add (argv[2]), Assoc_Temp (argv[4]);
    ifstream Page_Table, TLB_Access;
    ofstream TempOutput1, OutputFinal;
    ifstream TempOutput2;
    Page_Table.open(Page_Table_Add);
    TLB_Access.open(TLB_Access_Add);
    string s = "22125037_" + Page_Table_Add + "_" + TLB_Access_Add + "_LRU_" + Assoc_Temp;
    string s_ = s + "_TempOutput";
    TempOutput1.open(s_);
    OutputFinal.open(s);
    TempOutput2.open(s_);
    ulli PageBits, Assoc;
    ulli Access = 0, Miss = 0, Hit = 0;
    Assoc = stoull(Assoc_Temp);
    map < ulli, ulli > mapping;
    if(Page_Table.is_open()) {
        string t;
        Page_Table >> t;
        Page_Table >> t;
        Page_Table >> t;
        Page_Table >> t;
        ulli t1, t2;
        while (Page_Table >> t1 >> t2) {
            mapping[t1] = t2;
        }
    }
    if (TLB_Access.is_open() and TempOutput1.is_open()) {
        TLB_Access >> PageBits;
        deque < ulli > TLB;
        ulli PageSize = 1 << PageBits;
        ulli t1, t2, t3;
        while(TLB_Access >> t1) {
            bool flag = false;
            t2 = t1/PageSize;
            t3 = t1%PageSize;
            Access++;
            deque < ulli > :: iterator check = find(TLB.begin(), TLB.end(), t2);
            if (check != TLB.end()) {
                TLB.erase(check);
                Hit++;
                flag = true;
            }
            else Miss++;
            if (TLB.size() < Assoc) {
                TLB.push_back(t2);
            }
            else {
                TLB.pop_front();
                TLB.push_back(t2);
            }
            TempOutput1 << t3 + mapping[t2]*PageSize << " ";
            if (flag) TempOutput1 << "HIT\n";
            else TempOutput1 << "MISS\n";
        }
    }
    if(OutputFinal.is_open()) {
        OutputFinal << "TOTAL_ACCESSES = " << Access << endl;
        OutputFinal << "TOTAL_MISSES = " << Miss << endl;
        OutputFinal << "TOTAL_HITS = " << Hit << endl;
        if(TempOutput2.is_open()) {
            string s1, s2;
            while (TempOutput2 >> s1 >> s2) {
                OutputFinal << s1 << "\t" << s2 << endl;
            }
        }
    }
    TempOutput1.close();
    TempOutput2.close();
    OutputFinal.close();
    Page_Table.close();
    TLB_Access.close();
    remove(s_.c_str());
}
