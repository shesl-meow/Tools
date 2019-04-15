#!/usr/bin/env python

def cross_correlation(seq1, seq2):
    if isinstance(seq1, str) and isinstance(seq2, str):
        seq1 = [int(s) for s in list(seq1)]
        seq2 = [int(s) for s in list(seq2)]
    elif isinstance(seq1, list) and isinstance(seq2, list):
        seq1 = [int(s) for s in seq1]
        seq2 = [int(s) for s in seq2]
    else:
        assert False
    seq1, seq2 = (seq1, seq2) if len(seq1) < len(seq2) else (seq2, seq1)

    N, M = len(seq1), len(seq2)
    return [sum([(-1) ** (seq1[i % N] + seq2[(i + tau) % M]) for i in range(M)]) for tau in range(N)]


if __name__ == "__main__":
    a = "011"
    b = "1001011"
    c = "10000" + "10101" + "11011" + "00011" + "11100" + "110100"
    s = "11101" + "10011" + "00011" + "01101" + "11110" + "01001" + "01001" + "10101"
    res0 = cross_correlation(a, s)
    res2 = cross_correlation(c, s)
    print(res0)
    print(res2)
