#ifndef PIPELINE_H
#define PIPELINE_H

#include <type_traits>
#include <utility>
#include <stdexcept>
#include <iterator>

template <typename T>
class Pipeline;

template <typename T>
Pipeline<T> make_pipeline(T&& value);

template <typename T>
class Pipeline {
private:
    T value_;
    mutable bool executed_;

    template <typename U>
    friend class Pipeline;

    template <typename U>
    friend Pipeline<U> make_pipeline(U&& value);

    explicit Pipeline(T&& value): value_(std::forward<T>(value)), executed_(false){}
public:
    Pipeline(Pipeline&& other) noexcept :
        value_(std::move(other.value_)), executed_(other.executed_) {
            other.executed_ = false;        
    }

    Pipeline(const Pipeline& other) : value_(other.value_), executed_(false){}

    Pipeline& operator =  (Pipeline&& other) noexcept {
        if (this != &other){
            value_ = std::move(other.value_);
            executed_ = other.executed_;
            other.executed_ = false;
        }
        return *this;
    }
    Pipeline& operator = (const Pipeline& other){
        if (this != &other){
            value_ = other.value_;
            executed_ = false;
        }
        return *this;
    }

    ~Pipeline(){}

    template <typename Func>
    auto operator | (Func&& func){
        using ResultType = decltype(func(value_));
        if constexpr(std::is_void_v<ResultType>){
           func(value_);
           executed_ = true;
           return Pipeline<T>(std::move(value_));
        }else{
            return Pipeline<ResultType>(func(value_));
        }
    }

    template<typename Func>
    auto operator | (Func && func) const {
        using ResultType = decltype(func(value_));

        if constexpr (std::is_void_v<ResultType>){
            func(value_);
            return Pipeline<T>(value_);
        } else{
            return Pipeline<ResultType>(func(value_));
        }
    }

    T operator()() const {
        if (executed_){
            throw std::runtime_error("Pipeline already executed");
        }
        executed_ = true;
        return value_;
    }



    T operator()(){
        if (executed_){
            throw std::runtime_error("Pipeline already executed");
        }
        executed_ = true;
        return std::move(value_);
    }

    const T& get() const{
        return value_;
    }
    T& get(){
        return value_;
    }
};


template <typename T>
Pipeline<T> make_pipeline(T&& value){
    return Pipeline<T>(std::forward<T>(value));
}

struct SizeFunc{
    template<typename Container>
    constexpr auto operator() (const Container& c) const noexcept(noexcept(std::size(c))) -> decltype(std::size(c)){
        return std::size(c);
    }

};

inline constexpr SizeFunc size;

template<typename T, typename Func>
auto operator | (T&& value, Func&& func){
    return make_pipeline(std::forward<T>(value)) | std::forward<Func>(func);
}

#endif