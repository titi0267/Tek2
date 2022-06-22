#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../src/include/Components.hpp"
#include "../src/include/IncludeComponents.hpp"
#include "../src/include/Factory.hpp"
#include "../src/Utils/Utils.hpp"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test (Test_or, every_case_of_or, .init=redirect_all_stdout)
{
    cr_assert_eq(nts::Gates::Or(nts::Tristate::FALSE, nts::Tristate::FALSE), nts::Tristate::FALSE);
    cr_assert_eq(nts::Gates::Or(nts::Tristate::TRUE, nts::Tristate::FALSE), nts::Tristate::TRUE);
    cr_assert_eq(nts::Gates::Or(nts::Tristate::TRUE, nts::Tristate::UNDEFINED), nts::Tristate::TRUE);
    cr_assert_eq(nts::Gates::Or(nts::Tristate::FALSE, nts::Tristate::UNDEFINED), nts::Tristate::UNDEFINED);
    cr_assert_eq(nts::Gates::Or(nts::Tristate::UNDEFINED, nts::Tristate::UNDEFINED), nts::Tristate::UNDEFINED);
}

Test (Test_and, test_case_of_and, .init=redirect_all_stdout)
{
    cr_assert_eq(nts::Gates::And(nts::Tristate::FALSE, nts::Tristate::FALSE), nts::Tristate::FALSE);
    cr_assert_eq(nts::Gates::And(nts::Tristate::TRUE, nts::Tristate::TRUE), nts::Tristate::TRUE);
    cr_assert_eq(nts::Gates::And(nts::Tristate::FALSE, nts::Tristate::TRUE), nts::Tristate::FALSE);
    cr_assert_eq(nts::Gates::And(nts::Tristate::UNDEFINED, nts::Tristate::TRUE), nts::Tristate::UNDEFINED);
    cr_assert_eq(nts::Gates::And(nts::Tristate::UNDEFINED, nts::Tristate::FALSE), nts::Tristate::FALSE);
}

Test (Test_not, every_case_of_not, .init=redirect_all_stdout)
{
    cr_assert_eq(nts::Gates::Not(nts::Tristate::FALSE), nts::Tristate::TRUE);
    cr_assert_eq(nts::Gates::Not(nts::Tristate::TRUE), nts::Tristate::FALSE);
    cr_assert_eq(nts::Gates::Not(nts::Tristate::UNDEFINED), nts::Tristate::UNDEFINED);
}

Test (Test_xor, every_case_of_xor, .init=redirect_all_stdout)
{
    cr_assert_eq(nts::Gates::Xor(nts::Tristate::FALSE, nts::Tristate::FALSE), nts::Tristate::FALSE);
    cr_assert_eq(nts::Gates::Xor(nts::Tristate::TRUE, nts::Tristate::TRUE), nts::Tristate::FALSE);
    cr_assert_eq(nts::Gates::Xor(nts::Tristate::FALSE, nts::Tristate::TRUE), nts::Tristate::TRUE);
    cr_assert_eq(nts::Gates::Xor(nts::Tristate::UNDEFINED, nts::Tristate::TRUE), nts::Tristate::UNDEFINED);
    cr_assert_eq(nts::Gates::Xor(nts::Tristate::UNDEFINED, nts::Tristate::FALSE), nts::Tristate::UNDEFINED);
}

Test (Test_input, test_input_value, .init=redirect_all_stdout)
{
    nts::Factory facto;

    facto.addComp("test", "input");
    facto.setInputValue("test=0");
    cr_assert_eq(facto.getComp().find("test")->second->getState()[0], nts::FALSE);
    facto.getComp().find("test")->second->simulate(0);
    facto.getComp().find("test")->second->dump();
}

Test (Test_output, test_outputLink, .init=redirect_all_stdout)
{
    nts::Factory facto;

    facto.addComp("out", "output");
    facto.addComp("int", "input");
    facto.getComp().find("out")->second->setLink(1, *facto.getComp().find("int")->second.get(), 1);
    facto.setInputValue("int=1");
    facto.getComp().find("out")->second->compute(1);
    cr_assert_eq(facto.getComp().find("out")->second->getState()[0], nts::TRUE);
    facto.getComp().find("out")->second->simulate(0);
    facto.getComp().find("out")->second->dump();
}

