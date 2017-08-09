
template<typename T>
void stack<T>::destroy() { PROF

	contents.destroy();
}

template<typename T>
stack<T> stack<T>::make_copy(stack<T> src, allocator* a) { PROF

	stack<T> ret;

	ret.contents = make_vector_copy(src.contents, a);

	return ret;
}

template<typename T>
stack<T> stack<T>::make_copy_trim(stack<T> src, allocator* a) { PROF

	stack<T> ret;

	ret.contents = make_vector_copy_trim(src.contents, a);

	return ret;
}

template<typename T>
stack<T> stack<T>::make(u32 capacity, allocator* a) { PROF

	stack<T> ret;

	ret.contents = vector<T>::make(capacity, a);
	
	return ret;
}

template<typename T> 
stack<T> stack<T>::make_copy(stack<T> src) { PROF
	
	stack<T> ret;

	ret.contents = make_vector_copy(src.contents);

	return ret;
}

template<typename T>
stack<T> stack<T>::make(u32 capacity) { PROF

	stack<T> ret;

	ret.contents = make_vector<T>(capacity);

	return ret;
}

template<typename T>
void stack<T>::clear() { PROF

	contents.clear();
}

template<typename T>
void stack<T>::push(T value) { PROF

	contents.push(value);
}

template<typename T>
T stack<T>::pop() { PROF

	if(contents.size > 0) {
		
		T ret = *top();

		contents.pop();

		return ret;	
	}

	LOG_FATAL("Trying to pop empty stack!");
	T ret = {};
	return ret;
}

template<typename T>
T* stack<T>::top() { PROF

	if(contents.size > 0) {

		return contents.back();
	}

	LOG_FATAL("Trying to get top of empty stack!");
	return null;
}

template<typename T>
bool stack<T>::empty() { PROF
	return vector_empty(&contents);
}

template<typename T>
bool stack<T>::try_pop(T* out) {
	
	if(!empty()) {
		
		*out = *pop();
		return true;	
	}

	return false;
}

template<typename T>
con_stack<T> con_stack<T>::make(u32 capacity, allocator* a) {

	con_stack<T> ret;
	ret.contents = make_vector(capacity, a);
	global_api->platform_create_mutex(&ret.mut, false);
	global_api->platform_create_semaphore(&ret.sem, 0, INT_MAX);

	return ret;
}

template<typename T>
con_stack<T> con_stack<T>::make(u32 capacity) {

	return make_con_stack(capacity, CURRENT_ALLOC());
}

template<typename T>
void con_stack<T>::destroy() {

	destroy_vector(&contents);
	global_api->platform_destroy_mutex(&mut);
	global_api->platform_destroy_semaphore(&sem);
}

template<typename T>
T* con_stack<T>::push(T value) {

	global_api->platform_aquire_mutex(&mut, -1);
	T* ret = ((stack<T>*)this)->push(value);
	global_api->platform_release_mutex(&mut);
	global_api->platform_signal_semaphore(&sem, 1);
	return ret;
}

template<typename T>
T con_stack<T>::wait_pop() {

	global_api->platform_wait_semaphore(&sem, -1);
	T ret;
	try_pop(&ret);
	return ret;
}

template<typename T>
bool con_stack<T>::try_pop(T* out) {

	global_api->platform_aquire_mutex(&mut, -1);
	bool ret = ((stack<T>*)this)->try_pop(out);
	global_api->platform_release_mutex(&mut);
	return ret;
}
