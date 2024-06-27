#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

int hashh(string s) {
    if ('a' <= s[0] && s[0] <= 'z') {
        return s[0] - 'a';
    } else {
        return s[0] - 'A';
    }
}
void init(int arr[])
{
    for(int i=0;i<26;i++)
    {
        arr[i]=INT32_MIN;
    }
}

void myprint(string s[], stack<int*> &stck) {
    int found = 0;
    while (!found && !stck.empty()) {
        int *arr = stck.top();
        if (arr[hashh(s[1])] != INT32_MIN) {
            found = 1;
            cout << arr[hashh(s[1])] << endl;
        } else {
            stck.pop();
        }
    }
    if(found==0)
    {
        cout<<"ERROR:variable '"<<s[1]<<"' not declared in current scope"<<endl;
        EXIT_FAILURE;
    }
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open the input file." << endl;
        return 1;
    }

    string statement;
    stack<int*> stk;
    while (getline(inputFile, statement)) {
        string temp;
        string s[3];
        istringstream iss(statement);
        int i = 0;
        while (iss >> s[i]) {
            i++;
        }
       // cout<<s[0]<<" "<<s[1]<<endl;
        if (!s[0].compare("begin")) {
            //cout<<"in begin"<<endl;
            int* arr = new int[26];

            init(arr);
            stk.push(arr);
        } else if (!s[0].compare("assign")) {
            //cout<<"in assign"<<endl;
            int* arr = stk.top();
            arr[hashh(s[1])] = stoi(s[2]);
        } else if (!s[0].compare("print")) {
            
            myprint(s, stk);
        } else if (!s[0].compare("end")) {
           
            delete[] stk.top(); 
            stk.pop();
        }
    }

    inputFile.close();
    return 0;
}

