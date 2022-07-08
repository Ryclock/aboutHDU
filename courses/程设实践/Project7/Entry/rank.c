#include "snake.h"
#include "rank.h"

Score rank[RANKING_MAX];

void PrintRanking(void)
{
    for (int i = 0; i < RANKING_MAX; i++)
    {
        GotoXY(MAP_WIDTH + 10, 10 + i * 2);
        printf("Rank %d - Score: %d", i + 1, rank[i]);
    }
}
void ChangeRanking(int score)
{
    int tempRank = -1;
    for (int i = 0; i < RANKING_MAX; i++)
    {
        if (rank[i] == score)
        {
            break;
        }
        if (rank[i] < score)
        {
            tempRank = i;
            break;
        }
    }
    if (tempRank != -1)
    {
        for (int i = RANKING_MAX - 1; i > tempRank; i--)
        {
            rank[i] = rank[i - 1];
        }
        rank[tempRank] = score;
    }
}