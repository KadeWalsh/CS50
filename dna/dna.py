import csv
import sys


# check for 2 command line arguments as expected
def checkArgs():
    # if not 2 command line arguments
    if len(sys.argv) != 3:
        # print error message
        print("Usage: dna.py databasefile sequences")
        # exit program
        exit()


# assign filename variable from CL arguments
def setFilenames():
    # create empty dictionary
    filenames = {}

    # set database name from CL arg
    filenames["database"] = sys.argv[1]

    # set sequence file name from CL arg
    filenames["sequence"] = sys.argv[2]

    return filenames


# load database into list to search
def loadDatabase(filenames):
    # set variable for use in function
    database = filenames["database"]
    dbList = []
    # open file
    with open(database, "r") as dbFile:
        # read contents into DictReader object
        reader = csv.DictReader(dbFile)
        # copy rows from reader object to 'dbList'
        for row in reader:
            dbList.append(row)
    # return list to caller
    return dbList


# create list if STRs to search sequence for
def getSTRnames(dbList):
    STRnames = list(dbList[0])
    STRnames = STRnames[1:]
    return STRnames


# load sequence file to search for STR
def loadSequence(filenames):
    # set sequence filename
    sequence = filenames["sequence"]
    # open file
    with open(sequence, "r") as seqFile:
        # read file into 'searchSeq'
        searchSeq = seqFile.readline()
    # return value to caller
    return searchSeq


# check sequence for repeating STR
def checkSequence(searchSeq, STRnames):
    matches = {}
    STRcount = len(STRnames)
    currentSTR = 0

    for subSequence in STRnames:
        currentSTR = longest_match(searchSeq, subSequence)
        matches[subSequence] = str(currentSTR)

    return matches


# search sequence file for longest repeat of each sequence in DB
def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence. """

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


# search DB for matches
def compareToDB(dbList, repeats):
    # set empty value for dnaMatch
    dnaMatch = ""
    # for each person in database
    for person in dbList:
        # check if each STR count matches sequence given
        for STRmatch in repeats:
            # if same then set same true and check next STR
            if person[STRmatch] == repeats[STRmatch]:
                same = True

            # if not same then set same to false and exit loop for this person
            else:
                same = False
                break
        # if same was true for all STR comparisons
        if same == True:
            # set name of dnaMatch to 'name' of person
            dnaMatch = person['name']
            # exit loop of people in database list
            break
    # if dnaMatch set to person name instead of blank default
    if len(dnaMatch) > 0:
        # print name of dnaMatch
        print(dnaMatch)
    # if dnaMatch untouched and still blank default value
    else:
        # print "No match"
        print("No match")


def main():

    # check for command line arguments
    checkArgs()

    # set appropriate filenames for later use
    filenames = setFilenames()

    # load dna database
    dbList = loadDatabase(filenames)

    # get STR names
    STRnames = getSTRnames(dbList)

    # load DNA sequence to use in search
    dnaSequence = loadSequence(filenames)
    # remove any whitespace from list
    dnaSequence = dnaSequence.strip()

    # get count of how many times each STR found
    repeats = checkSequence(dnaSequence, STRnames)

    # compare results of sequence to database
    compareToDB(dbList, repeats)


main()
