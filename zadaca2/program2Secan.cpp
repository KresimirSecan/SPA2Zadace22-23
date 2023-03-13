#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


class hashfunk{
    vector<int> hashvec;
    int size;

public:

    //konstruktor
    hashfunk(int size) {
        hashvec = vector<int>(size, 0);
        this->size = size;
    }

    //hash1
    int h1(string s){
        unsigned long long int  i =0;
        for (auto c : s){
            i +=  fmod(int(c),size);
        }
         return (i%size);
    }

    //hash2
    int h2 (string s){
        unsigned long long int i = 1;
        for (int j =0;j<s.size();j++){
            i+= fmod( ( s[j]*pow(19,j-1) ) , size);
        }
       return (i%size);
    }
    

    //hash3
    int h3 (string s){
        unsigned long long int i = 7;
        for (int j =0;j<s.size();j++){
            i+= fmod( ( s[j]*pow(30,j-1) ) , size);
        }
       return (i%size);
    }
    

    //hash4
    int h4(string s){
        unsigned long long  int i = 3;
        for (int j =0;j<s.size();j++){
            i+= fmod( ( s[j]*pow(3,j-1)*pow(7,j-1) ) , size);
        }
       return (i%size);
    }


    //insert
    void insert (string s) {
        int i1 = h1(s);
        int i2 = h2(s);
        int i3 = h3(s);
        int i4 = h4(s);

        hashvec[i1] = 1;
        hashvec[i2] = 1;
        hashvec[i3] = 1;
        hashvec[i4] = 1;
        return;
    }   

    //search
    string  search (string s){
        int i1 = h1(s);
        int i2 = h2(s);
        int i3 = h3(s);
        int i4 = h4(s);

        if (hashvec[i1] == 0 ){
            return("element nije u tablici");
        }
        if (hashvec[i2] == 0 ){
            return("element nije u tablici");
        }
        if (hashvec[i3] == 0 ){
            return("element nije u tablici");
        }
        if (hashvec[i4] == 0 ){
            return("element nije u tablici");
        }

        return("element je vjv u tablici");

    }

};

int main(){
    hashfunk a (100);

    vector<string> s = {
        "jopis107", "hstranput", "Matej293", "MateaCucman", "JosipCestar", 
        "lanamak", "DanijelaValjak", "filipuranjek", "domagojziros", "lsanic",
        "TomislavVinkovic", "IvoSusac", "matej2810", "KresimirSecan", 
        "inespejic", "InesSimunovic", "IvanFrantal", "Frle001", "inesstrapac", 
        "mkolak", "Dpritisa", "istvavk", "mtoldi", "lbrodar5", "mkristic", 
        "andreamatasovic", "balentovicanja", "IvanaVinkovic", "prakidzija", 
        "DMV1204", "JMesaric", "KarloKampic", "jurick1910", "LarisaDarojkovic"
    };

    for(auto i : s) {
        a.insert(i);
    }


    cout << a.search("lbrodar5") << endl;
    cout << a.search("jopis107") << endl;

    cout<<a.search("branekadtibane")<<endl;
    cout << a.search("BMWKEC") << endl; 

    cout<<a.search("KresimirSecan")<<endl;
    return 0;
}