# RPH Challenge 3

- Design a binary file format capable of storing a three-dimensional array of integers.
- The integers may not be stored in plain text or ascii-encoding.
Use a binary header to store the date and time of creation (not in plain text or ascii-encoding), along with the name of the file's creator.
- Write a file generator function which takes the matrix and filename as input parameters, prompts the user for a name through the console, and outputs to your file.
- Write a file parser function which takes the filename as an input parameter, parses the file, prints the creation time (as a unix timestamp) and creator name to console, and returns the matrix in the same format received by the generator.

## The Input Format

```nohighlight
<Username>
<Filename>
<z> <y> <x>

<data...>
```

## The Output Format

Default: identical to input format

Verbose (`-v`):

```nohighlight
Encoded matrix '<filename>'
Owner: <username>
Timestamp: <timestamp>
<z> <y> <x>

<data...>
```

## The File Format

The matrix is encoded as an executable. That executable is the decoder. When it runs, it prints the information hardcoded within.

## The process

Username, filename, and dimensions are read from standard input by `Encode`. All three are provided to `TypedEncode.cc` as preprocessor macros. Importantly, dimensions being known at compile-time allows them to serve as template arguments to `Matrix`. `Encode` then invokes `TypedEncode`.

`TypedEncode` invokes `ld -r -b binary` three times, producing three object files containing the runtime representations of username, timestamp, and data. It compiles `Decode.cc`, forwarding the dimensions and linking against these three objects.

`Decode` is to be linked against objects that define the certain symbols produced by `ld` in `TypedEncode`. It just prints stuff. Pretty straightforward. `-v` enables verbose output.
