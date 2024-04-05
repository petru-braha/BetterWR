# Archive file viewer

! Shortcuts:
- GUI = graphical user interface 
- CMD = bash commands
- HUF = Huffaman trees functions
- LZW = Lempel-Ziv-Welch functions

! Map:
1. boot
2. option (compress / decompress)
3. algorithm (HUF / LZW)
4. packaging (Tar format , validate paths)

! Data structures: Binary trees, Priority Queue, Heap, Dictionary, Stack, Hash Table

## I. **Boot**:

- two ways of running the program: 
	1. double-click on ".boot." => opens GUI
	2. openning the folder in command prompt
		- type `./name_of_executable arguments` **[arguments]** 
		- if no arguments provided => opens GUI

### 1. GUI

- buttons:
Index 		Name
0 		compress
1 		decompress
2 		more informations
3 		stop
4 		go back
5 		done
6 		select
7 		mkdir
8 		fopen
9 		delete
10 		HUF
11 		LZW
12		announcement_box //to_be_reviewed

- file_coordo[0...10] == selected files
- file_coordo[11...infinity] == visible_files

### 2. CMD

- Usage: `./name_of_executable <operation> <algorithm> <nr_input_files> <input_file_paths> <output_path>`
- multiple files can be selectected to be encoded and decoded in one step

## II. **Algorithms**:

### 1. HUF algorithm

- encoding/decoding:
```
Pseudocode:

Creation of a Priority Queue Q, which contains each character
Sorting in ascending order of their frequencies 
For all unique characters:
    Create a newNode
    Extraction of the minimum value from Q and assigning it to the leftChild of the newNode 
    Retrieving the minimum value from Q and assigning it to the right child rightChild of newNode
    Computing the sum of the two minimum values and assigning this value to the newNode
    Inserting the newNode into the tree
return root
```

   Huffman encoding involves computing the frequency for each unique character that appears in the initial string. Once we obtain the necessary information (each character and its corresponding frequency), we will store it in a map that will be used to build the Huffman tree, necessary for both encoding and decoding. Based on the tree, we convert the initial string into a string of binary values, which will then be grouped in groups of 8 to form a byte and converted into the corresponding ASCII character. Finally, the resulting string is encoded and ready to be written to the output file. Also in this file we will keep the information needed to reconstruct the tree, i.e. each character together with its frequency plus the size of the tree. When we read the contents of the file to perform the decoding, we make sure that we first read the tree data correctly and then read the encoded string. Decoding will be done by traversing the reconstructed tree, and when the encoded value corresponding to a character is found, we will write it to our created decoding string.

### 2. LZW algorithm (dictionary based)

- the dictinonary is initialised with all the char elements from 0 to 255. 
- enconding:
```
Pseudocode:

repeat
	repeat
		if temp is in dictionary
		    add the following character
	until it is no longer in the dictionary
	add it to the dictionary
	output the part that was already in the dictionary //((strlen(temp)>1) means it is in the dictionary - memory saving method)
	reset variables 
until they reach the end of the input
```

- basic principle: the first character is always in the dictionary and the second character if it is not, means it is a copy of the previous one
- decode:
```
Pseudocode:

repeat
    if not in dictionary next
	    copy previous
    else
	    we put it in the analysis on next
	output<<temp
    add to dictionary(previous, current)
until final input
```

   The Lempel-Ziv-Welch (LZW) algorithm is a lossless data, compression algorithm. Abraham Lempel, Jakob Ziv and Terry Welch are the scientists who developed it. Procedure: it scans a file for data patterns that occur multiple times, which are saved later in a dictionary and their references are placed in a compressed file whenever repetitive data occurs. In hardware implementations, the algorithm is simple and has the potential for very high throughput. Other usages: GIF image format, Unix file compression utility.

- dictionary's memory + compressed message's memory < uncompressed message's memory
- dictionary is not send with the compressed message - you build the dictionary along the way (the receiver will constructor decoder alone)
- ideal for repetitive and long strings
- no prior information about the input data stream
- compress the input stream in one single step
- fast execution

## III. **Packaging**:

### 1. Tar format

   A TAR (tape archive) file format is an archive created by tar, a UNIX-based utility used to package files together for backup or distribution purposes. It contains multiple files (tarballs) stored in an uncompressed format, along with metadata about the archive. TAR files are not compressed archive files. They are often compressed with file compression utilities such as gzip or bzip2.
   Each file object includes any file data and is preceded by a 512-byte record-anthet. File data is written unmodified, except that its length is rounded to a multiple of 512 bytes. At the end of the archive file there are two 512-byte blocks, filled with binary zeros, to mark the end of the file. The record-antet file contains metadata about a file. To ensure portability between different architectures with different byte orderings, the information in the header record is encoded in ASCII. TAR files are fully compatible between UNIX and Windows systems because all header information is represented in ASCII.
   The TAR file format has changed over time as additional functionality has been developed for the UNIX tar utility, leading to format extensions that include additional information for required implementations, starting in the 1980s. Early versions of TAR formats were inconsistent in the way numeric fields were constructed, which were corrected in later implementations to improve the portability of the format, starting with the first POSIX standard for tar file formats in 1988.
   The tar file format does not contain native data compression, so tar archives are often compressed with an external utility such as; gzip, bzip2, XZ (using 7-Zip / p7zip LZMA / LZMA2 compression algorithms), Brotli, Zstandard and similar tools to reduce archive size for portability and data backup. The resulting compressed files can be found named with single extension, e.g. tgz, tbz, txz, tzst, or with double file extension, e.g. tar.gz, tar.br, tar.bz2, tar.xz, tar.zst.

On short terms:
- connects files without compression
- the information is encoded in in ASCII
- the order of events: first is the unification of files then we should apply the compression technique
Pros and cons:
+ we can use any compression algorithm after the unification
+ deletes doubled information
- can lose metadata of files (index of files)

### 2. Zip format
   A file with a .zip extension is an archive that can hold one or more files or directories. The archive may have compression applied to the included files to reduce the size of the ZIP file. The ZIP file format was made public as early as February 1989 by Phil Katz to achieve archiving of files and folders. The format was made part of the PKZIP utility, created by PKWARE, Inc. As soon as the then existing specifications were made available, many companies made the ZIP file format part of their software utilities, including Microsoft (since Windows 7), Apple (Mac OS X) and many others.
   The file is a compressed archive that supports lossless data compression. It is often used to send zipped email attachments; this way the message cannot be blocked by email server filters. It can also be used to hide a file type or prevent it from being opened.
    There are numerous other standards and formats that use "zip" as part of their name. Phil Katz stated that he wanted to allow the name "zip" for any type of archive. For example, zip is different from gzip, and the latter is defined in an IETF RFC (RFC 1952). Both zip and gzip primarily use the DEFLATE algorithm for compression. Likewise, the ZLIB format (IETF RFC 1950) also uses the DEFLATE compression algorithm, but specifies different error headers and consistency checking. Other similarly named formats and common programs with different native formats include 7-Zip, bzip2, and rzip.

On short terms:
- the order of events: firstly individual compression of the files then the unification
Pros and cons:
+ you can view and unarchive only one archive item
+ parallelize the archiving process on the CPU -> faster
- compression ratio -- (join duplicates, something that is redundant)


## IV **Limitations**:
## V **Future improvements**: