
#include <iostream>
#include <list>
using namespace std;

class Proses
{
public:
    string namaProses;
    int waktuKedatangan;
    int waktuBurst;

    bool isCompleted;

    int waktuDieksekusi;
    int waktuSelesai;

    int waktuMenunggu;
    int waktuTurnAround;

    void initialize()
    {
        isCompleted = false;
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
    cin >> banyakProses;

    // membuat array proses alokasi sesuai nilai banyakProses
    Proses queueProses[banyakProses];

    // list untuk menyimpan gant chart
    list<GantChart> gc;

    // Masukkin inputan user
    for (int n = 0; n < banyakProses; n++)
    {
        cout << "== Proses " << (n + 1) << " ==\n";
        cout << "Huruf proses: ";
        cin >> queueProses[n].namaProses;
        cout << "Waktu datang: ";
        cin >> queueProses[n].waktuKedatangan;
        cout << "Waktu Burst: ";
        cin >> queueProses[n].waktuBurst;
        cout << "=================\n";

        queueProses[n].initialize();
    }

    cout << "\n"
         << endl;

    // Mengurutkan elemen array sesuai waktu kedatangannya
    for (int i = 0; i < banyakProses - 1; i++)
    {
        for (int j = i + 1; j < banyakProses; j++)
        {
            if (queueProses[j].waktuKedatangan < queueProses[i].waktuKedatangan)
            {
                Proses temp = queueProses[j];
                queueProses[j] = queueProses[i];
                queueProses[i] = temp;
            }
        }
    }

    // waktu saat ini di set dengan proses yang waktu kedatangannya paling awal
    int waktuSaatIni = queueProses[0].waktuKedatangan;

    while (true)
    {
        // index sjf saat ini
        int currentShortestJobIndex = -1;
        // burst time
        int currentShortestJobRemainingTime = 9999;

        bool isAllCompleted = true;

        for (int i = 0; i < banyakProses; i++)
        {
            if (!queueProses[i].isCompleted)
            {
                isAllCompleted = false;
                if (queueProses[i].waktuKedatangan <= waktuSaatIni)
                {
                    // Crai burst time paling kecil untuk di proses
                    if (queueProses[i].waktuBurst < currentShortestJobRemainingTime)
                    {
                        currentShortestJobRemainingTime = queueProses[i].waktuBurst;
                        currentShortestJobIndex = i;
                    }
                }
            }
        }

        // Kalo udah semua di break
        if (isAllCompleted)
        {
            break;
        }

        // Kalo ada proses yang belum jalanin proses ini untuk perhitungan waktu waktunya
        queueProses[currentShortestJobIndex].waktuDieksekusi = waktuSaatIni;

        waktuSaatIni += queueProses[currentShortestJobIndex].waktuBurst;
        queueProses[currentShortestJobIndex].isCompleted = true;

        queueProses[currentShortestJobIndex].waktuSelesai = waktuSaatIni;

        // Proses membuat objek GantChart untuk dimasukkan ke dalam array object GantChart
        GantChart gantChart;
        gantChart.namaProses = queueProses[currentShortestJobIndex].namaProses;
        gantChart.waktuDieksekusi = queueProses[currentShortestJobIndex].waktuDieksekusi;
        // tambahkan gantChart ke dalam list
        gc.push_back(gantChart);
    }

    // Mengurutkan elemen array sesuai urutan eksekusi
    for (int i = 0; i < banyakProses - 1; i++)
    {
        for (int j = i + 1; j < banyakProses; j++)
        {
            if (queueProses[j].waktuSelesai < queueProses[i].waktuSelesai)
            {
                Proses temp = queueProses[j];
                queueProses[j] = queueProses[i];
                queueProses[i] = temp;
            }
        }
    }

    // Jika semua proses telah dikerjakan
    GantChart gantChart;
    gantChart.namaProses = "-";
    gantChart.waktuDieksekusi = waktuSaatIni;
    // Tambahkan gantChart ke dalam list
    gc.push_back(gantChart);

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

    double rerataWaktuTurnAround = 0.0, rerataWaktuMenunggu = 0.0;
    for (int n = 0; n < banyakProses; n++)
    {
        queueProses[n].waktuTurnAround = queueProses[n].waktuSelesai - queueProses[n].waktuKedatangan;
        queueProses[n].waktuMenunggu = queueProses[n].waktuTurnAround - queueProses[n].waktuBurst;

        rerataWaktuTurnAround += queueProses[n].waktuTurnAround;
        rerataWaktuMenunggu += queueProses[n].waktuMenunggu;

        cout << "|      " << queueProses[n].namaProses << "      |";
        if (queueProses[n].waktuKedatangan < 10)
        {
            cout << "    " << queueProses[n].waktuKedatangan << "    |";
        }
        else
        {
            cout << "   " << queueProses[n].waktuKedatangan << "    |";
        }
        if (queueProses[n].waktuDieksekusi < 10)
        {
            cout << "     " << queueProses[n].waktuDieksekusi << "    |";
        }
        else
        {
            cout << "    " << queueProses[n].waktuDieksekusi << "    |";
        }
        if (queueProses[n].waktuBurst < 10)
        {
            cout << "   " << queueProses[n].waktuBurst << "   |";
        }
        else
        {
            cout << "  " << queueProses[n].waktuBurst << "   |";
        }

        if (queueProses[n].waktuSelesai < 10)
        {
            cout << "     " << queueProses[n].waktuSelesai << "     |";
        }
        else
        {
            cout << "    " << queueProses[n].waktuSelesai << "     |";
        }

        if (queueProses[n].waktuTurnAround < 10)
        {
            cout << "      " << queueProses[n].waktuTurnAround << "     |";
        }
        else
        {
            cout << "     " << queueProses[n].waktuTurnAround << "     |";
        }

        if (queueProses[n].waktuMenunggu < 10)
        {
            cout << "    " << queueProses[n].waktuMenunggu << "    |";
        }
        else
        {
            cout << "   " << queueProses[n].waktuMenunggu << "    |";
        }
        cout << endl;
    }
    cout << "+-------------+---------+----------+-------+-----------+------------+---------+\n";

    rerataWaktuMenunggu /= banyakProses;
    rerataWaktuTurnAround /= banyakProses;

    cout << "=> Rata-rata Waktu Turn Around : \n"
         << rerataWaktuTurnAround << endl;
    cout << "=> Rata-rata Waktu Menunggu : \n"
         << rerataWaktuMenunggu << endl;
    return 0;
}
