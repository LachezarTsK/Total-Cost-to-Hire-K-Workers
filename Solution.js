
/**
 * @param {number[]} hireCostPerWorker
 * @param {number} neededWorkers
 * @param {number} candidatesPerSide
 * @return {number}
 */
var totalCost = function (hireCostPerWorker, neededWorkers, candidatesPerSide) {
    if (neededWorkers === hireCostPerWorker.length) {
        return hireCostPerWorker.reduce((x, y) => x + y);
    }

    //const {MinPriorityQueue} = require('@datastructures-js/priority-queue');
    //MinPriorityQueue<number>
    const frontSideMinHeap = new MinPriorityQueue({compare: (x, y) => x - y});
    const backSideMinHeap = new MinPriorityQueue({compare: (x, y) => x - y});

    let frontSideIndex = 0;
    let backSideIndex = hireCostPerWorker.length - 1;
    let minCostToHireNeededWorkers = 0;

    while (neededWorkers > 0) {

        if (frontSideIndex < backSideIndex && frontSideMinHeap.size() < candidatesPerSide) {
            frontSideMinHeap.enqueue(hireCostPerWorker[frontSideIndex]);
            ++frontSideIndex;
        }
        if (frontSideIndex <= backSideIndex && backSideMinHeap.size() < candidatesPerSide) {
            backSideMinHeap.enqueue(hireCostPerWorker[backSideIndex]);
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
};

/**
 * @param {MinPriorityQueue<number>} frontSideMinHeap
 * @param {MinPriorityQueue<number>} backSideMinHeap
 * @return {number}
 */
function getMinHireCost_breakTiesForSmallerIndex(frontSideMinHeap, backSideMinHeap) {
    if (!frontSideMinHeap.isEmpty() && !backSideMinHeap.isEmpty()) {
        return frontSideMinHeap.front() <= backSideMinHeap.front()
                ? frontSideMinHeap.dequeue()
                : backSideMinHeap.dequeue();
    }
    if (!frontSideMinHeap.isEmpty()) {
        return frontSideMinHeap.dequeue();
    }
    return backSideMinHeap.dequeue();
}
