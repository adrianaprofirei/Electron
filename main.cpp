#include <bits/stdc++.h>
#include <graphics.h>
#include <winbgim.h>
#define pb push_back
#define pf push_front
#define LATIME_WINDOW 1850
#define LUNGIME_WINDOW 930
#define X1 200
#define Y1 200
#define X2 LATIME_WINDOW - 200
#define Y2 LUNGIME_WINDOW - 100
#define DIMENSIUNE_MIN -3
#define DIMENSIUNE_MAX 6

using namespace std;


/// Istoricul fiecarui pixel
deque < int > h[LATIME_WINDOW+1][LUNGIME_WINDOW+1];

/// Obiecte de baza
struct Punct
{
    int x, y;
};

struct Linie
{
    Punct p1, p2;
    int culoare;
};

struct Legatura
{
    Punct p1, p2;
    Linie L1, L2;
    bool mai_mica_intai = 1;
};

struct crt1
{
    bool operator()(Legatura Leg1, Legatura Leg2)
    {
        if((Leg1.p1.x < Leg2.p1.x) || (Leg1.p1.x == Leg2.p1.x && Leg1.p1.y < Leg2.p1.y)) return 1;
        return 0;
    }
};
multiset < Legatura, crt1 > Legaturi;

struct Buton
{
    Punct p1, p2;
    string text;
    int latime, lungime, culoare_off, culoare_on, start_text_x, start_text_y;
    bool stare;
};

struct crt2
{
    bool operator()(Buton b1, Buton b2)
    {
        if((b1.p1.x < b2.p2.x) || (b1.p1.x == b2.p2.x && b1.p1.y < b2.p2.y)) return 1;
        return 0;
    }
};
multiset < Buton, crt2 > Butoane;



/// Piese: nod, generator, rezistor, condensator, amplificator operational, dioda Tunnel, dioda Zener, tranzistor NPN, tranzistor PNP, voltmetru, potentiometru, bec
struct Nod
{
    Punct centru, margine1, margine2, conect[5];
    string text;
    int culoare, raza, dimensiune = 0, orientare = 0;
    bool if_conect[5] = {0}, show_text;
};

struct crt3
{
    bool operator()(Nod a, Nod b)
    {
        if((a.centru.x < b.centru.x) || (a.centru.x == b.centru.x && a.centru.y < b.centru.y)) return 1;
        return 0;
    }
};
multiset < Nod, crt3 > Noduri;


struct Generator
{
    Punct centru, margine1, margine2, conect[3];
    Linie linie_plus, linie_minus, linie_spre_plus, linie_spre_minus, linie_plus_a, linie_plus_b, linie_minus_a;
    string text;
    int dimensiune = 0, orientare = 0;
    int lg_linie_minus, lg_linie_plus, lg_linie_spre, lg_linie_plus_a, lg_linie_plus_b, lg_linie_minus_a, dist_de_la_centru, culoare;
    bool show_text, if_conect[3] = {0};
};

struct crt4
{
    bool operator()(Generator a, Generator b)
    {
        if((a.centru.x < b.centru.x) || (a.centru.x == b.centru.x && a.centru.y < b.centru.y)) return 1;
        return 0;
    }
};
multiset < Generator, crt4 > Generatoare;


struct Rezistor
{
    Punct centru, margine1, margine2, conect[3];
    Linie linie_orizontala_sus, linie_orizontala_jos, linie_verticala_st, linie_verticala_dr, linie_spre_st, linie_spre_dr;
    string text;
    int dimensiune = 0, orientare = 0;
    int lg_linie_orizontala_sus, lg_linie_orizontala_jos, lg_linie_verticala_st, lg_linie_verticala_dr, dist_de_la_centru_spre_x, dist_de_la_centru_spre_y, lg_linie_spre_st, lg_linie_spre_dr, culoare;
    bool show_text, if_conect[3] = {0};
};

struct crt5
{
    bool operator()(Rezistor a, Rezistor b)
    {
        if((a.centru.x < b.centru.x) || (a.centru.x == b.centru.x && a.centru.y < b.centru.y)) return 1;
        return 0;
    }
};
multiset < Rezistor, crt5 > Rezistoare;


struct Condensator
{
    Punct centru, margine1, margine2, conect[3];
    Linie linie_orizontala_st, linie_orizontala_dr, linie_verticala_st, linie_verticala_dr;
    string text;
    int dimensiune = 0, orientare = 0;
    int lg_linie_orizontala_st, lg_linie_orizontala_dr, lg_linie_verticala_st, lg_linie_verticala_dr, dist_de_la_centru, culoare;
    bool show_text, if_conect[3] = {0};
};

struct crt6
{
    bool operator()(Condensator a, Condensator b)
    {
        if((a.centru.x < b.centru.x) || (a.centru.x == b.centru.x && a.centru.y < b.centru.y)) return 1;
        return 0;
    }
};
multiset < Condensator, crt6 > Condensatoare;


struct Amplificator_operational
{
    Punct centru, margine1, margine2, conect[4];
    Linie linie_orizontala_dr, linie_st, linie_sus, linie_jos, linie_a, linie_b, linie_minus, linie_plus_a, linie_plus_b;
    string text;
    int dimensiune = 0, orientare = 0;
    int lg_linie_orizontala_dr, lg_linie_st, lg_linie_sus, lg_linie_jos, lg_linie_a, lg_linie_b, lg_linie_plus_a, lg_linie_plus_b, lg_linie_minus, dist_de_la_centru, culoare;
    bool show_text, if_conect[4] = {0};
};

struct crt7
{
    bool operator()(Amplificator_operational a, Amplificator_operational b)
    {
        if((a.centru.x < b.centru.x) || (a.centru.x == b.centru.x && a.centru.y < b.centru.y)) return 1;
        return 0;
    }
};
multiset < Amplificator_operational, crt7 > Amplificatoare_operationale;


struct Dioda_tunnel
{
    Punct centru, margine1, margine2, conect[3];
    Linie linie_orizontala_st, linie_orizontala_dr, linie_st, linie_dr, linie_sus, linie_jos, linie_a, linie_b;
    string text;
    int dimensiune = 0, orientare = 0;
    int lg_linie_orizontala_st, lg_linie_orizontala_dr, lg_linie_st, lg_linie_dr, lg_linie_sus, lg_linie_jos, lg_linie_a, lg_linie_b, dist_de_la_centru, culoare;
    bool show_text, if_conect[3] = {0};
};

struct crt8
{
    bool operator()(Dioda_tunnel a, Dioda_tunnel b)
    {
        if((a.centru.x < b.centru.x) || (a.centru.x == b.centru.x && a.centru.y < b.centru.y)) return 1;
        return 0;
    }
};
multiset < Dioda_tunnel, crt8 > Diode_tunnel;


struct Dioda_zener
{
    Punct centru, margine1, margine2, conect[3];
    Linie linie_orizontala_st, linie_orizontala_dr, linie_st, linie_dr, linie_sus, linie_jos, linie_a, linie_b;
    string text;
    int dimensiune = 0, orientare = 0;
    int lg_linie_orizontala_st, lg_linie_orizontala_dr, lg_linie_st, lg_linie_dr, lg_linie_sus, lg_linie_jos, lg_linie_a, lg_linie_b, dist_de_la_centru, culoare;
    bool show_text, if_conect[3] = {0};
};

struct crt9
{
    bool operator()(Dioda_zener a, Dioda_zener b)
    {
        if((a.centru.x < b.centru.x) || (a.centru.x == b.centru.x && a.centru.y < b.centru.y)) return 1;
        return 0;
    }
};
multiset < Dioda_zener, crt9 > Diode_zener;


struct Tranzistor_npn
{
    Punct centru, margine1, margine2, conect[4];
    Linie linie_orizontala, linie_verticala, linie_oblica_sus, linie_oblica_jos, linie_sus, linie_jos, linie_a, linie_b, linie_c;
    string text;
    int dimensiune = 0, orientare = 0;
    int lg_linie_orizontala, lg_linie_verticala, lg_linie_oblica_sus, lg_linie_oblica_jos, lg_linie_sus, lg_linie_jos, lg_linie_a, lg_linie_b, lg_linie_c, dist_de_la_centru, culoare;
    bool show_text, if_conect[4] = {0};
};

struct crt10
{
    bool operator()(Tranzistor_npn a, Tranzistor_npn b)
    {
        if((a.centru.x < b.centru.x) || (a.centru.x == b.centru.x && a.centru.y < b.centru.y)) return 1;
        return 0;
    }
};
multiset < Tranzistor_npn, crt10 > Tranzistoare_npn;


struct Tranzistor_pnp
{
    Punct centru, margine1, margine2, conect[4];
    Linie linie_orizontala, linie_verticala, linie_oblica_sus, linie_oblica_jos, linie_sus, linie_jos, linie_a, linie_b, linie_c;
    string text;
    int dimensiune = 0, orientare = 0;
    int lg_linie_orizontala, lg_linie_verticala, lg_linie_oblica_sus, lg_linie_oblica_jos, lg_linie_sus, lg_linie_jos, lg_linie_a, lg_linie_b, lg_linie_c, dist_de_la_centru, culoare;
    bool show_text, if_conect[4] = {0};
};

struct crt11
{
    bool operator()(Tranzistor_pnp a, Tranzistor_pnp b)
    {
        if((a.centru.x < b.centru.x) || (a.centru.x == b.centru.x && a.centru.y < b.centru.y)) return 1;
        return 0;
    }
};
multiset < Tranzistor_pnp, crt11 > Tranzistoare_pnp;


struct Voltmetru
{
    Punct centru, margine1, margine2, conect[3];
    Linie linie_orizontala_st, linie_orizontala_dr, linie_st, linie_dr;
    string text;
    int dimensiune = 0, orientare = 0;
    int lg_linie_orizontala_st, lg_linie_orizontala_dr, lg_linie_st, lg_linie_dr, dist_de_la_centru, culoare;
    bool show_text, if_conect[3] = {0};
};

struct crt12
{
    bool operator()(Voltmetru a, Voltmetru b)
    {
        if((a.centru.x < b.centru.x) || (a.centru.x == b.centru.x && a.centru.y < b.centru.y)) return 1;
        return 0;
    }
};
multiset < Voltmetru, crt12 > Voltmetre;


struct Potentiometru
{
    Punct centru, margine1, margine2, conect[3];
    Linie linie_orizontala_st, linie_orizontala_dr, linie_st, linie_dr, linie_1, linie_2, linie_3, linie_4, linie_5;
    string text;
    int dimensiune = 0, orientare = 0;
    int lg_linie_orizontala_st, lg_linie_orizontala_dr, lg_linie_st, lg_linie_dr, lg_linie_1, lg_linie_2, lg_linie_3, lg_linie_4, lg_linie_5, dist_de_la_centru, culoare;
    bool show_text, if_conect[3] = {0};
};

struct crt13
{
    bool operator()(Potentiometru a, Potentiometru b)
    {
        if((a.centru.x < b.centru.x) || (a.centru.x == b.centru.x && a.centru.y < b.centru.y)) return 1;
        return 0;
    }
};
multiset < Potentiometru, crt13 > Potentiometre;


struct Bec
{
    Punct centru, margine1, margine2, conect[3];
    Linie linie_orizontala_st, linie_orizontala_dr, linie_st, linie_dr;
    string text;
    int dimensiune = 0, orientare = 0;
    int lg_linie_orizontala_st, lg_linie_orizontala_dr, lg_linie_st, lg_linie_dr, dist_de_la_centru, culoare;
    bool show_text, if_conect[3] = {0};
};

struct crt14
{
    bool operator()(Bec a, Bec b)
    {
        if((a.centru.x < b.centru.x) || (a.centru.x == b.centru.x && a.centru.y < b.centru.y)) return 1;
        return 0;
    }
};
multiset < Bec, crt14 > Becuri;


/// Functii random


void afiseaza_eroare(string text);

bool verif_punct_apartine_linie(Punct p, Linie L);
bool verif_punct_apartine_legatura(Punct p, Legatura Leg);
void modificare_legatura(Legatura Leg);



bool verif_punct_apartine_chenar(Punct p);
bool verif_piesa_suprapune_piesa(Punct margine1, Punct margine2, Punct margine3, Punct margine4);
bool verif_se_suprapune(Punct margine1, Punct margine2);


void regleaza_linie_dreapta(Linie &L);


void seteaza_linii_legatura(Legatura &Leg);
void deseneaza_legatura(Legatura Leg);
void sterge_ultima_legatura(Legatura Leg);



void deseneaza_cerc_gol(Punct centru, int raza, int culoare);
void sterge_cerc_gol(Punct centru, int raza);
void deseneaza_cerc_plin(Punct centru, int raza, int culoare);
void sterge_cerc_plin(Punct centru, int raza);


void coloreaza_dreptunghi(Punct p1, Punct p2, int culoare);

Linie setare_linie(Punct p1, Punct p2, int culoare);
void deseneaza_linie_dreapta(Linie L1);
void sterge_ultima_linie_dreapta(Linie L1);

Punct click_stanga();

void stergere_totala();



void deseneaza_linie_diagonala(Linie L);
void sterge_ultima_linie_diagonala(Linie L);


void setare_condensator(Condensator &c, Punct centru);
void deseneaza_condensator(Condensator c);
void sterge_ultimul_condensator(Condensator c);



int distanta_dintre_2_puncte(Punct p1, Punct p2);


void rotire_punct(Punct centru, Punct &p);
void rotire_linie(Punct centru, Linie &L);



void deseneaza_text(string text, Punct centru)
{
    int start_text_x, start_text_y;

    if(text != "")
    {
        text = text;
        start_text_y = centru.y - 7;
        start_text_x = centru.x - 5 - 3 * (text.size() - 1);

        setcolor(WHITE), setbkcolor(0);
        char c[text.size()];
        strcpy(c, text.c_str());
        outtextxy(start_text_x, start_text_y, (char*)c);
    }
}

void sterge_text(string text, Punct centru)
{
    int i, j;

    if(text != "")
    {
        char c[text.size()];
        strcpy(c, text.c_str());
        for(i = centru.x - textwidth((char*)c) / 2 - 5; i <= centru.x + textwidth((char*)c) / 2 + 10; i++)
            for(j = centru.y - textheight((char*)c) - 1; j <= centru.y + textheight((char*)c) + 1; j++)
            {
                if(h[i][j].empty() != 0) putpixel(i, j, 0);
                else putpixel(i, j, h[i][j].back());
            }
    }
}

string scrie_text(Punct p, string text)
{
    char c;

    text.pb('_');
    deseneaza_text(text, p);
    while(kbhit() == 0) delay(50);
    c = getch();
    text.pop_back();
    while(c != (char)13)
    {
        sterge_text(text, p);

        if(c == (char)8 && text.empty() == 0)
        {
            text.pop_back();
            text.pb('_');
            deseneaza_text(text, p);

            while(kbhit() == 0) delay(50);
            c = getch();
            sterge_text(text, p);
            text.pop_back();
            deseneaza_text(text, p);
        }
        else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        {
            text.pb(c);
            text.pb('_');
            deseneaza_text(text, p);

            while(kbhit() == 0) delay(50);
            c = getch();
            sterge_text(text, p);
            text.pop_back();
            deseneaza_text(text, p);
        }
    }

    return text;
}




class BUTON
{
public:Buton setare_buton(Punct p1, Punct p2, int culoare_off, int culoare_on, bool stare, string text)
{
    Buton b;

    b.p1 = p1, b.p2 = p2, b.latime = abs(b.p2.x - b.p1.x) + 1, b.lungime = abs(b.p2.y - b.p1.y) + 1, b.culoare_off = culoare_off, b.culoare_on = culoare_on, b.stare = stare;
    if(text != "")
    {
        b.text = text;
        b.start_text_y = (b.p1.y + b.p2.y) / 2 - 7;
        b.start_text_x = (b.p1.x + b.p2.x) / 2 - 5 - 3 * (text.size() - 1);
    }

    return b;
}

public:void deseneaza_buton(Buton b)
{
    if(b.stare == 0) coloreaza_dreptunghi(b.p1, b.p2, b.culoare_off);
    else coloreaza_dreptunghi(b.p1, b.p2, b.culoare_on);

    if(b.text != "")
    {
        setcolor(WHITE);
        if(b.stare == 0) setbkcolor(b.culoare_off);
        else setbkcolor(b.culoare_on);

        char c[b.text.size()];
        strcpy(c, b.text.c_str());
        outtextxy(b.start_text_x, b.start_text_y, (char*)c);
    }

    Butoane.insert(b);
}

public:void sterge_ultimul_buton(Buton b)
{
    int i, j;

    if(b.p1.x > b.p2.x) swap(b.p1.x, b.p2.x);
    if(b.p1.y > b.p2.y) swap(b.p1.y, b.p2.y);

    setcolor(0);
    bar(b.p1.x, b.p1.y, b.p2.x, b.p2.y);

    for(i = b.p1.x; i <= b.p2.x; i++)
        for(j = b.p1.y; j <= b.p2.y; j++) h[i][j].pop_back();

    Butoane.erase(b);
}

public:void apasare_buton(Buton &b)
{
    b.stare ^= 1;
}

public:bool verif_punct_apartine_buton(Punct p, Buton b)
{
    if(p.x >= min(b.p1.x, b.p2.x) && p.x <= max(b.p1.x, b.p2.x) && p.y >= min(b.p1.y, b.p2.y) && p.y <= max(b.p1.y, b.p2.y)) return 1;
    return 0;
}

public:void actioneaza_buton(Buton &b)
{
    apasare_buton(b);
    sterge_ultimul_buton(b);
    deseneaza_buton(b);
}

};





/// Clasele pieselor
class NOD
{
    BUTON buton;

public:void setare(Nod &n, Punct centru, string text, bool show_text)
{
    int i, j;

    n.centru = centru, n.raza = 12 + n.dimensiune, n.culoare = 15;
    n.text = text, n.show_text = show_text;

    n.margine1.x = n.centru.x - n.raza, n.margine1.y = n.centru.y - n.raza;
    n.margine2.x = n.centru.x + n.raza, n.margine2.y = n.centru.y + n.raza;


    n.conect[1].x = n.centru.x - n.raza, n.conect[1].y = n.centru.y;
    n.conect[2].x = n.centru.x, n.conect[2].y = n.centru.y + n.raza;
    n.conect[3].x = n.centru.x + n.raza, n.conect[3].y = n.centru.y;
    n.conect[4].x = n.centru.x, n.conect[4].y = n.centru.y - n.raza;

    for(i = 1; i <= n.orientare; i++)
        for(j = 1; j <= 4; j++)
            rotire_punct(n.centru, n.conect[j]);
}

public:void deseneaza(Nod n)
{
    if(n.culoare != 0)
    {
        deseneaza_cerc_plin(n.centru, n.raza, n.culoare);
        Noduri.insert(n);

        Punct p;
        if(n.show_text == 1)
        {
            if(n.orientare == 0 || n.orientare == 2) p.x = n.centru.x, p.y = max(n.margine1.y, n.margine2.y) + 10;
            else p.x = max(n.margine1.x, n.margine2.x) + 17, p.y = n.centru.y;

            deseneaza_text(n.text, p);
        }
    }
}

public:void sterge_ultimul(Nod n)
{
    if(Noduri.find(n) != Noduri.end())
    {
        sterge_cerc_plin(n.centru, n.raza);
        Noduri.erase(Noduri.find(n));

        Punct p;
        if(n.show_text == 1)
        {
            if(n.orientare == 0 || n.orientare == 2) p.x = n.centru.x, p.y = max(n.margine1.y, n.margine2.y) + 10;
            else p.x = max(n.margine1.x, n.margine2.x) + 17, p.y = n.centru.y;

            sterge_text(n.text, p);
        }
    }
}

public:void zoom_in(Nod &n)
{
    if(n.dimensiune == DIMENSIUNE_MAX) afiseaza_eroare("Nodul are dimensiunea maxima!");
    else
    {
        n.dimensiune++;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void zoom_out(Nod &n)
{
    if(n.dimensiune == DIMENSIUNE_MIN) afiseaza_eroare("Nodul are dimensiunea minima!");
    else
    {
        n.dimensiune--;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void rotire(Nod &n)
{
    n.orientare = (n.orientare + 1) % 4;
    setare(n, n.centru, n.text, n.show_text);
}

public:bool verif_punct_apartine(Punct p, Nod n)
{
    return p.x >= min(n.margine1.x, n.margine2.x) && p.x <= max(n.margine1.x, n.margine2.x) && p.y >= min(n.margine1.y, n.margine2.y) && p.y <= max(n.margine1.y, n.margine2.y);
}

public:bool verif_legatura_atinge(Legatura Leg, Nod n)
{
    return (verif_punct_apartine(Leg.p1, n) || verif_punct_apartine(Leg.p2, n));
}

public:void setare_legaturi(Nod n, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    if(Leg[nr_de_legaturi].p1.x == n.conect[1].x && Leg[nr_de_legaturi].p1.y == n.conect[1].y) caz[nr_de_legaturi] = 1;
    else if(Leg[nr_de_legaturi].p1.x == n.conect[2].x && Leg[nr_de_legaturi].p1.y == n.conect[2].y) caz[nr_de_legaturi] = 2;
    else if(Leg[nr_de_legaturi].p1.x == n.conect[3].x && Leg[nr_de_legaturi].p1.y == n.conect[3].y) caz[nr_de_legaturi] = 3;
    else if(Leg[nr_de_legaturi].p1.x == n.conect[4].x && Leg[nr_de_legaturi].p1.y == n.conect[4].y) caz[nr_de_legaturi] = 4;
    else if(Leg[nr_de_legaturi].p2.x == n.conect[1].x && Leg[nr_de_legaturi].p2.y == n.conect[1].y) caz[nr_de_legaturi] = 5;
    else if(Leg[nr_de_legaturi].p2.x == n.conect[2].x && Leg[nr_de_legaturi].p2.y == n.conect[2].y) caz[nr_de_legaturi] = 6;
    else if(Leg[nr_de_legaturi].p2.x == n.conect[3].x && Leg[nr_de_legaturi].p2.y == n.conect[3].y) caz[nr_de_legaturi] = 7;
    else if(Leg[nr_de_legaturi].p2.x == n.conect[4].x && Leg[nr_de_legaturi].p2.y == n.conect[4].y) caz[nr_de_legaturi] = 8;
}

public:void deseneaza_legaturi(Nod n, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    int i;

    for(i = 1; i <= nr_de_legaturi; i++)
    {
        if(caz[i] == 1) Leg[i].p1 = n.conect[1];
        else if(caz[i] == 2) Leg[i].p1 = n.conect[2];
        else if(caz[i] == 3) Leg[i].p1 = n.conect[3];
        else if(caz[i] == 4) Leg[i].p1 = n.conect[4];
        else if(caz[i] == 5) Leg[i].p2 = n.conect[1];
        else if(caz[i] == 6) Leg[i].p2 = n.conect[2];
        else if(caz[i] == 7) Leg[i].p2 = n.conect[3];
        else if(caz[i] == 8) Leg[i].p2 = n.conect[4];

        seteaza_linii_legatura(Leg[i]);
        deseneaza_legatura(Leg[i]);
    }
}


public:void Mod_punere(Buton &Punere_generator)
{
    Nod g;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0)
    {
        sterge_ultimul(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
        getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

        setare(g, p1, "", 0);
        if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
    }

    buton.actioneaza_buton(Punere_generator);
};

public:void Mutare(Punct p1, bool &gasit)
{
    Nod g;
    Legatura Leg[5];
    Punct p2 = p1;
    int i, nr_de_legaturi, caz[5];

    for(auto it:Noduri)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            gasit = 1, nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 4) break;
                }

            while(ismouseclick(WM_LBUTTONUP) == 0)
            {
                sterge_ultimul(g);

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

                for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);

                setare(g, p1, g.text, g.show_text);
                if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1)
                {
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                }

                else
                {
                    string text = "Nodul nu poate iesi din chenar!";
                    afiseaza_eroare(text);
                    setare(g, p2, g.text, g.show_text);
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                    break;
                }

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
            }

            sterge_ultimul(g);
            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);
            if(verif_se_suprapune(g.margine1, g.margine2) == 1)
            {
                setare(g, p2, g.text, g.show_text);
                string text = "Nodul se suprapune!";
                afiseaza_eroare(text);
            }
            deseneaza(g);
            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            clearmouseclick(WM_LBUTTONUP);
            break;
        }
    }
};

public:void Zoom(Punct p1, bool operatie, bool &gasit)
{
    Nod g;
    Legatura Leg[5];
    int i, nr_de_legaturi, caz[5];

    for(auto it:Noduri)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 4) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            if(operatie == 0) zoom_in(g);
            else if(operatie == 1) zoom_out(g);


            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Nodul iese din chenar!");
                else afiseaza_eroare("Nodul se suprapune cu o alta piesa!");

                if(operatie == 0) zoom_out(g);
                if(operatie == 1) zoom_in(g);
                deseneaza(g);
            }


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            gasit = 1;
            break;
        }
    }
}

public:void Rotire(Punct p1, bool &gasit)
{
    Nod g;
    Legatura Leg[5];
    int i, nr_de_legaturi, caz[5];

    for(auto it:Noduri)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 4) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            rotire(g);
            deseneaza(g);


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            break;
        }
    }
}

public:void Traseaza_linii(Punct &p, bool &gasit)
{
    Nod n;
    int i, v[5], vv[5];

    for(auto it:Noduri)
    {
        n = it;
        if(verif_punct_apartine(p, n) == 1 && (n.if_conect[1] == 0 || n.if_conect[2] == 0 || n.if_conect[3] == 0 || n.if_conect[4] == 0))
        {
            Noduri.erase(Noduri.find(it));

            for(i = 1; i <= 4; i++)
            {
                if(n.if_conect[i] == 0) vv[i] = 0;
                else vv[i] = 1;
            }

            for(i = 1; i <= 4; i++) v[i] = distanta_dintre_2_puncte(p, n.conect[i]) + vv[i] * (LATIME_WINDOW + LUNGIME_WINDOW);
            sort(v + 1, v + 5);
            for(i = 1; i <= 4; i++) if(v[1] == distanta_dintre_2_puncte(p, n.conect[i])) p = n.conect[i], n.if_conect[i] = 1, i = 5;

            Noduri.insert(n);
            gasit = 1;
            break;
        }
    }
}

public:void Modificare_text(Punct p, bool &gasit)
{
    Nod g;

    for(auto it:Noduri)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1)
        {
            Noduri.erase(Noduri.find(it));
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            g.text = scrie_text(p, g.text);

            Noduri.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Mod_sterge(Punct p, bool &gasit)
{
    int i;

    for(auto it:Noduri)
    {
        if(verif_punct_apartine(p, it) == 1)
        {
            for(i = 1; i <= 4; i++)
            {
                for(auto itt:Legaturi)
                {
                    if(verif_legatura_atinge(itt, it) == 1)
                    {
                        sterge_ultima_legatura(itt);
                        break;
                    }
                }
            }

            sterge_ultimul(it);
            gasit = 1;
            break;
        }
    }
}

};

