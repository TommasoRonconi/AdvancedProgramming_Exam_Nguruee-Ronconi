"""
@author Herbert Nguruwe and Tommaso Ronconi

"""
import datetime
import unittest

class PostCardList:
    """
     class manages postcards
    """

    def __init__(self, _file, _postcards, _date, _from, _to ):
        """"Initialize a  tree with all arguments """
        self._file = _file
        self._postcards = _postcards
        self._from = _from
        self._to = _to 
    
    def writeFile(self,_file):
        """ write self.{_date,_from,_to} to self._file"""
        pass

    def readFile(self,_file):
        """from self._file read self.{_date,_from,_to}"""
        pass

    def parsePostcards(self,_file):
        """parse self._postcards, set self.{_date,_from,_to}"""
        pass

    def updateFile(self,_file):
        """as write but appending to self._file"""
        pass

    def updateLists(self,_file):
        """as read but appending to self._postcards"""
        pass
    
    def getNumberOfPostcards(self):
        """returns length of self._postcards"""
        pass


    def getPostcardsByDateRange(self,date_range):
         """ returns the postcards within a date_range"""
         pass

    def getPostcardsBySender(self, sender):
        """returns the postcards from a sender"""
        pass

    def getPostcardsByReceiver(self, receiver): 
        """returns the postcards to a receiver"""
        pass


 
