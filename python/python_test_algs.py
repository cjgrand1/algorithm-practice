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
        N = 5

        # tests
        self.assertEqual(algs.GS(M, W, N), [0, 2, 1, 4, 3])

# Running tests
if __name__ == "__main__":
    unittest.main()