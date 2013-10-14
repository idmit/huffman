huffman
=======

Console utility for archiving ascii files.

Usage
-----------
**archive**
```c
  huffman a [-t <customTable>] <input> <output>
```
**extract**
```c
  huffman x [-t <customTable>] <input> <output>
```

Custom table
-------------------

Table is just a `txt` file with pairs of `<char> <prob>` on every line. `char` is a hex code of an ascii symbol in format `\xFF` or a symbol itself.  `prob` is probability of `char` occurring in your text. 
- No symbol repetition is allowed
- It's not required to fill up the whole table of ascii symbols
- Some symbols may have 0 probabilities
- You can omit some symbols, leaving resulting probability equal to one

If you are using a custom table to archive a file, you **must** provide the same one to extract your file in a proper way.