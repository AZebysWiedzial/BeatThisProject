#ifndef FILESFUNCS_H
#define FILESFUNCS_H
#include "constants.h"

typedef struct
{
    char nickname[128];
    int score;
} Score;

int getNumberOfScores();
Score* getScoresFromFile();
void addScore(Score* score);
void updateScores(Score* scoresToDisplay, int page);



#endif