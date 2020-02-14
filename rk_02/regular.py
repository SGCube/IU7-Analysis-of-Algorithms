import re

regexp0 = r'::EnterCriticalSection\(([A-Za-z&]\w*)\);' +\
         r'([\s\S])*' +\
         r'::LeaveCriticalSection\(\1\);'

regexp1 = r'::EnterCriticalSection\(([A-Za-z&]\w*)\);' +\
         r'((?!::EnterCriticalSection\(.*\);|' +\
         r'::LeaveCriticalSection\([^\1]\);)[\s\S])*' +\
    r'::LeaveCriticalSection\(\1\);'

regexp = r'::EnterCriticalSection\(([A-Za-z&]\w*)\);' +\
         r'((?!::EnterCriticalSection\(\1\);)[\s\S])*' +\
    r'::LeaveCriticalSection\(\1\);'


def find_crit(text):
    # i = 0
    # while len(text) <= i + 10:
    # tmp_stroke = text[i: i + 10]
    tmp = text

    found = False
    match = ""

    while match is not None:
        match = re.search(regexp, tmp)
        if match is not None:
            found = True
            print(match[0])
            tmp = tmp[match.end():]
            print("############")

    if not found:
        print("None")


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
    print("############")
    find_crit(code)
