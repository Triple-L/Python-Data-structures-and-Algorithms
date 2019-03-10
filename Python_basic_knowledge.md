# Python-Machine-Learning
2019/Machine Learning and python notes
## Part1.Basic Python knowledge

id(x)查看内存地址，指针形式的
起名规则：

      第一个为字母或者_，大小写敏感，空格和-无效
      
风格：全局变量纯大写   
用名词描述 task_detail taskDetail驼峰状推荐   
数据类型：数字类型 序列类型 映像类型   
类型查看type(a)  

(1) 数字类型    
bool：True/False  
整型:长整型 标准整型 （不用管 自动转换）  
非整型:float
       
（2）序列类型
字符串 strName.strip.split()
*  S.find(substring,[start[,end]])查找子字符串 返回索引 or -1
* S.rfind(substring,[start[,end]])#反向查找
* S.index(substring,[start[,end]])找不到就出错
* S.lowercase()
* S.capitalize()
* S.lower()
* S.upper()
* S.swapcase()
* 
* S.split()
* S.join(list,’ ‘)list转string，以空格链接
* 处理字符串的内置函数
* len(str)
* cmp(‘my friend’,str)
* max(‘abcdef')
* min(‘dsfrffre')

（3） List列表(数组) name_list=[‘alex’,’shelly’,’Amy’] 
特征：有序 可更改  
Initialization   a=[ ]  
len(list) list[0],list[1]  
增加元素 list.append()  
指定位置插入 list.insert(2,’hello’)  
删除元素 list.pop()默认最后一个 list.pop(1)  
list_name.pop(index)  

（4）Tuple元组
特征: 不可更改的数组，初始化时赋值.

（5）字典 
特征：无序，可改  
key-value name={‘alex’:[28,’IT’]} name[‘Alex’]  
dit['key’]
确认是否在字典里  
2 in dict / dict.get(name)  
赋值 dict[5]=’sam’  
获取所有key /value   
dict.key /dict.value()  
Dict.items()  

（6）Set 没有value的dict 去重和集合求并求交

（7）narray⚠️ 科学计算常用  
listde升级版本 科学技术 list遍历只能loop  
Narray要求元素要一样  
Initial a = np.array([1,2,3])  
array.indexOf(searchElement[, fromIndex = 0])  
array.lastIndexOf(searchElement[, fromIndex = array.length - 1])  

数据运算 从左往右  
+-*/%  
&与|或<<左移>>右移^异或~取反  
文件的file 操作  
f.readlines所有都读list形式   
readline读一行   
f.read字符串形式读  
f.tell 我在哪？  
f.seekl(0)回到开头  



```
[例子]读取文件基本操作
f=file(‘myFile.txt’,’r’)#a追加模式
for line in f.readlines(): #
     line=line.strip(‘\n’),split(‘.’) #strip 去掉\n 按照.分割
     Print line #获得一个list
f.close()```

写的时候 f.flush()刷新缓存进入文本
加解释#！/usr/bin/env python
