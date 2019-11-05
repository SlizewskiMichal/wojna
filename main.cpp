#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <time.h>
using namespace std;
class karta{
public:
    string figura;
    string kolor;
    void wypiszKarte(){
        cout<<figura<<" "<<kolor;
    }
};
class gracz{
public:
    queue<karta> reka;
    void dodajStosDoKolejki(stack<karta> stosDoWziecia){
        while (!stosDoWziecia.empty())
        {
            reka.push(stosDoWziecia.top());
            stosDoWziecia.pop();
        }
    }
    int ileKartWKolejce(){
        return reka.size();
    }
    void dodanieDoKolejki(karta karta){
        reka.push(karta);
    }
    karta usuniecieZKolejki(){
        karta goraKolejki=reka.front();
        reka.pop();
        return goraKolejki;
    }
};
vector<string> figury;
vector<string> kolory;
vector<karta> wypelnienieITasowanie();
bool czyKtosWygral(gracz pierwszy,gracz drugi){
    if(pierwszy.ileKartWKolejce()==0||drugi.ileKartWKolejce()==0)
        return true;
    return false;
}
void wpiszFiguryIKolory();
void rozdanie(gracz &pierwszy,gracz &drugi,vector<karta> talia);
bool czyPierwszyGraczWygral(karta &kartaGracza1,karta &kartaGracza2);
void runda(gracz &pierwszy,gracz &drugi);
void wojna(stack<karta> stolPoprzedni,gracz &pierwszy,gracz &drugi);
void wojna(stack<karta> stolPoprzedni,gracz &pierwszy,gracz &drugi){
    karta kartaGracza1zaslonieta=pierwszy.usuniecieZKolejki();
    karta kartaGracza2zaslonieta=drugi.usuniecieZKolejki();
    cout<<"Gracz pierwszy wystawia zaslonieta karte : ";
    kartaGracza1zaslonieta.wypiszKarte();
    cout<<"     ";
    cout<<"Gracz drugi wystawia zaslonieta karte : ";
    kartaGracza2zaslonieta.wypiszKarte();
    stolPoprzedni.push(kartaGracza1zaslonieta);
    stolPoprzedni.push(kartaGracza2zaslonieta);
    cout<<endl;
    if(pierwszy.ileKartWKolejce()!=0&&drugi.ileKartWKolejce()!=0){
        karta kartaGracza1=pierwszy.usuniecieZKolejki();
        karta kartaGracza2=drugi.usuniecieZKolejki();
        cout<<"Gracz pierwszy wystawia: ";
        kartaGracza1.wypiszKarte();
        cout<<"Gracz drugi wystawia: ";
        kartaGracza2.wypiszKarte();
        cout<<endl;
        stolPoprzedni.push(kartaGracza1);
        stolPoprzedni.push(kartaGracza2);
        if(kartaGracza2.figura==kartaGracza1.figura&&pierwszy.ileKartWKolejce()!=0&&drugi.ileKartWKolejce()!=0){
            cout<<"znowu wojna!"<<endl;
            wojna(stolPoprzedni, pierwszy, drugi);
        }
        else{
            if(czyPierwszyGraczWygral(kartaGracza1, kartaGracza2)&&kartaGracza2.figura!=kartaGracza1.figura){
                cout<<"Gracz pierwszy wygrywa wojne i bierze caly stos do swojej kolejki"<<endl;
                pierwszy.dodajStosDoKolejki(stolPoprzedni);
            }
            if(!czyPierwszyGraczWygral(kartaGracza1, kartaGracza2)&&kartaGracza2.figura!=kartaGracza1.figura){
                cout<<"Gracz drugi wygrywa wojne i bierze caly stos do swojej kolejki"<<endl;
                drugi.dodajStosDoKolejki(stolPoprzedni);
            }
            if(kartaGracza2.figura==kartaGracza1.figura){
                if(pierwszy.ileKartWKolejce()==0)
                    drugi.dodajStosDoKolejki(stolPoprzedni);
                if(drugi.ileKartWKolejce()==0)
                    pierwszy.dodajStosDoKolejki(stolPoprzedni);
            }
        }
    }
    else{
        if(pierwszy.ileKartWKolejce()==0)
            drugi.dodajStosDoKolejki(stolPoprzedni);
        if(drugi.ileKartWKolejce()==0)
            pierwszy.dodajStosDoKolejki(stolPoprzedni);
    }
}

