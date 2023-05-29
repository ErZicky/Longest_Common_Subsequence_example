#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


//scores
const int score_char = 5;
const int score_arithmetic = 3;
const int score_casesensitive = 2;
const int score_gratis = 0;

int ScoreMath(char c1, char c2) { //score calculation per pair of characters
    if (c1 == c2) { //if the characters are the same I consider the different cases that can give points
        if (c1 == '{' || c1 == '}' || c1 == '=' || c1 == '&' || c1 == '|' || c1 == '(' || c1 == ')')
            return score_char;
        else if (isdigit(c1))
            return score_arithmetic;
        else
            return score_casesensitive;
    } else if (c1 == ' ' || c1 == '\t' || c2 == ' ' || c2 == '\t') {
        return score_gratis;
    } else {
        return 0;
    }
}

string ReadInput(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error in opening the file check the file extension: " << filename << endl;
        exit(1);
    }

    string input;
    string line;
    while (getline(file, line)) {
        input += line + '\n';
    }

    file.close();
    return input;
}

vector<vector<int>> LongestCommonSequenceProcessing(const string& source1, const string& source2) { //subsequence matrix calculation
    int m = source1.length();
    int n = source2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); //array initialization of sequences

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] + ScoreMath(source1[i - 1], source2[j - 1])}); 
        }
    }

    return dp;
}

string getBestMatch(const string& source1, const string& source2, const vector<vector<int>>& dp) { //reconstructs the longest subsequence
    int i = source1.length();
    int j = source2.length();
    string lcs;

    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i - 1][j]) {
            --i; 
        } else if (dp[i][j] == dp[i][j - 1]) {
            --j; 
        } else {
            lcs = source1[i - 1] + lcs;
            --i;
            --j;
        }
    }

    return lcs;
}


void PrintMatrix(const vector<vector<int>>& dp)
{
    int n = dp.size();
    int m = dp[0].size();

    for(int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {

    string f1;
    string f2;

    cout<<"first input file"<<endl;
    cin>>f1;
    cout<<"second input file"<<endl;
    cin>>f2;


    string source1 = ReadInput(f1);
    string source2 = ReadInput(f2);

    vector<vector<int>> dp = LongestCommonSequenceProcessing(source1, source2);
    string lcs = getBestMatch(source1, source2, dp);

    bool pmatrix = false; // set to true to print the matrix

    cout<<endl;
    cout << "Longest Common Subsequence: " << lcs << endl;
    cout << "score: " << dp[source1.length()][source2.length()] << endl;




    if(pmatrix == true)
    {

        cout<<endl;
        cout<<endl;
        PrintMatrix(dp);
    }

    return 0;
}
