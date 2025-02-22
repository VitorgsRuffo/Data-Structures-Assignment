#ifndef CITY_H
#define CITY_H

#include "../../include/dataStructure.h"
#include "./city.h"

/*
* TAD cidade que vai conter a estrutura das entidades que serao desenhadas em um arquivo svg.
*/
typedef void* City;

/*
* Pré-Condição: nenhuma.
* Pós-Condição: retorna um TAD cidade com as estruturas das entidades vazias.
*/
City createCity();

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de circulos presente no TAD cidade.
*/
PQuadTree getCircles(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de retangulo presente no TAD cidade.
*/
PQuadTree getRectangles(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de textos presente no TAD cidade.
*/
PQuadTree getTexts(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de quadras presente no TAD cidade.
*/
PQuadTree getBlocks(City Ct);

/* 
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de quadras presente no TAD cidade.
*/
HashTable* getBlocksTable(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de hidrantes presente no TAD cidade.
*/
PQuadTree getHydrants(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de rádio-bases presente no TAD cidade.
*/
PQuadTree getBaseRadios(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de Semáfaros presente no TAD cidade.
*/
PQuadTree getSemaphores(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de postos de saude presente no TAD cidade.
*/
PQuadTree getHealthCenters(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de endereços de covid presente no TAD cidade.
*/
PQuadTree getCovidAddresses(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de regioes presente no TAD cidade.
*/
List getRegions(City Ct);

/* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de tipos de estabelecimentos comerciais presente no TAD cidade.
*/
HashTable* getEstablishmentTypes(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a tabela hash de estabelecimentos comerciais presente no TAD cidade.
*/
HashTable* getEstablishmentsTable(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a arvore de estabelecimentos comerciais presente no TAD cidade.
*/
PQuadTree getEstablishmentsTree(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de estabelecimentos comerciais presente no TAD cidade.
*/
HashTable* getEstablishmentsTable(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de casas presente no TAD cidade.
*/
PQuadTree getHousesTree(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de pessoas presente no TAD cidade.
*/
HashTable* getPeople(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a arvore de casas presente no TAD cidade.
*/
PQuadTree getHousesTree(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a hash table de casas presente no TAD cidade.
*/
HashTable* getHousesTable(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura que representa o sistema viario da cidade.
*/
Graph getRoadSystem(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade e uma instancia de um sistema viario.
* Pós-Condição: define o sistema viario passado como sendo o sistema viario da cidade.
*/
void setRoadSystem(City Ct, Graph roadSystem);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura que representa as intersecoes de rua da cidade.
*/
PQuadTree getRoadIntersections(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia do grafo que representa a ciclovia da cidade.
*/
Graph getBikePath(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade e uma instancia de uma ciclovia.
* Pós-Condição: define a ciclovia passada como sendo a ciclovia da cidade.
*/
void setBikePath(City Ct, Graph bikePath);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia do ponteiro para os registradores de referencias geograficas.
*/
Point* getLocations(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: retorna uma referencia para a estrutura de elementos de query presente no TAD cidade.
*/
List getQueryElements(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade e uma referencia para uma string que contenha o tipo de um elemento.
* Pós-Condição: retorna a estrutura de elementos cujo tipo foi passado por parametro.
*/
DataStructure getDataStructureByElementType(City Ct, char* elementType);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade, um id de um elemento (figura ou texto) a ser procurado nas estruturas do tad cidade, e um ponteiro para guardar o tipo da figura quando a encontrarmos (se encontrarmos).
* Pós-Condição: percorre as estruturas de figuras e a estrutura de texto em busca de um elemento que tenha o id especificado, se for encontrado retornamos o seu no e salvamos seu tipo no ponteiro passado, se nao for retornamos NULL.
*/
Node searchForFigureOrTextElementByIdentifier(City Ct, char* idToSearch, char* figureElementType);


/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade, um id de um elemento urbano a ser procurado nas estruturas do tad cidade, e um ponteiro para guardar o tipo do elemento quando o encontrarmos (se encontrarmos).
* Pós-Condição: percorre as estruturas de elementos urbanos em busca de um no cuja informacao tenha o id especificado, se for encontrado retornamos esse no e salvamos seu tipo dessa informacao no ponteiro passado, se nao for retornamos NULL.
*/
Node searchForUrbanElementByIdentifier(City Ct, char* idToSearch, char* urbanElementType);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade, um cep de uma quadra a ser procurada.
* Pós-Condição: percorre a estrutura de quadras em busca de um no cuja informacao tenha o cep especificado, se for encontrado retornamos esse no, se nao for retornamos NULL.
*/
Node searchForBlockByCep(City Ct, char* cepToSearch);


/*
* Pré-Condição: requer o endereco de uma instancia de cidade.
* Pós-Condição: imprimir na saida padrão essa variavel.
*/
void printCity(City Ct);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD cidade.
* Pós-Condição: libera a memoria usada pela instancia de cidade que foi passada.
*/
void freeCity(City Ct);

#endif