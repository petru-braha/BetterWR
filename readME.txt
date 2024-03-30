# Archive file viewer
# Used data structures: Binary trees, Priority Queue, Heap, Dictionary, Stack, Hash Table (Map)

# Huffman Algorithm
    Creation of a Priority Queue Q, which contains each character
    Sorting in ascending order of their frequencies 
    For all unique characters:
        Create a newNode
        Extraction of the minimum value from Q and assigning it to the leftChild of the newNode 
        Retrieving the minimum value from Q and assigning it to the right child rightChild of newNode
        Computing the sum of the two minimum values and assigning this value to the newNode
        Inserting the newNode into the tree
    return root

	Huffman encoding involves computing the frequency for each unique character that appears in the initial string. Once we obtain the necessary information (each character and its corresponding frequency), we will store it in a map that will be used to build the Huffman tree, necessary for both encoding and decoding. Based on the tree, we convert the initial string into a string of binary values, which will then be grouped in groups of 8 to form a byte and converted into the corresponding ASCII character. Finally, the resulting string is encoded and ready to be written to the output file. Also in this file we will keep the information needed to reconstruct the tree, i.e. each character together with its frequency plus the size of the tree. When we read the contents of the file to perform the decoding, we make sure that we first read the tree data correctly and then read the encoded string. Decoding will be done by traversing the reconstructed tree, and when the encoded value corresponding to a character is found, we will write it to our created decoding string.

