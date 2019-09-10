# Damerau-Levenshtein string distance (recursive)


def str_distance(s1, s2):
    s1_len = len(s1)
    s2_len = len(s2)

    if s1_len == 0:
        return s2_len
    if s2_len == 0:
        return s1_len

    match_fault = int(s1[-1] != s2[-1])

    result = min(str_distance(s1[:-1], s2) + 1,
                 str_distance(s1, s2[:-1]) + 1,
                 str_distance(s1[:-1], s2[:-1]) + match_fault)

    if s1_len > 1 and s2_len > 1:
        if s1[-1] == s2[-2] and s1[-2] == s2[-1]:
            result = min(result, str_distance(s1[:-2], s2[:-2]) + 1)

    return result


if __name__ == "__main__":
    print(str_distance("университте", "университет"))
