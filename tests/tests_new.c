/*
** EPITECH PROJECT, 2022
** rush2 [WSL: Ubuntu]
** File description:
** tests_new
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include "new.h"
#include "player.h"
#include "array.h"
#include "point.h"
#include "vertex.h"
#include "char.h"
#include "float.h"
#include "iterator.h"
#include "container.h"
#include "int.h"


Test (Task01, test_new_and_delete, .init = cr_redirect_stdout)
{
    Object *player = new(Player);
    cr_assert(player != NULL);
    delete(player);
}

Test (Testing_outputs, test_all_obj_outputs)
{
    Object *point = new(Point, 24, 32);
    Object *sec_point = new(Point, -25, 32);
    Object *vertex = new(Vertex, 34, 22, 10);
    Object *chars = new(Char, 'c');
    Object *floats = new(Float, 2.34);

    cr_assert_str_eq(str(point), "<Point (24, 32)>");
    cr_assert_str_eq(str(sec_point), "<Point (-25, 32)>");
    cr_assert_str_eq(str(vertex), "<Vertex (34, 22, 10)>");
    cr_assert_str_eq(str(chars), "<Char (c)>");
    cr_assert_str_eq(str(floats), "<Float (2.340000)>");
}

Test (Testing_outputs, test_complex_output)
{
    Object *array = new(Array, 5, Int, 0.0f);
    Object  *it = begin(array);
    Object *it_test = begin(array);
    Object  *it_end = end(array);
    char *test_str = malloc(100);
    strcpy(test_str, "");

    setitem(array, 0, 10);
    setitem(array, 1, 20);
    setitem(array, 2, 30);
    setitem(array, 3, 40);
    setitem(array, 4, 50);
    cr_assert(len(array) == 5);

    while (lt(it, it_end))
    {
        strcat(test_str, str(getval(it)));
        strcat(test_str, ",");
        incr(it);
    }
    cr_assert_str_eq("<Int (10)>,<Int (20)>,<Int (30)>,<Int (40)>,<Int (50)>,", test_str);
    cr_assert(gt(it_test, it) == 0);
    cr_assert(lt(it_test, it));
    cr_assert(eq(it_test, it) == 0);
    delete(it);
    delete(it_end);
    delete(array);
    free(test_str);
}

Test (Testing_outputs, testing_int)
{
    Object  *p1 = new(Int, 1);
    Object  *p2 = new(Int, 3);

    char *add = str(addition(p1, p2));
    char *sub = str(subtraction(p1, p2));
    char *mult = str(multiplication(p1, p2));
    char *div = str(division(p1, p2));
    int eq_ts = eq(p1, p2);
    int gt_ts = gt(p1, p2);
    int lt_ts = lt(p1, p2);
    cr_assert_str_eq(add, "<Int (4)>");
    cr_assert_str_eq(sub, "<Int (-2)>");
    cr_assert_str_eq(mult, "<Int (3)>");
    cr_assert_str_eq(div, "<Int (0)>");
    cr_assert(eq_ts == 0);
    cr_assert(gt_ts == 0);
    cr_assert(lt_ts == 1);
    delete(p1);
    delete(p2);
}

Test (Testing_outputs, testing_char)
{
    Object  *p1 = new(Char, '7');
    Object  *p2 = new(Char, '3');
    Object  *p3 = new(Char, '3');

    char *add = str(addition(p1, p2));
    char *sub = str(subtraction(p1, p2));
    char *mult = str(multiplication(p1, p2));
    char *div = str(division(p1, p2));
    int eq_ts = eq(p1, p2);
    int eq_sec_ts = eq(p2, p3);
    int gt_ts = gt(p1, p2);
    int lt_ts = lt(p1, p2);
    cr_assert_str_eq(add, "<Char (j)>");
    cr_assert_str_eq(sub, "<Char (\004)>");
    cr_assert(eq_ts == 0);
    cr_assert(eq_sec_ts == 1);
    cr_assert(gt_ts == 1);
    cr_assert(lt_ts == 0);
    delete(p1);
    delete(p2);
    delete(p3);
}

Test (Testing_outputs, testing_floats)
{
    Object  *p1 = new(Float, 10.0);
    Object  *p2 = new(Float, 0.5);
    Object  *p3 = new(Float, 0.5);

    char *add = str(addition(p1, p2));
    char *sub = str(subtraction(p1, p2));
    char *mult = str(multiplication(p1, p2));
    char *div = str(division(p1, p2));
    int eq_ts = eq(p1, p2);
    int eq_sec_ts = eq(p2, p3);
    int gt_ts = gt(p1, p2);
    int lt_ts = lt(p1, p2);
    cr_assert_str_eq(add, "<Float (10.500000)>");
    cr_assert_str_eq(sub, "<Float (9.500000)>");
    cr_assert_str_eq(mult, "<Float (5.000000)>");
    cr_assert_str_eq(div, "<Float (20.000000)>");
    cr_assert(eq_ts == 0);
    cr_assert(eq_sec_ts == 1);
    cr_assert(gt_ts == 1);
    cr_assert(lt_ts == 0);
    delete(p1);
    delete(p2);
    delete(p3);
}

Test (Testing_outputs, testing_points_pt)
{
    Object  *p1 = new(Point, 4, 4);
    Object  *p2 = new(Point, 3, 2);
    Object  *p3 = new(Point, 3, 2);

    char *add = str(addition(p1, p2));
    char *sub = str(subtraction(p1, p2));

    cr_assert_str_eq(add, "<Point (7, 6)>");
    cr_assert_str_eq(sub, "<Point (1, 2)>");
    delete(p1);
    delete(p2);
    delete(p3);
}

Test (Testing_outputs, testing_vertex_pt)
{
    Object  *p1 = new(Vertex, 4, 4, 3);
    Object  *p2 = new(Vertex, 5, 5, 8);

    char *add = str(addition(p1, p2));
    char *sub = str(subtraction(p1, p2));

    cr_assert_str_eq(add, "<Vertex (9, 9, 11)>");
    cr_assert_str_eq(sub, "<Vertex (-1, -1, -5)>");
    delete(p1);
    delete(p2);
}
