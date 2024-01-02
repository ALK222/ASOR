#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>
#include <unistd.h>

int leerDirectorio(char *parent, char *path, int tab);

void printWithTab(char **args, int format, int tabs)
{
    const int tabSize = 3;

    for (int i = 0; i < tabs; ++i)
    {
        printf("|%0*s", 3, " ");
    }

    switch (format)
    {
    case 0:
        printf("%s/\n", args[0]);
        break;
    case 1:
        printf("%s%s\n", args[0], args[1]);
        break;
    case 2:
        printf("%s -> %s\n", args[0], args[1], link);
        break;
    case 3:
        printf("%d kb\n", args[0]);
        break;

    default:
        break;
    }
}

int printData(char *parent, char *path, int tab)
{
    char aux[sizeof(parent) + sizeof(path) + 1];
    strcpy(aux, parent);
    strcat(aux, "/");
    strcat(aux, path);
    struct stat sb;
    if (lstat(aux, &sb) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    switch (sb.st_mode & __S_IFMT)
    {
    case __S_IFDIR:
        leerDirectorio(parent, path, tab);
        return 0;
    case __S_IFLNK:
        char link[100];
        readlink(path, link, sizeof(link) - 1);
        char *args[2] = {path, link};
        printWithTab(args, 2, tab);
        return sb.st_size;
        break;
    case __S_IFREG:

        char *exec = "";
        if (sb.st_mode & S_IXUSR)
        {
            exec = "*";
        }
        char *args2[2] = {path, exec};
        printWithTab(args2, 1, tab);
        return sb.st_size;
    default:
        printf("unknown?\n");
        break;
    }
}

int leerDirectorio(char *parent, char *path, int tab)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d == NULL)
    {
        printf("%s not a dir\n", path);
        return -1;
    }
    int totalTam = 0;
    char *args[1] = {path};
    printWithTab(args, 0, tab);
    int newTab = tab + 1;
    while ((dir = readdir(d)) != NULL)
    {
        if (strcmp(dir->d_name, parent) == 0 || strcmp(dir->d_name, "..") == 0 || strcmp(dir->d_name, path) == 0)
        {
            continue; // Skip parent and current directory entries
        }

        totalTam += printData(path, dir->d_name, newTab);
    }
    closedir(d);
    char *arg2[1] = {totalTam + '0'};
    printWithTab(arg2, 3, tab);

    return 0;
}

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        printf("usage: %s <dir>\n", argv[0]);
        return -1;
    }

    if (leerDirectorio("", argv[1], 0) == -1)
    {
        return -1;
    }
    return 0;
}