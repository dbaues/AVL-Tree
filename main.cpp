#include "tree.h"

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Validates the command line argument number.
**    Function Output: N/A (No return)
**    Side Effects: N/A
*/
void inputValidation(int argc, char **argv){
    string errorString;

    if(argc != 2){
        errorString = "USAGE: ";
        errorString += argv[0]; 
        errorString += " [FILENAME] \nexiting...";
        throw MyException(errorString);
    }
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Main program entrypoint.
**    Function Output: integer return codes.
**    Side Effects: Utilizes functions that do utilize side effects.
*/
int main(int argc, char **argv){
    C_Tree tree;

    try{
        inputValidation(argc, argv);  
        tree.readFile(argv[1]);  
    }
    catch(runtime_error &e){
        string error = "RUNTIME ERROR: ";
        error += e.what();
        cerr << MyException(error).what() << endl; // Colors it Red.
        return 1;
    }
    catch(MyException &e){
        cout << e.what() << endl;
        return 2;
    }
    
    return 0;
}