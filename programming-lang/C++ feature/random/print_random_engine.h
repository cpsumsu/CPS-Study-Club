#ifndef PRINT_RANDOM_ENGINE
#define PRINT_RANDOM_ENGINE

template<typename T>
void print_boundary(T u) {
    cout << u.min() << ' ' << u.max() << endl;
}

template<typename T, typename... Arg>
void print_boundary(T u, Arg... rest) {
    cout << u.min() << ' ' << u.max() << endl;
    return print_boundary(rest...);
}

// **error** if dist(raw()), since raw() generates new value and raw is a value, 
// dist() may call raw serveral times.
template<typename T>
void print_distribution(T dist) {
    default_random_engine raw;
    for (int i = 0; i < 5; i++)
        cout << dist(raw) << ' ';
    cout << endl;
}

template<typename T, typename... Arg>
void print_distribution(T dist, Arg... rest) {
    default_random_engine raw;
    for (int i = 0; i < 5; i++)
        cout << dist(raw) << ' ';
    cout << endl;
    return print_distribution(rest...);
}

// pass by reference
template<typename T, typename U>
void ref_print_distribution(T dist, U &raw) {
    for (int i = 0; i < 5; i++) 
        cout << dist(raw) << ' ';
    cout << endl;
}

template<typename T, typename U, typename... Arg>
void ref_print_distribution(T dist, U &raw, Arg&... rest) {
    for (int i = 0; i < 5; i++) 
        cout << dist(raw) << ' ';
    cout << endl;
    return ref_print_distribution(rest...);
}

#endif