#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>


using namespace std;

int seed = 1001001;

void print_vector(vector<int> v, int n){

    for(int i = 0; i<n; i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

int median3(int a, int b, int c){ //Fast median of 3 elements using xor

    if ((a > b) ^ (a > c))
        return a;
    else if ((b < a) ^ (b < c))
        return b;
    else
        return c;

}

void quickselect(vector<int> &A, int e, int d, int elem, int &comp){

    int r = rand() % (d-e);
    int p1 = A[r+e];
    r = rand() % (d-e);
    int p2 = A[r+e];
    r = rand() % (d-e);
    int p3 = A[r+e];

    int pivot = median3(p1,p2,p3);



    vector<int> Aord(A.size(),0);
    //print_vector(A, Aord.size());

    int lowerit = e;
    int higherit = d-1;
    for(int i = e; i< d; i++){
        //cout << "elem: "<< A[i] << endl;
        if(A[i] < pivot){
            comp++;
            Aord[lowerit] = A[i];
            lowerit++;
            //cout << "lower" << endl;
        }
        else if (A[i] > pivot){
            comp++;
            Aord[higherit] = A[i];
            higherit--;
            //cout << "higher" << endl;
        }
    }
    //lowerit++;
    Aord[lowerit] = pivot;

    //cout << "P: " << pivot << endl;
    //print_vector(Aord, Aord.size());
    A = Aord;



    //cout <<  A[lowerit] << endl;
    if(elem == lowerit){
        cout << elem << " == " << lowerit << endl;
        return;
        }
    else if (elem < lowerit) quickselect(A, e ,lowerit, elem, comp);

    else quickselect(A, lowerit, d, elem, comp);
}



int main(){

    int delta = 10000;
    int nmax =  200000;
    int nperm = 1000;

    //int delta = 2000; //Increment of the j element to find
    //int n = 20000; //size of the vector
    srand(seed);

    ofstream o;
    o.open("plots/comparisonsMedian3.txt");

    for(int n = 10000; n < nmax; n+= delta){

    vector<int> original_vector(n);

    int nperm = 1000;

    vector<vector<int>> permutations(0, vector<int>(n));

    for(int i = 0; i < n; i++) original_vector[i] = i;

    for(int j = 0; j < nperm; j++){
        random_shuffle(original_vector.begin(),original_vector.end());
        permutations.push_back(original_vector);

    }


    int comp;
   // for(int j = 0; j<n-1; j+=delta){
        int j = floor((n+1)/2);

        for(auto vec : permutations){
            comp = 0;
            quickselect(vec,0, vec.size(), j, comp);
            o << comp << ",";

        }
        o << endl;
    }
   // }
}

