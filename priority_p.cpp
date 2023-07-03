#include <iostream>
#include <limits>
#include <list>
#include <string.h>

using namespace std;

class Process
{
public:
    string namaProses;
    int arrivalTime;
    int burstTime;
    int priority;

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

class GantChart
{
public:
    string namaProses;
    int waktuDieksekusi;
};

int main()
{
    int jumlahProses;
    cout << "Masukkan banyaknya proses : ";
    cin >> jumlahProses;

    Process arrProses[jumlahProses];
    list<GantChart> gc;

    for (int n = 0; n < jumlahProses; n++)
    {
        cout << "== Proses " << (n + 1);
        cout << "\nMasukkan Nama proses  : ";
        cin >> arrProses[n].namaProses;
        cout << "Arival Time            : ";
        cin >> arrProses[n].arrivalTime;
        cout << "Burst Time             : ";
        cin >> arrProses[n].burstTime;
        cout << "Nilai Priority         : ";
        cin >> arrProses[n].priority;

        arrProses[n].initialize();
    }

    cout << "\n"
         << endl;

    for (int i = 0; i < jumlahProses - 1; i++)
    {
        for (int j = i + 1; j < jumlahProses; j++)
        {
            if (arrProses[j].arrivalTime < arrProses[i].arrivalTime)
            {
                Process temp = arrProses[j];
                arrProses[j] = arrProses[i];
                arrProses[i] = temp;
            }
        }
    }

    int waktuSaatIni = 0;
    int tempIndex = -1;
    while (true)
    {

        int currentHighestPriorityIndex = -1;
        int currentHighestPriority = numeric_limits<int>::max();

        bool isAllCompleted = true;

        for (int i = 0; i < jumlahProses; i++)
        {
            if (arrProses[i].remainingTime > 0)
            {
                isAllCompleted = false;
                if (arrProses[i].arrivalTime <= waktuSaatIni)
                {
                    if (arrProses[i].priority < currentHighestPriority)
                    {
                        currentHighestPriority = arrProses[i].priority;
                        currentHighestPriorityIndex = i;
                    }
                }
            }
        }

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
        if (tempIndex != currentHighestPriorityIndex)
        {
            tempIndex = currentHighestPriorityIndex;
            GantChart gantChart;
            gantChart.namaProses = arrProses[currentHighestPriorityIndex].namaProses;
            gantChart.waktuDieksekusi = waktuSaatIni;
            // tambahkan gantChart ke dalam list
            gc.push_back(gantChart);
        }

        if (arrProses[currentHighestPriorityIndex].remainingTime == arrProses[currentHighestPriorityIndex].burstTime)
        {
            arrProses[currentHighestPriorityIndex].responseTime = waktuSaatIni;
        }

        arrProses[currentHighestPriorityIndex].remainingTime--;
        waktuSaatIni++;

        if (arrProses[currentHighestPriorityIndex].remainingTime == 0)
        {
            arrProses[currentHighestPriorityIndex].completionTime = waktuSaatIni;
        }
    }

    for (int i = 0; i < jumlahProses - 1; i++)
    {
        for (int j = i + 1; j < jumlahProses; j++)
        {
            if (arrProses[j].completionTime < arrProses[i].completionTime)
            {
                Process temp = arrProses[j];
                arrProses[j] = arrProses[i];
                arrProses[i] = temp;
            }
        }
    }

    int sumResponseTime = 0;
    int sumCompletionTime = 0;
    int sumWaitingTime = 0;
    int sumTurnAroundTime = 0;

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
    for (int n = 0; n < jumlahProses; n++)
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
        sumResponseTime += arrProses[n].responseTime;
        sumCompletionTime += arrProses[n].turnAroundTime;
        sumWaitingTime += arrProses[n].waitingTime;
        sumTurnAroundTime += arrProses[n].turnAroundTime;
    }
    cout << "+-------------+---------+----------+-------+-----------+------------+---------+\n";
    cout << "\nAverage Response Time for " << (jumlahProses) << " arrProses: " << (float)sumResponseTime / jumlahProses;
    cout << "\nAverage Completion Time for " << (jumlahProses) << " arrProses: " << (float)sumCompletionTime / jumlahProses;
    cout << "\nAverage Waiting Time for " << (jumlahProses) << " arrProses: " << (float)sumWaitingTime / jumlahProses;
    cout << "\nAverage Turn Around Time for " << (jumlahProses) << " arrProses: " << (float)sumTurnAroundTime / jumlahProses;

    return 0;
}