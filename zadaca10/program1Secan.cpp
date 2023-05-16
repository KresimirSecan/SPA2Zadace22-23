 #include <iostream>
 #include <vector>
 using namespace std;

 
//O (n**2) nije bas efektivno ali radi 
vector<pair<int,int>> kritican (vector<vector<int>>& adjMatrix){
    vector<pair<int,int>> crit;
    bool kec ;
    pair<int,int> d;
    for (int i = 0; i < adjMatrix.size(); i++) {
        kec=false;
        for (int j = 0; j < adjMatrix.size(); j++) {
            if (adjMatrix[i][j]!=0){
                if (kec==false){
                    kec=true;
                    if (i>j){
                        d.first=j;
                        d.second=i;
                    }else{
                        d.first=i;
                        d.second=j;
                    }
                }else{
                    kec=false;
                    break;
                }
            }
        }
        if (kec==true){
            crit.push_back(d);
            adjMatrix[d.first][d.second] = 0;
            adjMatrix[d.second][d.first] = 0;
        }
    }
    return crit;
}


int main(){
    int cvorovi, bridovi;
    cin >> cvorovi >> bridovi;
    vector<vector<int>> matrica(bridovi, vector<int>(3));
    for (int i = 0; i < bridovi; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> matrica[i][j];
        }
    }

    //matrica susjedstva
    vector<vector<int>> adjMatrix (cvorovi,vector<int>((cvorovi),0));
    for (int i = 0; i < bridovi; i++) {
        adjMatrix[matrica[i][0]][matrica[i][1]] =matrica[i][2];
        adjMatrix[matrica[i][1]][matrica[i][0]] =matrica[i][2];
    }

    vector<pair<int,int>> crit = kritican(adjMatrix);

    cout<<crit.size()<<" kriticne veze"<<endl;
    for (auto i :crit) {
        cout<<i.first<<" - "<<i.second<<endl;
    }

    return 0;
}