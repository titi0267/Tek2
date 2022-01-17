#include <criterion/criterion.h>
Test(my_strlen , positive_return_value)
{
cr_assert_eq(my_strlen("toto"), 4);
}

Test(my_strlen , empty_string)
{
cr_assert_eq(my_strlen(""), 0);
}