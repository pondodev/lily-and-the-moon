#ifndef HELPERS_H
#define HELPERS_H

// create scope encapsulated by two functions to be called at the start and end
// defer(start_function(), end_function())
// {
//   // do things
// }
#define macro_var(name) name##__LINE__
#define defer(start, end) for (          \
        int macro_var(_i_) = (start, 0); \
        ! macro_var(_i_);                \
        (macro_var(_i_) += 1), end)

#endif

