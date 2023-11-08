#include <stdio.h>
#include <stdbool.h>

int next_field ( FILE *csv);

// #,Name,Type 1,Type 2,Total,HP,Attack,Defense,Sp. Atk,Sp. Def,Speed,Generation,Legendary,Pokedex Entry

struct pokemon {
    int number;
    char type1 [10];
    char type2 [10];
    int bst;
    int health;
    int attack;
    int defense;
    int spattack;
    int spdefense;
    int speed;
    int generation;
    char legendary [5];
    char pokedexEntry [150];
};

int main () {

    FILE * pFile = fopen("pokemon.csv", "r");
   
    int n = 0;

    while(n == 0){
         n = next_field(pFile);
         printf("\n");

    }

    return 0;
}

int next_field ( FILE *csv){

    struct pokemon thisPokemon;
    char c;
    int counter = 0;
    bool q = 0;
        do {
                c = fgetc (csv);
                if(c == EOF) return 1;
                if(c == '"') q = 1;
                if(!q){
                    if (c == ',') return 0;
                }
                printf("%c", c);
                if(counter = 0){
                    
                }else if(counter = 1){

                }else if(counter = 2){
                    
                }else if(counter = 3){
                    
                }else if(counter = 4){
                    
                }else if(counter = 5){
                    
                }else if(counter = 6){
                    
                }else if(counter = 7){
                    
                }else if(counter = 8){
                    
                }else if(counter = 9){
                    
                }else if(counter = 10){
                    
                }else if(counter = 11){
                    
                }else if(counter = 12){
                    
                }
            } while (c != '\n');


        return 0;
          
}