#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <string.h>
using namespace std;

const int MAX_CHAR = 50;

struct cereal{
    char name[MAX_CHAR];
    double caleries;
    double GramsOfFat;
    double GramsOfSodium;
    double GramsOfFiber;
    double GramsOfCarbohydrate;
    double GramsOfSugar;
    double CupsPerServing;
    int arrLen;
    cereal();    
};

cereal::cereal(){

    strcpy(name, "default name");
    caleries = 0;
    GramsOfFat = 0;
    GramsOfSodium = 0;
    GramsOfFiber = 0;
    GramsOfCarbohydrate = 0;
    GramsOfSugar = 0;
    CupsPerServing = 0;
    arrLen = 0;
    
};

void readCerealData(ifstream &cerealFile, int start, int end, cereal Cerealz[999]);
void printcereal(cereal Cerealz[999], int start, int end);
void resetCereal(cereal Cerealz[999], int index);

void addCereal(cereal Cerealz[999]);
void removeCereal(cereal Cerealz[999]);
void searchBySugar(cereal Cerealz[999]);
void reload(cereal Cerealz[999]);
void printArrayToFile(const char fileName[], cereal Cerealz[]);



int readInt(const char prompt[]);
double readDouble(const char prompt[]);


//Main is kindoff also my menu
//Main initialized all of my variables and gives you the menu loop
int main() {
    ifstream cerealFile("cereal.txt");
    cereal Cerealz[999];

    //menu things
        
    bool loaded = false;
    int choice;
    
    while(1 == 1){
        
    cout << "Load/Reload Data: 1" << endl;  
    cout << "Print Data: 2" << endl;
    cout << "Remove Data: 3" << endl;
    cout << "Add Data: 4" << endl;
    cout << "Output Data: 5" << endl;
    cout << "Search By Sugar: 6" << endl;
    cout << "Quit: 7" << endl << endl;

    choice = readInt("");  

        if(choice == 1){
            if(loaded == false){
                    readCerealData(cerealFile, 0, 999, Cerealz);
            }else{
                reload(Cerealz); 
                readCerealData(cerealFile, 0, 200);
                }
        }
        
        if(choice == 2){

            printcereal(Cerealz, 0, 999);

        }
        
        if(choice == 3){

            removeCereal(Cerealz);

        }
        
        if(choice == 4){

            addCereal(Cerealz);

        }
        
        if(choice == 5){

            cout << "Enter the name of the File: ";
            char fileName[10];
            cin >> fileName;

            printArrayToFile(fileName, Cerealz);
            
        }
        
        if(choice == 6){
        
            searchBySugar(Cerealz);

        }

        if(choice == 7){

            break;

        }


    }


    return 0;
}


//Output cereal saves all of the info to a file
void printArrayToFile(const char fileName[10], cereal Cerealz[]) {
    ofstream outFile(fileName);
    for (int index = 0; index < Cerealz[0].arrLen; index++) {

            outFile << Cerealz[index].name << ";";
            outFile << Cerealz[index].caleries << ";";
            outFile << Cerealz[index].GramsOfFat << ";";
            outFile << Cerealz[index].GramsOfSodium << ";";
            outFile << Cerealz[index].GramsOfCarbohydrate << ";";
            outFile << Cerealz[index].GramsOfSugar << ";";
            outFile << Cerealz[index].CupsPerServing << ";";
        
    }
}



//reload deletes and reloads my cereal varaible
void reload(cereal Cerealz[999]){

    cereal Default;
    int size = Cerealz[0].arrLen + 5;
    for(int index = 0; index < size; index++){
        Cerealz[index] = Default;
    }
    
    
}

