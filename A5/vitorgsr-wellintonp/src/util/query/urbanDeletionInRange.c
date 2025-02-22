#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../input/openInput.h"

typedef char* (*toString)(Info);
typedef char* (*getUrbanElementX)(Info);
typedef char* (*getUrbanElementY)(Info);
typedef char* (*getUrbanElementRadius)(Info);
typedef Point (*getUrbanElementCoordinates)(Info);
typedef void (*freeInfo)(Info);

typedef struct {
    City Ct;
    DataStructure elements;
    Circle circle;
    File txt;
    Rectangle building;
    Circle urbanElement;
    toString urbanElementToString;
    getUrbanElementX getX;
    getUrbanElementY getY;
    getUrbanElementRadius getRadius;
    getUrbanElementCoordinates getCoordinates;
    freeInfo freeUrbanElement;
    List pointsToRemove;
    Graph roadSystem;
    Graph bikePath;
}Variables;


void deleteBlocksInCircle(Variables variables);
void deleteUrbanElementsInCircle(Variables variables);
void deleteHousesInCircle(Variables variables);
void deleteEstablishmentsInCircle(Variables variables);
void deleteStreetsInCircle(Variables variables);
char* buildUrbanElementsDeletionCircleTag(char* x, char* y, char* radius);


void executeUrbanElementsDeletion(char* command, City Ct, File txt){

    char x[20], y[20], r[20];
    sscanf(&command[6], "%s %s %s", x, y, r);

    Variables variables;
    variables.Ct = Ct;

    variables.circle = 
        createCircle("................", r, x, y, "................", "................", "................");

    variables.txt = txt;

    variables.pointsToRemove = createList();

    variables.building = 
        createRectangle("........", "000000.000000000","000000.000000000","000000.000000000","000000.000000000","........", "........", "........");
    
    variables.urbanElement = 
        createCircle("........", "000000.000000000", "000000.000000000", "000000.000000000", "........", "........", "........");


    variables.elements = getBlocks(Ct);
    deleteBlocksInCircle(variables);
    
    variables.elements = getHydrants(Ct);
    variables.urbanElementToString = hydrantToString;
    variables.getX = getHydrantX;
    variables.getY = getHydrantY;
    variables.getRadius = getHydrantRadius;
    variables.freeUrbanElement = freeHydrant;
    variables.getCoordinates = getHydrantCoordinates;
    deleteUrbanElementsInCircle(variables);

    variables.elements = getBaseRadios(Ct);
    variables.urbanElementToString = baseRadioToString;
    variables.getX = getBaseRadioX;
    variables.getY = getBaseRadioY;
    variables.getRadius = getBaseRadioRadius;
    variables.freeUrbanElement = freeBaseRadio;
    variables.getCoordinates = getBaseRadioCoordinates;
    deleteUrbanElementsInCircle(variables);

    variables.elements = getSemaphores(Ct);
    variables.urbanElementToString = semaphoreToString;
    variables.getX = getSemaphoreX;
    variables.getY = getSemaphoreY;
    variables.getRadius = getSemaphoreRadius;
    variables.freeUrbanElement = freeSemaphore;
    variables.getCoordinates = getSemaphoreCoordinates;
    deleteUrbanElementsInCircle(variables);
    
    variables.elements = getHealthCenters(Ct);
    variables.urbanElementToString = healthCenterToString;
    variables.getX = getHealthCenterX;
    variables.getY = getHealthCenterY;
    variables.getRadius = getHealthCenterRadius;
    variables.freeUrbanElement = freeHealthCenter;
    variables.getCoordinates = getHealthCenterCoordinates;
    deleteUrbanElementsInCircle(variables);
    
    variables.elements = getHousesTree(Ct);
    deleteHousesInCircle(variables);

    variables.elements = getEstablishmentsTree(Ct);
    deleteEstablishmentsInCircle(variables);
    
    variables.elements = getRoadIntersections(Ct);
    variables.roadSystem = getRoadSystem(Ct);
    variables.bikePath = getBikePath(Ct);
    deleteStreetsInCircle(variables);
   
    char* circleTag = buildUrbanElementsDeletionCircleTag(x, y, r);
    insert(getQueryElements(Ct), circleTag);
    
    freeCircle(variables.circle);
    freeRectangle(variables.building);
    freeCircle(variables.urbanElement);
    freeList(variables.pointsToRemove, NULL);
}

