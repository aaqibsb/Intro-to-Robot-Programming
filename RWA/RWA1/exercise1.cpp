#include <iostream>
#include <string.h>

using namespace std;

int main(){
    //object
    const string cube="c";
    const string ball="b";
    const string peg="p";
    
    //grippers
    const string suction_gripper="s";
    const string finger_gripper="f";
    
    //tables
    const string red_table="r";
    const string green_table="g";
    const string blue_table="b";

    //variables to store values
    string object{};
    string gripper{};
    string table{};
    string user_choice{};
    string object_choice{};
    string gripper_choice{};
    string table_choice{};

    bool repeat=0;

    do{
        object.clear();
        gripper.clear();
        table.clear();
        user_choice.clear();
        object_choice.clear();
        gripper_choice.clear();
        table_choice.clear();

        cout << "\033[2J\033[1;1H";                         //clearing the screen
        cout<<"-----------------------------------\n";
        cout<<"EXERCISE 1\n";
        

        do{ 
            cout<<"-----------------------------------\n";
            cout<<"Which part to pick up (c, b, p)? ";
            std::getline(std::cin >> std::ws,object);
            if (object.length()>1){
                object="x";
            }else if(object==cube){
                object_choice="cube";
            }else if(object==ball){
                object_choice="ball";
            }else if(object==peg){
                object_choice="peg";
            }
        }while(object != cube && object != ball && object != peg);

            
        do{ 
            cout<<"-----------------------------------\n";
            cout<<"Which gripper to use (s, f)? ";
            std::getline(cin,gripper);
            if (gripper.length()>1){
                gripper="x";
            }else if(gripper==finger_gripper){
                gripper_choice="finger gripper";
            }else if(gripper==suction_gripper){
                gripper_choice="suction gripper";
            }
        }while(gripper != finger_gripper && gripper != suction_gripper);
        
        //using switch case
        switch(object[0]){
            //cube
            case 'c':
            {
                if (object==cube && gripper==finger_gripper){
                    do{
                        cout<<"-----------------------------------\n";
                        cout<<"Which table to use (r, g, b)? ";
                        std::getline(cin,table);
                        if (table.length()>1){
                            table="x";
                        }else if(table==red_table){
                            table_choice="red table";
                        }else if(table==blue_table){
                            table_choice="blue table";
                        }else if(table==green_table){
                            table_choice="green table";
                        }
                    }while(table != red_table && table != blue_table && table != green_table);
                    
                    cout<<"-----------------------------------\n";
                    if(table==red_table){
                        cout<<"Success: The cube was placed on the red table\n";
                        break;
                    }
                    else{
                        cout<<"Failure: Cannot place the "<<object_choice<<" on the "<<table_choice<<"\n";
                        break;
                    }
                }else{
                    cout<<"-----------------------------------\n";
                    cout<<"Failure: Cannot pick up the "<<object_choice<<" with the "<<gripper_choice<<"\n";
                    break;
                }
            }

            //ball
            case 'b':
            {
                if (object==ball && gripper==suction_gripper){
                    do{
                        cout<<"-----------------------------------\n";
                        cout<<"Which table to use (r, g, b)? ";
                        std::getline(cin,table);
                        if (table.length()>1){
                            table="x";
                        }else if(table==red_table){
                            table_choice="red table";
                        }else if(table==blue_table){
                            table_choice="blue table";
                        }else if(table==green_table){
                            table_choice="green table";
                        }
                    }while(table != red_table && table != blue_table && table != green_table);
                    
                    cout<<"-----------------------------------\n";
                    if(table==green_table){
                        cout<<"Success: The ball was placed on the green table\n";
                        break;
                    }
                    else{
                        cout<<"Failure: Cannot place the "<<object_choice<<" on the "<<table_choice<<"\n";
                        break;
                    }
                }else{
                    cout<<"-----------------------------------\n";
                    cout<<"Failure: Cannot pick up the "<<object_choice<<" with the "<<gripper_choice<<"\n";
                    break;
                }
            }

            //peg
            case 'p':
            {
                if (object==peg && gripper==finger_gripper){
                    do{
                        cout<<"-----------------------------------\n";
                        cout<<"Which table to use (r, g, b)? ";
                        std::getline(cin,table);
                        if (table.length()>1){
                            table="x";
                        }else if(table==red_table){
                            table_choice="red table";
                        }else if(table==blue_table){
                            table_choice="blue table";
                        }else if(table==green_table){
                            table_choice="green table";
                        }
                    }while(table != red_table && table != blue_table && table != green_table);
                    
                    cout<<"-----------------------------------\n";
                    if(table==blue_table){
                        cout<<"Success: The peg was placed on the blue table\n";
                        break;
                    }
                    else{
                        cout<<"Failure: Cannot place the "<<object_choice<<" on the "<<table_choice<<"\n";
                        break;
                    }
                }else{
                    cout<<"-----------------------------------\n";
                    cout<<"Failure: Cannot pick up the "<<object_choice<<" with the "<<gripper_choice<<"\n";
                    break;
                }
            }            
        }

        
        do{
            cout<<"-----------------------------------\n";
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
  
