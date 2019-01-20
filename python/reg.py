import re
import datetime

with open("exam_postcard_list9.txt", 'r') as f:
    for line in f:
        values = [s for s in line.split()]
        match = re.search("^From", values[0])
        date = datetime.datetime.strptime(match.group(), '%Y-%m-%d').date()
        print(date)
f.closed