void deleteBlockIfItsInsideCircle(Info blockInfo, ExtraInfo extraInfo);

void deleteBlocksInCircle(Variables variables){

    //buscando as quadras inteiramente dentro do circulo:
    levelOrderTraversal(variables.elements, deleteBlockIfItsInsideCircle, &variables);

    //removendo as quadras selecionadas da arvore:
    Node currentNode = getFirst(variables.pointsToRemove);
    while(currentNode != NULL){
        
        Info pointToRemove = get(variables.pointsToRemove, currentNode);
        double px = getPointX(pointToRemove);
        double py = getPointY(pointToRemove);

        Info nodeToRemove = getPQuadTreeNode(variables.elements, px, py);
        freeBlock(removePQuadTreeNode(variables.elements, nodeToRemove));

        removeNode(variables.pointsToRemove, currentNode, NULL);
        currentNode = getFirst(variables.pointsToRemove);
    }

}

void deleteBlockIfItsInsideCircle(Info blockInfo, ExtraInfo extraInfo){

    Variables* variables = (Variables*) extraInfo;

    setRectangleX(variables->building, getBlockX(blockInfo));
    setRectangleY(variables->building, getBlockY(blockInfo));
    setRectangleWidth(variables->building, getBlockWidth(blockInfo));
    setRectangleHeight(variables->building, getBlockHeight(blockInfo));
    

    if(isRectangleInsideCircle(variables->circle, variables->building)){

        char* blockString = blockToString(blockInfo);
        fprintf(variables->txt, "\"%s\" foi removido.\n", blockString);
        free(blockString);

        insert(variables->pointsToRemove, getBlockCoordinates(blockInfo));
    }

}


void deleteUrbanElementIfItsInsideCircle(Info element, ExtraInfo extraInfo);

void deleteUrbanElementsInCircle(Variables variables){

    //buscando as elementos urbanos inteiramente dentro do circulo:
    levelOrderTraversal(variables.elements, deleteUrbanElementIfItsInsideCircle, &variables);

    //removendo os elementos urbanos selecionados da arvore:
    Node currentNode = getFirst(variables.pointsToRemove);
    while(currentNode != NULL){
        
        Info pointToRemove = get(variables.pointsToRemove, currentNode);
        double px = getPointX(pointToRemove);
        double py = getPointY(pointToRemove);

        Info nodeToRemove = getPQuadTreeNode(variables.elements, px, py);
        (*(variables.freeUrbanElement))(
            removePQuadTreeNode(variables.elements, nodeToRemove));

        removeNode(variables.pointsToRemove, currentNode, NULL);
        currentNode = getFirst(variables.pointsToRemove);
    }
    //Obs: é necessario remover os nodes da tabela hash que correspondam as mesmas informacoes (caso exista uma tabela hash de quadras.), ou outras de estruturas que apontem para essas mesmas informacoes.
}

void deleteUrbanElementIfItsInsideCircle(Info urbanElement, ExtraInfo extraInfo){

    Variables* variables = (Variables*) extraInfo;
    
    Point urbanElementCoordinates = (*(variables->getCoordinates))(urbanElement);

    char ueX[20], ueY[20];
    sprintf(ueX, "%lf", getPointX(urbanElementCoordinates));
    sprintf(ueY, "%lf", getPointY(urbanElementCoordinates));

    setCircleX(variables->urbanElement, ueX);
    setCircleY(variables->urbanElement, ueY);   

    setCircleRadius(variables->urbanElement, (*(variables->getRadius))(urbanElement));

    if(isCircleInsideCircle(variables->urbanElement, variables->circle)){
        char* urbanElementString = (*variables->urbanElementToString)(urbanElement);
        fprintf(variables->txt, "\"%s\" foi removido.\n\n", urbanElementString);
        free(urbanElementString);

        insert(variables->pointsToRemove, (*variables->getCoordinates)(urbanElement));
    }
}


