#ifndef FILEFUNCS_H
#define FILEFUNCS_H

typedef struct
{
    const char* nickname;
    int score;
} Score;

Score* getScoresFromFile();
void addScore(Score* score);

#endif