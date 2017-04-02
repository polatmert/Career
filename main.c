
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h> //getche fonksiyonu icin
#define YIL 2016
struct okul{
    char o_ad[40];
    char o_lisans[40];
    char o_bolum[40];
    int baslangic_yili;
    int bitis_yili;
    double not_ortalamasi;

    struct okul * sonraki;
}yazma_yardimcisi,o_gecici,o_okunan,yazyard;

struct is{
    char is_ad[40];
    char is_adres[100];
    char is_gorevi[40];
    double  is_gorev_suresi;
    struct is *sonraki;

    }i_okunan,i_yard;

struct yabanci_dil{
    char dil_ad[40];

    struct yabanci_dil*sonraki;
}y_okunan,y_yard;

struct KISI{
    char ad[40];
    char soyad[40];
    char kisi_adres[100];
    double telefon;
    char mail[40];
    int dogum_tarihi;
    int ehliyet_kodlamasi;

    int okul_sayisi;
    int is_sayisi;
    int dil_sayisi;

    struct KISI * left,*right;
    struct okul * ptr_okul;
    struct is   * ptr_is;
    struct yabanci_dil * ptr_dil;

}eleman,k_okunan,e;

typedef struct KISI node;
typedef struct okul o_node;
typedef struct is   i_node;
typedef struct yabanci_dil y_node;
node *root;
node *gezici;
node *curr,*parent,*temp;

o_node *o_yeni,*o_bas,*o_son;
o_node *o_gezici,*o_gez;

i_node *i_yeni,*i_bas,*i_son;
i_node *i_dugum,*i_gezici,*i_gez;

y_node *y_yeni,*y_bas,*y_son;
y_node *y_dugum,*y_gezici,*y_gez;

int lisans_kontrol=0,ingilizce_kontrol=0,fazla_dilli=0,dil_sayisigecici=0,dnyim=0,eleman_sayisi=0;
float toplam_dny=0;
//silinecek isimlerin silme fonksiyonuna yollamak için gecici olarka kullanilmistir
char lisans_temizle[40],ingilizce_tem[40],dil_temiz[40],dnyim_tem[40],ehliyet_tem[40];

void bilgi_giris();
void bilgi_guncelle();
void bilgi_goruntule();
void agac_icin_dosyada_oku();
void preorder_gez(node * tree);
void inorder_gez(node * tree);
void postorder_gez(node * tree);
void agaca_ekle(node **tree,node * item);
void agacdan_silme(node **tree,char silinecek[40]);
void agaci_dosyaya_yaz(node * tree,FILE * dosya);
void bilgi_sil();
void ehliyet_cozumle(int ehliyetkod);
void en_az_lisans_listele(node *tree);
void ingilizce_filtresi(node *tree);
void birden_fazla_dil_bilenler(node*tree);
void deneyim_mini(node*tree,double xmin);
void deneyim_sifir(node*tree,double xmin);
void ehliyet_filtre(node*tree,double eh_aranan);
void yas_filtre(node*tree,int sinir_yili);

void filtreyi_dosyaya_yaz(node*tree,FILE*dosya);



