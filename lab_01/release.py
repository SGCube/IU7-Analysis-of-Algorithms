# Release program

import leven as lev
import damerau_leven_r as dam_r
import damerau_leven_m as dam_m

if __name__ == "__main__":
    s1 = input("Введите первую строку: ")
    s2 = input("Введите вторую строку: ")

    print("\nЛевенштейн:")
    print(str(lev.str_distance(s1, s2, True)))
    print("\nДамерау-Левенштейн (матричный):")
    print(str(dam_m.str_distance(s1, s2, True)))
    print("\nДамерау-Левенштейн (рекурсивный): " +
          str(dam_r.str_distance(s1, s2)))

