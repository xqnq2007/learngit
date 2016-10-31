#-*- coding:utf-8 -*-
import random
def maopao(lista):
    lena=len(lista)
    for i in range(0,lena-1):
        for j in range(lena-1,i,-1):
            if lista[j]<lista[j-1]:
                lista[j],lista[j-1]=lista[j-1],lista[j]
def qsort(lista,a,b):
    if a>=b:
        return;
    i=a
    j=b
    key=lista[i]
    while(i<j):
        while(i<j and key<=lista[j]):
            j-=1
        lista[i]=lista[j]
        while(i<j and key>=lista[i]):
            i+=1
        lista[j]=lista[i]
    lista[i]=key
    qsort(lista,a,i-1)
    qsort(lista,i+1,b)
for k in range(1,5):
    lista=[]
    listb=[]
    for i in range(2000):
        tmp=random.randint(0,10000)
        lista.append(tmp)
        listb.append(tmp)
    import timeit
    qsorttest='qsort(listb,0,1999)'
    maopaotest='maopao(lista)'
    print '第%d次排序' %(k)
    print timeit.repeat(qsorttest,'from __main__ import qsort,listb',timeit.default_timer,1,1)
    print timeit.repeat(maopaotest,'from __main__ import maopao,lista',timeit.default_timer,1,1)