int main()
    {

    char secim=0,secim2=0;
    while(1){
    system("cls");
    printf("*******************\n");
    printf("1.Aday Girisi\n");
    printf("2.Is Yeri Girisi\n");
    printf("X.CIKIS\n");
    printf("*******************\n");
    secim=getche();

    if(secim=='1')///aday grisi
        {fflush(stdin);
                system("cls");
                printf("*******************\n");
                printf("1.Bilgi Ekle\n");
                printf("2.Bilgi Goruntule\n");
                printf("3.Bilgi Sil\n");
                printf("4.Bilgi Guncelle\n");
                printf("X.CIKIS \n");
                printf("*******************\n");
                secim2=getche();
                fflush(stdin);
                system("cls");
                 if(secim2=='1'){

                        bilgi_giris();

                 }else if(secim2=='2'){

                        bilgi_goruntule();
                        printf("Bilgiler bulundu\nDevam etmek icin herhangi bir tusa basin\n");
                        getche();
                       fflush(stdin);

                 }else if(secim2=='3'){

                        agac_icin_dosyada_oku();
                        bilgi_sil();

                 }else if(secim2=='4'){
                        bilgi_guncelle();
                 }else{printf("Hatali giris !!");}

        }///secim bir sonu
                        else if(secim=='2'){///is yeri girisi

/**BURADAKÝ AGAC FILTRE ICINDIR */agac_icin_dosyada_oku();
                                   while(secim2!='X' || secim2!='x')
                                    {
                                    system("cls");
                                    printf("*********************************************************\n");
                                    printf("A. Tum kisilerin adlari, duzeyler ve traversal\n");
                                    printf("B. Tum adaylarin listelenmesi\n");
                                    printf("C. Adindan kisi arama ve tum bilgilerinin listesi\n\n");
                                    printf("D. En az lise mezunu olanlarin listesi\n");
                                    printf("E. ingilizce bilenlerin listelenmesi\n");
                                    printf("F. Birden fazla dil bilen kisilerin listelenmesi\n");
                                    printf("G. Girelen minumum deneyime gore listeleme\n");
                                    printf("H. Deneyimsiz kisilerin listelenmesi\n");
                                    printf("I. Girilecek yas degerinin altindakileri listelenmesi\n");
                                    printf("J. Belirli tip ehliyeti olanlarin listelenmesi\n");
                                    printf("K. Filtrelenmis bilgileri dosyaya yaz\n");
                                    printf("\nX. *****FILTREYI TEMIZLE*****\n");
                                    printf("**********************************************************\n");
                                secim2=getche();
                                fflush(stdin);
                                system("cls");

                                 if(secim2=='A' || secim2=='a'){
                                        printf("A. Preorder  Gez\n");
                                        printf("B. Inorder   Gez\n");
                                        printf("C. Postorder Gez\n");
                                        int secim_gez;
                                        secim_gez=getche();

                                        if(secim_gez=='a' || secim_gez=='A')
                                            {
                                                eleman_sayisi=0;
                                           preorder_gez(root);
                                            printf("\n\n\nEleman Sayisi: %d\n\n\n",eleman_sayisi);

                                        }else if(secim_gez=='b'||secim_gez=='B')
                                            {
                                                eleman_sayisi=0;
                                                inorder_gez(root);
                                                printf("\n\nEleman Sayisi: %d\n",eleman_sayisi);
                                            }else if(secim_gez=='c'||secim_gez=='C')
                                                {
                                                  eleman_sayisi=0;
                                                  postorder_gez(root);
                                                  printf("\n\nEleman Sayisi: %d\n",eleman_sayisi);
                                                }else{}

                                        printf("\bBilgiler listelendi\ndevam etmek icin herhangi bir tusa basin");
                                        getche();


                                }
                                 if(secim2=='B' || secim2=='b'){
                                    agac_icin_dosyada_oku();
                                    preorder_gez(root);
                                    printf("Bilgiler listelendi\ndevam etmek icin herhangi bir tusa basin");
                                    getch();
                                    fflush(stdin);

                                }
                                 if(secim2=='C' || secim2=='c'){
                                     bilgi_goruntule();
                                     getche();
                                     fflush(stdin);
                                }
                                 if(secim2=='D' || secim2=='d'){

                                      en_az_lisans_listele(root);
                                      printf("Bilgiler bulundu\nDevam etmek icin herhangi bir tusa basin\n");
                                      getche();
                                      fflush(stdin);
                                }
                                 if(secim2=='E' || secim2=='e'){
                                        ingilizce_filtresi(root);
                                        printf("Bilgiler bulundu\nDevam etmek icin herhangi bir tusa basin\n");
                                        getche();
                                        fflush(stdin);


                                }
                                 if(secim2=='F' || secim2=='f'){
                                        birden_fazla_dil_bilenler(root);
                                        printf("Bilgiler bulundu\nDevam etmek icin herhangi bir tusa basin\n");
                                        getche();
                                        fflush(stdin);


                                }
                                 if(secim2=='G' || secim2=='g'){
                                        double min_d=0;
                                        char min_dc[10];
                                       printf("Minumun deneyim suresini girin: ");
                                        fgets(min_dc,10,stdin);
                                         min_d=atof(min_dc);

                                        deneyim_mini(root,min_d);
                                        printf("Bilgiler bulundu\nDevam etmek icin herhangi bir tusa basin\n");
                                        getche();

                                }
                                 if(secim2=='H' || secim2=='h'){
                                        deneyim_sifir(root,0);
                                        printf("Bilgiler:\nDevam etmek icin herhangi bir tusa basin\n");
                                        getche();

                                }
                                 if(secim2=='I' || secim2=='i'){
                                    ///yas siniri
                                        int yas_siniri=0;
                                        char ys_sn[10];
                                        printf("Yas tepe degerini girin\n");
                                        fgets(ys_sn,10,stdin);
                                        yas_siniri=atoi(ys_sn);
                                        yas_siniri=YIL-yas_siniri;

                                       yas_filtre(root,yas_siniri);
                                        printf("Bilgiler:\nDevam etmek icin herhangi bir tusa basin\n");
                                        getche();
                                }
                                 if(secim2=='J' || secim2=='j'){
                                        ///ehliyet
                                         double eh_aranan=0;
                                        char eh_tip[10];
                                        printf("Ehliyet Secin:");
                                        printf("\n1.A2 \n2.B \n3.D\n4.E\n5.G\n6.H\n\n");
                                        fgets(eh_tip,10,stdin);
                                        eh_aranan=atof(eh_tip);
                                        ehliyet_filtre(root,eh_aranan);
                              printf("Bilgiler:\nDevam etmek icin herhangi bir tusa basin\n");
                                        getche();

                                }
                                 if(secim2=='K' || secim2=='k'){

                                    ///filtrelenmis verilerin ayri dosyay kayit edilmesi
                                        FILE *dosya=fopen("filtre.txt","w");
                                        filtreyi_dosyaya_yaz(root,dosya);
                                        fclose(dosya);
                                        printf("Yazma tamamlandi.");
                                        getche();


                                }

                                if(secim2=='X' || secim2=='x'){
                                        break;

                                }
                              }///while sonu




                        }else if(secim=='X' ||secim=='x'){
                            printf("\b   ");
                            exit(1);

                        }else{///1 veya 2 dýsýnda secildiyse
                            printf("Hatali giris");
                            }


    }///while dongusu sonu
        return 0;
    }///main sonu


void filtreyi_dosyaya_yaz(node*tree,FILE*dosya){

    if(tree==NULL){
        return;
    }
    fputs("\n_-_-_-_-_YENI KISI_-_-_-_-_\n",dosya);

        fprintf(dosya,"%s%s%s%7.lf\n",tree->ad,tree->soyad,tree->kisi_adres,tree->telefon);
        fprintf(dosya,"%s%d\n",tree->mail,tree->dogum_tarihi );
        ///ehliyet kodunu kullanarak ehliyetleri yazdir

        o_gez=tree->ptr_okul;
        i_gez=tree->ptr_is;
        y_gez=tree->ptr_dil;
        fputs("**OKUL BILGILERI**",dosya);
        while(o_gez!=NULL)
        {
            fputs("\n______________________________\n",dosya);
            fprintf(dosya,"%s%s%s%s%d\n",o_gez->o_ad,o_gez->o_lisans,o_gezici->o_bolum,o_gez->o_bolum ,o_gez->baslangic_yili);

            if(o_gez->bitis_yili==0)
                {fputs("Mezuniyet durumu: Devam ediyor\n",dosya);}
                else
                    {fprintf(dosya,"%d\n",o_gez->bitis_yili);}

            if(o_gez->not_ortalamasi==0)
                {fputs("Not ortalamasi: e",dosya);}
                else
                    {fprintf(dosya,"%lf\n",o_gez->not_ortalamasi);}
            o_gez=o_gez->sonraki;
        }

        fputs("\n\n***IS BILGILERI**",dosya);
        while(i_gez!=NULL)
        {
            fputs("\n______________________________\n",dosya);
            fprintf(dosya,"%s%s%s%lf",i_gez->is_ad,i_gez->is_adres,i_gez->is_gorevi,i_gez->is_gorev_suresi);

            i_gez=i_gez->sonraki;
        }
        fputs("\n\n**YABANCI DIL BILGILERI**",dosya);


            while(y_gez!=NULL)
            {
                fputs("\n____________________________\n",dosya);
                fprintf(dosya,"%s",y_gez->dil_ad);
                y_gez=y_gez->sonraki;


            }

        if((tree)->left)
            filtreyi_dosyaya_yaz((tree)->left,dosya);
        if((tree)->right)
            filtreyi_dosyaya_yaz((tree)->right,dosya);
}

