#pragma once

using namespace System;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;

ref class SqlRepoHandler abstract sealed {
public:
	//template <typename Func>
	static void ExecuteAsyncHelper(Action^ method) {
		Task::Run(method);
	}

	template <typename Func, typename ResultType>
	static Task<ResultType>^ ExecuteAsyncFuncHelper(Func^ method) {
		return System::Threading::Tasks::Task<ResultType>::Run(gcnew Func<ResultType>([=]() {
			try {
				return method();
			}
			catch (Exception^ ex) {
				// Log the exception or handle it as needed.
                throw gcnew Exception("Error during async operation: " + ex->Message);
			}
			}));
	}
};

generic <typename T>
where T : EntityBase, gcnew()
ref class SqlOperation {
private:
    List<T>^ resultList;
    Func<List<T>^>^ listOperation; 
    Action<T>^ _operation; 
    T _entity;

public:
    SqlOperation(T entity, Action<T>^ operation)
        : _entity(entity), _operation(operation){}

    SqlOperation(Func<List<T>^>^ operation)
        :  listOperation(operation) {}

    void Execute() {
        if (_operation != nullptr) {
            _operation(_entity); 
        }
        else if (listOperation != nullptr) {
            resultList = listOperation(); 
        }
    }

    List<T>^ GetResult() {
        return resultList;
    }
};
