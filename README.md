# Jukebox Album Suggester
JUKEBOX is a basic command line program for Windows to generate listening suggestions for users with large digital music libraries. 
The program reads the user's collection from a text file, selecting one at random and printing it on screen. A few simple PowerShell
commands can be used to automatically generate the list of albums or directories containing music. These commands search exclusively for
directories, not individual files. To aid the program, the number of items is included at the top of this file. The program reads 
the number of directories found from the top of the list and generates a random number between 1 and the total. 
It then reads through the list line by line until the corresponding album has been reached and prints it to the command line.

## Generating the List of Albums
```powershell
# Change the contents of the quotation marks to find specifically named directories
# otherwise remove the -Filter switch entirely.
$Dirs = Get-ChildItem -Directory -Recurse -Filter "[*]*"
# Writes the number of items to the specified file
$Dirs.Count | Out-File <path>\<filename> -Encoding ASCII
#	Appends the directory names in the specified file
$Dirs.Name  | Out-File <path>\<filename> -Append -Encoding ASCII
```

