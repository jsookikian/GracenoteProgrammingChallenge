import operator, string, re


class ArtistHandler:

    def __init__(self):
        self.artists = None

    # Part 1
    def readArtistsFromFile(self, filename):
        artistFile = open(filename, 'r')
        # Remove new line character from the artist and add it to the list
        self.artists = [artist.rstrip() for artist in artistFile.readlines()]

    # Part 2
    def getArtistsSortedByLength(self):
        artistsCopy = self.artists[:]
        artistsCopy.sort(key=len, reverse=True)
        return artistsCopy

    # Part 3
    def getUniqueWords(self):
        wordCountMap = dict()
        for artist in self.artists:
            for word in artist.split():
                if _isPunctuation(word):
                    continue
                # Remove punctuation
                word = word.translate(str.maketrans("", "", string.punctuation))
                if word.lower() not in wordCountMap:

                    wordCountMap[word.lower()] = 1
                else:
                    wordCountMap[word.lower()] += 1

        return sorted(wordCountMap.items(), key=operator.itemgetter(1), reverse=True)

    # Part 4
    def getArtistPalindromes(self):
        palindromes = []
        for artist in self.artists:
            palindrome = _buildPalindrome(artist)
            if palindrome is not None:
                palindromes.append((artist, palindrome))
        return palindromes

    # Part 5
    def getArtistCollaborations(self):
        # Filter by artists with multiple spaces
        artistsWithMultipleSpaces = [artist for artist in self.artists if artist.count(" ") > 1]
        # Filter by keywords
        return [_getArtistCollab(artist) for artist in artistsWithMultipleSpaces
                    if _containsCollabKeywords(artist)]



# Takes a word as an input
# Returns a string containing the a palindrome if one exists, else None
def _buildPalindrome(word):
    # We want to keep a list of the characters that have an odd number of occurrences
    singleChars = []
    palindrome = ""
    for char in list(word):
        # If we have not seen this character, add it to the list of characters with odd number of occurrences
        if char not in singleChars:
            singleChars.append(char)
        # If we have seen it, remove it from the list of characters with odd number of occurrences since there are now
        # two occurrences and add it to our palindrome string
        # (effectively building out the first half of the palindrome)
        else:
            palindrome += char
            singleChars.remove(char)
    # A palindrome can only have a max of one character with an odd number of occurrences
    if len(singleChars) > 1:
        return None
    # For odd length strings, there is a single character that the palindrome will pivot on.
    # So we add it, and also add the reversal of the first half of palindrome we've already constructed
    elif len(singleChars) == 1:
        return palindrome + singleChars[0] + palindrome[::-1]
    # Append the reversal of the first half of the palindrome we constructed, since we've already accounted for letters with
    # an even number of occurrences.
    else:
        return palindrome + palindrome[::-1]


# This function should not be used with any strings that have not already been validated,
# or it will return false results.
def _getArtistCollab(artist):
    # Acts like the normal string.split() method, but allows for keywords.
    # '(?i)' makes the regex case insensitive
    return (artist, re.split(",|&|;|:|feat.|vs.(?i)", artist))


def _containsCollabKeywords(artist):
    artist_lower = artist.lower()
    if "," in artist_lower or \
        "&" in artist_lower or \
        ";" in artist_lower or \
        ":" in artist or \
        "feat." in artist_lower or \
        "vs." in artist_lower or \
        " x " in artist_lower:
        return True
    else:
        return False

def _isPunctuation(word):
    punctuation = set("!?&-=+,.';:\"")
    return word in punctuation
