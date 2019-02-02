"""
@author Herbert Nguruwe and Tommaso Ronconi

Intresting notes:
Initially the  class was implemented using the defaultdict class 
from collections  package. This caused  problems with the method test
(test_check_sent_received_when)which is implemented using try-catch 
statement, so defaultdict doesn't return an error when  trying to 
access  an item that is not there it creates a new item. In this 
case it would create an empty list rather than throwing an exception.

All other functions passed the test.Defaultdict takes a type to initialize
as a default type.

"""
import datetime
import unittest
from collections import defaultdict
from datetime import datetime as dt
import re


class PostcardList:
    """
     class manages a list of post cards, that are added from a file.It
     reads a file where each line represents a postcard with to, from,
     and date when the post card was sent.
    """
    def __init__(self):
        """"Initialize a tree with all arguments to default
        value. We decided to create an object withtout a file to
        read from but use the methods provided by class. This is
        design passed by the class.
         """
        self._file = None
        self._postcards =[]
        # self._from = defaultdict(list)
        # self._to = defaultdict(list)
        # self._date = defaultdict(list)
        self._from = {}
        self._to = {}
        self._date = {}


    def writeFile(self, _file):
        """
        write to a new file self.{_date,_from,_to} to self._file.
        @param _file: inputfile to be written to using data  from
        object's _postcard's list member.
        """
        self._file = _file
        with open(self._file, 'w') as f:
            for p in self._postcards:
                f.write(p)
        f.closed

    def readFile(self,_file):
        """
        Read from a file to self._postcardlist.
        @param _file: inputfile to be written to using data that from
        object's _postcard's list member. Call the update list function
        """
        self._file = _file
        self.updateLists(_file)


    def parsePostcards(self, _postcard):
        """
        @param _postcard: list of postcards in the case object's.
        parse self._postcards, set self.{_date,_from,_to}
        and  return to the calling function
        """
        _date, _from, _to = _postcard.split()
        _date = _date.split(":")[1][:-1]
        _from = _from.split(":")[1][:-1]
        _to = _to.split(":")[1][:-1]
        return _date,_from,_to


    def updateFile(self):
        """
        Append to a self.{_date,_from,_to} to self._file.
        @param _file: outputfile to be updated using data from
        object's _postcard's list member.
        """
        with open(self._file, 'a+') as f:
            for p in self._postcards:
                f.write(p)
        f.closed

    def updateLists(self, _file):
        """
        Update the object's _postcardlist with
        postcards from  the passed file.
        @param _file: the file to be read from to
        update the _postcardlist.
        """
        self._file = _file
        with open(self._file, 'r') as f:
            for line in f:
                print(line.strip())
                index = self.getNumberOfPostcards()
                self._postcards.append(line)
                _date, _from, _to = self.parsePostcards(line)
                # self._date[_date].append(index)
                # self._from[_from].append(index)
                # self._to[_to].append(index)
                self.add_to_list(self._date, _date, index)
                self.add_to_list(self._from, _from, index)
                self.add_to_list(self._to, _to, index)

        f.closed

    def add_to_list(self, _dict,_key,_index):
        """
        @param _dict: dictionary to be added
        @param _key: key to be used 
        @param _index: The index of the record
        Function used to add an item to the dictionary
        """
        if not _key in _dict:
            _dict[_key]=list()
        _dict[_key].append(_index)

    def getNumberOfPostcards(self):
        """
        returns the number of postcards
        @return int: Number of postcards in the self._postcards
        """
        return len(self._postcards)

    def getPostcardsByDateRange(self,date_range):
        """
        returns the postcards within a date_range
        @param date_range : search for all the postcards
        that were  within the range that was passed.
        @return: list of postcards sent within the range.
        """
        dates_range = []
        date_start = date_range[0]
        date_end = date_range[1]
        fmt = "%Y-%m-%d"
        for dat in self._date.keys():
            if(dt.strptime(dat, fmt) >= date_start and dt.strptime(dat, fmt) <= date_end):
                dates_range +=[self._postcards[x] for x in self._date[dat]]
        return dates_range

    def getPostcardsBySender(self,sender):
        """
        returns the postcards from a sender.
        @param sender: search for all the postcards
        that were sent by sender
        @return: list of postcards send by the sender.
        """
        post_cards = []
        if sender in self._from:
            post_cards = [self._postcards[i]
                          for i in self._from[sender]]
        return post_cards

    def getPostcardsByReceiver(self, receiver):
        """
        get postcards send to a receiver
        @param receiver: search for all the postcards
        that were sent by Sender
        @return: list of postcards send by the sender.
        """
        post_cards=[]
        if receiver in self._to:
            post_cards = [self._postcards[i]
                          for i in self._to[receiver]]
        return post_cards




