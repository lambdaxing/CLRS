#pragma once

// template <typename T>
// T find_max_crossing_subarray(const T* const A, unsigned low, unsigned mid,
//                              unsigned high) {
//   T sum{};
//   auto left_sum = sum + A[mid];
//   if (mid != 0) {  // 避免 unsigned 溢出
//     for (auto i = mid - 1; i >= low; i--) {
//       sum += A[i];
//       if (sum > left_sum) {
//         left_sum = sum;
//       }
//       if (i == 0) break;  // 防止 unsigned i 溢出，不执行 i-- ,提前结束。
//     }
//   }
//   sum = T{};
//   auto right_sum = sum + A[mid + 1];
//   for (auto j = mid + 2; j <= high; j++) {
//     sum += A[j];
//     if (sum > right_sum) {
//       right_sum = sum;
//     }
//   }

//   return left_sum + right_sum;
// }

// template <typename T>
// T find_maximum_subarray(const T* const A, unsigned low, unsigned high) {
//   if (high == low) return A[low];

//   unsigned mid = (low + high) / 2;
//   auto left_sum = find_maximum_subarray(A, low, mid);
//   auto right_sum = find_maximum_subarray(A, mid + 1, high);
//   auto cross_sum = find_max_crossing_subarray(A, low, mid, high);

//   if (left_sum >= right_sum && left_sum >= cross_sum)
//     return left_sum;
//   else if (right_sum >= left_sum && right_sum >= cross_sum)
//     return right_sum;
//   else
//     return cross_sum;
// }

// template <typename T>
// T find_maximum_subarray(const T* const A, unsigned N) {
//   return find_maximum_subarray<T>(A, 0, N - 1);
// }

// template <typename T, unsigned N>
// T find_maximum_subarray(T (&A)[N]) {
//   return find_maximum_subarray<T>(A, 0, N - 1);
// }

template <typename T>
T find_maximum_subarray(const T* const A, unsigned N) {
  T ThisSum{};
  T MaxSum = ThisSum;
  for (unsigned j = 0; j < N; j++) {
    ThisSum += A[j];
    if (ThisSum > MaxSum)
      MaxSum = ThisSum;
    else if (ThisSum < 0)
      ThisSum = 0;
  }
  return MaxSum;
}

template <typename T, unsigned N>
T find_maximum_subarray(const T (&A)[N]) {
  T ThisSum{};
  T MaxSum = ThisSum;
  for (unsigned j = 0; j < N; j++) {
    ThisSum += A[j];
    if (ThisSum > MaxSum)
      MaxSum = ThisSum;
    else if (ThisSum < 0)
      ThisSum = 0;
  }
  return MaxSum;
}