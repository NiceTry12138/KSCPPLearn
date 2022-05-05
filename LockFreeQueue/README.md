# 无锁队列

## 原子操作

多线程程序中**最小的且不可并行化**的操作  

通常对一个共享资源的操作是原子操作的话，意味着多个线程访问该资源时，有且仅有唯一一个线程在对这个资源进行操作

实现互斥通常需要平台相关的特殊指令，在C++11之前意味着在代码中需要内联汇编代码，所以程序员必须了解平台上同步相关的汇编指令，或者使用POSIX标准的pthread库中的互斥锁(mutex)

```cpp
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

static long long total = 0;
std::mutex m;

void func(int thread_id) {
	for (int i = 0; i < 100000; i++) {
		m.lock();
		std::cout << thread_id << std::endl;
		total += i;
		m.unlock();
	}
}

int main() {
	std::thread thread1(func, 1), thread2(func, 2);
	thread1.join();
	thread2.join();
	std::cout << total << std::endl;
	return 0;
}
```

除了使用锁操作之外，还可以使用**原子数据类型**

```cpp
atomic_llong total {0};
```

| 原子类型名称 | 对应的内置类型名称 |
| --- | --- |
| atomic_bool | bool |
| atomic_char | char |
| atomic_schar | signed char |
| atomic_uchar | unsigned char |
| atomic_int | int |
| atomic_uint | unsigned int |
| atomic_short | short |
| atomic_ushort | unsigned short |
| atomic_long | long |
| atomic_ulong | unsigned long |
| atomic_llong | long long |
| atomic_ullong | unsigned long long |
| atomic_char16_t | char16_t |
| atomic_char32_t | char32_t |
| atomic_wchar_t | wchar_t |

除了使用上述的指定类型定义变量外，还可以使用`atomic`类模板

```cpp

template <class _Ty>
struct atomic : _Choose_atomic_base_t<_Ty>

std::atomic<T> temp;
```

但是原子类型只能从其模板参数类型中进行构造，目标不允许原子类型进行构造拷贝、移动构造、已经`operator =`等

```cpp
atomic<float> af{1.1f}; // OK
atomic<float> af2{af};  // Error
```

但是不通过`atomic<T>`类型的变量来构造其模板参数类型T的变量则是可以的

```cpp
atomic<float> af {1.1f};
float f = af;
float f1 {af};
```

这是由于`atomic`类模板总是定义了从`atomic<T>`到`T`的类型转换函数的缘故。在需要时编译器会隐式地完成原子类型到其对应的类型的转换

对于绝大多数的原子类型而言，都可以执行读(`load`)、写(`store`)、交换(`exchange`)、比较并交换(`compare_exchange_weak / compare_exchange_stronge`)等操作

```cpp
atomic<int> a{1};
int b = a;  // 等价于 int b = a.load();

atomic<int> a;
a = 1;      // 等价于 a.store(1);
```

## 顺序一致性和memory_order

```cpp
atomic<int> a{0};
atomic<int> b{0};

void valueSet(){
    int t = 1;
    a = t;
    b = 2;
}

void observer(){
    std::cout << "(" << a << ", " << b << ")" << std::endl;
}

int main(){
    std::thread t1(valueSet);
    std::thread t2(observer);

    t1.join();
    t2.join();

    std::cout << "final (" << a << ", " << b << ")" << std::endl;
    return 0;
}
```

上述代码中`observer`的输出，可能是(0, 0)、(1, 2)、(1, 0)，但是**有没有可能出现(0, 2)**的情况

一般而言`a = t`语句是在`b = 2`语句之前执行，所以(0, 2)一般不会出现，但是如果编译器或者处理器优化了代码，改变了代码的执行顺序从而导致了(0, 2)的出现，程序员几乎想不到问题的原因

这里仅仅是赋值语句的顺序发生了变换，如果是其他操作的顺序发生的变换可能导致程序的不稳定性

**实际上默认情况下，在C++中的原子类型的变量在线程中总是保持着顺序执行的特性**(非原子类型则没有必要，因为不需要在线程间进行同步)。我们称这种特性为**顺序一致性**，即代码在线程中运行的顺序与程序员看到的代码顺序一致

C++11提供多种内存模型，而顺序一致只是多种模型中的一种，因为顺序一致往往意味着最低效的同步方式

## 无锁队列的实现

