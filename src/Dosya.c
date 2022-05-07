#include "Dosya.h"

static int linePointerKisi = 0;
static int linePointerSayi = 0;
static boolean kisilerResult = false;

Dosya new_Dosya()
{
    Dosya this;
    this = (Dosya)malloc(sizeof(struct DOSYA)); 

    this->readKisi = &readKisi;
    this->readSayi = &readSayi;  
    this->isKisilerFinished = &isKisilerFinished;   
    this->delete = &delete_Dosya;

    return this;
}

char* readKisi()
{
    FILE *fileptr;
    char* line = NULL;
    size_t len = 0;
    size_t read;
    
    fileptr = fopen("C:\\Users\\ahmet\\OneDrive\\Desktop\\PDP Odev2\\Kisiler.txt", "r");

    if (NULL == fileptr)
        printf("Kisiler.txt can't be opened");

    int i = 0;
    
    while (getline(&line, &len, fileptr) != -1) {     

        if (i == linePointerKisi)
        {                  
            linePointerKisi++;
            fclose(fileptr);
            return line;
        }
            
        i++;   
        
        if (feof(fileptr))
        {
            kisilerResult = true;
            //printf("\nEOF, linePointerKisi: %d\n", linePointerKisi);
        }
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

    fileptr = fopen("C:\\Users\\ahmet\\OneDrive\\Desktop\\PDP Odev2\\Sayilar.txt", "r");

    if (NULL == fileptr) 
        printf("Sayilar.txt can't be opened\nlinePointerSayi: %d", linePointerSayi);
    
        

    int i = 0;

    while (fscanf(fileptr, "%hu", &number))
    {    
        if (feof(fileptr))
        {
            printf("\nEnd of sayilar.txt and i = %d\n", i);
            linePointerSayi = 0;
            fclose(fileptr);
            return number;
            
        }
        else if (i == linePointerSayi)
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

boolean isKisilerFinished() { return kisilerResult; }

void delete_Dosya(const Dosya this)
{
    if (this == NULL) return;
    free(this);
}