class GENERATOR
{
    BUTON buton;

public:void setare(Generator &g, Punct centru, string text, bool show_text)
{
    Punct p1, p2;
    int i, lg_linie_minus = 23 + g.dimensiune * 3, lg_linie_plus = 37 + g.dimensiune * 3, lg_linie_spre = 19 + g.dimensiune * 3, lg_linie_plus_a = 7 + g.dimensiune * 2, lg_linie_plus_b = 7 + g.dimensiune * 2, lg_linie_minus_a = 7 + g.dimensiune * 2, dist_de_la_centru = 5 + g.dimensiune, culoare = 15;

    g.centru = centru;
    g.lg_linie_minus = lg_linie_minus, g.lg_linie_plus = lg_linie_plus, g.lg_linie_spre = lg_linie_spre, g.dist_de_la_centru = dist_de_la_centru, g.culoare = culoare;
    g.lg_linie_plus_a = lg_linie_plus_a, g.lg_linie_plus_b = lg_linie_plus_b, g.lg_linie_minus_a = lg_linie_minus_a;
    g.text = text, g.show_text = show_text;

    p1.x = p2.x = g.centru.x - g.dist_de_la_centru;
    p1.y = g.centru.y - g.lg_linie_plus / 2, p2.y = g.centru.y + g.lg_linie_plus / 2;
    g.linie_plus = setare_linie(p1, p2, g.culoare);

    p1.x = p2.x = g.centru.x + g.dist_de_la_centru;
    p1.y = g.centru.y - g.lg_linie_minus / 2, p2.y = g.centru.y + g.lg_linie_minus / 2;
    g.linie_minus = setare_linie(p1, p2, g.culoare);

    p1.x = g.centru.x - g.dist_de_la_centru - g.lg_linie_spre, p2.x = g.centru.x - g.dist_de_la_centru;
    p1.y = p2.y = g.centru.y;
    g.linie_spre_plus = setare_linie(p1, p2, g.culoare);

    p1.x = g.centru.x + g.dist_de_la_centru, p2.x = g.centru.x + g.dist_de_la_centru + g.lg_linie_spre;
    p1.y = p2.y = g.centru.y;
    g.linie_spre_minus = setare_linie(p1, p2, g.culoare);

    p1.x = g.centru.x - g.lg_linie_plus / 2 - g.lg_linie_plus_a / 2, p2.x = g.centru.x - g.lg_linie_plus / 2 + g.lg_linie_plus_a / 2;
    p1.y = p2.y = g.centru.y - g.lg_linie_plus / 3;
    g.linie_plus_a = setare_linie(p1, p2, g.culoare);

    p1.x = p2.x = g.centru.x - g.lg_linie_plus / 2;
    p1.y = g.centru.y - g.lg_linie_plus / 3 - g.lg_linie_plus_b / 2, p2.y = g.centru.y - g.lg_linie_plus / 3 + g.lg_linie_plus_b / 2;
    g.linie_plus_b = setare_linie(p1, p2, g.culoare);

    p1.x = g.centru.x + g.lg_linie_plus / 2 - g.lg_linie_plus_a / 2, p2.x = g.centru.x + g.lg_linie_plus / 2 + g.lg_linie_plus_a / 2;
    p1.y = p2.y = g.centru.y - g.lg_linie_plus / 3;
    g.linie_minus_a = setare_linie(p1, p2, g.culoare);


    g.margine1.x = g.linie_spre_plus.p1.x, g.margine1.y = g.linie_plus.p1.y, g.margine2.x = g.linie_spre_minus.p2.x, g.margine2.y = g.linie_plus.p2.y;


    regleaza_linie_dreapta(g.linie_minus), regleaza_linie_dreapta(g.linie_plus), regleaza_linie_dreapta(g.linie_spre_minus), regleaza_linie_dreapta(g.linie_spre_plus), regleaza_linie_dreapta(g.linie_plus_a), regleaza_linie_dreapta(g.linie_plus_b), regleaza_linie_dreapta(g.linie_minus_a);
    g.conect[1] = g.linie_spre_plus.p1, g.conect[2] = g.linie_spre_minus.p2;
    for(i = 1; i <= g.orientare; i++)
    {
        rotire_linie(g.centru, g.linie_minus), rotire_linie(g.centru, g.linie_plus), rotire_linie(g.centru, g.linie_spre_minus), rotire_linie(g.centru, g.linie_spre_plus), rotire_linie(g.centru, g.linie_plus_a), rotire_linie(g.centru, g.linie_plus_b), rotire_linie(g.centru, g.linie_minus_a);
        rotire_punct(g.centru, g.margine1), rotire_punct(g.centru, g.margine2);
        rotire_punct(g.centru, g.conect[1]), rotire_punct(g.centru, g.conect[2]);

        regleaza_linie_dreapta(g.linie_minus), regleaza_linie_dreapta(g.linie_plus), regleaza_linie_dreapta(g.linie_spre_minus), regleaza_linie_dreapta(g.linie_spre_plus), regleaza_linie_dreapta(g.linie_plus_a), regleaza_linie_dreapta(g.linie_plus_b), regleaza_linie_dreapta(g.linie_minus_a);
    }
}

public:void deseneaza(Generator g)
{
    if(g.culoare != 0)
    {
        deseneaza_linie_dreapta(g.linie_plus);
        deseneaza_linie_dreapta(g.linie_minus);
        deseneaza_linie_dreapta(g.linie_spre_plus);
        deseneaza_linie_dreapta(g.linie_spre_minus);
        deseneaza_linie_dreapta(g.linie_plus_a);
        deseneaza_linie_dreapta(g.linie_plus_b);
        deseneaza_linie_dreapta(g.linie_minus_a);
        Generatoare.insert(g);

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            deseneaza_text(g.text, p);
        }
    }
}

public:void sterge_ultimul(Generator g)
{
    if(Generatoare.find(g) != Generatoare.end())
    {
        sterge_ultima_linie_dreapta(g.linie_spre_minus);
        sterge_ultima_linie_dreapta(g.linie_spre_plus);
        sterge_ultima_linie_dreapta(g.linie_minus);
        sterge_ultima_linie_dreapta(g.linie_plus);
        sterge_ultima_linie_dreapta(g.linie_plus_a);
        sterge_ultima_linie_dreapta(g.linie_plus_b);
        sterge_ultima_linie_dreapta(g.linie_minus_a);
        Generatoare.erase(Generatoare.find(g));

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            sterge_text(g.text, p);
        }
    }
}

public:void zoom_in(Generator &n)
{
    if(n.dimensiune == DIMENSIUNE_MAX) afiseaza_eroare("Generatorul are dimensiunea maxima!");
    else
    {
        n.dimensiune++;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void zoom_out(Generator &n)
{
    if(n.dimensiune == DIMENSIUNE_MIN) afiseaza_eroare("Generatorul are dimensiunea minima!");
    else
    {
        n.dimensiune--;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void rotire(Generator &g)
{
    g.orientare = (g.orientare + 1) % 4;
    setare(g, g.centru, g.text, g.show_text);
}

public:bool verif_punct_apartine(Punct p, Generator g)
{
    return p.x >= min(g.margine1.x, g.margine2.x) && p.x <= max(g.margine1.x, g.margine2.x) && p.y >= min(g.margine1.y, g.margine2.y) && p.y <= max(g.margine1.y, g.margine2.y);
}

public:bool verif_legatura_atinge(Legatura Leg, Generator g)
{
    return (verif_punct_apartine(Leg.p1, g) || verif_punct_apartine(Leg.p2, g));
}

public:void setare_legaturi(Generator g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    if(Leg[nr_de_legaturi].p1.x == g.conect[1].x && Leg[nr_de_legaturi].p1.y == g.conect[1].y) caz[nr_de_legaturi] = 1;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[2].x && Leg[nr_de_legaturi].p1.y == g.conect[2].y) caz[nr_de_legaturi] = 2;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[1].x && Leg[nr_de_legaturi].p2.y == g.conect[1].y) caz[nr_de_legaturi] = 3;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[2].x && Leg[nr_de_legaturi].p2.y == g.conect[2].y) caz[nr_de_legaturi] = 4;
}

public:void deseneaza_legaturi(Generator g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    int i;

    for(i = 1; i <= nr_de_legaturi; i++)
    {
        if(caz[i] == 1) Leg[i].p1 = g.conect[1];
        else if(caz[i] == 2) Leg[i].p1 = g.conect[2];
        else if(caz[i] == 3) Leg[i].p2 = g.conect[1];
        else if(caz[i] == 4) Leg[i].p2 = g.conect[2];

        seteaza_linii_legatura(Leg[i]);
        deseneaza_legatura(Leg[i]);
    }
}


public:void Mod_punere(Buton &Punere_generator)
{
    Generator g;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0)
    {
        sterge_ultimul(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
        getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

        setare(g, p1, "", 0);
        if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
    }

    buton.actioneaza_buton(Punere_generator);
};

public:void Mutare(Punct p1, bool &gasit)
{
    Generator g;
    Legatura Leg[3];
    Punct p2 = p1;
    int i, nr_de_legaturi, caz[3];

    for(auto it:Generatoare)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            gasit = 1, nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            while(ismouseclick(WM_LBUTTONUP) == 0)
            {
                sterge_ultimul(g);

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

                for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);

                setare(g, p1, g.text, g.show_text);
                if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1)
                {
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                }

                else
                {
                    setare(g, p2, g.text, g.show_text);
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                    string text = "Generatorul nu poate iesi din chenar!";
                    afiseaza_eroare(text);
                    break;
                }

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
            }

            sterge_ultimul(g);
            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);
            if(verif_se_suprapune(g.margine1, g.margine2) == 1)
            {
                setare(g, p2, g.text, g.show_text);
                string text = "Generatorul se suprapune!";
                afiseaza_eroare(text);
            }
            deseneaza(g);
            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            clearmouseclick(WM_LBUTTONUP);
            break;
        }
    }
};

public:void Zoom(Punct p1, bool operatie, bool &gasit)
{
    Generator g;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Generatoare)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            if(operatie == 0) zoom_in(g);
            else if(operatie == 1) zoom_out(g);


            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Generatorul iese din chenar!");
                else afiseaza_eroare("Generatorul se suprapune cu o alta piesa!");

                if(operatie == 0) zoom_out(g);
                if(operatie == 1) zoom_in(g);
                deseneaza(g);
            }


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            gasit = 1;
            break;
        }
    }
}

public:void Rotire(Punct p1, bool &gasit)
{
    Generator g, gg;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Generatoare)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            gg = g;
            sterge_ultimul(g);
            rotire(g);

            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0)
            {
                deseneaza(g);
                deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
            }
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Generatorul iese din chenar!");
                else afiseaza_eroare("Generatorul se suprapune cu o alta piesa!");
                deseneaza(gg);
                deseneaza_legaturi(gg, nr_de_legaturi, Leg, caz);
            }

            break;
        }
    }
}

public:void Traseaza_linii(Punct &p, bool &gasit)
{
    Generator g;

    for(auto it:Generatoare)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1 && (g.if_conect[1] == 0 || g.if_conect[2] == 0))
        {
            Generatoare.erase(Generatoare.find(it));

            if(g.if_conect[1] == 0 && g.if_conect[2] == 1) p = g.conect[1], g.if_conect[1] = 1;
            else if(g.if_conect[1] == 1 && g.if_conect[2] == 0) p = g.conect[2], g.if_conect[2] = 1;
            else if(distanta_dintre_2_puncte(p, g.conect[1]) < distanta_dintre_2_puncte(p, g.conect[2])) p = g.conect[1], g.if_conect[1] = 1;
            else p = g.conect[2], g.if_conect[2] = 1;

            Generatoare.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Modificare_text(Punct p, bool &gasit)
{
    Generator g;

    for(auto it:Generatoare)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1)
        {
            Generatoare.erase(Generatoare.find(it));
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            g.text = scrie_text(p, g.text);

            Generatoare.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Mod_sterge(Punct p, bool &gasit)
{
    int i;

    for(auto it:Generatoare)
    {
        if(verif_punct_apartine(p, it) == 1)
        {
            for(i = 1; i <= 2; i++)
            {
                for(auto itt:Legaturi)
                {
                    if(verif_legatura_atinge(itt, it) == 1)
                    {
                        sterge_ultima_legatura(itt);
                        break;
                    }
                }
            }

            sterge_ultimul(it);
            gasit = 1;
            break;
        }
    }
}

};

class REZISTOR
{
    BUTON buton;

public:void setare(Rezistor &r, Punct centru, string text, bool show_text)
{
    Punct p1, p2;
    int i, lg_linie_orizontala_sus = 30 + r.dimensiune * 3, lg_linie_orizontala_jos = 30 + r.dimensiune * 3, lg_linie_verticala_st = 7 + r.dimensiune, lg_linie_verticala_dr = 7 + r.dimensiune;
    int lg_linie_spre_st = 10 + r.dimensiune, lg_linie_spre_dr = 10 + r.dimensiune, dist_de_la_centru_spre_x = 15 + r.dimensiune * 2, dist_de_la_centru_spre_y = 7 + r.dimensiune;
    int culoare = 15;

    r.centru = centru;
    r.lg_linie_orizontala_sus = lg_linie_orizontala_sus, r.lg_linie_orizontala_jos = lg_linie_orizontala_jos, r.lg_linie_verticala_st = lg_linie_verticala_st, r.lg_linie_verticala_dr = lg_linie_verticala_dr;
    r.lg_linie_spre_st = lg_linie_spre_st, r.lg_linie_spre_dr = lg_linie_spre_dr, r.dist_de_la_centru_spre_x = dist_de_la_centru_spre_x, r.dist_de_la_centru_spre_y = dist_de_la_centru_spre_y, r.culoare = culoare;

    p1.x = r.centru.x - r.dist_de_la_centru_spre_x, p2.x = r.centru.x + r.dist_de_la_centru_spre_x;
    p1.y = p2.y = r.centru.y - r.dist_de_la_centru_spre_y;
    r.linie_orizontala_sus = setare_linie(p1, p2, r.culoare);

    p1.x = r.centru.x - r.dist_de_la_centru_spre_x, p2.x = r.centru.x + r.dist_de_la_centru_spre_x;
    p1.y = p2.y = r.centru.y + r.dist_de_la_centru_spre_y;
    r.linie_orizontala_jos = setare_linie(p1, p2, r.culoare);

    p1.x = p2.x = r.centru.x - r.dist_de_la_centru_spre_x;
    p1.y = r.centru.y - r.dist_de_la_centru_spre_y, p2.y = r.centru.y + r.dist_de_la_centru_spre_y;
    r.linie_verticala_st = setare_linie(p1, p2, r.culoare);

    p1.x = p2.x = r.centru.x + r.dist_de_la_centru_spre_x;
    p1.y = r.centru.y - r.dist_de_la_centru_spre_y, p2.y = r.centru.y + r.dist_de_la_centru_spre_y;
    r.linie_verticala_dr = setare_linie(p1, p2, r.culoare);

    p1.x = r.centru.x - r.dist_de_la_centru_spre_x - 10, p2.x = r.centru.x - r.dist_de_la_centru_spre_x;
    p1.y = p2.y = r.centru.y;
    r.linie_spre_st = setare_linie(p1, p2, r.culoare);

    p1.x = r.centru.x + r.dist_de_la_centru_spre_x, p2.x = r.centru.x + r.dist_de_la_centru_spre_x + 10;
    p1.y = p2.y = r.centru.y;
    r.linie_spre_dr = setare_linie(p1, p2, r.culoare);

    r.margine1.x = r.linie_spre_st.p1.x, r.margine1.y = r.linie_orizontala_sus.p1.y, r.margine2.x = r.linie_spre_dr.p2.x, r.margine2.y = r.linie_orizontala_jos.p2.y;


    regleaza_linie_dreapta(r.linie_orizontala_sus), regleaza_linie_dreapta(r.linie_orizontala_jos), regleaza_linie_dreapta(r.linie_verticala_st);
    regleaza_linie_dreapta(r.linie_verticala_dr), regleaza_linie_dreapta(r.linie_spre_st), regleaza_linie_dreapta(r.linie_spre_dr);
    r.conect[1] = r.linie_spre_st.p1, r.conect[2] = r.linie_spre_dr.p2;
    for(i = 1; i <= r.orientare; i++)
    {
        rotire_linie(r.centru, r.linie_orizontala_sus), rotire_linie(r.centru, r.linie_orizontala_jos), rotire_linie(r.centru, r.linie_verticala_st);
        rotire_linie(r.centru, r.linie_verticala_dr), rotire_linie(r.centru, r.linie_spre_st), rotire_linie(r.centru, r.linie_spre_dr);
        rotire_punct(r.centru, r.margine1), rotire_punct(r.centru, r.margine2);
        rotire_punct(r.centru, r.conect[1]), rotire_punct(r.centru, r.conect[2]);

        regleaza_linie_dreapta(r.linie_orizontala_sus), regleaza_linie_dreapta(r.linie_orizontala_jos), regleaza_linie_dreapta(r.linie_verticala_st);
        regleaza_linie_dreapta(r.linie_verticala_dr), regleaza_linie_dreapta(r.linie_spre_st), regleaza_linie_dreapta(r.linie_spre_dr);
    }
}

public:void deseneaza(Rezistor r)
{
    if(r.culoare != 0)
    {
        deseneaza_linie_dreapta(r.linie_orizontala_sus);
        deseneaza_linie_dreapta(r.linie_orizontala_jos);
        deseneaza_linie_dreapta(r.linie_spre_dr);
        deseneaza_linie_dreapta(r.linie_spre_st);
        deseneaza_linie_dreapta(r.linie_verticala_st);
        deseneaza_linie_dreapta(r.linie_verticala_dr);
        Rezistoare.insert(r);

        Punct p;
        if(r.show_text == 1)
        {
            if(r.orientare == 0 || r.orientare == 2) p.x = r.centru.x, p.y = max(r.margine1.y, r.margine2.y) + 10;
            else p.x = max(r.margine1.x, r.margine2.x) + 17, p.y = r.centru.y;

            deseneaza_text(r.text, p);
        }
    }
}

public:void sterge_ultimul(Rezistor r)
{
    if(Rezistoare.find(r) != Rezistoare.end())
    {
        sterge_ultima_linie_dreapta(r.linie_orizontala_sus);
        sterge_ultima_linie_dreapta(r.linie_orizontala_jos);
        sterge_ultima_linie_dreapta(r.linie_spre_dr);
        sterge_ultima_linie_dreapta(r.linie_spre_st);
        sterge_ultima_linie_dreapta(r.linie_verticala_st);
        sterge_ultima_linie_dreapta(r.linie_verticala_dr);
        Rezistoare.erase(Rezistoare.find(r));

        Punct p;
        if(r.show_text == 1)
        {
            if(r.orientare == 0 || r.orientare == 2) p.x = r.centru.x, p.y = max(r.margine1.y, r.margine2.y) + 10;
            else p.x = max(r.margine1.x, r.margine2.x) + 17, p.y = r.centru.y;

            sterge_text(r.text, p);
        }
    }
}

public:void zoom_in(Rezistor &n)
{
    if(n.dimensiune == DIMENSIUNE_MAX) afiseaza_eroare("Rezistorul are dimensiunea maxima!");
    else
    {
        n.dimensiune++;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void zoom_out(Rezistor &n)
{
    if(n.dimensiune == DIMENSIUNE_MIN) afiseaza_eroare("Rezistorul are dimensiunea minima!");
    else
    {
        n.dimensiune--;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void rotire(Rezistor &r)
{
    r.orientare = (r.orientare + 1) % 4;
    setare(r, r.centru, r.text, r.show_text);
}

public:bool verif_punct_apartine(Punct p, Rezistor r)
{
    return p.x >= min(r.margine1.x, r.margine2.x) && p.x <= max(r.margine1.x, r.margine2.x) && p.y >= min(r.margine1.y, r.margine2.y) && p.y <= max(r.margine1.y, r.margine2.y);
}

public:bool verif_legatura_atinge(Legatura Leg, Rezistor r)
{
    return (verif_punct_apartine(Leg.p1, r) || verif_punct_apartine(Leg.p2, r));
}

public:void setare_legaturi(Rezistor r, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    if(Leg[nr_de_legaturi].p1.x == r.conect[1].x && Leg[nr_de_legaturi].p1.y == r.conect[1].y) caz[nr_de_legaturi] = 1;
    else if(Leg[nr_de_legaturi].p1.x == r.conect[2].x && Leg[nr_de_legaturi].p1.y == r.conect[2].y) caz[nr_de_legaturi] = 2;
    else if(Leg[nr_de_legaturi].p2.x == r.conect[1].x && Leg[nr_de_legaturi].p2.y == r.conect[1].y) caz[nr_de_legaturi] = 3;
    else if(Leg[nr_de_legaturi].p2.x == r.conect[2].x && Leg[nr_de_legaturi].p2.y == r.conect[2].y) caz[nr_de_legaturi] = 4;
}

public:void deseneaza_legaturi(Rezistor r, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    int i;

    for(i = 1; i <= nr_de_legaturi; i++)
    {
        if(caz[i] == 1) Leg[i].p1 = r.conect[1];
        else if(caz[i] == 2) Leg[i].p1 = r.conect[2];
        else if(caz[i] == 3) Leg[i].p2 = r.conect[1];
        else if(caz[i] == 4) Leg[i].p2 = r.conect[2];

        seteaza_linii_legatura(Leg[i]);
        deseneaza_legatura(Leg[i]);
    }
}


public:void Mod_punere(Buton &Punere_generator)
{
    Rezistor g;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0)
    {
        sterge_ultimul(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
        getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

        setare(g, p1, "", 0);
        if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
    }

    buton.actioneaza_buton(Punere_generator);
};

public:void Mutare(Punct p1, bool &gasit)
{
    Rezistor g;
    Legatura Leg[3];
    Punct p2 = p1;
    int i, nr_de_legaturi, caz[3];

    for(auto it:Rezistoare)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            gasit = 1, nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            while(ismouseclick(WM_LBUTTONUP) == 0)
            {
                sterge_ultimul(g);

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

                for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);

                setare(g, p1, g.text, g.show_text);
                if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1)
                {
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                }

                else
                {
                    setare(g, p2, g.text, g.show_text);
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                    string text = "Rezistorul nu poate fi scos din chenar!";
                    afiseaza_eroare(text);
                    break;
                }

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
            }

            sterge_ultimul(g);
            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);
            if(verif_se_suprapune(g.margine1, g.margine2) == 1)
            {
                setare(g, p2, g.text, g.show_text);
                string text = "Rezistorul se suprapune!";
                afiseaza_eroare(text);
            }
            deseneaza(g);
            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            clearmouseclick(WM_LBUTTONUP);
            break;
        }
    }
};

public:void Zoom(Punct p1, bool operatie, bool &gasit)
{
    Rezistor g;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Rezistoare)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            if(operatie == 0) zoom_in(g);
            else if(operatie == 1) zoom_out(g);


            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Rezistorul iese din chenar!");
                else afiseaza_eroare("Rezistorul se suprapune cu o alta piesa!");

                if(operatie == 0) zoom_out(g);
                if(operatie == 1) zoom_in(g);
                deseneaza(g);
            }


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            gasit = 1;
            break;
        }
    }
}

public:void Rotire(Punct p1, bool &gasit)
{
    Rezistor g, gg;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Rezistoare)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            gg = g;
            sterge_ultimul(g);
            rotire(g);

            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0)
            {
                deseneaza(g);
                deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
            }
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Rezistorul iese din chenar!");
                else afiseaza_eroare("Rezistorul se suprapune cu o alta piesa!");
                deseneaza(gg);
                deseneaza_legaturi(gg, nr_de_legaturi, Leg, caz);
            }


            break;
        }
    }
}

public:void Traseaza_linii(Punct &p, bool &gasit)
{
    Rezistor g;

    for(auto it:Rezistoare)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1 && (g.if_conect[1] == 0 || g.if_conect[2] == 0))
        {
            Rezistoare.erase(Rezistoare.find(it));

            if(g.if_conect[1] == 0 && g.if_conect[2] == 1) p = g.conect[1], g.if_conect[1] = 1;
            else if(g.if_conect[1] == 1 && g.if_conect[2] == 0) p = g.conect[2], g.if_conect[2] = 1;
            else if(distanta_dintre_2_puncte(p, g.conect[1]) < distanta_dintre_2_puncte(p, g.conect[2])) p = g.conect[1], g.if_conect[1] = 1;
            else p = g.conect[2], g.if_conect[2] = 1;

            Rezistoare.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Modificare_text(Punct p, bool &gasit)
{
    Rezistor g;

    for(auto it:Rezistoare)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1)
        {
            Rezistoare.erase(Rezistoare.find(it));
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            g.text = scrie_text(p, g.text);

            Rezistoare.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Mod_sterge(Punct p, bool &gasit)
{
    int i;

    for(auto it:Rezistoare)
    {
        if(verif_punct_apartine(p, it) == 1)
        {
            for(i = 1; i <= 2; i++)
            {
                for(auto itt:Legaturi)
                {
                    if(verif_legatura_atinge(itt, it) == 1)
                    {
                        sterge_ultima_legatura(itt);
                        break;
                    }
                }
            }

            sterge_ultimul(it);
            gasit = 1;
            break;
        }
    }
}

};

class CONDENSATOR
{
    BUTON buton;

public:void setare(Condensator &c, Punct centru, string text, bool show_text)
{
    Punct p1, p2;
    int i, lg_linie_orizontala_st = 20 + c.dimensiune * 4, lg_linie_orizontala_dr = 20 + c.dimensiune * 4, lg_linie_verticala_st = 25 + c.dimensiune * 5, lg_linie_verticala_dr = 25 + c.dimensiune * 5;
    int dist_de_la_centru = 5 + c.dimensiune, culoare = 15;

    c.centru = centru;
    c.lg_linie_orizontala_st = lg_linie_orizontala_st, c.lg_linie_orizontala_dr = lg_linie_orizontala_dr, c.lg_linie_verticala_st = lg_linie_verticala_st, c.lg_linie_verticala_dr = lg_linie_verticala_dr;
    c.dist_de_la_centru = dist_de_la_centru, c.culoare = culoare;

    p1.x = c.centru.x - dist_de_la_centru - c.lg_linie_orizontala_st, p2.x = c.centru.x - dist_de_la_centru;
    p1.y = p2.y = c.centru.y;
    c.linie_orizontala_st = setare_linie(p1, p2, c.culoare);

    p1.x = c.centru.x + dist_de_la_centru, p2.x = c.centru.x + dist_de_la_centru + c.lg_linie_orizontala_dr;
    p1.y = p2.y = c.centru.y;
    c.linie_orizontala_dr = setare_linie(p1, p2, c.culoare);

    p1.x = p2.x = c.centru.x - dist_de_la_centru;
    p1.y = c.centru.y - c.lg_linie_verticala_st / 2, p2.y = c.centru.y + c.lg_linie_verticala_st / 2;
    c.linie_verticala_st = setare_linie(p1, p2, c.culoare);

    p1.x = p2.x = c.centru.x + dist_de_la_centru;
    p1.y = c.centru.y - c.lg_linie_verticala_dr / 2, p2.y = c.centru.y + c.lg_linie_verticala_dr / 2;
    c.linie_verticala_dr = setare_linie(p1, p2, c.culoare);

    c.margine1.x = c.linie_orizontala_st.p1.x, c.margine1.y = c.linie_verticala_st.p1.y, c.margine2.x = c.linie_orizontala_dr.p2.x, c.margine2.y = c.linie_verticala_st.p2.y;


    regleaza_linie_dreapta(c.linie_orizontala_st), regleaza_linie_dreapta(c.linie_orizontala_dr), regleaza_linie_dreapta(c.linie_verticala_st), regleaza_linie_dreapta(c.linie_verticala_dr);
    c.conect[1] = c.linie_orizontala_st.p1, c.conect[2] = c.linie_orizontala_dr.p2;
    for(i = 1; i <= c.orientare; i++)
    {
        rotire_linie(c.centru, c.linie_orizontala_st), rotire_linie(c.centru, c.linie_orizontala_dr), rotire_linie(c.centru, c.linie_verticala_st), rotire_linie(c.centru, c.linie_verticala_dr);
        rotire_punct(c.centru, c.margine1), rotire_punct(c.centru, c.margine2);
        rotire_punct(c.centru, c.conect[1]), rotire_punct(c.centru, c.conect[2]);

        regleaza_linie_dreapta(c.linie_orizontala_st), regleaza_linie_dreapta(c.linie_orizontala_dr), regleaza_linie_dreapta(c.linie_verticala_st), regleaza_linie_dreapta(c.linie_verticala_dr);
    }
}

public:void deseneaza(Condensator g)
{
    if (g.culoare != 0)
    {
        deseneaza_linie_dreapta(g.linie_orizontala_st);
        deseneaza_linie_dreapta(g.linie_orizontala_dr);
        deseneaza_linie_dreapta(g.linie_verticala_st);
        deseneaza_linie_dreapta(g.linie_verticala_dr);
        Condensatoare.insert(g);

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            deseneaza_text(g.text, p);
        }
    }
}

public:void sterge_ultimul(Condensator g)
{
    if(Condensatoare.find(g) != Condensatoare.end())
    {
        sterge_ultima_linie_dreapta(g.linie_orizontala_st);
        sterge_ultima_linie_dreapta(g.linie_orizontala_dr);
        sterge_ultima_linie_dreapta(g.linie_verticala_st);
        sterge_ultima_linie_dreapta(g.linie_verticala_dr);
        Condensatoare.erase(Condensatoare.find(g));

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            sterge_text(g.text, p);
        }
    }
}

