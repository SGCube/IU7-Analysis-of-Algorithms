# Damerau-Levenshtein string distance (by matrix)


def str_distance(s1, s2):
    s1_len = len(s1)
    s2_len = len(s2)

    # initialization of first two rows
    prev2_row = [0] * (s2_len + 1)
    prev_row = [i for i in range(s2_len + 1)]
    print(prev_row)
    current_row = [0] * (s2_len + 1)

    for i in range(1, s1_len + 1):          # row loop
        # current row fill
        current_row[0] = i
        for j in range(1, s2_len + 1):                  # column loop
            match_fault = int(s1[i - 1] != s2[j - 1])      # if symbol matches
            current_row[j] = min(current_row[j - 1] + 1,         # horizontal
                                 prev_row[j] + 1,                # vertical
                                 prev_row[j - 1] + match_fault)  # diagonal

            # transposition check
            if i > 2 and j > 2:
                if s1[i - 1] == s2[j - 2] and s1[i - 2] == s2[j - 1]:
                    current_row[j] = min(current_row[j],
                                         prev2_row[j - 2] + 1)

        print(current_row)
        # row switching
        prev2_row = prev_row
        prev_row = current_row
        current_row = [0] * (s2_len + 1)

    return prev_row[-1]         # value in bottom right corner of table


if __name__ == "__main__":
    print(str_distance("mispselling", "misspelling"))
