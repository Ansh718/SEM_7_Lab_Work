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

    int recursiveKnapsack(int, int);
    int memoizationKnapsack(int, int, vector<vector<int>> &);

public:
    Knapsack(int, const vector<Item> &);
    int solve();
    int solveRecursive();
    int solveMemoization();
};

Knapsack::Knapsack(int W, const vector<Item> &itemsList)
{
    capacity = W;
    items = itemsList;
}

int Knapsack::solve()
{
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i < n + 1; i++)
    {
        for (int w = 1; w < capacity + 1; w++)
        {
            if (items[i - 1].getWeight() <= w)
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

int Knapsack::recursiveKnapsack(int n, int W)
{
    if (n == 0 || W == 0)
        return 0;
    if (items[n - 1].getWeight() > W)
        return recursiveKnapsack(n - 1, W);
    return max(recursiveKnapsack(n - 1, W), items[n - 1].getValue() + recursiveKnapsack(n - 1, W - items[n - 1].getWeight()));
}

int Knapsack::solveRecursive()
{
    return recursiveKnapsack(items.size(), capacity);
}

int Knapsack::memoizationKnapsack(int n, int W, vector<vector<int>> &memo)
{
    if (n == 0 || W == 0)
        return 0;
    if (memo[n][W] != -1)
        return memo[n][W];
    if (items[n - 1].getWeight() > W)
        return memo[n][W] = memoizationKnapsack(n - 1, W, memo);
    return memo[n][W] = max(memoizationKnapsack(n - 1, W, memo), items[n - 1].getValue() + memoizationKnapsack(n - 1, W - items[n - 1].getWeight(), memo));
}

int Knapsack::solveMemoization()
{
    int n = items.size();
    vector<vector<int>> memo(n + 1, vector<int>(capacity + 1, -1));
    return memoizationKnapsack(n, capacity, memo);
}

int main()
{
    int W = 50;
    vector<Item> items = {Item(10, 60), Item(20, 100), Item(30, 120)};
    Knapsack knapsackSolver(W, items);

    int max_value_dp = knapsackSolver.solve();
    cout << "Maximum value (Dynamic Programming): " << max_value_dp << endl;

    int max_value_recursive = knapsackSolver.solveRecursive();
    cout << "Maximum value (Recursive): " << max_value_recursive << endl;

    int max_value_memoization = knapsackSolver.solveMemoization();
    cout << "Maximum value (Memoization): " << max_value_memoization << endl;

    return 0;
}