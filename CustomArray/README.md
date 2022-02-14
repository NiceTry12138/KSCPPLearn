# CustomArray

**当前版本未作深拷贝**

## 初始化参数列表

```cpp
CustomArray(std::initializer_list<T> initlist)
```

# CustomList

**当前版本未作深拷贝**

## 自定义迭代器

1、只要定义该容器相关的迭代器     //这里的迭代器是广义的迭代器，指针也属于该范畴。
2、该类型拥有begin() 和 end() 成员方法，返回值为迭代器（或者重载全局的begin() 和 end() 函数也可以） 。
3、迭代器支持 != 比较操作 。
4、迭代器支持++ 前置自增操作，显然该操作要是迭代器对象指向该容器的下一个元素 。
5、迭代器支持* 解引用操作，显然解引用操作必须容器对应元素的引用，否则引用遍历时将会出错。

```cpp
template<typename T>
class CustomListIterator : public BaseIterator<T>
{
public:
	void next() override;
	void behind() override;
	bool isDone() override;

	CustomListIterator(CustomListNode<T>* _node, CustomListNode<T>* _head, bool reverse = false) : m_Node(_node), m_Head(_head), BaseIterator<T>(reverse) {}

	T operator *();
	CustomListIterator<T>& operator ++();
	CustomListIterator<T>& operator --();
	bool operator !=(const CustomListIterator<T>& _other);

	void SetVal(const T& _val) override;

private:
	CustomListNode<T>* m_Node;
	CustomListNode<T>* m_Head;
};


template<typename T>
class CustomList
{
public:
	CustomList();
	virtual ~CustomList();

	void push_back(const T& _val);
	T pop_back();

	size_t Size();

	CustomListIterator<T> begin();
	CustomListIterator<T> end();

	CustomListIterator<T> rbegin();
	CustomListIterator<T> rend();
protected:
	CustomListNode<T>* GetLastNode();

private:
	size_t m_Size{ 0 };
	CustomListNode<T>* m_head{ nullptr };
};
```