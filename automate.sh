#!/usr/bin/env bash

set -e

pushd > /dev/null src/
make all-optimized
bash all_runs.sh
popd > /dev/null
bash /results/average-data.sh
