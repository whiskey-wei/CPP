## case1:不要在没有关联执行线程的std::thread对象上调用join()或者detach()
在调用join或detach()时先检查线程是否joinable

## case2:不要忘记使用关联的执行线程在std::thread对象上调用join或者detach()

1|1|
---|--|
2|2
3|3

- in
- go
  
1 golang
> ying

[liangjie](https://baidu.com)


