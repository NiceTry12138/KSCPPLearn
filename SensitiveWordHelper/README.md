# 敏感词匹配

```cpp
auto m = new SensitiveWordHelper();
m.load("xxxxFile.txt");
bool ret = m.check("xxx");
```

匹配算法使用**字典树**，进行单个单词的匹配

使用字典树，可以使用公共前缀，节省内存