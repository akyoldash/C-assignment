#include "Dosya.h"

static int linePointerKisi = 0;
static int linePointerSayi = 0;

int countLines();

Dosya new_Dosya()
{
    Dosya this;
    this = (Dosya)malloc(sizeof(struct DOSYA)); 

    this->readKisi = &readKisi;
    this->readSayi = &readSayi;  
    this->countLines = &countLines;
    this->countSayilar = &countSayilar;
    this->delete = &delete_Dosya;

    

    return this;
}

char* readKisi()
{
    FILE *fileptr;
    char* line = NULL;
    size_t len = 0;
    size_t read;
    
    fileptr = fopen("Kisiler.txt", "r");

    if (NULL == fileptr)
        printf("Kisiler.txt can't be opened");

    int i = 0;

    while (getline(&line, &len, fileptr) != -1) {     

        if (linePointerKisi == i) {
            linePointerKisi++;
            fclose(fileptr);
            return line;
        }     
        i++;       
     
    }

    fclose(fileptr);

    return NULL;

    
}

short readSayi()
{

    FILE* fileptr;
    unsigned short number = 0;
    size_t len = 0;
    size_t read;

    fileptr = fopen("Sayilar.txt", "r");

    if (NULL == fileptr) 
        printf("Sayilar.txt can't be opened\nlinePointerSayi: %d", linePointerSayi);
    
        
    int i = 0;

    while (fscanf(fileptr, "%hu", &number))
    {    
        
      
        if (i == linePointerSayi)
        {
            linePointerSayi++;
            fclose(fileptr);
            return number;
            
        }
        i++;
       
    }

    fclose(fileptr);

    return 0;
}



int countLines() { 
    FILE* fileptr;
    int count_lines = 0;

    fileptr = fopen("Kisiler.txt", "r");

    for (char c = getc(fileptr); c != EOF; c = getc(fileptr))
        if (c == '\n')
            count_lines++;

    fclose(fileptr); 

    return count_lines; 
}

int countSayilar() {

    FILE* fileptr;
    int count_lines = 0;

    fileptr = fopen("Sayilar.txt", "r");

    for (char c = getc(fileptr); c != EOF; c = getc(fileptr))
        if (c == '\n')
            count_lines++;

    fclose(fileptr);

    return count_lines+1;

}

void delete_Dosya(const Dosya this)
{
    if (this == NULL) return;
    free(this);
}


