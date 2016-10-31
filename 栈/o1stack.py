# -*- coding:utf-8 -*-
class Stack:
    def __init__(self,size):
        self.size=size
        self.stack=[]
        self.top=-1 
    def isfull(self):       
        return self.top+1==self.size
    def isempty(self):       
        return self.top==-1 
    def printst(self):
        print "栈中所有元素："
        for i in range(self.top,-1,-1):
            print self.stack[i]
        
def push(s1,s2,key):
    if s1.isfull():
        raise Exception("栈溢出")
    if s2.top==-1 or key<=s2.stack[s2.top]:
        s2.stack.append(key)
        s2.top+=1
    s1.stack.append(key)
    s1.top+=1
def pop(s1,s2):
    if s1.isempty():
        raise Exception("栈为空")
    if s1.stack[s1.top]==s2.stack[s2.top]:
        s2.stack.pop()
        s2.top-=1
    s1.top-=1
    return s1.stack.pop()
def mins(s2):
    if s2.isempty():
        print "栈为空"
        return 
    return s2.stack[s2.top]
st=Stack(5)
minst=Stack(5) 
import random
for i in range(5):
    tmp=random.randint(0,10000)
    push(st,minst,tmp)
    print "PUSH元素:%d" %(tmp)
    st.printst()
    print "当前最小元素:%d" %(mins(minst))
print "逐个弹出元素:" 
for i in range(5):  
    print "POP元素:%d" %(pop(st,minst))  
    st.printst()
    if mins(minst):
        print "当前最小元素:%d" %(mins(minst))
    else:
        print "栈为空"