
import java.util.Arrays;
import java.util.PriorityQueue;

public class Solution {

    public long totalCost(int[] hireCostPerWorker, int neededWorkers, int candidatesPerSide) {
        if (neededWorkers == hireCostPerWorker.length) {
            return Arrays.stream(hireCostPerWorker).mapToLong(n -> n).sum();
        }

        PriorityQueue<Integer> frontSideMinHeap = new PriorityQueue<>();
        PriorityQueue<Integer> backSideMinHeap = new PriorityQueue<>();

        int frontSideIndex = 0;
        int backSideIndex = hireCostPerWorker.length - 1;
        long minCostToHireNeededWorkers = 0;

        while (neededWorkers > 0) {

            if (frontSideIndex < backSideIndex && frontSideMinHeap.size() < candidatesPerSide) {
                frontSideMinHeap.add(hireCostPerWorker[frontSideIndex]);
                ++frontSideIndex;
            }
            if (frontSideIndex <= backSideIndex && backSideMinHeap.size() < candidatesPerSide) {
                backSideMinHeap.add(hireCostPerWorker[backSideIndex]);
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

    private int getMinHireCost_breakTiesForSmallerIndex(PriorityQueue<Integer> frontSideMinHeap, PriorityQueue<Integer> backSideMinHeap) {
        if (!frontSideMinHeap.isEmpty() && !backSideMinHeap.isEmpty()) {
            return frontSideMinHeap.peek() <= backSideMinHeap.peek()
                    ? frontSideMinHeap.poll()
                    : backSideMinHeap.poll();
        }
        if (!frontSideMinHeap.isEmpty()) {
            return frontSideMinHeap.poll();
        }
        return backSideMinHeap.poll();
    }
}
