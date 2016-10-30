import random
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
listb=[]
for i in range(10000):
    listb.append(random.randint(0,10000))
if __name__=='__main__':
    import timeit
    ftest='qsort(listb,0,9999)'
    print timeit.repeat(ftest,setup='from __main__ import qsort',timeit.default_timer,1,1)