#include "Oyun.h"
#include<conio.h>

int tur = 1;
double house = 0;
int lucky_number;
char* winner = "loses";


Oyun new_Oyun()
{
	Oyun this;
	this = (Oyun)malloc(sizeof(struct OYUN));

	this->start = &start;
	this->delete = &delete_Oyun;

	return this;
}
//private method
void setLuckyNumber(Dosya file) 
{
	lucky_number = file->readSayi();
}

//private method
void screen(Kisi gambler) 
{
    
    printf("\n\n\n\n\t\t\t#############################################\n"); printf("");
    printf("\t\t\t##              SANSLI SAYI : %2d           ##\n", lucky_number);
    printf("\t\t\t#############################################\n");
    printf("\t\t\t#############################################\n");          
    printf("\t\t\t##                 TUR: %3d                ##\n", tur);
    printf("\t\t\t##             MASA BAKIYE: %-8.0lf       ##\n", house);                
    printf("\t\t\t##                                         ##\n");    
    printf("\t\t\t##-----------------------------------------##\n");   
    printf("\t\t\t##              EN ZENGIN KISI             ##\n");   
    printf("\t\t\t##              %-20s       ##\n", gambler->getEnZenginKisi());
    printf("\t\t\t##      BAKIYESI: %-8.0lf                 ##\n", gambler->enZenginKisiBakiye());
    printf("\t\t\t##                                         ##\n");
    printf("\t\t\t#############################################\n\n"); 
    
    system("@cls||clear");
    

}

void endScreen() {

    printf("\n\n\n\n\t\t\t#############################################\n");
    printf("\t\t\t##                  TUR: %3d               ##\n", tur-1);
    printf("\t\t\t##           MASA BAKIYE: %-8.0lf         ##\n", house);
    printf("\t\t\t##                                         ##\n");
    printf("\t\t\t## ----------------------------------------##\n");
    printf("\t\t\t##                OYUN BITTI               ##\n");
    printf("\t\t\t##                                         ##\n");
    printf("\t\t\t##                                         ##\n");
    printf("\t\t\t##                                         ##\n");
    printf("\t\t\t#############################################\n\n");

}

void start()
{

    Kisi gambler = new_Kisi();
    Dosya file = new_Dosya();
       
    int kisi_ctr = 0;
    
    int kisi_sayisi = file->countLines() + 1;
    int lucky_number_count = file->countSayilar();
    
    while (tur <= lucky_number_count)
    {
        setLuckyNumber(file);
        kisi_ctr = 0;        
             
        while (kisi_ctr < kisi_sayisi)
        {
            
            gambler->setKisi(kisi_ctr); 
            gambler->setBet();

            if (!gambler->isMoneyEnough()) {
                kisi_ctr++; 
                continue;
            }    
           
            gambler->balanceMoney(-gambler->getBet()); 
            house += gambler->getBet(); 
            
            if (lucky_number == gambler->getNumber())
            {

                house -= gambler->getBet() * 10;
                gambler->balanceMoney(gambler->getBet() * 10);

            }
            else{}
                                 
            kisi_ctr++;
            
            
        }

        screen(gambler);

        tur++;
       
    }
    endScreen();
    //printf("Kisi sayisi: %d", kisi_ctr);

    
    file->delete(file);
    gambler->delete(gambler);
}


void delete_Oyun(const Oyun this) 
{
    if (this == NULL) return;
    free(this);

}