/*
   -----------------------------------------------------------
    Program 3: Vigenere
    Class: CS 141, Spring 2020.  Tues 4pm lab
    System: CLion
    Author: Krish Bavana
    -----------------------------------------------------------
  */

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cctype>     // Allows using the tolower() function
#include <cstring>  //for using strcmp and strlen
#include <sstream> //for using the string stream to extract the words from sentence
using namespace std; //so we dont preface everything with std::

// Global constants
const int LineLength = 81; //max lenght of the array
const int MaxWordSize = 21735; //max number of words in the dictionary text file
char dictio[21735][81];


char * dictWord(char dictionary[21735][81]){ //this function is used for returning the 2D array of dictionary with all the words in it.
    ifstream inStream;             // declare an input stream
    inStream.open( "D:\\College\\dictionary.txt"); //opening the file
    if( !inStream.is_open()) { //weather to check if the the file is open or not
        cout << "Could not find dictionary.txt.  Exiting..." << endl; //if it is not open
        exit( -1);//exit cases
    }
    char theWord[ 81];    // declare input space to be clearly larger than largest word
    int i = 0; //this used for inputing the values into dictonary from the theWord
    while(inStream >> theWord) { //while the words exisit send all of them to theWord
        if(strlen(theWord) >= 3){ //it is to only send the words that are larger than the length 3
            for(int k = 0; k < strlen(theWord); k++){ //writing this loop for passing all the values that are in the word
                dictionary[i][k] = theWord[k]; //passing functiom
            }//for loop close
            i++; //incrementer
        } //if statement close
    }//while loop close
    inStream.close();//close the file
}//closing the function bracker

int binSearch(char checkWord[], char dictWordTwo[][81]){ //this function is used for writing the binary search, which checks the word log n times faster
    //-------------------------------------------------------------------------
    ifstream inStream;             // declare an input stream
    inStream.open( "D:\\College\\dictionary.txt"); //opening the file
    if( !inStream.is_open()) { //weather to check if the the file is open or not
        cout << "Could not find dictionary.txt.  Exiting..." << endl; //if it is not open
        exit( -1);//exit cases
    }
    char theWord[ 81];    // declare input space to be clearly larger than largest word
    int i = 0; //this used for inputing the values into dictonary from the theWord
    while(inStream >> theWord) { //while the words exisit send all of them to theWord
        if(strlen(theWord) >= 3){ //it is to only send the words that are larger than the length 3
            for(int k = 0; k < strlen(theWord); k++){ //writing this loop for passing all the values that are in the word
                dictWordTwo[i][k] = theWord[k]; //passing functiom
            }//for loop close
            i++; //incrementer
        } //if statement close
    }//while loop close
    inStream.close();//close the file
    //---------------------------------------------------------------------------
    int top = MaxWordSize; //setting the top to be lenght of words in the dictionary file
    int down = 0; //lowest number of words
    int middle = 0; // assinged for later use
    while (down <= top) { //this loop is used for setting the middle until it reaches the accurate point
        middle = (top + down) / 2; //middle is been set by divison of both top and down
        int compare = strcmp(checkWord, dictWordTwo[middle]); //comparing both the string, and assinging the value to compare
        if (compare == 0) { //if compare returned 0, then the word is found
            return 9; //return value nine for running in later purposes
        }
        else if (compare < 0) { //if it is less than 0, then top will be middle - 1; so it can search with new values
            top = middle - 1;
        }
        else{
            down = middle + 1; //if is greater than 0, then down will be middle 1, so it can search again with new values
        }
    }
    return -1; //return value negative, if it fails
}//closing bracker of binSearch(0

