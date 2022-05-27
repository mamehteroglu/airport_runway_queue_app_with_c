

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct k Kayit;
struct k {
  int oncelik, ucak, talep, inis, gecikme, kalkis;
};

void output();
void input();
void ekle(int, int, int);
Kayit siradaki();
int boyut = -1;
void gecikme();
Kayit liste[24];

void gecikme() {
  //onceden olusturulmus oncelikli kuyruktaki ucuslarin saatlerini duzenler
  int i, j;
  int enSon = 0;
  int gecikme = 0;
  //tersten baslayarak kuyruk uzerinde ilerleme
  for (i = boyut; i >= 0; i--) {
    //24 saatlik dilim dolmus ise enSon degeri 1 olur ve bundan sonraki ucuslar kabul edilmez
    if (enSon) {
      //-1 izin verilmemesini ifade eder
      liste[i].inis = -1;
      liste[i].gecikme = -1;
      liste[i].kalkis = -1;
      continue;
    }
    //eger kendinden onceki inis kendisinin talep ettigi saate esit veya buyukse onceki inisten 1 saat sonrasi inis olarak ayarlanir
    //kuyruk tersten oldugu icin kendisinden onceki dizide sonraki elemana denk gelir
    if (liste[i].talep <= liste[i + 1].inis)
      liste[i].inis = liste[i + 1].inis + 1;

    //gecikme degerinin ayarlanmasi
    liste[i].gecikme = liste[i].inis - liste[i].talep;
    //kalkis degerinin ayarlanmasi
    liste[i].kalkis = (liste[i].talep + liste[i].gecikme) % 25 +1 ;

    //24 ucusun tamamlanmasi
    if(liste[i].inis >= 24)
      enSon = 1;
  }
}

void output() {
  //cikti dosyasina yazma
  FILE *file = fopen("output.txt", "w");
  while (boyut > 0) {
    //her seferinde dizide eleman kalmayana dek kuyruktaki o anki ucus bilgisinin cekilmesi
    Kayit cek = siradaki();









	if (cek.inis == -1 || cek.gecikme == 5) {
      //her ucusu ekrana yazdirma (izin verilmeyenler)
      printf("Ucak = %2d / Oncelik = %2d / Talep = %2d / Inis = "
             "%2d / Gecikme = %2d "
             "/ Kalkis = %2d izin = verilmedi\n",
             cek.ucak, cek.oncelik, cek.talep, cek.inis, cek.gecikme,
             cek.kalkis);
      printf("Sabiha Gokcen havalimanina ilerleyiniz.\n");

      //her ucusu dosyaya yazma (izin verilmeyenler)
      fprintf(
          file,
          "Ucak = %d / Oncelik = %d / Talep = %d / Inis = %d / Gecikme = %d "
          "/ Kalkis = %d izin = verilmedi\n",
          cek.ucak, cek.oncelik, cek.talep, cek.inis, cek.gecikme, cek.kalkis);

    } else {
       //her ucusu ekrana yazdirma (izin verilenler)
      printf("Ucak = %2d / Oncelik = %d / Talep = %d / Inis = "
             "%d / Gecikme = %d "
             "/ Kalkis = %d izin = verildi\n",
             cek.ucak, cek.oncelik, cek.talep, cek.inis, cek.gecikme,
             cek.kalkis);
      //her ucusu dosyaya yazma (izin verilenler)
      fprintf(file,
              "Ucak = %2d / Oncelik = %2d / Talep = %2d / Inis = "
              "%2d / Gecikme = %2d "
              "/ Kalkis = %2d izin = verildi\n",
              cek.ucak, cek.oncelik, cek.talep, cek.inis, cek.gecikme,
              cek.kalkis);

	}


  }

  fclose(file);
}

Kayit siradaki() {
  //en son indis degerindeki yani kuyruk sirasi gelen degeri doner
  int indis = boyut;


  Kayit enson = liste[indis];

  int i;
  //diger tum degerleri sona dogru 1 adim iteler
  for (i = indis; i < boyut; i++) {
    liste[i] = liste[i + 1];
  }
  //boyutu 1 azaltir
  boyut--;

  return enson;
}

void input() {
  //girdi dosyasinin okunmasi
  FILE *file;
  file = fopen("input.txt", "r");

//girdi dosyasi bulunamaz ise
  if (file == NULL) {
    printf("Girdi (input.txt) yok !\n");
    return;
  }
  char a[30];
  //ilk satirin okunmasi ve onemsiz bir degiskene doldurulmasi
  fscanf(file, "%s %s %s\n", a, a, a);
  //dosyanin sonuna gelene dek devam edilmesi
  while (!feof(file)) {
    int oncelik;
    int ucak;
    int talep;
    //dosyanin o anki satirinin okunup ilgili degiskenlere atanmasi
    fscanf(file, "%d %d %d\n", &oncelik, &ucak, &talep);
    //o anki satirdaki ucus bilgisinin kuyruga eklenmesi
    ekle(oncelik, ucak, talep);
  }
  fclose(file);
  //gecikmelerin hesaplanmasi
  gecikme();
  printf("------------------------------------------------------\n");
  //dosyanin yazilmesi
  output();
  printf("------------------------------------------------------\n");
  char bekle;
  printf("\nCikmak icin bir tusa basiniz...");
  scanf("%c", &bekle);
}

void ekle(int oncelik, int ucak, int talep) {
  //gelen ucus bilgileri icin yeni bir kayit olusturulmasi ve kuyruga eklenmesi
  int gecikme = 0;
  //her kayit icin boyutun 1 arttirilmasi
  boyut++;
  //kuyruk tamamen bos ise ilk elemanin eklenmesi
  if (boyut == 0) {
    liste[boyut].oncelik = oncelik;
    liste[boyut].ucak = ucak;
    liste[boyut].talep = talep;
    liste[boyut].inis = talep;
    return;
  }
  int indis = 0;

  int i, j;
  //kuyruk bos degilse o anki talep edilen ucus saati uzerinden diger elemanlar ile karsilastirma yapilmasi
  for (i = boyut; i >= 0; i--) {
    if (talep > liste[i].talep) {
      indis = i;
      gecikme++;
    }
  }
  //kuyruktaki elemanlarin 1 kaydirilmasi
  for (i = boyut; i > indis; i--) {
    liste[i] = liste[i - 1];
  }
  //yeni ucus icin ilgili degerlerin atanmasi
  liste[indis].oncelik = oncelik;
  liste[indis].ucak = ucak;
  liste[indis].talep = talep;
  //henuz gecikme hesaplanmadigi icin talep ile ayni oldugu farz edilir daha sonra hesaplanacaktir
  liste[indis].inis = talep;

  //saat bazinda oncelik sirasina gore kuyrugun yeniden duzenlenmesi
  for (i = 0; i <= boyut; i++) {

    for (j = i; j <= boyut; j++) {
      //eger o an ki elemanin talep edilen saat degeri oncesindeki bir deger ile eslesiyor ve oncelik degeri daha kucuk ya da esitse
      if (((liste[i].oncelik < liste[j].oncelik)||(liste[i].oncelik == liste[j].oncelik))
           && (liste[i].talep == liste[j].talep) ) {
          //yer degistirme yapilmasi
        Kayit gecici = liste[j];
        liste[j] = liste[i];
        liste[i] = gecici;
      }
    }
  }
}
int main(int argc, char **argv) { input(); }
