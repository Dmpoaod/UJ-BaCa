//MichaĹ‚ Wilewski
#include<iostream>
using namespace std;
unsigned long long int sumE = 0;
struct place
{
    unsigned short int goods;
    char label[2];

};

struct shelf
{
    short int Sindex = 0;
    place places[128];
};

struct rack
{
    short int Rindex = 0;
    shelf shelves[128];
};

struct warehouse
{
    short int Windex = 0;
    rack racks[128];
    shelf handy_shelf;
};

struct GW
{
    short int Gindex = 0;
    warehouse warehouses[128];

    rack handy_rack;
    shelf handy_shelf;
};

static GW MyGW;

static void SETAP (unsigned short int wb, unsigned short int rb, unsigned short int sb, unsigned short int Pe)
{

    if ( MyGW.warehouses[wb].racks[rb].shelves[sb].Sindex == 0)
    {
        MyGW.warehouses[wb].racks[rb].shelves[sb].Sindex = Pe;
        for (int i = 0; i < Pe; i++)
        {
            MyGW.warehouses[wb].racks[rb].shelves[sb].places[i] = {0};
            MyGW.warehouses[wb].racks[rb].shelves[sb].places[i].label[0] = '\0';
            MyGW.warehouses[wb].racks[rb].shelves[sb].places[i].label[1] = '\0';
        }
    }
    else
    {
        if ( MyGW.warehouses[wb].racks[rb].shelves[sb].Sindex > Pe)
        {
            for (int i = Pe; i < MyGW.warehouses[wb].racks[rb].shelves[sb].Sindex; i++)
            {
                sumE -=  MyGW.warehouses[wb].racks[rb].shelves[sb].places[i].goods;
            }
            MyGW.warehouses[wb].racks[rb].shelves[sb].Sindex = Pe;
        }
        else
        {
            for (int i = MyGW.warehouses[wb].racks[rb].shelves[sb].Sindex; i < Pe; i++)
            {
                MyGW.warehouses[wb].racks[rb].shelves[sb].places[i] = {0};
            }
            MyGW.warehouses[wb].racks[rb].shelves[sb].Sindex = Pe;
        }
    }
}

static void SETAS (unsigned short int wb, unsigned short int rb, unsigned short int Se, unsigned short int Pe)
{
    if ( MyGW.warehouses[wb].racks[rb].Rindex == 0)
    {
        MyGW.warehouses[wb].racks[rb].Rindex = Se;
        for (int j = 0; j < Se; j++)
        {
            MyGW.warehouses[wb].racks[rb].shelves[j].Sindex = Pe;
            for (int i = 0; i < Pe; i++)
            {
                MyGW.warehouses[wb].racks[rb].shelves[j].places[i] = {0};
                MyGW.warehouses[wb].racks[rb].shelves[j].places[i].label[0] = '\0';
                MyGW.warehouses[wb].racks[rb].shelves[j].places[i].label[1] = '\0';
            }
        }
    }
    else
    {
        MyGW.warehouses[wb].racks[rb].Rindex = Se;
        for(int i = 0; i < Se; i++) {
            SETAP(wb, rb, i, Pe);
            // MyGW.warehouses[wb].racks[rb].shelves[i].Sindex = Pe;
        }
    }
}

static void SETAR (unsigned short int wb, unsigned short int Re, unsigned short int Se, unsigned short int Pe)
{
    if (MyGW.warehouses[wb].Windex == 0)
    {
        MyGW.warehouses[wb].Windex = Re;
        for (int i = 0; i < Re; i++)
        {
            MyGW.warehouses[wb].racks[i].Rindex = Se;
            for (int j = 0; j < Se; j++)
            {
                MyGW.warehouses[wb].racks[i].shelves[j].Sindex = Pe;
                for(int k = 0; k < Pe; k++) {
                    MyGW.warehouses[wb].racks[i].shelves[j].places[k].goods = 0;
                    MyGW.warehouses[wb].racks[i].shelves[j].places[k].label[0] = '\0';
                    MyGW.warehouses[wb].racks[i].shelves[j].places[k].label[1] = '\0';
                }
            }
        }
    } else
    {
        MyGW.warehouses[wb].Windex = Re;
        for (int i = 0; i < Re; i++)
        {
            SETAS(wb, i, Se, Pe);
        }
    }
}
static void printMyGW() {
    cout << "Gindex - " << MyGW.Gindex << endl;
//    cout << "Rindex - " << MyGW.handy_rack.Rindex << endl;
//    cout << "Sindex - " << MyGW.handy_shelf.Sindex << endl;
    cout << "PodrÄ™czny regaĹ‚ (handy rack), Rindex - " << MyGW.handy_rack.Rindex << endl;
    for (int i = 0; i < MyGW.handy_rack.Rindex; i++) {
        cout << "  PĂłĹ‚ka (shelf) - " << i << ", Sindex - " << MyGW.handy_rack.shelves[i].Sindex << endl;
        for (int j = 0; j < MyGW.handy_rack.shelves[i].Sindex; j++) {
            cout << "      Miejsce (place) - " << j << ", Towar - " << MyGW.handy_rack.shelves[i].places[j].goods <<
                 ", Etykieta - " << MyGW.handy_rack.shelves[i].places[j].label[0] << MyGW.handy_rack.shelves[i].places[j].label[1] << endl;
        }
    }
    cout << "PodrÄ™czna pĂłĹ‚ka (handy shelf), Sindex - " << MyGW.handy_shelf.Sindex << endl;
    for (int i = 0; i < MyGW.handy_shelf.Sindex ; i++) {
        cout << "  Miejsce (place) - " << i << ", Towar - " << MyGW.handy_shelf.places[i].goods <<
             ", Etykieta - " << MyGW.handy_shelf.places[i].label[0] << MyGW.handy_shelf.places[i].label[1] << endl;
    }
    for (int i = 0; i < MyGW.Gindex; i++) {
        cout << endl;
        cout << "MAGAZYN (warehouse) - " << i << ", Windex - " << MyGW.warehouses[i].Windex << endl;
        cout << "PodrÄ™czna pĂłĹ‚ka (handy shelf), Sindex - " << MyGW.warehouses[i].handy_shelf.Sindex << endl;
        for(int n = 0; n < MyGW.warehouses[i].handy_shelf.Sindex; n++) {
            cout << "  Miejsce (place) - " << n << ", Towar - " << MyGW.warehouses[i].handy_shelf.places[n].goods <<
                 ", Etykieta - " << MyGW.warehouses[i].handy_shelf.places[n].label[0] << MyGW.warehouses[i].handy_shelf.places[n].label[1] << endl;
        }
        for (int j = 0; j < MyGW.warehouses[i].Windex; j++) {
            cout << "RegaĹ‚ (rack) -  " << j << ", Rindex - " << MyGW.warehouses[i].racks[j].Rindex << endl;
            for (int k = 0; k < MyGW.warehouses[i].racks[j].Rindex; k++) {
                cout << "  PĂłĹ‚ka (shelf) - " << k << ", Sindex - " << MyGW.warehouses[i].racks[j].shelves[k].Sindex << endl;
                for (int l = 0; l < MyGW.warehouses[i].racks[j].shelves[k].Sindex; l++) {
                    cout << "    Miejsce (place) - " << l << ", Towar - " << MyGW.warehouses[i].racks[j].shelves[k].places[l].goods <<
                         ", Etykieta - " << MyGW.warehouses[i].racks[j].shelves[k].places[l].label[0] << MyGW.warehouses[i].racks[j].shelves[k].places[l].label[1] << endl;
                }
            }
        }
    }
}

