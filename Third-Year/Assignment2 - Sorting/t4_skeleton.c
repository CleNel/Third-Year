#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h> 

typedef struct _game{
	char title[65];
    char platform[20];
    int score;
    int year;
 }game;

game* list[18626];

int partition(game* array[], int start, int end);
void QuickSort(game* arr[], int high, int low);

void QuickSort(game* arr[], int high, int low){
    
    int pivotIndex;

    if(low<high){
        pivotIndex = partition(arr, high, low);
        QuickSort(arr, pivotIndex - 1, low);
        QuickSort(arr, high, pivotIndex + 1);

    }
}

int partition(game* arr[], int high, int low){
    
    int pivot = arr[high]->score;
    int i = low - 1;
    game *temp;

    for(int j = low; j < high; j++){
        if(arr[j]->score >= pivot){
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;

    return (i + 1);

}

void next_token ( char *buf, FILE *f, int string_max ) {

	// read string of alphanumeric characters
	int i=0;
	for (;;) {
		buf[i] = fgetc(f); // get next character from file

		if(buf[i]=='"'){
			i++;
			buf[i] = fgetc(f);
			while(buf[i]!='"'){
				i++;
				buf[i] = fgetc(f);
			}
		}

		if( !isalnum(buf[i]) ) { 
            if(buf[i]==','){ // we still want to keep spaces
				break;
			}
        }
		if(buf[i]=='\n'){break; }
		if( feof(f) ) { break; }          // file ended?
		if( i < (string_max-1) ) { ++i; } // truncate strings that are too long
	}
	buf[i] = '\0'; // NULL terminate the string

}

int load_file ( char *fname ) {
	FILE *f;
	char buf[100];

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}

	for(int k = 0; k < 4; k++){
		next_token(buf, f, 100);
	}
	//printf("\n");

	for(int i = 0; i < 18625; i++){
		game* temp = (game*)malloc(sizeof(game));
		for(int j = 0; j < 4; j++){
			if(j == 0){
				next_token(buf,f,100);
				strcpy(temp->title, buf);
				//printf("%i : %s",i,temp->title);
			}else if(j == 1){
				next_token(buf,f,100);
				strcpy(temp->platform, buf);
				//printf("   |   %s", temp->platform);
			}else if(j == 2){
				next_token(buf,f,100);
				temp->score = atoi(buf);
				//printf("   |   %i", temp->score);
			}else if(j == 3){
				next_token(buf,f,100);
				temp->year = atoi(buf);
				//printf("   |   %i", temp->year);
				list[i] = temp;
			}

		}
		//printf("\n");
	}

    //printf("File %s loaded\n", fname);
    fclose(f);

	return 1;
}

int main(){
    
    load_file("t4_ign.csv");

	QuickSort(list, 18624, 0);

	for(int i = 0; i < 10; i++){

		printf("%-51s",list[i]->title);
		printf("%-21s",list[i]->platform);
		printf("%-3i",list[i]->score);
		printf("%i",list[i]->year);
		printf("\n");

	}

    return 0;

}