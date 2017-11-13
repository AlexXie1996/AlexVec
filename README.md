# AlexVec

- **用C语言实现c++ 泛型vector的基本功能**
- **实现了两个版本的vector**

## alexvec版本

- 使用宏定义解决泛型编程问题
- 用指针作为alexvec的类型
- 当最大存储空间不够时，采取扩大为原来存储空间**两倍**的策略
- 实现以下功能
    + init() 初始化
    + push_back() 入栈
    + pop_back() 出栈
    + size() 取出元素个数
    + maxsize() 取出vec的容量
    + destroy() 销毁
    
### 使用

- 包含头文件 "alexvec.h"
- 泛型使用
    - 先以alexvec为类型进行声明
    - 调用alexvec_init()进行初始化，传入泛型类型

## funnyvec版本

- 使用宏定义解决泛型编程问题
- 用结构体作为alexvec的类型
- 当最大存储空间不够时，采取扩大为原来存储空间**两倍**的策略
- 实现以下功能
      + init() 初始化
      + push_back() 入栈
      + pop_back() 出栈
      + push_front() 在开头插入一个元素
      + pop_front() 出队
      + get_elem() 按索引取出元素
      + size() 取出元素个数
      + maxsize() 取出vec的容量
      + destroy() 销毁
      
 ### 使用
 
 - 包含头文件 "funnyvec.h"
 - 泛型使用 
    - 先以funnyvec为类型进行声明
    - 调用funnyvec_init()进行初始化，传入泛型类型
    
    
## 注意

  - 由于宏定义实现泛型需要检查类型，传入元素的时候必须是相同类型的变量而不能是常量或表达式
  - 类型检查仅检查类型所需内存的字节数，若传入相同字节数的变量被认为是强制转换，可能会出现问题
      
      
      
      
      
      
      
      
