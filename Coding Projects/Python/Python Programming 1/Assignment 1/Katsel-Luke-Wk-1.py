textStr = ''' Between ten and eleven o’clock that morning two messengers were sent in
a taxicab from the East River National Bank, at Broadway and Third
street, to draw $25,000 in currency from the Produce Exchange National
Bank, at Broadway and Beaver street, in the downtown financial district,
and bring it uptown. This transfer of money had been made several times
a week for so long a period without danger or loss that the messengers
were unarmed. One of them, Wilbur F. Smith, was an old man who had been
in the service of the bank thirty-five years, and the other was a mere
boy, named Wardle, seventeen years old. The taxicab man, an Italian
named Geno Montani, seemed almost a trusted employee, too, for he
operated two cabs from a stand near the bank, and was frequently called
upon for such trips.'''

type(textStr)
<class 'str'>
len(textStr)
796
wordsFound=textStr.split()
type(wordsFound)
<class 'list'>
wordsFound.count("the")
8
len(wordsFound)
141
for eachWord in wordsFound:
    if eachWord.istitle():
        print("word is capitalized", eachWord)

word is capitalized Between
word is capitalized East
word is capitalized River
word is capitalized National
word is capitalized Bank,
word is capitalized Broadway
word is capitalized Third
word is capitalized Produce
word is capitalized Exchange
word is capitalized National
word is capitalized Bank,
word is capitalized Broadway
word is capitalized Beaver
word is capitalized This
word is capitalized One
word is capitalized Wilbur
word is capitalized F.
word is capitalized Smith,
word is capitalized Wardle,
word is capitalized The
word is capitalized Italian
word is capitalized Geno
word is capitalized Montani,
