#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Item
{
private:
    int weight;
    int value;

public:
    Item(int, int);
    int getWeight() const;
    int getValue() const;
};

Item::Item(int weight, int value)
{
    this->weight = weight;
    this->value = value;
}

int Item::getWeight() const
{
    return weight;
}

int Item::getValue() const
{
    return value;
}

class Knapsack
{
private:
    int capacity;
    vector<Item> items;

public:
    Knapsack(int, const vector<Item> &itemList);
    int solve();
};

Knapsack::Knapsack(int W, const vector<Item> &itemsList)
{
    capacity = W;
    items = itemsList;
}

int Knapsack::solve()
{
    int n = 0;
    n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i < n + 1; i++)
    {
        for (int w = 1; w < capacity + 1; w++)
        {
            if (items[i - 1].getWeight() < w + 1)
            {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].getWeight()] + items[i - 1].getValue());
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][capacity];
}

int main()
{
    int W = 50;
    vector<Item> items = {Item(10, 60), Item(20, 100), Item(30, 120)};
    Knapsack knapsackSolver(W, items);
    int max_value = knapsackSolver.solve();
    cout << "Maximum value: " << max_value << endl;
    return 0;
}