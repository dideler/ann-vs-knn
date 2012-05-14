#!/usr/bin/env bash

set -e

echo
echo "(!) Building project and cleaning up..."
echo
pushd > /dev/null src/
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
popd > /dev/null
pushd > /dev/null results/
bash average-data.sh
popd > /dev/null
echo
echo "(!) Results processed."
echo "    To save the graphs in 'results/' instead of displaying them,"
echo "    uncomment the 'set terminal' and 'set output' lines in 'results/*.plt'."
echo
echo "(!) All done!"
