#include "Kisi.h"
#include<string.h>

#define MAX_NUMBER 10000

char* kisi[MAX_NUMBER];
char* kisiArray[MAX_NUMBER][4];
double moneyArray[MAX_NUMBER];
float money_percentageArray[MAX_NUMBER];
char* name_surname;
double money;
float money_percentage;
int number;
static int kisi_counter;
static int kisi_sayisi;
double bet;
char* en_zengin_kisi;
void splitKisi(int);
void delete_Kisi(const Kisi);


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
	this->enZenginKisiBakiye = &enZenginKisiBakiye;
	this->getEnZenginKisi = &getEnZenginKisi;
	this->delete = &delete_Kisi;

	Dosya file = new_Dosya();

	kisi_sayisi = file->countLines() + 1;

	for (int i = 0; i < kisi_sayisi; i++) {
		kisi[i] = file->readKisi();
		splitKisi(i);
	}
	char* ptr;

	for (int i = 0; i < kisi_sayisi; i++) {
		moneyArray[i] = strtod(kisiArray[i][1], &ptr);
		money_percentageArray[i] = strtof(kisiArray[i][2], &ptr);

	}

	file->delete(file);

	return this;
}

//private method
void splitKisi(int index)
{
	//printf("splitKisi()\n");
	if (kisi[index] != "")
	{
		int i = 0;
		char* p = strtok(kisi[index], "#");

		while (p != NULL)
		{
			kisiArray[index][i++] = p;
			p = strtok(NULL, "#");
		}
		//printf("\nend of splitKisi()");

	}
}

void setKisi(int kisiCounter)
{
	kisi_counter = kisiCounter;
	char* ptr;
		
	name_surname = kisiArray[kisi_counter][0];
	money = moneyArray[kisi_counter];
	money_percentage = money_percentageArray[kisi_counter];
	number = atoi(kisiArray[kisi_counter][3]);
}

char* getName_surname() { return name_surname; }

int getNumber() { return number; }

double getMoney() { return money; }

double getBet() { return bet; }

void setBet() { bet = money * money_percentage; }

void balanceMoney(double sum) 
{
	money += sum;
	moneyArray[kisi_counter] += sum;	
}

boolean isMoneyEnough()
{
	if (money < 1000)
		return false;
	return true;
}
	
double enZenginKisiBakiye() {

	int i;
	int index = 0;
	double max = moneyArray[0];

	Dosya file = new_Dosya();
	
	for (i = 1; i < kisi_sayisi; i++)
		if (moneyArray[i] > max)
		{
			max = moneyArray[i];
			index = i;
		}
			
	en_zengin_kisi = kisiArray[index][0];
	return max;

}

char* getEnZenginKisi() { enZenginKisiBakiye();  return en_zengin_kisi; }

void delete_Kisi(const Kisi this)
{
	if (this == NULL) return;
	free(this);
}


