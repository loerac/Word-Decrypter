# Word-Decrypter
Enter a word that is encrypted in a substitution format and enter known letters that are in and not in the word. The wordlist and the C++ program need to be in the same folder.

I started this project 2 years ago and I lost that copy. This previous code was the only copy I had left of it and it was not complete. I am working on updating it and finishing it. Again, I started this code 2 years ago, I was learning C++ at that moment so I had a lot of redudent coding and terrible data structuring that I am now fixing.

# Usage:
Enter a encrypted word with the _-w_, enter known characters that are in the encrypted word with _-i_, and enter _-o_ for known characters that aren't in the encrypted word. _-i_ and _-o_ are optional but you need to pass the encrypted word in (_-w_)

# Example:
#### Input:
```
$ ./main -w qwert -i cbs -o plk
```
#### Output:
````
Found: scuba
Current word: qwert
Amount of words: 16
````
From there, you can enter letters that will shrink amount of words found.
