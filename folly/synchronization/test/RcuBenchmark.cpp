/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <folly/Benchmark.h>
#include <folly/synchronization/Rcu.h>

using namespace folly;

void runTest(int iters) {
  BenchmarkSuspender susp;

  { rcu_reader g; }
  susp.dismiss();

  // run the test loop
  for (int i = 0; i < iters; i++) {
    rcu_reader g;
  }
}

BENCHMARK_DRAW_LINE();
BENCHMARK(RcuReader, iters) {
  runTest(iters);
}
BENCHMARK_DRAW_LINE();

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  folly::runBenchmarks();

  return 0;
}
