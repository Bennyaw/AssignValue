#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>
#include <ctype.h>
#include "unity.h"
#include "Error.h"
#include "TestParser.h"
#include "Exception.h"
#include "CExceptionConfig.h"
#include "CException.h"

void setUp(void) {}

void tearDown(void) {}

void test_strcompare(void)
{
  char *str = "assign";
  char *originalStr = str;

  TEST_ASSERT_TRUE(parseAndCompare(&str,"assign"));
  TEST_ASSERT_EQUAL_PTR(originalStr+6,str);
}

void test_strcompare_with_cap_letter(void)
{
  char *str = "AssIgn";
  char *originalStr = str;

  TEST_ASSERT_TRUE(parseAndCompare(&str,"assign"));
  TEST_ASSERT_EQUAL_PTR(originalStr+6,str);
}

void test_strcompare_with_wrong_letter(void)
{
  char *str = "AssI";
  char *originalStr = str;

  TEST_ASSERT_FALSE(parseAndCompare(&str,"assign"));
  TEST_ASSERT_EQUAL_PTR(originalStr,str);
}

void test_strcompare_with_space_behind_str(void)
{
  char *str = "assign ";
  char *originalStr = str;

  TEST_ASSERT_TRUE(parseAndCompare(&str,"assign"));
  TEST_ASSERT_EQUAL_PTR(originalStr+7,str);
}

void test_strcompare_with_3_space_behind_str(void)
{
  char *str = "assign   ";
  char *originalStr = str;

  TEST_ASSERT_TRUE(parseAndCompare(&str,"assign "));
  TEST_ASSERT_EQUAL_PTR(originalStr+9,str);
}

void test_strcompare_with_1_space_infront_str(void)
{
  char *str = " assign";
  char *originalStr = str;

  TEST_ASSERT_TRUE(parseAndCompare(&str,"assign"));
  TEST_ASSERT_EQUAL_PTR(originalStr+7,str);
}

void test_strcompare_with_3_space_infront_str(void)
{
  char *str = "   assign";
  char *originalStr = str;

  TEST_ASSERT_TRUE(parseAndCompare(&str,"assign"));
  TEST_ASSERT_EQUAL_PTR(originalStr+9,str);
}
void test_strcompare_with_1_space_inside_str(void)
{
  char *str = "ass ign";
  char *originalStr = str;

  TEST_ASSERT_TRUE(parseAndCompare(&str,"assign"));
  TEST_ASSERT_EQUAL_PTR(originalStr+7,str);
}

void test_parseAndConvertToNum_given_string_55_to_integer(void)
{
  char *str = "55";
  char *originalStr = str;

  TEST_ASSERT_EQUAL(55,parseAndConvertToNum(&str));
  TEST_ASSERT_EQUAL_PTR(originalStr+2,str);
}

void test_parseAndConvertToNum_given_string_with_character_return_0(void)
{
  char *str = "1a3";
  char *originalStr = str;

  TEST_ASSERT_EQUAL(1,parseAndConvertToNum(&str));//take the digit before character
  TEST_ASSERT_EQUAL_PTR(originalStr+1,str);
}

void test_parseAndConvertToNum_given_string_with_space_infront_return_interger(void)
{
  char *str = " 6013";
  char *originalStr = str;

  TEST_ASSERT_EQUAL(6013,parseAndConvertToNum(&str));
  TEST_ASSERT_EQUAL_PTR(originalStr+5,str);
}

void test_parseAndConvertToNum_given_string_with_space_inside_return_interger(void)
{
  char *str = "12 134";
  char *originalStr = str;

  TEST_ASSERT_EQUAL(12134,parseAndConvertToNum(&str));
  TEST_ASSERT_EQUAL_PTR(originalStr+6,str);
}

void test_parseAndConvertToNum_given_string_with_space_behind_return_interger(void)
{
  char *str = "7890  ";
  char *originalStr = str;

  TEST_ASSERT_EQUAL(7890,parseAndConvertToNum(&str));
  TEST_ASSERT_EQUAL_PTR(originalStr+6,str);
}