void deleteHouseIfItsInsideCircle(Info house, ExtraInfo extraInfo);

void deleteHousesInCircle(Variables variables){

    //buscando as casas inteiramente dentro do circulo:
    levelOrderTraversal(variables.elements, deleteHouseIfItsInsideCircle, &variables);

    //removendo as casas selecionadas das estruturas de dados:
    Node currentNode = getFirst(variables.pointsToRemove);
    while(currentNode != NULL){
        
        Info pointToRemove = get(variables.pointsToRemove, currentNode);
        double px = getPointX(pointToRemove);
        double py = getPointY(pointToRemove);

        Info nodeToRemove = getPQuadTreeNode(variables.elements, px, py);
        House houseToRemove = removePQuadTreeNode(variables.elements, nodeToRemove);

        DataStructure* housesTable = getHousesTable(variables.Ct);
        removeHashTableInfo(*housesTable, getHouseCpf(houseToRemove), freeHouse);


        removeNode(variables.pointsToRemove, currentNode, NULL);
        currentNode = getFirst(variables.pointsToRemove);
    }
    //Obs: é necessario remover os nodes de outras de estruturas que apontem para essas mesmas informacoes.
}


void deleteHouseIfItsInsideCircle(Info house, ExtraInfo extraInfo){

    Variables* variables = (Variables*) extraInfo;

    char houseX[10], houseY[10], houseW[10], houseH[10];
    Point houseCoordinates = getHouseCoordinates(house);
    sprintf(houseX, "%.2lf", getPointX(houseCoordinates));
    sprintf(houseY, "%.2lf", getPointY(houseCoordinates));
    sprintf(houseW, "%.2lf", getHouseW(house));
    sprintf(houseH, "%.2lf", getHouseH(house));    

    setRectangleX(variables->building, houseX);
    setRectangleY(variables->building, houseY);
    setRectangleWidth(variables->building, houseW);
    setRectangleHeight(variables->building, houseH);

    if(isRectangleInsideCircle(variables->circle, variables->building)){
        char* houseString = houseToString(house);
        fprintf(variables->txt, "\"%s\" foi removido.\n", houseString);
        free(houseString);

        insert(variables->pointsToRemove, getHouseCoordinates(house));
    }

}


void deleteEstablishmentIfItsInsideCircle(Info establishment, ExtraInfo extraInfo);

void deleteEstablishmentsInCircle(Variables variables){

    //buscando as estabelecimentos inteiramente dentro do circulo:
    levelOrderTraversal(variables.elements, deleteEstablishmentIfItsInsideCircle, &variables);

    //removendo os estabelecimentos selecionados das estruturas de dados:
    Node currentNode = getFirst(variables.pointsToRemove);
    while(currentNode != NULL){
        
        Info pointToRemove = get(variables.pointsToRemove, currentNode);
        double px = getPointX(pointToRemove);
        double py = getPointY(pointToRemove);

        Info nodeToRemove = getPQuadTreeNode(variables.elements, px, py);
        Establishment establishmentToRemove = removePQuadTreeNode(variables.elements, nodeToRemove);

        DataStructure* establishmentsTable = getEstablishmentsTable(variables.Ct);
        removeHashTableInfo(*establishmentsTable, getEstablishmentCnpj(establishmentToRemove), freeEstablishment);


        removeNode(variables.pointsToRemove, currentNode, NULL);
        currentNode = getFirst(variables.pointsToRemove);
        
        //Obs: é necessario remover os nodes de outras de estruturas que apontem para essas mesmas informacoes.
    }

}

