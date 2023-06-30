#include <any>

template<template<typename... Args> typename T> 
struct erased_type {
    private:
        std::any internal;
    public:
        erased_type(): internal() {}
        template<typename... Args>
        erased_type(const T<Args...>& obj): internal(obj) {}
        template<typename... Args>
        erased_type(T<Args...>&& obj): internal(obj) {}
        template<typename... Args>
        erased_type& operator=(const T<Args...>& obj) {
            internal = obj;
            return *this;
        }
        template<typename... Args>
        erased_type& operator=(T<Args...>&& obj) {
            internal = std::move(obj);
            return *this;
        }
        template<typename... Args>
		T<Args...> get() {
			return std::any_cast<T<Args...>>(internal);
		}
		bool has_value() const noexcept {
			return internal.has_value();
		}
};
