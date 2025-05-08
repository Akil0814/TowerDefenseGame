#pragma once

template<typename T>
class Manager
{
public:
	static T* instance()//实现单例模式//只会且只能创建一个Manager对象
	{
		if (!manager)
			manager = new T();

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