int dictCount(char sentence[])//this fucntion is used for  breaking the sentence into words and finding how many words are in there
{
    char newWord[LineLength]; //setting up the new array with the maxium lenght of 81
    int counterFinal = 0; //using it for keeping track of how many words are there
    int incrementer = 2;
    //setting up a 2d array with max number of words and 81 line length

    stringstream wordBreaker(sentence); //assigning the stringstream wordBreak and passing the sentence to break words
    while (wordBreaker >> newWord) { //all the words are being transfered into newWord
        if (strlen(newWord) >= 6) { //checks weather this newWord is >= 3 letter or not
            if (binSearch(newWord, dictio) == 9) { //if the binary search value returns 9, then the binary Search got succeded and the words is found
                counterFinal = counterFinal + 1; //incrementing the counter to know the lenght
                incrementer = incrementer + 2;
            }
        }

    }
    return counterFinal; //returns the number of words found using the lenght
}

string keyGenerator(char text[], char orgKey[]) { //this function returns the key that matches the text lenght
    char key[LineLength]; //setting up the new array called key to generate the new key
    int textLen = strlen(text); //for knowing the lenght of the text user inputted
    int orgKeyLen = strlen(orgKey); //for knowing the lenght of the user inputted
    strcpy(key, orgKey); //for coping the orginal key into the key
    int divRule = textLen/orgKeyLen; //this for add the word multiple times
    for(int i = 1; i < (divRule); i++){ //this loop is for concatinating the word multiple times
        strcat(key, orgKey); //concate funtion
    }
    int modRule = textLen % orgKeyLen; //to see how many letters are remaining in the key to fill
    int keyLen = strlen(key); // to find the new key lenght
    for(int k = 0; k < modRule; k++) { //for filling the words reminder number of times
        key[keyLen] = orgKey[k]; //adding the words into new key
        keyLen++; //increment
    }
    key[textLen] = '\0'; //making the last character of the array null, so we dont occur with any problems
    return key; //return the new key
}

string vigEncode(char text[], string key){ //this funtion is for encoding the text
    int textLen = strlen(text); //this get the length of text
    char vigEncoded[LineLength]; //new char array created for new encrypted text
    for(int i = 0; i< textLen; i++) { //looping to make all the charcters to upper
        text[i] = toupper(text[i]); //to upper
        key[i] = toupper(key[i]); //to upper
    }
    for (int i = 0; i < (textLen) ; i++){ //for i less than text, we gwet the encryted key of every character
        if (text[i] == 32) { //if the chracter is space, just make it space
            vigEncoded[i] = ' ';
        } else {
            vigEncoded[i] = (text[i] + key[i]) % 26; //else shift the value to get the new text
            vigEncoded[i] = vigEncoded[i] + 65; //to make the letters capital
        }
    }
    for(int i = 0; i < textLen; i++){ //for making the word, lower
        text[i] = tolower(text[i]);
        key[i] = tolower(key[i]);//assigning everything to lower
        vigEncoded[i] = tolower(vigEncoded[i]);
    }
    cout<<key<<endl; //printing key
    cout<<text<<endl; //printing text
    cout<<vigEncoded<<endl;//printing vigEncide
    return vigEncoded;
}

char* vigDecode(char text[], string key, char orgKey[]){//this function is for decoding the text
    int textLen = strlen(text); //this is to find out the lenght of text
    static char vigDecode[LineLength]; //creating a new variable for making new text
    for(int i = 0; i< textLen; i++) { //for making all the character upper
        text[i] = toupper(text[i]); //upper
        key[i] = toupper(key[i]);
    }
    for (int i = 0; i < (textLen); ++i){ //for moving every character required
        if (text[i] == 32) { //if the chracter is space, then assign space
            vigDecode[i] = ' '; //space
        } else {
            vigDecode[i] = (text[i] - key[i] + 26) % 26; //for moving the required number of times
            vigDecode[i] = vigDecode[i] + 'A'; //for making the chracter capital
        }
    }
    for(int i = 0; i < textLen; i++) {
        text[i] = tolower(text[i]); //to lower the text
        key[i] = tolower(key[i]); //to lower the text
        vigDecode[i] = tolower(vigDecode[i]);
    }
    return vigDecode;
}


