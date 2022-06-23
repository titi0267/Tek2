/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD09-timothe.coniel
** File description:
** test_day9
*/

#include <criterion/criterion.h>
#include "../Paladin.hpp"
#include <criterion/redirect.h>

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stdout();
}

Test(Peasant, Peasant_main_test, .init=redirect_all_stdout)
{
    int ret_att0, ret_att1;
    {
        Peasant peasant("Gildas", 42);
        cr_assert_str_eq(peasant.getName().c_str(), "Gildas");
        cr_assert_eq(peasant.getHp(), 100);
        ret_att1 = peasant.special();
        ret_att0 = peasant.attack();
        cr_assert_eq(peasant.getPower(), 32);
        peasant.damage(50);
        peasant.damage(100);
        peasant.damage(200);
        peasant.rest();
    }
    cr_assert_eq(ret_att0, 5);
    cr_assert_eq(ret_att1, 0);
    cr_assert_stdout_eq_str("Gildas goes for an adventure.\nGildas doesn't know any special move.\nGildas tosses a stone.\nGildas takes 50 damage.\nGildas is out of combat.\nGildas is out of combat.\nGildas is out of combat.\nGildas is back to his crops.\n");
}

Test(Peasant, Peasant_other_tests, .init=redirect_all_stdout)
{
    {
    Peasant peasant("Gildas", 150);
    cr_assert_eq(peasant.getPower(), 100);
    Peasant peasant2("Jojo", 0);
    peasant2.attack();
    peasant2.damage(80);
    peasant2.damage(20);
    peasant2.attack();
    //peasant2.special();
    cr_assert_eq(peasant2.special(), 0);
    peasant.rest();
    cr_assert_eq(peasant.getPower(), 100);
    peasant.attack();
    peasant.attack();
    peasant.attack();
    peasant.attack();
    peasant.rest();
    cr_assert_eq(peasant.getPower(), 90);
    }
    cr_assert_stdout_eq_str("Gildas goes for an adventure.\nJojo goes for an adventure.\nJojo is out of power.\nJojo takes 80 damage.\nJojo is out of combat.\nJojo is out of combat.\nJojo is out of combat.\nGildas takes a nap.\nGildas tosses a stone.\nGildas tosses a stone.\nGildas tosses a stone.\nGildas tosses a stone.\nGildas takes a nap.\nJojo is back to his crops.\nGildas is back to his crops.\n");
}



Test(Priest, Test_Priest_main, .init=redirect_all_stdout)
{
    {
    Priest priest("Trichelieu", 20) ;
    priest.attack();
    priest.special();
    priest.rest();
    priest.damage(100);
    priest.rest();
    }
    cr_assert_stdout_eq_str("Trichelieu goes for an adventure.\nTrichelieu learns magic from his spellbook.\nTrichelieu enters in the order.\nTrichelieu doesn't know how to fight.\nTrichelieu is out of power.\nTrichelieu prays.\nTrichelieu is out of combat.\nTrichelieu is out of combat.\nTrichelieu finds peace.\nTrichelieu closes his spellbook.\nTrichelieu is back to his crops.\n");
}

Test(Enchanter, Test_Enchanter_main, .init=redirect_all_stdout)
{
    {
    Enchanter enchanter("Merlin", 20);
    enchanter.attack();
    enchanter.special();
    enchanter.rest();
    enchanter.special();
    enchanter.damage(50);
    Enchanter enchanter2("Lucas", 20);
    enchanter2.damage(100);
    enchanter2.attack();
    enchanter2.special();
    enchanter2.rest();
    }
cr_assert_stdout_eq_str("Merlin goes for an adventure.\nMerlin learns magic from his spellbook.\nMerlin doesn't know how to fight.\nMerlin is out of power.\nMerlin meditates.\nMerlin casts a fireball.\nMerlin takes 50 damage.\nLucas goes for an adventure.\nLucas learns magic from his spellbook.\nLucas is out of combat.\nLucas is out of combat.\nLucas is out of combat.\nLucas is out of combat.\nLucas closes his spellbook.\nLucas is back to his crops.\nMerlin closes his spellbook.\nMerlin is back to his crops.\n");
}

Test(Paladin, Paladin_main_test, .init=redirect_all_stdout)
{
    {
    Paladin paladin("Uther", 99);
    paladin.attack();
    paladin.special();
    paladin.rest();
    paladin.damage(50);
    }

cr_assert_stdout_eq_str("Uther goes for an adventure.\nUther vows to protect the kingdom.\nUther learns magic from his spellbook.\nUther enters in the order.\nUther fights for the light.\nUther strikes with his sword.\nUther casts a fireball.\nUther prays.\nUther takes 50 damage.\nUther is blessed.\nUther finds peace.\nUther closes his spellbook.\nUther takes off his armor.\nUther is back to his crops.\n");
}

Test(Knight, Knight_main_test, .init=redirect_all_stdout)
{
    {
    Knight knight("Arthur", 20);
    knight.attack();
    knight.special();
    knight.attack();
    knight.attack();
    knight.rest();
    knight.special();
    knight.rest();
    knight.rest();
    knight.damage(100);
    knight.attack();
    knight.special();
    knight.rest();
    }
    cr_assert_stdout_eq_str("Arthur goes for an adventure.\nArthur vows to protect the kingdom.\nArthur strikes with his sword.\nArthur is out of power.\nArthur strikes with his sword.\nArthur is out of power.\nArthur eats.\nArthur impales his enemy.\nArthur eats.\nArthur eats.\nArthur is out of combat.\nArthur is out of combat.\nArthur is out of combat.\nArthur is out of combat.\nArthur takes off his armor.\nArthur is back to his crops.\n");
}