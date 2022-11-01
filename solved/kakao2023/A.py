from datetime import date, datetime, timedelta
from dateutil.relativedelta import relativedelta


def solution(today, terms, privacies):
    answer = []
    t = datetime.strptime(today, '%Y.%m.%d')
    mp = {}
    for i in terms:
        k = i.split()
        mp[k[0]] = int(k[1])
    cnt = 1
    for i in privacies:
        a, b = i.split()
        here = datetime.strptime(a, '%Y.%m.%d')
        tmp = relativedelta(months=mp[b]) + here
        if t >= tmp:
            answer.append(cnt)
        cnt += 1
    return answer