void deleteEstablishmentIfItsInsideCircle(Info establishment, ExtraInfo extraInfo){

    Variables* variables = (Variables*) extraInfo;

    char estX[10], estY[10], estW[10], estH[10];
    Point estCoordinates = getEstablishmentCoordinates(establishment);
    sprintf(estX, "%.2lf", getPointX(estCoordinates));
    sprintf(estY, "%.2lf", getPointY(estCoordinates));
    sprintf(estW, "%.2lf", getEstablishmentWidth(establishment));
    sprintf(estH, "%.2lf", getEstablishmentHeight(establishment));    

    setRectangleX(variables->building, estX);
    setRectangleY(variables->building, estY);
    setRectangleWidth(variables->building, estW);
    setRectangleHeight(variables->building, estH);

    if(isRectangleInsideCircle(variables->circle, variables->building)){

        DataStructure* establishmentsTypes = getEstablishmentTypes(variables->Ct);
        Info establishmentType = getHashTableInfo(*establishmentsTypes, getEstablishmentCode(establishment));

        char* estString = establishmentToString(establishment, establishmentType);
        fprintf(variables->txt, "\"%s\" foi removido.\n", estString);
        free(estString);

        insert(variables->pointsToRemove, getEstablishmentCoordinates(establishment));
    }
}


void deleteRoadIntersectionIfItsInsideCircle(Info roadIntersection, ExtraInfo extraInfo);

void deleteStreetsInCircle(Variables variables){
    //buscando as esquinas inteiramente dentro do circulo:
    levelOrderTraversal(variables.elements, deleteRoadIntersectionIfItsInsideCircle, &variables);
    
    //removendo as esquinas selecionados da arvore (+ as ruas associadas a elas):
    Node currentNode = getFirst(variables.pointsToRemove);
    while(currentNode != NULL){
        
        Info pointToRemove = get(variables.pointsToRemove, currentNode);
        double px = getPointX(pointToRemove);
        double py = getPointY(pointToRemove);

        PQuadTreeNode nodeToRemove = getPQuadTreeNode(variables.elements, px, py);
        
        IdedPoint roadIntersection = getPQuadTreeNodeInfo(variables.elements, nodeToRemove);
        char* roadIntersectionId = getIdedPointId(roadIntersection);
        
        //removendo a esquina e todas as ruas que estao ligadas a esquina a ser removida.
        //em outras palavras: removendo todas as arestas que saem ou chegam no vertice a ser removido:
        removeVertex(variables.roadSystem, 1, roadIntersectionId, NULL);
        removeVertex(variables.bikePath, 0, roadIntersectionId, NULL); //os vertices de ambos os grafos sao correspondentes, e, estao associados a mesma informacao, portanto, desalocamos essa informacao apenas uma vez.

        //removendo a intersecao da arvore de intersecao de ruas:
        removePQuadTreeNode(variables.elements, nodeToRemove);
        freeIdedPoint(roadIntersection);

        removeNode(variables.pointsToRemove, currentNode, NULL);
        currentNode = getFirst(variables.pointsToRemove);
    }
    //Obs: é necessario remover os nodes da tabela hash que correspondam as mesmas informacoes (caso exista uma tabela hash de quadras.), ou outras de estruturas que apontem para essas mesmas informacoes.
}

void deleteRoadIntersectionIfItsInsideCircle(Info roadIntersection, ExtraInfo extraInfo){

    Variables* variables = (Variables*) extraInfo;
    
    Point roadIntersectionCoordinates = getIdedPointCoordinates(roadIntersection);

    if(isPointInsideCirc(variables->circle, roadIntersectionCoordinates)){
        char* vertexString = idedPointToString(roadIntersection);
        fprintf(variables->txt, "O vertice \"%s\" foi removido.\n\n", vertexString);
        free(vertexString);

        insert(variables->pointsToRemove, roadIntersectionCoordinates);
    }
}


char* buildUrbanElementsDeletionCircleTag(char* x, char* y, char* radius){
    char* circleTag = (char*) malloc(300 * sizeof(char));
    if(circleTag == NULL) return NULL;

    sprintf(circleTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"#6C6753\" stroke-width=\"3\" fill=\"#CCFF00\" fill-opacity=\"0.5\" />\n", x, y, radius);
    return circleTag;
}