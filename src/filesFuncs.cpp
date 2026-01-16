#include "filesFuncs.h"
#include <stdio.h>
#include <string.h>
#include "constants.h"

int getNumberOfScores()
{
    FILE* scoresFile = fopen("scores.txt", "r");
    if(scoresFile == nullptr) 
    {
        printf("no such file\n");
        return 0;
    }
    int size;
    fscanf(scoresFile, "%d", &size);
    fclose(scoresFile);
    return size;
}
Score* getScoresFromFile()
{
    FILE* scoresFile = fopen("scores.txt", "r");
    if(scoresFile == nullptr) 
    {
        printf("no such file\n");
        return nullptr;
    }

    int size;
    fscanf(scoresFile, "%d", &size);

    Score* scores = new Score[size];
    int currScore;
    for(int i = 0; i < size; i++)
    {
        fscanf(scoresFile, "%s %d", scores[i].nickname, &currScore);
        scores[i].score = currScore;
    }
    fclose(scoresFile);
    // for (int i = 0; i < size; i++)
    // {
    //     printf("%s - %d\n", scores[i].nickname, scores[i].score);
    // }
    
    return scores;
}

void addScore(Score* scoreToAdd)
{
    // printf("%s %d\n", scoreToAdd->nickname, scoreToAdd->score);

    Score* scores = getScoresFromFile();
    FILE* scoresFile;
    
    int size;
    if(scores == nullptr) size = 0;
    else 
    {
        scoresFile = fopen("scores.txt", "r");
        fscanf(scoresFile, "%d", &size);
        fclose(scoresFile);
    }
    
    // printf("Number of scores: %d\n", size);

    scoresFile = fopen("scores.txt", "w");
    fprintf(scoresFile, "%d\n", (size+1));
    // printf("%d\n", (size == 0));
    if(size == 0)
    {
        fprintf(scoresFile, "%s %d\n", scoreToAdd->nickname, scoreToAdd->score);
        fclose(scoresFile);
        return;
    }

    bool hasPrintedNewScore = false;
    for(int i = 0; i < size; i++)
    {
        if(!hasPrintedNewScore && scoreToAdd->score > scores[i].score)
        {
            hasPrintedNewScore = true;
            fprintf(scoresFile, "%s %d\n", scoreToAdd->nickname, scoreToAdd->score);
        }
        fprintf(scoresFile, "%s %d\n", scores[i].nickname, scores[i].score);
    }
    if(!hasPrintedNewScore) fprintf(scoresFile, "%s %d\n", scoreToAdd->nickname, scoreToAdd->score);

    fclose(scoresFile);
    // delete scoreToAdd;
    delete[] scores;
}

void updateScores(Score* scoresToDisplay, int page)
{
    int numberOfScores = getNumberOfScores();
    if(page * SCORES_PER_PAGE > numberOfScores) return;

    Score* allScores = getScoresFromFile();
    for (int i = 0; i < SCORES_PER_PAGE; i++)
    {
        if((SCORES_PER_PAGE * page) + i > numberOfScores) break;
        strcpy(scoresToDisplay[i].nickname, allScores[(SCORES_PER_PAGE * page) + i].nickname);
        scoresToDisplay[i].score = allScores[(SCORES_PER_PAGE * page) + i].score;
    }
    delete[] allScores;
}
