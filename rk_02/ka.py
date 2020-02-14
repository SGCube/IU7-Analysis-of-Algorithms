enter_str = "::EnterCriticalSection"
leave_str = "::LeaveCriticalSection"

name_symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvxyz_"
digits = "0123456789"


def find_crit(s):
    state = 1
    crit_section = ""
    result = []

    for value in s:
        if state == 1:
            if value == ':':
                state = 2
        elif 2 <= state <= 22:
            if value == enter_str[state - 1]:
                state += 1
            else:
                state = 1
        elif state == 23:
            if value == '(':
                state = 24
            else:
                state = 1
        elif state == 24:
            if value == '&':
                state = 25
            elif value in name_symbols:
                state = 26
            else:
                state = 1
        elif state == 25:
            if value in name_symbols + digits:
                state = 26
            else:
                state = 1
        elif state == 26:
            if value in name_symbols + digits:
                state = 26
            elif value == ')':
                state = 27
            else:
                state = 1
        elif state == 27:
            if value == ';':
                state = 28
            else:
                state = 1

        elif state == 28:
            if value == ':':
                state = 29

        elif 29 <= state <= 49:
            if value == leave_str[state - 28]:
                state += 1
            else:
                state = 28
        elif state == 50:
            if value == '(':
                state = 51
            else:
                state = 28
        elif state == 51:
            if value == '&':
                state = 52
            elif value in name_symbols:
                state = 53
            else:
                state = 28
        elif state == 52:
            if value in name_symbols + digits:
                state = 53
            else:
                state = 28
        elif state == 53:
            if value in name_symbols + digits:
                state = 53
            elif value == ')':
                state = 54
            else:
                state = 28
        elif state == 54:
            if value == ';':
                state = 55
            else:
                state = 28

        if state == 1:
            crit_section = ""
        else:
            crit_section += value

        if state == 55:
            result.append(crit_section)
            crit_section = ""
            state = 1

    return result


code = '''do_work(12);
::EnterCriticalSection(&m_obj);
do_work(1);

for (int i = 0; i < 5; i++)
{
    do_work(5);
    do_work(4);
    if (boolvar)
        do_work(7);
    else
        do_work(6);
}
do_work(4);
::LeaveCriticalSection(&m_obj);
do_work(3);

do_work(12);
for (int i = 0; i < 5; i++)
{
    do_work(5);
    do_work(4);
    if (boolvar)
        do_work(7);
    else
        do_work(6);
}

::EnterCriticalSection(&m_obj2);
do_work(1);
if (boolvar)
    do_work(7);
else
    do_work(6);
do_work(4);
::LeaveCriticalSection(&m_obj3);
do_work(3);

if (boolvar)
{
    ::EnterCriticalSection(&m_obj2);
    do_work(1);
    if (boolvar)
        do_work(7);
    else
        do_work(6);
    do_work(4);
    ::LeaveCriticalSection(&m_obj2);
}
::LeaveCriticalSection(&m_obj2);
'''

if __name__ == '__main__':
    sections = find_crit(code)
    for section in sections:
        print("############")
        print(section)
    print("############")






























