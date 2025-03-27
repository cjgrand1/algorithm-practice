#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# imports
import queue

def inverseArray(arr, N):
    """Description
    
    Args:
        arr: An array of numbers.
        
    Returns:
        returns something
        
    Raises:
        TypeError: none but should have one.
    """
    inverse = []
    for i in range(N):
        row = [0] * N
        for j in range(N):
            row[arr[i][j] - 1] = j
        inverse.append(row)
    return inverse


def GS(M, W, N):
    """Implementation of the Gale-Shapely (GS) matching algorithm

    Running time: O(n^2)

    Args:
        M: An array of preferences for each m.
        W: An array of preferences for each w.

    Returns:
        A queue of stable matching pairs.

    Raises:
        TypeError: none but should have one.
    """
    MQueue = queue.Queue() # maintain a list of free M entries
    list(map(MQueue.put, range(N)))

    WtoM = [-1] * N # found pairs
    count = [0] * N # num of proposals by M

    # preprocess M preference in O(N) time
    inverse = inverseArray(W, N)

    while not MQueue.empty() and count[MQueue.queue[0]] < N:
        m = MQueue.get()
        w = M[m][count[m]] - 1 # first choice on m list not yet proposed to
        count[m] += 1

        if WtoM[w] == -1:
            # assign m and w to be engaged
            WtoM[w] = m
        elif inverse[w][m] < inverse[w][WtoM[w]]:
            # assign m and w to be engaged, and m' to be free
            MQueue.put(WtoM[w])
            WtoM[w] = m
        else:
            # w rejects m
            MQueue.put(m)

    return WtoM