void yas_filtre(node*tree,int sinir_yili){

        if(tree==NULL){
        return;
        }


        if((tree->dogum_tarihi)>sinir_yili)//belirlenen yastan kucuk ise
            {
               printf("%s%s\n\n",tree->ad,tree->soyad);
            }

        if((tree)->left)
            yas_filtre((tree)->left,sinir_yili);
        if((tree)->right)
            yas_filtre((tree)->right,sinir_yili);


}

void ehliyet_filtre(node*tree,double eh_aranan){

        if(root==NULL){
        return;
        }

        int ehgec=0;
        ehgec=tree->ehliyet_kodlamasi;

        while(ehgec!=0){

            if((ehgec%10)==eh_aranan){

                printf("%s",tree->ad);
                printf("%s\n\n",tree->soyad);


            }else{

              strcpy(ehliyet_tem,tree->ad);
                agacdan_silme(&root,ehliyet_tem);
            }


            ehgec=ehgec/10;
        }
        if((tree)->left)
            ehliyet_filtre((tree)->left,eh_aranan);
        if((tree)->right)
            ehliyet_filtre((tree)->right,eh_aranan);

}

void deneyim_sifir(node*tree,double xmin){

        if(tree==NULL){
        return;
        }


        i_gezici=tree->ptr_is;
        dnyim=0;
        toplam_dny=0;
        while(i_gezici!=NULL)
        {
            toplam_dny=toplam_dny +(i_gezici->is_gorev_suresi);
            i_gezici=i_gezici->sonraki;
            }

        if(toplam_dny==xmin){

            printf("%s%s\n",tree->ad,tree->soyad);
        }

        if(toplam_dny!=xmin){
                strcpy(dnyim_tem,tree->ad);
                agacdan_silme(&root,dnyim_tem);
        }
        if((tree)->left)
            deneyim_sifir((tree)->left,0);
        if((tree)->right)
            deneyim_sifir((tree)->right,0);
}

void deneyim_mini(node*tree,double xmin){

        if(tree==NULL){
        return;
        }


        i_gezici=tree->ptr_is;
        dnyim=0;
        toplam_dny=0;
        while(i_gezici!=NULL)
        {
            toplam_dny=toplam_dny +(i_gezici->is_gorev_suresi);

         i_gezici=i_gezici->sonraki;
               }
   ///  ///////     /////////////   /////////////////////  //////////////////
        if(toplam_dny>xmin){

            printf("%s%s\n",tree->ad,tree->soyad);
        }

        if(toplam_dny<xmin){
                strcpy(dnyim_tem,tree->ad);
            agacdan_silme(&root,dnyim_tem);
        }
        if((tree)->left)
            deneyim_mini((tree)->left,xmin);
        if((tree)->right)
            deneyim_mini((tree)->right,xmin);
}

void ingilizce_filtresi(node *tree){

        if(tree==NULL){
        return;
        }


        y_gezici=tree->ptr_dil;
        ingilizce_kontrol=0;

        while(y_gezici!=NULL)
        {
        if(strstr(y_gezici->dil_ad,"ingilizce")!=NULL)
         ingilizce_kontrol=1;
        if(strstr(y_gezici->dil_ad,"ing")!=NULL)
         ingilizce_kontrol=1;
        if(strstr(y_gezici->dil_ad,"INGILIZCE")!=NULL)
         ingilizce_kontrol=1;

         y_gezici=y_gezici->sonraki;
               }

               ///
        if(ingilizce_kontrol==1){

            printf("%s%s\n",tree->ad,tree->soyad);
        }

        if(ingilizce_kontrol==0){
                strcpy(ingilizce_tem,tree->ad);
            agacdan_silme(&root,ingilizce_tem);
        }

        if((tree)->left)
            ingilizce_filtresi((tree)->left);
        if((tree)->right)
            ingilizce_filtresi((tree)->right);
///strstr(s1, s2) s1 iicinde s2 yi arar-bulursa adres dondurur

}

void en_az_lisans_listele(node *tree){

        if(tree==NULL)
        {
            return;
        }

       o_gezici=tree->ptr_okul;
        lisans_kontrol=0;

        while(o_gezici->sonraki!=NULL)
        {
        if(strstr(o_gezici->o_lisans,"lisans")!=NULL)
            lisans_kontrol=1;
         else if(strstr(o_gezici->o_lisans,"LISANS")!=NULL)
            lisans_kontrol=1;
        else if(strstr(o_gezici->o_lisans,"yuksek lisans")==NULL)
            lisans_kontrol=1;
        else if(strstr(o_gezici->o_lisans,"YUKSEK LISANS")==NULL)
            lisans_kontrol=1;
        else if(strstr(o_gezici->o_lisans,"doktora")==NULL)
            lisans_kontrol=1;
        else if(strstr(o_gezici->o_lisans,"DOKTORA")==NULL)
            lisans_kontrol=1;
        else if(strstr(o_gezici->o_lisans,"yuksek okul")==NULL)
            lisans_kontrol=1;
        else if(strstr(o_gezici->o_lisans,"YUKSEK OKUL")==NULL)
            lisans_kontrol=1;

         o_gezici=o_gezici->sonraki;
        }

        if(lisans_kontrol==1){
            printf("%s%s\n",tree->ad,tree->soyad);
        }

        if(lisans_kontrol==0){

                strcpy(lisans_temizle,tree->ad);
            agacdan_silme(&root,lisans_temizle);
        }


        if((tree)->left)
            en_az_lisans_listele((tree)->left);
        if((tree)->right)
            en_az_lisans_listele((tree)->right);


}

void bilgi_guncelle(){

    bilgi_sil();
    bilgi_giris();
}

void bilgi_sil(){
        char k_silinecek[40];
        char buffer[40];

        printf("______________________\n ismi giriniz: ");
        fgets(k_silinecek,40,stdin);
        printf("telefon:");
        fgets(buffer,40,stdin);
        eleman.telefon=atof(buffer);

        agacdan_silme(&root,k_silinecek);
        FILE*dosya=fopen("bilgiler.txt","wb+");
        agaci_dosyaya_yaz(root,dosya);
        fclose(dosya);


}

