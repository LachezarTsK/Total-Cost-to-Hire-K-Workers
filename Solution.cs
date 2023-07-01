
using System;
using System.Collections.Generic;

public class Solution
{
    public long TotalCost(int[] hireCostPerWorker, int neededWorkers, int candidatesPerSide)
    {
        if (neededWorkers == hireCostPerWorker.Length)
        {
            return hireCostPerWorker.Sum(n => (long)n);

        }

        PriorityQueue<int, int> frontSideMinHeap = new PriorityQueue<int, int>();
        PriorityQueue<int, int> backSideMinHeap = new PriorityQueue<int, int>();

        int frontSideIndex = 0;
        int backSideIndex = hireCostPerWorker.Length - 1;
        long minCostToHireNeededWorkers = 0;

        while (neededWorkers > 0)
        {

            if (frontSideIndex < backSideIndex && frontSideMinHeap.Count < candidatesPerSide)
            {
                frontSideMinHeap.Enqueue(hireCostPerWorker[frontSideIndex], hireCostPerWorker[frontSideIndex]);
                ++frontSideIndex;
            }
            if (frontSideIndex <= backSideIndex && backSideMinHeap.Count < candidatesPerSide)
            {
                backSideMinHeap.Enqueue(hireCostPerWorker[backSideIndex], hireCostPerWorker[backSideIndex]);
                --backSideIndex;
            }

            if (frontSideIndex < backSideIndex
                    && frontSideMinHeap.Count < candidatesPerSide
                    && backSideMinHeap.Count < candidatesPerSide)
            {
                continue;
            }

            minCostToHireNeededWorkers += getMinHireCost_breakTiesForSmallerIndex(frontSideMinHeap, backSideMinHeap);
            --neededWorkers;
        }
        return minCostToHireNeededWorkers;
    }

    private int getMinHireCost_breakTiesForSmallerIndex(PriorityQueue<int, int> frontSideMinHeap, PriorityQueue<int, int> backSideMinHeap)
    {
        if (frontSideMinHeap.Count > 0 && backSideMinHeap.Count > 0)
        {
            return frontSideMinHeap.Peek() <= backSideMinHeap.Peek()
                    ? frontSideMinHeap.Dequeue()
                    : backSideMinHeap.Dequeue();
        }
        if (frontSideMinHeap.Count > 0)
        {
            return frontSideMinHeap.Dequeue();
        }
        return backSideMinHeap.Dequeue();
    }
}
