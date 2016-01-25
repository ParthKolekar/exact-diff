#include<stdio.h>
#include<sys/stat.h>

int main(const int argc, const char ** argv) {
    if (argc != 3) 
        return -1;
    struct stat statstruct;
    if (stat(argv[1], &statstruct) == -1) 
        return -1;
    off_t size1 = statstruct.st_size;
    if (stat(argv[2], &statstruct) == -1)
        return -1;
    off_t size2 = statstruct.st_size;
    if (size1 != size2) {
        return -1;
    }
    FILE *f1 = fopen(argv[1], "r");
    if (!f1) 
        return -1;
    FILE *f2 = fopen(argv[2], "r");
    if (!f2)
        return -1;
    char ch1, ch2;
    fscanf(f1, "%c", &ch1); 
    fscanf(f2, "%c", &ch2);
    while(ch1 == ch2) {
        if (feof(f1) && feof(f2)) {
            fclose(f1);
            fclose(f2);
            return 0;
        }
        if ((feof(f1) && !feof(f2)) || (!feof(f1) && feof(f2))) {
            fclose(f1);
            fclose(f2);
            return -1;
        }
        fscanf(f1, "%c", &ch1); 
        fscanf(f2, "%c", &ch2);
    }
    if(!feof(f1) || !feof(f2)) //once more just in case
    {
        fclose(f1);
        fclose(f2);
        return -1;
    }
    fclose(f1);
    fclose(f2);
    return 0;
}

