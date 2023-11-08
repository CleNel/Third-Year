#include<stdio.h>
#include<stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum

// NB: this skeleton is here to help you - ignore anything that does not help you
// There are a lot of others (and better!) ways of doing this

// note this sekeleton uses a global variable. It therefore will only work with 
// one hashtable, of the size set. In general global variables should be avoided
// as their global scope makes it very challenging to see where they are updated 
// (as it can be anywhere!), and don't work well when several threads/programs
// update them at the same time (concurency), amongst others problems.
// Having said that, they can make coding a bit easier, so that's why we are using 
// one here. If you can, try using a hashTable as a variable, passing it as a 
// parameter to functions!



#define MAX_STRING_SIZE 20 //max length of a string
#define ARRAY_SIZE 62003  //best be prime
#define NAME_PROMPT "Enter term to get frequency or type \"quit\" to escape\n>>> " //you can use this string as your invitation to the user
#define NEW_LINE_PROMPT ">>> " //you can use this string as your invitation to the user where the user should input the name

//Linked List Code

typedef struct _vet{
	int id;
	char depId[MAX_STRING_SIZE];
	char surname[MAX_STRING_SIZE];
	char forename[MAX_STRING_SIZE];
	int age;
	char personType[MAX_STRING_SIZE];
	char gender[MAX_STRING_SIZE];
	char nationality[MAX_STRING_SIZE];
	char religion[MAX_STRING_SIZE];
	char occupation[MAX_STRING_SIZE];
 }vet;

typedef struct _listOfPeople{
	struct _listOfPeople* next;
	vet* veteran;
}listOfPeople;

vet* createNode(){
	vet* temp;
	temp = (vet*)malloc(sizeof(vet));
	return temp;
}

void addVetToList(listOfPeople* list, vet* addedPerson){
	while(list->next){
		list = list->next;
	}

    listOfPeople* temp;
    temp = (listOfPeople*)malloc(sizeof(listOfPeople));

	temp->veteran = addedPerson;
    temp->next = NULL;
	list->next = temp;

    return;
}

void printLinkedList(listOfPeople* list){
	printf("%i  %s  %s  %s  %i  %s  %s  %s  %s  %s", list->veteran->id, list->veteran->depId, list->veteran->surname, list->veteran->forename, list->veteran->age, list->veteran->personType, list->veteran->gender, list->veteran->nationality, list->veteran->religion, list->veteran->occupation);
	while(list->next){
		list = list->next;
		printf("%i  %s  %s  %s  %i  %s  %s  %s  %s  %s", list->veteran->id, list->veteran->depId, list->veteran->surname, list->veteran->forename, list->veteran->age, list->veteran->personType, list->veteran->gender, list->veteran->nationality, list->veteran->religion, list->veteran->occupation);
	}
}

//Hash Table code

typedef struct Element Element;
struct Element{
    int freq;
	listOfPeople* linkedList;
};

Element* hashTable[ARRAY_SIZE];
int collisions = 0;
int num_terms = 0;

int hash_function(char* s){
    int hash = 0;
    while(*s){
       hash = (hash + *s**s - 'A') %ARRAY_SIZE;
        s++;
    }
    return hash;
}


Element* createNewElement(vet* vet){
    // TODO2
    // you might want to use the function strcpy from the string package here!
	Element* newEle;
	newEle = (Element*)malloc(sizeof(struct Element));
	newEle -> freq = 1;

	listOfPeople* temp;
    temp = (listOfPeople*)malloc(sizeof(listOfPeople));

	temp->veteran = vet;
    temp->next = NULL;
	newEle->linkedList = temp;

	return newEle;
}


// returns the element with name name or NULL if the element is not present
Element* search (char* name){
    //TODO4
	int i = hash_function(name);
	while(hashTable[i] != NULL){
		if(strcmp(hashTable[i] -> linkedList->veteran->surname, name) == 0){
			return hashTable[i];
		}
		++i;
		i %= ARRAY_SIZE;
	}
    return NULL;
}

// assuming that no element of key name is in the list (use search first!), add element at the correct place in the list
// NB: it would be more efficient for search to return the index where it should be stored directly, but aiming for simplicity here!
void insert(vet* dummy){
   // TODO3
	Element* item = createNewElement(dummy);
	int currentIndex = hash_function(dummy->surname);


		while (hashTable[currentIndex] != NULL){
			++currentIndex;
			currentIndex %=ARRAY_SIZE;
			++collisions;
		}

		hashTable[currentIndex] = item;
	
}

