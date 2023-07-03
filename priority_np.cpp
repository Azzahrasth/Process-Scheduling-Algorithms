#include <iostream>
#include <limits>
#include <list>

using namespace std;

class Process
{
public:
    string namaProses;
    int waktuKedatangan;
    int waktuBurst;
    int prioritas;

    int waktuTersisa;

    int waktuDieksekusi;
    int waktuSelesai;

    int waktuMenunggu;
    int waktuTurnAround;

    void initialize()
    {
        waktuTersisa = waktuBurst;
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
    cout << "Masukkan banyaknya proses: ";

    // input jumlah sproses
    cin >> banyakProses;

    // list untuk menyimpan gant chart
    list<GantChart> gc;

    // masukkan proses ke array sesuai jumlah proses
    Process arrProses[banyakProses];

    // input nama, waktu kedatangan, waktu burst, dan prioritas sebanyak jumlah proses
    for (int n = 0; n < banyakProses; n++)
    {
        cout << "== Proses " << (n + 1) << " ==\n";
        cout << "Huruf proses   : ";
        cin >> arrProses[n].namaProses;
        cout << "Waktu datang   : ";
        cin >> arrProses[n].waktuKedatangan;
        cout << "Waktu Burst    : ";
        cin >> arrProses[n].waktuBurst;
        cout << "Prioritas      : ";
        cin >> arrProses[n].prioritas;
        cout << "=================\n";

        arrProses[n].initialize();
    }

    cout << "\n"
         << endl;

    // mengurutkan proses sesuai waktu kedatangannya
    for (int i = 0; i < banyakProses - 1; i++)
    {
        for (int j = i + 1; j < banyakProses; j++)
        {
            if (arrProses[j].waktuKedatangan < arrProses[i].waktuKedatangan)
            {
                Process temp = arrProses[j];
                arrProses[j] = arrProses[i];
                arrProses[i] = temp;
            }
        }
    }

    // waktu saat ini di set dengan proses yang waktu kedatangannya paling awal
    int waktuSaatIni = arrProses[0].waktuKedatangan;

    int tempIndex = -1;
    while (true)
    {
        // index prioritas saat ini
        int currentHighestprioritasIndex = -1;

        // prioritas saat ini diinisialisasi dengan nilai maksimum
        int currentHighestprioritas = numeric_limits<int>::max();

        // penanda jika semua array telah selesai diproses
        bool isAllCompleted = true;

        for (int i = 0; i < banyakProses; i++)
        {
            // jika proses belum selesai
            if (arrProses[i].waktuTersisa > 0)
            {
                // tandai false
                isAllCompleted = false;

                // jika waktu kedatangannya lebih kecil atau adalah waktu saat ini
                if (arrProses[i].waktuKedatangan <= waktuSaatIni)
                {
                    // jika prioritasnya lebih besar dari prioritas saat ini
                    if (arrProses[i].prioritas < currentHighestprioritas)
                    {
                        // update nilai prioritas saat ini
                        currentHighestprioritas = arrProses[i].prioritas;

                        // tandai indexnya
                        currentHighestprioritasIndex = i;
                    }
                }
            }
        }

        // jika proses selesai
        if (isAllCompleted)
        {
            GantChart gantChart;
            gantChart.namaProses = "-"; // artinya proses selesai
            gantChart.waktuDieksekusi = waktuSaatIni;
            // tambahkan gantChart ke dalam list
            gc.push_back(gantChart);
            break;
        }

        // jika terjadi pergantian proses
        if (tempIndex != currentHighestprioritasIndex)
        {
            tempIndex = currentHighestprioritasIndex;
            GantChart gantChart;
            gantChart.namaProses = arrProses[currentHighestprioritasIndex].namaProses;
            gantChart.waktuDieksekusi = waktuSaatIni;
            // tambahkan gantChart ke dalam list
            gc.push_back(gantChart);
        }

        // jika proses belom pernah di eksekusi
        if (arrProses[currentHighestprioritasIndex].waktuTersisa == arrProses[currentHighestprioritasIndex].waktuBurst)
        {
            // set waktu diekseskusi/ respone time dengan waktu saat ini
            arrProses[currentHighestprioritasIndex].waktuDieksekusi = waktuSaatIni;
        }

        // ubah waktu tersisa menjadi 0
        arrProses[currentHighestprioritasIndex].waktuTersisa = 0;

        // waktu saat ini adalah waktu saat ini ditambah dengan waktu burst
        waktuSaatIni += arrProses[currentHighestprioritasIndex].waktuBurst;

        // jika burst time tersisa udh abis
        if (arrProses[currentHighestprioritasIndex].waktuTersisa == 0)
        {
            // set waktu selesai / complete time nya dengan waktu saat ini
            arrProses[currentHighestprioritasIndex].waktuSelesai = waktuSaatIni;
        }
    }

    // Mengurutkan proses pada array sesuai urutan di eksekusi
    for (int i = 0; i < banyakProses - 1; i++)
    {
        for (int j = i + 1; j < banyakProses; j++)
        {
            if (arrProses[j].waktuDieksekusi < arrProses[i].waktuDieksekusi)
            {
                Process temp = arrProses[j];
                arrProses[j] = arrProses[i];
                arrProses[i] = temp;
            }
        }
    }

    // print Gant Chart
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
    int totalWaktuDieksekusi = 0;
    int totalWaktuSelesai = 0;
    int totalWaktuMenunggu = 0;
    int totalwaktuTurnAround = 0;

    double rerataWaktuTurnAround = 0.0, rerataWaktuMenunggu = 0.0;
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

    for (int i = 0; i < banyakProses - 1; i++)
    {
        for (int j = 0; j < banyakProses - i - 1; j++)
        {
            if (arrProses[j].waktuSelesai > arrProses[j + 1].waktuSelesai)
            {
                Process temp = arrProses[j];
                arrProses[j] = arrProses[j + 1];
                arrProses[j + 1] = temp;
            }
        }
    }

    for (int n = 0; n < banyakProses; n++)
    {
        // menghitung waktu turn around
        arrProses[n].waktuTurnAround = arrProses[n].waktuSelesai - arrProses[n].waktuKedatangan;

        // menghitung waktu menunggu
        arrProses[n].waktuMenunggu = arrProses[n].waktuTurnAround - arrProses[n].waktuBurst;

        // menjumlahkan waktu turn around dan waktu menunggu
        rerataWaktuTurnAround += arrProses[n].waktuTurnAround;
        rerataWaktuMenunggu += arrProses[n].waktuMenunggu;
        cout << "|      " << arrProses[n].namaProses << "      |";
        if (arrProses[n].waktuKedatangan < 10)
        {
            cout << "    " << arrProses[n].waktuKedatangan << "    |";
        }
        else
        {
            cout << "   " << arrProses[n].waktuKedatangan << "    |";
        }
        if (arrProses[n].waktuDieksekusi < 10)
        {
            cout << "     " << arrProses[n].waktuDieksekusi << "    |";
        }
        else
        {
            cout << "    " << arrProses[n].waktuDieksekusi << "    |";
        }
        if (arrProses[n].waktuBurst < 10)
        {
            cout << "   " << arrProses[n].waktuBurst << "   |";
        }
        else
        {
            cout << "  " << arrProses[n].waktuBurst << "   |";
        }

        if (arrProses[n].waktuSelesai < 10)
        {
            cout << "     " << arrProses[n].waktuSelesai << "     |";
        }
        else
        {
            cout << "    " << arrProses[n].waktuSelesai << "     |";
        }

        if (arrProses[n].waktuTurnAround < 10)
        {
            cout << "      " << arrProses[n].waktuTurnAround << "     |";
        }
        else
        {
            cout << "     " << arrProses[n].waktuTurnAround << "     |";
        }

        if (arrProses[n].waktuMenunggu < 10)
        {
            cout << "    " << arrProses[n].waktuMenunggu << "    |";
        }
        else
        {
            cout << "   " << arrProses[n].waktuMenunggu << "    |";
        }
        cout << endl;

        totalWaktuDieksekusi += arrProses[n].waktuDieksekusi;
        totalWaktuSelesai += arrProses[n].waktuSelesai;
        totalWaktuMenunggu += arrProses[n].waktuMenunggu;
        totalwaktuTurnAround += arrProses[n].waktuTurnAround;
    }
    cout << "+-------------+---------+----------+-------+-----------+------------+---------+\n";

    // menghitung rata2 waktu turn around dan waktu menunggu
    rerataWaktuTurnAround /= banyakProses;
    rerataWaktuMenunggu /= banyakProses;

    cout << "\n=> Rata-rata Waktu Turn Around : "
         << rerataWaktuTurnAround << endl;
    cout << "=> Rata-rata Waktu Menunggu    : "
         << rerataWaktuMenunggu << endl;

    return 0;
}

/* TEST CASE
6
A 0 4 4
B 1 5 3
C 2 1 1
D 3 2 6
E 4 3 7
F 5 6 2
*/