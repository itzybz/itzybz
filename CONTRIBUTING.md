Here are some things you can do to help contribute!
- [Bug Review & Search](https://github.com/itzybz/itzybz/labels/bug)
- Wiki / Code Documentation
- Example Creation
- Platform Testing
- Optimizations
- [Feature Implementations or Requests](https://github.com/itzybz/itzybz/labels/feature-request)

## Code Style Guide

- Itzy core functions and types should be prefixed with `itzy_` or `iz` in order to avoid any namespace collisions.
- C code should aim to be as close to compliant to core C99 standards *as possible* (NOTE: Not GNU99)
- C code should be memory safe
- Opening Curly braces `{` should be on the same line as their statement
- Single line for/if statements without braces are OK
- Pointers should be indicated with the star on the left (e.g. `char* a` instead of `char *a`)
- Function names for C Code should have underscores between words (e.g. `itzy_cleaned_str`)
- Aim to have the code as simple and easy to use as possible 