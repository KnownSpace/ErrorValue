#pragma once
#ifndef _ERRORVALUE_RESULT_HPP
#define _ERRORVALUE_RESULT_HPP

#include <utility>

#ifndef _NDEBUG
// include type_trait for debug
#include <type_traits>
#endif

namespace ErrorValue {

    template<typename _T, typename _E>
    class Result {
    private:
        using Self = ErrorValue::Result<_T, _E>;

#ifndef _NDEBUG
        static_assert(std::is_default_constructible<_T>::value, "Type Result<_T,_E>::_T should be default constructible");
        static_assert(std::is_move_constructible<_T>::value,"Type Result<_T,_E>::_T should be move constructible");
        static_assert(std::is_move_assignable<_T>::value, "Type Result<_T,_E>::_T should be move assignable");
        static_assert(std::is_default_constructible<_E>::value, "Type Result<_T,_E>::_E should be default constructible");
        static_assert(std::is_move_constructible<_E>::value,"Type Result<_T,_E>::_E should be move constructible");
        static_assert(std::is_move_assignable<_E>::value, "Type Result<_T,_E>::_E should be move assignable");
#endif
    public:
        // NOTE: in generally, these members should not be used directly.
        _T value_;
        _E err_;

    public:
        Result(_T value) noexcept
            : value_(std::move(value))
            , err_() {
        }

        Result(_E err) noexcept
            : value_()
            , err_(std::move(err)) {
        }

        Result(const Self &other) = delete;

        Result(Self &&other) noexcept = default;

        Self &operator=(const Self &other) = delete;

        inline Self &operator=(Self &&other) noexcept {
            if (this != &other) {
                this->value_ = std::move(other.value_);
                this->err_ = std::move(other.err_);
            }
            return *this;
        }

        ~Result() noexcept = default;
    };
}   // namespace ErrorValue

#endif