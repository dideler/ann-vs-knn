#!/usr/bin/env bash

set -e

echo
echo "(!) Building project and cleaning up..."
echo
pushd src/  # To silence pushd and popd, redirect to /dev/null.
make all-optimized
echo
echo "(!) Build complete."
echo "(!) Starting experimental runs..."
echo
bash all_runs.sh
echo
echo "(!) Runs complete."
echo "(!) Processing results..."
echo
popd
pushd results/
bash average-data.sh
popd
echo
echo "(!) All done!"