// prints the number of occurences, or 0 if not in the file
void printOccurences(char* name){
    //TODO5
	Element* parce;
		if(search(name) == NULL){
			printf("%s not in the table",name);
			return;
		}else{
			parce = search(name);
			printf(" Person ID Deposition ID Surname Forename Age Person Type Gender Nationality Religion Occupation\n");
			printLinkedList(parce->linkedList);
			
		}
}


//searches the name in the array, if it is there increment its count, if not, add it
void addOrIncrement(vet* dummy){
    //TODO6
	if(search(dummy->surname) == NULL){
		insert(dummy);
	}else{
		Element* buf = createNewElement(dummy);
		addVetToList(buf->linkedList, dummy);
	}
}



// From assignment 0
// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
vet* next_token ( char *buf, FILE *f, int string_max ) {
	int end = 0;
	// start by skipping any characters we're not interested in
	buf[0] = fgetc(f);
	int buffer;
	vet* dummy = createNode();
	
	while ( !isalnum(buf[0]) && !feof(f) ) { buf[0] = fgetc(f); }
	int i=1;
	for(int j = 0; j < 10; j++){
	// read string of alphanumeric characters
	while (buf[i] != ',') { 
		buf[i] = fgetc(f);              // get next character from file
		if(buf[i] == '"'){buf[i] = fgetc(f);}
		if(buf[i] == '\n'){buf[i] = 0; end = 1; break; }
		if(buf[i] == ','){buf[i] = 0; end = 1; break; }
		if( !isalnum(buf[i]) ) { 
            if(buf[i]!=' '){ // we still want to keep spaces
                break; // only load letters and numbers
            }
        } 
		if( feof(f) ) { end = 1; break; }          // file ended?
		if( i < (string_max-1) ) { i++; } // truncate strings that are too long
	}

	if(j == 0 || j == 4){
		buffer = atoi(buf);	
	}

	if(j == 0){
		dummy->id = buffer;
	}else if(j == 1){
		strcpy(dummy->depId, buf);
	}else if(j == 2){
		strcpy(dummy->surname, buf);
	}else if(j == 3){
		strcpy(dummy->forename, buf);
	}else if(j == 4){
		dummy->age = buffer;
	}else if(j == 5){
		strcpy(dummy->personType, buf);
	}else if(j == 6){
		strcpy(dummy->gender, buf);
	}else if(j == 7){
		strcpy(dummy->nationality, buf);
	}else if(j == 8){
		strcpy(dummy->religion, buf);
	}else if(j == 9){
		strcpy(dummy->occupation, buf);
	}

	
	buf[i] = '\0'; // NULL terminate the string
	i = 0;
	memset(buf, 0, MAX_STRING_SIZE);

	}

	return dummy;
}



//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file ( char *fname ) {
	FILE *f;
	char buf[MAX_STRING_SIZE];

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}
	
	while(!next_token(buf,f,MAX_STRING_SIZE));

	// read until the end of the file
	while ( !feof(f) ) {
			addOrIncrement(next_token(buf, f, MAX_STRING_SIZE));
			num_terms++;
	}
    
    printf("File %s loaded\n", fname);
    float load = (float)num_terms/ARRAY_SIZE; //TODO7
    printf(" Capacity: %i\n Num Terms: %i\n Collisions: %i\n Load: %f\n", ARRAY_SIZE, num_terms, collisions,load);
	// always remember to close your file stream
	fclose(f);

	return 1;
}



int main ( int argc, char *argv[] ) {
    
	//TODO0
	//advice: follow the TODO number order
	//first test insert and search
    //then move on to addOrIncrement
    //only then worry about loading the file - see the function above and assignment 0 as to have to use arguments for your executable
    //and later again about an interactive interface - see the assignment 0 solution and the #define strings above

    load_file("truncated.csv");
	//load_file("people.csv");
	//printf("Cle is %u\n", hash_function("Cleo"));

	//printf("(%i)\n",hash_function("Wicken"));
	//print_all_occurances();
	char term[MAX_STRING_SIZE];
	printf("Enter term to get frequency or type \"quit\" to escape");
	while(strcmp(term, "quit") != 0){
		printf("\n>>> ");
		scanf("%s", term);
		if(strcmp(term, "quit") != 0){
			printOccurences(term);
		}
	}
    return 0;
}