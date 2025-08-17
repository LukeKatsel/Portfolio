Python 3.11.2 (tags/v3.11.2:878ead1, Feb  7 2023, 16:38:35) [MSC v.1934 64 bit (AMD64)]
Type "help", "copyright", "credits" or "license" for more information.
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
wordsFound = textStr.split()
print(wordsFound)
['Between', 'ten', 'and', 'eleven', 'o’clock', 'that', 'morning', 'two', 'messengers', 'were', 'sent', 'in', 'a', 'taxicab', 'from', 'the', 'East', 'River', 'National', 'Bank,', 'at', 'Broadway', 'and', 'Third', 'street,', 'to', 'draw', '$25,000', 'in', 'currency', 'from', 'the', 'Produce', 'Exchange', 'National', 'Bank,', 'at', 'Broadway', 'and', 'Beaver', 'street,', 'in', 'the', 'downtown', 'financial', 'district,', 'and', 'bring', 'it', 'uptown.', 'This', 'transfer', 'of', 'money', 'had', 'been', 'made', 'several', 'times', 'a', 'week', 'for', 'so', 'long', 'a', 'period', 'without', 'danger', 'or', 'loss', 'that', 'the', 'messengers', 'were', 'unarmed.', 'One', 'of', 'them,', 'Wilbur', 'F.', 'Smith,', 'was', 'an', 'old', 'man', 'who', 'had', 'been', 'in', 'the', 'service', 'of', 'the', 'bank', 'thirty-five', 'years,', 'and', 'the', 'other', 'was', 'a', 'mere', 'boy,', 'named', 'Wardle,', 'seventeen', 'years', 'old.', 'The', 'taxicab', 'man,', 'an', 'Italian', 'named', 'Geno', 'Montani,', 'seemed', 'almost', 'a', 'trusted', 'employee,', 'too,', 'for', 'he', 'operated', 'two', 'cabs', 'from', 'a', 'stand', 'near', 'the', 'bank,', 'and', 'was', 'frequently', 'called', 'upon', 'for', 'such', 'trips.']
wordsFound.sort
<built-in method sort of list object at 0x000001C01638E740>
wordsFound.sort()
len(wordsFound.sort)
Traceback (most recent call last):
  Python Shell, prompt 8, line 1
builtins.TypeError: object of type 'builtin_function_or_method' has no len()
len(wordsFound.sort())
Traceback (most recent call last):
  Python Shell, prompt 9, line 1
builtins.TypeError: object of type 'NoneType' has no len()
wordList = wordsFound.sort()
len(wordList)
Traceback (most recent call last):
  Python Shell, prompt 11, line 1
builtins.TypeError: object of type 'NoneType' has no len()
wordFoundSet = set(wordsFound)
wordFoundList = list(wordFoundSet)
len (wordFoundList)
99
for words in wordsFound
Traceback (most recent call last):
  Python Shell, prompt 15, line 1
Syntax Error: expected ':': <string>, line 1, pos 24
count = 0
for words in wordsFound:
    if words.istitle():
        count += 1
print(count)

23
