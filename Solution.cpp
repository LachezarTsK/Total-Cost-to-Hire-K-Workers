
#include <vector>
using namespace std;

/*
Customized Priority Queue: Make the Priority Queue to return a value while polling it, 
instead of using top() and then pop(). Just for a quick stretch!
 */
template <typename T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
class CustomizedPriorityQueue : public priority_queue<T, Container, Compare> {
    
public:
    using priority_queue<T, Container, Compare>::top;
    using priority_queue<T, Container, Compare>::pop;
    using priority_queue<T, Container, Compare>::push;
    using priority_queue<T, Container, Compare>::empty;

    T poll() {
        T value = top();
        pop();
        return value;
    }
};

class Solution {
    
    using CustomMinHeap = CustomizedPriorityQueue<int, vector<int>, greater<>>;
    
public:
    long long totalCost(const vector<int>& hireCostPerWorker, int neededWorkers, int candidatesPerSide) const {
        if (neededWorkers == hireCostPerWorker.size()) {
            return accumulate(hireCostPerWorker.begin(), hireCostPerWorker.end(), 0L);
        }

        CustomMinHeap frontSideMinHeap;
        CustomMinHeap backSideMinHeap;

        int frontSideIndex = 0;
        int backSideIndex = hireCostPerWorker.size() - 1;
        long long minCostToHireNeededWorkers = 0;

        while (neededWorkers > 0) {

            if (frontSideIndex < backSideIndex && frontSideMinHeap.size() < candidatesPerSide) {
                frontSideMinHeap.push(hireCostPerWorker[frontSideIndex]);
                ++frontSideIndex;
            }
            if (frontSideIndex <= backSideIndex && backSideMinHeap.size() < candidatesPerSide) {
                backSideMinHeap.push(hireCostPerWorker[backSideIndex]);
                --backSideIndex;
            }

            if (frontSideIndex < backSideIndex
                    && frontSideMinHeap.size() < candidatesPerSide
                    && backSideMinHeap.size() < candidatesPerSide) {
                continue;
            }

            minCostToHireNeededWorkers += getMinHireCost_breakTiesForSmallerIndex(frontSideMinHeap, backSideMinHeap);
            --neededWorkers;
        }
        return minCostToHireNeededWorkers;
    }

private:
    int getMinHireCost_breakTiesForSmallerIndex(CustomMinHeap& frontSideMinHeap, CustomMinHeap& backSideMinHeap) const {
        if (!frontSideMinHeap.empty() && !backSideMinHeap.empty()) {
            return frontSideMinHeap.top() <= backSideMinHeap.top()
                    ? frontSideMinHeap.poll()
                    : backSideMinHeap.poll();
        }
        if (!frontSideMinHeap.empty()) {
            return frontSideMinHeap.poll();
        }
        return backSideMinHeap.poll();
    }
};
