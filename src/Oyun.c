#include "Oyun.h"

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
    
    printf("#############################################\n"); printf("");
    printf("##              SANSLI SAYI : %hu           ##\n", lucky_number);
    printf("#############################################\n");
    printf("#############################################\n");          
    printf("##                 TUR: %d                 ##\n", tur);
    printf("##             MASA BAKIYE: %f             ##\n", house);                
    printf("##                                         ##\n");    
    printf("##-----------------------------------------##\n");   
    printf("##              EN ZENGIN KISI             ##\n");   
    printf("##             %s %s %d           ##\n", gambler->getName_surname(),winner, gambler->getNumber());
    printf("##               BAKIYESI: %f            ##\n", gambler->getMoney());
    printf("#############################################\n\n"); 
    
    //system("@cls||clear");

}

void start()
{
    Kisi gambler = new_Kisi();

    Dosya file = new_Dosya();

    
    int ctr = 1;
    
    int kisi_ctr = 0;
    
    while (!file->isKisilerFinished())
    {
        if (!gambler->isMoneyEnough()) {
            gambler->setKisi();
            kisi_ctr++;
        }
        
        setLuckyNumber(file);
        gambler->setBet();

        gambler->balanceMoney(-gambler->getBet()); //bahis yatirilir
        house += gambler->getBet(); //yatirilan bahis masaya eklenir

        printf("The bet is: %f\n", gambler->getBet());
        if (lucky_number == gambler->getNumber()) 
        {
            winner = "wins";
            house -= gambler->getBet() * 10;
            gambler->balanceMoney(gambler->getBet() * 10);

        }
        else
        {
            winner = "loses";
        }
        
     
        screen(gambler);

        ctr++;
        tur++;
    }

    printf("Kisi sayisi: %d", kisi_ctr);

    /*
    The bet is: 385.809887
#############################################
##              SANSLI SAYI : 5           ##
#############################################
#############################################
##                 TUR: 28061                 ##
##             MASA BAKIYE: 48537243.474174             ##
##                                         ##
##-----------------------------------------##
##              EN ZENGIN KISI             ##
##             Henry Hammes             ##
##               BAKIYESI: 900.223069            ##
#############################################
    */


    /*
    * AFTER CHANHING money_percentage to float type
    * 
    The bet is: 385.809742
#############################################
##              SANSLI SAYI : 5           ##
#############################################
#############################################
##                 TUR: 28061                 ##
##             MASA BAKIYE: 48534627.666499             ##
##                                         ##
##-----------------------------------------##
##              EN ZENGIN KISI             ##
##             Henry Hammes loses 7           ##
##               BAKIYESI: 900.222680            ##
#############################################
    */

    /*
    * AFTER REPLACING functions with atof and atol
    
    The bet is: 385.807414
#############################################
##              SANSLI SAYI : 5           ##
#############################################
#############################################
##                 TUR: 28061                 ##
##             MASA BAKIYE: 48534176.613466             ##
##                                         ##
##-----------------------------------------##
##              EN ZENGIN KISI             ##
##             Henry Hammes loses 7           ##
##               BAKIYESI: 900.217249            ##
#############################################
    
    */
    
    gambler->delete(gambler);
}


void delete_Oyun(const Oyun this) 
{
    if (this == NULL) return;
    free(this);

}