public:void zoom_in(Condensator &n)
{
    if(n.dimensiune == DIMENSIUNE_MAX) afiseaza_eroare("Condensatorul are dimensiunea maxima!");
    else
    {
        n.dimensiune++;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void zoom_out(Condensator &n)
{
    if(n.dimensiune == DIMENSIUNE_MIN) afiseaza_eroare("Condensatorul are dimensiunea minima!");
    else
    {
        n.dimensiune--;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void rotire(Condensator &g)
{
    g.orientare = (g.orientare + 1) % 4;
    setare(g, g.centru, g.text, g.show_text);
}

public:bool verif_punct_apartine(Punct p, Condensator g)
{
    return p.x >= min(g.margine1.x, g.margine2.x) && p.x <= max(g.margine1.x, g.margine2.x) && p.y >= min(g.margine1.y, g.margine2.y) && p.y <= max(g.margine1.y, g.margine2.y);
}

public:bool verif_legatura_atinge(Legatura Leg, Condensator g)
{
    return (verif_punct_apartine(Leg.p1, g) || verif_punct_apartine(Leg.p2, g));
}

public:void setare_legaturi(Condensator g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    if(Leg[nr_de_legaturi].p1.x == g.conect[1].x && Leg[nr_de_legaturi].p1.y == g.conect[1].y) caz[nr_de_legaturi] = 1;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[2].x && Leg[nr_de_legaturi].p1.y == g.conect[2].y) caz[nr_de_legaturi] = 2;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[1].x && Leg[nr_de_legaturi].p2.y == g.conect[1].y) caz[nr_de_legaturi] = 3;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[2].x && Leg[nr_de_legaturi].p2.y == g.conect[2].y) caz[nr_de_legaturi] = 4;
}

public:void deseneaza_legaturi(Condensator g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    int i;

    for(i = 1; i <= nr_de_legaturi; i++)
    {
        if(caz[i] == 1) Leg[i].p1 = g.conect[1];
        else if(caz[i] == 2) Leg[i].p1 = g.conect[2];
        else if(caz[i] == 3) Leg[i].p2 = g.conect[1];
        else if(caz[i] == 4) Leg[i].p2 = g.conect[2];

        seteaza_linii_legatura(Leg[i]);
        deseneaza_legatura(Leg[i]);
    }
}


public:void Mod_punere(Buton &Punere_generator)
{
    Condensator g;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0)
    {
        sterge_ultimul(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
        getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

        setare(g, p1, "", 0);
        if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
    }

    buton.actioneaza_buton(Punere_generator);
};

public:void Mutare(Punct p1, bool &gasit)
{
    Condensator g;
    Legatura Leg[3];
    Punct p2 = p1;
    int i, nr_de_legaturi, caz[3];

    for(auto it:Condensatoare)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            gasit = 1, nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            while(ismouseclick(WM_LBUTTONUP) == 0)
            {
                sterge_ultimul(g);

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

                for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);

                setare(g, p1, g.text, g.show_text);
                if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1)
                {
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                }

                else
                {
                    setare(g, p2, g.text, g.show_text);
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                    string text = "Condensatorul nu poate fi scos din chenar!";
                    afiseaza_eroare(text);
                    break;
                }

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
            }

            sterge_ultimul(g);
            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);
            if(verif_se_suprapune(g.margine1, g.margine2) == 1)
            {
                setare(g, p2, g.text, g.show_text);
                string text = "Condensatorul se suprapune!";
                afiseaza_eroare(text);
            }
            deseneaza(g);
            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            clearmouseclick(WM_LBUTTONUP);
            break;
        }
    }
};

public:void Zoom(Punct p1, bool operatie, bool &gasit)
{
    Condensator g;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Condensatoare)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            if(operatie == 0) zoom_in(g);
            else if(operatie == 1) zoom_out(g);


            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Condensatorul iese din chenar!");
                else afiseaza_eroare("Condensatorul se suprapune cu o alta piesa!");

                if(operatie == 0) zoom_out(g);
                if(operatie == 1) zoom_in(g);
                deseneaza(g);
            }


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            gasit = 1;
            break;
        }
    }
}

public:void Rotire(Punct p1, bool &gasit)
{
    Condensator g, gg;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Condensatoare)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            gg = g;
            sterge_ultimul(g);
            rotire(g);

            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0)
            {
                deseneaza(g);
                deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
            }
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Condensatorul iese din chenar!");
                else afiseaza_eroare("Condensatorul se suprapune cu o alta piesa!");
                deseneaza(gg);
                deseneaza_legaturi(gg, nr_de_legaturi, Leg, caz);
            }

            break;
        }
    }
}

public:void Traseaza_linii(Punct &p, bool &gasit)
{
    Condensator g;

    for(auto it:Condensatoare)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1 && (g.if_conect[1] == 0 || g.if_conect[2] == 0))
        {
            Condensatoare.erase(Condensatoare.find(it));

            if(g.if_conect[1] == 0 && g.if_conect[2] == 1) p = g.conect[1], g.if_conect[1] = 1;
            else if(g.if_conect[1] == 1 && g.if_conect[2] == 0) p = g.conect[2], g.if_conect[2] = 1;
            else if(distanta_dintre_2_puncte(p, g.conect[1]) < distanta_dintre_2_puncte(p, g.conect[2])) p = g.conect[1], g.if_conect[1] = 1;
            else p = g.conect[2], g.if_conect[2] = 1;

            Condensatoare.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Modificare_text(Punct p, bool &gasit)
{
    Condensator g;

    for(auto it:Condensatoare)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1)
        {
            Condensatoare.erase(Condensatoare.find(it));
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            g.text = scrie_text(p, g.text);

            Condensatoare.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Mod_sterge(Punct p, bool &gasit)
{
    int i;

    for(auto it:Condensatoare)
    {
        if(verif_punct_apartine(p, it) == 1)
        {
            for(i = 1; i <= 2; i++)
            {
                for(auto itt:Legaturi)
                {
                    if(verif_legatura_atinge(itt, it) == 1)
                    {
                        sterge_ultima_legatura(itt);
                        break;
                    }
                }
            }

            sterge_ultimul(it);
            gasit = 1;
            break;
        }
    }
}

};

class AMPLIFICATOR_OPERATIONAL
{
    BUTON buton;

public:void setare(Amplificator_operational &a, Punct centru, string text, bool show_text)
{
    Punct p1, p2;
    int lg_linie_orizontala_dr = 15 + a.dimensiune * 5, lg_linie_st = 30 + a.dimensiune * 8, lg_linie_sus = 15 + a.dimensiune * 4, lg_linie_jos = 15 + a.dimensiune * 4;
    int lg_linie_a = 15 + a.dimensiune * 4, lg_linie_b = 15 + a.dimensiune * 4, lg_linie_plus_a = 5 + a.dimensiune * 3, lg_linie_plus_b = 5 + a.dimensiune * 3;
    int lg_linie_minus = 5 + a.dimensiune * 3, dist_de_la_centru = 15 + a.dimensiune * 4, culoare = 15;

    a.centru = centru;
    a.lg_linie_orizontala_dr = lg_linie_orizontala_dr, a.lg_linie_st = lg_linie_st, a.lg_linie_sus = lg_linie_sus, a.lg_linie_jos = lg_linie_jos, a.lg_linie_a = lg_linie_a;
    a.lg_linie_b = lg_linie_b, a.lg_linie_plus_a = lg_linie_plus_a, a.lg_linie_plus_b = lg_linie_plus_b, a.lg_linie_minus = lg_linie_minus, a.dist_de_la_centru = dist_de_la_centru;
    a.culoare = culoare;
    a.text = text, a.show_text = show_text;

    p1.x = a.centru.x + a.dist_de_la_centru, p2.x = a.centru.x + a.dist_de_la_centru + a.lg_linie_orizontala_dr;
    p1.y = p2.y = a.centru.y;
    a.linie_orizontala_dr = setare_linie(p1, p2, a.culoare);

    p1.x = p2.x = a.centru.x - a.dist_de_la_centru;
    p1.y = a.centru.y - a.lg_linie_st, p2.y = a.centru.y + a.lg_linie_st;
    a.linie_st = setare_linie(p1, p2, a.culoare);

    p1.x = a.centru.x - a.dist_de_la_centru, p2.x = a.centru.x + a.dist_de_la_centru;
    p1.y = a.centru.y - a.lg_linie_sus * 2, p2.y = a.centru.y;
    a.linie_sus = setare_linie(p1, p2, a.culoare);

    p1.x = a.centru.x - a.dist_de_la_centru, p2.x = a.centru.x + a.dist_de_la_centru;
    p1.y = a.centru.y + a.lg_linie_jos * 2, p2.y = a.centru.y;
    a.linie_jos = setare_linie(p1, p2, a.culoare);

    p1.x = a.centru.x - a.dist_de_la_centru - a.lg_linie_a,  p2.x = a.centru.x - a.dist_de_la_centru;
    p1.y = p2.y = a.centru.y - a.lg_linie_st / 2;
    a.linie_a = setare_linie(p1, p2, a.culoare);

    p1.x = a.centru.x - a.dist_de_la_centru - a.lg_linie_b,  p2.x = a.centru.x - a.dist_de_la_centru;
    p1.y = p2.y = a.centru.y + a.lg_linie_st / 2;
    a.linie_b = setare_linie(p1, p2, a.culoare);

    p1.x = a.centru.x - a.dist_de_la_centru + a.dist_de_la_centru / 2 - a.lg_linie_plus_a / 2, p2.x = a.centru.x - a.dist_de_la_centru + a.dist_de_la_centru / 2 + a.lg_linie_plus_a / 2;
    p1.y = p2.y = a.centru.y - a.lg_linie_st / 2;
    a.linie_plus_a = setare_linie(p1, p2, a.culoare);

    p1.x = p2.x = a.centru.x - a.dist_de_la_centru + a.dist_de_la_centru / 2;
    p1.y = a.centru.y - a.lg_linie_st / 2 - a.lg_linie_plus_b / 2, p2.y = a.centru.y - a.lg_linie_st / 2 + a.lg_linie_plus_b / 2;
    a.linie_plus_b = setare_linie(p1, p2, a.culoare);

    p1.x = a.centru.x - a.dist_de_la_centru + a.dist_de_la_centru / 2 - a.lg_linie_plus_a / 2, p2.x = a.centru.x - a.dist_de_la_centru + a.dist_de_la_centru / 2 + a.lg_linie_plus_a / 2;
    p1.y = p2.y = a.centru.y + a.lg_linie_st / 2;
    a.linie_minus = setare_linie(p1, p2, a.culoare);

    a.margine1.x = a.linie_a.p1.x, a.margine1.y = a.linie_st.p1.y, a.margine2.x = a.linie_orizontala_dr.p2.x, a.margine2.y = a.linie_st.p2.y;


    regleaza_linie_dreapta(a.linie_orizontala_dr), regleaza_linie_dreapta(a.linie_st), regleaza_linie_dreapta(a.linie_a), regleaza_linie_dreapta(a.linie_b);
    regleaza_linie_dreapta(a.linie_plus_a), regleaza_linie_dreapta(a.linie_plus_b), regleaza_linie_dreapta(a.linie_minus);
    a.conect[1] = a.linie_a.p1, a.conect[2] = a.linie_b.p1, a.conect[3] = a.linie_orizontala_dr.p2;


    int i;
    for(i = 1; i <= a.orientare; i++)
    {
        rotire_linie(a.centru, a.linie_orizontala_dr), rotire_linie(a.centru, a.linie_st), rotire_linie(a.centru, a.linie_a), rotire_linie(a.centru, a.linie_b);
        rotire_linie(a.centru, a.linie_plus_a), rotire_linie(a.centru, a.linie_plus_b), rotire_linie(a.centru, a.linie_minus);
        rotire_linie(a.centru, a.linie_sus), rotire_linie(a.centru, a.linie_jos);
        rotire_punct(a.centru, a.margine1), rotire_punct(a.centru, a.margine2);
        rotire_punct(a.centru, a.conect[1]), rotire_punct(a.centru, a.conect[2]), rotire_punct(a.centru, a.conect[3]);

        regleaza_linie_dreapta(a.linie_orizontala_dr), regleaza_linie_dreapta(a.linie_st), regleaza_linie_dreapta(a.linie_a), regleaza_linie_dreapta(a.linie_b);
        regleaza_linie_dreapta(a.linie_plus_a), regleaza_linie_dreapta(a.linie_plus_b), regleaza_linie_dreapta(a.linie_minus);
    }
}

public:void deseneaza(Amplificator_operational g)
{
    if(g.culoare != 0)
    {
        deseneaza_linie_dreapta(g.linie_orizontala_dr);
        deseneaza_linie_dreapta(g.linie_st);
        deseneaza_linie_diagonala(g.linie_sus);
        deseneaza_linie_diagonala(g.linie_jos);
        deseneaza_linie_dreapta(g.linie_a);
        deseneaza_linie_dreapta(g.linie_b);
        deseneaza_linie_dreapta(g.linie_plus_a);
        deseneaza_linie_dreapta(g.linie_plus_b);
        deseneaza_linie_dreapta(g.linie_minus);
        Amplificatoare_operationale.insert(g);

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            deseneaza_text(g.text, p);
        }
    }
}

public:void sterge_ultimul(Amplificator_operational g)
{
    if(Amplificatoare_operationale.find(g) != Amplificatoare_operationale.end())
    {
        sterge_ultima_linie_dreapta(g.linie_orizontala_dr);
        sterge_ultima_linie_dreapta(g.linie_st);
        sterge_ultima_linie_diagonala(g.linie_sus);
        sterge_ultima_linie_diagonala(g.linie_jos);
        sterge_ultima_linie_dreapta(g.linie_a);
        sterge_ultima_linie_dreapta(g.linie_b);
        sterge_ultima_linie_dreapta(g.linie_plus_a);
        sterge_ultima_linie_dreapta(g.linie_plus_b);
        sterge_ultima_linie_dreapta(g.linie_minus);
        Amplificatoare_operationale.erase(Amplificatoare_operationale.find(g));

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            sterge_text(g.text, p);
        }
    }
}

public:void zoom_in(Amplificator_operational &n)
{
    if(n.dimensiune == DIMENSIUNE_MAX) afiseaza_eroare("Amplificatorul operational are dimensiunea maxima!");
    else
    {
        n.dimensiune++;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void zoom_out(Amplificator_operational &n)
{
    if(n.dimensiune == DIMENSIUNE_MIN) afiseaza_eroare("Amplificatorul operational are dimensiunea minima!");
    else
    {
        n.dimensiune--;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void rotire(Amplificator_operational &g)
{
    g.orientare = (g.orientare + 1) % 4;
    setare(g, g.centru, g.text, g.show_text);
}

public:bool verif_punct_apartine(Punct p, Amplificator_operational g)
{
    return p.x >= min(g.margine1.x, g.margine2.x) && p.x <= max(g.margine1.x, g.margine2.x) && p.y >= min(g.margine1.y, g.margine2.y) && p.y <= max(g.margine1.y, g.margine2.y);
}

public:bool verif_legatura_atinge(Legatura Leg, Amplificator_operational g)
{
    return (verif_punct_apartine(Leg.p1, g) || verif_punct_apartine(Leg.p2, g));
}

public:void setare_legaturi(Amplificator_operational g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    if(Leg[nr_de_legaturi].p1.x == g.conect[1].x && Leg[nr_de_legaturi].p1.y == g.conect[1].y) caz[nr_de_legaturi] = 1;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[2].x && Leg[nr_de_legaturi].p1.y == g.conect[2].y) caz[nr_de_legaturi] = 2;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[3].x && Leg[nr_de_legaturi].p1.y == g.conect[3].y) caz[nr_de_legaturi] = 3;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[1].x && Leg[nr_de_legaturi].p2.y == g.conect[1].y) caz[nr_de_legaturi] = 4;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[2].x && Leg[nr_de_legaturi].p2.y == g.conect[2].y) caz[nr_de_legaturi] = 5;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[3].x && Leg[nr_de_legaturi].p2.y == g.conect[3].y) caz[nr_de_legaturi] = 6;
}

public:void deseneaza_legaturi(Amplificator_operational g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    int i;

    for(i = 1; i <= nr_de_legaturi; i++)
    {
        if(caz[i] == 1) Leg[i].p1 = g.conect[1];
        else if(caz[i] == 2) Leg[i].p1 = g.conect[2];
        else if(caz[i] == 3) Leg[i].p1 = g.conect[3];
        else if(caz[i] == 4) Leg[i].p2 = g.conect[1];
        else if(caz[i] == 5) Leg[i].p2 = g.conect[2];
        else if(caz[i] == 6) Leg[i].p2 = g.conect[3];

        seteaza_linii_legatura(Leg[i]);
        deseneaza_legatura(Leg[i]);
    }
}


public:void Mod_punere(Buton &Punere_generator)
{
    Amplificator_operational g;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0)
    {
        sterge_ultimul(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
        getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

        setare(g, p1, "", 0);
        if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
    }

    buton.actioneaza_buton(Punere_generator);
};

public:void Mutare(Punct p1, bool &gasit)
{
    Amplificator_operational g;
    Legatura Leg[4];
    Punct p2 = p1;
    int i, nr_de_legaturi, caz[4];

    for(auto it:Amplificatoare_operationale)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            gasit = 1, nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 3) break;
                }

            while(ismouseclick(WM_LBUTTONUP) == 0)
            {
                sterge_ultimul(g);

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

                for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);

                setare(g, p1, g.text, g.show_text);
                if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1)
                {
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                }

                else
                {
                    setare(g, p2, g.text, g.show_text);
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                    string text = "Amplificatorul nu poate fi scos din chenar!";
                    afiseaza_eroare(text);
                    break;
                }

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
            }

            sterge_ultimul(g);
            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);
            if(verif_se_suprapune(g.margine1, g.margine2) == 1)
            {
                setare(g, p2, g.text, g.show_text);
                string text = "Amplificatorul se suprapune!";
                afiseaza_eroare(text);
            }
            deseneaza(g);
            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            clearmouseclick(WM_LBUTTONUP);
            break;
        }
    }
};

public:void Zoom(Punct p1, bool operatie, bool &gasit)
{
    Amplificator_operational g;
    Legatura Leg[4];
    int i, nr_de_legaturi, caz[4];

    for(auto it:Amplificatoare_operationale)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 3) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            if(operatie == 0) zoom_in(g);
            else if(operatie == 1) zoom_out(g);


            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Amplificatorul operational iese din chenar!");
                else afiseaza_eroare("Amplificatorul operational se suprapune cu o alta piesa!");

                if(operatie == 0) zoom_out(g);
                if(operatie == 1) zoom_in(g);
                deseneaza(g);
            }


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            gasit = 1;
            break;
        }
    }
}

public:void Rotire(Punct p1, bool &gasit)
{
    Amplificator_operational g, gg;
    Legatura Leg[4];
    int i, nr_de_legaturi, caz[4];

    for(auto it:Amplificatoare_operationale)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 3) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            gg = g;
            sterge_ultimul(g);
            rotire(g);

            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0)
            {
                deseneaza(g);
                deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
            }
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Amplificatorul operational iese din chenar!");
                else afiseaza_eroare("Amplificatorul operational se suprapune cu o alta piesa!");
                deseneaza(gg);
                deseneaza_legaturi(gg, nr_de_legaturi, Leg, caz);
            }

            break;
        }
    }
}

public:void Traseaza_linii(Punct &p, bool &gasit)
{
    Amplificator_operational n;
    int i, v[4], vv[4];

    for(auto it:Amplificatoare_operationale)
    {
        n = it;
        if(verif_punct_apartine(p, n) == 1 && (n.if_conect[1] == 0 || n.if_conect[2] == 0 || n.if_conect[3] == 0 || n.if_conect[4] == 0))
        {
            Amplificatoare_operationale.erase(Amplificatoare_operationale.find(it));

            for(i = 1; i <= 3; i++)
            {
                if(n.if_conect[i] == 0) vv[i] = 0;
                else vv[i] = 1;
            }

            for(i = 1; i <= 3; i++) v[i] = distanta_dintre_2_puncte(p, n.conect[i]) + vv[i] * (LATIME_WINDOW + LUNGIME_WINDOW);
            sort(v + 1, v + 4);
            for(i = 1; i <= 3; i++) if(v[1] == distanta_dintre_2_puncte(p, n.conect[i])) p = n.conect[i], n.if_conect[i] = 1, i = 4;

            Amplificatoare_operationale.insert(n);
            gasit = 1;
            break;
        }
    }
}

public:void Modificare_text(Punct p, bool &gasit)
{
    Amplificator_operational g;

    for(auto it:Amplificatoare_operationale)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1)
        {
            Amplificatoare_operationale.erase(Amplificatoare_operationale.find(it));
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            g.text = scrie_text(p, g.text);

            Amplificatoare_operationale.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Mod_sterge(Punct p, bool &gasit)
{
    int i;

    for(auto it:Amplificatoare_operationale)
    {
        if(verif_punct_apartine(p, it) == 1)
        {
            for(i = 1; i <= 3; i++)
            {
                for(auto itt:Legaturi)
                {
                    if(verif_legatura_atinge(itt, it) == 1)
                    {
                        sterge_ultima_legatura(itt);
                        break;
                    }
                }
            }

            sterge_ultimul(it);
            gasit = 1;
            break;
        }
    }
}

};

class DIODA_TUNNEL
{
    BUTON buton;

public:void setare(Dioda_tunnel &dt, Punct centru, string text, bool show_text)
{
    Punct p1, p2;
    int lg_linie_orizontala_st = 30 + dt.dimensiune * 5, lg_linie_orizontala_dr = 30 + dt.dimensiune * 5, lg_linie_st = 20 + dt.dimensiune * 4, lg_linie_dr = 20 + dt.dimensiune * 4, lg_linie_sus = 20 + dt.dimensiune * 4, lg_linie_jos = 20 + dt.dimensiune * 4, lg_linie_a = 7 + dt.dimensiune * 4, lg_linie_b = 7 + dt.dimensiune * 4, dist_de_la_centru = 10 + dt.dimensiune * 4, culoare = 15;

    dt.centru = centru;
    dt.lg_linie_orizontala_st = lg_linie_orizontala_st, dt.lg_linie_orizontala_dr = lg_linie_orizontala_dr, dt.lg_linie_st = lg_linie_st, dt.lg_linie_dr = lg_linie_dr;
    dt.lg_linie_sus = lg_linie_sus, dt.lg_linie_jos = lg_linie_jos, dt.lg_linie_a = lg_linie_a, dt.lg_linie_b = lg_linie_b, dt.dist_de_la_centru = dist_de_la_centru, dt.culoare = culoare;
    dt.text = text, dt.show_text = show_text;

    p1.x = dt.centru.x - dt.dist_de_la_centru - dt.lg_linie_orizontala_st, p2.x = dt.centru.x - dt.dist_de_la_centru;
    p1.y = p2.y = dt.centru.y;
    dt.linie_orizontala_st = setare_linie(p1, p2, dt.culoare);

    p1.x = dt.centru.x + dt.dist_de_la_centru, p2.x = dt.centru.x + dt.dist_de_la_centru + dt.lg_linie_orizontala_dr;
    p1.y = p2.y = dt.centru.y;
    dt.linie_orizontala_dr = setare_linie(p1, p2, dt.culoare);

    p1.x = p2.x = dt.centru.x - dt.dist_de_la_centru;
    p1.y = dt.centru.y - dt.lg_linie_st, p2.y = dt.centru.y + dt.lg_linie_st;
    dt.linie_st = setare_linie(p1, p2, dt.culoare);

    p1.x = dt.centru.x - dt.dist_de_la_centru, p2.x = dt.centru.x + dt.dist_de_la_centru;
    p1.y = dt.centru.y - dt.lg_linie_st, p2.y = dt.centru.y;
    dt.linie_sus = setare_linie(p1, p2, dt.culoare);

    p1.x = dt.centru.x - dt.dist_de_la_centru, p2.x = dt.centru.x + dt.dist_de_la_centru;
    p1.y = dt.centru.y + dt.lg_linie_jos, p2.y = dt.centru.y;
    dt.linie_jos = setare_linie(p1, p2, dt.culoare);

    p1.x = p2.x = dt.centru.x + dt.dist_de_la_centru;
    p1.y = dt.centru.y - dt.lg_linie_dr, p2.y = dt.centru.y + dt.lg_linie_dr;
    dt.linie_dr = setare_linie(p1, p2, dt.culoare);

    p1.x = dt.centru.x + dt.dist_de_la_centru - dt.lg_linie_a, p2.x = dt.centru.x + dt.dist_de_la_centru;
    p1.y = p2.y = dt.centru.y - dt.lg_linie_sus;
    dt.linie_a = setare_linie(p1, p2, dt.culoare);

    p1.x = dt.centru.x + dt.dist_de_la_centru - dt.lg_linie_b, p2.x = dt.centru.x + dt.dist_de_la_centru;
    p1.y = p2.y = dt.centru.y + dt.lg_linie_jos;
    dt.linie_b = setare_linie(p1, p2, dt.culoare);

    dt.margine1.x = dt.linie_orizontala_st.p1.x, dt.margine1.y = dt.linie_sus.p1.y, dt.margine2.x = dt.linie_orizontala_dr.p2.x, dt.margine2.y = dt.linie_dr.p2.y;


    regleaza_linie_dreapta(dt.linie_orizontala_st), regleaza_linie_dreapta(dt.linie_orizontala_dr), regleaza_linie_dreapta(dt.linie_st), regleaza_linie_dreapta(dt.linie_dr), regleaza_linie_dreapta(dt.linie_a), regleaza_linie_dreapta(dt.linie_b);
    dt.conect[1] = dt.linie_orizontala_st.p1, dt.conect[2] = dt.linie_orizontala_dr.p2;

    int i;
    for(i = 1; i <= dt.orientare; i++)
    {
        rotire_linie(dt.centru, dt.linie_orizontala_st), rotire_linie(dt.centru, dt.linie_orizontala_dr), rotire_linie(dt.centru, dt.linie_st), rotire_linie(dt.centru, dt.linie_dr), rotire_linie(dt.centru, dt.linie_a), rotire_linie(dt.centru, dt.linie_b), rotire_linie(dt.centru, dt.linie_sus), rotire_linie(dt.centru, dt.linie_jos);
        rotire_punct(dt.centru, dt.margine1), rotire_punct(dt.centru, dt.margine2);
        rotire_punct(dt.centru, dt.conect[1]), rotire_punct(dt.centru, dt.conect[2]);
        regleaza_linie_dreapta(dt.linie_orizontala_st), regleaza_linie_dreapta(dt.linie_orizontala_dr), regleaza_linie_dreapta(dt.linie_st), regleaza_linie_dreapta(dt.linie_dr), regleaza_linie_dreapta(dt.linie_a), regleaza_linie_dreapta(dt.linie_b);
    }
}

public:void deseneaza(Dioda_tunnel g)
{
    if(g.culoare != 0)
    {
        deseneaza_linie_dreapta(g.linie_orizontala_st);
        deseneaza_linie_dreapta(g.linie_orizontala_dr);
        deseneaza_linie_dreapta(g.linie_st);
        deseneaza_linie_diagonala(g.linie_sus);
        deseneaza_linie_diagonala(g.linie_jos);
        deseneaza_linie_dreapta(g.linie_dr);
        deseneaza_linie_dreapta(g.linie_a);
        deseneaza_linie_dreapta(g.linie_b);
        Diode_tunnel.insert(g);

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            deseneaza_text(g.text, p);
        }
    }
}