string autoDecode(char secText[]){ //this fucntion is for decoding the
    // Open a file for reading
    int counterTest = 0; //to see how many times to print the decrypter
    ifstream file;             // declare an input stream
    file.open( "D:\\College\\TheSecretAgentByJosephConrad.txt");
    if( !file.is_open()) {
        cout << "Could not find dictionary.txt.  Exiting..." << endl;
        exit( -1);
    }
    char theWord[ 81];    // declare input space to be clearly larger than largest word
    while( file >> theWord) { //inputting all the words
        int num = dictCount(vigDecode(secText, keyGenerator(secText, theWord), theWord)); //calling to see how many words exisit
        if(strlen(theWord) >= 6){ //if the word is greater than 6
            if(num > counterTest){ //if the words are greater than counterTest than print, so it dont print any duplicates
                cout << num;
                cout << " words found using keyword: " << theWord << " giving:" << endl;
                cout << "   " << vigDecode(secText, keyGenerator(secText, theWord), theWord) << endl;
                counterTest = num;//setting the counterTest to number of words
            }
        }
    }
    file.close();//closing the file

}

//---------------------------------------------------------------------------
int main() {
    // Declare variables
    int menuOption;                   // Userinput for menu option
    char returnCharacter;             // Separately store the return character so cin.getline does not consider it the next user input


    // Display menu and handle menu options
    cout << "21735 words of size >= 3 were read in from dictionary. " << endl;
    cout << endl;
    cout << "Choose from the following options: \n"
         << "    1. Lookup dictionary word \n"
         << "    2. Encode some text  \n"
         << "    3. Decode some text  \n"
         << "    4. Auto-decode the ciphertext given with the assignment  \n"
         << "    5. Exit program  \n"
         << "Your choice: ";
    cin >> menuOption;
    returnCharacter = cin.get();  // Read and discard the return character at the end of the above input line.
    // This is necessary because otherwise a subsequent cin.getline() reads it as
    // an empty line of input.
    char text[LineLength]; //to input the text
    char orgKey[LineLength]; //to input the key
    char checkWord[LineLength]; //to input the text for decrypt
    char autoDecodeWord[LineLength]; //to decrypt text from user
    int search; //used in finding words
    char dictionary[21735][81]; //created a char 2d arrayd for binary search
    switch (menuOption) {
        case 1: // Do dictionary lookup of a word and indicate whether or not it was found.
            dictWord(dictionary); //generating the text into 2d array
            cout << "Enter a word to be looked up in dictionary: ";
            cin.getline(checkWord, LineLength); //user input
            search = binSearch(checkWord, dictionary); //to get the number of words
            if(search == 9) { //if resulted 9, then it is in the dictionary
                cout << checkWord << " IS in the dictionary." << endl;
            }
            else{
                cout << checkWord << " is NOT in the dictionary." << endl;
            }
            break;

        case 2: // Encode some text
            cout << "Enter the text to be encoded: ";
            cin.getline(text, LineLength);//userInput
            cout << "Enter a keyword for Vigenere encryption: ";
            cin.getline(orgKey, LineLength);//userInput

            cout << "Keyword, plainText and ciphertext are:  " << endl;
            vigEncode(text, keyGenerator(text, orgKey)); //calling vigEncode
            break;

        case 3: // Decode using user-entered values
            cout << "Enter the cipherText to be decoded: ";
            cin.getline(text, LineLength); //userInput
            cout << "Enter a Vigenere keyword to be tried: ";
            cin.getline(orgKey, LineLength);//userInput
            cout << dictCount(vigDecode(text, keyGenerator(text, orgKey), orgKey));
            cout << " words found using keyword: " << orgKey << " giving:" << endl;
            cout << "   " << vigDecode(text, keyGenerator(text, orgKey), orgKey) << endl;
            break;


        case 4: // Decode ciphertext given with the assignment
            cout << "Enter the cipherText to be decoded: ";
            cin.getline(autoDecodeWord, LineLength);//userInput
            autoDecode(autoDecodeWord); //calling autodecode
            break;

        case 5: // exit program
            cout << "Exiting program" << endl;
            exit( 0);
            break;

        default:
            // Sanity check
            cout << "Invalid menu option.  Exiting program." << endl;
            break;
    }// end switch( menuOption)

    return 0;
}//end main()
