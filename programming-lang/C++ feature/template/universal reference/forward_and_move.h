#define FORWARD
#define MOVE

template<typename T>
typename remove_reference<T>::type &&po_move(T &&t) 
{
    return static_cast<typename remove_reference<T>::type &&>(t);
}

// The vital point is forced the user to explicitly provide template parameter, otherwise the 
// reference collipase will always produces lvalue reference (see g(), U type will be 
// lvalue reference) after second pass

// first implementation of forward<>
template<typename T>
T &&po_forward(typename remove_reference<T>::type &t) noexcept
{
    return static_cast<T &&>(t);
}

template<typename T>
T &&po_forward(typename remove_reference<T>::type &&t) noexcept
{
    return static_cast<T &&>(t);
}

// second impolementation of forward<>
template<typename T>
struct identity 
{
    typedef T type;
};

template<typename T>
T &&po_forward_v2(typename identity<T>::type &t) noexcept
{
    return static_cast<typename identity<T>::type &&>(t);
}

template<typename T>
T &&po_forward_v2(typename identity<T>::type &&t) noexcept
{
    return static_cast<typename identity<T>::type &&>(t);
}
