


typedef struct DestinationNode{
    int distance;
    struct DestinationNode *next;
} DestinationNode;

typedef struct City{
    int cityName;
    struct DestinationNode *destinations;
} City;

typedef struct AdjCityListGraph{
    int length;
    City **cityList;
} AdjCityListGraph;

