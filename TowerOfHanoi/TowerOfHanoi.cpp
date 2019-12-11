#include <stdio.h>
#define SIZE 6
int adim = 0;
struct stack {
	int veri[SIZE];
	int sayac;
}
a[3]; // �� direk
int pop(stack* d) {
	d->sayac--;
	return d->veri[d->sayac];
}
void push(stack* d, int veri) {
	d->veri[d->sayac] = veri;
	d->sayac++;
	//printf("push %d", veri);
}
int top(stack* d) {
	return d->veri[d->sayac - 1];
}
int birincidisk() {             // Oyunun ��z�m� iki ad�mdan olu�ur.S�rekli bu iki ad�m birbirini takip eder.
	for (int i = 0; i < 3; i++) // Birinci ad�m birinci diski do�ru hareket ettirmek.
		if (top(&a[i]) == 1) // Burada birinci ad�m�n fonksiyonunu yazd�k.
			return i;
}
int enkucukdisk() {
	int ekdisk = 100; //Oyunun ��z�m�n�n ikinci ad�m�n�n fonksiyonudur.
	int ekdirek = 0; //Ama� birinci diskten sonraki en k���k diski do�ru oynatmakt�r.
	for (int i = 0; i < 3; i++)
		if (top(&a[i]) < ekdisk && top(&a[i]) > 1 && a[i].sayac != 0)
		{
			ekdisk = top(&a[i]);
			ekdirek = i;
		}
	return ekdirek;
}

int oynarmi(stack* direk1, stack* direk2) {
	if (direk2->sayac <= 0) //Oyunun kurallar�ndan b�y�k disk k���k diskin �st�ne gelmemeli
		return 1; //kontol� burada yap�ld�.
	if (top(direk1) < top(direk2))
		return 1;
	return 0;
}
int oyunbittimi() {
	if (a[0].sayac <= 0 && a[1].sayac == SIZE) // Birinci dire�in bo� olup t�m disklerin farkl� bir direkte do�ru bir �ekilde olmas�n�
		return 1; // kontrol eder.
	if (a[0].sayac <= 0 && a[2].sayac == SIZE)
		return 1;
	return 0;
}
void print() {
	printf("step %d \n", adim);
	for (int i = 0; i < 3; i++) {
		printf("pole %d --->    ", i + 1);

		for (int j = 0; j < a[i].sayac; j++) {
			printf("%d \t", a[i].veri[j]);

		}
		printf("\n");



	}
}
void oyna(stack* kimden, stack* kime) { // T�m kurallar kontrol edildikten sonra diski oynatt���m�z fonksiyondur.
	push(kime, pop(kimden));
	adim++;
	print();
}

int main() {

	for (int i = 0; i < 3; i++) // Direklerin(stack) saya�lar�n� s�f�rlad�k.
		a[i].sayac = 0;
	for (int i = SIZE; i > 0; i--) // Oynamak istedi�imiz disk say�s� kadar birinci dire�e(stack) eleman ekliyoruz.
		push(&a[0], i);
	print();
	while (!oyunbittimi()) { // Oyun bitmediyse diskleri hareket ettirmeye devam eder.
		int kimden = birincidisk();
		int kime = kimden;
		while (!oynarmi(&a[kimden], &a[kime])) { // Oynataca��m�z diski kurallara uygun dire�e ta��ma i�lemi.
			kime++; // Bu while oyunumuzun birinci ad�m�n� kullan�r.
			if (kime > 2)
				kime = 0;
		}
		printf("------------------------------------------------------------------- \n");
		printf("from %d to %d \n", kimden + 1, kime + 1);
		oyna(&a[kimden], &a[kime]); // Kurallara uygun dire�i buldu�umuzda diski hareket ettiriyoruz.
		if (oyunbittimi())
			break;
		kimden = enkucukdisk();
		kime = kimden;
		while (!oynarmi(&a[kimden], &a[kime])) { //Bu while oyunumuzun ikinci ad�m�n� kullan�r.
			kime++;
			if (kime > 2)
				kime = 0;
		}
		printf("------------------------------------------------------------------- \n");
		printf("from %d to %d \n", kimden + 1, kime + 1);
		oyna(&a[kimden], &a[kime]);  // Kurallara uygun dire�i buldu�umuzda diski hareket ettiriyoruz.
	}
	printf("------------------------------------------------------------------- \n");
	printf("Game Over Thank You For Playing \n");
}