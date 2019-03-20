//Adam Laviguer
//Section 02
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

//the PERSON struct
struct PERSON{
  char Name[20];
  float Balance;
};

double findN(fstream &inData);
PERSON * readData(int N);
void display(PERSON P[], int N, fstream &inData);
void findRichest(PERSON P[], int N);
void getDeposit(PERSON P[], int N);
void deposit(PERSON P[], int N, string custName, float depositAmount);
void newCopy(fstream &inData, string fileName, PERSON P[], int N);
void printmenu() {
    cout << "Please enter a choice:" << endl;
    cout << "1. Display records"<< endl;
    cout << "2. Deposit funds"<< endl;
    cout << "3. Find Highest Balance" << endl;
    cout << "4. Update records" << endl;
    cout << "5. Exit the program" << endl;
}

int main()
{
    //N will be the number of items in the file
    int N=0;
    fstream inData;   //defining an fstream object named "inData"
    N=findN(inData);  //call the findN function
    PERSON * P;
    P=readData(N);
    int choice;
    do
    {
        printmenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Act on display
                display(P, N, inData);    //call the display function
                break;

            case 2:
                // Act on deposit
                getDeposit(P, N);
                break;

            case 3:
                // Act highest balance
                findRichest(P, N);    //call the findRichest function
                break;

            case 4:
                // Act on update records
                newCopy(inData, "data.txt", P, N);    //call the copy function
                break;

            case 5:
                // Must call update records here before exiting the program
                newCopy(inData, "data.txt", P, N);    //call the copy function
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 5);
      return 0;
}
//the findN function
double findN(fstream &inData){
    string line;
    double N=0;
    //using the open function to open with two args: the txt file and the in flag to read the file
    inData.open("data.txt", ios::in);
    if (!inData){   //check to see if the file is open
      //the file does not exist
      cout<<"ERROR: The file does not exist. Program ending.\n";
      return 0;
    }
    else{
      //the file DOES exist
      cout<<"The file opened successfully.\n";
      //read each line of the file into "line" and increment N until the end of the file
      while (getline(inData, line)){
        ++N;
      }
      cout<<"The number of items in the file has been recorded.\n";
    }
    inData.close();
    return N;
}
PERSON * readData(int N){
    fstream inData;
    inData.open("data.txt", ios::in);
    PERSON * P;
    P=new PERSON[N];    //create the array to hold the data from the file
    string str1, str2;  //read data from the file into the array P of PERSON type
    for (int i=0; i<N;i++){
      inData>>str1>>str2;
      if (str1.length()>9 || str2.length()>10){
          str1.resize(9);
          str2.resize(10);
      }
      inData>>P[i].Balance;
      string sName= str1+" "+str2;
      strcpy(P[i].Name, sName.c_str());
    }
    inData.close();
    return P;
}
//the display function
void display(PERSON P[], int N, fstream &inData){
  //read data from the file into the array P of PERSON type
  cout<<"\n\tName\t\t\tBalance\n   -----------------------------------------\n";
  for (int i=0; i<N;i++){
    cout<<"\t"<<left<<setw(20)<<P[i].Name<<"\t"<<fixed<<setprecision(2)<<P[i].Balance<<endl;
  }
}
//the findRichest function
void findRichest(PERSON P[], int N){
  float highest, lowest;
  int index=0;
  highest = lowest = P[0].Balance;
  for (int j=0; j<N;j++){
    if (P[j].Balance<lowest){
      lowest=P[j].Balance;
    }
    if (P[j].Balance>highest){
      highest=P[j].Balance;
      index=j;
    }
  }
  cout<<"\nThe customer with the largest balance is "<<P[index].Name<<".\n\n";
}
void getDeposit(PERSON P[], int N){
    cout<<"Enter name: ";
    string custName;
    cin.ignore();
    getline(cin, custName);
    for (int i=0; i<N; i++){
      if (strcmp(P[i].Name, custName.c_str())==0){
          cout<<"Amount: ";
          float depositAmount=0;
          cin>>depositAmount;
          cin.ignore();
          deposit(P, N, custName, depositAmount);  //call the deposit function
      }
      else if (strcmp(P[i].Name, custName.c_str())==1){
          cout<<"Record not found\n";
      }
    }
}
//the deposit function
void deposit(PERSON P[], int N, string custName, float depositAmount){
  for (int i=0; i<N; i++){
    if (strcmp(P[i].Name, custName.c_str())==0){
      P[i].Balance += depositAmount;
      cout<<"New balance: "<<P[i].Balance<<".\n";
    }
  }
}
//the newCopy function
void newCopy(fstream &inData, string fileName, PERSON P[], int N){
  //inData<<"\n\n-----------Here are the updated records-----------\n";
  inData.open("data.txt", ios::out);
  for (int i=0; i<N; i++){
    inData<<P[i].Name<< " "<<P[i].Balance<<"\n";
  }
  cout<<"File updated..."<<endl;
  //close the file
  inData.close();
}
