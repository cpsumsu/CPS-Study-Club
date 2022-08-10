#print用法
print(666)
#單雙引號
print('hello world')
print("hello world")
#三引號&轉義字符
print('''hello
 world''')
print('hello\n world')

#數據類型轉換
str('123')
int(89.0)
float(89)
#查看數據類型
type()

#條件判斷
#單向判斷
if a>=6:
    print(123)
#雙向判斷
if a>=6:
    print(123)
else:
    print(321)
#多向判斷
if a>=6:
    print(123)
elif a<=3:
    print(666)
else:
    print(321)
    
#input
number = input('你鍾意既數字')

if number==1:
    print('yes')
else:
    print("no")
#input數據類型(str)
type(number)
#完善coding
number = int(input('你鍾意既數字'))

if number==1:
    print('yes')
else:
    print("no")

#列表list
list =[0,1,2,3,4]
print(list)
#提取單個元素
print(list[0])

#提取多個元素
#提取所有
print(list[:])
#提取第3個後所有
print(list[2:])
#提取第3個之前所有
print(list[:2])
#提取第2個至第4個
print(list[1:3])

#add/delete元素
list.append(5)
#不能一次加兩個list.append(6,7)
list.append([6,7])
del list[6]

#字典(一個key with value)
name = ['tony','tom','ken']
scores = {'tony':95,'tom':90,'ken':90}
print(len(name))
print(len(scores))
print(scores)
print(scores['tom'])
del scores['ken']
scores['ken'] = 100

#list同字典的差異點在於位置
students1 = ['小明','小红','小刚']
students2 = ['小刚','小明','小红']
print(students1 == students2)

scores1 = {'小明':95,'小红':90,'小刚':100}
scores2 = {'小刚':100,'小明':95,'小红':90}
print(scores1 == scores2)

#共通點(可用赋值修改元素)
list1 = ['小明','小红','小刚','小美']
list1[1] = '小蓝'
print(list1)

gender = {'小明':'男'}
gender['小明'] = '女'
print(gender)

#一同使用
group={'group one':['james','ken','tony'],'group two':['kelvin','tom','roy']}
print(group['group one'][3])

#for loop
for i in[1,2,3,4,5]:
    print(i)
#與字典一同使用
capital={'日本':'东京','英国':'伦敦','法国':'巴黎'}
for i in capital:
    print(i)
    print(capital[i])
#for在字串
for i in 'james':
    print(i)
#for in range
for i in range(3):
    print(i)
#output 0,1,2
for i in range(13,17):
    print(i)
#output 13-16
for i in range(0,10,3):
    print(i)
#output從0到9每3跳一下(0,3,6,9)

#while loop
a=0
while a < 5:
    a = a + 1
    print(a)

#數值比較
#等於==
#不等於!=
#大於>
#小於<
#大於等於>=
#小於等於<=

#真假判斷
#假(False,0,'',[],{},None)
#真(True,任意整數,任意float,字符串,[1,2,3],{a:'1',b:'2'})

#測試
print(bool(False))
print(bool(0))
print(bool(''))
print(bool(None))
print(bool(True))
print(bool(1))
print(bool('abc'))

#and運算
if a==1 and b==1:
    print('yes')
#or運算
if a==1 or b==1:
    print('yes')
#not
a=True
print(not a)
#in and not in
list = [1,2,3,4,5]
a = 1
print(bool(a in list))
print(bool(a not in list))

#break語句
for i in range(5):
    print('第'+str(i)+'天')
    if i==3:
        break

#continue語句
i = 0
while i<5:
    print('第'+str(i)+'天')
    i = i+1
    if i==3:  # 当i等于3的时候触发
        continue # 回到循环开头
    print('當i=3就不print')
    
#pass 語句
a = int(input('请输入一个整数:'))
if a > 100:
    pass #(唔用會error)
else:
    print('你输入了一个小于100的数字')

#else語句(for,while)
for i in range(5):
    a = int(input('輸入0結束'))
    if a == 0:
        print('輸入了0')    
        break
else:
    print('5次都無輸入0,所以else生效')
    
#類class&實例Instance(狗&柴犬)
class Computer: #(類)
    screen = True #(屬性)
    def start(self): #(實例創建)
        print('正在開機inggggggg') #(行動)
        
my_computer = Computer()
print(type(my_computer))
print(my_computer)
print(my_computer.screen)
my_computer.start()

#self係咩???
#self會接收實例化過程中傳入的數據，當實例對象創建後，實例便會代替 self，在代碼中運行。
#self
class People:
    
    name = 'James'
    def UM(self):     
        print(self.name + 'on UM')

person = People()
person.UM()
#no self
class People:
    
    name = 'James'
    def UM(People):     
        print(People.name + 'on UM')

person = People()
person.UM()

#定義初始化方法
class Chinese:
    def __init__(self): 
        print('Hello，我係初始化方法')
person = Chinese()

#實例
class num_peo:
    def __init__ (self):
        self.um = 1
        self.people = 2
    
    def person(self):
        print('UM有%s個人' % self.um)
        print('人有%s個' % self.people)

person = num_peo()
person.person()

#作用
class ID:
    def __init__(self, name, birthday, region):
        self.name = name   # self.name = 'James' 
        self.birth = birthday  # self.birth = '0204'
        self.region = region  # self.region = 'MACAU'

    def born(self):
        print(self.name + '生日在' + self.birth)

    def live(self):
        print(self.name + '居住在' + self.region)    

person = ID('James','0204','MACAU') # 传入初始化方法的参数
person.born()
person.live()

#繼承(class A(B),class子類(父類))
class Cat:
    tail = True
    def say(self):
        print('喵喵喵喵喵~')
class Ragdoll(Cat):
    pass
qq=Ragdoll()
print(qq.tail)
qq.say()

#多重繼承(就近原則)
class N:
    born='北部'
    wearing='thick'
    
    def eat(self):
        print("愛咸味")
        
class S:
    now='南部'
    wearing='thin'
    
    def eat(self):
        print("愛甜味")

class ABC(N,S):
    pass

Tom=ABC()
print(Tom.wearing)
print(Tom.born)
Tom.eat