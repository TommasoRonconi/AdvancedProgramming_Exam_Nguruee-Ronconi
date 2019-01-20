"""
@author Herbert Nguruwe and Tommaso Ronconi

"""
import datetime
import unittest
from collections import defaultdict

class PostCardList:
    """
     class manages postcards
    """

    def __init__(self):
        """"Initialize a  tree with all arguments """
        self._file = None
        self._postcards =[]
        self._from = defaultdict(list)
        self._to = defaultdict(list)
        self._date = defaultdict(list)
    
        
    def writeFile(self, write_file):
        """ write self.{_date,_from,_to} to self._file"""
        with open(write_file, 'w+') as f:
            for p in self._postcards:
                f.write(p)
        f.closed


    def readFile(self, _file):
        """from self._file read self.{_date,_from,_to}"""
        index = 0
        with open(_file, 'r') as f:
            for line in f:
                self._postcards.append(line)
                values = [s for s in line.split()]
                self._date[values[0]].append(index)
                self._from[values[1]].append(index)
                self._to[values[2]].append(index)
                index = index+1
        f.closed

    def parsePostcards(self,_file):
        """parse self._postcards, set self.{_date,_from,_to}"""
        pass

    def updateFile(self, write_file):
        """as write but appending to self._file"""
        with open(write_file, 'a+') as f:
            for p in self._postcards:
                f.write(p)
        f.closed

    def updateLists(self, _file):
        """as read but appending to self._postcards"""
        with open(_file, 'r') as f:
            for line in f:
                self._postcards.append(line)
        f.closed
        
    def getNumberOfPostcards(self):
        """returns length of self._postcards"""
        return len(self._postcards)

    def getPostcardsByDateRange(self,date_range):
         """ returns the postcards within a date_range"""
         pass

    def getPostcardsBySender(self,sender):
        """returns the postcards from a sender"""
        lines = self._from[sender]
        for l in lines:
            print(self._postcards[int(l)].strip())
    

    def getPostcardsByReceiver(self, receiver): 
        """returns the postcards to a receiver"""
        lines = self._to.get(receiver)
        for l in lines:
            print(self._postcards[int(l)].strip())
        
 
p = PostCardList()
p.readFile("exam_postcard_list9.txt")
#print("\n")
#print(p._from)
p.getPostcardsBySender("from:Hook;")
print("\n")
print("\n")
p.getPostcardsByReceiver("to:$crooge;")
#p.writeFile("test.txt")
#p.updateFile("test.txt")
#print(p.getNumberOfPostcards(to:$crooge;))
#print(p._date)
#print("\n")
#print(p._from)
#print("\n")
#print(p._to)


