#ifndef CITY_H_INCLUDED
#define CITY_H_INCLUDED

#define MAX 1000
typedef struct{
	unsigned int demand;
	unsigned int visitd;
	unsigned int ID;
}TCity;

typedef struct{
    TCity city[MAX];
    unsigned int sumDemand;
    unsigned int greater_Demand;
    unsigned int topo;
}TListCity;

void initCity(TCity* city, unsigned int position);
void initListCity(TListCity* listCity);
int insertListCity(TListCity* listCity, TCity* city);

#endif // CITY_H_INCLUDED
