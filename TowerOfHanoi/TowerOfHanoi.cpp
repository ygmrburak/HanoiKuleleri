#include <stdio.h>
#define SIZE 6
int adim = 0;
struct stack {
	int veri[SIZE];
	int sayac;
}
a[3]; // üç direk
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
int birincidisk() {             // Oyunun çözümü iki adýmdan oluþur.Sürekli bu iki adým birbirini takip eder.
	for (int i = 0; i < 3; i++) // Birinci adým birinci diski doðru hareket ettirmek.
		if (top(&a[i]) == 1) // Burada birinci adýmýn fonksiyonunu yazdýk.
			return i;
}
int enkucukdisk() {
	int ekdisk = 100; //Oyunun çözümünün ikinci adýmýnýn fonksiyonudur.
	int ekdirek = 0; //Amaç birinci diskten sonraki en küçük diski doðru oynatmaktýr.
	for (int i = 0; i < 3; i++)
		if (top(&a[i]) < ekdisk && top(&a[i]) > 1 && a[i].sayac != 0)
		{
			ekdisk = top(&a[i]);
			ekdirek = i;
		}
	return ekdirek;
}

int oynarmi(stack* direk1, stack* direk2) {
	if (direk2->sayac <= 0) //Oyunun kurallarýndan büyük disk küçük diskin üstüne gelmemeli
		return 1; //kontolü burada yapýldý.
	if (top(direk1) < top(direk2))
		return 1;
	return 0;
}
int oyunbittimi() {
	if (a[0].sayac <= 0 && a[1].sayac == SIZE) // Birinci direðin boþ olup tüm disklerin farklý bir direkte doðru bir þekilde olmasýný
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
void oyna(stack* kimden, stack* kime) { // Tüm kurallar kontrol edildikten sonra diski oynattýðýmýz fonksiyondur.
	push(kime, pop(kimden));
	adim++;
	print();
}

int main() {

	for (int i = 0; i < 3; i++) // Direklerin(stack) sayaçlarýný sýfýrladýk.
		a[i].sayac = 0;
	for (int i = SIZE; i > 0; i--) // Oynamak istediðimiz disk sayýsý kadar birinci direðe(stack) eleman ekliyoruz.
		push(&a[0], i);
	print();
	while (!oyunbittimi()) { // Oyun bitmediyse diskleri hareket ettirmeye devam eder.
		int kimden = birincidisk();
		int kime = kimden;
		while (!oynarmi(&a[kimden], &a[kime])) { // Oynatacaðýmýz diski kurallara uygun direðe taþýma iþlemi.
			kime++; // Bu while oyunumuzun birinci adýmýný kullanýr.
			if (kime > 2)
				kime = 0;
		}
		printf("------------------------------------------------------------------- \n");
		printf("from %d to %d \n", kimden + 1, kime + 1);
		oyna(&a[kimden], &a[kime]); // Kurallara uygun direði bulduðumuzda diski hareket ettiriyoruz.
		if (oyunbittimi())
			break;
		kimden = enkucukdisk();
		kime = kimden;
		while (!oynarmi(&a[kimden], &a[kime])) { //Bu while oyunumuzun ikinci adýmýný kullanýr.
			kime++;
			if (kime > 2)
				kime = 0;
		}
		printf("------------------------------------------------------------------- \n");
		printf("from %d to %d \n", kimden + 1, kime + 1);
		oyna(&a[kimden], &a[kime]);  // Kurallara uygun direði bulduðumuzda diski hareket ettiriyoruz.
	}
	printf("------------------------------------------------------------------- \n");
	printf("Game Over Thank You For Playing \n");
}