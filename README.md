# Basic implementation of a bigint (arbitrary sized integer)

## Features

- Initialize from strings (arbitrary size) or ints (up to 999999999)
- Only positive integers allowed by now
- Decimal based frames (currently mainly to facilitate input and printing)
- Sum operator
- Increment operators

## Notes

My main goal here is to be able to operate on bigints (currently, increment them and sum two of them). However in order to input data and test we need constructors and conversion to string functions.

The main constructor is `bigint(string)` which creates a bigint from an arbitrarily long string. 
Just for convenience a basic integer based constructor is provided however is limited to `999999999` as input value.

Conversion to string currently does not strip leading zeroes. So we can see the complete frame (9 digits each). 
It means that `bigint(1).show()` will print as `000000001`

To be able to print a bigint easier (specially while debugging) the `operator<<` has been provided.

By now in code comments are in PT-BR. But it may change in the future depending on how this project gets used.
