# Damerau-Levenshtein string distance (recursive)


def str_distance(s1, s2):
    s1_len = len(s1)
    s2_len = len(s2)

    if s1_len == 0:
        return s2_len
    if s2_len == 0:
        return s1_len

    match_fault = int(s1[s1_len - 1] != s2[s2_len - 1])
    return min(str_distance(s1[:s1_len - 1], s2[:s2_len]) + 1,
               str_distance(s1[:s1_len], s2[:s2_len - 1]) + 1,
               str_distance(s1[:s1_len - 1], s2[:s2_len - 1]) + match_fault)


if __name__ == "__main__":
    print(str_distance("occasion", "accasion"))