int main()
{
    string Type;
    unsigned short int wb = 0;
    unsigned short int rb = 0;
    unsigned short int sb = 0;
    unsigned short int Pe = 0;
    unsigned short int Se = 0;
    unsigned short int Re = 0;
    unsigned short int We = 0;
    unsigned short int w = 0;
    unsigned short int r = 0;
    unsigned short int s = 0;
    unsigned short int p = 0;
    unsigned short int we = 0;
    unsigned short int re = 0;
    unsigned short int se = 0;
    unsigned short int W = 0;
    unsigned short int R = 0;
    unsigned short int S = 0;
    unsigned short int P = 0;
    unsigned short int A = 0;
    char d1 = 0;
    char d2 = 0;


    cin >> Type;

    while (Type.substr(0,6) != "END")
    {
        if (Type.substr(0,6) == "SET-AP")
        {
            cin >> wb >> rb >> sb >> Pe;
            if (wb > MyGW.Gindex-1 || rb > MyGW.warehouses[wb].Windex-1 || sb > MyGW.warehouses[wb].racks[rb].Rindex-1 || Pe > 128)
            {
                cout << "error" << endl;
            }
            else
            {
                SETAP(wb, rb, sb, Pe);
                //printmyGW();
            }
        }
        if (Type.substr(0,6) == "SET-AS")
        {
            cin >> wb >> rb >> Se >> Pe;
            if (wb > MyGW.Gindex-1 || rb > MyGW.warehouses[wb].Windex-1 || Se > 128 || Pe > 128)
            {
                cout << "error" << endl;
            }
            else
            {
                SETAS (wb, rb, Se, Pe);
                //printmyGW();
            }
        }
        if (Type.substr(0,6) == "SET-AR")
        {
            cin >> wb >> Re >> Se >> Pe;
            if (wb > MyGW.Gindex-1 || Re > 128 || Se > 128 || Pe > 128)
            {
                cout << "error" << endl;
            }
            else
            {
                SETAR (wb, Re, Se,Pe);
                // //printmyGW();
            }
        }
        if (Type.substr(0,6) == "SET-AW")
        {
            cin >> We >> Re >> Se >> Pe;
            if (We > 128 || Re > 128 || Se > 128 || Pe > 128)
            {
                cout << "error" << endl;
            }
            else
            {
                if (MyGW.Gindex == 0)
                {
                    MyGW.Gindex = We;
                    for (int k = 0; k < We  ; k++)
                    {
                        MyGW.warehouses[k].Windex = Re;
                        for (int i = 0; i < Re; i++)
                        {
                            MyGW.warehouses[k].racks[i].Rindex = Se;
                            for (int j = 0; j < Se; j++)
                            {
                                MyGW.warehouses[k].racks[i].shelves[j].Sindex = Pe;
                                for (int l = 0; l < Pe; l++)
                                {
                                    MyGW.warehouses[k].racks[i].shelves[j].places[l].goods = 0;
                                    MyGW.warehouses[k].racks[i].shelves[j].places[l].label[0] = '\0';
                                    MyGW.warehouses[k].racks[i].shelves[j].places[l].label[1] = '\0';
                                }
                            }
                        }
                    }
                }
                else {
                    MyGW.Gindex = We;
                    for(int i = 0; i < We; i++) {
                        SETAR(i, Re, Se, Pe);
                    }
                }
                // printMyGW();
            }
        }

//        if (Type.substr(0,6) == "SET-AW")
//        {
//            cin >> We >> Re >> Se >> Pe;
//            if (We > 128 || Re > 128 || Se > 128 || Pe > 128)
//            {
//                cout << "error" << endl;
//            }
//            else
//            {
//                if (MyGW.Gindex == 0)
//                {
//                    MyGW.Gindex = We;
//                    for (int k = 0; k < We  ; k++)
//                    {
//                        MyGW.warehouses[k].Windex = Re;
//                        for (int i = 0; i < Re; i++)
//                        {
//                            MyGW.warehouses[k].racks[i].Rindex = Se;
//                            for (int j = 0; j < Se; j++)
//                            {
//                                MyGW.warehouses[k].racks[i].shelves[j].Sindex = Pe;
//                                for (int l = 0; l < Pe; l++)
//                                {
//                                    MyGW.warehouses[k].racks[i].shelves[j].places[l].goods = 0;
//                                    MyGW.warehouses[k].racks[i].shelves[j].places[l].label[0] = '\0';
//                                    MyGW.warehouses[k].racks[i].shelves[j].places[l].label[1] = '\0';
//                                }
//                            }
//                        }
//                    }
//                }
//                else {
//                    if (MyGW.Gindex > We) {
//                        for(int i = We; i < MyGW.Gindex; i++) {
//                            for(int j = 0; j < MyGW.warehouses[i].Windex; j++) {
//                                for(int k = 0; k < MyGW.warehouses[i].racks[j].Rindex; k++) {
//                                    for(int l = 0; k < MyGW.warehouses[i].racks[j].shelves[k].Sindex; l++) {
//                                        MyGW.warehouses[i].racks[j].shelves[k].places[l].goods = 0;
//                                        MyGW.warehouses[i].racks[j].shelves[k].places[l].label[0] = '\0';
//                                        MyGW.warehouses[i].racks[j].shelves[k].places[l].label[1] = '\0';
//                                    }
//                                    MyGW.warehouses[i].racks[j].shelves[k].Sindex = 0;
//                                }
//                                MyGW.warehouses[i].racks[j].Rindex = 0;
//                            }
//                            MyGW.warehouses[i].Windex = 0;
//                        }
//                        MyGW.Gindex = We;
//                    } else {
//                        MyGW.Gindex = We;
//                        for(int i = 0; i < We; i++) {
//                            SETAR(i, Re, Se, Pe);
//                        }
//                    }
//                }
//             //   printMyGW();
//            }
//        }

        if (Type.substr(0,6) == "SET-HW")
        {
            cin >> w >> P;
            if (w > MyGW.Gindex-1 || P > 128)
            {
                cout << "error" << endl;
            }
            else
            {
                //SETHW(w, P);
                if ( MyGW.warehouses[w].handy_shelf.Sindex == 0)
                {
                    MyGW.warehouses[w].handy_shelf.Sindex = P;
                    for (int i = 0; i < P; i++)
                    {
                        MyGW.warehouses[w].handy_shelf.places[i] = {0};
                        MyGW.warehouses[w].handy_shelf.places[i].label[0] = '\0';
                        MyGW.warehouses[w].handy_shelf.places[i].label[1] = '\0';
                    }
                }
                else
                {
                    if ( MyGW.warehouses[w].handy_shelf.Sindex > P)
                    {
                        for (int i = P; i < MyGW.warehouses[w].handy_shelf.Sindex; i++)
                        {
                            sumE -= MyGW.warehouses[w].handy_shelf.places[i].goods;
                        }
                        MyGW.warehouses[w].handy_shelf.Sindex = P;
                    }
                    else
                    {
                        for (int i = MyGW.warehouses[w].handy_shelf.Sindex; i < P; i++)
                        {
                            MyGW.warehouses[w].handy_shelf.places[i] = {0};
                        }
                        MyGW.warehouses[w].handy_shelf.Sindex = P;
                    }
                }
                //printmyGW();
            }
        }
        if (Type.substr(0,6) == "SET-HR")
        {
            cin >> S >> P;
            if (S > 128 || P > 128)
            {
                cout << "error" << endl;
            }
            else {
                if (MyGW.handy_rack.Rindex == 0)
                {
                    MyGW.handy_rack.Rindex = S;
                    for (int j = 0; j < S; j++)
                    {
                        MyGW.handy_rack.shelves[j].Sindex = P;
                        for (int i = 0; i < P; i++)
                        {
                            MyGW.handy_rack.shelves[j].places[i].goods = 0;
                            MyGW.handy_rack.shelves[j].places[i].label[0] = '\0';
                            MyGW.handy_rack.shelves[j].places[i].label[1] = '\0';
                        }
                    }
                } else {
                    if (MyGW.handy_rack.Rindex > S)
                    {
                        for (int k = S; k < MyGW.handy_rack.Rindex; k++)
                        {
                            for (int l = 0; l < MyGW.handy_rack.shelves[k].Sindex; l++)
                            {
                                sumE -= MyGW.handy_rack.shelves[k].places[l].goods;
                            }
                        }
                        MyGW.handy_rack.Rindex = S;
                        for (int j = 0; j < S; j++)
                        {
                            if (MyGW.handy_rack.shelves[j].Sindex < P) {
                                for (int i = MyGW.handy_rack.shelves[j].Sindex; i < P; i++)
                                {
                                    MyGW.handy_rack.shelves[j].places[i].goods = 0;
                                    MyGW.handy_rack.shelves[j].places[i].label[0] = '\0';
                                    MyGW.handy_rack.shelves[j].places[i].label[1] = '\0';
                                }
                                MyGW.handy_rack.shelves[j].Sindex = P;
                            } else {

                                    for (int l = P; l < MyGW.handy_rack.shelves[j].Sindex; l++)
                                    {
                                        sumE -= MyGW.handy_rack.shelves[j].places[l].goods;
                                    }
                                MyGW.handy_rack.shelves[j].Sindex = P;
                            }
                        }
                    }
                    if (MyGW.handy_rack.Rindex < S)
                    {
                        for (int j = 0; j < MyGW.handy_rack.Rindex; j++) {
                            if (MyGW.handy_rack.shelves[j].Sindex < P) {
                                for (int i = MyGW.handy_rack.shelves[j].Sindex; i < P; i++)
                                {
                                    MyGW.handy_rack.shelves[j].places[i].goods = 0;
                                    MyGW.handy_rack.shelves[j].places[i].label[0] = '\0';
                                    MyGW.handy_rack.shelves[j].places[i].label[1] = '\0';
                                }
                                MyGW.handy_rack.shelves[j].Sindex = P;
                            } else {
                                for (int l = P; l < MyGW.handy_rack.shelves[j].Sindex; l++)
                                {
                                    sumE -= MyGW.handy_rack.shelves[j].places[l].goods;
                                }
                                MyGW.handy_rack.shelves[j].Sindex = P;
                            }
                        }

                        for (int j = MyGW.handy_rack.Rindex; j < S; j++)
                        {
                            for (int i = 0; i < P; i++)
                            {
                                MyGW.handy_rack.shelves[j].places[i].goods = 0;
                                MyGW.handy_rack.shelves[j].places[i].label[0] = '\0';
                                MyGW.handy_rack.shelves[j].places[i].label[1] = '\0';
                            }
                            MyGW.handy_rack.shelves[j].Sindex = P;
                        }
                        MyGW.handy_rack.Rindex = S;
                    }
                }
                // //printmyGW();
            }
        }
        if (Type.substr(0,6) == "SET-HS")
        {
            cin >> P;
            if (P > 128)
            {
                cout << "error" << endl;
            }
            else {
                if (MyGW.handy_shelf.Sindex == 0)
                {
                    MyGW.handy_shelf.Sindex = P;
                    for (int i = 0; i < P; i++)
                    {
                        MyGW.handy_shelf.places[i].goods = 0;
                        MyGW.handy_shelf.places[i].label[0] = '\0';
                        MyGW.handy_shelf.places[i].label[1] = '\0';
                    }
                }
                if (MyGW.handy_shelf.Sindex > P)
                {
                    for (int i = P; i < MyGW.handy_shelf.Sindex; i++)
                    {
                        sumE -= MyGW.handy_shelf.places[i].goods;
                    }
                    MyGW.handy_shelf.Sindex = P;
                }
                if (MyGW.handy_shelf.Sindex < P)
                {
                    for (int i = MyGW.handy_shelf.Sindex; i < P; i++)
                    {
                        MyGW.handy_shelf.places[i].goods = 0;
                        MyGW.handy_shelf.places[i].label[0] = '\0';
                        MyGW.handy_shelf.places[i].label[1] = '\0';
                    }
                    MyGW.handy_shelf.Sindex = P;
                }
                //printmyGW();
            }
        }
        if (Type.substr(0,6) == "PUT-W")
        {
            cin >> w >> r >> s >> p >> A;
            if (w > MyGW.Gindex-1 || r > MyGW.warehouses[w].Windex-1 || s > MyGW.warehouses[w].racks[r].Rindex-1 || p > MyGW.warehouses[w].racks[r].shelves[s].Sindex-1 || A > 65535)
            {
                cout << "error" << endl;
            }
            else {
                //PUTW(w, r, s, p, A);
                long temp = MyGW.warehouses[w].racks[r].shelves[s].places[p].goods + A;
                if (temp > 65535)
                {
                    A = 65535 - MyGW.warehouses[w].racks[r].shelves[s].places[p].goods;
                    MyGW.warehouses[w].racks[r].shelves[s].places[p].goods += A;
                }
                else MyGW.warehouses[w].racks[r].shelves[s].places[p].goods += A;
                //printmyGW();
                sumE += A;
            }
        }
        if (Type.substr(0,6) == "PUT-H")
        {
            cin >> w >> p >> A;
            if (w > MyGW.Gindex-1 || p > MyGW.warehouses[w].handy_shelf.Sindex-1 || A > 65535)
            {
                cout << "error" << endl;
            } else {
                long temp = MyGW.warehouses[w].handy_shelf.places[p].goods + A;
                if (temp > 65535)
                {
                    A = 65535 - MyGW.warehouses[w].handy_shelf.places[p].goods;
                    MyGW.warehouses[w].handy_shelf.places[p].goods += A;
                }
                else MyGW.warehouses[w].handy_shelf.places[p].goods += A;
                // //printmyGW();
                sumE += A;
            }
        }
        if (Type.substr(0,6) == "PUT-R")
        {
            cin >> s >> p >> A;
            if (s > MyGW.handy_rack.Rindex-1 || p > MyGW.handy_rack.shelves[s].Sindex-1 || A > 65535)
            {
                cout << "error" << endl;
            } else {
                long temp = MyGW.handy_rack.shelves[s].places[p].goods + A;
                if (temp > 65535)
                {
                    A = 65535 - MyGW.handy_rack.shelves[s].places[p].goods;
                    MyGW.handy_rack.shelves[s].places[p].goods += A;
                }
                else MyGW.handy_rack.shelves[s].places[p].goods += A;
                // //printmyGW();
                sumE += A;
            }
        }
        if (Type.substr(0,6) == "PUT-S")
        {
            cin >> p >> A;
            if (p > MyGW.handy_shelf.Sindex-1 || A > 65535)
            {
                cout << "error" << endl;
            } else {
                long temp = MyGW.handy_shelf.places[p].goods + A;
                if (temp > 65535)
                {
                    A = 65535 - MyGW.handy_shelf.places[p].goods;
                    MyGW.handy_shelf.places[p].goods += A;
                }
                else MyGW.handy_shelf.places[p].goods += A;
                //printmyGW();
                sumE += A;
            }
        }
        if (Type.substr(0,4) == "FILL")
        {
            sumE = 0;
            cin >> W >> R >> S >> P >> A;
            if (W > 128 || R > 128 || S > 128 || P > 128 || A > 65535)
            {
                cout << "error";
            }
            else {

                MyGW.Gindex = W;
                for (int i = 0; i < MyGW.Gindex; i++) {
                    MyGW.warehouses[i].Windex = R;
                    //  cout << MyGW.warehouses[i].Windex;
                    for (int j = 0; j < MyGW.warehouses[i].Windex; j++) {
                        MyGW.warehouses[i].racks[j].Rindex = S;
                        for (int k = 0; k < MyGW.warehouses[i].racks[j].Rindex; k++) {
                            MyGW.warehouses[i].racks[j].shelves[k].Sindex = P;
                            for (int l = 0; l < MyGW.warehouses[i].racks[j].shelves[k].Sindex; l++) {
                                MyGW.warehouses[i].racks[j].shelves[k].places[l].goods = A;
                                MyGW.warehouses[i].racks[j].shelves[k].places[l].label[0] = '\0';
                                MyGW.warehouses[i].racks[j].shelves[k].places[l].label[1] = '\0';
                                sumE +=  MyGW.warehouses[i].racks[j].shelves[k].places[l].goods;
                            }
                        }
                    }
                }
            }
            MyGW.handy_shelf.Sindex = P;
            for (int i = 0; i < MyGW.handy_shelf.Sindex; i++)
            {
                MyGW.handy_shelf.places[i].goods = A;
                MyGW.handy_shelf.places[i].label[0] = '\0';
                MyGW.handy_shelf.places[i].label[1] = '\0';
                sumE +=  MyGW.handy_shelf.places[i].goods;
            }
            MyGW.handy_rack.Rindex = S;
            for (int i = 0; i < MyGW.handy_rack.Rindex; i++)
            {
                MyGW.handy_rack.shelves[i].Sindex = P;
                for (int j = 0; j < MyGW.handy_rack.shelves[i].Sindex; j++)
                {
                    MyGW.handy_rack.shelves[i].places[j].goods = A;
                    MyGW.handy_rack.shelves[i].places[j].label[0] = '\0';
                    MyGW.handy_rack.shelves[i].places[j].label[1] = '\0';
                    sumE += MyGW.handy_rack.shelves[i].places[j].goods;
                }
            }

            for (int i = 0; i < MyGW.Gindex; i++)
            {
                MyGW.warehouses[i].handy_shelf.Sindex = P;
                for (int j = 0; j < MyGW.warehouses[i].handy_shelf.Sindex; j++)
                {
                    MyGW.warehouses[i].handy_shelf.places[j].goods = A;
                    sumE += MyGW.warehouses[i].handy_shelf.places[j].goods;
                }
            }
            //printmyGW();
        }
        if (Type.substr(0,6) == "POP-W")
        {
            cin >> w >> r >> s >> p >> A;
            if (w > MyGW.Gindex-1 || r > MyGW.warehouses[w].Windex-1 || s > MyGW.warehouses[w].racks[r].Rindex-1 || p > MyGW.warehouses[w].racks[r].shelves[s].Sindex-1 || A > 65535)
            {
                cout << "error" << endl;
            } else {
                //POPW(w, r, s, p, A);
                int temp = MyGW.warehouses[w].racks[r].shelves[s].places[p].goods - A;
                if (temp < 0)
                {
                    A = MyGW.warehouses[w].racks[r].shelves[s].places[p].goods;
                    MyGW.warehouses[w].racks[r].shelves[s].places[p].goods -= A;
                }
                else MyGW.warehouses[w].racks[r].shelves[s].places[p].goods -= A;
                //printmyGW();
                sumE -=A;
            }
        }
        if (Type.substr(0,6) == "POP-H")
        {
            cin >> w >> p >> A;
            if (w > MyGW.Gindex-1 || p > MyGW.warehouses[w].handy_shelf.Sindex-1 || A > 65535)
            {
                cout << "error" << endl;
            } else {
                int temp = MyGW.warehouses[w].handy_shelf.places[p].goods - A;
                if (temp < 0)
                {
                    A = MyGW.warehouses[w].handy_shelf.places[p].goods;
                    MyGW.warehouses[w].handy_shelf.places[p].goods -= A;
                }
                else MyGW.warehouses[w].handy_shelf.places[p].goods -= A;
                //printmyGW();
                sumE -=A;
            }
        }
        if (Type.substr(0,6) == "POP-R")
        {
            cin >> s >> p >> A;
            if (s > MyGW.handy_rack.Rindex-1 || p > MyGW.handy_rack.shelves[s].Sindex-1 || A > 65535)
            {
                cout << "error" << endl;
            } else {
                //POPR(s, p, A);
                int temp = MyGW.handy_rack.shelves[s].places[p].goods - A;
                if (temp < 0)
                {
                    A = MyGW.handy_rack.shelves[s].places[p].goods;
                    MyGW.handy_rack.shelves[s].places[p].goods -= A;
                } else MyGW.handy_rack.shelves[s].places[p].goods -= A;
                //printmyGW();
                sumE -=A;
            }
        }
        if (Type.substr(0,6) == "POP-S")
        {
            cin >> p >> A;
            if (p > MyGW.handy_shelf.Sindex-1 || A > 65535)
            {
                cout << "error" << endl;
            } else {
                //POPS(p, A);
                int temp = MyGW.handy_shelf.places[p].goods - A;
                if (temp < 0)
                {
                    A = MyGW.handy_shelf.places[p].goods;
                    MyGW.handy_shelf.places[p].goods -= A;

                }
                else MyGW.handy_shelf.places[p].goods -= A;
                //printmyGW();
                sumE -=A;
            }
        }
        if (Type.substr(0,6) == "MOV-W")
        {
            cin >> wb >> rb >> sb >> we >> re >> se >> p >>A;
            if (wb > MyGW.Gindex-1 || rb > MyGW.warehouses[wb].Windex-1 || sb > MyGW.warehouses[wb].racks[rb].Rindex-1 ||
                we > MyGW.Gindex-1 || re > MyGW.warehouses[we].Windex-1 || se > MyGW.warehouses[we].racks[re].Rindex-1 ||
                p > MyGW.warehouses[wb].racks[rb].shelves[sb].Sindex-1 || p > MyGW.warehouses[we].racks[re].shelves[se].Sindex || A > 65535)
            {
                cout << "error" << endl;
            } else {
                //MOVW(wb, rb, sb, we, re, se, p, A);
                if (MyGW.warehouses[wb].racks[rb].shelves[sb].places[p].goods < A) {
                    A = MyGW.warehouses[wb].racks[rb].shelves[sb].places[p].goods;

                    if (MyGW.warehouses[we].racks[re].shelves[se].places[p].goods + A > 65535) {
                        A = 65535 - MyGW.warehouses[we].racks[re].shelves[se].places[p].goods;
                    }
                }
                if (MyGW.warehouses[wb].racks[rb].shelves[sb].places[p].goods > A)
                {

                    if ( MyGW.warehouses[we].racks[re].shelves[se].places[p].goods + A > 65535)
                    {
                        A = 65535 - MyGW.warehouses[we].racks[re].shelves[se].places[p].goods;
                    }
                }
                MyGW.warehouses[wb].racks[rb].shelves[sb].places[p].goods -= A;
                MyGW.warehouses[we].racks[re].shelves[se].places[p].goods += A;
                //printmyGW();
            }
        }
        if (Type.substr(0,6) == "MOV-H")
        {
            cin >> w >> r >> s >> p >> A;
            if (w > MyGW.Gindex-1 || r > MyGW.warehouses[w].Windex-1 || s > MyGW.warehouses[w].racks[r].Rindex-1 ||
                p > MyGW.warehouses[w].racks[r].shelves[s].Sindex-1 || p > MyGW.handy_shelf.Sindex-1 || A > 65535)
            {
                cout << "error" << endl;
            } else {
                //MOVH(w, r, s, p, A);
                if (MyGW.warehouses[w].racks[r].shelves[s].places[p].goods < A)
                {
                    A = MyGW.warehouses[w].racks[r].shelves[s].places[p].goods;
                }
                if (MyGW.warehouses[w].handy_shelf.places[p].goods + A > 65535)
                {
                    A = 65535 - MyGW.warehouses[w].handy_shelf.places[p].goods;
                }
                MyGW.warehouses[w].racks[r].shelves[s].places[p].goods -= A;
                MyGW.warehouses[w].handy_shelf.places[p].goods += A;
                //printmyGW();
            }
        }
        if (Type.substr(0,6) == "MOV-R")
        {
            cin >> w >> r >> sb >> se >> p >> A;
            if (w > MyGW.Gindex-1 || r > MyGW.warehouses[w].Windex-1 || sb > MyGW.warehouses[w].racks[r].Rindex-1 ||
                se > MyGW.handy_rack.Rindex-1 || p > MyGW.warehouses[w].racks[r].shelves[sb].Sindex-1 || p > MyGW.handy_rack.shelves[se].Sindex-1 || A > 65535)
            {
                cout << "error" << endl;
            } else {
                //MOVR(w, r, sb, se, p, A);
                if (MyGW.warehouses[w].racks[r].shelves[sb].places[p].goods < A)
                {
                    A = MyGW.warehouses[w].racks[r].shelves[sb].places[p].goods;
                }
                if (MyGW.handy_rack.shelves[se].places[p].goods + A > 65535)
                {
                    A = 65535 - MyGW.handy_rack.shelves[se].places[p].goods;
                }
                MyGW.warehouses[w].racks[r].shelves[sb].places[p].goods -= A;
                MyGW.handy_rack.shelves[se].places[p].goods  += A;
                //printmyGW();
            }
        }
        if (Type.substr(0,6) == "MOV-S")
        {
            cin >> s >> p >> A;
            if (s > MyGW.handy_rack.Rindex-1 || p > MyGW.handy_rack.shelves[s].Sindex-1 || p > MyGW.handy_shelf.Sindex-1 || A > 65535)
            {
                cout << "error" << endl;
            } else {
                //MOVS(s, p, A);
                if (MyGW.handy_rack.shelves[s].places[p].goods < A)
                {
                    A = MyGW.handy_rack.shelves[s].places[p].goods;
                }
                if (MyGW.handy_shelf.places[p].goods + A > 65535)
                {
                    A = 65535 - MyGW.handy_shelf.places[p].goods;
                }
                MyGW.handy_rack.shelves[s].places[p].goods -= A;
                MyGW.handy_shelf.places[p].goods += A;
                //printmyGW();
            }
        }
        if (Type.substr(0,6) == "GET-E")
        {
            cout << sumE << endl;
//            unsigned long long int sum = 0;
//            for (int i = 0; i < MyGW.Gindex; i ++)
//            {
//                for (int j = 0; j < MyGW.warehouses[i].Windex; j++)
//                {
//                    for (int k = 0; k < MyGW.warehouses[i].racks[j].Rindex; k++)
//                    {
//                        for (int l = 0; l < MyGW.warehouses[i].racks[j].shelves[k].Sindex; l++)
//                        {
//                            sum +=  MyGW.warehouses[i].racks[j].shelves[k].places[l].goods;
//                        }
//                    }
//                }
//            }
//            for (int i = 0; i < MyGW.handy_shelf.Sindex; i++)
//            {
//                sum += MyGW.handy_shelf.places[i].goods;
//            }
//            for (int i = 0; i < MyGW.handy_rack.Rindex; i++)
//            {
//                for (int j = 0; j < MyGW.handy_rack.shelves[i].Sindex; j++)
//                {
//                    sum += MyGW.handy_rack.shelves[i].places[j].goods;
//                }
//            }
//            for (int i = 0; i < MyGW.Gindex; i++)
//            {
//                for (int j = 0; j < MyGW.warehouses[i].handy_shelf.Sindex; j++)
//                {
//                    sum +=MyGW.warehouses[i].handy_shelf.places[j].goods;
//                }
//            }
//            cout << sum << endl;
//            sum = 0;
//            // //printmyGW();
        }

        if (Type.substr(0,6) == "GET-W")
        {
            unsigned long long int sumW = 0;
            cin >> w;
            if (w > MyGW.Gindex-1)
            {
                cout << "error" << endl;
            } else {

                for (int i = 0; i < MyGW.warehouses[w].Windex; i++) {
                    for (int j = 0; j < MyGW.warehouses[w].racks[i].Rindex; j++) {
                        for (int k = 0; k < MyGW.warehouses[w].racks[i].shelves[j].Sindex; k++) {
                            sumW += MyGW.warehouses[w].racks[i].shelves[j].places[k].goods;
                        }
                    }
                }
                for (int i = 0; i < MyGW.warehouses[w].handy_shelf.Sindex; i++) {
                    sumW += MyGW.warehouses[w].handy_shelf.places[i].goods;
                }
                cout << sumW << endl;
            }
            //    //printmyGW();
        }
        if (Type.substr(0,6) == "GET-RW")
        {
            unsigned long long int sumRW = 0;
            cin >> w >> r;
            if (w > MyGW.Gindex-1 || r > MyGW.warehouses[w].Windex -1)
            {
                cout << "error" << endl;
            } else {
                for (int i = 0; i < MyGW.warehouses[w].racks[r].Rindex; i++) {
                    for (int j = 0; j < MyGW.warehouses[w].racks[r].shelves[i].Sindex; j++) {
                        sumRW += MyGW.warehouses[w].racks[r].shelves[i].places[j].goods;
                    }
                }
                cout << sumRW << endl;
            }
            //  //printmyGW();
        }
        if (Type.substr(0,6) == "GET-RH")
        {
            unsigned long long int sumRH = 0;
            for (int i = 0; i < MyGW.handy_rack.Rindex; i++)
            {
                for (int j = 0; j < MyGW.handy_rack.shelves[i].Sindex; j++)
                {
                    sumRH += MyGW.handy_rack.shelves[i].places[j].goods;
                }
            }
            cout << sumRH << endl;
            //printmyGW();
        }
        if (Type.substr(0,6) == "GET-SW")
        {
            unsigned long long int sumSW = 0;
            cin >> w >> r >> s;
            if (w > MyGW.Gindex-1 || r > MyGW.warehouses[w].Windex -1 || s > MyGW.warehouses[w].racks[r].Rindex-1)
            {
                cout << "error" << endl;
            } else {

                for (int i = 0; i < MyGW.warehouses[w].racks[r].shelves[s].Sindex; i++) {
                    sumSW += MyGW.warehouses[w].racks[r].shelves[s].places[i].goods;
                }
                cout << sumSW << endl;
            }
            //printmyGW();
        }
        if (Type.substr(0,6) == "GET-SH")
        {
            unsigned long long int sumSH = 0;
            cin >> w;
            if (w > MyGW.Gindex-1)
            {
                cout << "error" << endl;
            } else {
                for (int i = 0; i < MyGW.warehouses[w].handy_shelf.Sindex; i++) {
                    sumSH += MyGW.warehouses[w].handy_shelf.places[i].goods;
                }
                cout << sumSH << endl;
            }
            //printmyGW();
        }
        if (Type.substr(0,6) == "GET-SR")
        {
            unsigned long long int sumSR = 0;
            cin >> s;
            if (s > MyGW.handy_rack.Rindex-1)
            {
                cout << "error" << endl;
            } else {
                for (int i = 0; i < MyGW.handy_rack.shelves[s].Sindex; i++) {
                    sumSR += MyGW.handy_rack.shelves[s].places[i].goods;
                }
                cout << sumSR << endl;
            }
            //printmyGW();
        }
        if (Type.substr(0,6) == "GET-S")
        {
            unsigned long long int sumS = 0;
            for (int i = 0; i < MyGW.handy_shelf.Sindex; i++)
            {
                sumS += MyGW.handy_shelf.places[i].goods;
            }
            cout << sumS << endl;
            //printmyGW();
        }
        if (Type.substr(0,6) == "SET-LW")
        {
            cin >> w >> r >> s >> p >> d1 >> d2;
            if (w > MyGW.Gindex-1 || r > MyGW.warehouses[w].Windex-1 || s > MyGW.warehouses[w].racks[r].Rindex-1 || p > MyGW.warehouses[w].racks[r].shelves[s].Sindex-1)
            {
                cout << "error" << endl;
            }
            else {
                MyGW.warehouses[w].racks[r].shelves[s].places[p].label[0] = d1;
                MyGW.warehouses[w].racks[r].shelves[s].places[p].label[1] = d2;
                //printmyGW();
            }
        }
        if (Type.substr(0,6) == "SET-LH")
        {
            cin >> w >> p >> d1 >> d2;
            if (w > MyGW.Gindex-1 || p > MyGW.warehouses[w].handy_shelf.Sindex-1)
            {
                cout << "error" << endl;
            } else {
                MyGW.warehouses[w].handy_shelf.places[p].label[0] = d1;
                MyGW.warehouses[w].handy_shelf.places[p].label[1] = d2;
//                //printmyGW();
            }
        }
        if (Type.substr(0,6) == "SET-LR")
        {
            cin >> s >> p >> d1 >> d2;
            if (s > MyGW.handy_rack.Rindex-1 || p > MyGW.handy_rack.shelves[s].Sindex-1)
            {
                cout << "error" << endl;
            } else {
                MyGW.handy_rack.shelves[s].places[p].label[0] = d1;
                MyGW.handy_rack.shelves[s].places[p].label[1] = d2;
                //printmyGW();
            }
        }
        if (Type.substr(0,6) == "SET-LS")
        {
            cin >> p >> d1 >> d2;
            if (p > MyGW.handy_shelf.Sindex-1)
            {
                cout << "error" << endl;
            } else {
                MyGW.handy_shelf.places[p].label[0] = d1;
                MyGW.handy_shelf.places[p].label[1] = d2;
                //printmyGW();
            }
        }
        if (Type.substr(0,6) == "GET-LW")
        {
            cin >> w >> r >> s >> p;
            if (w > MyGW.Gindex-1 || r > MyGW.warehouses[w].Windex-1 || s > MyGW.warehouses[w].racks[r].Rindex-1 || p > MyGW.warehouses[w].racks[r].shelves[s].Sindex-1)
            {
                cout << "error" << endl;
            } else {
                if ( MyGW.warehouses[w].racks[r].shelves[s].places[p].label[0] != '\0' && MyGW.warehouses[w].racks[r].shelves[s].places[p].label[1] != '\0') {
                    cout << MyGW.warehouses[w].racks[r].shelves[s].places[p].label[0]
                         << MyGW.warehouses[w].racks[r].shelves[s].places[p].label[1] << endl;
                }
                else cout << "--" << endl;
            }
            //printmyGW();
        }
        if (Type.substr(0,6) == "GET-LH")
        {
            cin >> w >> p;
            if (w > MyGW.Gindex-1 || p > MyGW.warehouses[w].handy_shelf.Sindex-1)
            {
                cout << "error" << endl;
            } else {
                if (MyGW.warehouses[w].handy_shelf.places[p].label[0] != '\0' && MyGW.warehouses[w].handy_shelf.places[p].label[1] != '\0') {
                    cout << MyGW.warehouses[w].handy_shelf.places[p].label[0]
                         << MyGW.warehouses[w].handy_shelf.places[p].label[1] << endl;
                }
                else cout << "--" << endl;
            }
            //printmyGW();
        }
        if (Type.substr(0,6) == "GET-LR")
        {
            cin >> s >> p;
            if (s > MyGW.handy_rack.Rindex-1 || p > MyGW.handy_rack.shelves[s].Sindex-1)
            {
                cout << "error" << endl;
            } else {
                if (MyGW.handy_rack.shelves[s].places[p].label[0] != '\0' && MyGW.handy_rack.shelves[s].places[p].label[1] != '\0') {
                    cout << MyGW.handy_rack.shelves[s].places[p].label[0]
                         << MyGW.handy_rack.shelves[s].places[p].label[1]
                         << endl;
                }
                else cout << "--" << endl;
            }
            // //printmyGW();
        }
        if (Type.substr(0,6) == "GET-LS")
        {
            cin >> p;
            if (p > MyGW.handy_shelf.Sindex-1)
            {
                cout << "error" << endl;
            } else {
                if (MyGW.handy_shelf.places[p].label[0] != '\0' && MyGW.handy_shelf.places[p].label[1] != '\0') {
                    cout << MyGW.handy_shelf.places[p].label[0] << MyGW.handy_shelf.places[p].label[1] << endl;
                }
                else cout << "--" << endl;
            }
            // //printmyGW();
        }

        Type = "";
        cin >> Type;
    }

}