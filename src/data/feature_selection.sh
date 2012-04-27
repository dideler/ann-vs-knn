#!/usr/bin/env bash

# For use with the steel plates faults dataset.
# Grab the selected attributes (columns) and put in new file.
# Columns 28-34 are the classification data.
awk '{print $6, $7, $9, $10, $11, $14, $28, $29, $30, $31, $32, $33, $34}' faults.data > faults-subset.data

