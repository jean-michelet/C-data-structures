import test, { describe, type TestContext } from "node:test";

function insertionSort(toSort: number[]) {
  const arr = [...toSort];
  for (let i = 1; i < arr.length; i++) {
    const current = arr[i];
    let prevIndex = i - 1;

    while (prevIndex >= 0 && arr[prevIndex] > current) {
      arr[prevIndex + 1] = arr[prevIndex];
      prevIndex--;
    }

    arr[prevIndex + 1] = current;
  }

  return arr;
}

describe("insertionSort", () => {
  test("sorts correctly", (t: TestContext) => {
    t.assert.deepStrictEqual(insertionSort([3, 2, 1]), [1, 2, 3]);
    t.assert.deepStrictEqual(insertionSort([2, 3, 1, 4, 2]), [1, 2, 2, 3, 4]);
    t.assert.deepStrictEqual(insertionSort([]), []);
    t.assert.deepStrictEqual(insertionSort([1]), [1]);
  });

  test("does not mutate original array", (t: TestContext) => {
    const arr = [3, 2, 1];
    insertionSort(arr);
    t.assert.deepStrictEqual(arr, [3, 2, 1]);
  });
});
