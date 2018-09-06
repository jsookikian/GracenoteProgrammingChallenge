from ArtistHandler import ArtistHandler

def main():
    artistHandler = ArtistHandler()
    artistHandler.readArtistsFromFile("artistnames.txt")

    print ("--- Printing Artists Sorted By Length ---")
    sortedArtists = artistHandler.getArtistsSortedByLength()
    printSortedArtists(sortedArtists)

    print ("\n\n--- Printing Unique Words and their Frequency ---")
    uniqueWordMap = artistHandler.getUniqueWords()
    printUniqueWords(uniqueWordMap)

    print ("\n\n--- Printing Artist Palindromes ---")
    palindromes = artistHandler.getArtistPalindromes()
    printArtistPalindromes(palindromes)

    print ("\n\n--- Printing Artist Collaborations ---")
    collabs = artistHandler.getArtistCollaborations()
    printArtistCollaborations(collabs)


def printSortedArtists(artists):
    for artist in artists:
        print(str(len(artist)) + "\t" + artist)

def printUniqueWords(wordCountMap):
    for key, value in wordCountMap:
        print("{0}\t{1}".format(str(value), key))

def printArtistPalindromes(palindromes):
    for artist, palindrome in palindromes:
        print(artist + " => " + palindrome)

def getArtistCollabString(artistString, collabList):
    collabString = ""
    for ndx, artist in enumerate(collabList):
        if ndx < len(collabList) - 1:
            collabString += artist.strip() + " (AND) "
        else:
            collabString += artist.strip()
    return artistString + " => " + (collabString)

def printArtistCollaborations(artistCollaborations):
    for artist, collabList in artistCollaborations:
        print(getArtistCollabString(artist, collabList))


if __name__ == "__main__":
    main()
