#include <unistd.h>

template<typename Traits>
class unique_handle
{
    using pointer = typename Traits::pointer;
    pointer m_value;
public:
    //コピー禁止
    unique_handle(unique_handle const&) = delete;
    unique_handle& operator=(unique_handle const&) = delete;

    explicit unique_handle(pinter value = Traits::invalid()) noexcept 
        : m_value{value} {}

    //ムーブは許可
    unique_handle(unique_handle && other)
        : m_value{other.release()} {}
    unique_handle& operator=(unique_handle && other)
    {
        if (this != other) reset(other.release());
        return *this;
    }

    ~unique_handle() noexcept 
    {
        Traits::close(m_value);
    }

    explicit operator bool() const noexcept 
    {
        return m_value != Traits::invalid();
    }

    pointer get() const noexcept { return m_value; }

    pointer release() noexcept 
    {
        auto value = m_value;
        m_value = Traits::invalid();
        return value;
    }

    bool reset(pointer value = Traits::invalid()) noexcept 
    {
        if (m_value != value)
        {
            Traits::close(m_value);
            m_value = value;
        }
        return static_cast<bool>(*this);
    }

    void swap(unique_handle<Traits>& other) noexcept 
    {
        std::swap(m_value,other.m_value);
    }
};

template<typename Traits>
void swap(unique_handle<Traits>& left,
          unique_handle<Traits>& right) noexcept
{
    left.swap(right);
}

template<typename Traits>
bool operator==(unique_handle<Traits>& left,
          unique_handle<Traits>& right) noexcept
{
    return left.get() == right.get();
}

struct null_handle_traits
{
    using pointer = int;
    static pointer invalid() noexcept { return -1; }
    static void close(pointer value) noexcept 
    {
        close(value);
    }
};

struct invalid_handle_traits
{
    using pointer = int;
    static pointer invalid() noexcept { return -1; }
    static void close(pointer value) noexcept 
    {
        close(value);
    }
};


