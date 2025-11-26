
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "map.h"

#define MAX_FILE_LINE_LENGTH 226

typedef struct DestinationNode{
    char destinationName[MAX_FILE_LINE_LENGTH];
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



bool validCity(const char *city1, AdjCityListGraph *graph){

    for (int i = 0; i < graph->length; i++){
        if (strcmp(city1, graph->cityList[i]->cityName) == 0) return true;
    }
    return false;
 
}

AdjCityListGraph* makeGraphFromCities(int fileLength, FILE *citiesFilePtr, const char *citiesFileName){

    AdjCityListGraph *graph = (AdjCityListGraph*)malloc(sizeof(AdjCityListGraph));
    graph->length = fileLength;
    graph->cityList = (City**)malloc(sizeof(City) * fileLength);

    char buffer[MAX_FILE_LINE_LENGTH];
    citiesFilePtr = fopen(citiesFileName, "r");

    int i = 0;
    while (fgets(buffer, MAX_FILE_LINE_LENGTH, citiesFilePtr) != NULL){
        int j = 0;
        while (buffer[j] != '\n' && buffer[j] != '\0'){
            j++;
        }
        if (buffer[j] == '\n') buffer[j] = '\0';
        City *city = (City*)malloc(sizeof(City));
        //printf("city name: %s\n", buffer);
        strncpy(city->cityName, buffer, MAX_FILE_LINE_LENGTH);
        city->destinations = NULL;
        graph->cityList[i++] = city;
        
    }

    return graph;

}

void addEdgesToGraph(AdjCityListGraph *graph, const char *distancesFileName){

    FILE *distancesFilePtr;
    distancesFilePtr = fopen(distancesFileName, "r");
    printf("in addEdgesToGraph\n");

    char buffer[MAX_FILE_LINE_LENGTH];

    while (fgets(buffer, MAX_FILE_LINE_LENGTH, distancesFilePtr) != NULL){
        
        char *source;
        char *destinationName;
        char *distance;
        source = strtok(buffer, " ");
        destinationName = strtok(NULL, " ");
        distance = strtok(NULL, " ");

        printf("source: %s, destinationName: %s, distance: %s\n", source, destinationName, distance);

        if (!validCity(source, graph) || !validCity(destinationName, graph)){
            continue;
        }

        bool cityAdded = false;
        

        int i = 0;
        while (cityAdded == false && i < graph->length){
            if (strcmp(source, graph->cityList[i]->cityName) == 0){
                DestinationNode *node = (DestinationNode *)malloc(sizeof(DestinationNode));
                strncpy(node->destinationName, destinationName, 226);
                
                node->distance = atoi(distance);
                node->next = graph->cityList[i]->destinations;
                graph->cityList[i]->destinations = node;
                cityAdded = true;
                break;
                
            }else{
                i++;
            }
        }

    }

}

void printGraph(AdjCityListGraph *graph){
    for (int i = 0; i < graph->length; i++){
        City *city = graph->cityList[i];
        printf("%s: [", city->cityName);
        DestinationNode *destination = city->destinations;
        while(destination != NULL){
            printf("(%s, %d)", destination->destinationName, destination->distance);
            if (destination->next != NULL) printf(" -> ");
            destination = destination->next;
        }
        printf("]\n");
    }
}



AdjCityListGraph* convertFilesToGraph(const char *citiesFileName, const char *distancesFileName){
    char buffer[MAX_FILE_LINE_LENGTH];

    FILE *citiesFilePtr;


    citiesFilePtr = fopen(citiesFileName, "r");


    /*if (citiesFilePtr == NULL || distancesFilePtr || NULL) {
        perror("Error opening a file");
    }*/

    int fileLength = 0;
    while (fgets(buffer, MAX_FILE_LINE_LENGTH, citiesFilePtr) != NULL){
        fileLength++;
    }

    fclose(citiesFilePtr);

    AdjCityListGraph * adjCityListGraph = makeGraphFromCities(fileLength, citiesFilePtr, citiesFileName);
    addEdgesToGraph(adjCityListGraph, distancesFileName);

    return adjCityListGraph;
    
}




void djikstrasAlgo(const char *city1, const char *city2){
    
}


char * makeStringLowercase(const char *string){
    char *stringLowercase = (char *)malloc(strlen(string) * sizeof(char));;
    
    int i = 0;
    while (string[i] != '\0'){
        //printf("%c\n", string[i]);
        stringLowercase[i] = tolower(string[i]);
        i++;
    }

    return stringLowercase; 
}

bool validateFile(const char *file){
    FILE *file_pointer;
    file_pointer = fopen(file, "r");

    return file_pointer != NULL;
}

void displayPrompt(){
    printf("*****Welcome to the shortest path finder!******\n");
    printf("Commands:\n");
    printf("\tlist - list all cities\n");
    printf("\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\thelp - print this help message\n");
    printf("\texit - exit the program\n");
    printf("*******************************************************\n");
    printf("Where do you want to go today? what do i do?\n");
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
    printGraph(graph);

    char choice[100] = "";
    
    while (true){
        displayPrompt();

        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            break; 
        }

        if (strcmp(choice, "help") == 0){
            continue;
        } else if (strcmp(choice, "exit") == 0){
            printf("Goodbye!");
            break;
        } else{
            char *city1;
            char *city2;
            city1 = strtok(choice, " ");
            city1 = makeStringLowercase(city1);
            //printf("city1: %s,\n", city1);
            city2 = strtok(NULL, " ");
            int j = 0;
            while (city2[j] != '\n' && city2[j] != '\0'){
                j++;
            }
            if (city2[j] == '\n') city2[j] = '\0';
            
            city2 = makeStringLowercase(city2);
            //printf("city2: %s,\n", city2);
            /*while (city2 != NULL) {
                city2 = makeStringLowercase(strtok(NULL, " ")); 
            } */
            if (validCity(city1, graph) == false){
                printf("City 1 is not a valid city!\n");
            } else if (validCity(city2, graph) == false){
                printf("City 2 is not a valid city!\n");
            }else {
                printGraph(graph);
                djikstrasAlgo(city1, city2);
            }
        }
    }
}