# Lempel-Ziv-Welch Algorithm
    	Enconding:
    	repeat
	    repeat
		    if temp is in dictionary
			    add the following character
	    until it is no longer in the dictionary
	    add it to the dictionary
	    output the part that was already in the dictionary (considering that the dictionary contains at the beginning all the char elements from 0 to 255; (strlen(temp>1) is equivalent to talking about something in the dictionary, it is a memory saving method)
	    reset variables 
    	until they reach the end of the input

   	Decode: 
    	basic principle: the first character is always in the dictionary and the second character if it is not, means it is a copy of the previous one
    	repeat
	    if not in dictionary next
		    copy previous
	    else
		    we put it in the analysis on next
	    output<<temp
	    add to dictionary(previous, current)
	    until final input

	The Lempel-Ziv-Welch (LZW) algorithm is a common lossless data compression algorithm. Because it is a lossless compression algorithm, there is no loss of data during compression. LZW (Lempel-Ziv-Welch) is named after the scientists who developed it, Abraham Lempel, Jakob Ziv and Terry Welch. LZW is a "dictionary-based" lossless compression algorithm that scans a file for data patterns that occur multiple times. These patterns are then saved in a dictionary, and references are placed in the compressed file whenever repetitive data occurs. In hardware implementations, the algorithm is simple and has the potential for very high throughput. It is the algorithm used in the GIF image format and is part of the widely used Unix file compression utility Compress.

# Formatul TAR 
    Un format de fișier TAR (tape archive) este o arhivă creată de tar, un utilitar bazat pe UNIX, folosit pentru a împacheta fișierele împreună , în scopuri de backup sau distribuție. Acesta conține mai multe fișiere (cunoscute și sub numele de tarball) stocate într-un format necomprimat, împreună cu metadate despre arhivă. Fișierele TAR nu sunt fișiere de arhivă comprimate. Acestea sunt adesea comprimate cu utilitare de compresie a fișierelor, cum ar fi gzip sau bzip2.
    Fiecare obiect fișier include orice date de fișier și este precedat de o înregistrare-antet de 512 octeți. Datele fișierului sunt scrise nemodificate, cu excepția faptului că lungimea lor este rotunjită la un multiplu de 512 octeți. La sfârșitul fișierului arhivă există două blocuri de 512 octeți, umplute cu zerouri binare, pentru a marca sfârșitul de fișier. Înregistrarea-antet fișier conține metadate despre un fișier. Pentru a asigura portabilitatea între diferite arhitecturi cu diferite ordonari de octeți, informațiile din înregistrarea-antet sunt codificate în ASCII. Arhivele TAR sunt pe deplin compatibile între sistemele UNIX și Windows, deoarece toate informațiile antetului sunt reprezentate în ASCII.
    Formatul de fișier TAR s-a schimbat în timp, deoarece au fost dezvoltate funcționalități suplimentare pentru utilitarul tar UNIX, ceea ce a dus la extensii de format care includ informații suplimentare pentru implementările necesare, începând cu anii 1980. Versiunile timpurii ale formatelor TAR au fost inconsecvente în modul în care au fost construite câmpurile numerice, care au fost corectate în implementările ulterioare, pentru a îmbunătăți portabilitatea formatului, începând cu primul standard POSIX pentru formatele de fișiere tar în 1988.
    Formatul de fișier tar nu conține compresie nativă a datelor, astfel încât arhivele tar sunt adesea comprimate cu un utilitar extern, cum ar fi; gzip, bzip2, XZ (folosind algoritmi de compresie 7-Zip / p7zip LZMA / LZMA2), Brotli, Zstandard și instrumente similare pentru a reduce dimensiunea arhivei pentru portabilitate și backup de date. Fișierele comprimate rezultate pot fi găsite numite cu extensie unică, de ex. tgz, tbz, txz, tzst, sau cu extensie de fișier dublu, de exemplu tar.gz, tar.br, tar.bz2, tar.xz, tar.zst.

# Formatul ZIP
    Un fișier cu extensia .zip este o arhivă care poate deține unul sau mai multe fișiere sau directoare. Arhiva poate avea compresie aplicată fișierelor incluse pentru a reduce dimensiunea fișierului ZIP. Formatul fișierului ZIP a fost făcut public încă din februarie 1989 de Phil Katz pentru a realiza arhivarea fișierelor și folderelor. Formatul a fost făcut parte din utilitarul PKZIP, creat de PKWARE, Inc. Imediat ce specificațiile existente în momentul respectiv au fost făcute disponibile, multe companii au făcut ca formatul de fișier ZIP să facă parte din utilitățile lor software, inclusiv Microsoft (din Windows 7), Apple (Mac OS X) și multe altele.
    Fișierul este o arhivă comprimată care suportă compresia fără pierderi a datelor. Este adesea utilizat pentru a trimite atasamente de e-mail, cu fermoar; în acest fel mesajul nu poate fi blocat de filtrele de server de e-mail. Acesta poate fi, de asemenea, utilizat pentru ascunderea unui tip de fișier sau pentru a preveni deschiderea acestuia.
    Există numeroase alte standarde și formate care folosesc “zip” ca parte din numele lor. Phil Katz a declarat că a vrut să permită numele “zip” pentru orice tip de arhivă. De exemplu, zip este diferit de gzip, iar acesta din urmă este definit într -un IETF RFC (RFC 1952). Atât zip cât şi gzip folosesc în primul rând algoritmul DEFLATE pentru compresie. De asemenea, formatul ZLIB (IETF RFC 1950), de asemenea, foloseşte algoritmul de compresie DEFLATE, dar precizează diferite anteturi de eroare și verificarea consistenței. Alte formate şi programe comune denumite similar, cu diferite formate native, includ 7-Zip, bzip2, și rzip.


Schelet EXTRA SIMPLIFICAT:
Tar
Huffman
Lempel-Ziv-Welch
Grafica
Comezi-command_prompt


Lempel
    - memoria pentru dictionar + memoria mesajului comprimat < memoria mesajului necomprimat (eu nu trebuie sa memorez dictionarul)
    - construiesti dictionar pe parcurs, asadar nu trimiti dictionarul cu mesajul comprimat (the receiver will constructor decoder alone)
    - 4096 - table entries (first 255 - octeti unici din fisierul de intrare) →hash map
    - `Initialize table with single character strings`
    - foarte bun pentru sirurile lungi si repetitive
    - **Advantages of LZW over [Huffman](https://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/):**
    
    - no prior information about the input data stream
    
    - compress the input stream in one single pass
    
    - fast execution




I.	LZW codare: EXTRA SIMPLIFICAT
repeta
	repeta
		daca temp e in dictionar
			ii adaug urmatorul caracter
	pana cand nu mai e in dictionar
	il adaug in dictionar
	output partea care era deja in dictionar (considerand ca dictionarul contine la inceput toate elementele char de la 0 la 255; (strlen(temp>1) este echivalent cu faptul ca se vorbeste de ceva din dictionar, este o metoda de salva memorie)
	reinitiliazez variabilele
pana cand ajung la finalul inputului

II.	LZW decodare: EXTRA SIMPLIFICAT
pricipiu de baza: primul caracter e mereu in dictionar si al doilea daca nu e, inseamna ca e copia anteriorului

repeta
	daca nu e in dictionar next
		copierea anteriorului
	else
		il punem in analiza pe next
	output<<temp
	adaugare in dictionar(anterior, current)
pana cand final input


Tar format:
- linux
- connects files without compression
- within the same window size, for exemple: one of the 2 files w the same info can be eliminated to save 50% space 
- the information is encoded in in ASCII
- the order of events: first is the unification of files then we should apply the compression technique

+ ca e poti folosi oricare algoritm de compresie dupa
+ elimina informatie dubla
- metadata in the end (posibil sa pierzi index fiecarui fisier -> indexed_tar_files)

VS

ZIP format
- the order of events: firstly individual compression of the files then the unification

+ poti vizualiza si dezarhiva doar un singur element al arhivei
+ paraleliza procesul de arhivare pe CPU -> mai rapid
- compresion ratio -- (unesti dubluri, ceva ce este redundant)

Buttons:
0 arhivare
1 dezarhivare
2 info
3 STOP
4 INAPOI
5 GATA
6 selecteaza
7 mkdir
8 fopen
9 delete
10 HUF
11 LZW
12 //pentru anunturi (de facut)

primele 10 spatii din file_coordo sunt pentru selectate
11->infinit for visible_files