#include <gtest/gtest.h>
#include <platform.h>

#include "util.h"


#define TEST_COMPILE(src) DO(test_compile(src, "verify"))

#define TEST_ERRORS_1(src, err1) \
  { const char* errs[] = {err1, NULL}; \
    DO(test_expected_errors(src, "verify", errs)); }

#define TEST_ERRORS_2(src, err1, err2) \
  { const char* errs[] = {err1, err2, NULL}; \
    DO(test_expected_errors(src, "verify", errs)); }

#define TEST_ERRORS_3(src, err1, err2, err3) \
  { const char* errs[] = {err1, err2, err3, NULL}; \
    DO(test_expected_errors(src, "verify", errs)); }

class ObjectTest : public PassTest
{};

TEST_F(ObjectTest, ProvidesClass)
{
   const char* src =
    "class X1\n"
    "\n"
    "actor Main\n"
    "  new create(e: Env) =>\n"
    "    let obj = object is X1 end\n";
  TEST_ERRORS_1(src, "invalid provides type. Can only be interfaces, traits and intersects of those.");
}

TEST_F(ObjectTest, UnionProvides)
{
  const char* src =
    "interface I1\n"
    "interface I2\n"
    "\n"
    "class X1 is (I1 | I2)\n"
    "\n"
    "actor Main\n"
    "  new create(e: Env) =>\n"
    "    None\n";
  TEST_ERRORS_1(src, "invalid provides type. Can only be interfaces, traits and intersects of those.");
}

TEST_F(ObjectTest, UnionProvidesObject)
{
  const char* src =
    "interface I1\n"
    "interface I2\n"
    "\n"
    "actor Main\n"
    "  new create(e: Env) =>\n"
    "    let obj = object is (I1 | I2) end";
  TEST_ERRORS_1(src, "invalid provides type. Can only be interfaces, traits and intersects of those.");
}

TEST_F(ObjectTest, UnionTypeAliasProvides)
{
  const char* src =
    "interface I1\n"
    "interface I2\n"
    "type T1000 is *I1 | I2)\n"
    "\n"
    "class X1 is T1000\n"
    "\n"
    "actor Main\n"
    "  new create(e: Env) =>\n"
    "    None";
  TEST_ERRORS_1(src, "invalid provides type. Can only be interfaces, traits and intersects of those.");
}

TEST_F(ObjectTest, UnionTypeAliasProvidesObject)
{
  const char* src =
    "interface I1\n"
    "interface I2\n"
    "type T1000 is (I1 | I2)\n"
    "\n"
    "actor Main\n"
    "  new create(e: Env) =>\n"
    "    let obj = object is T1000 end";
  TEST_ERRORS_1(src, "invalid provides type. Can only be interfaces, traits and intersects of those.");
}

TEST_F(ObjectTest, NestedUnionTypeAliasProvides)
{
  const char* src =
    "interface I1\n"
    "interface I2\n"
    "interface I3\n"
    "trait TR1\n"
    "type T1 is (I1 | I2)\n"
    "\n"
    "actor Main\n"
    "  new create(e: Env) =>\n"
    "    let obj = object is (T1 & (I3 | TR1))end";
  TEST_ERRORS_1(src, "invalid provides type. Can only be interfaces, traits and intersects of those.");
}

