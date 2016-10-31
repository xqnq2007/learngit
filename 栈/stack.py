# -*- coding:utf-8 -*-
class Stack:
    def __init__(self,size):
        self.size=size
        self.stack=[]
        self.top=-1
    def push(self,ele):
        if self.isfull():
            raise Exception("栈溢出")
        else:
            self.stack.append(ele)
            self.top+=1
    def pop(self):
        if self.isempty():
            raise Exception("栈已经空")
        else:
            return self.stack.pop()
    def isfull(self):       
        return self.top+1==self.size
    def isempty(self):       
        return self.top==-1  
s=Stack(1)



#print s.pop()
#print s.pop()  