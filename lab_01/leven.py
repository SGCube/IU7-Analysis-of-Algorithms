# Levenshtein string distance


def str_distance(s1, s2):
    s1_len = len(s1)
    s2_len = len(s2)

    # initialization of first two rows
    prev_row = [i for i in range(s2_len + 1)]   # first row - [0, 1, ..., n]
    print(prev_row)
    current_row = [0] * (s2_len + 1)

    for i in range(1, s1_len + 1):          # row loop
        # current row fill
        current_row[0] = i
        for j in range(1, s2_len + 1):                  # column loop
            match_fault = int(s1[i - 1] != s2[j - 1])            # symbol match
            current_row[j] = min(current_row[j - 1] + 1,         # horizontal
                                 prev_row[j] + 1,                # vertical
                                 prev_row[j - 1] + match_fault)  # diagonal

        print(current_row)
        # row switching
        prev_row = current_row
        current_row = [0] * (s2_len + 1)

    return prev_row[-1]     # value in bottom right corner of table


if __name__ == "__main__":
    print(str_distance("error", "horror"))
