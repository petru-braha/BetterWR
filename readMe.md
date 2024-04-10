# Archive file viewer

### Administrative:
1. Shortcuts:
   - GUI = graphical user interface 
   - CMD = bash commands
   - HUF = Huffaman trees functions
   - LZW = Lempel-Ziv-Welch functions

2. Map of execution:
```
Pseudocode:

boot
   gui
      fullscreen window
      gui_commands
         menu
            check_stop
            option (compress/decompress)
	 explorer
         third_step
	    commands_STOP();
            commands_go_back(which_button, first_command);
            commands_alg(which_button);
            commands_deselect();
            commands_ready(which_button);
            commands_sidebar();
            commands_folder_manipulation();
   complex bash commands   
      decide_option (compress / decompress)
      decide_algorithm (HUF / LZW)
      paths validation
      tar temp file
      operation
error
```

3. Data structures: 
   - Binary trees 
   - Priority Queue
   - Heap
   - Dictionary
   - Hash Table

4. Folder structure:
   - workspaces (all my work):
     - `admin`
     - `algorithms`
     - `usage`
   - exemples: `files`
   - execution:
     - `bin`
     - `obj`
     - `photos`

5. Principles:
   - the path to a folder always contains at the end of the string "/"
   - gui-function has two components: graphic method, backend method
   - object-oriented programming

## I. **Boot**:

- two ways of running the program: 
  - double-click on ".boot.exe" => opens GUI
  - openning the folder in command prompt
    - type `./name_of_executable *arguments*` 
    - if no arguments provided => opens GUI

### 1. GUI

- buttons:
```
Index 		Name
0 		compress
1 		decompress
2 		information
3 		test_algorithm_string
4 		stop
5 		back
6 		done
7 		select
8 		mkdir
9 		fopen
10 		delete
11 		HUF
12		LZW
```

- file_coordo[0...10] == selected files
- file_coordo[11...infinity] == visible_files

### 2. CMD

- Usage: `./name_of_executable <operation> <algorithm> <nr_input_files> <input_file_paths> <output_path>`
- multiple files can be selectected to be encoded and decoded in one step
- some exemples:
```
& '.\bin\Debug\Better Winrar.exe' compress HUF 1 files/to_encode/element_1/ files/encoded/ unpack

& '.\bin\Debug\Better Winrar.exe' compress HUF 2 files/to_encode/element_1/ files/to_encode/element_2/ files/encoded/ unpack
```


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
	output the part that was already in the dictionary 
	//((strlen(temp)>1) means it is in the dictionary - memory saving method)
	
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

### 1. Tar format (used in my case)

   A tape archive file format is an UNIX-based utility used to package files together. It contains multiple files (tarballs) stored in an uncompressed format. They are often compressed with file compression utilities such as gzip or bzip2.
   Each file object includes its data and a 512-byte record-anthet. Files' data is written unmodified, except that its length is rounded to a multiple of 512 bytes. At the end of the archive file there are two 512-byte blocks, filled with binary zeros, to mark the end of the file. To ensure portability between different architectures with different byte orderings, the information in the header record is encoded in ASCII. TAR files are fully compatible between UNIX and Windows systems because all header information is represented in ASCII.	

On short terms:
- connects files without compression
- the information is encoded in in ASCII
- the order of events: first is the unification of files then we should apply the compression technique
Pros and cons:
+ we can use any compression algorithm after the unification
+ deletes doubled information
- can lose metadata of files (index of files)

how content of the tar file will look like:
```
element_1//
	forth.txt

patru s-a luat
cuci s-au aruncat
hahalero, kokos s-a diluat
am ster so mor decaptat

*5EPArAToR*

	lyrics/
		1.txt

hello world
pleasure to meet youu

*5EPArAToR*

	end_oF_lyrics/
end_oF_element_1//

```

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

### 3. Binary files 

Images: jpg, png, gif, bmp.
Videos: mp4, mkv, avi, mov.
Audio: mp3, aac, wav, flac.
Documents: pdf, doc, xls.
Archive: zip, rar, 7z, tar.
Database: mdb, sqlite.
Executable: exe, dll, so.

### 4. Text files

Web standards: html, xml, css, svg, json, ...
Source code: c, cpp, h, cs, js, py, java, rb, pl, php, sh, ...
Documents: txt, tex, markdown, asciidoc, rtf, ps, ...
Configuration: ini, cfg, rc, reg, ...
Tabular data: csv, tsv, ...

[Source] (https://www.nayuki.io/page/what-are-binary-and-text-files)

## IV **Limitations**:

1. Small number for input paths
2. From the graphical point of view:
- graphics.h is a primitive library [Additional documentation](https://www.programmingsimplified.com/c/graphics.h)

3. 32-bit compiler - it was used such that the project could support graphics.h

## V **Future improvements**:

1. Add more languages:
- [x] english
- [ ] romanian
- [ ] french
- [ ] german

2. announcement box

3. use `temp.tar` as a binary file s. t. binary files coud be read. !!!

## VI **How to set up this project**

1. Have g++ follow al least the C++17 GNU C++ language standard (ISO C++ plus GNU extensions)

2. Install a 32-bit compiler and set it up in your IDE as default

3. Install graphics.h

- set up linker settings: `-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32`