public:void sterge_ultimul(Dioda_tunnel g)
{
    if(Diode_tunnel.find(g) != Diode_tunnel.end())
    {
        sterge_ultima_linie_dreapta(g.linie_orizontala_st);
        sterge_ultima_linie_dreapta(g.linie_orizontala_dr);
        sterge_ultima_linie_dreapta(g.linie_st);
        sterge_ultima_linie_diagonala(g.linie_sus);
        sterge_ultima_linie_diagonala(g.linie_jos);
        sterge_ultima_linie_dreapta(g.linie_dr);
        sterge_ultima_linie_dreapta(g.linie_a);
        sterge_ultima_linie_dreapta(g.linie_b);
        Diode_tunnel.erase(Diode_tunnel.find(g));

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            sterge_text(g.text, p);
        }
    }
}

public:void zoom_in(Dioda_tunnel &n)
{
    if(n.dimensiune == DIMENSIUNE_MAX) afiseaza_eroare("Dioda Tunnel are dimensiunea maxima!");
    else
    {
        n.dimensiune++;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void zoom_out(Dioda_tunnel &n)
{
    if(n.dimensiune == DIMENSIUNE_MIN) afiseaza_eroare("Dioda Tunnel are dimensiunea minima!");
    else
    {
        n.dimensiune--;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void rotire(Dioda_tunnel &g)
{
    g.orientare = (g.orientare + 1) % 4;
    setare(g, g.centru, g.text, g.show_text);
}

public:bool verif_punct_apartine(Punct p, Dioda_tunnel g)
{
    return p.x >= min(g.margine1.x, g.margine2.x) && p.x <= max(g.margine1.x, g.margine2.x) && p.y >= min(g.margine1.y, g.margine2.y) && p.y <= max(g.margine1.y, g.margine2.y);
}

public:bool verif_legatura_atinge(Legatura Leg, Dioda_tunnel g)
{
    return (verif_punct_apartine(Leg.p1, g) || verif_punct_apartine(Leg.p2, g));
}

public:void setare_legaturi(Dioda_tunnel g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    if(Leg[nr_de_legaturi].p1.x == g.conect[1].x && Leg[nr_de_legaturi].p1.y == g.conect[1].y) caz[nr_de_legaturi] = 1;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[2].x && Leg[nr_de_legaturi].p1.y == g.conect[2].y) caz[nr_de_legaturi] = 2;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[1].x && Leg[nr_de_legaturi].p2.y == g.conect[1].y) caz[nr_de_legaturi] = 3;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[2].x && Leg[nr_de_legaturi].p2.y == g.conect[2].y) caz[nr_de_legaturi] = 4;
}

public:void deseneaza_legaturi(Dioda_tunnel g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    int i;

    for(i = 1; i <= nr_de_legaturi; i++)
    {
        if(caz[i] == 1) Leg[i].p1 = g.conect[1];
        else if(caz[i] == 2) Leg[i].p1 = g.conect[2];
        else if(caz[i] == 3) Leg[i].p2 = g.conect[1];
        else if(caz[i] == 4) Leg[i].p2 = g.conect[2];

        seteaza_linii_legatura(Leg[i]);
        deseneaza_legatura(Leg[i]);
    }
}


public:void Mod_punere(Buton &Punere_generator)
{
    Dioda_tunnel g;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0)
    {
        sterge_ultimul(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
        getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

        setare(g, p1, "", 0);
        if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
    }

    buton.actioneaza_buton(Punere_generator);
};

public:void Mutare(Punct p1, bool &gasit)
{
    Dioda_tunnel g;
    Legatura Leg[3];
    Punct p2 = p1;
    int i, nr_de_legaturi, caz[3];

    for(auto it:Diode_tunnel)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            gasit = 1, nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            while(ismouseclick(WM_LBUTTONUP) == 0)
            {
                sterge_ultimul(g);

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

                for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);

                setare(g, p1, g.text, g.show_text);
                if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1)
                {
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                }

                else
                {
                    setare(g, p2, g.text, g.show_text);
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                    string text = "Dioda nu poate fi scoasa din chenar!";
                    afiseaza_eroare(text);
                    break;
                }

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
            }

            sterge_ultimul(g);
            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);
            if(verif_se_suprapune(g.margine1, g.margine2) == 1)
            {
                setare(g, p2, g.text, g.show_text);
                string text = "Dioda se suprapune!";
                afiseaza_eroare(text);
            }
            deseneaza(g);
            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            clearmouseclick(WM_LBUTTONUP);
            break;
        }
    }
};

public:void Zoom(Punct p1, bool operatie, bool &gasit)
{
    Dioda_tunnel g;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Diode_tunnel)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            if(operatie == 0) zoom_in(g);
            else if(operatie == 1) zoom_out(g);


            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Dioda Tunnel iese din chenar!");
                else afiseaza_eroare("Dioda Tunnel se suprapune cu o alta piesa!");

                if(operatie == 0) zoom_out(g);
                if(operatie == 1) zoom_in(g);
                deseneaza(g);
            }


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            gasit = 1;
            break;
        }
    }
}

public:void Rotire(Punct p1, bool &gasit)
{
    Dioda_tunnel g, gg;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Diode_tunnel)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            gg = g;
            sterge_ultimul(g);
            rotire(g);

            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0)
            {
                deseneaza(g);
                deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
            }
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Dioda Tunnel iese din chenar!");
                else afiseaza_eroare("Dioda Tunnel se suprapune cu o alta piesa!");
                deseneaza(gg);
                deseneaza_legaturi(gg, nr_de_legaturi, Leg, caz);
            }

            break;
        }
    }
}

public:void Traseaza_linii(Punct &p, bool &gasit)
{
    Dioda_tunnel g;

    for(auto it:Diode_tunnel)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1 && (g.if_conect[1] == 0 || g.if_conect[2] == 0))
        {
            Diode_tunnel.erase(Diode_tunnel.find(it));

            if(g.if_conect[1] == 0 && g.if_conect[2] == 1) p = g.conect[1], g.if_conect[1] = 1;
            else if(g.if_conect[1] == 1 && g.if_conect[2] == 0) p = g.conect[2], g.if_conect[2] = 1;
            else if(distanta_dintre_2_puncte(p, g.conect[1]) < distanta_dintre_2_puncte(p, g.conect[2])) p = g.conect[1], g.if_conect[1] = 1;
            else p = g.conect[2], g.if_conect[2] = 1;

            Diode_tunnel.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Modificare_text(Punct p, bool &gasit)
{
    Dioda_tunnel g;

    for(auto it:Diode_tunnel)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1)
        {
            Diode_tunnel.erase(Diode_tunnel.find(it));
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            g.text = scrie_text(p, g.text);

            Diode_tunnel.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Mod_sterge(Punct p, bool &gasit)
{
    int i;

    for(auto it:Diode_tunnel)
    {
        if(verif_punct_apartine(p, it) == 1)
        {
            for(i = 1; i <= 2; i++)
            {
                for(auto itt:Legaturi)
                {
                    if(verif_legatura_atinge(itt, it) == 1)
                    {
                        sterge_ultima_legatura(itt);
                        break;
                    }
                }
            }

            sterge_ultimul(it);
            gasit = 1;
            break;
        }
    }
}

};

class DIODA_ZENER
{
    BUTON buton;

public:void setare(Dioda_zener &dz, Punct centru, string text, bool show_text)
{
    Punct p1, p2;
    int lg_linie_orizontala_st = 30 + dz.dimensiune * 5, lg_linie_orizontala_dr = 30 + dz.dimensiune * 5, lg_linie_st = 20 + dz.dimensiune * 4, lg_linie_dr = 20 + dz.dimensiune * 4, lg_linie_sus = 20 + dz.dimensiune * 4, lg_linie_jos = 20 + dz.dimensiune * 4, lg_linie_a = 7 + dz.dimensiune * 4, lg_linie_b = 7 + dz.dimensiune * 4, dist_de_la_centru = 10 + dz.dimensiune * 4, culoare = 15;

    dz.centru = centru;
    dz.lg_linie_orizontala_st = lg_linie_orizontala_st, dz.lg_linie_orizontala_dr = lg_linie_orizontala_dr, dz.lg_linie_st = lg_linie_st, dz.lg_linie_dr = lg_linie_dr;
    dz.lg_linie_sus = lg_linie_sus, dz.lg_linie_jos = lg_linie_jos, dz.lg_linie_a = lg_linie_a, dz.lg_linie_b = lg_linie_b, dz.dist_de_la_centru = dist_de_la_centru, dz.culoare = culoare;
    dz.text = text, dz.show_text = show_text;

    p1.x = dz.centru.x - dz.dist_de_la_centru - dz.lg_linie_orizontala_st, p2.x = dz.centru.x - dz.dist_de_la_centru;
    p1.y = p2.y = dz.centru.y;
    dz.linie_orizontala_st = setare_linie(p1, p2, dz.culoare);

    p1.x = dz.centru.x + dz.dist_de_la_centru, p2.x = dz.centru.x + dz.dist_de_la_centru + dz.lg_linie_orizontala_dr;
    p1.y = p2.y = dz.centru.y;
    dz.linie_orizontala_dr = setare_linie(p1, p2, dz.culoare);

    p1.x = p2.x = dz.centru.x - dz.dist_de_la_centru;
    p1.y = dz.centru.y - dz.lg_linie_st, p2.y = dz.centru.y + dz.lg_linie_st;
    dz.linie_st = setare_linie(p1, p2, dz.culoare);

    p1.x = dz.centru.x - dz.dist_de_la_centru, p2.x = dz.centru.x + dz.dist_de_la_centru;
    p1.y = dz.centru.y - dz.lg_linie_st, p2.y = dz.centru.y;
    dz.linie_sus = setare_linie(p1, p2, dz.culoare);

    p1.x = dz.centru.x - dz.dist_de_la_centru, p2.x = dz.centru.x + dz.dist_de_la_centru;
    p1.y = dz.centru.y + dz.lg_linie_jos, p2.y = dz.centru.y;
    dz.linie_jos = setare_linie(p1, p2, dz.culoare);

    p1.x = p2.x = dz.centru.x + dz.dist_de_la_centru;
    p1.y = dz.centru.y - dz.lg_linie_dr, p2.y = dz.centru.y + dz.lg_linie_dr;
    dz.linie_dr = setare_linie(p1, p2, dz.culoare);

    p1.x = dz.centru.x + dz.dist_de_la_centru - dz.lg_linie_a, p2.x = dz.centru.x + dz.dist_de_la_centru;
    p1.y = p2.y = dz.centru.y - dz.lg_linie_sus;
    dz.linie_a = setare_linie(p1, p2, dz.culoare);

    p1.x = dz.centru.x + dz.dist_de_la_centru, p2.x = dz.centru.x + dz.dist_de_la_centru + dz.lg_linie_b;
    p1.y = p2.y = dz.centru.y + dz.lg_linie_jos;
    dz.linie_b = setare_linie(p1, p2, dz.culoare);

    dz.margine1.x = dz.linie_orizontala_st.p1.x, dz.margine1.y = dz.linie_sus.p1.y, dz.margine2.x = dz.linie_orizontala_dr.p2.x, dz.margine2.y = dz.linie_dr.p2.y;


    regleaza_linie_dreapta(dz.linie_orizontala_st), regleaza_linie_dreapta(dz.linie_orizontala_dr), regleaza_linie_dreapta(dz.linie_st), regleaza_linie_dreapta(dz.linie_dr), regleaza_linie_dreapta(dz.linie_a), regleaza_linie_dreapta(dz.linie_b);
    dz.conect[1] = dz.linie_orizontala_st.p1, dz.conect[2] = dz.linie_orizontala_dr.p2;

    int i;
    for(i = 1; i <= dz.orientare; i++)
    {
        rotire_linie(dz.centru, dz.linie_orizontala_st), rotire_linie(dz.centru, dz.linie_orizontala_dr), rotire_linie(dz.centru, dz.linie_st), rotire_linie(dz.centru, dz.linie_dr), rotire_linie(dz.centru, dz.linie_a), rotire_linie(dz.centru, dz.linie_b), rotire_linie(dz.centru, dz.linie_sus), rotire_linie(dz.centru, dz.linie_jos);
        rotire_punct(dz.centru, dz.margine1), rotire_punct(dz.centru, dz.margine2);
        rotire_punct(dz.centru, dz.conect[1]), rotire_punct(dz.centru, dz.conect[2]);

        regleaza_linie_dreapta(dz.linie_orizontala_st), regleaza_linie_dreapta(dz.linie_orizontala_dr), regleaza_linie_dreapta(dz.linie_st), regleaza_linie_dreapta(dz.linie_dr), regleaza_linie_dreapta(dz.linie_a), regleaza_linie_dreapta(dz.linie_b);
    }
}

public:void deseneaza(Dioda_zener g)
{
    if(g.culoare != 0)
    {
        deseneaza_linie_dreapta(g.linie_orizontala_st);
        deseneaza_linie_dreapta(g.linie_orizontala_dr);
        deseneaza_linie_dreapta(g.linie_st);
        deseneaza_linie_diagonala(g.linie_sus);
        deseneaza_linie_diagonala(g.linie_jos);
        deseneaza_linie_dreapta(g.linie_dr);
        deseneaza_linie_dreapta(g.linie_a);
        deseneaza_linie_dreapta(g.linie_b);
        Diode_zener.insert(g);

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            deseneaza_text(g.text, p);
        }
    }
}

public:void sterge_ultimul(Dioda_zener g)
{
    if(Diode_zener.find(g) != Diode_zener.end())
    {
        sterge_ultima_linie_dreapta(g.linie_orizontala_st);
        sterge_ultima_linie_dreapta(g.linie_orizontala_dr);
        sterge_ultima_linie_dreapta(g.linie_st);
        sterge_ultima_linie_diagonala(g.linie_sus);
        sterge_ultima_linie_diagonala(g.linie_jos);
        sterge_ultima_linie_dreapta(g.linie_dr);
        sterge_ultima_linie_dreapta(g.linie_a);
        sterge_ultima_linie_dreapta(g.linie_b);
        Diode_zener.erase(Diode_zener.find(g));

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            sterge_text(g.text, p);
        }
    }
}

public:void zoom_in(Dioda_zener &n)
{
    if(n.dimensiune == DIMENSIUNE_MAX) afiseaza_eroare("Dioda Zener are dimensiunea maxima!");
    else
    {
        n.dimensiune++;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void zoom_out(Dioda_zener &n)
{
    if(n.dimensiune == DIMENSIUNE_MIN) afiseaza_eroare("Dioda Zener are dimensiunea minima!");
    else
    {
        n.dimensiune--;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void rotire(Dioda_zener &g)
{
    g.orientare = (g.orientare + 1) % 4;
    setare(g, g.centru, g.text, g.show_text);
}

public:bool verif_punct_apartine(Punct p, Dioda_zener g)
{
    return p.x >= min(g.margine1.x, g.margine2.x) && p.x <= max(g.margine1.x, g.margine2.x) && p.y >= min(g.margine1.y, g.margine2.y) && p.y <= max(g.margine1.y, g.margine2.y);
}

public:bool verif_legatura_atinge(Legatura Leg, Dioda_zener g)
{
    return (verif_punct_apartine(Leg.p1, g) || verif_punct_apartine(Leg.p2, g));
}

public:void setare_legaturi(Dioda_zener g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    if(Leg[nr_de_legaturi].p1.x == g.conect[1].x && Leg[nr_de_legaturi].p1.y == g.conect[1].y) caz[nr_de_legaturi] = 1;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[2].x && Leg[nr_de_legaturi].p1.y == g.conect[2].y) caz[nr_de_legaturi] = 2;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[1].x && Leg[nr_de_legaturi].p2.y == g.conect[1].y) caz[nr_de_legaturi] = 3;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[2].x && Leg[nr_de_legaturi].p2.y == g.conect[2].y) caz[nr_de_legaturi] = 4;
}

public:void deseneaza_legaturi(Dioda_zener g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    int i;

    for(i = 1; i <= nr_de_legaturi; i++)
    {
        if(caz[i] == 1) Leg[i].p1 = g.conect[1];
        else if(caz[i] == 2) Leg[i].p1 = g.conect[2];
        else if(caz[i] == 3) Leg[i].p2 = g.conect[1];
        else if(caz[i] == 4) Leg[i].p2 = g.conect[2];

        seteaza_linii_legatura(Leg[i]);
        deseneaza_legatura(Leg[i]);
    }
}


public:void Mod_punere(Buton &Punere_generator)
{
    Dioda_zener g;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0)
    {
        sterge_ultimul(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
        getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

        setare(g, p1, "", 0);
        if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
    }

    buton.actioneaza_buton(Punere_generator);
};

public:void Mutare(Punct p1, bool &gasit)
{
    Dioda_zener g;
    Legatura Leg[3];
    Punct p2 = p1;
    int i, nr_de_legaturi, caz[3];

    for(auto it:Diode_zener)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            gasit = 1, nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            while(ismouseclick(WM_LBUTTONUP) == 0)
            {
                sterge_ultimul(g);

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

                for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);

                setare(g, p1, g.text, g.show_text);
                if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1)
                {
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                }

                else
                {
                    setare(g, p2, g.text, g.show_text);
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                    string text = "Dioda nu poate fi scoasa din chenar!";
                    afiseaza_eroare(text);
                    break;
                }

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
            }

            sterge_ultimul(g);
            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);
            if(verif_se_suprapune(g.margine1, g.margine2) == 1)
            {
                setare(g, p2, g.text, g.show_text);
                string text = "Dioda se suprapune!";
                afiseaza_eroare(text);
            }
            deseneaza(g);
            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            clearmouseclick(WM_LBUTTONUP);
            break;
        }
    }
};

public:void Zoom(Punct p1, bool operatie, bool &gasit)
{
    Dioda_zener g;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Diode_zener)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            if(operatie == 0) zoom_in(g);
            else if(operatie == 1) zoom_out(g);


            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Dioda Zener iese din chenar!");
                else afiseaza_eroare("Dioda Zener se suprapune cu o alta piesa!");

                if(operatie == 0) zoom_out(g);
                if(operatie == 1) zoom_in(g);
                deseneaza(g);
            }


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            gasit = 1;
            break;
        }
    }
}

public:void Rotire(Punct p1, bool &gasit)
{
    Dioda_zener g, gg;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Diode_zener)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            gg = g;
            sterge_ultimul(g);
            rotire(g);

            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0)
            {
                deseneaza(g);
                deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
            }
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Dioda Zener iese din chenar!");
                else afiseaza_eroare("Dioda Zener se suprapune cu o alta piesa!");
                deseneaza(gg);
                deseneaza_legaturi(gg, nr_de_legaturi, Leg, caz);
            }

            break;
        }
    }
}

public:void Traseaza_linii(Punct &p, bool &gasit)
{
    Dioda_zener g;

    for(auto it:Diode_zener)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1 && (g.if_conect[1] == 0 || g.if_conect[2] == 0))
        {
            Diode_zener.erase(Diode_zener.find(it));

            if(g.if_conect[1] == 0 && g.if_conect[2] == 1) p = g.conect[1], g.if_conect[1] = 1;
            else if(g.if_conect[1] == 1 && g.if_conect[2] == 0) p = g.conect[2], g.if_conect[2] = 1;
            else if(distanta_dintre_2_puncte(p, g.conect[1]) < distanta_dintre_2_puncte(p, g.conect[2])) p = g.conect[1], g.if_conect[1] = 1;
            else p = g.conect[2], g.if_conect[2] = 1;

            Diode_zener.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Modificare_text(Punct p, bool &gasit)
{
    Dioda_zener g;

    for(auto it:Diode_zener)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1)
        {
            Diode_zener.erase(Diode_zener.find(it));
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            g.text = scrie_text(p, g.text);

            Diode_zener.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Mod_sterge(Punct p, bool &gasit)
{
    int i;

    for(auto it:Diode_zener)
    {
        if(verif_punct_apartine(p, it) == 1)
        {
            for(i = 1; i <= 2; i++)
            {
                for(auto itt:Legaturi)
                {
                    if(verif_legatura_atinge(itt, it) == 1)
                    {
                        sterge_ultima_legatura(itt);
                        break;
                    }
                }
            }

            sterge_ultimul(it);
            gasit = 1;
            break;
        }
    }
}

};

class TRANZISTOR_NPN
{
    BUTON buton;

public:void setare(Tranzistor_npn &tn, Punct centru, string text, bool show_text)
{
    Punct p1, p2;
    int lg_linie_orizontala = 20 + tn.dimensiune * 5, lg_linie_verticala = 20 + tn.dimensiune * 5, lg_linie_oblica_sus = 12 + tn.dimensiune * 4, lg_linie_oblica_jos = 12 + tn.dimensiune * 4, lg_linie_sus = 20 + tn.dimensiune * 4, lg_linie_jos = 20 + tn.dimensiune * 4, dist_de_la_centru = 20 + tn.dimensiune * 4, culoare = 15;
    int lg_linie_a = 5 + tn.dimensiune, lg_linie_b = 5 + tn.dimensiune, lg_linie_c = 5 + tn.dimensiune * 4;

    tn.centru = centru;
    tn.lg_linie_orizontala = lg_linie_orizontala, tn.lg_linie_verticala = lg_linie_verticala, tn.lg_linie_oblica_jos = lg_linie_oblica_jos, tn.lg_linie_oblica_sus = lg_linie_oblica_sus;
    tn.lg_linie_jos = lg_linie_jos, tn.lg_linie_sus = lg_linie_sus, tn.dist_de_la_centru = dist_de_la_centru, tn.culoare = culoare;
    tn.lg_linie_a = lg_linie_a, tn.lg_linie_b = lg_linie_b, tn.lg_linie_c = lg_linie_c;
    tn.text = text, tn.show_text = show_text;

    p1.x = tn.centru.x - tn.dist_de_la_centru - tn.lg_linie_orizontala / 2, p2.x = tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2;
    p1.y = p2.y = tn.centru.y;
    tn.linie_orizontala = setare_linie(p1, p2, tn.culoare);

    p1.x = p2.x = tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2;
    p1.y = tn.centru.y - tn.lg_linie_verticala / 2, p2.y = tn.centru.y + tn.lg_linie_verticala / 2;
    tn.linie_verticala = setare_linie(p1, p2, tn.culoare);

    p1.x = tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2, p2.x = tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2 + tn.lg_linie_oblica_sus;
    p1.y = tn.centru.y, p2.y = tn.centru.y - tn.lg_linie_oblica_sus;
    tn.linie_oblica_sus = setare_linie(p1, p2, tn.culoare);

    p1.x = tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2, p2.x = tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2 + tn.lg_linie_oblica_jos;
    p1.y = tn.centru.y, p2.y = tn.centru.y + tn.lg_linie_oblica_jos;
    tn.linie_oblica_jos = setare_linie(p1, p2, tn.culoare);

    p1.x = p2.x = tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2 + tn.lg_linie_oblica_sus;
    p1.y = tn.centru.y - tn.lg_linie_oblica_sus - tn.lg_linie_sus, p2.y = tn.centru.y - tn.lg_linie_oblica_sus;
    tn.linie_sus = setare_linie(p1, p2, tn.culoare);

    p1.x = p2.x = tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2 + tn.lg_linie_oblica_jos;
    p1.y = tn.centru.y + tn.lg_linie_oblica_jos, p2.y = tn.centru.y + tn.lg_linie_oblica_jos + tn.lg_linie_jos;
    tn.linie_jos = setare_linie(p1, p2, tn.culoare);

    p1.x = (tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2 + tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2 + tn.lg_linie_oblica_jos) / 2 - tn.lg_linie_a;
    p2.x = (tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2 + tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2 + tn.lg_linie_oblica_jos) / 2;
    p1.y = p2.y = (tn.centru.y + tn.centru.y + tn.lg_linie_oblica_jos) / 2;
    tn.linie_a = setare_linie(p1, p2, tn.culoare);

    p1.x = p2.x = (tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2 + tn.centru.x - tn.dist_de_la_centru + tn.lg_linie_orizontala / 2 + tn.lg_linie_oblica_jos) / 2;
    p1.y = (tn.centru.y + tn.centru.y + tn.lg_linie_oblica_jos) / 2 - tn.lg_linie_b;
    p2.y = (tn.centru.y + tn.centru.y + tn.lg_linie_oblica_jos) / 2;
    tn.linie_b = setare_linie(p1, p2, tn.culoare);

    tn.margine1.x = tn.linie_orizontala.p1.x, tn.margine1.y = tn.linie_sus.p1.y, tn.margine2.x = tn.centru.x + tn.dist_de_la_centru, tn.margine2.y = tn.linie_jos.p2.y;


    regleaza_linie_dreapta(tn.linie_orizontala), regleaza_linie_dreapta(tn.linie_verticala), regleaza_linie_dreapta(tn.linie_sus), regleaza_linie_dreapta(tn.linie_jos), regleaza_linie_dreapta(tn.linie_a), regleaza_linie_dreapta(tn.linie_b);
    tn.conect[1] = tn.linie_orizontala.p1, tn.conect[2] = tn.linie_sus.p1, tn.conect[3] = tn.linie_jos.p2;

    int i;
    for(i = 1; i <= tn.orientare; i++)
    {
        rotire_linie(tn.centru, tn.linie_orizontala), rotire_linie(tn.centru, tn.linie_verticala), rotire_linie(tn.centru, tn.linie_sus), rotire_linie(tn.centru, tn.linie_jos), rotire_linie(tn.centru, tn.linie_a), rotire_linie(tn.centru, tn.linie_b), rotire_linie(tn.centru, tn.linie_oblica_sus), rotire_linie(tn.centru, tn.linie_oblica_jos);
        rotire_punct(tn.centru, tn.margine1), rotire_punct(tn.centru, tn.margine2);
        rotire_punct(tn.centru, tn.conect[1]), rotire_punct(tn.centru, tn.conect[2]), rotire_punct(tn.centru, tn.conect[3]);

        regleaza_linie_dreapta(tn.linie_orizontala), regleaza_linie_dreapta(tn.linie_verticala), regleaza_linie_dreapta(tn.linie_sus), regleaza_linie_dreapta(tn.linie_jos), regleaza_linie_dreapta(tn.linie_a), regleaza_linie_dreapta(tn.linie_b);
    }
};

public:void deseneaza(Tranzistor_npn g)
{
    if(g.culoare != 0)
    {
        deseneaza_linie_dreapta(g.linie_orizontala);
        deseneaza_linie_dreapta(g.linie_verticala);
        deseneaza_linie_diagonala(g.linie_oblica_sus);
        deseneaza_linie_diagonala(g.linie_oblica_jos);
        deseneaza_linie_dreapta(g.linie_sus);
        deseneaza_linie_dreapta(g.linie_jos);
        deseneaza_cerc_gol(g.centru, g.dist_de_la_centru, g.culoare);
        deseneaza_linie_dreapta(g.linie_a);
        deseneaza_linie_dreapta(g.linie_b);
        Tranzistoare_npn.insert(g);

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0) p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            else if(g.orientare == 1) p.x = g.centru.x, p.y = min(g.margine1.y, g.margine2.y) - 10;
            else if(g.orientare == 2) p.x = min(g.margine1.x, g.margine2.x) - 17, p.y = g.centru.y;
            else p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;

            deseneaza_text(g.text, p);
        }
    }
}

public:void sterge_ultimul(Tranzistor_npn g)
{
    if(Tranzistoare_npn.find(g) != Tranzistoare_npn.end())
    {
        sterge_ultima_linie_dreapta(g.linie_orizontala);
        sterge_ultima_linie_dreapta(g.linie_verticala);
        sterge_ultima_linie_diagonala(g.linie_oblica_sus);
        sterge_ultima_linie_diagonala(g.linie_oblica_jos);
        sterge_ultima_linie_dreapta(g.linie_sus);
        sterge_ultima_linie_dreapta(g.linie_jos);
        sterge_cerc_gol(g.centru, g.dist_de_la_centru);
        sterge_ultima_linie_dreapta(g.linie_a);
        sterge_ultima_linie_dreapta(g.linie_b);
        Tranzistoare_npn.erase(Tranzistoare_npn.find(g));

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0) p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            else if(g.orientare == 1) p.x = g.centru.x, p.y = min(g.margine1.y, g.margine2.y) - 10;
            else if(g.orientare == 2) p.x = min(g.margine1.x, g.margine2.x) - 17, p.y = g.centru.y;
            else p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;

            sterge_text(g.text, p);
        }
    }
}

public:void zoom_in(Tranzistor_npn &n)
{
    if(n.dimensiune == DIMENSIUNE_MAX) afiseaza_eroare("Tranzistorul NPN are dimensiunea maxima!");
    else
    {
        n.dimensiune++;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void zoom_out(Tranzistor_npn &n)
{
    if(n.dimensiune == DIMENSIUNE_MIN) afiseaza_eroare("Tranzistorul NPN are dimensiunea minima!");
    else
    {
        n.dimensiune--;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void rotire(Tranzistor_npn &g)
{
    g.orientare = (g.orientare + 1) % 4;
    setare(g, g.centru, g.text, g.show_text);
}

public:bool verif_punct_apartine(Punct p, Tranzistor_npn g)
{
    return p.x >= min(g.margine1.x, g.margine2.x) && p.x <= max(g.margine1.x, g.margine2.x) && p.y >= min(g.margine1.y, g.margine2.y) && p.y <= max(g.margine1.y, g.margine2.y);
}

public:bool verif_legatura_atinge(Legatura Leg, Tranzistor_npn g)
{
    return (verif_punct_apartine(Leg.p1, g) || verif_punct_apartine(Leg.p2, g));
}

public:void setare_legaturi(Tranzistor_npn g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    if(Leg[nr_de_legaturi].p1.x == g.conect[1].x && Leg[nr_de_legaturi].p1.y == g.conect[1].y) caz[nr_de_legaturi] = 1;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[2].x && Leg[nr_de_legaturi].p1.y == g.conect[2].y) caz[nr_de_legaturi] = 2;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[3].x && Leg[nr_de_legaturi].p1.y == g.conect[3].y) caz[nr_de_legaturi] = 3;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[1].x && Leg[nr_de_legaturi].p2.y == g.conect[1].y) caz[nr_de_legaturi] = 4;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[2].x && Leg[nr_de_legaturi].p2.y == g.conect[2].y) caz[nr_de_legaturi] = 5;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[3].x && Leg[nr_de_legaturi].p2.y == g.conect[3].y) caz[nr_de_legaturi] = 6;
}

public:void deseneaza_legaturi(Tranzistor_npn g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    int i;

    for(i = 1; i <= nr_de_legaturi; i++)
    {
        if(caz[i] == 1) Leg[i].p1 = g.conect[1];
        else if(caz[i] == 2) Leg[i].p1 = g.conect[2];
        else if(caz[i] == 3) Leg[i].p1 = g.conect[3];
        else if(caz[i] == 4) Leg[i].p2 = g.conect[1];
        else if(caz[i] == 5) Leg[i].p2 = g.conect[2];
        else if(caz[i] == 6) Leg[i].p2 = g.conect[3];

        seteaza_linii_legatura(Leg[i]);
        deseneaza_legatura(Leg[i]);
    }
}


public:void Mod_punere(Buton &Punere_generator)
{
    Tranzistor_npn g;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0)
    {
        sterge_ultimul(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
        getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

        setare(g, p1, "", 0);
        if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
    }

    buton.actioneaza_buton(Punere_generator);
}

public:void Mutare(Punct p1, bool &gasit)
{
    Tranzistor_npn g;
    Legatura Leg[4];
    Punct p2 = p1;
    int i, nr_de_legaturi, caz[4];

    for(auto it:Tranzistoare_npn)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            gasit = 1, nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 3) break;
                }

            while(ismouseclick(WM_LBUTTONUP) == 0)
            {
                sterge_ultimul(g);

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

                for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);

                setare(g, p1, g.text, g.show_text);
                if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1)
                {
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                }

                else
                {
                    setare(g, p2, g.text, g.show_text);
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                    string text = "Tranzistorul NPN nu poate fi scos din chenar!";
                    afiseaza_eroare(text);
                    break;
                }

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
            }

            sterge_ultimul(g);
            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);
            if(verif_se_suprapune(g.margine1, g.margine2) == 1)
            {
                setare(g, p2, g.text, g.show_text);
                string text = "Tranzistorul NPN se suprapune!";
                afiseaza_eroare(text);
            }
            deseneaza(g);
            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            clearmouseclick(WM_LBUTTONUP);
            break;
        }
    }
}

public:void Zoom(Punct p1, bool operatie, bool &gasit)
{
    Tranzistor_npn g;
    Legatura Leg[4];
    int i, nr_de_legaturi, caz[4];

    for(auto it:Tranzistoare_npn)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 3) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            if(operatie == 0) zoom_in(g);
            else if(operatie == 1) zoom_out(g);


            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Tranzistorul NPN iese din chenar!");
                else afiseaza_eroare("Tranzistorul NPN se suprapune cu o alta piesa!");

                if(operatie == 0) zoom_out(g);
                if(operatie == 1) zoom_in(g);
                deseneaza(g);
            }


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            gasit = 1;
            break;
        }
    }
}

public:void Rotire(Punct p1, bool &gasit)
{
    Tranzistor_npn g, gg;
    Legatura Leg[4];
    int i, nr_de_legaturi, caz[4];

    for(auto it:Tranzistoare_npn)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 3) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            gg = g;
            sterge_ultimul(g);
            rotire(g);

            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0)
            {
                deseneaza(g);
                deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
            }
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Tranzistorul NPN iese din chenar!");
                else afiseaza_eroare("Tranzistorul NPN se suprapune cu o alta piesa!");
                deseneaza(gg);
                deseneaza_legaturi(gg, nr_de_legaturi, Leg, caz);
            }

            break;
        }
    }
}

public:void Traseaza_linii(Punct &p, bool &gasit)
{
    Tranzistor_npn n;
    int i, v[4], vv[4];

    for(auto it:Tranzistoare_npn)
    {
        n = it;
        if(verif_punct_apartine(p, n) == 1 && (n.if_conect[1] == 0 || n.if_conect[2] == 0 || n.if_conect[3] == 0 || n.if_conect[4] == 0))
        {
            Tranzistoare_npn.erase(Tranzistoare_npn.find(it));

            for(i = 1; i <= 3; i++)
            {
                if(n.if_conect[i] == 0) vv[i] = 0;
                else vv[i] = 1;
            }

            for(i = 1; i <= 3; i++) v[i] = distanta_dintre_2_puncte(p, n.conect[i]) + vv[i] * (LATIME_WINDOW + LUNGIME_WINDOW);
            sort(v + 1, v + 4);
            for(i = 1; i <= 3; i++) if(v[1] == distanta_dintre_2_puncte(p, n.conect[i])) p = n.conect[i], n.if_conect[i] = 1, i = 4;

            Tranzistoare_npn.insert(n);
            gasit = 1;
            break;
        }
    }
}

public:void Modificare_text(Punct p, bool &gasit)
{
    Tranzistor_npn g;

    for(auto it:Tranzistoare_npn)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1)
        {
            Tranzistoare_npn.erase(Tranzistoare_npn.find(it));
            if(g.orientare == 0) p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            else if(g.orientare == 1) p.x = g.centru.x, p.y = min(g.margine1.y, g.margine2.y) - 10;
            else if(g.orientare == 2) p.x = min(g.margine1.x, g.margine2.x) - 17, p.y = g.centru.y;
            else p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            g.text = scrie_text(p, g.text);

            Tranzistoare_npn.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Mod_sterge(Punct p, bool &gasit)
{
    int i;

    for(auto it:Tranzistoare_npn)
    {
        if(verif_punct_apartine(p, it) == 1)
        {
            for(i = 1; i <= 3; i++)
            {
                for(auto itt:Legaturi)
                {
                    if(verif_legatura_atinge(itt, it) == 1)
                    {
                        sterge_ultima_legatura(itt);
                        break;
                    }
                }
            }

            sterge_ultimul(it);
            gasit = 1;
            break;
        }
    }
}

};

class TRANZISTOR_PNP
{
    BUTON buton;

public:void setare(Tranzistor_pnp &tp, Punct centru, string text, bool show_text)
{
    Punct p1, p2;
    int lg_linie_orizontala = 20 + tp.dimensiune * 5, lg_linie_verticala = 20 + tp.dimensiune * 5, lg_linie_oblica_sus = 12 + tp.dimensiune * 4, lg_linie_oblica_jos = 12 + tp.dimensiune * 4, lg_linie_sus = 20 + tp.dimensiune * 4, lg_linie_jos = 20 + tp.dimensiune * 4, dist_de_la_centru = 20 + tp.dimensiune * 4, culoare = 15;
    int lg_linie_a = 5 + tp.dimensiune, lg_linie_b = 5 + tp.dimensiune, lg_linie_c = 5 + tp.dimensiune * 4;

    tp.centru = centru;
    tp.lg_linie_orizontala = lg_linie_orizontala, tp.lg_linie_verticala = lg_linie_verticala, tp.lg_linie_oblica_jos = lg_linie_oblica_jos, tp.lg_linie_oblica_sus = lg_linie_oblica_sus;
    tp.lg_linie_jos = lg_linie_jos, tp.lg_linie_sus = lg_linie_sus, tp.dist_de_la_centru = dist_de_la_centru, tp.culoare = culoare;
    tp.lg_linie_a = lg_linie_a, tp.lg_linie_b = lg_linie_b, tp.lg_linie_c = lg_linie_c;
    tp.text = text, tp.show_text = show_text;

    p1.x = tp.centru.x - tp.dist_de_la_centru - tp.lg_linie_orizontala / 2, p2.x = tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2;
    p1.y = p2.y = tp.centru.y;
    tp.linie_orizontala = setare_linie(p1, p2, tp.culoare);

    p1.x = p2.x = tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2;
    p1.y = tp.centru.y - tp.lg_linie_verticala / 2, p2.y = tp.centru.y + tp.lg_linie_verticala / 2;
    tp.linie_verticala = setare_linie(p1, p2, tp.culoare);

    p1.x = tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2, p2.x = tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2 + tp.lg_linie_oblica_sus;
    p1.y = tp.centru.y, p2.y = tp.centru.y - tp.lg_linie_oblica_sus;
    tp.linie_oblica_sus = setare_linie(p1, p2, tp.culoare);

    p1.x = tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2, p2.x = tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2 + tp.lg_linie_oblica_jos;
    p1.y = tp.centru.y, p2.y = tp.centru.y + tp.lg_linie_oblica_jos;
    tp.linie_oblica_jos = setare_linie(p1, p2, tp.culoare);

    p1.x = p2.x = tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2 + tp.lg_linie_oblica_sus;
    p1.y = tp.centru.y - tp.lg_linie_oblica_sus - tp.lg_linie_sus, p2.y = tp.centru.y - tp.lg_linie_oblica_sus;
    tp.linie_sus = setare_linie(p1, p2, tp.culoare);

    p1.x = p2.x = tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2 + tp.lg_linie_oblica_jos;
    p1.y = tp.centru.y + tp.lg_linie_oblica_jos, p2.y = tp.centru.y + tp.lg_linie_oblica_jos + tp.lg_linie_jos;
    tp.linie_jos = setare_linie(p1, p2, tp.culoare);

    p1.x = (tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2 + tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2 + tp.lg_linie_oblica_sus) / 2;
    p2.x = (tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2 + tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2 + tp.lg_linie_oblica_sus) / 2 + tp.lg_linie_a;
    p1.y = p2.y = (tp.centru.y + tp.centru.y - tp.lg_linie_oblica_jos) / 2;
    tp.linie_a = setare_linie(p1, p2, tp.culoare);

    p1.x = p2.x = (tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2 + tp.centru.x - tp.dist_de_la_centru + tp.lg_linie_orizontala / 2 + tp.lg_linie_oblica_sus) / 2;
    p1.y = (tp.centru.y + tp.centru.y - tp.lg_linie_oblica_jos) / 2 - tp.lg_linie_b;
    p2.y = (tp.centru.y + tp.centru.y - tp.lg_linie_oblica_jos) / 2;
    tp.linie_b = setare_linie(p1, p2, tp.culoare);

    tp.margine1.x = tp.linie_orizontala.p1.x, tp.margine1.y = tp.linie_sus.p1.y, tp.margine2.x = tp.centru.x + tp.dist_de_la_centru, tp.margine2.y = tp.linie_jos.p2.y;


    regleaza_linie_dreapta(tp.linie_orizontala), regleaza_linie_dreapta(tp.linie_verticala), regleaza_linie_dreapta(tp.linie_sus), regleaza_linie_dreapta(tp.linie_jos), regleaza_linie_dreapta(tp.linie_a), regleaza_linie_dreapta(tp.linie_b);
    tp.conect[1] = tp.linie_orizontala.p1, tp.conect[2] = tp.linie_sus.p1, tp.conect[3] = tp.linie_jos.p2;

    int i;
    for(i = 1; i <= tp.orientare; i++)
    {
        rotire_linie(tp.centru, tp.linie_orizontala), rotire_linie(tp.centru, tp.linie_verticala), rotire_linie(tp.centru, tp.linie_sus), rotire_linie(tp.centru, tp.linie_jos), rotire_linie(tp.centru, tp.linie_a), rotire_linie(tp.centru, tp.linie_b), rotire_linie(tp.centru, tp.linie_oblica_sus), rotire_linie(tp.centru, tp.linie_oblica_jos);
        rotire_punct(tp.centru, tp.margine1), rotire_punct(tp.centru, tp.margine2);
        rotire_punct(tp.centru, tp.conect[1]), rotire_punct(tp.centru, tp.conect[2]), rotire_punct(tp.centru, tp.conect[3]);

        regleaza_linie_dreapta(tp.linie_orizontala), regleaza_linie_dreapta(tp.linie_verticala), regleaza_linie_dreapta(tp.linie_sus), regleaza_linie_dreapta(tp.linie_jos), regleaza_linie_dreapta(tp.linie_a), regleaza_linie_dreapta(tp.linie_b);
    }
};

public:void deseneaza(Tranzistor_pnp g)
{
    if(g.culoare != 0)
    {
        deseneaza_linie_dreapta(g.linie_orizontala);
        deseneaza_linie_dreapta(g.linie_verticala);
        deseneaza_linie_diagonala(g.linie_oblica_sus);
        deseneaza_linie_diagonala(g.linie_oblica_jos);
        deseneaza_linie_dreapta(g.linie_sus);
        deseneaza_linie_dreapta(g.linie_jos);
        deseneaza_cerc_gol(g.centru, g.dist_de_la_centru, g.culoare);
        deseneaza_linie_dreapta(g.linie_a);
        deseneaza_linie_dreapta(g.linie_b);
        Tranzistoare_pnp.insert(g);

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0) p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            else if(g.orientare == 1) p.x = g.centru.x, p.y = min(g.margine1.y, g.margine2.y) - 10;
            else if(g.orientare == 2) p.x = min(g.margine1.x, g.margine2.x) - 17, p.y = g.centru.y;
            else p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;

            deseneaza_text(g.text, p);
        }
    }
}

public:void sterge_ultimul(Tranzistor_pnp g)
{
    if(Tranzistoare_pnp.find(g) != Tranzistoare_pnp.end())
    {
        sterge_ultima_linie_dreapta(g.linie_orizontala);
        sterge_ultima_linie_dreapta(g.linie_verticala);
        sterge_ultima_linie_diagonala(g.linie_oblica_sus);
        sterge_ultima_linie_diagonala(g.linie_oblica_jos);
        sterge_ultima_linie_dreapta(g.linie_sus);
        sterge_ultima_linie_dreapta(g.linie_jos);
        sterge_cerc_gol(g.centru, g.dist_de_la_centru);
        sterge_ultima_linie_dreapta(g.linie_a);
        sterge_ultima_linie_dreapta(g.linie_b);
        Tranzistoare_pnp.erase(Tranzistoare_pnp.find(g));

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0) p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            else if(g.orientare == 1) p.x = g.centru.x, p.y = min(g.margine1.y, g.margine2.y) - 10;
            else if(g.orientare == 2) p.x = min(g.margine1.x, g.margine2.x) - 17, p.y = g.centru.y;
            else p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;

            sterge_text(g.text, p);
        }
    }
}

public:void zoom_in(Tranzistor_pnp &n)
{
    if(n.dimensiune == DIMENSIUNE_MAX) afiseaza_eroare("Tranzistorul PNP are dimensiunea maxima!");
    else
    {
        n.dimensiune++;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void zoom_out(Tranzistor_pnp &n)
{
    if(n.dimensiune == DIMENSIUNE_MIN) afiseaza_eroare("Tranzistorul PNP are dimensiunea minima!");
    else
    {
        n.dimensiune--;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void rotire(Tranzistor_pnp &g)
{
    g.orientare = (g.orientare + 1) % 4;
    setare(g, g.centru, g.text, g.show_text);
}

public:bool verif_punct_apartine(Punct p, Tranzistor_pnp g)
{
    return p.x >= min(g.margine1.x, g.margine2.x) && p.x <= max(g.margine1.x, g.margine2.x) && p.y >= min(g.margine1.y, g.margine2.y) && p.y <= max(g.margine1.y, g.margine2.y);
}

public:bool verif_legatura_atinge(Legatura Leg, Tranzistor_pnp g)
{
    return (verif_punct_apartine(Leg.p1, g) || verif_punct_apartine(Leg.p2, g));
}

public:void setare_legaturi(Tranzistor_pnp g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    if(Leg[nr_de_legaturi].p1.x == g.conect[1].x && Leg[nr_de_legaturi].p1.y == g.conect[1].y) caz[nr_de_legaturi] = 1;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[2].x && Leg[nr_de_legaturi].p1.y == g.conect[2].y) caz[nr_de_legaturi] = 2;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[3].x && Leg[nr_de_legaturi].p1.y == g.conect[3].y) caz[nr_de_legaturi] = 3;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[1].x && Leg[nr_de_legaturi].p2.y == g.conect[1].y) caz[nr_de_legaturi] = 4;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[2].x && Leg[nr_de_legaturi].p2.y == g.conect[2].y) caz[nr_de_legaturi] = 5;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[3].x && Leg[nr_de_legaturi].p2.y == g.conect[3].y) caz[nr_de_legaturi] = 6;
}

public:void deseneaza_legaturi(Tranzistor_pnp g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    int i;

    for(i = 1; i <= nr_de_legaturi; i++)
    {
        if(caz[i] == 1) Leg[i].p1 = g.conect[1];
        else if(caz[i] == 2) Leg[i].p1 = g.conect[2];
        else if(caz[i] == 3) Leg[i].p1 = g.conect[3];
        else if(caz[i] == 4) Leg[i].p2 = g.conect[1];
        else if(caz[i] == 5) Leg[i].p2 = g.conect[2];
        else if(caz[i] == 6) Leg[i].p2 = g.conect[3];

        seteaza_linii_legatura(Leg[i]);
        deseneaza_legatura(Leg[i]);
    }
}


public:void Mod_punere(Buton &Punere_generator)
{
    Tranzistor_pnp g;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0)
    {
        sterge_ultimul(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
        getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

        setare(g, p1, "", 0);
        if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
    }

    buton.actioneaza_buton(Punere_generator);
}

public:void Mutare(Punct p1, bool &gasit)
{
    Tranzistor_pnp g;
    Legatura Leg[4];
    Punct p2 = p1;
    int i, nr_de_legaturi, caz[4];

    for(auto it:Tranzistoare_pnp)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            gasit = 1, nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 3) break;
                }

            while(ismouseclick(WM_LBUTTONUP) == 0)
            {
                sterge_ultimul(g);

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

                for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);

                setare(g, p1, g.text, g.show_text);
                if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1)
                {
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                }

                else
                {
                    setare(g, p2, g.text, g.show_text);
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                    string text = "Tranzistorul PNP nu poate fi scos din chenar!";
                    afiseaza_eroare(text);
                    break;
                }

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
            }

            sterge_ultimul(g);
            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);
            if(verif_se_suprapune(g.margine1, g.margine2) == 1)
            {
                setare(g, p2, g.text, g.show_text);
                string text = "Tranzistorul PNP se suprapune!";
                afiseaza_eroare(text);
            }
            deseneaza(g);
            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            clearmouseclick(WM_LBUTTONUP);
            break;
        }
    }
}

public:void Zoom(Punct p1, bool operatie, bool &gasit)
{
    Tranzistor_pnp g;
    Legatura Leg[4];
    int i, nr_de_legaturi, caz[4];

    for(auto it:Tranzistoare_pnp)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 3) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            if(operatie == 0) zoom_in(g);
            else if(operatie == 1) zoom_out(g);


            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Tranzistorul PNP iese din chenar!");
                else afiseaza_eroare("Tranzistorul PNP se suprapune cu o alta piesa!");

                if(operatie == 0) zoom_out(g);
                if(operatie == 1) zoom_in(g);
                deseneaza(g);
            }


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            gasit = 1;
            break;
        }
    }
}

public:void Rotire(Punct p1, bool &gasit)
{
    Tranzistor_pnp g, gg;
    Legatura Leg[4];
    int i, nr_de_legaturi, caz[4];

    for(auto it:Tranzistoare_pnp)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 3) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            gg = g;
            sterge_ultimul(g);
            rotire(g);

            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0)
            {
                deseneaza(g);
                deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
            }
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Tranzistorul PNP iese din chenar!");
                else afiseaza_eroare("Tranzistorul PNP se suprapune cu o alta piesa!");
                deseneaza(gg);
                deseneaza_legaturi(gg, nr_de_legaturi, Leg, caz);
            }

            break;
        }
    }
}

public:void Traseaza_linii(Punct &p, bool &gasit)
{
    Tranzistor_pnp n;
    int i, v[4], vv[4];

    for(auto it:Tranzistoare_pnp)
    {
        n = it;
        if(verif_punct_apartine(p, n) == 1 && (n.if_conect[1] == 0 || n.if_conect[2] == 0 || n.if_conect[3] == 0 || n.if_conect[4] == 0))
        {
            Tranzistoare_pnp.erase(Tranzistoare_pnp.find(it));

            for(i = 1; i <= 3; i++)
            {
                if(n.if_conect[i] == 0) vv[i] = 0;
                else vv[i] = 1;
            }

            for(i = 1; i <= 3; i++) v[i] = distanta_dintre_2_puncte(p, n.conect[i]) + vv[i] * (LATIME_WINDOW + LUNGIME_WINDOW);
            sort(v + 1, v + 4);
            for(i = 1; i <= 3; i++) if(v[1] == distanta_dintre_2_puncte(p, n.conect[i])) p = n.conect[i], n.if_conect[i] = 1, i = 4;

            Tranzistoare_pnp.insert(n);
            gasit = 1;
            break;
        }
    }
}

public:void Modificare_text(Punct p, bool &gasit)
{
    Tranzistor_pnp g;

    for(auto it:Tranzistoare_pnp)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1)
        {
            Tranzistoare_pnp.erase(Tranzistoare_pnp.find(it));
            if(g.orientare == 0) p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            else if(g.orientare == 1) p.x = g.centru.x, p.y = min(g.margine1.y, g.margine2.y) - 10;
            else if(g.orientare == 2) p.x = min(g.margine1.x, g.margine2.x) - 17, p.y = g.centru.y;
            else p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            g.text = scrie_text(p, g.text);

            Tranzistoare_pnp.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Mod_sterge(Punct p, bool &gasit)
{
    int i;

    for(auto it:Tranzistoare_pnp)
    {
        if(verif_punct_apartine(p, it) == 1)
        {
            for(i = 1; i <= 3; i++)
            {
                for(auto itt:Legaturi)
                {
                    if(verif_legatura_atinge(itt, it) == 1)
                    {
                        sterge_ultima_legatura(itt);
                        break;
                    }
                }
            }

            sterge_ultimul(it);
            gasit = 1;
            break;
        }
    }
}

};

