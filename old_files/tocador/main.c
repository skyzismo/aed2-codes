#include <stdio.h>
#include "music.h"

int main(int argc, char const *argv[])
{
    /* code */
    type_music *music_1 = new_music("Bliding Lights", "The Weeknd");

    print_music(music_1);
    return 0;
}
