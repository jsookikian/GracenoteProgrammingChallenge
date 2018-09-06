import unittest
from ArtistHandler import ArtistHandler

class TestArtistHandler(unittest.TestCase):

    def testReadArtistsFromFile(self):
        artistHandler = ArtistHandler()
        artistHandler.readArtistsFromFile("artistsSample.txt")
        self.assertTrue(artistHandler.artists[0], "The Red Hot Chili Peppers")
        self.assertEqual(len(artistHandler.artists), 14)


    def testGetUniqueWords(self):
        artistHandler = ArtistHandler()
        artistHandler.readArtistsFromFile("artistsSample.txt")
        uniqueWords = artistHandler.getUniqueWords()
        self.assertEqual(uniqueWords[0], ("the", 4))
        self.assertEqual(uniqueWords[1], ("john", 3))
        self.assertEqual(uniqueWords[2], ("frusciante", 2))


    def testGetPalindromes(self):
        artistHandler = ArtistHandler()
        artistHandler.readArtistsFromFile("artistsSample.txt")
        palindromes = artistHandler.getArtistPalindromes()
        self.assertEqual(palindromes[0][1], "carerac")
        self.assertEqual(palindromes[1][1], "lzela alezl")

    def testGetArtistCollaborations(self):
        artistHandler = ArtistHandler()
        artistHandler.readArtistsFromFile("artistsSample.txt")
        collabs = artistHandler.getArtistCollaborations()
        self.assertTrue(str(collabs[0]), "Crosby, Stills, Nash => Crosby (AND) Stills (AND) Nash")
        self.assertTrue(str(collabs[1]), "Jeff Beck & Rod Stewart => Jeff Beck (AND) Rod Stewart")
        self.assertTrue(str(collabs[2]), "Beyonce Feat. Jay Z => Beyonce (AND) Jay Z")
        self.assertTrue(str(collabs[3]), "John Frusciante Vs. Josh Klinghoffer => John Frusciante (AND) Josh Klinghoffer")



if __name__ == "__main__":
    unittest.main()