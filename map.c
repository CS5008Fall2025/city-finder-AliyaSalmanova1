
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include "map.h"


#define MAX_FILE_LINE_LENGTH 226

typedef struct DestinationNode{
    char destinationName[MAX_FILE_LINE_LENGTH];
    int distance;
    int vertexIndex;
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

typedef struct Node{
	char cityName[MAX_FILE_LINE_LENGTH];
	struct Node *next;
} Node;



bool validCity(const char *city1, AdjCityListGraph *graph){

    for (int i = 0; i < graph->length; i++){
        if (strcmp(city1, graph->cityList[i]->cityName) == 0) return true;
    }
    return false;
 
}

AdjCityListGraph* makeGraphFromCities(int fileLength, FILE *citiesFilePtr, const char *citiesFileName){

    AdjCityListGraph *graph = (AdjCityListGraph*)malloc(sizeof(AdjCityListGraph));
    graph->length = fileLength;
    graph->cityList = (City**)malloc(sizeof(City*) * fileLength);

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

int findIndexOfVertex(const char *cityName, AdjCityListGraph *graph){

    for (int i = 0; i < graph->length; i++){
        if (strcmp(cityName, graph->cityList[i]->cityName) == 0){
            return i;
        }
    }
    return -1;
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

        //printf("source: %s, destinationName: %s, distance: %s\n", source, destinationName, distance);

        if (!validCity(source, graph) || !validCity(destinationName, graph)){
            continue;
        }

        bool cityAdded = false;
        

        int i = 0;
        while (cityAdded == false && i < graph->length){
            if (strcmp(source, graph->cityList[i]->cityName) == 0){
                DestinationNode *node = (DestinationNode *)malloc(sizeof(DestinationNode));
                strncpy(node->destinationName, destinationName, 226);
                node->vertexIndex = findIndexOfVertex(node->destinationName, graph);
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



bool allVisited(bool *visited, int length){
    for (int i = 0; i < length; i++){
        if (visited[i] == false) return false;

    }
    return true;
}

int findMinDistanceIndex(int *minDistances, bool *visited, int length){
    int minDistance = INT_MAX;
    int index = -1;
    for (int i = 0; i < length; i++){
        if (!visited[i] && minDistances[i] < minDistance){
            minDistance = minDistances[i];
            index = i;
        }
    }
    return index;
}

void dijkstrasAlgo(const char *city1, const char *city2, AdjCityListGraph *graph){

    int *minDistances = (int *)malloc(sizeof(int) * graph->length);
    int previous[graph->length];
    bool *visited = (bool *)malloc(sizeof(bool) * graph->length);

    for (int i = 0; i < graph->length; i++){
        minDistances[i] = INT_MAX;
        previous[i] = -1;
        visited[i] = false;
    }

    int city1Index = findIndexOfVertex(city1, graph);
    minDistances[city1Index] = 0;
    previous[city1Index] = 0;
    
    while (!allVisited(visited, graph->length)){
        int currCityIndex = findMinDistanceIndex(minDistances, visited, graph->length);
        City *currentCity = graph->cityList[currCityIndex];
        DestinationNode *destinations = currentCity->destinations;
        while (destinations != NULL){
  
            if (minDistances[currCityIndex] + destinations->distance <= 
                minDistances[destinations->vertexIndex]){
                    
                    minDistances[destinations->vertexIndex] = minDistances[currCityIndex] + destinations->distance;
					previous[destinations->vertexIndex] = currCityIndex;
            }
            destinations = destinations->next;
        }
        visited[currCityIndex] = true;
        
    }

    int city2Index = findIndexOfVertex(city2, graph);

	
	if (minDistances[city2Index] == INT_MAX){
		printf("No path found.\n");
	}else {
		Node *node = NULL;  
    	int prev = city2Index;


    	Node *start = (Node *)malloc(sizeof(Node));
    	strcpy(start->cityName, graph->cityList[prev]->cityName);
    	start->next = NULL;
    	node = start;

    	while (strcmp(graph->cityList[prev]->cityName, city1) != 0){
        	prev = previous[prev];
        	if (prev == -1) {
            	printf("No path found.\n");
            
            	return;
        	}
        	Node *newNode = (Node *)malloc(sizeof(Node));
        	strcpy(newNode->cityName, graph->cityList[prev]->cityName);
        	newNode->next = node;
        	node = newNode;
    	}



    	Node *curr = node;
    	while (curr != NULL){
        	printf("%s\n", curr->cityName);
        	curr = curr->next;
    	}
    	printf("Total Distance: %d\n", minDistances[city2Index]);
	}

}


char *makeStringLowercase(const char *string){
    size_t len = strlen(string);
    char *stringLowercase = malloc(len + 1);  
    if (!stringLowercase) return NULL;

    for (size_t i = 0; i < len; i++){
        stringLowercase[i] = tolower((unsigned char)string[i]);
    }
    stringLowercase[len] = '\0';
    return stringLowercase; 
}

bool validateFile(const char *file){
    FILE *file_pointer;
    file_pointer = fopen(file, "r");

    return file_pointer != NULL;
}

void printGreeting(){
    printf("*****Welcome to the shortest path finder!******\n");
}

void printCommands(){
	printf("Commands:\n\tlist - list all cities\n\t<city1> <city2> - find the shortest path between two cities\n\thelp - print this help message\n\texit - exit the program\n");
}

void printLine(){
    printf("*******************************************************\n");
}

void printQuestion(){
	printf("Where do you want to go today? what do i do? ");
}


void printCities(AdjCityListGraph *graph){
    for (int i = 0; i < graph->length; i++){
        City *city = graph->cityList[i];
        printf("%s\n", city->cityName);
    }
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
    //printGraph(graph);

    char choice[100] = "";
    

	printGreeting();
	printCommands();
	printLine();


    while (true){
		
		printQuestion();
        if (fgets(choice, sizeof(choice), stdin) == NULL) {
        	break;  // EOF
    	}

    	// Strip trailing newline if present
    	choice[strcspn(choice, "\n")] = '\0';

        if (strcmp(choice, "help") == 0){
            printCommands();
			continue;
			
        } if (strcmp(choice, "list") == 0 || strcmp(choice, "list\n") == 0){
            printCities(graph);
        }else if (strcmp(choice, "exit") == 0){
            printf("Goodbye!");
			break;
        } else{
            char *city1Raw = strtok(choice, " ");
            char *city2Raw = strtok(NULL, " ");

        	if (city1Raw == NULL || city2Raw == NULL) {

        		printf("City 2 is not a valid city!\n");
        		continue;
    		}

    		char *city1 = makeStringLowercase(city1Raw);
    		char *city2 = makeStringLowercase(city2Raw);

    		if (!validCity(city1, graph)) {
        		printf("City 1 is not a valid city!\n");
    		} else if (!validCity(city2, graph)) {
        		printf("City 2 is not a valid city!\n");
    		} else {
        		dijkstrasAlgo(city1, city2, graph);
    		}

    		free(city1);
    		free(city2);
        }
    }
}