Test (Test_true, test_basic_true, .init=redirect_all_stdout)
{
    nts::Factory facto;

    facto.addComp("tru", "true");
    facto.addComp("out", "output");
    facto.getComp().find("out")->second->setLink(1, *facto.getComp().find("tru")->second.get(), 1);
    cr_assert_eq(facto.getComp().find("tru")->second->getState()[0], nts::TRUE);
    cr_assert_eq(facto.getComp().find("out")->second->getState()[0], nts::TRUE);
    facto.setInputValue("tru=0");
    cr_assert_eq(facto.getComp().find("tru")->second->getState()[0], nts::TRUE);
    cr_assert_eq(facto.getComp().find("out")->second->getState()[0], nts::TRUE);
    facto.setInputValue("tru=U");
    cr_assert_eq(facto.getComp().find("tru")->second->compute(1), nts::TRUE);
    cr_assert_eq(facto.getComp().find("out")->second->getState()[0], nts::TRUE);
    facto.getComp().find("tru")->second->simulate(0);
    facto.getComp().find("tru")->second->dump();
}

Test (Test_false, test_basic_false, .init=redirect_all_stdout)
{
    nts::Factory facto;

    facto.addComp("test", "false");
    facto.addComp("out", "output");
    facto.getComp().find("out")->second->setLink(1, *facto.getComp().find("test")->second.get(), 1);
    cr_assert_eq(facto.getComp().find("test")->second->getState()[0], nts::FALSE);
    cr_assert_eq(facto.getComp().find("out")->second->getState()[0], nts::FALSE);
    facto.setInputValue("test=1");
    cr_assert_eq(facto.getComp().find("test")->second->getState()[0], nts::FALSE);
    cr_assert_eq(facto.getComp().find("out")->second->getState()[0], nts::FALSE);
    facto.setInputValue("test=U");
    cr_assert_eq(facto.getComp().find("test")->second->compute(1), nts::FALSE);
    cr_assert_eq(facto.getComp().find("out")->second->getState()[0], nts::FALSE);
    facto.getComp().find("test")->second->simulate(0);
    facto.getComp().find("test")->second->dump();
}

Test (Test_clock, test_basic_clock, .init=redirect_all_stdout)
{
    nts::Factory facto;

    facto.addComp("test", "clock");
    facto.addComp("out", "output");
    facto.getComp().find("out")->second->setLink(1, *facto.getComp().find("test")->second.get(), 1);
    facto.setInputValue("test=1");
    facto.getComp().find("out")->second->compute(1);
    cr_assert_eq(facto.getComp().find("test")->second->getState()[0], nts::TRUE);
    cr_assert_eq(facto.getComp().find("out")->second->getState()[0], nts::TRUE);
    facto.getComp().find("out")->second->compute(1);
    cr_assert_eq(facto.getComp().find("test")->second->getState()[0], nts::FALSE);
    cr_assert_eq(facto.getComp().find("out")->second->getState()[0], nts::FALSE);
    facto.getComp().find("test")->second->simulate(1);
    facto.getComp().find("test")->second->dump();
}

Test (Test_utils, test_utils, .init=redirect_all_stdout)
{
    nts::Utils tools;

    std::vector<ChipsetPair> chipsets;
    std::vector<std::string> str = tools.split("miam miam", ' ');

    chipsets.push_back(std::make_tuple("comp", "test"));
    cr_assert_eq("miam", str[0]);
    cr_assert_eq(tools.isValidComponent("4069"), true);
    cr_assert_eq(tools.isInChipsets(chipsets, "test"), true);
}

Test (Test_Comp4001, test_comp4001, .init=redirect_all_stdout)
{
    nts::Factory facto;

    facto.addComp("in_01", "input");
    facto.addComp("in_02", "input");
    facto.addComp("in_05", "input");
    facto.addComp("in_06", "input");
    facto.addComp("out_03", "output");
    facto.addComp("out_04", "output");
    facto.addComp("comp", "4001");
    facto.getComp().find("out_03")->second->setLink(1, *facto.getComp().find("comp")->second.get(), 3);
    facto.getComp().find("comp")->second->setLink(1, *facto.getComp().find("in_01")->second.get(), 1);
    facto.getComp().find("comp")->second->setLink(2, *facto.getComp().find("in_02")->second.get(), 1);
    facto.getComp().find("out_04")->second->setLink(1, *facto.getComp().find("comp")->second.get(), 4);
    facto.getComp().find("comp")->second->setLink(5, *facto.getComp().find("in_05")->second.get(), 1);
    facto.getComp().find("comp")->second->setLink(6, *facto.getComp().find("in_06")->second.get(), 1);
    facto.getComp().find("comp")->second->simulate(1);
    facto.getComp().find("comp")->second->dump();
}