#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "Players_data.h"

typedef struct player
{
    int playerID;
    char name[50];
    char teamName[50];
    char role[50];
    int totalRuns;
    float battingAvg;
    float strikeRate;
    int wickets;
    float economyRate;
    float performanceIndex;
    struct player *nextPlayer;
}player;

typedef struct team
{
    int teamId;
    char teamName[50];
    int totalPlayers;
    float avgBattingStrike;
    struct player *players;
    struct team *nextTeam;
}team;

team *teams=NULL;
team* teamArray[10];
int teamArraySize=0;

void initTeams();
void initPlayers();
void computeTeamsAvgStrikeRates();
void addPlayerToTeam();
void displayPlayersOfTeam();
void displayTeamsByAvgBattingSR();
void displayTopKPlayersOfTeam();
void displayAllPlayersByPerformanceIndex();
void freeTeams(team *head);
void freePlayers(player *head);
team *findTeam(const char *name);
player *fetchPlayer(Player p);
void sortByAvgBattingSR(team *teamArray[],int teamArraySize);
char* getRole(int role);
void collectPlayersOfTeam(int teamID,player *playerArray[],int* playerArraySize,char *roleStr);
void sortPlayersOfTeam(player *playerArray[],int playerArraySize);
void collectPlayersAllTeams(player *playerArray[], int *playerArraySize, char *roleStr);

int main()
{
    initTeams();
    initPlayers();
    computeTeamsAvgStrikeRates();

    while(1)
    {
        int choice;
        printf("\n\n");
        printf("=====================================================================================\n");
        printf("ICC ODI Player Performance Analyzer\n");
        printf("=====================================================================================\n");
        printf("1. Add Player to Team\n");
        printf("1. Display Players of a specific team.\n");
        printf("2. Display Teams by Average Batting Strike Rate.\n");
        printf("3. Display Top K Players of a Specific Team by Role.\n");
        printf("4. Display all Players of specific role Across All Teams by performance index.\n");
        printf("5. Exit.\n");
        printf("=====================================================================================\n");
        printf("Enter you choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: addPlayerToTeam();break;
            case 2: displayPlayersOfTeam(); break;
            case 3: displayTeamsByAvgBattingSR();break;
            case 4: displayTopKPlayersOfTeam();break;
            case 5: displayAllPlayersByPerformanceIndex();break;
            case 6: freeTeams(teams);exit(0);
        }
    }
}

void initTeams()
{
    team *head = NULL;
    team *tail = NULL;

    for (int i = 0; i < teamCount; ++i) {
        team *node = malloc(sizeof(team));
        if (!node) {
            printf("Memory not allocated!\n");
            return;
        }

        node->teamId = i + 1;
        strncpy(node->teamName, Teams[i], sizeof(node->teamName) - 1);
        node->teamName[sizeof(node->teamName) - 1] = '\0';

        node->totalPlayers = 0;
        node->avgBattingStrike = 0;
        node->players = NULL;
        node->nextTeam = NULL;

        if (head == NULL) {
            head = tail = node;
        } else {
            tail->nextTeam = node;
            tail = node;
        }
    }

    teams = head; 

    team *temp=teams;
    while(temp!=NULL)
    {
        teamArray[teamArraySize++]=temp;
        temp=temp->nextTeam;
    }
}

void initPlayers()
{
    for(int i=0;i<playerCount;i++)
    {
        Player p=players[i];

        team *currTeam=findTeam(p.team);
        if (currTeam == NULL)
        {
            printf("Team not found for player: %s\n", p.name);
            continue;
        }
        player *currPlayer=fetchPlayer(p);
        if (currTeam->players == NULL) 
        {
            currTeam->players = currPlayer;
        } 
        else 
        {
            player *temp = currTeam->players;
            while (temp->nextPlayer != NULL)
                temp = temp->nextPlayer;
            temp->nextPlayer = currPlayer;
        }
        currTeam->totalPlayers++;
    }
}

void computeTeamsAvgStrikeRates()
{
    team *currTeam = teams;
    while (currTeam != NULL)
    {
        float sumSR = 0.0;
        int count = 0;
        player *currPlayer = currTeam->players;
        while (currPlayer != NULL)
        {
            if (strcmp(currPlayer->role, "Batsman") == 0 || strcmp(currPlayer->role, "All-rounder") == 0)
            {
                sumSR += currPlayer->strikeRate;
                count++;
            }
            currPlayer = currPlayer->nextPlayer;
        }
        if (count > 0)
            currTeam->avgBattingStrike = sumSR / count;
        else
            currTeam->avgBattingStrike = 0;
        currTeam = currTeam->nextTeam;
    }
}

