#!/usr/bin/env python

# To call a function from the interpreter:
# >>> execfile('preprocess.py')
# >>> simplify_class()

# Source: http://code.google.com/p/aima-python/source/browse/trunk/learning.py
def parse_csv(input, delim=','):
    """Input is a string consisting of lines, each line has comma-delimited
    fields.  Convert this into a list of lists.  Blank lines are skipped.
    Fields that look like numbers are converted to numbers.
    The delim defaults to ',' but '\t' and None are also reasonable values.
    >>> parse_csv('1, 2, 3 \n 0, 2, na')
    [[1, 2, 3], [0, 2, 'na']]

    Example:
    if isinstance(examples, str):
        self.examples = parse_csv(examples)
    elif examples is None:
         self.examples = parse_csv(DataFile(name+'.csv').read())
    """
    lines = [line for line in input.splitlines() if line.strip()]
    return [map(num_or_str, line.split(delim)) for line in lines]

def simplify_class():
    """Makes the last digit in each example the expected outcome."""
    ip = open('faults.data', 'r')
    op = open('faults-simple1.data', 'w')
    lines = [line.strip() for line in ip.readlines()]
    
    for line in lines:
        if line.endswith('1 0 0 0 0 0 0'):
            op.write(line[:-13] + '1\n')
        elif line.endswith('0 1 0 0 0 0 0'):
            op.write(line[:-13] + '2\n')
        elif line.endswith('0 0 1 0 0 0 0'):
            op.write(line[:-13] + '3\n')
        elif line.endswith('0 0 0 1 0 0 0'):
            op.write(line[:-13] + '4\n')
        elif line.endswith('0 0 0 0 1 0 0'):
            op.write(line[:-13] + '5\n')
        elif line.endswith('0 0 0 0 0 1 0'):
            op.write(line[:-13] + '6\n')
        elif line.endswith('0 0 0 0 0 0 1'):
            op.write(line[:-13] + '7\n')
    
    ip.close()
    op.close()
    
    ip = open('digits.data', 'r')
    op = open('digits-simple1.data', 'w')
    lines = [line.strip() for line in ip.readlines()]
    
    for line in lines:
        if line.endswith('1 0 0 0 0 0 0 0 0 0'):
            op.write(line[:-19] + '1\n') # in reality it's 0, not 1, and so on.
        elif line.endswith('0 1 0 0 0 0 0 0 0 0'):
            op.write(line[:-19] + '2\n')
        elif line.endswith('0 0 1 0 0 0 0 0 0 0'):
            op.write(line[:-19] + '3\n')
        elif line.endswith('0 0 0 1 0 0 0 0 0 0'):
            op.write(line[:-19] + '4\n')
        elif line.endswith('0 0 0 0 1 0 0 0 0 0'):
            op.write(line[:-19] + '5\n')
        elif line.endswith('0 0 0 0 0 1 0 0 0 0'):
            op.write(line[:-19] + '6\n')
        elif line.endswith('0 0 0 0 0 0 1 0 0 0'):
            op.write(line[:-19] + '7\n')
        elif line.endswith('0 0 0 0 0 0 0 1 0 0'):
            op.write(line[:-19] + '8\n')
        elif line.endswith('0 0 0 0 0 0 0 0 1 0'):
            op.write(line[:-19] + '9\n')
        elif line.endswith('0 0 0 0 0 0 0 0 0 1'):
            op.write(line[:-19] + '10\n')

    ip.close()
    op.close()
