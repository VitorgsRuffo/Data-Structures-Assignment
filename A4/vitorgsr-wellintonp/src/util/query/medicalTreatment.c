#include "../../include/headers.h"
#include "../../include/urbanElements.h"
#include "../../include/dataStructure.h"
#include "../input/openInput.h"
#include "../algorithm/sort.h"


typedef struct {
    HealthCenter healthCenter;
    double distance;
}NearHealthCenter;


char* buildBlueHouseTag(House H);
void calculateDistanceFromHouseToHealthCenters(House H, NearHealthCenter** nearHealthCenters, int healthCentersAmount);
int compareNearHealthCenters(Info Hc1, Info Hc2);
char* buildLineSegmentTag(double x, double y, House H);
void writeHealthCenterCoordinatesOnTxt(File txt, int i, double x, double y, double distance);

void executeMedicalTreatmentSearching(char* command, City Ct, File txt){

    int K; char cep[30]; char face; int number;

    sscanf(&command[4], "%d %s %c %d", &K, cep, &face, &number);

    House house = createHouse("none", cep, face, number, "none", Ct); 

    char* blueHouseTag = buildBlueHouseTag(house);
    List queryElementsList = getQueryElements(Ct);
    insert(queryElementsList, blueHouseTag);

    DataStructure healthCenters = getHealthCenters(Ct);
    HealthCenter* healthCentersArray = PQuadTreeToArray(healthCenters);


    int healthCentersAmount = PQuadTreeSize(healthCenters);

    NearHealthCenter** nearHealthCenters = (NearHealthCenter**) malloc(healthCentersAmount * sizeof(NearHealthCenter*));

    for(int i = 0; i<healthCentersAmount; i++){
        *(nearHealthCenters + i) = (NearHealthCenter*) malloc(sizeof(NearHealthCenter));
        (**(nearHealthCenters + i)).healthCenter = healthCentersArray[i];
    }

    free(healthCentersArray);
    
    calculateDistanceFromHouseToHealthCenters(house, nearHealthCenters, healthCentersAmount);
    
    shellsort((Info*) nearHealthCenters, healthCentersAmount, compareNearHealthCenters);

    int healthCenterX, healthCenterY;
    char* lineSegmentTag;
    
    if(K > healthCentersAmount) K = healthCentersAmount;
    
    for(int i = 0; i < K; i++){

        healthCenterX = atof(getHealthCenterX((**(nearHealthCenters + i)).healthCenter));
        healthCenterY = atof(getHealthCenterY((**(nearHealthCenters + i)).healthCenter));
        lineSegmentTag = buildLineSegmentTag(healthCenterX, healthCenterY, house);
        insert(queryElementsList, lineSegmentTag);
        writeHealthCenterCoordinatesOnTxt(txt, i, healthCenterX, healthCenterY, (**(nearHealthCenters + i)).distance);
    }

    freeHouse(house);

    for(int i = 0; i<healthCentersAmount; i++)
        free(*(nearHealthCenters + i));

    free(nearHealthCenters);
}

char* buildBlueHouseTag(House H){

    char* houseTag = (char*) malloc(200 * sizeof(char));
    if(houseTag == NULL)
        return NULL;

    double x = getPointX(getHouseCoordinates(H));
    double y = getPointY(getHouseCoordinates(H));
    double w = getHouseW(H);
    double h = getHouseH(H);

    sprintf(houseTag, "\t<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"white\" stroke-width=\"1\" fill=\"lightblue\" />\n", w, h, x, y);
    return houseTag;
}

void calculateDistanceFromHouseToHealthCenters(House H, NearHealthCenter** nearHealthCenters, int healthCentersAmount){
    
    double healthCenterX, healthCenterY;

    double houseCenterOfMassX = getPointX(getHouseCenterOfMass(H));
    double houseCenterOfMassY = getPointY(getHouseCenterOfMass(H));

    for(int i = 0; i<healthCentersAmount; i++){
        healthCenterX = atof(getHealthCenterX( (**(nearHealthCenters + i)).healthCenter ));
        healthCenterY = atof(getHealthCenterY( (**(nearHealthCenters + i)).healthCenter ));
        
        (**(nearHealthCenters + i)).distance = sqrt(pow((healthCenterX - houseCenterOfMassX), 2) + pow((healthCenterY - houseCenterOfMassY), 2));
    }
}

int compareNearHealthCenters(Info Hc1, Info Hc2){

    NearHealthCenter* hc1 = (NearHealthCenter*) Hc1;
    NearHealthCenter* hc2 = (NearHealthCenter*) Hc2;

    if(hc1->distance > hc2->distance)
        return 1;

    else if(hc1->distance < hc2->distance)
        return -1;

    else
        return 0;
}

char* buildLineSegmentTag(double x, double y, House H){

    char* lineSegmentTag = (char*) malloc(200 * sizeof(char));
    if(lineSegmentTag == NULL) return NULL;

    double houseCenterOfMassX = getPointX(getHouseCenterOfMass(H));
    double houseCenterOfMassY = getPointY(getHouseCenterOfMass(H));

    sprintf(lineSegmentTag, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"0.8\" stroke-dasharray=\"5,5\"/>", houseCenterOfMassX, houseCenterOfMassY, x, y);
    return lineSegmentTag;
}

void writeHealthCenterCoordinatesOnTxt(File txt, int i, double x, double y, double distance){
    i++;
    fprintf(txt, "Posto de saude (%d) - x: %.2lf, y: %.2lf, distancia: %.2lf.\n\n", i, x, y, distance);
}