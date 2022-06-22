#include "tree.h"

// Configures/toggles basic debugging data.
const bool DEBUG_ENABLED = false;
const bool INSERT_STEPPING = false;
const bool DELETE_STEPPING = false;

// Constructor/Destructor Set.
/*
**    Author: Dan Bauer
**    Function Purpose:
**        Constructor for Tree object.
**    Function Output: N/A (Constructor)
**    Side Effects: Sets private variables root, tmp_array, and tmp_index to
**        to base values of NULL, NULL, and 0 respectively.
*/
C_Tree::C_Tree(){
    this->p_root = NULL;
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Destructor of Tree object.
**    Function Output: N/A (Constructor)
**    Side Effects: Deletes the tree, tmp_array, and sets tmp_index t0 0.
*/
C_Tree::~C_Tree(){
    this->deleteTree();
}


// Insert Method Set.
/*
**    Author: Dan Bauer
**    Function Purpose:
**        Inserts a value into the tree.
**    Function Output: N/A (No return)
**    Side Effects: Modifies the internal data structure.
*/
void C_Tree::insertValue(int val){
    if(this->p_root == NULL)
        this->p_createTree(val);
    else if(this->findNode(val) != NULL)
        throw MyException("Value already in the tree.");
    else{
        this->p_insertValue(this->p_root, val);
        if(INSERT_STEPPING){ this->debug(DEBUG_ENABLED); }
    }
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Inserts a value into the proper location in the Tree.
**    Function Output: N/A (No return)
**    Side Effects: Modifies aspects of the internal data structure.
*/
void C_Tree::p_insertValue(S_NODE* node, int value){
    if(value < node->value){
        if(node->left == NULL){
            node->left = this->p_createNode(node, value);
            this->p_updateHeights(node, node->left);
        }
        else{ this->p_insertValue(node->left, value); }
    }
    else if(value > node->value){
        if(node->right == NULL){
            node->right = this->p_createNode(node, value);
            this->p_updateHeights(node, node->right);
        }
        else{ this->p_insertValue(node->right, value); }
    }
    else{ throw MyException("This value is already in the tree."); }
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Creates a Node to place into the tree.
**    Function Output: S_NODE pointer to the created node.
**    Side Effects: N/A
*/
S_NODE* C_Tree::p_createNode(S_NODE* parent, int val){
    S_NODE *tmp = (S_NODE*)malloc(sizeof(S_NODE));

    tmp->value = val;
    tmp->parent = parent;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->lheight = 0;
    tmp->rheight = 0;

    return tmp;
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Creates the first node in the tree.
**    Function Output: N/A (No return)
**    Side Effects: Sets the root value to the first node.
*/
void C_Tree::p_createTree(int value){
    if(this->p_root != NULL)
        throw MyException("Tree already created.");
    else
        this->p_root = this->p_createNode(NULL, value);
}


// Update Height Method.
/*
**    Author: Dan Bauer
**    Function Purpose:
**        Updates the heights going up towards the root.
**    Function Output: N/A (No return)
**    Side Effects: Modifies nodes within the internal data structure.
*/
void C_Tree::p_updateHeights(S_NODE* node, S_NODE* from, bool inserting){
    int difference, caseCode;

    // Increments/Decrements left side height.
    if(node->left == from){
        (inserting) ? node->lheight++ : node->lheight--;
        difference = abs(node->rheight - node->lheight);

        // Check for problem and address it.
        if(difference > 1){ caseCode = this->p_balance(node); }

        // Continue up the tree.
        if(node != this->p_root){
            if(inserting && node->lheight > node->rheight)
                this->p_updateHeights(node->parent, node);
            else if(!inserting && node->lheight >= node->rheight){
                if(caseCode == 2 || caseCode == 4){
                    // Jumps to prevent a double decrement.
                    if(node->parent != this->p_root)
                        this->p_updateHeights(node->parent->parent, node->parent, inserting);
                }
                else{ this->p_updateHeights(node->parent, node, inserting); }
            }
        }
    }
    // Increments/Decrements right side height.
    else if(node->right == from){
        (inserting) ? node->rheight++ : node->rheight--;
        difference = abs(node->rheight - node->lheight);

        // Check for problem and address it.
        if(difference > 1){ caseCode = this->p_balance(node); }

        // Continue up the tree.
        if(node != this->p_root){
            if(inserting && node->rheight > node->lheight)
                this->p_updateHeights(node->parent, node);
            else if(!inserting && node->rheight >= node->lheight){
                if(caseCode == 1 || caseCode == 3){
                    // Jumps to prevent a double decrement.
                    if(node->parent != this->p_root)
                        this->p_updateHeights(node->parent->parent, node->parent, inserting);
                }
                else{ this->p_updateHeights(node->parent, node, inserting); }
            }
        }
    }
    else{ throw MyException("Pointer error. Invalid \"from\" pointer."); }
}


// Balancing Method Set.
/*
**    Author: Dan Bauer
**    Function Purpose:
**        Self balances the tree as nodes are inserted based on heights.
**    Function Output: Integer code based on specific case execution.
**    Side Effects: Modifies the internal data structure.
**
**    =================================================
**    Case 1:   |   Case 2:   |   Case 3:   |   Case 4:
**       A      |      A      |       A     |    A
**      /       |       \     |      /      |     \
**     B        |        B    |     B       |      B
**      \       |       /     |    /        |       \
**       C      |      C      |   C         |        C
**    =================================================
*/
int C_Tree::p_balance(S_NODE* node){
    S_NODE* parent; // Used for the "Parent" node.

    if(node->lheight > node->rheight){
        parent = node->left;
        // Case 1.
        if(parent->rheight > parent->lheight){
            this->p_case1(node);
            return 1;
        }
        // Case 3.
        else if(parent->lheight >= parent->rheight){
            this->p_case3(node);
            return 3;
        }
    }
    else if(node->rheight > node->lheight){
        parent = node->right;
        // Case 2.
        if(parent->lheight > parent->rheight){
            this->p_case2(node);
            return 2;
        }
        // Case 4.
        else if(parent->rheight >= parent->lheight){
            this->p_case4(node);
            return 4;
        }
    }
    return 0;
}

/*
**    Author: Dan Bauer                                         |   A   |
**    Function Purpose:                                         |  /    |
**        Performs the proper rotations for case 1 of AVL       | B     |
**    Function Output: N/A (No return)                          |  \    |
**    Side Effects: Modifies the internal data structure.       |   C   |
*/
void C_Tree::p_case1(S_NODE* node){
    if(DEBUG_ENABLED){ cout << "Case 1" << endl; }
    // Rotate Left on parent.
    this->p_rotateLeft(node->left);
    // Rotate Right on Grandparent.
    this->p_rotateRight(node);
}

/*
**    Author: Dan Bauer                                         |   A   |
**    Function Purpose:                                         |    \  |
**        Performs the proper rotations for case 2 of AVL       |     B |
**    Function Output: N/A (No return)                          |    /  |
**    Side Effects: Modifies the internal data structure.       |   C   |
*/
void C_Tree::p_case2(S_NODE* node){
    if(DEBUG_ENABLED){ cout << "Case 2" << endl; }
    // Rotate right on Parent.
    this->p_rotateRight(node->right);
    // Rotate Left on Grandparent.
    this->p_rotateLeft(node);
}

/*
**    Author: Dan Bauer                                         |     A |
**    Function Purpose:                                         |    /  |
**        Performs the proper rotations for case 1 of AVL       |   B   |
**    Function Output: N/A (No return)                          |  /    |
**    Side Effects: Modifies the internal data structure.       | C     |
*/
void C_Tree::p_case3(S_NODE* node){
    if(DEBUG_ENABLED){ cout << "Case 3" << endl; }
    // Rotate right on Grandparent.
    this->p_rotateRight(node);
}

/*
**    Author: Dan Bauer                                         | A     |
**    Function Purpose:                                         |  \    |
**        Performs the proper rotations for case 4 of AVL       |   B   |
**    Function Output: N/A (No return)                          |    \  |
**    Side Effects: Modifies the internal data structure.       |     C |
*/
void C_Tree::p_case4(S_NODE* node){
    if(DEBUG_ENABLED){ cout << "Case 4" << endl; }
    // Rotate left on Grandparent.
    this->p_rotateLeft(node);
}


// Print Method Set.
/*
**    Author: Dan Bauer
**    Function Purpose:
**        Prints out the values of the data structure.
**    Function Output: N/A (No return)
**    Side Effects: Calls private print that utilizes IO
*/
void C_Tree::print(bool formatted){
    if(this->p_root == NULL)
        throw MyException("Tree does not exist. Cannot Print.");
    else{
        // Utilizes formatted print when not specified otherwise.
        if(formatted)
            this->p_formattedPrint(this->p_root);
        else
            this->p_printInOrder(this->p_root);
    }
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Prints out the contents of the tree In-order.
**    Function Output: N/A (No return)
**    Side Effects: Utilizes IO functions.
*/
void C_Tree::p_printInOrder(S_NODE* node){
    if(node->left != NULL)
        this->p_printInOrder(node->left);
    cout << node->value << " ";
    if(node->right != NULL)
        this->p_printInOrder(node->right);
}

/*
**    Author: Alex Wollman, Dan Bauer
**    Function Purpose:
**        Prints out the tree formatted left to right.
**    Function Output: N/A (No return)
**    Side Effects: Utilizes I/O functions.
*/
void C_Tree::p_formattedPrint(S_NODE *node, int indent){
    if(node == NULL){ return; }
    else{
        this->p_formattedPrint(node->left, indent+4);
        if( indent )
            cout << setw(indent) << " ";

        // Colors the heights yellow.
        char buffer[50];
        sprintf(buffer, " \033[1;33m[%d:%d]\033[0m", node->lheight, node->rheight);

        // Highlights height imbalances when debugging is enabled.
        char buffer_2[50] = "";
        if(DEBUG_ENABLED){
            int difference = abs(node->lheight - node->rheight);

            // Colors differences greater than 1 red.
            if(difference < 2){ sprintf(buffer_2, " %d", difference); }
            else{ sprintf(buffer_2, " \033[1;31m%d\033[0m", difference); }
        }

        cout << node->value << buffer << buffer_2 << endl;
        this->p_formattedPrint(node->right, indent+4);
    }
}


// Delete Method Set.
/*
**    Author: Dan Bauer
**    Function Purpose:
**        Removes a value from the [Data structure]
**    Function Output: N/A (No return)
**    Side Effects: Calls private remove which uses side effects.
*/
void C_Tree::deleteNode(int value){
    if(this->p_root == NULL)
        throw MyException("Tree does not exist. Cannot remove value.");
    else if(this->findNode(value) == NULL)
        throw MyException("Cannot remove value that does not exist.");
    else{
        this->p_deleteNode(this->findNode(value), value);
        if(DELETE_STEPPING){ this->debug(DEBUG_ENABLED); }
    }
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Removes the specified value from the tree.
**    Function Output: N/A (No return)
**    Side Effects: Modifies the internal private data structure.
*/
void C_Tree::p_deleteNode(S_NODE* node, int value){
    if(DEBUG_ENABLED){ cout << "Delete " << value << " Node" << endl; }

    if(node->value == value){
        // Deletion Case.
        if(node->left == NULL && node->right == NULL){
            if(DEBUG_ENABLED){ cout << "Deletion time\n"; }

            // Sets parent's respective pointer to NULL.
            S_NODE* parent = node->parent;
            if(parent != NULL){
                if(parent->right == node){
                    this->p_updateHeights(parent, parent->right, false);
                    parent->right = NULL;
                }
                else if(parent->left == node){
                    this->p_updateHeights(parent, parent->left, false);
                    parent->left = NULL;
                }
                else{ throw MyException("Floating pointer?"); }
            }
            delete node;
        }
        // Predecessor Case.
        else if(node->right == NULL){
            if(DEBUG_ENABLED && DELETE_STEPPING){ cout << "Finding predecessor\n"; }

            // Replaces the node value with in-order predecessor.
            S_NODE* predecessor = this->p_findPredecessor(node->left);
            node->value = predecessor->value;
            this->p_deleteNode(predecessor, predecessor->value);
        }
        // Successor Case.
        else{
            if(DEBUG_ENABLED && DELETE_STEPPING){ cout << "Finding successor\n"; }

            // Replaces the node value with in-order successor.
            S_NODE* successor = this->p_findSuccessor(node->right);
            node->value = successor->value;
            this->p_deleteNode(successor, successor->value);
        }
    }
    // Traverses for proper node.
    else if(node->value < value){ this->p_deleteNode(node->left, value); }
    else if(node->value > value){ this->p_deleteNode(node->right, value); }
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Deletes the contents of the tree.
**    Function Output: N/A (No return)
**    Side Effects: Calls private deleteTree that utilizes side effects.
*/
void C_Tree::deleteTree(){
    if(this->p_root != NULL)
        this->p_deleteTree(this->p_root);
    else{ return; } // Not worth killing execution.
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Deletes the tree and all of its contents.
**    Function Output: N/A (No return)
**    Side Effects: Deletes the internal data structure.
*/
void C_Tree::p_deleteTree(S_NODE* node){
    if(node->left != NULL)
        this->p_deleteTree(node->left);
    if(node->right != NULL)
        this->p_deleteTree(node->right);
    delete(node);
    if(node == this->p_root){ this->p_root = NULL; }
}


// Find Node Method Set.
/*
**    Author: Dan Bauer
**    Function Purpose:
**        Searches to see if a node exists.
**    Function Output: S_NODE pointer to the node of specified value. NULL if not found.
**    Side Effects: N/A
*/
S_NODE* C_Tree::findNode(int target){
    if(this->p_root == NULL)
        throw MyException("Tree does not exist. Cannot find node.");
    else
        return this->p_findNode(this->p_root, target);
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Traverses the tree to find a node of specified value.
**    Function Output: S_NODE pointer to a node of specified value. NULL if none is found.
**    Side Effects: N/A
*/
S_NODE* C_Tree::p_findNode(S_NODE* node, int target){
    S_NODE* retval = NULL;
    if(target == node->value){ retval = node; }
    else if(target > node->value){
        if(node->right != NULL)
            retval = this->p_findNode(node->right, target);
    }
    else if(target < node->value){
        if(node->left != NULL)
            retval = this->p_findNode(node->left, target);
    }
    return retval;
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Finds the in-order predecessor of the specified node.
**    Function Output: Pointer to the in-order predecessor node.
**    Side Effects: N/A
*/
S_NODE* C_Tree::p_findPredecessor(S_NODE* node){
    if(node->right == NULL){ return node; }
    else{ return this->p_findPredecessor(node->right); }
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Finds the in-order successor of the specified node.
**    Function Output: Pointer to the in-order successor node.
**    Side Effects: N/A
*/
S_NODE* C_Tree::p_findSuccessor(S_NODE* node){
    if(node->left == NULL){return node; }
    else{ return this->p_findSuccessor(node->left); }
}


// Get Height Method Set.
/*
**    Author: Dan Bauer
**    Function Purpose:
**        Finds the max height of the Tree.
**    Function Output: The height of the deepest branch.
**    Side Effects: N/A
*/
int C_Tree::getTreeHeight(){
    if(this->p_root == NULL){ return 0; }
    else{ return this->getHeight(this->p_root); }
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Gets the height of a specified node.
**    Function Output: The height of the deepest branch from specified node.
**    Side Effects: N/A
*/
int C_Tree::getHeight(S_NODE* node){
    if(this->p_root == NULL)
        throw MyException("Tree has not been created.");
    else
        return this->p_getHeight(node);
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Traverses the tree to get max height.
**    Function Output: The height from the specified node.
**    Side Effects: N/A
*/
int C_Tree::p_getHeight(S_NODE* node){
    if(node == NULL){ return 0; }

    int lHeight=1, rHeight=1;
    lHeight += this->p_getHeight(node->left);
    rHeight += this->p_getHeight(node->right);

    return (lHeight > rHeight) ? lHeight : rHeight;
}


// Read File Method Set.
/*
**    Author: Dan Bauer
**    Function Purpose:
**        Checks if a file exists and then reads through the specified file.
**    Function Output: N/A (No return)
**    Side Effects: Calls private readFile that utilizes side effects.
*/
void C_Tree::readFile(char* fileName){
    struct stat fileInfo;
    string errorString;

    // Performs basic input validation.
    int error = stat(fileName, &fileInfo);
    if(error != 0){
        errorString = strerror(errno);
        errorString += ": ";
        errorString += fileName;
        throw runtime_error(errorString);
    }
    else if(fileInfo.st_size == 0){
        errorString = "File is empty: ";
        errorString += fileName;
        throw runtime_error(errorString);
    }
    else{ this->p_readFile(fileName); }
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Reads through the file and then executes the commands specified by the file.
**    Function Output: N/A (No return)
**    Side Effects: Calls essentially every class function that utilizes side effects.
*/
void C_Tree::p_readFile(char* fileName){
    fstream file;
    int cmd, num;
    bool ended = false;

    file.open(fileName);
    while(file >> cmd && !ended){
        switch(cmd){
            case 0: // Inserts the following value.
                if(file >> num){ this->insertValue(num); }
                else{ throw MyException("Unexpected End-of-file."); }
                break;
            case 1: // Removes the following value.
                if(file >> num){ this->deleteNode(num); }
                else{ throw MyException("Unexpected End-of-file."); }
                break;
            case 2: // Prints the current AVL Tree.
                cout << "\033[1;30m<><><><><><><PRINT TREE><><><><><><>\033[0m" << endl;
                this->print();
                cout << "\033[1;30m<><><><><><><><><><><><><><><><><><>\033[0m" << endl;
                break;
            case 8: // Deletes the current AVL Tree.
                this->deleteTree();
                break;
            case 9: // Quits
                ended = this->p_stop();
                break;
            default:
                throw MyException("Invalid Command.");
        }
    }
    if(!ended)
        throw MyException("Preliminary Exit. Exitted without exit command.");
}


// Stop & Debug Method Set.
/*
**    Author: Dan Bauer
**    Function Purpose:
**        Stops the reading from the file.
**    Function Output: Bool for ending the file loop. True to stop, False to not.
**    Side Effects: Calls delete tree which utilizes side effects.
*/
bool C_Tree::p_stop(){
    // Ending debugging data. Allows for exit printing.
    debug(DEBUG_ENABLED);

    // Not worth killing the execution.
    if(this->p_root != NULL){ this->deleteTree(); }

    cout << "Quitting..." << endl;
    return true;
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Outputs some basic debugging data and allows for stepping.
**        Allows the User to step threw the insertions.
**    Function Output: N/A (No return)
**    Side Effects: Utilizes IO functions.
*/
void C_Tree::debug(bool set){
    if(!set){ return; }

    if(this->p_root != NULL){ this->print(); }
    else{ cout << "No tree to print." << endl; }

    cout << endl <<"Hit [ENTER] to continue..." << endl;
    cin.ignore();
}


// Rotation Method Set.
/*
**    Author: Dan Bauer
**    Function Purpose:
**        Runs the Left rotation algorithm on a specified node.
**    Function Output: N/A (No return)
**    Side Effects: Modifies the internal data structure.
*/
void C_Tree::p_rotateLeft(S_NODE* node){
    if(node == NULL)
        throw MyException("CRITICAL Rotation Error. Cannot rotate NULL node.");
    else if(node->right == NULL)
        throw MyException("Rotation Error. Cannot Rotate Left.");
    else
        this->p_rotateLeft(node->parent, node, node->right);
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Adjusts the internal data structure to comply with a Left rotation on
**        a specified node. Overloaded for parameter simplicity.
**    Function Output: N/A (No return)
**    Side Effects: Modifies the internal data structure.
*/
void C_Tree::p_rotateLeft(S_NODE* gp, S_NODE* node, S_NODE* child){
    if(child != NULL){
        if(gp != NULL)
            (gp->left == node) ? gp->left = child : gp->right = child;
        else{ this->p_root = child; }

        child->parent = gp;
        node->parent = child;
        node->right = child->left;
        child->left = node;
        if(node->right != NULL){ node->right->parent = node; }

        // Height modifications.
        node->rheight = child->lheight;
        child->lheight = max(node->lheight, node->rheight) + 1;
    }
    else{ throw MyException("Left rotation could not be performed."); }
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Runs the Right rotation algorithm on a specified node.
**    Function Output: N/A (No return)
**    Side Effects: Modifies the internal data structure.
*/
void C_Tree::p_rotateRight(S_NODE* node){
    if(node == NULL)
        throw MyException("CRITICAL Rotation Error. Cannot rotate NULL node.");
    else if(node->left == NULL)
        throw MyException("Rotation Error. Cannot Rotate Right.");
    else
        this->p_rotateRight(node->parent, node, node->left);
}

/*
**    Author: Dan Bauer
**    Function Purpose:
**        Adjusts the internal data structure to comply with a Right rotation on
**        a specified node. Overloaded for parameter simplicity.
**    Function Output: N/A (No return)
**    Side Effects: Modifies the internal data structure.
*/
void C_Tree::p_rotateRight(S_NODE* gp, S_NODE* node, S_NODE* child){
    if(child != NULL){
        if(gp != NULL)
            (gp->right == node) ? gp->right = child : gp->left = child;
        else{ this->p_root = child; }

        child->parent = gp;
        node->parent = child;
        node->left = child->right;
        child->right = node;
        if(node->left != NULL){ node->left->parent = node; }

        // Height modifications.
        node->lheight = child->rheight;
        child->rheight = max(node->rheight, node->lheight) + 1;
    }
    else{ throw MyException("Right rotation could not be performed."); }
}
