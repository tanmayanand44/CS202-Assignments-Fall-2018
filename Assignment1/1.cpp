#include "sat.h"

int main(){
	int a[9][9];
	char tempChar;
	ifstream fin;
	fin.open("input_sudoku.txt");
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			fin>>tempChar;
			if(tempChar != '.'){
				a[i][j] = tempChar-'0';
			} else{
				a[i][j] = -1;
			}
		}
	}
	fin.close();
	generateSatInput(a);
	if(!solveSat()){
	    cout<<"The input sudoku is unsatisfiable.\n";
		return 0;
	};
	outputSudoku(a);
	for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
	return 0;
}
