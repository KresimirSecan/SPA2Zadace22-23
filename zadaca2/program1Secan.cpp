#include <iostream>
#include <vector>
#include <random>
#include <list>
using namespace std;

typedef list <pair <int,float> > link;


class hashfunk{
    vector<link*> hashvec;

public:
    hashfunk(int size) {
        hashvec = vector<link*>(size, nullptr);
    }

    int f (int x){
        default_random_engine generator;
        uniform_int_distribution<int> distribution(0,6);
        int ai ,xi; 
        int index = 0;
        while (x!=0){
            ai = distribution(generator);
            xi = x % 10 ;
            x=x/10;
            index = index+(ai*xi);
        } 
        return (index %7);  
    }

    void insert(int x,float v){
        int i = f(x);
        pair<int,float> d = {x,v}; 
        if (hashvec[i] == nullptr){
            hashvec[i] = new link();
        }
        hashvec[i]->push_back(d);
        
    }


    void search(int key) {
    int i = f(key);
    if (hashvec[i] == nullptr) {
        cout << "kljuc ne postoji" << endl;
    } else {
        for (auto p : *(hashvec[i])) {
            if (p.first == key) {
                cout << "kljuc je pronaden, vrijednost: " << p.second << endl;
                return;
            }
        }
        cout << "kljuc ne postoji" << endl;
    }
}


};
int main(){

    hashfunk a(10);
    vector <pair <int,float>>  v  { {7,0.1},{5,0.1},{300,0.2},{1,0.4} };

    for (auto i: v){
        a.insert (i.first,i.second);
    }

    a.search(5);
    a.search(300);
    a.search(2);
    a.search(1);
    a.search(21);

    return 0;
}