void preorder_gez(node*tree){

       eleman_sayisi++;

       if(tree==NULL){
        return;
        }

        o_gez=tree->ptr_okul;
        i_gez=tree->ptr_is;
        y_gez=tree->ptr_dil;

        printf("\n\n    **************BILGILER**************\n");
        printf("Ad              : %s",tree->ad);
        printf("Soyad           : %s",tree->soyad);
        printf("Adres           : %s",tree->kisi_adres);
        printf("Telefon         : %7.f\n",tree->telefon);
        printf("Mail            : %s",tree->mail);
        printf("Dogum Tarihi    : %d\n",tree->dogum_tarihi);
        printf("Ehliyet Bilgi   :");ehliyet_cozumle(tree->ehliyet_kodlamasi);
        printf("________________________________________________\n");

        while(o_gez!=NULL)
        {
        printf("Okul ad         : %s",o_gez->o_ad);
        printf("Okul lisans tipi: %s",o_gez->o_lisans);
        printf("Bolum           : %s",o_gez->o_bolum);
        if((o_gez->not_ortalamasi)==0)
        printf("Not ortalamasi  : e\n");
        else
        {printf("Not ortalamasi  : %lf\n",o_gez->not_ortalamasi);}
        printf("Baslama Yili    : %d\n",o_gez->baslangic_yili);

        if((o_gez->bitis_yili)==0)
        printf("Bitis Yili      : Devam ediyor\n");
        else
        {printf("Bitis Yili      : %d\n",o_gez->bitis_yili);}




        printf("________________________________________________\n");
        o_gez=o_gez->sonraki;
        }///okul while sonu

        while(i_gez!=NULL)
        {
        printf("Is ad           : %s",i_gez->is_ad);
        printf("Is adres        : %s",i_gez->is_adres);
        printf("Is gorevi       : %s",i_gez->is_gorevi);
        printf("Is gorev suresi : %lf\n",i_gez->is_gorev_suresi);
        printf("________________________________________________\n");
        i_gez=i_gez->sonraki;
        }///is while sonu


        while(y_gez!=NULL)
        {
            printf("Yabanci Dil: %s",y_gez->dil_ad);

            y_gez=y_gez->sonraki;
        }///yabanci dil while



                if(tree->left)
                    preorder_gez(tree->left);
                if(tree->right)
                    preorder_gez(tree->right);

                    }

void inorder_gez(node*tree){

       eleman_sayisi++;
       if(tree==NULL){
        return;
        }

                if(tree->left)
                    inorder_gez(tree->left);


        o_gez=tree->ptr_okul;
        i_gez=tree->ptr_is;
        y_gez=tree->ptr_dil;

        printf("\n\n    **************BILGILER**************\n");
        printf("Ad              : %s",tree->ad);
        printf("Soyad           : %s",tree->soyad);
        printf("Adres           : %s",tree->kisi_adres);
        printf("Telefon         : %7.f\n",tree->telefon);
        printf("Mail            : %s",tree->mail);
        printf("Dogum Tarihi    : %d\n",tree->dogum_tarihi);
        printf("Ehliyet Bilgi   :");ehliyet_cozumle(tree->ehliyet_kodlamasi);
        printf("________________________________________________\n");

        while(o_gez!=NULL)
        {
        printf("Okul ad         : %s",o_gez->o_ad);
        printf("Okul lisans tipi: %s",o_gez->o_lisans);
        printf("Bolum           : %s",o_gez->o_bolum);
        if((o_gez->not_ortalamasi)==0)
        printf("Not ortalamasi  : e\n");
        else
        {printf("Not ortalamasi  : %lf\n",o_gez->not_ortalamasi);}
        printf("Baslama Yili    : %d\n",o_gez->baslangic_yili);

        if((o_gez->bitis_yili)==0){
        printf("Bitis yili      : Devam ediyor");
        }else
        {printf("Bitis Yili      : %d\n",o_gez->bitis_yili);}

        printf("________________________________________________\n");
        o_gez=o_gez->sonraki;
        }///okul while sonu

        while(i_gez!=NULL)
        {
        printf("Is ad           : %s",i_gez->is_ad);
        printf("Is adres        : %s",i_gez->is_adres);
        printf("Is gorevi       : %s",i_gez->is_gorevi);
        printf("Is gorev suresi : %lf\n",i_gez->is_gorev_suresi);
        printf("________________________________________________\n");
        i_gez=i_gez->sonraki;
        }///is while sonu

        while(y_gez!=NULL)
        {
            printf("Yabanci: %s",y_gez->dil_ad);

            y_gez=y_gez->sonraki;
        }///yabanci dil while



                if(tree->right)
                    inorder_gez(tree->right);

                    }

void postorder_gez(node*tree){

        eleman_sayisi++;
        if(tree==NULL){
        return;
        }

        if(tree->left)
           postorder_gez(tree->left);
        if(tree->right)
            postorder_gez(tree->right);

        o_gez=tree->ptr_okul;
        i_gez=tree->ptr_is;
        y_gez=tree->ptr_dil;

        printf("\n\n    **************BILGILER**************\n");
        printf("Ad              : %s",tree->ad);
        printf("Soyad           : %s",tree->soyad);
        printf("Adres           : %s",tree->kisi_adres);
        printf("Telefon         : %7.f\n",tree->telefon);
        printf("Mail            : %s",tree->mail);
        printf("Dogum Tarihi    : %d\n",tree->dogum_tarihi);
        printf("Ehliyet Bilgi   :");ehliyet_cozumle(tree->ehliyet_kodlamasi);
        printf("________________________________________________\n");

        while(o_gez!=NULL)
        {
        printf("Okul ad         : %s",o_gez->o_ad);
        printf("Okul lisans tipi: %s",o_gez->o_lisans);
        printf("Bolum           : %s",o_gez->o_bolum);
        if((o_gez->not_ortalamasi)==0)
        printf("Not ortalamasi  : e \n");
        else
        {printf("Not ortalamasi  : %lf\n",o_gez->not_ortalamasi);}
        printf("Baslama Yili    : %d\n",o_gez->baslangic_yili);

        if((o_gez->bitis_yili)==0){
        printf("Bitis yili      : Devam ediyor");
        }else
        {printf("Bitis Yili      : %d\n",o_gez->bitis_yili);}

 printf("________________________________________________\n");
        o_gez=o_gez->sonraki;
        }///okul while sonu

        while(i_gez!=NULL)
        {
        printf("Is ad           : %s",i_gez->is_ad);
        printf("Is adres        : %s",i_gez->is_adres);
        printf("Is gorevi       : %s",i_gez->is_gorevi);
        printf("Is gorev suresi : %lf\n",i_gez->is_gorev_suresi);
        printf("________________________________________________\n");
        i_gez=i_gez->sonraki;
        }///is while sonu

        while(y_gez!=NULL)
        {
            printf("Yabanci: %s",y_gez->dil_ad);

            y_gez=y_gez->sonraki;
        }///yabanci dil while




                    }

