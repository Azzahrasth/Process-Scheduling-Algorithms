#include <iostream>
#include <list>
using namespace std;

using namespace std;

class Proses
{
public:
    string namaProses;
    int waktuKedatangan;
    int waktuBurst;

    int waktuDieksekusi;
    int waktuSelesai;

    int waktuMenunggu;
    int waktuTurnAround;
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

    // input banyakProses
    cin >> banyakProses;

    // membuat array proses alokasi sesuai nilai banyakProses
    Proses arrProses[banyakProses];

    // list untuk menyimpan gant chart
    list<GantChart> gc;

    // input nama, waktu kedatangan, dan waktu Burst setiap proses
    for (int n = 0; n < banyakProses; n++)
    {
        cout << "== Proses " << (n + 1) << " ==\n";
        cout << "Huruf proses: ";
        cin >> arrProses[n].namaProses;
        cout << "Waktu datang: ";
        cin >> arrProses[n].waktuKedatangan;
        cout << "Waktu Burst: ";
        cin >> arrProses[n].waktuBurst;
        cout << "=================\n";
    }

    // mengurutkan proses sesuai waktu kedatangannya
    for (int i = 0; i < banyakProses - 1; i++)
    {
        for (int j = i + 1; j < banyakProses; j++)
        {
            if (arrProses[j].waktuKedatangan < arrProses[i].waktuKedatangan)
            {
                Proses temp = arrProses[j];
                arrProses[j] = arrProses[i];
                arrProses[i] = temp;
            }
        }
    }

    // Proses Eksekusi Proses sesuai Algoritma FCS
    // Menghitung Waktu Start Dieksekusi, Waktu Menunggu, Waktu Selesai, dan Waktu TurnAround Setiap Proses
    int totalWaktuResponse = 0;
    int totalWaktuSelesai = 0;
    int totalWaktuMenunggu = 0;
    int totalWaktuTurnAround = 0;

    // waktu saat ini di set dengan proses yang waktu kedatangannya paling awal
    int waktuSaatIni = arrProses[0].waktuKedatangan;

    for (int n = 0; n < banyakProses; n++)
    {
        arrProses[n].waktuMenunggu = waktuSaatIni - arrProses[n].waktuKedatangan;
        if (n == 0)
        {
            arrProses[n].waktuDieksekusi = arrProses[n].waktuKedatangan;
        }
        else
        {
            arrProses[n].waktuDieksekusi = arrProses[n - 1].waktuSelesai;
        }
        arrProses[n].waktuSelesai = arrProses[n].waktuDieksekusi + arrProses[n].waktuBurst;

        arrProses[n].waktuTurnAround = arrProses[n].waktuSelesai - arrProses[n].waktuKedatangan;

        totalWaktuResponse += arrProses[n].waktuDieksekusi;
        totalWaktuSelesai += arrProses[n].waktuSelesai;
        totalWaktuMenunggu += arrProses[n].waktuMenunggu;
        totalWaktuTurnAround += arrProses[n].waktuTurnAround;

        // Proses membuat objek GantChart untuk dimasukkan ke dalam array object GantChart
        GantChart gantChart;
        gantChart.namaProses = arrProses[n].namaProses;
        gantChart.waktuDieksekusi = waktuSaatIni;
        // tambahkan gantChart ke dalam list
        gc.push_back(gantChart);

        waktuSaatIni += arrProses[n].waktuBurst;
    }

    // Jika semua proses telah dikerjakan
    GantChart gantChart;
    gantChart.namaProses = "-";
    gantChart.waktuDieksekusi = waktuSaatIni;
    // Tambahkan gantChart ke dalam list
    gc.push_back(gantChart);

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

    double rerataWaktuTurnAround = 0.0, rerataWaktuMenunggu = 0.0;

    // print judul
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

    for (int n = 0; n < banyakProses; n++)
    {
        // set waktu turnaround dengan waktu selesai di proses dikurangi waktu kedatangan
        arrProses[n].waktuTurnAround = arrProses[n].waktuSelesai - arrProses[n].waktuKedatangan;
        // set waktu menunggu dengan waktu turnaround dikurangi waktu burst
        arrProses[n].waktuMenunggu = arrProses[n].waktuTurnAround - arrProses[n].waktuBurst;

        // menjumlahkan waktu turn around dan waktu menunggu
        rerataWaktuTurnAround += arrProses[n].waktuTurnAround;
        rerataWaktuMenunggu += arrProses[n].waktuMenunggu;

        // print waktu-waktu yang dimiliki proses dalam array
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
    }
    cout << "+-------------+---------+----------+-------+-----------+------------+---------+\n";

    // menghitung rata2 waktu turn around dan waktu menunggu
    rerataWaktuTurnAround /= banyakProses;
    rerataWaktuMenunggu /= banyakProses;

    // print rata2 waktu turn around dan waktu menunggu
    cout << "=> Rata-rata Waktu Turn Around : "
         << rerataWaktuTurnAround << endl;
    cout << "=> Rata-rata Waktu Menunggu : "
         << rerataWaktuMenunggu << endl;

    return 0;
}
