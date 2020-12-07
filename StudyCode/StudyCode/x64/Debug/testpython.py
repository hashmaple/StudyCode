#!/usr/bin/python3
 

print ("Hello, Python!")

def PyHello():
    print("call Hello()")
    
def PyAdd(a,b):
    return a+b
    
class MyClass:
    i = 12345
    
    def greet(self, str):
        print(str)
        
    
    def f(self, num):
        i = num
        print(i)
        return i
 
# 实例化类
x = MyClass()
print("MyClass 类的属性 i 为：", x.i)
print("MyClass 类的方法 f 输出为：", x.f(9527))
print("MyClass 类的方法 greet 输出为：", x.greet("Hello Mike  中国人"))
    
# 以下为PYTHON的功能测试
total = ['item_one', 'item_two', 'item_three',
        'item_four', 'item_five']
        
word = '字符串'
sentence = "这是一个句子。"
paragraph = """这是一个段落，
可以由多行组成"""
print (word + " " + sentence + paragraph)

str='Runoob'
print(str)                 # 输出字符串
print(str[0:-1])           # 输出第一个到倒数第二个的所有字符
print(str[0])              # 输出字符串第一个字符
print(str[2:5])            # 输出从第三个开始到第五个的字符
print(str[2:])             # 输出从第三个开始后的所有字符
print(str * 2)             # 输出字符串两次
print(str + '你好')        # 连接字符串
 
print('------------------------------')
 
print('hello\nrunoob')      # 使用反斜杠(\)+n转义特殊字符
print(r'hello\nrunoob')     # 在字符串前面添加一个 r，表示原始字符串，不会发生转义

# 导入 sys 模块
import sys
print('==Python import mode==')
print ('命令行参数为:')
for i in sys.argv:
    print (i)
print ('\n python 路径为',sys.path)

#import os
#os.system("cls")