void agac_icin_dosyada_oku(){
            FILE* dosya= fopen("bilgiler.txt","rb");
            root=NULL;

            int  sayac1=0;

while(1)
{
    if(fread(&k_okunan,sizeof(struct KISI),1,dosya)!=1)//okunacak bilgi kalmadi ise programi bitirir
        {
          break;}

            curr=(node* )malloc(sizeof(node));
            curr->left=curr->right=NULL;

            strcpy(curr->ad,k_okunan.ad);
            strcpy(curr->soyad,k_okunan.soyad);
            strcpy(curr->kisi_adres,k_okunan.kisi_adres);
            curr->telefon=k_okunan.telefon;
            strcpy(curr->mail,k_okunan.mail);
            curr->dogum_tarihi=k_okunan.dogum_tarihi;
            curr->ehliyet_kodlamasi=k_okunan.ehliyet_kodlamasi;
            curr->okul_sayisi=k_okunan.okul_sayisi;
            curr->is_sayisi=k_okunan.is_sayisi;
            curr->dil_sayisi=k_okunan.dil_sayisi;

            curr->ptr_okul=NULL;
            curr->ptr_is=NULL;
            curr->ptr_dil=NULL;


///okul bagli listesi olusturuluyor
         sayac1=0;
        while(sayac1<k_okunan.okul_sayisi)///okul bilgileri okunuyor        ///***
            {
                    if(fread(&o_okunan,sizeof(struct okul),1,dosya)!=1)///**
                        {
                         break;
                        }else{
                            if(sayac1==0)
                                {
                                o_yeni=(o_node*)malloc(sizeof(o_node));///****

                                strcpy(o_yeni->o_ad,o_okunan.o_ad);
                                strcpy(o_yeni->o_lisans,o_okunan.o_lisans);
                                strcpy(o_yeni->o_bolum,o_okunan.o_bolum);
                                o_yeni->baslangic_yili=o_okunan.baslangic_yili;
                                o_yeni->bitis_yili=o_okunan.bitis_yili;
                                o_yeni->not_ortalamasi=o_okunan.not_ortalamasi;


                                o_yeni->sonraki=NULL;///***
                                o_gezici=o_bas=o_son=o_yeni;///***
                                curr->ptr_okul=o_bas;///***
                                }else{
                                    o_yeni=(o_node*)malloc((sizeof(o_node)));///***

                                    strcpy(o_yeni->o_ad,o_okunan.o_ad);
                                    strcpy(o_yeni->o_lisans,o_okunan.o_lisans);
                                    strcpy(o_yeni->o_bolum,o_okunan.o_bolum);
                                    o_yeni->baslangic_yili=o_okunan.baslangic_yili;
                                    o_yeni->bitis_yili=o_okunan.bitis_yili;
                                    o_yeni->not_ortalamasi=o_okunan.not_ortalamasi;


                                    o_yeni->sonraki=NULL;///***
                                    o_gezici->sonraki=o_yeni;///***
                                    o_son=o_yeni;///***
                                   o_gezici=o_yeni;///***
                                    }
                        }
                   sayac1++;
           }//while sonu okullar okundu

///is bagli listesi olusturuluyor
  int sayac1=0;
        while(sayac1<k_okunan.is_sayisi)///is bilgileri okunuyor
            {
                    if(fread(&i_okunan,sizeof(struct is),1,dosya)!=1)
                        {
                         break;
                        }else{
                            if(sayac1==0)
                                {
                                i_yeni=(i_node*)malloc(sizeof(i_node));

                                strcpy(i_yeni->is_ad,i_okunan.is_ad);
                                strcpy(i_yeni->is_adres,i_okunan.is_adres);
                                strcpy(i_yeni->is_gorevi,i_okunan.is_gorevi);
                                i_yeni->is_gorev_suresi=i_okunan.is_gorev_suresi;


                                i_yeni->sonraki=NULL;
                                i_bas=i_son=i_yeni;
                                curr->ptr_is=i_bas;
                                }else{
                                    i_yeni=(i_node*)malloc((sizeof(i_node)));

                                    strcpy(i_yeni->is_ad,i_okunan.is_ad);
                                    strcpy(i_yeni->is_adres,i_okunan.is_adres);
                                    strcpy(i_yeni->is_gorevi,i_okunan.is_gorevi);
                                    i_yeni->is_gorev_suresi=i_okunan.is_gorev_suresi;

                                    i_yeni->sonraki=NULL;
                                    i_son->sonraki=i_yeni;
                                    i_son=i_yeni;

                                    }
                        }
                   sayac1++;
           }//while sonu okullar okundu

///yabanci dil bagli listesi olusturuluyor
 sayac1=0;
        while(sayac1<k_okunan.dil_sayisi)///yd bilgileri okunuyor
            {
                    if(fread(&y_okunan,sizeof(struct yabanci_dil),1,dosya)!=1)
                        {
                         break;
                        }else{
                            if(sayac1==0)
                                {
                                y_yeni=(y_node*)malloc(sizeof(y_node));

                                strcpy(y_yeni->dil_ad,y_okunan.dil_ad);

                                y_yeni->sonraki=NULL;
                                y_bas=y_son=y_yeni;
                                curr->ptr_dil=y_bas;
                                sayac1++;
                                }else{
                                    y_yeni=(y_node*)malloc((sizeof(y_node)));

                                   strcpy(y_yeni->dil_ad,y_okunan.dil_ad);

                                    y_yeni->sonraki=NULL;
                                    y_son->sonraki=y_yeni;
                                    y_son=y_yeni;
                                    sayac1++;
                                    }
                        }

           }//while sonu okullar okundu

            /**diger esitlemeler*/

            agaca_ekle(&root,curr);



    }//while sonu



            fclose(dosya);

        }//fonksiyon sonu

