#include "filesFuncs.h"
#include <stdio.h>

Score* getScoresFromFile()
{
    FILE* scoresFile = fopen("scores.txt", "r");
    if(scoresFile == nullptr) return nullptr;

    int size;
    fscanf(scoresFile, "%d", &size);

    Score* scores = new Score[size];
    for(int i = 0; i < size; i++)
    {
        fprintf(scoresFile, "%s %d", scores[i].nickname, scores[i].score);
    }
    fclose(scoresFile);
    return scores;
}

void addScore(Score* score)
{
    Score* scores = getScoresFromFile();
    FILE* scoresFile = fopen("scores.txt", "r");
    if(scoresFile == nullptr) return;

    int size;
    fprintf(scoresFile, "%d", size);
    fclose(scoresFile);

    scoresFile = fopen("scores.txt", "w");
    fprintf(scoresFile, "%d\n", (size+1));

    bool hasPrintedNewScore = false;
    for(int i = 0; i < size; i++)
    {
        if(!hasPrintedNewScore && score->score > scores[i].score)
        {
            hasPrintedNewScore = true;
            fprintf(scoresFile, "%s %d\n", score->nickname, score->score);
            i--;
        }
        fprintf(scoresFile, "%s %d\n", scores[i].nickname, score[i].score);
    }
    fclose(scoresFile);
}