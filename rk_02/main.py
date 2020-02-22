import ka
import regular
from time import perf_counter

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
    file = open("report/time.csv", "w")
    file.write("KA;RegExp\n")
    for k in range(0, 20):
        ka_time = 0
        for i in range(0, 100):
            begin = perf_counter()
            ka.find_crit(code)
            end = perf_counter()
            ka_time += end - begin
        ka_time /= 100

        reg_time = 0
        for i in range(0, 100):
            begin = perf_counter()
            regular.find_crit(code)
            end = perf_counter()
            reg_time += end - begin
        reg_time /= 100

        file.write("%f;%f\n" % (ka_time, reg_time))
    file.close()
