#ifndef MUSIC_H
#define MUSIC_H

typedef struct type_music type_music;

type_music *new_music(char *musicName, char *artistName);

void print_music(type_music *music);

#endif