void agaci_dosyaya_yaz(node * tree,FILE * dosya){
///agac oluþturmak icin gecici degiskenler
        o_node * j;
        i_node * k;
        y_node * y;

///e kisi tipinde bir struct
///kisi bilgilerini e streuctina atiyor

        strcpy(e.ad,tree->ad);
        strcpy(e.soyad,tree->soyad);
        strcpy(e.kisi_adres,tree->kisi_adres);
         e.telefon=tree->telefon;
        strcpy(e.mail,tree->mail);
        e.dogum_tarihi=tree->dogum_tarihi;
        e.ehliyet_kodlamasi=tree->ehliyet_kodlamasi;
        e.okul_sayisi=tree->okul_sayisi;
        e.is_sayisi=tree->is_sayisi;
        e.dil_sayisi=tree->dil_sayisi;


        fwrite(&e,sizeof(struct KISI),1,dosya);
///okul agaci ekleme
j=tree->ptr_okul;
            int sayac3=0;//agaci dosyaya yazarken dongu kontrol icin
            while(sayac3<e.okul_sayisi){
                strcpy(yazyard.o_ad,j->o_ad);
                strcpy(yazyard.o_lisans,j->o_lisans);
                strcpy(yazyard.o_bolum,j->o_bolum);
                yazyard.baslangic_yili=j->baslangic_yili;
                yazyard.bitis_yili=j->bitis_yili;
                yazyard.not_ortalamasi=j->not_ortalamasi;

                fwrite(&yazyard,sizeof(struct okul),1,dosya);
                j=j->sonraki;

                sayac3++;
                }
///is bilgiler agaca ekleme
 k=tree->ptr_is;
            sayac3=0;//agaci dosyaya yazarken dongu kontrol icin
            while(sayac3<e.is_sayisi)
                {
                strcpy(i_yard.is_ad,k->is_ad);
                strcpy(i_yard.is_adres,k->is_adres);
                strcpy(i_yard.is_gorevi,k->is_gorevi);
                i_yard.is_gorev_suresi=k->is_gorev_suresi;

                fwrite(&i_yard,sizeof(struct is),1,dosya);
                k=k->sonraki;
                sayac3++;
                }


///yabanci dil bilgilerini agac ekleme

y=tree->ptr_dil;
        sayac3=0;
        while(sayac3<e.dil_sayisi)
        {
            strcpy(y_yard.dil_ad,y->dil_ad);
            fwrite(&y_yard,sizeof(struct yabanci_dil),1,dosya);
            sayac3++;
        }

        if(tree->right!=NULL)
        agaci_dosyaya_yaz(tree->right,dosya);
        if(tree->left!=NULL)
        agaci_dosyaya_yaz(tree->left,dosya);


}

void agacdan_silme(node **tree,char silinecek[40]){

          if(!(*tree)){
                printf("Bu isimde birisi bulunmamaktadir !!!!!\nDevam etmek icin herhangi bir tusa basin");
                getch();
                fflush(stdin);
                return;
                }
          if(strcmp(silinecek,(*tree)->ad)==0)
             {
                 if ((*tree) -> left != NULL && (*tree) -> right != NULL )///cift cocuk varsa
                    {
                        parent = *tree ;
                        temp = (*tree) -> right ;
                        while ( (temp) -> left != NULL )
                        {
                            parent = temp ;
                            temp = temp -> left ;
                        }
                        strcpy((*tree) ->ad ,temp -> ad );
                        strcpy((*tree) ->soyad , temp -> soyad );
                        parent->left=NULL;
                        free(temp);
                    }else if((*tree)->left == NULL && (*tree)->right == NULL)///cocuk yok ise
                            {
                                free(tree);
                                *tree=NULL;
                            }else if((*tree)->left==NULL)                    ///tek cocuk varsa
                                    {
                                        node *temp=(*tree);
                                        (*tree)=(*tree)->right;
                                        free(temp);
                                    }
                                    else if((*tree)->right==NULL)
                                    {
                                        node *temp=(*tree);
                                        (*tree)=(*tree)->left;
                                        free(temp);
                                     }
                                     }
                                     else if(strcmp(silinecek,(*tree)->ad)<0)
                                     {
                                         agacdan_silme(&((*tree)->left),silinecek);
                                     }else if(strcmp(silinecek,(*tree)->ad)>0)
                                             {
                                                agacdan_silme(&((*tree)->right),silinecek);
                                             }
}

void agaca_ekle(node **tree,node * item){

            if(!(*tree)){
                *tree=item;
                (*tree)->left=NULL;
                (*tree)->right=NULL;
                return;
            }
            if(strcmp(item->ad,(*tree)->ad)<0)
                {   agaca_ekle(&(*tree)->left,item); }
                else if(strcmp(item->ad,(*tree)->ad)>0)
                {   agaca_ekle(&(*tree)->right,item); }

}