//search by sugar asks for a low and high value and then searches and finds all cereals with a value between those
void searchBySugar(cereal Cerealz[999]){

    double low = readDouble("Input lowest sugar(g) value: ");
    double high = readDouble("Input highest sugar(g) value: ");
    
    for(int index = 0; index < Cerealz[0].arrLen; index++){
        if(Cerealz[index].GramsOfSugar >= low && Cerealz[index].GramsOfSugar <= high){
            cout << Cerealz[index].name << ";";
            cout << Cerealz[index].caleries << ";";
            cout << Cerealz[index].GramsOfFat << ";";
            cout << Cerealz[index].GramsOfSodium << ";";
            cout << Cerealz[index].GramsOfCarbohydrate << ";";
            cout << Cerealz[index].GramsOfSugar << ";";
            cout << Cerealz[index].CupsPerServing << ";";
        }
    }
    
}

//remove Cereal gets rid of a cereal and then moves all of the other cereal down to fit its spot and shrinks the array size
void removeCereal(cereal Cerealz[999]){
    
    int removalPoint = readInt("Index to be removed: ");

    for(int index = removalPoint - 1; index < Cerealz[0].arrLen; index++){
        Cerealz[index] = Cerealz[index + 1];
    }
    cereal defaultCereal;
    Cerealz[Cerealz[0].arrLen - 1] = defaultCereal;

    Cerealz[0].arrLen -= 1;
    
}

void addCereal(cereal Cerealz[999]){

    int id = Cerealz[0].arrLen + 1;
    Cerealz[0].arrLen += 1;

    cout << "Please enter a name: ";
    cin >> Cerealz[id].name;
    Cerealz[id].caleries = readDouble("Please Enter Caleries: ");
    Cerealz[id].GramsOfFat = readDouble("Please Enter Grams Of Fat: ");
    Cerealz[id].GramsOfSodium = readDouble("Please Enter Grams Of Sodium: ");
    Cerealz[id].GramsOfFiber = readDouble("Please Enter Grams Of Fiber: ");
    Cerealz[id].GramsOfCarbohydrate = readDouble("Please Enter Grams Of Carbohydrate: ");
    Cerealz[id].GramsOfSugar = readDouble("Please Enter Grams Of Sugar: ");
    Cerealz[id].CupsPerServing = readDouble("Please Enter Cups Per Serving: ");

}

int readInt(const char prompt[]){
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}
double readDouble(const char prompt[]){
    double temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}

void resetCereal(cereal Cerealz[999], int index){
    cereal Default;
    Cerealz[index] = Default;
}

void printcereal(cereal Cerealz[999], int start, int end){

    for(int index = start; index < end && index < Cerealz[0].arrLen; index++){

        cout << Cerealz[index].name << ";";
        cout << Cerealz[index].caleries << ";";
        cout << Cerealz[index].GramsOfFat << ";";
        cout << Cerealz[index].GramsOfSodium << ";";
        cout << Cerealz[index].GramsOfCarbohydrate << ";";
        cout << Cerealz[index].GramsOfSugar << ";";
        cout << Cerealz[index].CupsPerServing << ";";
        
    }
}

void readCerealData(ifstream &cerealFile, int start, int end, cereal Cerealz[999]){

    //just reads and puts each variable into the right spot
    for(int index = start; index < end; index++){

        cerealFile.get(Cerealz[index].name, 100, ';');
        cerealFile.ignore(100, ';'); 
        cerealFile >> Cerealz[index].caleries;
        cerealFile.ignore(100, ';');
        cerealFile >> Cerealz[index].GramsOfFat;
        cerealFile.ignore(100, ';');
        cerealFile >> Cerealz[index].GramsOfSodium;
        cerealFile.ignore(100, ';');
        cerealFile >> Cerealz[index].GramsOfFiber;
        cerealFile.ignore(100, ';');
        cerealFile >> Cerealz[index].GramsOfCarbohydrate;
        cerealFile.ignore(100, ';');
        cerealFile >> Cerealz[index].GramsOfSugar;
        cerealFile.ignore(100, ';');
        cerealFile >> Cerealz[index].CupsPerServing;
        cerealFile.ignore(100, ';');

        if(Cerealz[index].caleries != 0){
            Cerealz[0].arrLen += 1;
        }
        
    }
}

