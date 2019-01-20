"""
@author Herbert Nguruwe and Tommaso Ronconi

"""
import datetime
import unittest
from collections import defaultdict
import re


class PostcardList:
    """
     class manages postcards
    """
    def __init__(self, ):
        """"Initialize a tree with all arguments to default 
        value. We decided not  create an abject with a file to 
        read from but  use the methods provided by class.
         """
        self._file = None 
        self._postcards =[]
        self._from = defaultdict(list)
        self._to = defaultdict(list)
        self._date = defaultdict(list)
    
        
    def writeFile(self, _file):
        """ write to a new filew self.{_date,_from,_to} to self._file"""
        with open(self._file, 'w+') as f:
            for p in self._postcards:
                f.write(p)
        f.closed


    def readFile(self,_file):
        """from self._file read self.{_date,_from,_to}"""
        """index = 0
        with open(_file, 'r') as f:
            for line in f:
                self._postcards.append(line)
                values = [s for s in line.split()]
                self._date[values[0]].append(index)
                self._from[values[1]].append(index)
                self._to[values[2]].append(index)
                index = index+1
        f.closed"""

        index = 0
        with open(_file, 'r') as f:
            for line in f:
                self._postcards.append(line)
                values = [s for s in line.split()]
                self._date[re.search(
                    "([0-9]{4}\-[0-9]{2}\-[0-9]{2})", values[0]).group()].append(index)
                self._from[values[1].split(":")[1][:-1]].append(index)
                self._to[values[2].split(":")[1][:-1]].append(index)
                index = index+1
        f.closed

    def parsePostcards(self):
        """parse self._postcards, set self.{_date,_from,_to}"""
        index = 0
        with open(self._file, 'r') as f:
            for line in f:
                self._postcards.append(line)
                values = [s for s in line.split()]
                self._date[re.search(
                    "([0-9]{4}\-[0-9]{2}\-[0-9]{2})", values[0]).group()].append(index)
                self._from[values[1].split(":")[1][:-1]].append(index)
                self._to[values[2].split(":")[1][:-1]].append(index)
                index = index+1
        f.closed

    def updateFile(self):
        """as write but appending to self._file"""
        with open(self._file, 'a+') as f:
            for p in self._postcards:
                f.write(p)
        f.closed

    def updateLists(self):
        """as read but appending to self._postcards"""
        with open(self._file, 'r') as f:
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
        
 
#p = PostCardList("../exam_postcard_list9.txt")
#p.readFile()
#print("\n")
#print(p._from)
#p.getPostcardsBySender("Hook")
#print("\n")
#print("\n")
#p.getPostcardsByReceiver("Happy")
#p.writeFile("test.txt")
#p.updateFile("test.txt")
#print(p.getNumberOfPostcards(to:$crooge;))
#$print(p._date)
#print("\n")
#print(p._from)
#print("\n")
#print(p._to)


