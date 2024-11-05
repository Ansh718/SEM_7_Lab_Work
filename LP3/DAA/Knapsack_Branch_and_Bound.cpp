#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

class Knapsack;

class Item
{
private:
    int weight;
    int value;
    double ratio;

public:
    Item(int, int);
    double getRatio() const;
    friend class Knapsack;
};

Item::Item(int weight, int value)
{
    this->weight = weight;
    this->value = value;
    ratio = static_cast<double>(value) / weight;
}

double Item::getRatio() const
{
    return ratio;
}

class Node
{
private:
    int level;
    int profit;
    int weight;
    double bound;

public:
    Node(int level = -1, int profit = 0, int weight = 0, double bound = 0); 
    friend class Knapsack;
};

Node::Node(int level, int profit, int weight, double bound) 
{
    this->level = level;
    this->profit = profit;
    this->weight = weight;
    this->bound = bound;
}

class Knapsack
{
private:
    int W;
    vector<Item> items;
    static bool compareItems(const Item &, const Item &);
    double calculateBound(const Node &) const;

public:
    Knapsack(int, const vector<Item> &);
    int solve();
};

bool Knapsack::compareItems(const Item &a, const Item &b)
{
    return a.getRatio() > b.getRatio();
}

double Knapsack::calculateBound(const Node &u) const
{
    if (u.weight >= W)
    {
        return 0;
    }
    double profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;
    while (j < items.size() && totweight + items[j].weight <= W)
    {
        totweight += items[j].weight;
        profit_bound += items[j].value;
        j++;
    }
    if (j < items.size())
    {
        profit_bound += (W - totweight) * items[j].getRatio();
    }
    return profit_bound;
}

Knapsack::Knapsack(int capacity, const vector<Item> &itemList)
{
    W = capacity;
    items = itemList;
    sort(items.begin(), items.end(), compareItems);
}

int Knapsack::solve()
{
    queue<Node> Q;
    Node u, v;
    u = Node(-1, 0, 0, 0);
    Q.push(u);
    int maxP = 0;
    while (!Q.empty())
    {
        u = Q.front();
        Q.pop();
        if (u.level == -1)
        {
            v.level = 0;
        }
        else if (u.level == items.size() - 1)
        {
            continue;
        }
        else
        {
            v.level = u.level + 1;
        }
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;
        if (v.weight <= W && v.profit > maxP)
        {
            maxP = v.profit;
        }
        v.bound = calculateBound(v);
        if (v.bound > maxP)
        {
            Q.push(v);
        }
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = calculateBound(v);
        if (v.bound > maxP)
        {
            Q.push(v);
        }
    }
    return maxP;
}

int main()
{
    int W = 50;
    vector<Item> items = {
        Item(10, 60), Item(20, 100), Item(30, 120)};

    Knapsack solver(W, items);
    int max_value = solver.solve();
    cout << "Maximum value: " << max_value << endl;

    return 0;
}