class VOLTMETRU
{
    BUTON buton;

public:void setare(Voltmetru &v, Punct centru, string text, bool show_text)
{
    Punct p1, p2;
    int lg_linie_orizontala_st = 20 + v.dimensiune * 5, lg_linie_orizontala_dr = 20 + v.dimensiune * 5, dist_de_la_centru = 15 + v.dimensiune * 4, culoare = 15;
    int lg_linie_st = 10 + v.dimensiune * 4, lg_linie_dr = 10 + v.dimensiune * 4;

    v.centru = centru;
    v.lg_linie_orizontala_st = lg_linie_orizontala_st, v.lg_linie_orizontala_dr = lg_linie_orizontala_dr, v.dist_de_la_centru = dist_de_la_centru;
    v.culoare = culoare;
    v.text = text, v.show_text = show_text;

    p1.x = v.centru.x - dist_de_la_centru - lg_linie_orizontala_st, p2.x = v.centru.x - dist_de_la_centru;
    p1.y = p2.y = v.centru.y;
    v.linie_orizontala_st = setare_linie(p1, p2, v.culoare);

    p1.x = v.centru.x + dist_de_la_centru, p2.x = v.centru.x + dist_de_la_centru + lg_linie_orizontala_dr;
    p1.y = p2.y = v.centru.y;
    v.linie_orizontala_dr = setare_linie(p1, p2, v.culoare);

    p1.x = v.centru.x - lg_linie_st / 2, p2.x = v.centru.x;
    p1.y = v.centru.y - lg_linie_st / 2, p2.y = v.centru.y + lg_linie_st / 2;
    v.linie_st = setare_linie(p1, p2, v.culoare);

    p1.x = v.centru.x, p2.x = v.centru.x + lg_linie_dr / 2;
    p1.y = v.centru.y + lg_linie_dr / 2, p2.y = v.centru.y - lg_linie_dr / 2;
    v.linie_dr = setare_linie(p1, p2, v.culoare);

    v.margine1.x = v.linie_orizontala_st.p1.x, v.margine1.y = v.centru.y - dist_de_la_centru, v.margine2.x = v.linie_orizontala_dr.p2.x, v.margine2.y = v.centru.y + dist_de_la_centru;
    regleaza_linie_dreapta(v.linie_orizontala_st), regleaza_linie_dreapta(v.linie_orizontala_dr);
    v.conect[1] = v.linie_orizontala_st.p1, v.conect[2] = v.linie_orizontala_dr.p2;

    int i;
    for(i = 1; i <= v.orientare; i++)
    {
        rotire_linie(v.centru, v.linie_orizontala_st), rotire_linie(v.centru, v.linie_orizontala_dr);
        rotire_punct(v.centru, v.margine1), rotire_punct(v.centru, v.margine2);
        rotire_punct(v.centru, v.conect[1]), rotire_punct(v.centru, v.conect[2]);

        regleaza_linie_dreapta(v.linie_orizontala_st), regleaza_linie_dreapta(v.linie_orizontala_dr);
    }

};

public:void deseneaza(Voltmetru g)
{
    if (g.culoare != 0)
    {
        deseneaza_linie_dreapta(g.linie_orizontala_st);
        deseneaza_linie_dreapta(g.linie_orizontala_dr);
        deseneaza_linie_diagonala(g.linie_st);
        deseneaza_linie_diagonala(g.linie_dr);
        deseneaza_cerc_gol(g.centru, g.dist_de_la_centru, g.culoare);
        Voltmetre.insert(g);

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            deseneaza_text(g.text, p);
        }
    }
}

public:void sterge_ultimul(Voltmetru g)
{
    if(Voltmetre.find(g) != Voltmetre.end())
    {
        sterge_ultima_linie_dreapta(g.linie_orizontala_st);
        sterge_ultima_linie_dreapta(g.linie_orizontala_dr);
        sterge_ultima_linie_diagonala(g.linie_st);
        sterge_ultima_linie_diagonala(g.linie_dr);
        sterge_cerc_gol(g.centru, g.dist_de_la_centru);
        Voltmetre.erase(Voltmetre.find(g));

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            sterge_text(g.text, p);
        }
    }
}

public:void zoom_in(Voltmetru &n)
{
    if(n.dimensiune == DIMENSIUNE_MAX) afiseaza_eroare("Voltmetrul are dimensiunea maxima!");
    else
    {
        n.dimensiune++;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void zoom_out(Voltmetru &n)
{
    if(n.dimensiune == DIMENSIUNE_MIN) afiseaza_eroare("Voltmetrul are dimensiunea minima!");
    else
    {
        n.dimensiune--;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void rotire(Voltmetru &g)
{
    g.orientare = (g.orientare + 1) % 4;
    setare(g, g.centru, g.text, g.show_text);
}

public:bool verif_punct_apartine(Punct p, Voltmetru g)
{
    return p.x >= min(g.margine1.x, g.margine2.x) && p.x <= max(g.margine1.x, g.margine2.x) && p.y >= min(g.margine1.y, g.margine2.y) && p.y <= max(g.margine1.y, g.margine2.y);
}

public:bool verif_legatura_atinge(Legatura Leg, Voltmetru g)
{
    return (verif_punct_apartine(Leg.p1, g) || verif_punct_apartine(Leg.p2, g));
}

public:void setare_legaturi(Voltmetru g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    if(Leg[nr_de_legaturi].p1.x == g.conect[1].x && Leg[nr_de_legaturi].p1.y == g.conect[1].y) caz[nr_de_legaturi] = 1;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[2].x && Leg[nr_de_legaturi].p1.y == g.conect[2].y) caz[nr_de_legaturi] = 2;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[1].x && Leg[nr_de_legaturi].p2.y == g.conect[1].y) caz[nr_de_legaturi] = 3;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[2].x && Leg[nr_de_legaturi].p2.y == g.conect[2].y) caz[nr_de_legaturi] = 4;
}

public:void deseneaza_legaturi(Voltmetru g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    int i;

    for(i = 1; i <= nr_de_legaturi; i++)
    {
        if(caz[i] == 1) Leg[i].p1 = g.conect[1];
        else if(caz[i] == 2) Leg[i].p1 = g.conect[2];
        else if(caz[i] == 3) Leg[i].p2 = g.conect[1];
        else if(caz[i] == 4) Leg[i].p2 = g.conect[2];

        seteaza_linii_legatura(Leg[i]);
        deseneaza_legatura(Leg[i]);
    }
}


public:void Mod_punere(Buton &Punere_generator)
{
    Voltmetru g;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0)
    {
        sterge_ultimul(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
        getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

        setare(g, p1, "", 0);
        if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
    }

    buton.actioneaza_buton(Punere_generator);
};

public:void Mutare(Punct p1, bool &gasit)
{
    Voltmetru g;
    Legatura Leg[3];
    Punct p2 = p1;
    int i, nr_de_legaturi, caz[3];

    for(auto it:Voltmetre)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            gasit = 1, nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            while(ismouseclick(WM_LBUTTONUP) == 0)
            {
                sterge_ultimul(g);

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

                for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);

                setare(g, p1, g.text, g.show_text);
                if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1)
                {
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                }

                else
                {
                    setare(g, p2, g.text, g.show_text);
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                    string text = "Voltmetrul nu poate fi scos din chenar!";
                    afiseaza_eroare(text);
                    break;
                }

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
            }

            sterge_ultimul(g);
            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);
            if(verif_se_suprapune(g.margine1, g.margine2) == 1)
            {
                setare(g, p2, g.text, g.show_text);
                string text = "Voltmetrul se suprapune!";
                afiseaza_eroare(text);
            }
            deseneaza(g);
            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            clearmouseclick(WM_LBUTTONUP);
            break;
        }
    }
};

public:void Zoom(Punct p1, bool operatie, bool &gasit)
{
    Voltmetru g;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Voltmetre)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            if(operatie == 0) zoom_in(g);
            else if(operatie == 1) zoom_out(g);


            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Voltmetrul iese din chenar!");
                else afiseaza_eroare("Voltmetrul se suprapune cu o alta piesa!");

                if(operatie == 0) zoom_out(g);
                if(operatie == 1) zoom_in(g);
                deseneaza(g);
            }


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            gasit = 1;
            break;
        }
    }
}

public:void Rotire(Punct p1, bool &gasit)
{
    Voltmetru g, gg;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Voltmetre)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            gg = g;
            sterge_ultimul(g);
            rotire(g);

            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0)
            {
                deseneaza(g);
                deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
            }
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Voltmetrul iese din chenar!");
                else afiseaza_eroare("Voltmetrul se suprapune cu o alta piesa!");
                deseneaza(gg);
                deseneaza_legaturi(gg, nr_de_legaturi, Leg, caz);
            }

            break;
        }
    }
}

public:void Traseaza_linii(Punct &p, bool &gasit)
{
    Voltmetru g;

    for(auto it:Voltmetre)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1 && (g.if_conect[1] == 0 || g.if_conect[2] == 0))
        {
            Voltmetre.erase(Voltmetre.find(it));

            if(g.if_conect[1] == 0 && g.if_conect[2] == 1) p = g.conect[1], g.if_conect[1] = 1;
            else if(g.if_conect[1] == 1 && g.if_conect[2] == 0) p = g.conect[2], g.if_conect[2] = 1;
            else if(distanta_dintre_2_puncte(p, g.conect[1]) < distanta_dintre_2_puncte(p, g.conect[2])) p = g.conect[1], g.if_conect[1] = 1;
            else p = g.conect[2], g.if_conect[2] = 1;

            Voltmetre.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Modificare_text(Punct p, bool &gasit)
{
    Voltmetru g;

    for(auto it:Voltmetre)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1)
        {
            Voltmetre.erase(Voltmetre.find(it));
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            g.text = scrie_text(p, g.text);

            Voltmetre.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Mod_sterge(Punct p, bool &gasit)
{
    int i;

    for(auto it:Voltmetre)
    {
        if(verif_punct_apartine(p, it) == 1)
        {
            for(i = 1; i <= 2; i++)
            {
                for(auto itt:Legaturi)
                {
                    if(verif_legatura_atinge(itt, it) == 1)
                    {
                        sterge_ultima_legatura(itt);
                        break;
                    }
                }
            }

            sterge_ultimul(it);
            gasit = 1;
            break;
        }
    }
}

};

class POTENTIOMETRU
{
    BUTON buton;

public:void setare(Potentiometru &p, Punct centru, string text, bool show_text)
{
    Punct p1, p2;
    int lg_linie_orizontala_st = 20 + p.dimensiune * 4, lg_linie_orizontala_dr = 20 + p.dimensiune * 4, lg_linie_st = 5 + p.dimensiune * 4, lg_linie_dr = 5 + p.dimensiune * 4;
    int lg_linie_1 = 5 + p.dimensiune * 4, lg_linie_2 = 5 + p.dimensiune * 4, lg_linie_3 = 5 + p.dimensiune * 4, lg_linie_4 = 5 + p.dimensiune * 4, lg_linie_5 = 5 + p.dimensiune * 4;
    int dist_de_la_centru = 18 + p.dimensiune * 14, culoare = 15;

    p.centru = centru;
    p.lg_linie_orizontala_st = lg_linie_orizontala_st, p.lg_linie_orizontala_dr = lg_linie_orizontala_dr, p.lg_linie_st = lg_linie_st, p.lg_linie_dr = lg_linie_dr;
    p.lg_linie_1 = lg_linie_1, p.lg_linie_2 = lg_linie_2, p.lg_linie_3 = lg_linie_3, p.lg_linie_4 = lg_linie_4, p.lg_linie_5 = lg_linie_5, p.dist_de_la_centru = dist_de_la_centru, p.culoare = culoare;
    p.text = text, p.show_text = show_text;

    p1.x = p.centru.x - p.dist_de_la_centru - p.lg_linie_orizontala_st, p2.x = p.centru.x - p.dist_de_la_centru;
    p1.y = p2.y = p.centru.y;
    p.linie_orizontala_st = setare_linie(p1, p2, p.culoare);

    p1.x = p.centru.x + p.dist_de_la_centru, p2.x = p.centru.x + p.dist_de_la_centru + p.lg_linie_orizontala_dr;
    p1.y = p2.y = p.centru.y;
    p.linie_orizontala_dr = setare_linie(p1, p2, p.culoare);

    p1.x = p.centru.x - p.dist_de_la_centru, p2.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st;
    p1.y = p.centru.y, p2.y = p.centru.y - p.dist_de_la_centru / 2;
    p.linie_st = setare_linie(p1, p2, p.culoare);

    p1.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st, p2.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st + p.lg_linie_1;
    p1.y = p.centru.y - p.dist_de_la_centru / 2, p2.y = p.centru.y + p.dist_de_la_centru / 2;
    p.linie_1 = setare_linie(p1, p2, p.culoare);

    p1.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st + p.lg_linie_1, p2.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st + p.lg_linie_1 + p.lg_linie_2;
    p1.y = p.centru.y + p.dist_de_la_centru / 2, p2.y = p.centru.y - p.dist_de_la_centru / 2;
    p.linie_2 = setare_linie(p1, p2, p.culoare);

    p1.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st + p.lg_linie_1 + p.lg_linie_2, p2.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st + p.lg_linie_1 + p.lg_linie_2 + p.lg_linie_3;
    p1.y = p.centru.y - p.dist_de_la_centru / 2, p2.y = p.centru.y + p.dist_de_la_centru / 2;
    p.linie_3 = setare_linie(p1, p2, p.culoare);

    p1.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st + p.lg_linie_1 + p.lg_linie_2 + p.lg_linie_3, p2.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st + p.lg_linie_1 + p.lg_linie_2 + p.lg_linie_3 + p.lg_linie_4;
    p1.y = p.centru.y + p.dist_de_la_centru / 2, p2.y = p.centru.y - p.dist_de_la_centru / 2;
    p.linie_4 = setare_linie(p1, p2, p.culoare);

    p1.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st + p.lg_linie_1 + p.lg_linie_2 + p.lg_linie_3 + p.lg_linie_4, p2.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st + p.lg_linie_1 + p.lg_linie_2 + p.lg_linie_3 + p.lg_linie_4 + p.lg_linie_5;
    p1.y = p.centru.y - p.dist_de_la_centru / 2, p2.y = p.centru.y + p.dist_de_la_centru / 2;
    p.linie_5 = setare_linie(p1, p2, p.culoare);

    p1.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st + p.lg_linie_1 + p.lg_linie_2 + p.lg_linie_3 + p.lg_linie_4 + p.lg_linie_5, p2.x = p.centru.x - p.dist_de_la_centru + p.lg_linie_st + p.lg_linie_1 + p.lg_linie_2 + p.lg_linie_3 + p.lg_linie_4 + p.lg_linie_5 + p.lg_linie_dr;
    p1.y = p.centru.y + p.dist_de_la_centru / 2, p2.y = p.centru.y;
    p.linie_dr = setare_linie(p1, p2, p.culoare);

    p.margine1.x = p.linie_orizontala_st.p1.x, p.margine1.y = p.linie_1.p1.y, p.margine2.x = p.linie_orizontala_dr.p2.x, p.margine2.y = p.linie_2.p1.y;

    regleaza_linie_dreapta(p.linie_orizontala_st), regleaza_linie_dreapta(p.linie_orizontala_dr);
    p.conect[1] = p.linie_orizontala_st.p1, p.conect[2] = p.linie_orizontala_dr.p2;

    int i;
    for(i = 1; i <= p.orientare; i++)
    {
        rotire_linie(p.centru, p.linie_orizontala_st), rotire_linie(p.centru, p.linie_orizontala_dr), rotire_linie(p.centru, p.linie_st), rotire_linie(p.centru, p.linie_1);
        rotire_linie(p.centru, p.linie_2), rotire_linie(p.centru, p.linie_3), rotire_linie(p.centru, p.linie_4), rotire_linie(p.centru, p.linie_5);
        rotire_linie(p.centru, p.linie_dr);
        rotire_punct(p.centru, p.margine1), rotire_punct(p.centru, p.margine2);
        rotire_punct(p.centru, p.conect[1]), rotire_punct(p.centru, p.conect[2]);

        regleaza_linie_dreapta(p.linie_orizontala_st), regleaza_linie_dreapta(p.linie_orizontala_dr);
    }
}

public:void deseneaza(Potentiometru g)
{
    if(g.culoare != 0)
    {
        deseneaza_linie_dreapta(g.linie_orizontala_st);
        deseneaza_linie_dreapta(g.linie_orizontala_dr);
        deseneaza_linie_diagonala(g.linie_1);
        deseneaza_linie_diagonala(g.linie_2);
        deseneaza_linie_diagonala(g.linie_3);
        deseneaza_linie_diagonala(g.linie_4);
        deseneaza_linie_diagonala(g.linie_5);
        deseneaza_linie_diagonala(g.linie_dr);
        deseneaza_linie_diagonala(g.linie_st);
        Potentiometre.insert(g);

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            deseneaza_text(g.text, p);
        }
    }
}

public:void sterge_ultimul(Potentiometru g)
{
    if(Potentiometre.find(g) != Potentiometre.end())
    {
        sterge_ultima_linie_dreapta(g.linie_orizontala_st);
        sterge_ultima_linie_dreapta(g.linie_orizontala_dr);
        sterge_ultima_linie_diagonala(g.linie_1);
        sterge_ultima_linie_diagonala(g.linie_2);
        sterge_ultima_linie_diagonala(g.linie_3);
        sterge_ultima_linie_diagonala(g.linie_4);
        sterge_ultima_linie_diagonala(g.linie_5);
        sterge_ultima_linie_diagonala(g.linie_dr);
        sterge_ultima_linie_diagonala(g.linie_st);
        Potentiometre.erase(Potentiometre.find(g));

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            sterge_text(g.text, p);
        }
    }
}

public:void zoom_in(Potentiometru &n)
{
    if(n.dimensiune == DIMENSIUNE_MAX) afiseaza_eroare("Potentiometrul are dimensiunea maxima!");
    else
    {
        n.dimensiune++;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void zoom_out(Potentiometru &n)
{
    if(n.dimensiune == DIMENSIUNE_MIN) afiseaza_eroare("Potentiometrul are dimensiunea minima!");
    else
    {
        n.dimensiune--;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void rotire(Potentiometru &g)
{
    g.orientare = (g.orientare + 1) % 4;
    setare(g, g.centru, g.text, g.show_text);
}

public:bool verif_punct_apartine(Punct p, Potentiometru g)
{
    return p.x >= min(g.margine1.x, g.margine2.x) && p.x <= max(g.margine1.x, g.margine2.x) && p.y >= min(g.margine1.y, g.margine2.y) && p.y <= max(g.margine1.y, g.margine2.y);
}

public:bool verif_legatura_atinge(Legatura Leg, Potentiometru g)
{
    return (verif_punct_apartine(Leg.p1, g) || verif_punct_apartine(Leg.p2, g));
}

public:void setare_legaturi(Potentiometru g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    if(Leg[nr_de_legaturi].p1.x == g.conect[1].x && Leg[nr_de_legaturi].p1.y == g.conect[1].y) caz[nr_de_legaturi] = 1;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[2].x && Leg[nr_de_legaturi].p1.y == g.conect[2].y) caz[nr_de_legaturi] = 2;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[1].x && Leg[nr_de_legaturi].p2.y == g.conect[1].y) caz[nr_de_legaturi] = 3;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[2].x && Leg[nr_de_legaturi].p2.y == g.conect[2].y) caz[nr_de_legaturi] = 4;
}

public:void deseneaza_legaturi(Potentiometru g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    int i;

    for(i = 1; i <= nr_de_legaturi; i++)
    {
        if(caz[i] == 1) Leg[i].p1 = g.conect[1];
        else if(caz[i] == 2) Leg[i].p1 = g.conect[2];
        else if(caz[i] == 3) Leg[i].p2 = g.conect[1];
        else if(caz[i] == 4) Leg[i].p2 = g.conect[2];

        seteaza_linii_legatura(Leg[i]);
        deseneaza_legatura(Leg[i]);
    }
}


public:void Mod_punere(Buton &Punere_generator)
{
    Potentiometru g;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0)
    {
        sterge_ultimul(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
        getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

        setare(g, p1, "", 0);
        if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
    }

    buton.actioneaza_buton(Punere_generator);
};

public:void Mutare(Punct p1, bool &gasit)
{
    Potentiometru g;
    Legatura Leg[3];
    Punct p2 = p1;
    int i, nr_de_legaturi, caz[3];

    for(auto it:Potentiometre)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            gasit = 1, nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            while(ismouseclick(WM_LBUTTONUP) == 0)
            {
                sterge_ultimul(g);

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

                for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);

                setare(g, p1, g.text, g.show_text);
                if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1)
                {
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                }

                else
                {
                    setare(g, p2, g.text, g.show_text);
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                    string text = "Potentiometrul nu poate fi scos din chenar!";
                    afiseaza_eroare(text);
                    break;
                }

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
            }

            sterge_ultimul(g);
            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);
            if(verif_se_suprapune(g.margine1, g.margine2) == 1)
            {
                setare(g, p2, g.text, g.show_text);
                string text = "Potentiometrul se suprapune!";
                afiseaza_eroare(text);
            }
            deseneaza(g);
            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            clearmouseclick(WM_LBUTTONUP);
            break;
        }
    }
};

public:void Zoom(Punct p1, bool operatie, bool &gasit)
{
    Potentiometru g;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Potentiometre)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            if(operatie == 0) zoom_in(g);
            else if(operatie == 1) zoom_out(g);


            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Potentiometrul iese din chenar!");
                else afiseaza_eroare("Potentiometrul se suprapune cu o alta piesa!");

                if(operatie == 0) zoom_out(g);
                if(operatie == 1) zoom_in(g);
                deseneaza(g);
            }


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            gasit = 1;
            break;
        }
    }
}

public:void Rotire(Punct p1, bool &gasit)
{
    Potentiometru g, gg;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Potentiometre)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            gg = g;
            sterge_ultimul(g);
            rotire(g);

            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0)
            {
                deseneaza(g);
                deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
            }
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Potentiometrul iese din chenar!");
                else afiseaza_eroare("Potentiometrul se suprapune cu o alta piesa!");
                deseneaza(gg);
                deseneaza_legaturi(gg, nr_de_legaturi, Leg, caz);
            }

            break;
        }
    }
}

