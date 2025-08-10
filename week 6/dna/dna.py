import csv
import sys


def main():

    # TODO: Check for command-line usage
    arguments = sys.argv

    if len(arguments) != 3:
        print("Invalid command-line argument")
        sys.exit(1)
    else:
        filename = sys.argv[1]
        filename_text_file = sys.argv[2]



    # TODO: Read database file into a variable
    with open(filename, "r") as file:
        reader = csv.DictReader(file)
        database = list(reader)
        Strs = reader.fieldnames[1:]

    # TODO: Read DNA sequence file into a variable
    #sequence = ""
    with open(filename_text_file, encoding = "utf-8") as f:
        sequence = f.read().strip()

    # TODO: Find longest match of each STR in DNA sequence
    longest_m = {}

    for STR in Strs:
        longest_m[STR] = longest_match(sequence, STR)


    # TODO: Check database for matching profiles
    for person in database:
        match = True
        for STR in Strs:
            if int(person[STR]) != longest_m[STR]:
                match = False
                break
        if match:
            print(person['name'])
            return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

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

            # If there is a match in the substring9
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
