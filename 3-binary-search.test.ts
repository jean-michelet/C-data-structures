import { describe, test, type TestContext } from "node:test";

function binarySearchRecursive(
  val: number,
  sortedArr: number[],
  min = 0,
  max = sortedArr.length - 1
) {
  if (min > max) return -1;

  const mid = Math.floor((min + max) / 2);
  if (sortedArr[mid] === val) {
    return mid;
  }

  if (sortedArr[mid] < val) {
    return binarySearchRecursive(val, sortedArr, mid + 1, max);
  }

  return binarySearchRecursive(val, sortedArr, min, mid - 1);
}

function binarySearch(val: number, sortedArr: number[]) {
  let min = 0;
  let max = sortedArr.length - 1;

  while (min <= max) {
    const mid = Math.floor((min + max) / 2);
    if (sortedArr[mid] === val) {
      return mid;
    }

    if (sortedArr[mid] < val) {
      min = mid + 1;
    } else {
      max = mid - 1;
    }
  }

  return -1;
}

describe("binary search", () => {
  test("binarySearch: finds value at start/middle/end", (t: TestContext) => {
    t.assert.strictEqual(binarySearch(1, [1, 2, 3]), 0);
    t.assert.strictEqual(binarySearch(2, [1, 2, 3]), 1);
    t.assert.strictEqual(binarySearch(3, [1, 2, 3]), 2);
  });

  test("binarySearch: returns -1 when not found", (t: TestContext) => {
    t.assert.strictEqual(binarySearch(4, [1, 2, 3]), -1);
    t.assert.strictEqual(binarySearch(1, []), -1);
    t.assert.strictEqual(binarySearch(0, [1]), -1);
    t.assert.strictEqual(binarySearch(999, [1, 2, 3]), -1);
  });

  test("binarySearchRecursive: behaves the same as iterative", (t: TestContext) => {
    t.assert.strictEqual(binarySearchRecursive(1, [1, 2, 3]), 0);
    t.assert.strictEqual(binarySearchRecursive(2, [1, 2, 3]), 1);
    t.assert.strictEqual(binarySearchRecursive(3, [1, 2, 3]), 2);
    t.assert.strictEqual(binarySearchRecursive(4, [1, 2, 3]), -1);
    t.assert.strictEqual(binarySearchRecursive(999, [1, 2, 3]), -1);
  });
});