public:void Traseaza_linii(Punct &p, bool &gasit)
{
    Potentiometru g;

    for(auto it:Potentiometre)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1 && (g.if_conect[1] == 0 || g.if_conect[2] == 0))
        {
            Potentiometre.erase(Potentiometre.find(it));

            if(g.if_conect[1] == 0 && g.if_conect[2] == 1) p = g.conect[1], g.if_conect[1] = 1;
            else if(g.if_conect[1] == 1 && g.if_conect[2] == 0) p = g.conect[2], g.if_conect[2] = 1;
            else if(distanta_dintre_2_puncte(p, g.conect[1]) < distanta_dintre_2_puncte(p, g.conect[2])) p = g.conect[1], g.if_conect[1] = 1;
            else p = g.conect[2], g.if_conect[2] = 1;

            Potentiometre.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Modificare_text(Punct p, bool &gasit)
{
    Potentiometru g;

    for(auto it:Potentiometre)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1)
        {
            Potentiometre.erase(Potentiometre.find(it));
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            g.text = scrie_text(p, g.text);

            Potentiometre.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Mod_sterge(Punct p, bool &gasit)
{
    int i;

    for(auto it:Potentiometre)
    {
        if(verif_punct_apartine(p, it) == 1)
        {
            for(i = 1; i <= 2; i++)
            {
                for(auto itt:Legaturi)
                {
                    if(verif_legatura_atinge(itt, it) == 1)
                    {
                        sterge_ultima_legatura(itt);
                        break;
                    }
                }
            }

            sterge_ultimul(it);
            gasit = 1;
            break;
        }
    }
}

};

class BEC
{
    BUTON buton;

public:void setare(Bec &b, Punct centru, string text, bool show_text)
{
    Punct p1, p2;
    int lg_linie_orizontala_st = 20 + b.dimensiune * 5, lg_linie_orizontala_dr = 20 + b.dimensiune * 5, dist_de_la_centru = 15 + b.dimensiune * 4, culoare = 15;
    int lg_linie_st = 20 + b.dimensiune * 5, lg_linie_dr = 20 + b.dimensiune * 5;

    b.centru = centru;
    b.lg_linie_orizontala_st = lg_linie_orizontala_st, b.lg_linie_orizontala_dr = lg_linie_orizontala_dr, b.lg_linie_st = lg_linie_st, b.lg_linie_dr = lg_linie_dr, b.dist_de_la_centru = dist_de_la_centru;
    b.culoare = culoare;
    b.text = text, b.show_text = show_text;

    p1.x = b.centru.x - b.dist_de_la_centru - lg_linie_orizontala_st, p2.x = b.centru.x - b.dist_de_la_centru;
    p1.y = p2.y = b.centru.y;
    b.linie_orizontala_st = setare_linie(p1, p2, b.culoare);

    p1.x = b.centru.x + b.dist_de_la_centru, p2.x = b.centru.x + b.dist_de_la_centru + b.lg_linie_orizontala_dr;
    p1.y = p2.y = b.centru.y;
    b.linie_orizontala_dr = setare_linie(p1, p2, b.culoare);

    p1.x = b.centru.x - b.lg_linie_st / 2, p2.x = b.centru.x + b.lg_linie_st / 2;
    p1.y = b.centru.y - b.lg_linie_st / 2, p2.y = b.centru.y + b.lg_linie_st / 2;
    b.linie_st = setare_linie(p1, p2, b.culoare);

    p1.x = b.centru.x - b.lg_linie_dr / 2, p2.x = b.centru.x + b.lg_linie_dr / 2;
    p1.y = b.centru.y + b.lg_linie_dr / 2, p2.y = b.centru.y - b.lg_linie_dr / 2;
    b.linie_dr = setare_linie(p1, p2, b.culoare);

    b.margine1.x = b.linie_orizontala_st.p1.x, b.margine1.y = b.centru.y - b.lg_linie_st, b.margine2.x = b.linie_orizontala_dr.p2.x, b.margine2.y = b.centru.y + b.lg_linie_st;
    regleaza_linie_dreapta(b.linie_orizontala_st), regleaza_linie_dreapta(b.linie_orizontala_dr);
    b.conect[1] = b.linie_orizontala_st.p1, b.conect[2] = b.linie_orizontala_dr.p2;

    int i;
    for(i = 1; i <= b.orientare; i++)
    {
        rotire_linie(b.centru, b.linie_orizontala_st), rotire_linie(b.centru, b.linie_orizontala_dr);
        rotire_punct(b.centru, b.margine1), rotire_punct(b.centru, b.margine2);
        rotire_punct(b.centru, b.conect[1]), rotire_punct(b.centru, b.conect[2]);

        regleaza_linie_dreapta(b.linie_orizontala_st), regleaza_linie_dreapta(b.linie_orizontala_dr);
    }

};

public:void deseneaza(Bec g)
{
    if (g.culoare != 0)
    {
        deseneaza_linie_dreapta(g.linie_orizontala_st);
        deseneaza_linie_dreapta(g.linie_orizontala_dr);
        deseneaza_linie_diagonala(g.linie_st);
        deseneaza_linie_diagonala(g.linie_dr);
        deseneaza_cerc_gol(g.centru, g.dist_de_la_centru, g.culoare);
        Becuri.insert(g);

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            deseneaza_text(g.text, p);
        }
    }
}

public:void sterge_ultimul(Bec g)
{
    if(Becuri.find(g) != Becuri.end())
    {
        sterge_ultima_linie_dreapta(g.linie_orizontala_st);
        sterge_ultima_linie_dreapta(g.linie_orizontala_dr);
        sterge_ultima_linie_diagonala(g.linie_st);
        sterge_ultima_linie_diagonala(g.linie_dr);
        sterge_cerc_gol(g.centru, g.dist_de_la_centru);
        Becuri.erase(Becuri.find(g));

        Punct p;
        if(g.show_text == 1)
        {
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;

            sterge_text(g.text, p);
        }
    }
}

public:void zoom_in(Bec &n)
{
    if(n.dimensiune == DIMENSIUNE_MAX) afiseaza_eroare("Becul are dimensiunea maxima!");
    else
    {
        n.dimensiune++;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void zoom_out(Bec &n)
{
    if(n.dimensiune == DIMENSIUNE_MIN) afiseaza_eroare("Becul are dimensiunea minima!");
    else
    {
        n.dimensiune--;
        setare(n, n.centru, n.text, n.show_text);
    }
}

public:void rotire(Bec &g)
{
    g.orientare = (g.orientare + 1) % 4;
    setare(g, g.centru, g.text, g.show_text);
}

public:bool verif_punct_apartine(Punct p, Bec g)
{
    return p.x >= min(g.margine1.x, g.margine2.x) && p.x <= max(g.margine1.x, g.margine2.x) && p.y >= min(g.margine1.y, g.margine2.y) && p.y <= max(g.margine1.y, g.margine2.y);
}

public:bool verif_legatura_atinge(Legatura Leg, Bec g)
{
    return (verif_punct_apartine(Leg.p1, g) || verif_punct_apartine(Leg.p2, g));
}

public:void setare_legaturi(Bec g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    if(Leg[nr_de_legaturi].p1.x == g.conect[1].x && Leg[nr_de_legaturi].p1.y == g.conect[1].y) caz[nr_de_legaturi] = 1;
    else if(Leg[nr_de_legaturi].p1.x == g.conect[2].x && Leg[nr_de_legaturi].p1.y == g.conect[2].y) caz[nr_de_legaturi] = 2;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[1].x && Leg[nr_de_legaturi].p2.y == g.conect[1].y) caz[nr_de_legaturi] = 3;
    else if(Leg[nr_de_legaturi].p2.x == g.conect[2].x && Leg[nr_de_legaturi].p2.y == g.conect[2].y) caz[nr_de_legaturi] = 4;
}

public:void deseneaza_legaturi(Bec g, int nr_de_legaturi, Legatura Leg[], int caz[])
{
    int i;

    for(i = 1; i <= nr_de_legaturi; i++)
    {
        if(caz[i] == 1) Leg[i].p1 = g.conect[1];
        else if(caz[i] == 2) Leg[i].p1 = g.conect[2];
        else if(caz[i] == 3) Leg[i].p2 = g.conect[1];
        else if(caz[i] == 4) Leg[i].p2 = g.conect[2];

        seteaza_linii_legatura(Leg[i]);
        deseneaza_legatura(Leg[i]);
    }
}


public:void Mod_punere(Buton &Punere_generator)
{
    Bec g;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0)
    {
        sterge_ultimul(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
        getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

        setare(g, p1, "", 0);
        if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);

        while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
    }

    buton.actioneaza_buton(Punere_generator);
};

public:void Mutare(Punct p1, bool &gasit)
{
    Bec g;
    Legatura Leg[3];
    Punct p2 = p1;
    int i, nr_de_legaturi, caz[3];

    for(auto it:Becuri)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            gasit = 1, nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            while(ismouseclick(WM_LBUTTONUP) == 0)
            {
                sterge_ultimul(g);

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                getmouseclick(WM_MOUSEMOVE, p1.x, p1.y);

                for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);

                setare(g, p1, g.text, g.show_text);
                if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1)
                {
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                }

                else
                {
                    setare(g, p2, g.text, g.show_text);
                    deseneaza(g);
                    deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
                    string text = "Becul nu poate fi scos din chenar!";
                    afiseaza_eroare(text);
                    break;
                }

                while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
            }

            sterge_ultimul(g);
            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);
            if(verif_se_suprapune(g.margine1, g.margine2) == 1)
            {
                setare(g, p2, g.text, g.show_text);
                string text = "Becul se suprapune!";
                afiseaza_eroare(text);
            }
            deseneaza(g);
            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            clearmouseclick(WM_LBUTTONUP);
            break;
        }
    }
};

public:void Zoom(Punct p1, bool operatie, bool &gasit)
{
    Bec g;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Becuri)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            sterge_ultimul(g);
            if(operatie == 0) zoom_in(g);
            else if(operatie == 1) zoom_out(g);


            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0) deseneaza(g);
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Becul iese din chenar!");
                else afiseaza_eroare("Becul se suprapune cu o alta piesa!");

                if(operatie == 0) zoom_out(g);
                if(operatie == 1) zoom_in(g);
                deseneaza(g);
            }


            deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);

            gasit = 1;
            break;
        }
    }
}

public:void Rotire(Punct p1, bool &gasit)
{
    Bec g, gg;
    Legatura Leg[3];
    int i, nr_de_legaturi, caz[3];

    for(auto it:Becuri)
    {
        g = it;
        if(verif_punct_apartine(p1, g) == 1)
        {
            nr_de_legaturi = 0;
            for(auto itt:Legaturi)
                if(verif_legatura_atinge(itt, g) == 1)
                {
                    Leg[++nr_de_legaturi] = itt;
                    setare_legaturi(g, nr_de_legaturi, Leg, caz);
                    if(nr_de_legaturi == 2) break;
                }

            for(i = 1; i <= nr_de_legaturi; i++) sterge_ultima_legatura(Leg[i]);


            gg = g;
            sterge_ultimul(g);
            rotire(g);

            if(verif_punct_apartine_chenar(g.margine1) == 1 && verif_punct_apartine_chenar(g.margine2) == 1 && verif_se_suprapune(g.margine1, g.margine2) == 0)
            {
                deseneaza(g);
                deseneaza_legaturi(g, nr_de_legaturi, Leg, caz);
            }
            else
            {
                if(verif_punct_apartine_chenar(g.margine1) == 0 || verif_punct_apartine_chenar(g.margine2) == 0) afiseaza_eroare("Becul iese din chenar!");
                else afiseaza_eroare("Becul se suprapune cu o alta piesa!");
                deseneaza(gg);
                deseneaza_legaturi(gg, nr_de_legaturi, Leg, caz);
            }

            break;
        }
    }
}

public:void Traseaza_linii(Punct &p, bool &gasit)
{
    Bec g;

    for(auto it:Becuri)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1 && (g.if_conect[1] == 0 || g.if_conect[2] == 0))
        {
            Becuri.erase(Becuri.find(it));

            if(g.if_conect[1] == 0 && g.if_conect[2] == 1) p = g.conect[1], g.if_conect[1] = 1;
            else if(g.if_conect[1] == 1 && g.if_conect[2] == 0) p = g.conect[2], g.if_conect[2] = 1;
            else if(distanta_dintre_2_puncte(p, g.conect[1]) < distanta_dintre_2_puncte(p, g.conect[2])) p = g.conect[1], g.if_conect[1] = 1;
            else p = g.conect[2], g.if_conect[2] = 1;

            Becuri.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Modificare_text(Punct p, bool &gasit)
{
    Bec g;

    for(auto it:Becuri)
    {
        g = it;
        if(verif_punct_apartine(p, g) == 1)
        {
            Becuri.erase(Becuri.find(it));
            if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
            else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
            g.text = scrie_text(p, g.text);

            Becuri.insert(g);
            gasit = 1;
            break;
        }
    }
}

public:void Mod_sterge(Punct p, bool &gasit)
{
    int i;

    for(auto it:Becuri)
    {
        if(verif_punct_apartine(p, it) == 1)
        {
            for(i = 1; i <= 2; i++)
            {
                for(auto itt:Legaturi)
                {
                    if(verif_legatura_atinge(itt, it) == 1)
                    {
                        sterge_ultima_legatura(itt);
                        break;
                    }
                }
            }

            sterge_ultimul(it);
            gasit = 1;
            break;
        }
    }
}

};


/// Clasa finala
class Rulare_finala
{
    BUTON buton;
    NOD nod;
    GENERATOR generator;
    REZISTOR rezistor;
    CONDENSATOR condensator;
    AMPLIFICATOR_OPERATIONAL amplificator_operational;
    DIODA_TUNNEL dioda_tunnel;
    DIODA_ZENER dioda_zener;
    TRANZISTOR_NPN tranzistor_npn;
    TRANZISTOR_PNP tranzistor_pnp;
    VOLTMETRU voltmetru;
    POTENTIOMETRU potentiometru;
    BEC bec;

public:void Mod_mutare(Buton &Mutare)
{
    Punct p;
    bool gasit;

    while(Mutare.stare == 1)
    {
        while(ismouseclick(WM_LBUTTONUP) == 0) delay(50);
        getmouseclick(WM_LBUTTONUP, p.x, p.y), clearmouseclick(WM_LBUTTONUP);

        if(buton.verif_punct_apartine_buton(p, Mutare) == 1) buton.actioneaza_buton(Mutare);
        else
        {
            gasit = 0;
            nod.Mutare(p, gasit);
            if(gasit == 0) generator.Mutare(p, gasit);
            if(gasit == 0) rezistor.Mutare(p, gasit);
            if(gasit == 0) condensator.Mutare(p, gasit);

            if(gasit == 0) amplificator_operational.Mutare(p, gasit);
            if(gasit == 0) dioda_tunnel.Mutare(p, gasit);
            if(gasit == 0) dioda_zener.Mutare(p, gasit);
            if(gasit == 0) tranzistor_npn.Mutare(p, gasit);

            if(gasit == 0) tranzistor_pnp.Mutare(p, gasit);
            if(gasit == 0) voltmetru.Mutare(p, gasit);
            if(gasit == 0) potentiometru.Mutare(p, gasit);
            if(gasit == 0) bec.Mutare(p, gasit);
        }
    }
}

public:void Mod_zoom(Buton &Zoom)
{
    /// operatie = 0 -> zoom in
    /// operatie = 1 -> zoom out

    Punct p1;
    bool gasit, operatie;

    while(Zoom.stare == 1)
    {
        while(ismouseclick(WM_LBUTTONUP) == 0 && ismouseclick(WM_RBUTTONUP) == 0) delay(50);
        if(ismouseclick(WM_LBUTTONUP) != 0) getmouseclick(WM_LBUTTONUP, p1.x, p1.y), clearmouseclick(WM_LBUTTONUP), operatie = 0;
        else getmouseclick(WM_RBUTTONUP, p1.x, p1.y), clearmouseclick(WM_RBUTTONUP), operatie = 1;

        if(operatie == 0 && buton.verif_punct_apartine_buton(p1, Zoom) == 1) buton.actioneaza_buton(Zoom);
        else
        {
            gasit = 0;
            nod.Zoom(p1, operatie, gasit);
            if(gasit == 0) generator.Zoom(p1, operatie, gasit);
            if(gasit == 0) rezistor.Zoom(p1, operatie, gasit);
            if(gasit == 0) condensator.Zoom(p1, operatie, gasit);

            if(gasit == 0) amplificator_operational.Zoom(p1, operatie, gasit);
            if(gasit == 0) dioda_tunnel.Zoom(p1, operatie, gasit);
            if(gasit == 0) dioda_zener.Zoom(p1, operatie, gasit);
            if(gasit == 0) tranzistor_npn.Zoom(p1, operatie, gasit);

            if(gasit == 0) tranzistor_pnp.Zoom(p1, operatie, gasit);
            if(gasit == 0) voltmetru.Zoom(p1, operatie, gasit);
            if(gasit == 0) potentiometru.Zoom(p1, operatie, gasit);
            if(gasit == 0) bec.Zoom(p1, operatie, gasit);
        }
    }
}

public:void Mod_rotire(Buton &Rotire)
{
    Punct p1;
    bool gasit;

    while(Rotire.stare == 1)
    {
        while(ismouseclick(WM_LBUTTONUP) == 0) delay(50);
        getmouseclick(WM_LBUTTONUP, p1.x, p1.y), clearmouseclick(WM_LBUTTONUP);

        if(buton.verif_punct_apartine_buton(p1, Rotire) == 1) buton.actioneaza_buton(Rotire);
        else
        {
            gasit = 0;
            nod.Rotire(p1, gasit);
            if(gasit == 0) generator.Rotire(p1, gasit);
            if(gasit == 0) rezistor.Rotire(p1, gasit);
            if(gasit == 0) condensator.Rotire(p1, gasit);

            if(gasit == 0) amplificator_operational.Rotire(p1, gasit);
            if(gasit == 0) dioda_tunnel.Rotire(p1, gasit);
            if(gasit == 0) dioda_zener.Rotire(p1, gasit);
            if(gasit == 0) tranzistor_npn.Rotire(p1, gasit);

            if(gasit == 0) tranzistor_pnp.Rotire(p1, gasit);
            if(gasit == 0) voltmetru.Rotire(p1, gasit);
            if(gasit == 0) potentiometru.Rotire(p1, gasit);
            if(gasit == 0) bec.Rotire(p1, gasit);
        }
    }
}

public:void Mod_traseaza_linii(Buton &Traseaza_linii)
{
    Nod n;
    Generator g;
    Legatura Leg;
    Punct p1, p2, p3;
    int culoare;
    bool ok, gasit;

    /// p1 -> Punctul initial
    /// p2 -> Punctul final
    /// p3 -> Punctul intermediar

    while(Traseaza_linii.stare == 1)
    {
        ok = 0;
        while(ok == 0)
        {
            while(ismouseclick(WM_LBUTTONUP) == 0) delay(50);
            getmouseclick(WM_LBUTTONUP, p1.x, p1.y), clearmouseclick(WM_LBUTTONUP);

            if(buton.verif_punct_apartine_buton(p1, Traseaza_linii) == 1)
            {
                buton.actioneaza_buton(Traseaza_linii);
                break;
            }
            else
            {
                nod.Traseaza_linii(p1, ok);
                if(ok == 0) generator.Traseaza_linii(p1, ok);
                if(ok == 0) rezistor.Traseaza_linii(p1, ok);
                if(ok == 0) condensator.Traseaza_linii(p1, ok);

                if(ok == 0) amplificator_operational.Traseaza_linii(p1, ok);
                if(ok == 0) dioda_tunnel.Traseaza_linii(p1, ok);
                if(ok == 0) dioda_zener.Traseaza_linii(p1, ok);
                if(ok == 0) tranzistor_npn.Traseaza_linii(p1, ok);

                if(ok == 0) tranzistor_pnp.Traseaza_linii(p1, ok);
                if(ok == 0) voltmetru.Traseaza_linii(p1, ok);
                if(ok == 0) potentiometru.Traseaza_linii(p1, ok);
                if(ok == 0) bec.Traseaza_linii(p1, ok);
            }
        }

        if(ok == 1)
        {
            culoare = 14;
            p2 = p3 = p1;
            Leg.L1 = setare_linie(p1, p3, 0), Leg.L2 = setare_linie(p3, p2, 0);
            while(1)
            {
                while(ismouseclick(WM_LBUTTONUP) == 0)
                {
                    getmouseclick(WM_MOUSEMOVE, p2.x, p2.y);

                    if(abs(p1.y - p2.y) < abs(p1.x - p2.x)) p3 = {p1.x, p2.y};
                    else p3 = {p2.x, p1.y};

                    sterge_ultima_legatura(Leg);
                    Leg.L1 = setare_linie(p1, p3, culoare), Leg.L2 = setare_linie(p3, p2, culoare), Leg.p1 = p1, Leg.p2 = p2;
                    deseneaza_legatura(Leg);

                    clearmouseclick(WM_MOUSEMOVE);
                    while(ismouseclick(WM_MOUSEMOVE) == 0) delay(50);
                }

                getmouseclick(WM_LBUTTONUP, p2.x, p2.y), clearmouseclick(WM_LBUTTONUP);


                gasit = 0;
                nod.Traseaza_linii(p2, gasit);
                if(gasit == 0) generator.Traseaza_linii(p2, gasit);
                if(gasit == 0) rezistor.Traseaza_linii(p2, gasit);
                if(gasit == 0) condensator.Traseaza_linii(p2, gasit);

                if(gasit == 0) amplificator_operational.Traseaza_linii(p2, gasit);
                if(gasit == 0) dioda_tunnel.Traseaza_linii(p2, gasit);
                if(gasit == 0) dioda_zener.Traseaza_linii(p2, gasit);
                if(gasit == 0) tranzistor_npn.Traseaza_linii(p2, gasit);

                if(gasit == 0) tranzistor_pnp.Traseaza_linii(p2, gasit);
                if(gasit == 0) voltmetru.Traseaza_linii(p2, gasit);
                if(gasit == 0) potentiometru.Traseaza_linii(p2, gasit);
                if(gasit == 0) bec.Traseaza_linii(p2, gasit);

                if(gasit == 1)
                {
                    sterge_ultima_legatura(Leg);
                    if(abs(p1.y - p2.y) < abs(p1.x - p2.x)) p3 = {p1.x, p2.y};
                    else p3 = {p2.x, p1.y};
                    Leg.L1 = setare_linie(p1, p3, culoare), Leg.L2 = setare_linie(p3, p2, culoare), Leg.p1 = p1, Leg.p2 = p2;
                    deseneaza_legatura(Leg);

                    break;
                }
            }
        }
    }
}

public:void Mod_modificare_text(Buton &Modificare_text)
{
    Punct p;
    bool gasit;

    for(auto it:Noduri)
    {
        Nod g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        deseneaza_text(g.text, p);

        Noduri.erase(Noduri.find(g));
        g.show_text = 1;
        Noduri.insert(g);
    }

    for(auto it:Generatoare)
    {
        Generator g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        deseneaza_text(g.text, p);

        Generatoare.erase(Generatoare.find(g));
        g.show_text = 1;
        Generatoare.insert(g);
    }

    for(auto it:Rezistoare)
    {
        Rezistor g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        deseneaza_text(g.text, p);

        Rezistoare.erase(Rezistoare.find(g));
        g.show_text = 1;
        Rezistoare.insert(g);
    }

    for(auto it:Condensatoare)
    {
        Condensator g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        deseneaza_text(g.text, p);

        Condensatoare.erase(Condensatoare.find(g));
        g.show_text = 1;
        Condensatoare.insert(g);
    }

    for(auto it:Amplificatoare_operationale)
    {
        Amplificator_operational g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        deseneaza_text(g.text, p);

        Amplificatoare_operationale.erase(Amplificatoare_operationale.find(g));
        g.show_text = 1;
        Amplificatoare_operationale.insert(g);
    }

    for(auto it:Diode_tunnel)
    {
        Dioda_tunnel g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        deseneaza_text(g.text, p);

        Diode_tunnel.erase(Diode_tunnel.find(g));
        g.show_text = 1;
        Diode_tunnel.insert(g);
    }

    for(auto it:Diode_zener)
    {
        Dioda_zener g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        deseneaza_text(g.text, p);

        Diode_zener.erase(Diode_zener.find(g));
        g.show_text = 1;
        Diode_zener.insert(g);
    }

    for(auto it:Tranzistoare_npn)
    {
        Tranzistor_npn g = it;
        if(g.orientare == 0) p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        else if(g.orientare == 1) p.x = g.centru.x, p.y = min(g.margine1.y, g.margine2.y) - 10;
        else if(g.orientare == 2) p.x = min(g.margine1.x, g.margine2.x) - 17, p.y = g.centru.y;
        else p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        deseneaza_text(g.text, p);

        Tranzistoare_npn.erase(Tranzistoare_npn.find(g));
        g.show_text = 1;
        Tranzistoare_npn.insert(g);
    }

    for(auto it:Tranzistoare_pnp)
    {
        Tranzistor_pnp g = it;
        if(g.orientare == 0) p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        else if(g.orientare == 1) p.x = g.centru.x, p.y = min(g.margine1.y, g.margine2.y) - 10;
        else if(g.orientare == 2) p.x = min(g.margine1.x, g.margine2.x) - 17, p.y = g.centru.y;
        else p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        deseneaza_text(g.text, p);

        Tranzistoare_pnp.erase(Tranzistoare_pnp.find(g));
        g.show_text = 1;
        Tranzistoare_pnp.insert(g);
    }

    for(auto it:Voltmetre)
    {
        Voltmetru g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        deseneaza_text(g.text, p);

        Voltmetre.erase(Voltmetre.find(g));
        g.show_text = 1;
        Voltmetre.insert(g);
    }

    for(auto it:Potentiometre)
    {
        Potentiometru g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        deseneaza_text(g.text, p);

        Potentiometre.erase(Potentiometre.find(g));
        g.show_text = 1;
        Potentiometre.insert(g);
    }

    for(auto it:Becuri)
    {
        Bec g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        deseneaza_text(g.text, p);

        Becuri.erase(Becuri.find(g));
        g.show_text = 1;
        Becuri.insert(g);
    }



    while(Modificare_text.stare == 1)
    {
        while(ismouseclick(WM_LBUTTONUP) == 0) delay(50);
        getmouseclick(WM_LBUTTONUP, p.x, p.y), clearmouseclick(WM_LBUTTONUP);

        if(buton.verif_punct_apartine_buton(p, Modificare_text) == 1) buton.actioneaza_buton(Modificare_text);
        else
        {
            gasit = 0;
            nod.Modificare_text(p, gasit);
            if(gasit == 0) generator.Modificare_text(p, gasit);
            if(gasit == 0) rezistor.Modificare_text(p, gasit);
            if(gasit == 0) condensator.Modificare_text(p, gasit);
            if(gasit == 0) amplificator_operational.Modificare_text(p, gasit);
            if(gasit == 0) dioda_tunnel.Modificare_text(p, gasit);
            if(gasit == 0) dioda_zener.Modificare_text(p, gasit);
            if(gasit == 0) tranzistor_npn.Modificare_text(p, gasit);
            if(gasit == 0) tranzistor_pnp.Modificare_text(p, gasit);
            if(gasit == 0) voltmetru.Modificare_text(p, gasit);
            if(gasit == 0) potentiometru.Modificare_text(p, gasit);
            if(gasit == 0) bec.Modificare_text(p, gasit);
        }
    }


    for(auto it:Noduri)
    {
        Nod g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        sterge_text(g.text, p);

        Noduri.erase(Noduri.find(g));
        g.show_text = 0;
        Noduri.insert(g);
    }

    for(auto it:Generatoare)
    {
        Generator g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        sterge_text(g.text, p);

        Generatoare.erase(Generatoare.find(g));
        g.show_text = 0;
        Generatoare.insert(g);
    }

    for(auto it:Rezistoare)
    {
        Rezistor g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        sterge_text(g.text, p);

        Rezistoare.erase(Rezistoare.find(g));
        g.show_text = 0;
        Rezistoare.insert(g);
    }

    for(auto it:Condensatoare)
    {
        Condensator g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        sterge_text(g.text, p);

        Condensatoare.erase(Condensatoare.find(g));
        g.show_text = 0;
        Condensatoare.insert(g);
    }

    for(auto it:Amplificatoare_operationale)
    {
        Amplificator_operational g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        sterge_text(g.text, p);

        Amplificatoare_operationale.erase(Amplificatoare_operationale.find(g));
        g.show_text = 0;
        Amplificatoare_operationale.insert(g);
    }

    for(auto it:Diode_tunnel)
    {
        Dioda_tunnel g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        sterge_text(g.text, p);

        Diode_tunnel.erase(Diode_tunnel.find(g));
        g.show_text = 0;
        Diode_tunnel.insert(g);
    }

    for(auto it:Diode_zener)
    {
        Dioda_zener g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        sterge_text(g.text, p);

        Diode_zener.erase(Diode_zener.find(g));
        g.show_text = 0;
        Diode_zener.insert(g);
    }

    for(auto it:Tranzistoare_npn)
    {
        Tranzistor_npn g = it;
        if(g.orientare == 0) p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        else if(g.orientare == 1) p.x = g.centru.x, p.y = min(g.margine1.y, g.margine2.y) - 10;
        else if(g.orientare == 2) p.x = min(g.margine1.x, g.margine2.x) - 17, p.y = g.centru.y;
        else p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        sterge_text(g.text, p);

        Tranzistoare_npn.erase(Tranzistoare_npn.find(g));
        g.show_text = 0;
        Tranzistoare_npn.insert(g);
    }

    for(auto it:Tranzistoare_pnp)
    {
        Tranzistor_pnp g = it;
        if(g.orientare == 0) p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        else if(g.orientare == 1) p.x = g.centru.x, p.y = min(g.margine1.y, g.margine2.y) - 10;
        else if(g.orientare == 2) p.x = min(g.margine1.x, g.margine2.x) - 17, p.y = g.centru.y;
        else p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        sterge_text(g.text, p);

        Tranzistoare_pnp.erase(Tranzistoare_pnp.find(g));
        g.show_text = 0;
        Tranzistoare_pnp.insert(g);
    }

    for(auto it:Voltmetre)
    {
        Voltmetru g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        sterge_text(g.text, p);

        Voltmetre.erase(Voltmetre.find(g));
        g.show_text = 0;
        Voltmetre.insert(g);
    }

    for(auto it:Potentiometre)
    {
        Potentiometru g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        sterge_text(g.text, p);

        Potentiometre.erase(Potentiometre.find(g));
        g.show_text = 0;
        Potentiometre.insert(g);
    }

    for(auto it:Becuri)
    {
        Bec g = it;
        if(g.orientare == 0 || g.orientare == 2) p.x = g.centru.x, p.y = max(g.margine1.y, g.margine2.y) + 10;
        else p.x = max(g.margine1.x, g.margine2.x) + 17, p.y = g.centru.y;
        sterge_text(g.text, p);

        Becuri.erase(Becuri.find(g));
        g.show_text = 0;
        Becuri.insert(g);
    }
}

public:void Mod_modificare_legaturi(Buton &Modificare_legaturi)
{
    Legatura Leg;
    Punct p1;

    while(Modificare_legaturi.stare == 1)
    {
        while(ismouseclick(WM_LBUTTONUP) == 0) delay(50);
        getmouseclick(WM_LBUTTONUP, p1.x, p1.y), clearmouseclick(WM_LBUTTONUP);

        if(buton.verif_punct_apartine_buton(p1, Modificare_legaturi) == 1) buton.actioneaza_buton(Modificare_legaturi);
        else
        {
            for(auto it:Legaturi)
            {
                Leg = it;
                if(verif_punct_apartine_legatura(p1, Leg) == 1)
                {
                    modificare_legatura(Leg);
                    break;
                }
            }
        }
    }
}

public:void Mod_stergere(Buton &Sterge)
{
    Punct p;
    bool gasit;

    while(Sterge.stare == 1)
    {
        while(ismouseclick(WM_LBUTTONUP) == 0) delay(50);
        getmouseclick(WM_LBUTTONUP, p.x, p.y), clearmouseclick(WM_LBUTTONUP);

        if(buton.verif_punct_apartine_buton(p, Sterge) == 1) buton.actioneaza_buton(Sterge);
        else
        {
            gasit = 0;
            nod.Mod_sterge(p, gasit);
            if(gasit == 0) generator.Mod_sterge(p, gasit);
            if(gasit == 0) rezistor.Mod_sterge(p, gasit);
            if(gasit == 0) condensator.Mod_sterge(p, gasit);
            if(gasit == 0) amplificator_operational.Mod_sterge(p, gasit);
            if(gasit == 0) dioda_tunnel.Mod_sterge(p, gasit);
            if(gasit == 0) dioda_zener.Mod_sterge(p, gasit);
            if(gasit == 0) tranzistor_npn.Mod_sterge(p, gasit);
            if(gasit == 0) tranzistor_pnp.Mod_sterge(p, gasit);
            if(gasit == 0) voltmetru.Mod_sterge(p, gasit);
            if(gasit == 0) potentiometru.Mod_sterge(p, gasit);
            if(gasit == 0) bec.Mod_sterge(p, gasit);
        }
    }
}

public:void testare_finala()
{
    Buton Zoom, Rotire, Mutare, Traseaza_linii, Modificare_text, Modificare_legaturi, Sterge, Inapoi;
    Buton Punere_nod, Punere_generator, Punere_rezistor, Punere_condensator, Punere_amplificator_operational;
    Buton Punere_tranzistor_NPN, Punere_tranzistor_PNP, Punere_dioda_Tunnel, Punere_dioda_Zener, Punere_voltmetru, Punere_potentiometru, Punere_bec;

    Buton Electron, New_Project, Load_Project, Tutorial, Exit;
    Punct p1, p2, p3;

    readimagefile("./Imagini/Prima.jpg", 0, 0, LATIME_WINDOW, LUNGIME_WINDOW);
    readimagefile("./Imagini/Titlu.jpg", 700, 150, 1150, 250);

    p1 = {850, 350}, p2 = {1000, 400};
    New_Project = buton.setare_buton(p1, p2, 0, 2, 0, "New Project");
    buton.deseneaza_buton(New_Project);

    p1 = {850, 430}, p2 = {1000, 480};
    Exit = buton.setare_buton(p1, p2, 0, 2, 0, "Exit");
    buton.deseneaza_buton(Exit);

    p3 = click_stanga();
    while(buton.verif_punct_apartine_buton(p3, New_Project) == 0 && buton.verif_punct_apartine_buton(p3, Exit) == 0) p3 = click_stanga();

    if(buton.verif_punct_apartine_buton(p3, New_Project) == 1)
    {
        buton.apasare_buton(New_Project);
        stergere_totala();


        readimagefile("./Imagini/A_doua.jpg", 0, 0, LATIME_WINDOW, LUNGIME_WINDOW);
        setcolor(WHITE);
        setfillstyle(0, BLACK);
        bar(X1, Y1, X2, Y2);


        p1 = {10, 200 + 70 * 0}, p2 = {180, 250 + 70 * 0};
        Punere_nod = buton.setare_buton(p1, p2, 8, 7, 0, "Nod");
        buton.deseneaza_buton(Punere_nod);

        p1 = {10, 200 + 70 * 1}, p2 = {180, 250 + 70 * 1};
        Punere_generator = buton.setare_buton(p1, p2, 8, 7, 0, "Generator");
        buton.deseneaza_buton(Punere_generator);

        p1 = {10, 200 + 70 * 2}, p2 = {180, 250 + 70 * 2};
        Punere_rezistor = buton.setare_buton(p1, p2, 8, 7, 0, "Rezistor");
        buton.deseneaza_buton(Punere_rezistor);

        p1 = {10, 200 + 70 * 3}, p2 = {180, 250 + 70 * 3};
        Punere_condensator = buton.setare_buton(p1, p2, 8, 7, 0, "Condensator");
        buton.deseneaza_buton(Punere_condensator);

        p1 = {10, 200 + 70 * 4}, p2 = {180, 250 + 70 * 4};
        Punere_amplificator_operational = buton.setare_buton(p1, p2, 8, 7, 0, "Amplificator operational");
        buton.deseneaza_buton(Punere_amplificator_operational);

        p1 = {10, 200 + 70 * 5}, p2 = {180, 250 + 70 * 5};
        Punere_dioda_Tunnel = buton.setare_buton(p1, p2, 8, 7, 0, "Dioda Tunnel");
        buton.deseneaza_buton(Punere_dioda_Tunnel);

        p1 = {1670, 200 + 70 * 0}, p2 = {1840, 250 + 70 * 0};
        Punere_dioda_Zener = buton.setare_buton(p1, p2, 8, 7, 0, "Dioda Zener");
        buton.deseneaza_buton(Punere_dioda_Zener);

        p1 = {1670, 200 + 70 * 1}, p2 = {1840, 250 + 70 * 1};
        Punere_tranzistor_NPN = buton.setare_buton(p1, p2, 8, 7, 0, "Tranzistor NPN");
        buton.deseneaza_buton(Punere_tranzistor_NPN);

        p1 = {1670, 200 + 70 * 2}, p2 = {1840, 250 + 70 * 2};
        Punere_tranzistor_PNP = buton.setare_buton(p1, p2, 8, 7, 0, "Tranzistor PNP");
        buton.deseneaza_buton(Punere_tranzistor_PNP);

        p1 = {1670, 200 + 70 * 3}, p2 = {1840, 250 + 70 * 3};
        Punere_voltmetru = buton.setare_buton(p1, p2, 8, 7, 0, "Voltmetru");
        buton.deseneaza_buton(Punere_voltmetru);

        p1 = {1670, 200 + 70 * 4}, p2 = {1840, 250 + 70 * 4};
        Punere_potentiometru = buton.setare_buton(p1, p2, 8, 7, 0, "Potentiometru");
        buton.deseneaza_buton(Punere_potentiometru);

        p1 = {1670, 200 + 70 * 5}, p2 = {1840, 250 + 70 * 5};
        Punere_bec = buton.setare_buton(p1, p2, 8, 7, 0, "Bec");
        buton.deseneaza_buton(Punere_bec);



        p1 = {145 * 4 + 10, 10}, p2 = {145 * 4 + 150, 100};
        Traseaza_linii = buton.setare_buton(p1, p2, 8, 7, 0, "Traseaza linii");
        buton.deseneaza_buton(Traseaza_linii);

        p1 = {145 * 5 + 10, 10}, p2 = {145 * 5 + 150, 100};
        Mutare = buton.setare_buton(p1, p2, 8, 7, 0, "Mutare");
        buton.deseneaza_buton(Mutare);

        p1 = {145 * 6 + 10, 10}, p2 = {145 * 6 + 150, 100};
        Zoom = buton.setare_buton(p1, p2, 8, 7, 0, "Zoom");
        buton.deseneaza_buton(Zoom);

        p1 = {145 * 7 + 10, 10}, p2 = {145 * 7 + 150, 100};
        Rotire = buton.setare_buton(p1, p2, 8, 7, 0, "Rotire");
        buton.deseneaza_buton(Rotire);

        p1 = {145 * 8 + 10, 10}, p2 = {145 * 8 + 150, 100};
        Modificare_text = buton.setare_buton(p1, p2, 8, 7, 0, "Modificare valoare");
        buton.deseneaza_buton(Modificare_text);

        p1 = {145 * 9 + 10, 10}, p2 = {145 * 9 + 150, 100};
        Modificare_legaturi = buton.setare_buton(p1, p2, 8, 7, 0, "Modificare legaturi");
        buton.deseneaza_buton(Modificare_legaturi);

        p1 = {1700, 780}, p2 = {1800, 880};
        Sterge = buton.setare_buton(p1, p2, 8, 7, 0, "Sterge");
        buton.deseneaza_buton(Sterge);

        p1 = {50, 10}, p2 = {150, 100};
        Inapoi = buton.setare_buton(p1, p2, 8, 7, 0, "Inapoi");
        buton.deseneaza_buton(Inapoi);

        while(1)
        {
            clearmouseclick(WM_LBUTTONUP);
            while((Punere_nod.stare | Punere_generator.stare | Punere_rezistor.stare | Punere_condensator.stare | Punere_voltmetru.stare | Punere_tranzistor_NPN.stare | Punere_bec.stare | Punere_amplificator_operational.stare | Punere_dioda_Tunnel.stare | Punere_dioda_Zener.stare | Punere_potentiometru.stare | Punere_tranzistor_PNP.stare | Traseaza_linii.stare | Mutare.stare | Zoom.stare | Rotire.stare | Modificare_text.stare | Modificare_legaturi.stare | Sterge.stare) == 0)
            {
                while(ismouseclick(WM_LBUTTONUP) == 0) delay(50);
                getmouseclick(WM_LBUTTONUP, p1.x, p1.y), clearmouseclick(WM_LBUTTONUP);

                if(buton.verif_punct_apartine_buton(p1, Punere_nod) == 1) buton.actioneaza_buton(Punere_nod);
                else if(buton.verif_punct_apartine_buton(p1, Punere_rezistor) == 1) buton.actioneaza_buton(Punere_rezistor);
                else if(buton.verif_punct_apartine_buton(p1, Punere_generator) == 1) buton.actioneaza_buton(Punere_generator);
                else if(buton.verif_punct_apartine_buton(p1, Punere_condensator) == 1) buton.actioneaza_buton(Punere_condensator);
                else if(buton.verif_punct_apartine_buton(p1, Punere_amplificator_operational) == 1) buton.actioneaza_buton(Punere_amplificator_operational);
                else if(buton.verif_punct_apartine_buton(p1, Punere_dioda_Tunnel) == 1) buton.actioneaza_buton(Punere_dioda_Tunnel);
                else if(buton.verif_punct_apartine_buton(p1, Punere_dioda_Zener) == 1) buton.actioneaza_buton(Punere_dioda_Zener);
                else if(buton.verif_punct_apartine_buton(p1, Punere_tranzistor_NPN) == 1) buton.actioneaza_buton(Punere_tranzistor_NPN);
                else if(buton.verif_punct_apartine_buton(p1, Punere_tranzistor_PNP) == 1) buton.actioneaza_buton(Punere_tranzistor_PNP);
                else if(buton.verif_punct_apartine_buton(p1, Punere_voltmetru) == 1) buton.actioneaza_buton(Punere_voltmetru);
                else if(buton.verif_punct_apartine_buton(p1, Punere_potentiometru) == 1) buton.actioneaza_buton(Punere_potentiometru);
                else if(buton.verif_punct_apartine_buton(p1, Punere_bec) == 1) buton.actioneaza_buton(Punere_bec);

                else if(buton.verif_punct_apartine_buton(p1, Traseaza_linii) == 1) buton.actioneaza_buton(Traseaza_linii);
                else if(buton.verif_punct_apartine_buton(p1, Mutare) == 1) buton.actioneaza_buton(Mutare);
                else if(buton.verif_punct_apartine_buton(p1, Zoom) == 1) buton.actioneaza_buton(Zoom);
                else if(buton.verif_punct_apartine_buton(p1, Rotire) == 1) buton.actioneaza_buton(Rotire);
                else if(buton.verif_punct_apartine_buton(p1, Modificare_text) == 1) buton.actioneaza_buton(Modificare_text);
                else if(buton.verif_punct_apartine_buton(p1, Modificare_legaturi) == 1) buton.actioneaza_buton(Modificare_legaturi);
                else if(buton.verif_punct_apartine_buton(p1, Sterge) == 1) buton.actioneaza_buton(Sterge);
                else if(buton.verif_punct_apartine_buton(p1, Inapoi) == 1) testare_finala();

            }

            if(Punere_nod.stare == 1) nod.Mod_punere(Punere_nod);
            else if(Punere_generator.stare == 1) generator.Mod_punere(Punere_generator);
            else if(Punere_rezistor.stare == 1) rezistor.Mod_punere(Punere_rezistor);
            else if(Punere_condensator.stare == 1) condensator.Mod_punere(Punere_condensator);
            else if(Punere_amplificator_operational.stare == 1) amplificator_operational.Mod_punere(Punere_amplificator_operational);
            else if(Punere_dioda_Tunnel.stare == 1) dioda_tunnel.Mod_punere(Punere_dioda_Tunnel);
            else if(Punere_dioda_Zener.stare == 1) dioda_zener.Mod_punere(Punere_dioda_Zener);
            else if(Punere_tranzistor_NPN.stare == 1) tranzistor_npn.Mod_punere(Punere_tranzistor_NPN);
            else if(Punere_tranzistor_PNP.stare == 1) tranzistor_pnp.Mod_punere(Punere_tranzistor_PNP);
            else if(Punere_voltmetru.stare == 1) voltmetru.Mod_punere(Punere_voltmetru);
            else if(Punere_potentiometru.stare == 1) potentiometru.Mod_punere(Punere_potentiometru);
            else if(Punere_bec.stare == 1) bec.Mod_punere(Punere_bec);

            else if(Mutare.stare == 1) Mod_mutare(Mutare);
            else if(Zoom.stare == 1) Mod_zoom(Zoom);
            else if(Rotire.stare == 1) Mod_rotire(Rotire);
            else if(Traseaza_linii.stare == 1) Mod_traseaza_linii(Traseaza_linii);
            else if(Modificare_text.stare == 1) Mod_modificare_text(Modificare_text);
            else if(Modificare_legaturi.stare == 1) Mod_modificare_legaturi(Modificare_legaturi);
            else if(Sterge.stare == 1) Mod_stergere(Sterge);


        }
    }

    else if(buton.verif_punct_apartine_buton(p3, Exit) == 1)
    {
        exit(0);
    }
}

};




