#ifndef CITY_H
#define CITY_H
typedef struct{
	unsigned int requirements;
	unsigned char met_requirements;
}City;
void initCity(City*,unsigned int);
void meetRequirements(City*);
unsigned int getRequirements(City);
unsigned char getMetRequirements(City);
#endif
