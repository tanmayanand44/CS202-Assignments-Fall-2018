#include<bits/stdc++.h>
using namespace std;

//Takes a partially filled sudoku and generates the output to be fed to minisat.
void generateSatInput(int a[9][9]) {
    set<int> given;
    ofstream fout;
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(a[i-1][j-1] > 0){
                given.insert((a[i-1][j-1]-1)*81 + 9*(i-1) + j);
            }
        }
    }
    fout.open("input_minisat.txt");
    fout<<"p cnf 729 "<<6417+given.size()<<"\n";
    for(set<int>::iterator i=given.begin(); i!=given.end(); i++){
        fout<<*i<<" 0\n";
    }
    //Each box should have one number only.
    for(int r=1;r<=9;r++){
        for(int c=1;c<=9;c++)
        {
            for(int i=1;i<=9;i++)
                fout<<81*(i-1)+9*(r-1)+c<<" ";
            fout<<"0\n";
            for(int i=1;i<=9;i++)
            {
                for(int j=i+1;j<=9;j++)
                    fout<<(-(81*(i-1)+9*(r-1)+c))<<" "<<(-(81*(j-1)+9*(r-1)+c))<<" 0\n";
            }
        }
    }
    for(int i=1;i<=9;i++)//each number from 1 to 9
    {
        for(int r=1;r<=9;r++)//each row should have only one number
            for(int j=1;j<=9;j++)//one row element
                for(int k=j+1;k<=9;k++)//second row
                    fout<<(-(81*(i-1)+9*(r-1)+j))<<" "<<(-(81*(i-1)+9*(r-1)+k))<<" "<<"0"<<"\n";
        for(int c=1;c<=9;c++)//each column should have only one number
            for(int j=1;j<=9;j++)//one row element
                for(int k=j+1;k<=9;k++)//second row
                    fout<<(-(81*(i-1)+9*(j-1)+c))<<" "<<(-(81*(i-1)+9*(k-1)+c))<<" "<<"0"<<"\n";
        for(int e=1;e<=9;e++)//each number must be present in one row
        {
            for(int f=1;f<=9;f++)
                fout<<(81*(i-1)+9*(e-1)+f)<<" ";
            fout<<"0"<<"\n";
        }
        for(int e=1;e<=9;e++)//each number must be present in one column
        {
            for(int f=1;f<=9;f++)
                fout<<(81*(i-1)+9*(f-1)+e)<<" ";
            fout<<"0"<<"\n";
        }
        for(int f=1;f<=9;f++)
            fout<<(81*(i-1)+9*(f-1)+f)<<" ";
        fout<<"0"<<"\n";
        for(int f=1;f<=9;f++)
            fout<<(81*(i-1)+10-f+9*(f-1))<<" ";
        fout<<"0"<<"\n";
        for(int p=1;p<=7;p=p+3)//box encoding
            for(int q=1;q<=7;q=q+3)
            {
                for(int r=0;r<=2;r++)
                    for(int s=0;s<=2;s++)
                        for(int t=0;t<=2;t++)
                            for(int u=0;s<=2;s++)
                                if(u!=s&&t!=r)
                                    fout<<(-(81*(i-1)+9*(q+s-1)+p+r))<<" "<<(-(81*(i-1)+9*(q+u-1)+p+t))<<" 0\n";
                for(int r=0;r<=2;r+=1)
                    for(int s=0;s<=2;s+=1)
                        fout<<(81*(i-1)+9*(q+s-1)+r+p)<<" ";
                fout<<"0\n";
            }
    }
    fout.close();
}

// Runs the minisat executable and returns satisfiability.
bool solveSat(){
    system("minisat -rnd-init -rnd-seed=$(date +%s) input_minisat.txt output_minisat.txt 1> /dev/null 2> /dev/null");
    ifstream fin;
    fin.open("output_minisat.txt");
    string satisfiable;
    fin>>satisfiable;
    fin.close();
    if(satisfiable == "SAT"){
        return true;
    }

    return false;
}

// Takes a input matrix and fills it with the output of the minisat.
bool outputSudoku(int a[9][9]){
	ifstream fin;
    fin.open("output_minisat.txt");
    int t;
    string satisfiable;
    fin>>satisfiable;
    if(satisfiable == "UNSAT") {
        return false;
    }
    for(int i=0;i<729;i++){
        fin>>t;
        t--;
        if(t>=0){
            int d1=t/81+1;
            int pos=t%81;
            int r=pos/9;
            int c=pos%9;
            a[r][c]=d1;
        }
    }
    fin.close();
    return true;

}

// Takes a partially filled sudoku and checks if the sudoku has a unique solution
bool hasUnique(int A[9][9]){
    generateSatInput(A);
	if(!solveSat())
		 return false;
	int B[9][9];
	outputSudoku(B);
	ofstream fout;
	fout.open("input_minisat.txt",ios_base::app);
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			fout<<-(81*(B[i][j]-1)+9*(i)+j+1)<<" ";
		}
	}
    fout<<"0 \n";
	fout.close();
    if(solveSat()){
        return false;
    }
    return true;
}