int main()
{
    Rulare_finala A;

    initwindow(LATIME_WINDOW, LUNGIME_WINDOW);


    A.testare_finala();

    getch();
    closegraph();


    return 0;
}



void afiseaza_eroare(string text)
{
    BUTON buton;
    Buton Inchide;
    Punct p1, p2;

    const int fereastra_curenta = getcurrentwindow();

    initwindow(350, 200, "", 775, 365);

    p1.y = 65 - 7;
    p1.x = 175 - 5 - 3 * (text.size() - 1);

    char c[text.size()];
    strcpy(c, text.c_str());
    outtextxy(p1.x, p1.y, (char*)c);

    p1 = {125, 135}, p2 = {225, 175};
    Inchide = buton.setare_buton(p1, p2, 4, 2, 0, "OK");
    buton.deseneaza_buton(Inchide);

    clearmouseclick(WM_LBUTTONDOWN);

    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x = mousex(), y = mousey();
            if(x >= 125 && x <= 225 && y >= 135 && y <= 175) break;
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }

    closegraph(CURRENT_WINDOW);
    setcurrentwindow(fereastra_curenta);
}





bool verif_punct_apartine_linie(Punct p, Linie L)
{
    double a = L.p1.y - L.p2.y, b = L.p2.x - L.p1.x, c = - a * L.p1.x - b * L.p1.y;
    double dist = double(double(abs(a * p.x + b * p.y + c)) / double(sqrt(a * a + b * b)));

    if(L.p1.x == L.p2.x && p.y >= min(L.p1.y, L.p2.y) && p.y <= max(L.p1.y, L.p2.y) && dist <= 6) return 1;
    else if(L.p1.y == L.p2.y && p.x >= min(L.p1.x, L.p2.x) && p.x <= max(L.p1.x, L.p2.x) && dist <= 6) return 1;

    return 0;
}

bool verif_punct_apartine_legatura(Punct p, Legatura Leg)
{
    return (verif_punct_apartine_linie(p, Leg.L1) || verif_punct_apartine_linie(p, Leg.L2));
}

void modificare_legatura(Legatura Leg)
{
    sterge_ultima_legatura(Leg);
    Leg.mai_mica_intai ^= 1;
    seteaza_linii_legatura(Leg);
    deseneaza_legatura(Leg);
}


bool verif_punct_apartine_chenar(Punct p)
{
    return (p.x > X1 && p.y > Y1 && p.x < X2 && p.y < Y2);
}

bool verif_piesa_suprapune_piesa(Punct margine1, Punct margine2, Punct margine3, Punct margine4)
{
    if((max(margine1.x, margine2.x) < min(margine3.x, margine4.x)) || (max(margine3.x, margine4.x) < min(margine1.x, margine2.x))) return 0;
    if((max(margine1.y, margine2.y) < min(margine3.y, margine4.y)) || (max(margine3.y, margine4.y) < min(margine1.y, margine2.y))) return 0;
    return 1;

}

bool verif_se_suprapune(Punct margine1, Punct margine2)
{
    for (auto it: Noduri) if(verif_piesa_suprapune_piesa(margine1, margine2, it.margine1, it.margine2) == 1) return 1;
    for (auto it: Generatoare) if(verif_piesa_suprapune_piesa(margine1, margine2, it.margine1, it.margine2) == 1) return 1;
    for (auto it: Rezistoare) if(verif_piesa_suprapune_piesa(margine1, margine2, it.margine1, it.margine2) == 1) return 1;
    for (auto it: Condensatoare) if(verif_piesa_suprapune_piesa(margine1, margine2, it.margine1, it.margine2) == 1) return 1;
    for (auto it: Amplificatoare_operationale) if(verif_piesa_suprapune_piesa(margine1, margine2, it.margine1, it.margine2) == 1) return 1;
    for (auto it: Diode_tunnel) if(verif_piesa_suprapune_piesa(margine1, margine2, it.margine1, it.margine2) == 1) return 1;
    for (auto it: Diode_zener) if(verif_piesa_suprapune_piesa(margine1, margine2, it.margine1, it.margine2) == 1) return 1;
    for (auto it: Tranzistoare_npn) if(verif_piesa_suprapune_piesa(margine1, margine2, it.margine1, it.margine2) == 1) return 1;
    for (auto it: Tranzistoare_pnp) if(verif_piesa_suprapune_piesa(margine1, margine2, it.margine1, it.margine2) == 1) return 1;
    for (auto it: Voltmetre) if(verif_piesa_suprapune_piesa(margine1, margine2, it.margine1, it.margine2) == 1) return 1;
    for (auto it: Potentiometre) if(verif_piesa_suprapune_piesa(margine1, margine2, it.margine1, it.margine2) == 1) return 1;
    for (auto it: Becuri) if(verif_piesa_suprapune_piesa(margine1, margine2, it.margine1, it.margine2) == 1) return 1;

    return 0;
}


void regleaza_linie_dreapta(Linie &L)
{
    if(L.p1.x > L.p2.x) swap(L.p1, L.p2);
    else if(L.p1.y > L.p2.y) swap(L.p1, L.p2);
}



void seteaza_linii_legatura(Legatura &Leg)
{
    Punct p;

    if(Leg.mai_mica_intai == 1)
    {
        if(abs(Leg.p1.y - Leg.p2.y) < abs(Leg.p1.x - Leg.p2.x)) p = {Leg.p1.x, Leg.p2.y};
        else p = {Leg.p2.x, Leg.p1.y};
    }
    else
    {
        if(abs(Leg.p1.y - Leg.p2.y) < abs(Leg.p1.x - Leg.p2.x)) p = {Leg.p2.x, Leg.p1.y};
        else p = {Leg.p1.x, Leg.p2.y};
    }

    Leg.L1.culoare = Leg.L2.culoare = 14;
    Leg.L1.p1 = Leg.p1, Leg.L2.p2 = Leg.p2;
    Leg.L1.p2 = Leg.L2.p1 = p;
}

void deseneaza_legatura(Legatura Leg)
{
    deseneaza_linie_dreapta(Leg.L1), deseneaza_linie_dreapta(Leg.L2);
    Legaturi.insert(Leg);
}

void sterge_ultima_legatura(Legatura Leg)
{
    sterge_ultima_linie_dreapta(Leg.L1), sterge_ultima_linie_dreapta(Leg.L2);
    if(Leg.L1.culoare != 0 && Leg.L2.culoare != 0) Legaturi.erase(Leg);
}






Linie setare_linie(Punct p1, Punct p2, int culoare)
{
    Linie L = {p1, p2, culoare};
    return L;
}

void deseneaza_linie_dreapta(Linie L1)
{
    int i;

    if(L1.p1.x > L1.p2.x) swap(L1.p1.x, L1.p2.x);
    if(L1.p1.y > L1.p2.y) swap(L1.p1.y, L1.p2.y);

    setcolor(L1.culoare);
    line(L1.p1.x, L1.p1.y, L1.p2.x, L1.p2.y);

    if(L1.p1.x == L1.p2.x) for(i = L1.p1.y; i <= L1.p2.y; i++) h[L1.p1.x][i].pb(L1.culoare);
    else if(L1.p1.y == L1.p2.y) for(i = L1.p1.x; i <= L1.p2.x; i++) h[i][L1.p1.y].pb(L1.culoare);
}

void sterge_ultima_linie_dreapta(Linie L1)
{
    int i, j;

    if(L1.p1.x > L1.p2.x) swap(L1.p1.x, L1.p2.x);
    if(L1.p1.y > L1.p2.y) swap(L1.p1.y, L1.p2.y);

    for(i = L1.p1.x; i <= L1.p2.x; i++)
        for(j = L1.p1.y; j <= L1.p2.y; j++)
            if(h[i][j].empty() == 0)
            {
                h[i][j].pop_back();
                if(h[i][j].empty() != 0) putpixel(i, j, 0);
                else putpixel(i, j, h[i][j].back());
            }
}




void deseneaza_linie_diagonala(Linie L)
{
    int i, j;

    setcolor(L.culoare);
    line(L.p1.x, L.p1.y, L.p2.x, L.p2.y);
    for(i = min(L.p1.x, L.p2.x); i <= max(L.p1.x, L.p2.x); i++)
        for(j = min(L.p1.y, L.p2.y); j <= max(L.p1.y, L.p2.y); j++)
            h[i][j].pb(getpixel(i, j));
}

void sterge_ultima_linie_diagonala(Linie L)
{
    int i, j;

    for(i = min(L.p1.x, L.p2.x); i <= max(L.p1.x, L.p2.x); i++)
        for(j = min(L.p1.y, L.p2.y); j <= max(L.p1.y, L.p2.y); j++)
            if(h[i][j].empty() == 0)
            {
                h[i][j].pop_back();
                if(h[i][j].empty() != 0) putpixel(i, j, 0);
                else putpixel(i, j, h[i][j].back());
            }
}


void deseneaza_cerc_plin(Punct centru, int raza, int culoare)
{
    int i, j;

    setfillstyle(SOLID_FILL, culoare);
    fillellipse(centru.x, centru.y, raza, raza);
    for(i = centru.x - raza; i <= centru.x + raza; i++)
        for(j = centru.y - raza; j <= centru.y + raza; j++)
            h[i][j].pb(getpixel(i, j));
}

void sterge_cerc_plin(Punct centru, int raza)
{
    int i, j;

    for(i = centru.x - raza; i <= centru.x + raza; i++)
        for(j = centru.y - raza; j <= centru.y + raza; j++)
            if(h[i][j].empty() == 0)
            {
                h[i][j].pop_back();
                if(h[i][j].empty() != 0) putpixel(i, j, 0);
                else putpixel(i, j, h[i][j].back());
            }
}

void deseneaza_cerc_gol(Punct centru, int raza, int culoare)
{
    int i, j;

    setcolor(culoare);
    circle(centru.x, centru.y, raza);
    for(i = centru.x - raza; i <= centru.x + raza; i++)
        for(j = centru.y - raza; j <= centru.y + raza; j++)
            h[i][j].pb(getpixel(i, j));
}

void sterge_cerc_gol(Punct centru, int raza)
{
    int i, j;

    for(i = centru.x - raza; i <= centru.x + raza; i++)
        for(j = centru.y - raza; j <= centru.y + raza; j++)
        {
            h[i][j].pop_back();
            if(h[i][j].empty() != 0) putpixel(i, j, 0);
            else putpixel(i, j, h[i][j].back());
        }
}





void rotire_punct(Punct centru, Punct &p)
{
    p.x -= centru.x, p.y -= centru.y;
    p = {p.y, -p.x};
    p.x += centru.x, p.y += centru.y;
}

void rotire_linie(Punct centru, Linie &L)
{
    rotire_punct(centru, L.p1), rotire_punct(centru, L.p2);
}




int distanta_dintre_2_puncte(Punct p1, Punct p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

void stergere_totala()
{
    int i, j;

    cleardevice();
    for(i = 0; i < LATIME_WINDOW; i++)
        for(j = 0; j < LUNGIME_WINDOW; j++)
            if(h[i][j].empty() == 0) h[i][j].clear();

    Butoane.clear();
}


Punct click_stanga()
{
    const int DELAY = 50;
    Punct p1;

    while(ismouseclick(WM_LBUTTONUP) == 0) delay(DELAY);
    getmouseclick(WM_LBUTTONUP, p1.x, p1.y);

    return p1;
}


void coloreaza_dreptunghi(Punct p1, Punct p2, int culoare)
{
    int i, j;

    if(p1.x > p2.x) swap(p1.x, p2.x);
    if(p1.y > p2.y) swap(p1.y, p2.y);

    setcolor(culoare);
    for(i = p1.x; i <= p2.x; i++) line(i, p1.y, i, p2.y);

    for(i = p1.x; i <= p2.x; i++)
        for(j = p1.y; j <= p2.y; j++)
            h[i][j].pb(culoare);
}



/// initwindow(x, y) - initializaza o fereastra x pe y (latime x, lungime y)
/// line(x1, y1, x2, y2) - deseneaza o linie alba intre punctele de coordonate (x1, y1) si (x2, y2)
/// circle(x, y, radius) - deseneaza un cerc alb (cu interiorul negru) cu centrul in (x, y) si cu raza = radius
/// rectangle(x1, y1, x2, y2) - deseneaza un dreptunghi alb (cu interiorul negru) cu varfurile opuse de coordonate (x1, y1) si (x2, y2)
/// bar(x1, y1, x2, y2) - deseneaza un dreptunghi alb (cu interiorul alb) cu varfurile opuse de coordonate (x1, y1) si (x2, y2)
/// putpixel(x, y, culoare) - deseneaza un pixel de culoare = culoare la coordonatele (x, y)

/// delay(x) - face un delay de x milisecunde
/// getmaxx() - returneaza un int ((val. maxima care se poate folosi pt. x) - 1)
/// getmaxy() - returneaza un int ((val. maxima care se poate folosi pt. y) - 1)



/*
Culori:
0 - BLACK
1 - BLUE
2 - GREEN
3 - CYAN
4 - RED
5 - MAGENTA
6 - BROWN
7 - LIGHTGRAY
8 - DARKGRAY
9 - LIGHTBLUE
10 - LIGHTGREEN
11 - LIGHTCYAN
12 - LIGHTRED
13 - LIGHTMAGENTA
14 - YELLOW
15 - WHITE
*/










