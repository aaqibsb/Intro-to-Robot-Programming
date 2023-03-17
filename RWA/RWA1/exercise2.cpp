
#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int main(){
    string user_choice;                                                             //User input
    string temp{};
    bool repeat=0;          

    do{
        std::array <std::array<string, 3>, 3> A{{{"1", "2", "3"},                   //Storing the original array in A 
                                                 {"4", "5", "6"},
                                                 {"7", "8", "9"}}};


        std::vector <string> Dy{};                                                  // String Vector to store positions and give dynamic output for positions available
        std::vector <int> T{};                                                      // Int Vector to store positions in integer       

        //Checking available positions and storing them in Dy
        for (size_t i=0; i<3; i++){
            for (size_t j=0; j<3;j++){
                if (A.at(i).at(j)=="1"){    
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="2"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="3"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="4"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="5"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="6"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="7"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="8"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="9"){ 
                    Dy.push_back(A.at(i).at(j));
                }
            }        
        }

        cout << "\033[2J\033[1;1H";                                                 //clearing the screen
        cout<<"---------------------------------------------\n";
        cout<<"EXERCISE 2\n";
        cout<<"---------------------------------------------\n";

        //Display the array
        for (size_t i=0; i<3; i++){
            for (size_t j=0; j<3;j++){
                if (j==3 || j==6){
                    cout<<"\n";
                }
                cout<<A.at(i).at(j)<<" ";
            }
            cout<<"\n";
        }


        //RED PEGS   
        do{
            cout<<"---------------------------------------------\n";
            cout<<"Do you want to place red pegs (y,n)? ";
            cin>>user_choice;
        }while(user_choice!="y" && user_choice!="n");

        if (user_choice=="n"){
            exit(0);
        }
        
        //Checking if number of elements are equal in A and Dy
        int rows = sizeof(A)/sizeof(A[0]);
        int cols = sizeof(A[0])/sizeof(A[0][0]);
        int m = rows*cols;
        int n = size(Dy);

        if (m==n){
            temp="1-9";
        }else{
            //Loop for giving dynamic output for positions available
            for (size_t i=0;i<size(Dy);i++){
                if (i!=size(Dy)-1){
                    temp+=Dy.at(i)+", ";
                }else{
                    temp+=Dy.at(i);
                }
            }
        }    
        
        bool el_present=0;
        do{
            cout<<"---------------------------------------------\n";
            cout<<"Where to place red pegs "<<"("<<temp<<")? ";
            std::getline(std::cin >> std::ws, user_choice);                     //Getting user inputs in string
            int n = size(user_choice);
            for (int i=0;i<n;i++){
                if(!isspace(user_choice.at(i))){                                //Removing whitespace
                    int a=user_choice.at(i)-48;                                 //Converting each char to int 
                    T.push_back(a);                                             //Storing the positions in T vector
                }
            }


            // Loop for converting Dy vector to integer vector named intNumbers
            int n1 =size(Dy);
            std::vector<int> intNumbers;
            for (int i=0; i<n1; i++)
            {
                int num = atoi(Dy.at(i).c_str());
                intNumbers.push_back(num);
            }

            for (int c : T){
                if (std::find(intNumbers.begin(), intNumbers.end(), c) == intNumbers.end()){    //comparing intNumbers and T
                    el_present=0;
                }else{
                    el_present=1;
                    for (size_t i=0; i<3; i++){                                                 //Loop for inserting the pegs in the array
                        for (size_t j=0; j<3; j++){
                            for (size_t k=0;k<size(T);k++){
                                if (T[k]==1 || T[k]==2 || T[k]==3){
                                    A[0][T[k]-1]="r";
                                }else if(T[k]==4 || T[k]==5 || T[k]==6){
                                    A[1][T[k]-4]="r";
                                }else if(T[k]==7 || T[k]==8 || T[k]==9){
                                    A[2][T[k]-7]="r";
                                }
                            }
                        }
                    } 
                }
            }
        }while(el_present!=1);

        cout<<"---------------------------------------------\n";
        //Display the array
        for (size_t i=0; i<3; i++){
            for (size_t j=0; j<3;j++){
                if (j==3 || j==6){
                    cout<<"\n";
                }
                cout<<A.at(i).at(j)<<" ";
            }
            cout<<"\n";
        }


        //GREEN PEGS
        Dy.clear();
        temp.clear();
        T.clear();

        //Checking available positions and storing them in Dy
        for (size_t i=0; i<3; i++){
            for (size_t j=0; j<3;j++){
                if (A.at(i).at(j)=="1"){    
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="2"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="3"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="4"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="5"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="6"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="7"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="8"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="9"){ 
                    Dy.push_back(A.at(i).at(j));
                }
            }        
        }

        bool green=0;

        //Loop for checking if positions are avaialble or not
        for (size_t i=0; i<3; i++){
            for (size_t j=0; j<3;j++){
                if (A[i][j]=="1" || A[i][j]=="2" || A[i][j]=="3" || A[i][j]=="4" || A[i][j]=="5" || A[i][j]=="6" || A[i][j]=="7" || A[i][j]=="8" || A[i][j]=="9"){
                    green=1;   
                }
            }
        }
        if (green==1){        
            do{
                cout<<"---------------------------------------------\n";
                cout<<"Do you want to place green pegs (y,n)? ";
                cin>>user_choice;
            }while(user_choice!="y" && user_choice!="n");

            if (user_choice=="n"){
                exit(0);
            }
            
            //Checking if number of elements are equal in A and Dy
            int rows = sizeof(A)/sizeof(A[0]);
            int cols = sizeof(A[0])/sizeof(A[0][0]);
            int m = rows*cols;
            int n = size(Dy);

            if (m==n){
                temp="1-9";
            }else{
                //Loop for giving dynamic output for positions available
                for (size_t i=0;i<size(Dy);i++){
                    if (i!=size(Dy)-1){
                        temp+=Dy.at(i)+", ";
                    }else{
                        temp+=Dy.at(i);
                    }
                }
            }    
            
            bool el_present=0;
            do{
                cout<<"---------------------------------------------\n";
                cout<<"Where to place green pegs "<<"("<<temp<<")? ";
                std::getline(std::cin >> std::ws, user_choice);                     //Getting user inputs in string
                int n = size(user_choice);
                for (int i=0;i<n;i++){
                    if(!isspace(user_choice.at(i))){                                //Removing whitespace
                        int a=user_choice.at(i)-48;                                 //Converting each char to int
                        T.push_back(a);                                             //Storing the positions in T vector
                    }
                }

              
                // Loop for converting Dy vector to integer vector named intNumbers
                int n1 =size(Dy);
                std::vector<int> intNumbers;
                for (int i=0; i<n1; i++)
                {
                    int num = atoi(Dy.at(i).c_str());
                    intNumbers.push_back(num);
                }

                for (int c : T){                                                    
                    if (std::find(intNumbers.begin(), intNumbers.end(), c) == intNumbers.end()){      //comparing intNumbers and T
                        el_present=0;
                    }else{
                        el_present=1;
                        for (size_t i=0; i<3; i++){                                                   //Loop for inserting the pegs in the array
                            for (size_t j=0; j<3; j++){
                                for (size_t k=0;k<size(T);k++){
                                    if (T[k]==1 || T[k]==2 || T[k]==3){
                                        A[0][T[k]-1]="g";
                                    }else if(T[k]==4 || T[k]==5 || T[k]==6){
                                        A[1][T[k]-4]="g";
                                    }else if(T[k]==7 || T[k]==8 || T[k]==9){
                                        A[2][T[k]-7]="g";
                                    }
                                }
                            }
                        } 
                    }
                }
            }while(el_present!=1);

            cout<<"---------------------------------------------\n";
            for (size_t i=0; i<3; i++){
                for (size_t j=0; j<3;j++){
                    if (j==3 || j==6){
                        cout<<"\n";
                    }
                    cout<<A.at(i).at(j)<<" ";
                }
                cout<<"\n";
            }
        }

        //BLUE PEGS
        Dy.clear();
        temp.clear();
        T.clear();

        //Checking available positions and storing them in Dy
        for (size_t i=0; i<3; i++){
            for (size_t j=0; j<3;j++){
                if (A.at(i).at(j)=="1"){    
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="2"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="3"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="4"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="5"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="6"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="7"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="8"){ 
                    Dy.push_back(A.at(i).at(j));
                }else if(A.at(i).at(j)=="9"){ 
                    Dy.push_back(A.at(i).at(j));
                }
            }        
        }

        bool blue=0;

        //Loop for checking if positions are avaialble or not
        for (size_t i=0; i<3; i++){
            for (size_t j=0; j<3;j++){
                if (A[i][j]=="1" || A[i][j]=="2" || A[i][j]=="3" || A[i][j]=="4" || A[i][j]=="5" || A[i][j]=="6" || A[i][j]=="7" || A[i][j]=="8" || A[i][j]=="9"){
                    blue=1;   
                }
            }
        }
        if (blue==1){        
            do{
                cout<<"---------------------------------------------\n";
                cout<<"Do you want to place blue pegs (y,n)? ";
                cin>>user_choice;
            }while(user_choice!="y" && user_choice!="n");

            if (user_choice=="n"){
                exit(0);
            }

            //Checking if number of elements are equal in A and Dy
            int rows = sizeof(A)/sizeof(A[0]);
            int cols = sizeof(A[0])/sizeof(A[0][0]);
            int m = rows*cols;
            int n = size(Dy);

            if (m==n){
                temp="1-9";
            }else{
                for (size_t i=0;i<size(Dy);i++){
                    if (i!=size(Dy)-1){
                        temp+=Dy.at(i)+", ";
                    }else{
                        temp+=Dy.at(i);
                    }
                }
            }    
            
            bool el_present=0;
            do{
                cout<<"---------------------------------------------\n";
                cout<<"Where to place blue pegs "<<"("<<temp<<")? ";
                std::getline(std::cin >> std::ws, user_choice);
                int n = size(user_choice);
                for (int i=0;i<n;i++){
                    if(!isspace(user_choice.at(i))){
                        int a=user_choice.at(i)-48;
                        T.push_back(a);
                    }
                }


                // Loop for converting Dy vector to integer vector named intNumbers
                int n1 =size(Dy);
                std::vector<int> intNumbers;
                for (int i=0; i<n1; i++)
                {
                    int num = atoi(Dy.at(i).c_str());
                    intNumbers.push_back(num);
                }

                for (int c : T){
                    if (std::find(intNumbers.begin(), intNumbers.end(), c) == intNumbers.end()){        //comparing intNumbers and 
                        el_present=0;
                    }else{
                        el_present=1;
                        for (size_t i=0; i<3; i++){                                                     //Loop for inserting the pegs in the array
                            for (size_t j=0; j<3; j++){
                                for (size_t k=0;k<size(T);k++){
                                    if (T[k]==1 || T[k]==2 || T[k]==3){
                                        A[0][T[k]-1]="b";
                                    }else if(T[k]==4 || T[k]==5 || T[k]==6){
                                        A[1][T[k]-4]="b";
                                    }else if(T[k]==7 || T[k]==8 || T[k]==9){
                                        A[2][T[k]-7]="b";
                                    }
                                }
                            }
                        } 
                    }
                }
            }while(el_present!=1);

            cout<<"---------------------------------------------\n";
            
            //Display the array
            for (size_t i=0; i<3; i++){
                for (size_t j=0; j<3;j++){
                    if (j==3 || j==6){
                        cout<<"\n";
                    }
                    cout<<A.at(i).at(j)<<" ";
                }
                cout<<"\n";
            }
        }
        
        do{
            cout<<"---------------------------------------------\n";
            cout<<"Try again (y,n)? ";
            cin>>user_choice;
            if (user_choice=="n"){
                repeat=1;
            }else if (user_choice=="y"){
                repeat=0;
            }
        }while(user_choice != "y" && user_choice != "n");
    }while(repeat == 0);
}