void bilgi_goruntule(){
        FILE * dosya = fopen("bilgiler.txt","rb");
        char aranan_ad[40];
        double aranan_tel;
        char buffer[40];
        int kontrol=0;

        printf("Aranan KISI adi      : ");
         fgets(aranan_ad,40,stdin);
        printf("Aranan kisi telefonu : ");
         fgets(buffer,40,stdin);
          aranan_tel=atof(buffer);
    int i=0;
        rewind(dosya);
    while(1)
    {
        if(fread(&k_okunan,sizeof(struct KISI),1,dosya)!=1){
             printf("\nBu isimde birisi bulunamadi !\n");
                printf("Hatali isim veya telefon numarasi !\n");
                printf("Devam etmek icin herhangi bir tusa basin\n");
                kontrol=2;
        }

        if(kontrol==2)
            break;


        if(strcmp(k_okunan.ad,aranan_ad)==0 && aranan_tel==k_okunan.telefon)
            {
             kontrol=1;
            }

        if(kontrol==0)
        {
            for(i=0; i<k_okunan.okul_sayisi; i++)
            {
                fread(&o_okunan,sizeof(struct okul),1,dosya);
            }
            for(i=0;i<k_okunan.is_sayisi;i++)
            {
                fread(&i_okunan,sizeof(struct is),1,dosya);
            }
            for(i=0;i<k_okunan.dil_sayisi;i++)
            {
                fread(&y_okunan,sizeof(struct yabanci_dil),1,dosya);
            }
            /**bir sonraki kisiye atlamak icn bos okuma yapiliyor*/
        }

        if(kontrol==1)
            {
                    printf("________________________________________________\n");
                    printf("Ad              : %s",k_okunan.ad);
                    printf("Soyad           : %s",k_okunan.soyad);
                    printf("Adres           : %s",k_okunan.kisi_adres);
                    printf("Telefon         : %7.f\n",k_okunan.telefon);
                    printf("Mail            : %s",k_okunan.mail);
                    printf("Dogum Tarihi    : %d\n",k_okunan.dogum_tarihi);
                    ehliyet_cozumle(k_okunan.ehliyet_kodlamasi);
                    printf("________________________________________________\n");
                for(i=0; i<k_okunan.okul_sayisi; i++)
                {
                  fread(&o_okunan,sizeof(struct okul),1,dosya);
                    printf("Okul ad         : %s",o_okunan.o_ad);
                    printf("Okul lisans tipi: %s",o_okunan.o_lisans);
                    printf("Bolum           : %s",o_okunan.o_bolum);

                    printf("Not ortalamasi  : %lf\n",o_okunan.not_ortalamasi);
                    printf("Baslama Yili    : %d\n",o_okunan.baslangic_yili);
                    printf("Bitis Yili      : %d\n",o_okunan.bitis_yili);
                    printf("________________________________________________\n");
                }

                for(i=0;i<k_okunan.is_sayisi;i++)
                {
                    fread(&i_okunan,sizeof(struct is),1,dosya);
                    printf("Is ad           : %s",i_okunan.is_ad);
                    printf("Is adres        : %s",i_okunan.is_adres);
                    printf("Is gorevi       : %s",i_okunan.is_gorevi);
                    printf("Is gorev suresi : %lf\n",i_okunan.is_gorev_suresi);
                    printf("________________________________________________\n");
                }
                for(i=0;i<k_okunan.dil_sayisi;i++){
                    fread(&y_okunan,sizeof(struct yabanci_dil),1,dosya);
                    printf("Yabanci: %s",y_okunan.dil_ad);
                }

             break;
            }//if kontrol==1 sonu

    }//while sonu
    fclose(dosya);
    }

