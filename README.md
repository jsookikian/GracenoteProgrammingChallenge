# Gracenote Music Programming Challenge


# Program 1
This solution was implemented in Python 3.6
# Running
To run this program, use the following command
```
python3 main.py
```
## Part 1 and Part 2 - Read Artists From File and Sort by Artist Length
Parts 1 and 2 were very straightforward, and I was able to leverage existing python libraries to read and sort the artists.


## Part 3 - Word Frequency Counter
To count the unique words and their frequencies within the artists list, I create a dictionary to store each word and its number of occurrences while iterating through the list.


## Part 4 - Artist Palindromes
If a string has a palindrome, it can have at most 1 letter with an odd number of occurrences. Using this to an advantage, we keep a list of letters that have only one occurrence. If we see that letter again, then add that letter to the palindrome string and remove it from our list. This effectively builds the first half of the palindrome as we iterate through the string. 

Then, after iterating through the whole artist string, if the list containing letters with odd number of occurrences has more than one letter in it, then we cannot create a palindrome.

If we pass this check, then we add the extra letter in the list to our palindrome (if there is one), and add the reverse of the first half of the palindrome we created to complete the palindrome. 



## Part 5 - Artist Collaborations
### Initial Implementation
First, we take our list of artists and filter out every artist that does not contain any spaces since a collaboration is marked with an ampersand, comma, semicolon, colon, the string "feat.", the string "vs."
and must have more than one space in it. 
Then, we filter by keywords and special characters that indicate a collaboration, and perform a regex split on the artist string which divides the artist up into multiple artists in a list. 

### Going Forward

If provided with a larger dataset including songs and artists, we could create a database full of metadata for each artist. Then when we come across a song with artists that appears to be a collaboration (passes through filters and validations), then we can cross reference the supposed artist collaborations with our metadata to see if those artists have songs out under their own names.


# Program 2 - TabFlip

I chose to implement this program in C because Gracenote primarily uses C and python.


# Running
To run this program, use the following command
```

make
./tab_flip /path/to/tab/file > path/to/output
```

In this program, I chose to read each line into a string buffer, placing it into a Tab struct
```
typedef struct {
    char *strings[6];
    int stringBufIndices[6];
} Tab;
```

The string buffer indices are used while parsing the tab to keep track of how much of the buffer we have read so far.

### Going Forward

If I had more time for this project, I would have liked to implement a more complete tab reader that includes support for reading tabs that include string bends and returns, slides, vibrato, hammer-ons, and pull-offs. 