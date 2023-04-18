#include "music.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct type_music
{
    char musicName[30];
    char artistName[30];
};

type_music *new_music (char *musicName, char *artistName){

    type_music *music = malloc(sizeof(type_music));

    strcpy(music->musicName, musicName);
    strcpy(music->artistName, artistName);

    return music;
}

void print_music(type_music *music){
    printf("Music: ( Name: %s, Artist: %s )\n",
        music->musicName,
        music->artistName
    );
}
