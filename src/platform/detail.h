#pragma once

#include <memory>
#include <mutex>
#include <type_traits>

#if __cplusplus >= 201703L

namespace std {

// deduction guides for std::unique_ptr
template <typename T, typename D>
unique_ptr(T* p, D&& d) -> unique_ptr<T, std::decay_t<D>>;

} // namespace std

namespace ipc {
namespace detail {

using std::unique_ptr;
using std::unique_lock;

#else /*__cplusplus < 201703L*/

namespace ipc {
namespace detail {

// deduction guides for std::unique_ptr
template <typename T, typename D>
constexpr auto unique_ptr(T* p, D&& d) {
    return std::unique_ptr<T, std::decay_t<D>> { p, std::forward<D>(d) };
}

// deduction guides for std::unique_lock
template <typename T>
constexpr auto unique_lock(T&& lc) {
    return std::unique_lock<std::decay_t<T>> { std::forward<T>(lc) };
}

#endif/*__cplusplus < 201703L*/

} // namespace detail
} // namespace ipc
