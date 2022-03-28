/*
 *  JUKEBOX ALBUM SUGGESTOR, v0.2
 *
 *  @author: Bruno Pezer
 *  11/03/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define LINECHARS 500   //  Maximum album name length
#define MAXNUM    5     //  Maximum number of digits for the string containing the number of albums.

const char *program_version = "\nJUKEBOX 0.2";
const char *bug_address = "<bruno.pezer@tutanota.com>";

//  Program documentation
static char doc[] = "\nJUKEBOX is a tool for suggesting albums to listen to from the user's collection.\nThe program scans the user's music library which should previously be stored in a text file\nand suggests a random album from the list.\nJUKEBOX is intended for users with large digital libraries of music, in order to help them rediscover\nalbums or artists which can easily be buried and forgotten on their hard drives.\n";
static char usage[] = "\nUSAGE> If JUKEBOX has never been run before, the user must first generate the text file with the list of directories containing music.\nOpen a PowerShell instance and navigate to the directory containing this program, then input the following commands:\n\n\t$Albums = Get-ChildItem -Directory -Recurse\n\t$Albums.Count | Out-File res\\albums -Encoding ASCII\n\t$Albums.Name | Out-File res\\albums -Append -Encoding ASCII\n\nAfter generating the file, copy the full file path and pass it to Jukebox.\n\nEXAMPLE> jukebox <filepath>\n";

void read_file(const char *filename) {
    FILE *cfPtr;
    if ((cfPtr = fopen(filename, "r")) == NULL) {
        puts("Error opening file.");
    } else {
        char album[LINECHARS];
        unsigned int currentline = 1;   //  Line 0 of the file is reserved for the number of directories
        //  Read the first line to obtain the number of directories found
        fgets(album, LINECHARS, cfPtr);
        unsigned int total = atoi(album);
        unsigned int album_suggestion = (rand() % total) + 1;
        while (!feof(cfPtr)) {
            fgets(album, LINECHARS, cfPtr);
            if (currentline == album_suggestion) {
                printf("%s", album);
                break;
            }
            currentline++;
        }
        fclose(cfPtr);
    }
}

//  Converts the user input into lowercase
void parse_str(char *str) {
    for (; *str != '\0'; str++)
        *str = tolower(*str);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if (argc > 1) {
        parse_str(argv[1]);
        if (strcmp(argv[1], "help") == 0) {
            puts(program_version);
            puts(doc);
            puts(usage);
            printf("Send bug reports to %s\n", bug_address);
            return 0;
        } else read_file(argv[1]);
    } else {
        puts("Error. No input file specified.\nPlease type \"jukebox help\" for information.");
    }
}
