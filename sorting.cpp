//sorting
#include<iostream>
using namespace std;

bool isSorted(int *a){
	for(int i=0; i<9;i++){
		if (*(a+i)>*(a+i+1)) return false;
	}
	return true;
}//checks the order of the array


int main(){
	//declaring the variables
	int numbers[10]={0};
	
	//setup the array
	for (int i=0; i<10; i++){
		cout<<"Enter number"<<i+1<<":";
		cin>>numbers[i];
	}
	
	//display the contents of the array
	cout<<"Your array is: {";
	for (int i=0; i<10; i++){
		if(i==9) cout<<numbers[i]<<"}"<<endl;
		else cout<<numbers[i]<<", ";
	}
	
	//BubbleSort
	int temp=0;
	while(isSorted(&numbers[0])==false){
		for(int i=0; i<9; i++){
			if(numbers[i]>numbers[i+1]){
				temp=numbers[i];
				numbers[i]=numbers[i+1];
				numbers[i+1]=temp;
			}
		}
		cout<<"Now Sorting: {";
		for (int i=0; i<10; i++){
			if(i==9) cout<<numbers[i]<<"}"<<endl;
			else cout<<numbers[i]<<", ";
		}
	}
	
	
	return 0;
}
