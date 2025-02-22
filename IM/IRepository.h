#pragma once

#include "EntityBase.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;

generic <typename T> where T : EntityBase
public interface class IRepository {
public:
	void Add(T entity);
	void Update(T entity);
	void Delete(int id);
	List<T>^ GetAll();
	T GetById(int id);
};
