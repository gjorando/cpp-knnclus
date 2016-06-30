#ifndef _TESTEKNN_FUNCTIONS_H_
#define _TESTEKNN_FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <eknnwindev.h>

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#define CLEAR_SCREEN() (system("clear"))
#endif
#if defined(_WIN32) || defined(_WIN64)
#define CLEAR_SCREEN() (system("cls"))
#endif

void displayMenu(int *choice, int max, int mode);
void printAbout();
void printState(EkNNSystem *f);
void initRandomSystem(EkNNSystem **f);
void deleteSystem(EkNNSystem *f);
void clusterize(EkNNSystem *f);
void exportToCSV(EkNNSystem *f);
void importFromDataset(EkNNSystem **f);

#endif //_TESTEKNN_FUNCTIONS_H_