void bilgi_giris(){
           FILE * dosya = fopen("bilgiler.txt","ab+");
           char buffer[40];

           printf("Isim:");
            fgets(eleman.ad,40,stdin);
           printf("Soyad:");
            fgets(eleman.soyad,40,stdin);
           printf("Adres:");
            fgets(eleman.kisi_adres,100,stdin);
           printf("telefon:");
            fgets(buffer,20,stdin);
            eleman.telefon=atof(buffer);
           printf("Mail Adresi:") ;
            fgets(eleman.mail,40,stdin);
           printf("Dogum Tarihi(ornek: 2016)");
            fgets(buffer,20,stdin);
            eleman.dogum_tarihi=atoi(buffer);


            printf("OKUL sayisini giriniz:");
            fgets(buffer,20,stdin);
            eleman.okul_sayisi=atoi(buffer);

            printf("IS sayisini giriniz:");
            fgets(buffer,20,stdin);
            eleman.is_sayisi=atoi(buffer);

            printf("Yabanci Dil sayisini giriniz:");
            fgets(buffer,20,stdin);
            eleman.dil_sayisi=atoi(buffer);


///ehliyet
  char gecici_ehliyet[4];
  char gecici;
            eleman.ehliyet_kodlamasi=0;
            while (1){
                  printf("  Ehliyet Ekleyecekmisiniz (E/H)\n");
                  gecici=getche();
                  printf("\b");
                    if(gecici=='H' || gecici=='h')
                    {
                        break;
                    }
fflush (stdin);
                 printf ("Ehliyet Tipi:                  \n");
                ///*************************** fflush (stdin);
                 scanf ("%2s",gecici_ehliyet);

                if(strcmp ("A2",gecici_ehliyet) == 0)
                    { printf("A2 Eklendi\n");
                     eleman.ehliyet_kodlamasi=(eleman.ehliyet_kodlamasi)*10+1;
                        }
                    else if(strcmp ("B",gecici_ehliyet) == 0)
                            {
                             printf("B Eklendi\n");
                            eleman.ehliyet_kodlamasi=(eleman.ehliyet_kodlamasi)*10+2;
                            }else if(strcmp ("D",gecici_ehliyet) == 0)
                                {
                                    printf("D Eklendi\n");
                                   eleman.ehliyet_kodlamasi= (eleman.ehliyet_kodlamasi)*10+3;
                                }else if(strcmp ("E",gecici_ehliyet) == 0)
                                    {
                                        printf("E Eklendi\n");
                                        eleman.ehliyet_kodlamasi=(eleman.ehliyet_kodlamasi)*10+4;
                                    }else if(strcmp ("G",gecici_ehliyet) == 0)
                                    {
                                        printf("G Eklendi\n");
                                        eleman.ehliyet_kodlamasi=(eleman.ehliyet_kodlamasi)*10+5;
                                    }else if(strcmp ("H",gecici_ehliyet) == 0)
                                            {
                                                printf("H Eklendi\n");
                                            eleman.ehliyet_kodlamasi=(eleman.ehliyet_kodlamasi)*10+6;
                                            }else
                                            {printf("hatali ehliyet tipi !!\n");
                                             continue;
                                            }

                        }
///****************************************
           fwrite(&eleman,sizeof(struct KISI),1,dosya);///KISI bilgileri dosyaya kayit edildi
fflush (stdin);
           struct okul *bas=NULL;
           struct okul *son=NULL;
           struct okul *yeni=NULL;
           struct is *i_bas=NULL;
           struct is *i_son=NULL;
           struct is *i_yeni=NULL;
           struct yabanci_dil *y_bas=NULL;
           struct yabanci_dil *y_son=NULL;
           struct yabanci_dil *y_yeni=NULL;

           int sayac=0;
///okul bilgiler
           while(sayac<eleman.okul_sayisi){
                ///hic okul eklenmediyse
                if(sayac==0)
                    {
                        yeni=malloc(sizeof(struct okul));

                        printf("%d Okul adi:",sayac+1);
                         fgets(yeni->o_ad,40,stdin);
                        printf("%d Okul lisans turu: ",sayac+1);
                         fgets(yeni->o_lisans,40,stdin);
                        printf("%d Bolum:",sayac+1);
                         fgets(yeni->o_bolum,40,stdin);
                        printf("Okula Baslama Yili:");
                         fgets(buffer,40,stdin);
                           yeni->baslangic_yili=atoi(buffer);
                        printf("Mezuniyet Yili:");
                         fgets(buffer,40,stdin);
                           yeni->bitis_yili=atoi(buffer);
                        printf("Okul Not Ortalamasi:");
                         fgets(buffer,40,stdin);
                           yeni->not_ortalamasi=atof(buffer);

                        yeni->sonraki=NULL;
                        bas=son=yeni;
                        eleman.ptr_okul=bas;

                        fwrite(yeni,sizeof(struct okul),1,dosya);
                    sayac++;
                    }else if(sayac>0)///en az bir okul var ise
                            {
                                yeni=malloc(sizeof(struct okul));

                                printf("%d Okul adi:",sayac+1);
                                 fgets(yeni->o_ad,40,stdin);
                                 printf("%d Okul lisans turu:",sayac+1);
                                 fgets(yeni->o_lisans,40,stdin);
                                printf("%d Bolum:",sayac+1);
                                 fgets(yeni->o_bolum,40,stdin);
                                printf("Okula Baslama Yili:");
                                 fgets(buffer,40,stdin);
                                 yeni->baslangic_yili=atoi(buffer);
                                printf("Mezuniyet Yili:");
                                 fgets(buffer,40,stdin);
                                  yeni->bitis_yili=atoi(buffer);
                                printf("Okul Not Ortalamasi:");
                                 fgets(buffer,40,stdin);
                                  yeni->not_ortalamasi=atof(buffer);



                                yeni->sonraki=NULL;
                                son->sonraki=yeni;
                                son=yeni;
                                fwrite(son,sizeof(struct okul),1,dosya);
                                sayac++;
                            }

           }//while sonu

///is bilgiler
                sayac=0;
                while(sayac<eleman.is_sayisi){
                ///hic IS eklenmediyse
                if(sayac==0)
                    {
                        i_yeni=malloc(sizeof(struct is));

                        printf("%d. Is adi:",sayac+1);
                          fgets(i_yeni->is_ad,40,stdin);
                        printf("%d. Is yeri adresi:",sayac+1);
                          fgets(i_yeni->is_adres,40,stdin);
                        printf("%d. Is goreviniz:",sayac+1);
                          fgets(i_yeni->is_gorevi,40,stdin);
                        printf("Gorev suresi:");
                          fgets(buffer,40,stdin);
                          i_yeni->is_gorev_suresi=atof(buffer);


                        sayac++;
                        i_yeni->sonraki=NULL;
                        i_bas=i_son=i_yeni;
                        eleman.ptr_is=i_bas;

                        fwrite(i_yeni,sizeof(struct is),1,dosya);
                    }else if(sayac>0)///en az bir IS var ise
                            {
                                i_yeni=malloc(sizeof(struct is));
                                printf("%d. Is adi:",sayac+1);
                                  fgets(i_yeni->is_ad,40,stdin);
                                printf("%d. Is yeri adresi:",sayac+1);
                                  fgets(i_yeni->is_adres,40,stdin);
                                printf("%d. Is goreviniz:",sayac+1);
                                  fgets(i_yeni->is_gorevi,40,stdin);
                                printf("Gorev suresi");
                                  fgets(buffer,40,stdin);
                                  i_yeni->is_gorev_suresi=atof(buffer);

                                sayac++;
                                i_yeni->sonraki=NULL;
                                i_son->sonraki=i_yeni;
                                i_son=i_yeni;
                                fwrite(i_yeni,sizeof(struct is),1,dosya);
                            }
           }//while sonu
///YABANCI DIL
                sayac=0;
                while(sayac<eleman.dil_sayisi){
                ///hic yd eklenmediyse
                if(sayac==0)
                    {
                        y_yeni=malloc(sizeof(struct yabanci_dil));

                        printf("%d Yabanci Dil Adi:",sayac+1);
                          fgets(y_yeni->dil_ad,40,stdin);

                        sayac++;
                        y_yeni->sonraki=NULL;
                        y_bas=y_son=y_yeni;
                        eleman.ptr_dil=y_bas;
                        fwrite(y_yeni,sizeof(struct yabanci_dil),1,dosya);
                    }else if(sayac>0)///en az bir yd eklenmis ise
                            {
                                y_yeni=malloc(sizeof(struct yabanci_dil));
                                printf("%d Yabanci Dil Adi:",sayac+1);
                                  fgets(y_yeni->dil_ad,40,stdin);
                                sayac++;
                                y_yeni->sonraki=NULL;
                                y_son->sonraki=y_yeni;
                                y_son=y_yeni;
                                fwrite(y_yeni,sizeof(struct yabanci_dil),1,dosya);

                            }

           }//while sonu
           fclose(dosya);
    }//fonksiyon sonu


void ehliyet_cozumle(int ehliyetkod){
    int eh_kontrol;
    while(1)
    {
    if(ehliyetkod==0)
        {printf("Ehliyet Sonu\n");
        return;}
        else
        {
          eh_kontrol=ehliyetkod%10;
            if(eh_kontrol==1)
                printf(" A2 ");
                else if(eh_kontrol==2)
                    printf(" B ");
                else if(eh_kontrol==3)
                    printf(" D ");
                else if(eh_kontrol==4)
                    printf(" E ");
                else if(eh_kontrol==5)
                    printf(" G ");
                else if(eh_kontrol==6)
                    printf(" H ");



         ehliyetkod=ehliyetkod/10;
        }
    }
}


void birden_fazla_dil_bilenler(node*tree){

    if(tree==NULL){
       return;
    }

    fazla_dilli=0;
    dil_sayisigecici=tree->dil_sayisi;
    if(!(2>dil_sayisigecici))
        {fazla_dilli=1;}

    if(fazla_dilli==1)
    {
        printf("%s%s\n",tree->ad,tree->soyad);
    }
    if(fazla_dilli==0)
    {
        strcpy(dil_temiz,tree->ad);
        agacdan_silme(&root,dil_temiz);
    }
/*
    a_gecici=tree->dil_sayisi;
   if(a_gecici>1)
    {
        printf("%s%s\n",tree->ad,tree->soyad);
    }else{

    }
*/
        if((tree)->left)
            birden_fazla_dil_bilenler((tree)->left);
        if((tree)->right)
            birden_fazla_dil_bilenler((tree)->right);

///strstr(s1, s2) s1 iicinde s2 yi arar-bulursa adres dondurur

}
