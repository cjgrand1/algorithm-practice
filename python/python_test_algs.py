#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import python_algs as algs
import unittest

# Creating test cases for Gale-Shapley algorithm
class TestGSOperation(unittest.TestCase):
    def test_GS(self):
        # inputs
        M = [ [2, 1, 4, 5, 3],
             [4, 2, 1, 3, 5],
             [2, 5, 3, 4, 1],
             [1, 4, 3, 2, 5],
             [2, 4, 1, 5, 3] ]
        W = [ [5, 1, 2, 4, 3],
             [3, 2, 4, 1, 5],
             [2, 3, 4, 5, 1],
             [1, 5, 4, 3, 2],
             [4, 2, 5, 3, 1] ]
        M2 = [ [2, 1, 3],
              [3, 1, 2],
              [3, 2, 1] ]
        W2 = [ [2, 1, 3],
              [3, 2, 1],
              [3, 1, 2] ]

        # tests
        self.assertEqual(algs.GaleShapley(M, W), ["(M, W)", "(1, 1)", "(2, 3)", "(3, 2)", "(4, 5)", "(5, 4)"])
        self.assertEqual(algs.GaleShapley(M2, W2), ["(M, W)", "(1, 2)", "(2, 1)", "(3, 3)"])

# Running tests
if __name__ == "__main__":
    unittest.main()