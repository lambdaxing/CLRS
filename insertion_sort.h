#pragma once

template <typename T, unsigned N>
void insertion_sort(T (&A)[N]) {
  for (unsigned j = 1; j < N; j++) {
    auto key = A[j];
    // Insert A[j] into the sorted sequence A[1..j-1].
    unsigned i = j - 1;
    while (i >= 0 and A[i] > key) {
      A[i + 1] = A[i];
      if (i == 0)
        break;
      else
        i--;
    }
    if (i == 0)
      A[i] = key;
    else
      A[i + 1] = key;
  }
}

// 注：书中的伪码主要讲述算法思想，
// 而具体到一门语言则要考虑一些现实问题，
// 比如数组下标从 0 开始带来的边界不一以及无符号整型永远不会小于 0。