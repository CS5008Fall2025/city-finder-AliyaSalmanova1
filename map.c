
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "map.h"

#define MAX_FILE_LINE_LENGTH 226

typedef struct DestinationNode{
    int distance;
    struct DestinationNode *next;
} DestinationNode;

typedef struct City{
    char cityName[MAX_FILE_LINE_LENGTH];
    struct DestinationNode *destinations;
} City;

typedef struct AdjCityListGraph{
    int length;
    City **cityList;
} AdjCityListGraph;




bool validCities(const char *city1, const char *city2, const char *fileName){
    /*char buffer[MAX_FILE_LINE_LENGTH];

    FILE *file_ptr;

    file_ptr = fopen(fileName, "r");

    if (file_ptr == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, MAX_FILE_LINE_LENGTH, file_ptr) != NULL){
        
    }
     */
    return true;
    
    
}

AdjCityListGraph* makeGraphFromCities(int fileLength, FILE *citiesFilePtr){

    AdjCityListGraph *graph = (AdjCityListGraph*)malloc(sizeof(AdjCityListGraph));
    graph->length = fileLength;
    graph->cityList = (City**)malloc(sizeof(City) * fileLength);

    char buffer[MAX_FILE_LINE_LENGTH];

    int i = 0;
    while (fgets(buffer, MAX_FILE_LINE_LENGTH, citiesFilePtr) != NULL){
        City *city = (City*)malloc(sizeof(City));
        strncpy(city->cityName, buffer, MAX_FILE_LINE_LENGTH);
        city->destinations = NULL;
        graph->cityList[i++] = city;
        
    }

    return graph;

}

void addEdgesToGraph(AdjCityListGraph *graph, FILE *distancesFilePtr){

    char buffer[MAX_FILE_LINE_LENGTH];

    while (fgets(buffer, MAX_FILE_LINE_LENGTH, distancesFilePtr) != NULL){
        
    }

}



AdjCityListGraph* convertFilesToGraph(const char *citiesFileName, const char *distancesFileName){
    char buffer[MAX_FILE_LINE_LENGTH];

    FILE *citiesFilePtr;
    FILE *distancesFilePtr;

    citiesFilePtr = fopen(citiesFileName, "r");
    distancesFilePtr = fopen(distancesFileName, "r");


    /*if (citiesFilePtr == NULL || distancesFilePtr || NULL) {
        perror("Error opening a file");
    }*/

    int fileLength = 0;
    while (fgets(buffer, MAX_FILE_LINE_LENGTH, citiesFilePtr) != NULL){
        fileLength++;
    }

    AdjCityListGraph * adjCityListGraph = makeGraphFromCities(fileLength, citiesFilePtr);
    
    addEdgesToGraph(adjCityListGraph, distancesFilePtr);

    return adjCityListGraph;
    
}




void djikstrasAlgo(const char *city1, const char *city2){
    
}


char * makeStringLowercase(const char *string){
    char stringLowercase[strlen(string)];
    
    int i = 0;
    while (string[i] != "\0"){
        printf("%c", string[i]);
        stringLowercase[i] = tolower(string[i]);
    }

    return stringLowercase; 
}

bool validateFile(const char *file){
    FILE *file_pointer;
    file_pointer = fopen(file, "r");

    return file_pointer != NULL;
}

int main (int argc, char *argv[]){

    if (argc < 3) {
        printf("Must enter vertex file and distance file!");
        return 1;
    } 
    if (!validateFile(argv[1]) || !validateFile(argv[2])){
        printf("Invalid file!\n");
        return 1;
    }

    AdjCityListGraph* graph = convertFilesToGraph(argv[1], argv[2]);

    char choice[100] = "";
    
    while (true){
        printf("*****Welcome to the shortest path finder!******\n");
        printf("Commands:\n");
        printf("\tlist - list all cities\n");
        printf("\t<city1> <city2> - find the shortest path between two cities\n");
        printf("\thelp - print this help message\n");
        printf("\texit - exit the program\n");
        printf("*******************************************************\n");
        printf("Where do you want to go today? what do i do?\n");
        scanf("%99s", choice);

        if (strcmp(choice, "help") == 0){
            continue;
        } else if (strcmp(choice, "exit") == 0){
            printf("Goodbye!");
            break;
        } else{
            char* city1 = makeStringLowercase(strtok(choice, " "));
            char* city2 = makeStringLowercase(strtok(choice, " "));
            while (city2 != NULL) {
                printf("%s\n", city2);
                city2 = makeStringLowercase(strtok(NULL, " "));
                if (validCities(city1, city2, argv[1]) == true){
                    djikstrasAlgo(city1, city2);
                } else {
                    printf("These are not valid cities!");
                    continue;
                }
            } 
        }
    }
}