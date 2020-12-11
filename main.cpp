#include <iostream>
#include <fstream>
#include <vector>
void banker_algorithm(int processes, int resources, int allocated[], int available[], int need[], bool marked[],std::vector<int> safe);
bool is_available(int processes, int resources, int need[]);
int main()
{
    setlocale(LC_ALL, "Russian");
    int processes,resources, available;
    int *allocated, *max, *need;
    bool *marked;
    std::vector<int> safe;
    std::ifstream in;
    in.open("input.txt");
    if (in.is_open())
    {
        in >> processes;
        allocated = new int[processes];
        max = new int[processes];
        need = new int[processes];
        marked = new bool[processes];
        in >> resources;
        for (int i = 0; i < processes; i++)
        {
            in >> allocated[i];
        }
        for (int i = 0; i < processes; i++)
        {
            in >> max[i];
        }
        for (int i = 0; i < processes; i++)
        {
            need[i] = max[i] - allocated[i];
        }
        for (int i = 0; i < processes; i++)
        {
            marked[i] = false;    
        }
        int sum = 0;
        for (int i = 0; i < processes; i++)
        {
            sum += allocated[i];
        }
        available = resources - sum;
        in.close();
        std::cout << "Всего сейчас доступно ресурса: " << available << '\n';
        for (int i = 0; i < processes; i++)
        {
            std::cout << "Процесс #" << i + 1 << ": " << " выделенно = " << allocated[i] << ", всего нужно = " << max [i]<<'\n';
        }
        std::cout << "Возможные способы распределения ресурсов:\n";
        banker_algorithm(processes, available, allocated, max, need, marked, safe);
        delete[] need;
        delete[] max;
        delete[] allocated;
        delete[] marked;
    }

}

void banker_algorithm(int processes, int available, int allocated[], int max[], int need[], bool marked[], std::vector<int> safe)
{
    for (int i = 0; i < processes; i++)
    {
        if (!marked[i] && is_available(i, available, need))
        {
            marked[i] = true;
       
            available += allocated[i];
            safe.push_back(i);

            banker_algorithm(processes, available,allocated,max,need,marked,safe);
            safe.pop_back();

            marked[i] = false;

            available -= allocated[i];
        }
    }
    if (safe.size() == processes)
    {
        for (int i = 0; i < processes; i++)
        {
            std::cout << "P" << safe[i] + 1;
            if (i != (processes - 1))
                std::cout << "--> ";
        }
        std::cout << '\n';
    }
}
bool is_available(int process, int resources,int need[])
{
    return need[process] <= resources;
}