bool czyPierwszyGraczWygral(karta &kartaGracza1,karta &kartaGracza2){
    for(int i=12;i>=0;i--){
        if(kartaGracza1.figura==figury[i])
            return true;
        if(kartaGracza2.figura==figury[i])
            return false;
    }
    return false;
}
void runda(gracz &pierwszy,gracz &drugi){
    stack<karta> stol;
    karta kartaGracza1,kartaGracza2;
    kartaGracza1=pierwszy.usuniecieZKolejki();
    kartaGracza2=drugi.usuniecieZKolejki();
    cout<<"Gracz pierwszy wystawia: ";
    kartaGracza1.wypiszKarte();
    cout<<"     ";
    cout<<"Gracz drugi wystawia: ";
    kartaGracza2.wypiszKarte();
    cout<<endl;
    stol.push(kartaGracza1);
    stol.push(kartaGracza2);
    if(kartaGracza2.figura==kartaGracza1.figura&&pierwszy.ileKartWKolejce()!=0&&drugi.ileKartWKolejce()!=0){
        cout<<"wojna!"<<endl;
        wojna(stol, pierwszy, drugi);
    }
    else{
        if(czyPierwszyGraczWygral(kartaGracza1, kartaGracza2)){
            cout<<"Gracz pierwszy wygrał rundę i bierze stos do swojej kolejki"<<endl;
            pierwszy.dodajStosDoKolejki(stol);
        }
        else{
            cout<<"Gracz drugi wygrał rundę i bierze stos do swojej kolejki"<<endl;
            drugi.dodajStosDoKolejki(stol);
        }
    }
}
void rozdanie(gracz &pierwszy,gracz &drugi,vector<karta> talia){
    for(int i=0;i<52;i+=2){
        pierwszy.dodanieDoKolejki(talia[i]);
        drugi.dodanieDoKolejki(talia[i+1]);
        talia[i].wypiszKarte();
        cout<<"                   ";
        talia[i+1].wypiszKarte();
        cout<<endl;
    }
}
vector<karta> wypelnienieITasowanie(){
    vector<karta> talia;
    wpiszFiguryIKolory();
    for(int i=0;i<13;i++){
        for(int j=0;j<4;j++){
            karta kartaDoPotasowania;
            kartaDoPotasowania.figura=figury[i];
            kartaDoPotasowania.kolor=kolory[j];
            talia.push_back(kartaDoPotasowania);
        }
    }
    for(int i=0;i<52;i++){
        int indeks1=rand()%52;
        int indeks2=rand()%52;
        karta bufor;
        bufor=talia[indeks1];
        talia[indeks1]=talia[indeks2];
        talia[indeks2]=bufor;
    }
    return talia;
}
void wpiszFiguryIKolory(){
    figury.push_back("2");
    figury.push_back("3");
    figury.push_back("4");
    figury.push_back("5");
    figury.push_back("6");
    figury.push_back("7");
    figury.push_back("8");
    figury.push_back("9");
    figury.push_back("10");
    figury.push_back("W");
    figury.push_back("D");
    figury.push_back("K");
    figury.push_back("A");
    kolory.push_back("TREFL");
    kolory.push_back("PIK");
    kolory.push_back("KARO");
    kolory.push_back("KIER");
}
int main() {
    srand (time(NULL));
    vector<karta> talia;
    talia=wypelnienieITasowanie();
    gracz pierwszy,drugi;
    cout<<"gracz1                   gracz2"<<endl;
    rozdanie(pierwszy, drugi, talia);
    cout<<endl;
    cout<<endl<<"wpisz cos aby zacząć: "<<endl;
    string startvar;
    cin>>startvar;
    while(!czyKtosWygral(pierwszy,drugi)){
        runda(pierwszy, drugi);
    }
    if(pierwszy.ileKartWKolejce()==0)
        cout<<"GRACZ 2 WYGRAŁ!";
    else
        cout<<"GRACZ 1 WYGRAŁ!";
}
