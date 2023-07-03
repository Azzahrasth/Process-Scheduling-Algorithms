#include <iostream>
#include <list>
using namespace std;

// class proses : menyimpan nama proses dan waktu-waktu penjadwalan setiap proses
class Proses
{
public:
    string namaProses;
    int arrivalTime;
    int burstTime;

    int remainingTime;

    int responseTime;
    int completionTime;

    int waitingTime;
    int turnAroundTime;

    void initialize()
    {
        remainingTime = burstTime;
    }
};

// class gantChart : menyimpan nama proses dan responseTime nya setiap terjadi pergantian proses yang di eksekusi
class GantChart
{
public:
    string namaProses;
    int responseTime;
};

int main()
{
    // input banyakProses
    int banyakProses;
    cout << "Masukkan banyaknya proses: ";
    cin >> banyakProses;

    // membuat array proses, alokasi sesuai  banyakProses inputan user
    Proses arrProses[banyakProses];
    // membuat list gc untuk menyimpan gant chart
    list<GantChart> gc;

    // input nama, arrivalTime, dan burstTime setiap proses
    for (int n = 0; n < banyakProses; n++)
    {
        cout << "== Proses " << (n + 1) << " ==\n";
        cout << "Huruf proses: ";
        cin >> arrProses[n].namaProses;
        cout << "Waktu datang: ";
        cin >> arrProses[n].arrivalTime;
        cout << "Waktu Burst: ";
        cin >> arrProses[n].burstTime;
        cout << "=================\n";

        arrProses[n].initialize();
    }

    cout << "\n"
         << endl;

    // Mengurutkan proses pada array sesuai waktu kedatangan nya
    for (int i = 0; i < banyakProses - 1; i++)
    {
        for (int j = i + 1; j < banyakProses; j++)
        {
            if (arrProses[j].arrivalTime < arrProses[i].arrivalTime)
            {
                Proses temp = arrProses[j];
                arrProses[j] = arrProses[i];
                arrProses[i] = temp;
            }
        }
    }

    // set waktu saat ini / current time dengan waktu kedatangan dari proses yang paling awal datang
    int currentTime = arrProses[0].arrivalTime;

    // variabel untuk mengecek terjadi pergantian proses
    int tempIndex = -1;
    while (true)
    {
        //  var untuk menyimpan index dri proses yg punya burst time paling kecil, set nilai awal dengan -1
        int currentShortestJobIndex = -1;
        //  var untuk menyimpan nilai burstTime tersisa yang paling kecil, set nilai awal dengan 9999
        int currentShortestJobremainingTime = 9999;
        // var untuk mengecek apakah semua proses dalam array sudah selesai di proses
        bool isAllCompleted = true;

        // looping setiap proses pada array untuk mencari proses yang memiliki sisa burst time paling kecil
        // proses yang memiliki sisa burst time paling kecil akan di eksekusi
        for (int i = 0; i < banyakProses; i++)
        {
            // jika proses tersebut belom complete / sisa burstTime > 0
            if (arrProses[i].remainingTime > 0)
            {
                // set var isAllCompleted jadi false
                isAllCompleted = false;
                // jika proses tsb waktu kedatangan nya <= waktu saat ini
                if (arrProses[i].arrivalTime <= currentTime)
                {
                    // jika sisa burst time proses tsb lebih kecil
                    if (arrProses[i].remainingTime < currentShortestJobremainingTime)
                    {
                        // ambil nilai sisa busrt time dan index nya
                        currentShortestJobremainingTime = arrProses[i].remainingTime;
                        currentShortestJobIndex = i;
                    }
                }
            }
        }

        // jika semua proses dalam array sudah selesai di proses / nilai isAllCompleted nya true
        if (isAllCompleted)
        {
            // buat objek gantChart penutup, isi nama proses nya dengan "-" dan isi responseTime nya dengan waktu saat ini
            GantChart gantChart;
            gantChart.namaProses = "-"; // artinya proses selesai
            gantChart.responseTime = currentTime;
            // tambahkan gantChart ke dalam list gc
            gc.push_back(gantChart);
            break;
        }

        // jika terjadi pergantian proses
        if (tempIndex != currentShortestJobIndex)
        {
            tempIndex = currentShortestJobIndex;
            // buat objek GantChart, isi nama proses dan isi responseTime nya dengan waktu saat ini
            GantChart gantChart;
            gantChart.namaProses = arrProses[currentShortestJobIndex].namaProses;
            gantChart.responseTime = currentTime;
            // tambahkan gantChart tsb ke dalam list
            gc.push_back(gantChart);
        }

        // jika proses belom pernah di eksekusi, dimana nilai sisa burst time = total burst time
        if (arrProses[currentShortestJobIndex].remainingTime == arrProses[currentShortestJobIndex].burstTime)
        {
            // set respone time nya dengan waktu saat ini
            arrProses[currentShortestJobIndex].responseTime = currentTime;
        }

        // mengurangi nilai burst time tersisa proses yg sedang dieksekusi
        arrProses[currentShortestJobIndex].remainingTime--;

        // menambah nilai waktu saat ini
        currentTime++;

        // jika burst time tersisa = 0, artinya proses selesai di eksekusi
        if (arrProses[currentShortestJobIndex].remainingTime == 0)
        {
            // set waktu selesai / complete time nya dengan waktu saat ini
            arrProses[currentShortestJobIndex].completionTime = currentTime;
        }
    } // looping ini akan terus berjalan hingga semua proses telah di eksekusi (isAllCompleted = true)

    // Mengurutkan proses pada array sesuai urutan waktu selesai nya
    for (int i = 0; i < banyakProses - 1; i++)
    {
        for (int j = i + 1; j < banyakProses; j++)
        {
            if (arrProses[j].completionTime < arrProses[i].completionTime)
            {
                Proses temp = arrProses[j];
                arrProses[j] = arrProses[i];
                arrProses[i] = temp;
            }
        }
    }

    cout << "=> Gant Chart <=" << endl;

    for (list<GantChart>::iterator it = gc.begin(); it != gc.end(); it++)
    {
        if (it == gc.begin())
        {
            cout << it->responseTime;
        }
        else
        {
            if (it->responseTime < 10)
            {
                for (int l = 0; l < 10; l++)
                {
                    cout << " ";
                }
                cout << it->responseTime;
            }
            else
            {
                for (int l = 0; l < 9; l++)
                {
                    cout << " ";
                }
                cout << it->responseTime;
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

    // var menyimpan rerata
    double rerataturnAroundTime = 0.0, reratawaitingTime = 0.0;

    cout << "+-------------+---------+----------+-------+-----------+------------+---------+\n";
    cout << "| Nama Proses | Arrival | Response | Burst | Completed | TurnAround | Waiting |\n";
    cout << "+-------------+---------+----------+-------+-----------+------------+---------+\n";
    for (int n = 0; n < banyakProses; n++)
    {
        arrProses[n].turnAroundTime = arrProses[n].completionTime - arrProses[n].arrivalTime;
        arrProses[n].waitingTime = arrProses[n].turnAroundTime - arrProses[n].burstTime;

        cout << "|      " << arrProses[n].namaProses << "      |";
        if (arrProses[n].arrivalTime < 10)
        {
            cout << "    " << arrProses[n].arrivalTime << "    |";
        }
        else
        {
            cout << "   " << arrProses[n].arrivalTime << "    |";
        }
        if (arrProses[n].responseTime < 10)
        {
            cout << "     " << arrProses[n].responseTime << "    |";
        }
        else
        {
            cout << "    " << arrProses[n].responseTime << "    |";
        }
        if (arrProses[n].burstTime < 10)
        {
            cout << "   " << arrProses[n].burstTime << "   |";
        }
        else
        {
            cout << "  " << arrProses[n].burstTime << "   |";
        }

        if (arrProses[n].completionTime < 10)
        {
            cout << "     " << arrProses[n].completionTime << "     |";
        }
        else
        {
            cout << "    " << arrProses[n].completionTime << "     |";
        }

        if (arrProses[n].turnAroundTime < 10)
        {
            cout << "      " << arrProses[n].turnAroundTime << "     |";
        }
        else
        {
            cout << "     " << arrProses[n].turnAroundTime << "     |";
        }

        if (arrProses[n].waitingTime < 10)
        {
            cout << "    " << arrProses[n].waitingTime << "    |";
        }
        else
        {
            cout << "   " << arrProses[n].waitingTime << "    |";
        }
        cout << endl;
        // menjumlahkan turn around time dan waiting time untuk menghitung rerata
        rerataturnAroundTime += arrProses[n].turnAroundTime;
        reratawaitingTime += arrProses[n].waitingTime;
    }
    cout << "+-------------+---------+----------+-------+-----------+------------+---------+\n";

    // menghitung rata2 turn around time dan waiting time
    rerataturnAroundTime /= banyakProses;
    reratawaitingTime /= banyakProses;

    // print rata2 turn around time dan waiting time
    cout << "=> Rata-rata Waktu Turn Around : "
         << rerataturnAroundTime << endl;
    cout << "=> Rata-rata Waktu Menunggu : "
         << reratawaitingTime << endl;

    return 0;
}