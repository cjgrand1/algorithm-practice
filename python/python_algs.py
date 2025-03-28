#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# imports
import queue

class StableMatching:
    def __init__(self):
        self.M = None
        self.W = None

    def inverseArray(self, arr, N):
        """Takes an array of array's and inverses the number value with the position.
        Numbers must range from [1, len(array) + 1]
        [8, 3, 7, 1, 4, 5, 6, 2] --> [4, 8, 2, 5, 6, 7, 3, 1]
        
        Args:
            arr: An array of array's of unique numbers no larger than len(array).
        """
        inverse = []
        for i in range(N):
            row = [0] * N
            for j in range(N):
                row[arr[i][j] - 1] = j
            inverse.append(row)
        return inverse

    def GaleShapley(self, M, W, MOptimal=True):
        """Implementation of the Gale-Shapely stable matching algorithm
        
        Running time: O(n^2)

        Args:
            M: An array of preferences for each m.
            W: An array of preferences for each w.

        Returns:
            A queue of stable matching pairs.

        Raises:
            TypeError: Error if len(M) > len(W).
        """
        if MOptimal:
            self.M = M
            self.W = W
        else:
            self.M = W
            self.W = M
        N = len(self.M[0])

        if N > len(self.W[0]):
            raise TypeError("len(M) must be <= len(W)")

        MQueue = queue.Queue() # maintain a list of free M entries
        list(map(MQueue.put, range(N)))

        WtoM = [-1] * N # found pairs
        MtoW = [-1] * N
        count = [0] * N # num of proposals by M

        # preprocess W preference in O(N) time
        inverse = self.inverseArray(W, N)

        while not MQueue.empty() and count[MQueue.queue[0]] < N:
            m = MQueue.get()
            w = M[m][count[m]] - 1 # first choice on m list not yet proposed to
            count[m] += 1

            if WtoM[w] == -1:
                # assign m and w to be engaged
                WtoM[w] = m
                MtoW[m] = w
            elif inverse[w][m] < inverse[w][WtoM[w]]:
                # assign m and w to be engaged, and m' to be free
                MQueue.put(WtoM[w])
                WtoM[w] = m
                MtoW[m] = w
            else:
                # w rejects m
                MQueue.put(m)

        output = []
        if MOptimal:
            output.append("(M, W)")
        else:
            output.append("(W, M)")

        for i in range(len(MtoW)):
            output.append(f"{i + 1, MtoW[i] + 1}")
        return output