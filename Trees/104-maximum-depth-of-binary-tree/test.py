"""Test cases for LeetCode 104 - Maximum Depth of Binary Tree"""
import unittest
from typing import Optional


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# Solution implementations
class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        return 1 + max(self.maxDepth(root.left), self.maxDepth(root.right))


def build_tree(values):
    """Build tree from level-order list, None for missing nodes."""
    if not values:
        return None
    nodes = [None if v is None else TreeNode(v) for v in values]
    kids = nodes[::-1]
    root = kids.pop()
    for node in nodes:
        if node:
            if kids:
                node.left = kids.pop()
            if kids:
                node.right = kids.pop()
    return root


class TestMaxDepth(unittest.TestCase):
    def test_example_1(self):
        # [3,9,20,null,null,15,7] -> depth 3
        root = build_tree([3, 9, 20, None, None, 15, 7])
        self.assertEqual(Solution().maxDepth(root), 3)

    def test_example_2(self):
        # [1,null,2] -> depth 2
        root = build_tree([1, None, 2])
        self.assertEqual(Solution().maxDepth(root), 2)

    def test_empty(self):
        self.assertEqual(Solution().maxDepth(None), 0)

    def test_single_node(self):
        root = build_tree([0])
        self.assertEqual(Solution().maxDepth(root), 1)

    def test_left_skewed(self):
        root = build_tree([1, 2, None, 3, None, 4, None])
        self.assertEqual(Solution().maxDepth(root), 4)

    def test_right_skewed(self):
        root = build_tree([1, None, 2, None, 3, None, 4])
        self.assertEqual(Solution().maxDepth(root), 4)

    def test_balanced(self):
        # Perfect tree of depth 3 -> depth 3
        root = build_tree([1, 2, 3, 4, 5, 6, 7])
        self.assertEqual(Solution().maxDepth(root), 3)


if __name__ == "__main__":
    unittest.main(verbosity=2)