void test_parseTextAndAssignValues_given_no_table_mapping_should_throw_ERR_TABLE_IS_MISSING(void) {
  CEXCEPTION_T e;
  char *line = " assign mango = 589 ";

  Try {
    parseTextAndAssignValues(&line,NULL);
    TEST_FAIL_MESSAGE("Expect ERR_TABLE_IS_MISSING. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_no_command_should_do_nothing(void) {
  CEXCEPTION_T e;
  int tomato = 0;
  VariableMapping varTableMapping[] = {
    {"tomato", &tomato},
    {NULL, NULL},
  };
  char *line = NULL;

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    // Should reach here because no command given
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_input_command_is_NULL_should_do_nothing(void) {
  CEXCEPTION_T e;
  int kiwi = 0;
  VariableMapping varTableMapping[] = {
    {"kiwi", &kiwi},
    {NULL, NULL},
  };
  char *line = "  ";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    // Should reach here because no command given
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}
/*
// assign orange  = 21346 apple = 1 lemon=10
void test_parseTextAndAssignValues_given_orange_21346_apple_1_lemon_10_should_assigned_correctly(void) {
  CEXCEPTION_T e;
  int orange = 0, apple = 0, lemon = 0;
  VariableMapping varTableMapping[] = {
    {"apple", &apple},
    {"orange", &orange},
    {"lemon", &lemon},
    {NULL, NULL},
  };
  char *line = "assign orange  = 21346 apple = 1 lemon=10";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);

    TEST_ASSERT_EQUAL(21346, orange);
    TEST_ASSERT_EQUAL(1, apple);
    TEST_ASSERT_EQUAL(10, lemon);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_melon_and_value_with_trailing_spaces_should_parse_properly(void) {
  CEXCEPTION_T e;
  int melon = 0;
  VariableMapping varTableMapping[] = {
    {"melon  ", &melon},
    {NULL, NULL},
  };
  char *line = "assign melon = 89   ";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_ASSERT_EQUAL(89, melon);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}
*/
void test_parseTextAndAssignValues_given_text_without_assign_should_throw_ERR_UNKNOWN_COMMAND(void) {
  CEXCEPTION_T e;
  int papaya = 0;
  VariableMapping varTableMapping[] = {
    {"papaya", &papaya},
    {NULL, NULL},
  };
  char *line = "  papaya = 345 ";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_UNKNOWN_COMMAND. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_UNKNOWN_COMMAND, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_malform_ciku_without_number_should_throw_ERR_NOT_A_NUMBER(void) {
  CEXCEPTION_T e;
  int ciku = 0;
  VariableMapping varTableMapping[] = {
    {"ciku", &ciku},
    {NULL, NULL},
  };
  char *line = "assign ciku =  durian = 6";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_NOT_A_NUMBER. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_NOT_A_NUMBER, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_malform_pineapple_without_equal_sign_should_throw_ERR_MALFORM_ASSIGN(void) {
  CEXCEPTION_T e;
  int pineapple = 0;
  VariableMapping varTableMapping[] = {
    {"pineapple", &pineapple},
    {NULL, NULL},
  };
  char *line = "assign pineapple 23 ";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_MALFORM_ASSIGN. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_MALFORM_ASSIGN, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_guava_23_cucumber_92_should_throw_ERR_UNKNOWN_VARIABLE(void) {
  CEXCEPTION_T e;
  int guava = 0;
  VariableMapping varTableMapping[] = {
    {"guava", &guava},
    {NULL, NULL},
  };
  char *line = "assign guava=23 cucumber=92";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_UNKNOWN_VARIABLE. But no exception thrown.");
  } Catch(e) {
    TEST_ASSERT_EQUAL(23, guava);
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_UNKNOWN_VARIABLE, e->errorCode);
    freeError(e);
  }
}
