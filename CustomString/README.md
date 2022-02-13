<!--
 * @Author: your name
 * @Date: 2022-02-13 22:01:55
 * @LastEditTime: 2022-02-13 22:09:07
 * @LastEditors: Please set LastEditors
 * @FilePath: \undefinede:\KSCPPLearn\CustomString\README.md
-->
# CustomString

自定义String类型

```cpp
#pragma once
#include "vector"
#include <iostream>

class CustomString
{
public:
	CustomString(const char* _str = nullptr);	// 默认构造
	CustomString(const CustomString& _other);	// 拷贝构造
	CustomString& operator =(const CustomString& _other);

	inline bool operator == (const CustomString& _other);   
	
	friend std::ostream& operator<<(std::ostream& os, const CustomString& str) // 友元
	{
		os << str.m_data ;
		return os;
	}

	~CustomString();

	void append(const char* _other);
	void append(const CustomString& _other);
	
	int len();

	CustomString sub(int startIndex = 0, int endIndex = -1);

	std::vector<CustomString> split(const char* _key);

	int find(const char* _target);
protected:
	void setValueByOtherCustomString(const char* _other);
	
private:
	char* m_data{nullptr};						// 数据实际存放位置
};
```

| 函数名      | 功能                             |
| ----------- | -------------------------------- |
| append      | 将指定字符添加到字符末尾         |
| len         | 字符串长度                       |
| sub         | 从startIndex到endIndex切割字符串 |
| find        | 找到指定字符串的位置             |
| operator << | 重载输出操作符                   |
| operator == | 重载==操作符                     |
| opeartor =  | 赋值操作                         |
| split       | 切割字符串                       |