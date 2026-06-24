# 104. Maximum Depth of Binary Tree

Given the `root` of a binary tree, return its maximum depth.

A binary tree's **maximum depth** is the number of nodes along the longest path from the root node down to the farthest leaf node.

## Examples

**Example 1:**
```
Input: root = [3,9,20,null,null,15,7]
Output: 3
```

**Example 2:**
```
Input: root = [1,null,2]
Output: 2
```

**Example 3:**
```
Input: root = []
Output: 0
```

## Approach

Use **DFS recursion**: the depth of a node is `1 + max(depth(left), depth(right))`. The base case is an empty tree, which has depth `0`.

**Complexity:** O(n) time, O(h) space where h is tree height (recursion stack).

## Files

- `solution.py` — reference solution
- `test.py` — unit tests
