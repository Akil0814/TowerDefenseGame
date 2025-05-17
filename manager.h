#pragma once

template<typename T>
class Manager
{
public:
	static T* instance()//实现单例模式
	//只会且只能创建一个Manager对象
	//创建后再次调用只会获取接口
	{
		if (!manager)
			manager = new T();//线程不安全
		//在多线程中可能会出现多个线程同时通过判断的可能性

		return manager;
	}

private:
	static T* manager;

protected:
	Manager() = default;
	~Manager() = default;
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
};

template<typename T>
T* Manager<T>::manager = nullptr;