void addPlayerToTeam()
{
    Player newPlayer;
    printf("Enter Player Details: \n");
    printf("Enter Player ID: ");
    scanf("%d", &newPlayer.id);
    printf("Enter Player Name: ");
    scanf("%s", newPlayer.name);
    printf("Enter Team Name: ");
    scanf("%s", newPlayer.team);
    printf("Enter Role (Batsman/Bowler/All-rounder): ");
    scanf("%s", newPlayer.role);
    printf("Enter Total Runs: ");
    scanf("%d", &newPlayer.totalRuns);
    printf("Enter Batting Average: ");
    scanf("%f", &newPlayer.battingAverage);
    printf("Enter Strike Rate: ");
    scanf("%f", &newPlayer.strikeRate);
    printf("Enter Wickets: ");
    scanf("%d", &newPlayer.wickets);
    printf("Enter Economy Rate: ");
    scanf("%f", &newPlayer.economyRate);

    team *currTeam = findTeam(newPlayer.team);
    if(currTeam == NULL)
    {
        printf("Team not found! Cannot add player.\n");
        return;
    }

    player *newNode = fetchPlayer(newPlayer);
    if(currTeam->players == NULL)
    {
        currTeam->players = newNode;
    }
    else
    {
        player *temp = currTeam->players;
        while(temp->nextPlayer != NULL)
            temp = temp->nextPlayer;

        temp->nextPlayer = newNode;
    }
    currTeam->totalPlayers++;
    computeTeamsAvgStrikeRates();
    printf("Player successfully added to Team %s!\n",currTeam->teamName);
}

void displayPlayersOfTeam()
{
    int teamID;
    printf("Enter Team ID: ");
    scanf("%d",&teamID);
    team *currTeam=teams;
    while(currTeam!=NULL)
    {
        if(teamID==currTeam->teamId)
        {
            player *currPlayer=currTeam->players;
            printf("=====================================================================================\n");
            printf("ID\tNAME\t\tROLE\t\tRUNS\tAVG\tSR\tWKTS\tER\tPERFORMANCE INDEX\n");
            printf("=====================================================================================\n");
            while(currPlayer!=NULL)
            {
                printf("%d\t%s\t\t%s\t\t%d\t%.2f\t%.2f\t%d\t%.2f\t%.2f\n",
                    currPlayer->playerID,
                    currPlayer->name,
                    currPlayer->role,
                    currPlayer->totalRuns,
                    currPlayer->battingAvg,
                    currPlayer->strikeRate,
                    currPlayer->wickets,
                    currPlayer->economyRate,
                    currPlayer->performanceIndex);

                currPlayer=currPlayer->nextPlayer;
            }
            printf("=====================================================================================\n");
            printf("Total Players: %d\n",currTeam->totalPlayers);
            printf("Average Batting Strike Rate: %.2f\n",currTeam->avgBattingStrike);
            return;
        }
        currTeam=currTeam->nextTeam;
    }
    printf("Team not found!\n");
    return;
}

void displayTeamsByAvgBattingSR()
{

    sortByAvgBattingSR(teamArray,teamArraySize);
    printf("=====================================================================================\n");
    printf("ID\tTeam Name\t\tAvg Bat SR\tTotal Players\n");
    printf("=====================================================================================\n");
    for (int i = 0; i < teamArraySize; i++)
    {
        printf("%d\t%s\t%.2f\t%d\n",
            teamArray[i]->teamId,
            teamArray[i]->teamName,
            teamArray[i]->avgBattingStrike,
            teamArray[i]->totalPlayers);
    }
    printf("=====================================================================================\n");

}

void displayTopKPlayersOfTeam()
{
    int teamID;
    int role;
    int k;
    printf("Enter Team ID: ");
    scanf("%d",&teamID);
    printf("Enter Role (1-Batsman, 2-Bowler, 3-All-rounder): ");
    scanf("%d",&role);
    printf("Enter number of players: ");
    scanf("%d",&k);

    char* roleStr=getRole(role);
    if(roleStr == NULL)
    {
        printf("Invalid role entered!\n");
        return;
    }

    player *playerArray[20];
    int playerArraySize=0;
    collectPlayersOfTeam(teamID,playerArray,&playerArraySize,roleStr);
    sortPlayersOfTeam(playerArray,playerArraySize);

    printf("=====================================================================================\n");
    printf("Top %d %s of Team %d\n", k, roleStr, teamID);
    printf("=====================================================================================\n");
    printf("ID\tNAME\t\tROLE\t\tRUNS\tAVG\tSR\tWKTS\tER\tPERFORMANCE INDEX\n");
    printf("=====================================================================================\n");
    for(int i=0; i<playerArraySize && i<k; i++)
    {
        printf("%d\t%s\t\t%s\t\t%d\t%.2f\t%.2f\t%d\t%.2f\t%.2f\n\n",
            playerArray[i]->playerID,
            playerArray[i]->name,
            playerArray[i]->role,
            playerArray[i]->totalRuns,
            playerArray[i]->battingAvg,
            playerArray[i]->strikeRate,
            playerArray[i]->wickets,
            playerArray[i]->economyRate,
            playerArray[i]->performanceIndex);
    }

    printf("=====================================================================================\n");
}

