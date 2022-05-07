#include "Kisi.h"
#include<string.h>

char* kisi ="";
char* kisiArray[4];
char* name_surname;
double money;
float money_percentage;
int number;
double bet;

Kisi new_Kisi()
{
	Kisi this;
	this = (Kisi)malloc(sizeof(struct KISI));

	this->setKisi = &setKisi;
	this->getName_surname = &getName_surname;
	this->getNumber = &getNumber;
	this->getMoney = &getMoney;
	this->getBet = &getBet;
	this->setBet = &setBet;
	this->balanceMoney = &balanceMoney;
	this->isMoneyEnough = &isMoneyEnough;
	this->delete = &delete_Kisi;

	setKisi();

	return this;
}

//private method
void splitKisi()
{
	//printf("splitKisi()\n");
	if (kisi != "")
	{
		int i = 0;
		char* p = strtok(kisi, "#");

		while (p != NULL)
		{
			kisiArray[i++] = p;
			p = strtok(NULL, "#");
		}
		//printf("\nend of splitKisi()");

	}
}

void setKisi()
{
	//printf("setkisi()\n");
	Dosya file = new_Dosya();
	kisi = file->readKisi();
	//printf("kisi: %s\n", kisi);
	splitKisi();
	
	name_surname = (char*)malloc(sizeof(kisiArray[0]));
	name_surname = kisiArray[0];
	

	name_surname = kisiArray[0];
	//printf("\nbefore sscanf\n");
	char* eptr;
	
	//money = strtod(kisiArray[1], &eptr);
	//money_percentage = strtof(kisiArray[2], &eptr);
	money = atol(kisiArray[1]);
	money_percentage = atof(kisiArray[2]);
	number = atoi(kisiArray[3]);

	printf("\nname_surname: %s\nmoney: %f\nmoney_percentage: %f\nnumber: %d\n", name_surname, money, money_percentage, number);

	//printf("after sscanf\n");
	file->delete(file);

}

//48538766.570316

char* getName_surname() { return name_surname; }

int getNumber() { return number; }

double getMoney() { return money; }

double getBet() { return bet;  }

void setBet() { bet = money * money_percentage; }

void balanceMoney(double sum) { money += sum; }

boolean isMoneyEnough()
{
	if (money < 1000)
		return false;
	return true;
}

void delete_Kisi(const Kisi this)
{
	if (this == NULL) return;
	free(this);
}


