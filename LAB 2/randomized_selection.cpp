#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <fstream>

using namespace std;

int num;
int seed = 1001001;

void print_vector(vector<int> v, int n){

    for(int i = 0; i<n; i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

bool comp(int x, int y){
    num++;
    return x < y;

}

int randomized_sel(vector<int> &A){

    int n = A.size();

    int sizeR = int(pow(n, 3.0/4.0));
    vector <int> R = vector<int> (sizeR);

    for(int i = 0; i<R.size(); i++){
        int idx = rand() % n;
        R[i]=A[idx];
    }
    sort(R.begin(),R.end(), comp);

    //cout << "Vector R: " << endl;
    //print_vector(R,R.size());

    int v = pow(n, 3.0/4.0)/2;

    int d =  R[int(v - sqrt(n))];
    int u =  R[int(v + sqrt(n))];

    cout << "d " << d << " u " << u << endl;


    vector <int> C = vector<int> ();

    int ld = 0;
    int lu = 0;

    for(int i = 0; i<n; i++){

        if(A[i] >= d and A[i] <= u){
            C.push_back(A[i]);
        }
        else if(A[i] < d) ld += 1;
        else if(A[i] > u) lu += 1;

    }
    cout << "ld " << ld << "  lu " << lu << endl;


    if(ld > n/2 or lu > n/2 or C.size() > pow(n, 3.0/4.0)*4) return -1;

    //cout << "Vector C: " << endl;
    sort(C.begin(),C.end(),comp);

    //print_vector(C,C.size());

    return C[ceil(n/2)-ld+1];

}



int main(){

    int delta = 10000;
    int nmax =  200000;
    int nperm = 1000;
    int total = nperm*(nmax/delta);
    int fallos = 0;

    ofstream o;
    o.open("plots/comparisonsExtraRS.txt");
    srand(seed);

/*
    int n = 20000;

    vector<vector<int>> permutations(0, vector<int>(n));
    vector<int> original_vector(n);

    for(int i = 0; i < n; i++) original_vector[i] = i;

    for(int j = 0; j < nperm; j++){
            random_shuffle(original_vector.begin(),original_vector.end());
            permutations.push_back(original_vector);

    }

    for(auto vec : permutations){
            num = 0;
            int v = randomized_sel(vec);
            cout << v << endl;
            if(v != -1)o << num << ",";
            else {
                fallos++;
            }
    }
    o << endl;

    */
    for(int n = 10000; n < nmax; n+= delta){

        vector<int> original_vector(n);

        vector<vector<int>> permutations(0, vector<int>(n));

        for(int i = 0; i < n; i++) original_vector[i] = i;

        for(int j = 0; j < nperm; j++){
            random_shuffle(original_vector.begin(),original_vector.end());
            permutations.push_back(original_vector);

        }

        for(auto vec : permutations){
            num = 0;
            int v = randomized_sel(vec);
            cout << v << endl;
            if(v != -1)o << num << ",";
            else {
                fallos++;
            }
        }
        o << endl;
    }
    cout << fallos << "  " << double(fallos)/total << endl;
}