void displayAllPlayersByPerformanceIndex()
{
    int role;
    printf("Enter Role (1-Batsman, 2-Bowler, 3-All-rounder): ");
    scanf("%d",&role);
    char *roleStr = getRole(role);
    if(roleStr == NULL)
    {
        printf("Invalid role entered!\n");
        return;
    }

    player *playerArray[200];
    int playerArraySize = 0;

    collectPlayersAllTeams(playerArray, &playerArraySize, roleStr);
    if(playerArraySize == 0)
    {
        printf("No players of role %s found!\n", roleStr);
        return;
    }

    sortPlayersOfTeam(playerArray, playerArraySize);

    printf("=====================================================================================\n");
    printf(" All %s Across All Teams (Sorted by Performance Index)\n", roleStr);
    printf("=====================================================================================\n");
    printf("ID\tNAME\t\tROLE\t\tRUNS\tAVG\tSR\tWKTS\tER\tPERFORMANCE INDEX\n");
    printf("=====================================================================================\n");
    for(int i=0; i<playerArraySize; i++)
    {
        printf("%d\t%s\t\t%s\t\t%d\t%.2f\t%.2f\t%d\t%.2f\t%.2f\n",
            playerArray[i]->playerID,
            playerArray[i]->name,
            playerArray[i]->role,
            playerArray[i]->totalRuns,
            playerArray[i]->battingAvg,
            playerArray[i]->strikeRate,
            playerArray[i]->wickets,
            playerArray[i]->economyRate,
            playerArray[i]->performanceIndex);
    }

    printf("=====================================================================================\n");
}

team *findTeam(const char *name)
{
    team *temp=teams;
    while(temp!=NULL)
    {
        if(strcmp(temp->teamName,name)==0)return temp;
        temp=temp->nextTeam;
    }
    return NULL;
}

player *fetchPlayer(Player p)
{
    player *currPlayer=malloc(sizeof(player));
    currPlayer->playerID=p.id;
    strcpy(currPlayer->name,p.name);
    strcpy(currPlayer->teamName,p.team);
    strcpy(currPlayer->role,p.role);
    currPlayer->totalRuns=p.totalRuns;
    currPlayer->battingAvg=p.battingAverage;
    currPlayer->strikeRate=p.strikeRate;
    currPlayer->wickets=p.wickets;
    currPlayer->economyRate=p.economyRate;
    if(strcmp(p.role,"Batsman")==0)
    {
        currPlayer->performanceIndex=(p.battingAverage*p.strikeRate)/100;
    }
    else if(strcmp(p.role,"Bowler")==0)
    {
        currPlayer->performanceIndex=(p.wickets*2)+(100-p.economyRate);
    }
    else if(strcmp(p.role,"All-rounder")==0)
    {
        currPlayer->performanceIndex=((p.battingAverage*p.strikeRate)/100)+(p.wickets*2);
    }
    currPlayer->nextPlayer=NULL;
    return currPlayer;
}

void sortByAvgBattingSR(team *teamArray[],int teamArraySize)
{
    for (int i = 0; i < teamArraySize - 1; i++)
    {
        for (int j = 0; j < teamArraySize - i - 1; j++)
        {
            if (teamArray[j]->avgBattingStrike < teamArray[j+1]->avgBattingStrike)
            {
                team *temp = teamArray[j];
                teamArray[j] = teamArray[j+1];
                teamArray[j+1] = temp;
            }
        }
    }
}

char* getRole(int role)
{
    switch(role)
    {
        case 1:return "Batsman";
        case 2:return "Bowler";
        case 3:return "All-rounder";
        default: return NULL;
    }
}

void collectPlayersOfTeam(int teamID,player *playerArray[],int *playerArraySize,char *roleStr)
{
    team *currTeam=teams;
    while(currTeam!=NULL)
    {
        if(currTeam->teamId==teamID)
        {
            player *temp=currTeam->players;
            while(temp!=NULL)
            {
                if(strcmp(roleStr,temp->role)==0)
                {
                    playerArray[(*playerArraySize)++]=temp;

                }
                temp=temp->nextPlayer;
            }
            break;
        }
        currTeam=currTeam->nextTeam;
    }   
}

void sortPlayersOfTeam(player *playerArray[],int playerArraySize)
{
    for(int i=0; i<playerArraySize-1; i++)
    {
        for(int j=0; j<playerArraySize-i-1; j++)
        {
            if(playerArray[j]->performanceIndex < playerArray[j+1]->performanceIndex)
            {
                player* tmp = playerArray[j];
                playerArray[j] = playerArray[j+1];
                playerArray[j+1] = tmp;
            }
        }
    }
}

void collectPlayersAllTeams(player *playerArray[], int *playerArraySize, char *roleStr)
{
    team *currTeam = teams;

    while (currTeam != NULL)
    {
        player *temp = currTeam->players;
        while (temp != NULL)
        {
            if (strcmp(temp->role, roleStr) == 0)
            {
                playerArray[(*playerArraySize)++] = temp;
            }
            temp = temp->nextPlayer;
        }
        currTeam = currTeam->nextTeam;
    }
}

void freeTeams(team *head)
{
    team *temp;
    while(head != NULL)
    {
        temp = head;
        freePlayers(head->players);

        head = head->nextTeam;
        free(temp);
    }
}

void freePlayers(player *head)
{
    player *temp;
    while(head != NULL)
    {
        temp = head;
        head = head->nextPlayer;
        free(temp);
    }
}
