#include<bits/stdc++.h>

#define CONTRADICTION 100001

using namespace std;
using namespace std::chrono;
class node {
    public:
        vector<vector<int>> f;
        set<int>v;
        void fill();
        void printNode(); //For debugging purpose.
};

void node::printNode(){
    cout<<"f = \n";
    for(int i=0; i<f.size(); i++){
        cout<<"\t";
        for(int j=0; j<f[i].size(); j++){
            cout<<f[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"v = \n\t";
    for(set<int>::iterator itr = v.begin(); itr != v.end(); itr++){
        cout<<*itr<<" ";
    }
    cout<<endl<<endl;
}



stack<node*>s;
int variables, clauses, temp, sat=0, counter = 0;

void printSat(set <int> &v){
    cout<<"SAT\n";
    for(int i=1; i<=variables; i++){
        if(v.count(i) > 0){
            cout<<i<<" ";
        } else {
            cout<<-i<<" ";
        }
    }
    cout<<endl;
}

// Cleans a formula by removing the true clauses and also removing the false literals in the formula.
// literal is the new element thatt  has been added/
// RETURN TRUE OR FALSE BASED ON IF IT COULD CLEAN SUCCESSFDULLY OR NOT;
bool cleanFormula(vector <vector<int>> &f, set <int> &v, int literal){
    vector<int>::iterator negation;
    vector<int>trueClauses;
    //Uncomment the next section if wrong asnwers are recieved.
    //if(v.count(-literal) > 0){
        //return false;
    //}
    for(int i=0; i<f.size(); i++){
        if(find(f[i].begin(), f[i].end(), literal) != f[i].end()){
            trueClauses.push_back(i);
        }
        negation = find(f[i].begin(), f[i].end(), -literal);
        if(negation != f[i].end()){
            if(f[i].size() == 1){
                return false;
            }
            f[i][negation-f[i].begin()] = f[i].back();
            f[i].pop_back();
        }
    }
    for(int i=trueClauses.size()-1; i>=0; i--){
        f[trueClauses[i]] = f.back();
        f.pop_back();
    }
    return true;
}

//Returns the literal which is a unit contradiction;
//Returns 0 if UnitClause not found and CONTRADICTION if unitClause found raises a contradiction;
int findUnitClause(vector<vector<int>> &f, set<int>&v){
    for(int i=0; i<f.size(); i++){
        if(f[i].size() == 1){
            if(v.count(-f[i][0]) > 0){
                return CONTRADICTION;
            }
            return f[i][0];
        }
    }
    return 0;
}

void node::fill(){

    //printNode();
    //Search for unit clauses and set them if possible, else return;
    int unitClause;
    do{
        unitClause = findUnitClause(f,v);
        if(unitClause == CONTRADICTION){
            return;
        }
        if(unitClause == 0){
            break;
        }
        v.insert(unitClause);
        if(!cleanFormula(f,v,unitClause)) return;
    } while(unitClause != 0);

    // REACHED A SATISFIABLE ASSIGNMENT
    if(f.size() == 0){
        printSat(v);
        sat = 1;
        return ;
    }
    //node child with true;
    node* child1 = new node;
    (*child1).f = f;
    (*child1).v = v;
    (*child1).v.insert(f[0][0]);
    if(cleanFormula((*child1).f, (*child1).v, f[0][0])) s.push(child1); else delete child1;

    //node child with false;
    node* child0 = new node;
    (*child0).f = f;
    (*child0).v = v;
    (*child0).v.insert(-f[0][0]);
    if(cleanFormula((*child0).f, (*child0).v, -f[0][0])) s.push(child0); else delete child0;
}

bool dfs(){
    while(!s.empty()){
        node* top = (s.top());
        counter++;
        s.pop();
        (*top).fill();
        (*top).~node();
        if(sat == 1){
            return true;
        }
    }
    return false;
}


int main(){
    vector<vector<int>> originalF;
    cin>>variables>>clauses;
    for(int i=0; i<clauses; i++){
        vector<int> a;
        while(true){
            cin>>temp;
            if(temp == 0){
                break;
            }
            a.push_back(temp);
        }
        originalF.push_back(a);
    }
    auto start = high_resolution_clock::now();
    node *root = new node;
    (*root).f = originalF;
    s.push(root);
    if(!dfs()){
        cout<<"UNSAT\n";
    }
    cout<<"Number of Decompositions = "<<counter<<"\n";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken in "
         << (duration.count()/1000) << " miliseconds" << endl;
    return 0;
}
