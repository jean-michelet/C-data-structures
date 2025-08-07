import test, { describe, type TestContext } from "node:test";

function strEquals(strLeft: string, strRight: string) {
  if (strLeft.length !== strRight.length) {
    return false;
  }

  for (let i = 0; i < strLeft.length; i++) {
    if (strLeft[i] !== strRight[i]) {
      return false;
    }
  }

  return true;
}

describe("strEquals", () => {
  test("strEquals: equal strings", (t: TestContext) => {
    t.assert.strictEqual(strEquals("aaab", "aaab"), true);
    t.assert.strictEqual(strEquals("", ""), true);
  });

  test("strEquals: different lengths", (t: TestContext) => {
    t.assert.strictEqual(strEquals("aaab", "aa"), false);
    t.assert.strictEqual(strEquals("a", ""), false);
  });

  test("strEquals: same length, different content", (t: TestContext) => {
    t.assert.strictEqual(strEquals("abcd", "abce"), false);
    t.assert.strictEqual(strEquals("abc", "def"), false);
  });
});
