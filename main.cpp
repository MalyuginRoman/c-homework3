#include <iostream>
#include <map>
#include "MyAllocator.h"
#include "MyList.h"

long long fact(int n){
    long long factorial = 1;
    for (int i = 1; i <= n; ++i)
    {
        factorial *= i;
    }
    return factorial;
}

template <typename Map>
static void PrintMap(const Map& map)
{
    for (auto pair : map){
        std::cout << pair.first << " " << pair.second << std::endl; }
}

template <typename List>
static void PrintList(const List& list)
{
    for (auto i : list){
        std::cout << i << " ";}
    std::cout << std::endl;
}

int main(){
    int const count = 10;
//- создание экземпляра std::map<int, long long>
//- заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    auto Map = std::map<int, long long>{};
    for(int i = 0; i < count; i++)
        Map.emplace(i, fact(i));
    PrintMap(Map);

//- создание экземпляра std::map<int, long long> с новым аллокатором, ограниченным 10 элементами
//- заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    auto a_Map = std::map<int, long long, std::less<int>, MyAllocator<std::pair<int, long long>, count>>{};
 	  for (auto i = 0; i < count; i++)
        a_Map.emplace(i, fact(i));
    PrintMap(a_Map);

//- создание экземпляра своего контейнера для хранения значений типа int
//- заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    auto List = MyList<int>{};
    for(auto i = 0; i < count; ++i)
        List.append(i);
    PrintList(List);

//- создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором, ограниченным 10 элементами
//- заполнение 10 элементами от 0 до 9
    auto a_List = MyList<int, MyAllocator<int, count>>{};
    for(auto i = 0; i < count; ++i)
        a_List.append(i);
    PrintList(a_List);

	return 0;
};
