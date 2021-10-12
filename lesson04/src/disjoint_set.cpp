#include <iostream>
#include "disjoint_set.h"

#define ROOT -1 // объявили макрос (считайте константу) равный минус единице - чтобы не было "волшебной переменной", а была именованная константа "корень дерева"


DisjointSet::DisjointSet(int size)
{
    parents = std::vector<int>(size);
    ranks = std::vector<int>(size);
    sizes = std::vector<int>(size);
    for (int i = 0; i < size; ++i) {
        parents[i] = ROOT;
        ranks[i] = 0;
        sizes[i] = 1;
    }
}

int	DisjointSet::get_set(int element)
{
    if (parents[element] != ROOT){
        parents[element] = get_set(parents[element]);
        return parents[element];
    }
    return element;
}

int DisjointSet::count_differents() const
{
    int count = 0;
    for (size_t i = 0; i < this->parents.size(); i++) {
        if (parents[i] == ROOT){
            count++;
        }
    }
    return count;
}

int DisjointSet::get_set_size(int element)
{
    return sizes[get_set(element)];
}

int	DisjointSet::union_sets(int element0, int element1)
{
    int size = get_set_size(element0) + get_set_size(element1);
    if (ranks[get_set(element0)] > ranks[get_set(element1)]){
        parents[get_set(element1)] = get_set(element0);
    }
    else if (ranks[get_set(element0)] < ranks[get_set(element1)]){
        parents[get_set(element0)] = get_set(element1);
    }
    else{
        if (get_set_size(element0) > get_set_size(element1)){
            parents[get_set(element0)] = get_set(element1);
        }
        else{
            parents[get_set(element1)] = get_set(element0);
        }
    }
    sizes[get_set(element1)] = size;
    ranks[get_set(element1)]++;
    return 0;
}