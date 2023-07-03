#include <iostream>
#include <deque>
#include <list>

using namespace std;

class Process
{
public:
    string namaProses;
    int waktuBurst;
    int waktuKedatangan;

    int waktuMenunggu;
    int waktuSelesai;
    int waktuDieksekusi;
    int waktuTurnAround;

    int waktuBurstTersisa;

    void initialize()
    {
        waktuMenunggu = 0;
        waktuDieksekusi = 0;
        waktuTurnAround = 0;
        waktuBurstTersisa = waktuBurst;
    }
};

class GantChart
{
public:
    string namaProses;
    int waktuDieksekusi;
};

int main()
{
    int banyakProses;
    int timeQuantum;
    int waktuSaatIni = 0;

    cout << "\nMasukkan time quantum: ";
    cin >> timeQuantum;

    cout << "Masukkan banyaknya proses: ";
    cin >> banyakProses;

    Process daftarProses[banyakProses];

    for (int n = 0; n < banyakProses; n++)
    {
        cout << "== Proses " << (n + 1) << " ==\n";
        cout << "Huruf proses: ";
        cin >> daftarProses[n].namaProses;
        cout << "Waktu datang: ";
        cin >> daftarProses[n].waktuKedatangan;
        cout << "Waktu Burst: ";
        cin >> daftarProses[n].waktuBurst;
        cout << "=================\n";

        daftarProses[n].initialize();
    }

    cout << "\n"
         << endl;

    for (int i = 0; i < banyakProses - 1; i++)
    {
        for (int j = i + 1; j < banyakProses; j++)
        {
            if (daftarProses[j].waktuKedatangan < daftarProses[i].waktuKedatangan)
            {
                Process temp = daftarProses[j];
                daftarProses[j] = daftarProses[i];
                daftarProses[i] = temp;
            }
        }
    }

    deque<Process> antrian;
    deque<Process> selesai;

    list<GantChart> gc;

    antrian.push_back(daftarProses[0]);

    waktuSaatIni = daftarProses[0].waktuKedatangan;
    int sisaProses = banyakProses;

    int i = 1;
    while (sisaProses > 0)
    {
        if (!antrian.empty())
        {
            GantChart temp;
            temp.namaProses = antrian.front().namaProses;
            temp.waktuDieksekusi = waktuSaatIni;

            gc.push_back(temp);

            if (antrian.front().waktuBurstTersisa == antrian.front().waktuBurst)
            {
                antrian.front().waktuDieksekusi = waktuSaatIni;
            }

            if (antrian.front().waktuBurstTersisa <= timeQuantum)
            {
                waktuSaatIni += antrian.front().waktuBurstTersisa;
                antrian.front().waktuSelesai = waktuSaatIni;
                antrian.front().waktuBurstTersisa = 0;

                for (int j = i; j < banyakProses; j++)
                {
                    if (daftarProses[j].waktuKedatangan <= waktuSaatIni)
                    {
                        antrian.push_back(daftarProses[j]);
                        i++;
                    }
                }

                sisaProses--;

                selesai.push_back(antrian.front());
            }
            else
            {
                waktuSaatIni += timeQuantum;
                antrian.front().waktuBurstTersisa -= timeQuantum;
                for (int j = i; j < banyakProses; j++)
                {
                    if (daftarProses[j].waktuKedatangan <= waktuSaatIni)
                    {
                        antrian.push_back(daftarProses[j]);
                        i++;
                    }
                }
                antrian.push_back(antrian.front());
            }

            antrian.pop_front();
        }
        else
        {
            waktuSaatIni++;
            for (int j = i; j < banyakProses; j++)
            {
                if (daftarProses[j].waktuKedatangan <= waktuSaatIni)
                {
                    antrian.push_back(daftarProses[j]);
                    i++;
                }
            }
        }
    }

    // Memasukkan objek penutup Gantt Chart ke dalam list Gantt Chart
    GantChart temp;
    temp.namaProses = "-";               // Nama proses dinamakan "-" artinya tidak ada proses lagi yang harus dikerjakan
    temp.waktuDieksekusi = waktuSaatIni; // Waktu Dieksekusi pada objek penutup Gantt Chart menandakan waktu berakhirnya seluruh proses diekseksui
    gc.push_back(temp);

    double rerataWaktuTurnAround = 0.0, rerataWaktuMenunggu = 0.0;

    cout << "=> Gant Chart <=" << endl;

    for (list<GantChart>::iterator it = gc.begin(); it != gc.end(); it++)
    {
        if (it == gc.begin())
        {
            cout << it->waktuDieksekusi;
        }
        else
        {
            if (it->waktuDieksekusi < 10)
            {
                for (int l = 0; l < 10; l++)
                {
                    cout << " ";
                }
                cout << it->waktuDieksekusi;
            }
            else
            {
                for (int l = 0; l < 9; l++)
                {
                    cout << " ";
                }
                cout << it->waktuDieksekusi;
            }
        }
    }
    cout << endl;
    for (list<GantChart>::iterator it = gc.begin(); it != gc.end(); it++)
    {
        if (it->namaProses != "-")
        {
            cout << "+---------+";
        }
    }
    cout << endl;
    for (list<GantChart>::iterator it = gc.begin(); it != gc.end(); it++)
    {
        if (it->namaProses != "-")
        {
            cout << "|    " << it->namaProses << "    |";
        }
    }
    cout << endl;
    for (list<GantChart>::iterator it = gc.begin(); it != gc.end(); it++)
    {
        if (it->namaProses != "-")
        {
            cout << "+---------+";
        }
    }
    cout << endl
         << endl;
    cout << "+-------------+---------+----------+-------+-----------+------------+---------+\n";
    cout << "| Nama Proses | Arrival | Response | Burst | Completed | TurnAround | Waiting |\n";
    cout << "+-------------+---------+----------+-------+-----------+------------+---------+\n";

    deque<Process>::iterator it;
    for (it = selesai.begin(); it != selesai.end(); ++it)
    {
        it->waktuTurnAround = it->waktuSelesai - it->waktuKedatangan;
        it->waktuMenunggu = it->waktuTurnAround - it->waktuBurst;

        rerataWaktuTurnAround += it->waktuTurnAround;
        rerataWaktuMenunggu += it->waktuMenunggu;

        cout << "|      " << it->namaProses << "      |";
        if (it->waktuKedatangan < 10)
        {
            cout << "    " << it->waktuKedatangan << "    |";
        }
        else
        {
            cout << "   " << it->waktuKedatangan << "    |";
        }
        if (it->waktuDieksekusi < 10)
        {
            cout << "     " << it->waktuDieksekusi << "    |";
        }
        else
        {
            cout << "    " << it->waktuDieksekusi << "    |";
        }
        if (it->waktuBurst < 10)
        {
            cout << "   " << it->waktuBurst << "   |";
        }
        else
        {
            cout << "  " << it->waktuBurst << "   |";
        }

        if (it->waktuSelesai < 10)
        {
            cout << "     " << it->waktuSelesai << "     |";
        }
        else
        {
            cout << "    " << it->waktuSelesai << "     |";
        }

        if (it->waktuTurnAround < 10)
        {
            cout << "      " << it->waktuTurnAround << "     |";
        }
        else
        {
            cout << "     " << it->waktuTurnAround << "     |";
        }

        if (it->waktuMenunggu < 10)
        {
            cout << "    " << it->waktuMenunggu << "    |";
        }
        else
        {
            cout << "   " << it->waktuMenunggu << "    |";
        }
        cout << endl;
    }

    cout << "+-------------+---------+----------+-------+-----------+------------+---------+\n";

    cout << endl;

    rerataWaktuTurnAround /= banyakProses;
    rerataWaktuMenunggu /= banyakProses;

    cout << "=> Rata-rata Waktu Turn Around : "
         << rerataWaktuTurnAround << endl;
    cout << "=> Rata-rata Waktu Menunggu : "
         << rerataWaktuMenunggu << endl;

    return 0;
}

/* daftar test case

tc 1 (urut, sibuk)

3
5
A 0 4
B 2 3
C 4 8
D 7 1
E 10 2

tc 2 (tidak urut, sibuk)

3
5
A 6 4
B 11 3
C 3 8
D 1 1
E 2 2

tc 3 (tidak urut, tidak sibuk)

3
5
A 6 4
B 11 3
C 3 8
D 0 1
E 2 2

*/
